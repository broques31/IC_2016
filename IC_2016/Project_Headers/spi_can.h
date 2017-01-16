/*
 * spi_can.h
 *
 *  Created on: Jan 16, 2017
 *      Author: Antoine
 */
/*

/*! \mainpage SPI Driver for MPC5604B_MV27
*
* \section intro_sec About
*
*	This driver provides a simple user interface for using
*	the three DSPI modules on this microcontroller. It provides
*	high level data transfer functions that can run on either background
*	or foreground, using Transfer Complete interrupts as needed.
*
*	A lot of flexibility is still available to the user via some Macros for
*	modifying Transfer and Data attributes, or with a lot of different transfer
*	methods for different needs.
*
*	The following code shows how the module is used:
*
*	\code
struct _SPI_DRV SPI[];			//SPI variable has to be imported from the SPI Driver module, do not forget this line!
uint16_t RxData[128];			//An array for storing received data
uint16_t i;						//A dummy variable.
int main(void) {
  	initModesAndClks();     //remember to enable DSPI module with PCTL registers, and set Sys_Clk(=Peripheral_Clock) to 64MHz
  							//if you wish to use predefined baud-rates
  	initPeriClkGen();            
  	disableWatchdog();           
	initialise_SPI_DRIVER();		//must be called before using the driver
  	enableIrq();
  	
    SPI[0].init(SPI_BAUD_62500, SPI_DELAY_DEFAULT);	//Initialise SPI module you wish to use, in this example PORT_A of DSPI0 is defined
    SPI[1].init(SPI_BAUD_62500, SPI_DELAY_DEFAULT);	//and PORT_E of DSPI1, and they are connected with jumper wires.
	
	//Following lines test the driver with different methods and changing
	//DSPI modules roles as it goes (master/slave, tx/rx etc..). At the end of the
	//program you can check the memory map, @RxData and see if there has been any undesirable behaviours.
	//For instance, it is practical for setting right values for the Delay Attributes.
	
    SPI[1].listen(RxData, 6,1);		//Here listen is running on the background, after each frame transfer
    								//an interrupt incerements RX_Index and waits for the next data to be received.
    								//Useful for a slave device waiting for commands.
  	for(i=0xA500;i<0xA509;i++)
  	{
  		SPI[0].write(&i);			//Write a single data, runs only on foreground. Can be used to send quick commands.
  	}
   	while (!(SPI[0].Completed && SPI[1].Completed)){}	//Always wait for things to be completed when using background methods.
    SPI[0].listen_till((RxData+6), 0x5A1F,1);		//This time listen method runs until a specific data is received.
    												//Would be practical for using on ascii transmissions ending with '\0'.
  	for(i=0x5A00;i<0x5A2F;i++)
  	{
  		SPI[1].write(&i);
  	}
   	while (!(SPI[0].Completed && SPI[1].Completed)){}
   	
   	i=0xD6E1;
   	SPI[0].show(&i,1);								//show method, running on the background, places a singla data on TX Buffer
   													//and when the transfer is completed, an interrupt updates its flags.
	SPI[1].read(RxData+40);							//Read method, receives specific data from a slave. Could be used to
													//get a chip's status.
  	while (!(SPI[0].Completed && SPI[1].Completed)){}
  	
  	i=0x0666;										//Roles are inverted now, to check if any bugs related to the driver exists.
  	SPI[1].show(&i,1);								//Methods set the modules to master or to slave according to their needs.
	SPI[0].read(RxData+45);
  	while (!(SPI[0].Completed && SPI[1].Completed)){}
  	
  	SPI[0].listen((RxData+50), 4,1);				//Now both modules are running on the background, 'write array' get the next half word
  	SPI[1].write_array((uint16_t*)"Coucou!\0",4,1);	//when the current one is transmitted and 'listen' manages the RX array.
  													//In real situations, it would be absur to transfer data between two SPI modules
  													//on the same chip, so it isn't primal if one of the interrupts conflict with the other one.
  													//(Didn't happen in these tests though. Not even with 4MHz SCK clock.)
   	while (!(SPI[0].Completed && SPI[1].Completed)){}
   	
  	SPI[1].listen_till((RxData+60), 0,1);			//Reversed roles.
  	SPI[0].write_array((uint16_t*)"The night is dark, and full of terror.\0\0",20,1);
   	while (!(SPI[1].Completed && SPI[0].Completed)){}
   	
   	SPI[1].show_array((uint16_t*)"Lannisters send their regards.",16,1);	//These are practical for checking delay attributes. If those are
   	SPI[0].read_array(RxData+85,16,0);										//too short and error on MSB of frames will occur.Or sometimes repeated frames.
   	while (!(SPI[0].Completed && SPI[1].Completed)){}						//It rarely occurs with medium speed ports but right delay amounts are primordial for slow ports.
   	
  	SPI[0].show_array((uint16_t*)"Lannisters send their regards.",16,1);
   	SPI[1].read_array(RxData+110,16,0);
   	while (!(SPI[0].Completed && SPI[1].Completed)){}
  	
  	i=0x0A50;
  	SPI[1].show(&i,1);
  	i=0xF5AF;
	SPI[0].exchange(&i,RxData+127);
   	while (!(SPI[0].Completed && SPI[1].Completed)){}
   	while (1)    //End of program 
  	{
  	}
}
*	\endcode
*
*
*
*/

#ifndef _SPI_CAN_H
#define _SPI_CAN_H
#include "MPC5645S.h"
#include "IntcInterrupts.h"
#include <string.h>

/**
 * \def SPI_ERROR();
 *
 * An inifite loop that is entered on a detectable error on the driver,
 * usually related to missing or inappropriate user parameters.
*/
#define SPI_ERROR(); 	  while(1){}

/**
 * \defgroup group1	Baud-Rate Attributes
 * \{
 * 
 * \brief SPI transfer baud-rate.
 * 
 * A simplified way for specifying the baud rate to the
 * driver, common values are defined at 64MHz peripheral clock. 
 * This 8-bit value is defined, relative to the MPC5604B doc, as:\n
 * 	-bits [3:0] : BR field of the CTAR register (baud-rate base),\n
 *  -bits [5:4] : PBR field of the CTAR register (prescaler),\n
 *  -bit 6		: DBR field of the CTAR register (double baud-rate).\n\n
 *
 * See the paragraph about baud rate on the quick start to MPC5604B document
 * for more info on choosing DBR, BR and PBR field values.\n
 *
*/
#define SPI_BAUD_25000		0x29
#define SPI_BAUD_62500		0x09
#define SPI_BAUD_100000		0x27
#define SPI_BAUD_500000		0x06
#define SPI_BAUD_1000000	0x05
#define SPI_BAUD_4000000	0x03
/**
 * \}
*/

/**
 * 	\defgroup group2 Delay Attributes
 *	\brief Delay configuration for the driver.
 * 	\{
 *	\def SPI_DELAY_DEFAULT 
 *	\brief Default values specified at baud rate of 62500Hz (or higher)
 * 	for the driver, system clock being 64MHz.
 *
 * 	This 32-bit value is an example for setting delay value characteristics
 * 	of the driver. This example is set for a baud rate of 62500Hz, it can be
 * 	used for higher baud rates (not optimal though).
 * 	This value is defined relative to the MPC5604B doc as:\n
 *	-bits [3:0]: TD, after transfer delay(0 to F),\n
 *  -bits [7:4]: PTD, prescaler for after transfer delay(0 to 3),\n
 *	-bits [11:8]: ASC, after SCK delay(0 to F),\n
 *	-bits [15:12]: PASC, prescaler for after SCK delay(0 to 3),\n
 * 	-bits [19:16]: CSSCK, CS to SCK delay(0 to F),\n
 *	-bits [23:20]: PCSSCK, prescaler for CS to SCK delay(0 to 3),\n
 *	-bits [31:24]: unused.\n\n
 *
 * 	Minimum CSSCK, ASC and TD values has to be half a SCK clock period for MPC5604B,
 * 	on the other hand, external devices may have different needs, so the final values 
 *  must be the maximum of the minimum values needed by both MPC5604B and the external device.\n\n
 *
 *	Example for MPC5604B communicating with itself @ 62500Hz, a period is
 * 	1024 clock cycles when F_periph=F_sys = 64MHz so half a clock is 512 cycles.
 * 	This value can be set using a prescaler of 1 (0) and a value of 512 (8) for
 * 	each delay.
 *
*/
#define SPI_DELAY_DEFAULT 0x00080808
/**
 * \}
*/

/**
 *	\defgroup group3 Data Attributes
 *	\{
 *	\brief SPI data transfer attributes.
 *	
 *	Clock polariry and phase are set to 0 (because this config is
 *	mostly supported everywhere, if something else is needed change the init function).
 *	Similarly, MSB is always transferred first.\n\n
 */
/** \def SPI_MAX_DATA_SIZE
 *
 * Maximum array size that can be transferred (by default 128)
 * with this driver, it can be changed as needed but should be
 * enough for basic usage.
 *
*/
#define SPI_MAX_DATA_SIZE 	128
/**	
 *	\def SPI_FRAMESIZE
 * 	The framesize is by default set to the maximum of 16 but can be altered, if needed,
 *  using the SPI_FRAMESIZE define(value betweeen 4 and 16).
*/
#define SPI_FRAMESIZE 16
/**
 *	\}
*/
 
/**
 *	\defgroup group4 Signal Attributes
 *  \{
 *  \brief Information about port configurations.
 *
 *	Each of the three DSPI modes are assigned to some pins, this driver
 * 	configures these pins to match SPI requirements (push-pull output, slew rate, buffers etc) and
 * 	the user only needs to select one of the available ports for each module.
 *
 *	
 *  DSPI0 has only pins on PORT A (medium speed), pins 12-15.\n 
 *	-A12: SIN, A13: SOUT,\n
 *	-A14: SCK, A15: CS.\n\n
 *
 *	DSPI1 has three possible ports:\n
 *	-PORT C (slow), pins 2-5:\n
 *	--C2: SCK, C3:CS,\n
 *	--C4: SIN, C5:SOUT.\n
 *	-PORT E (medium speed, don't forget to remove button jumpers on TRK board), pins 2-5:\n
 *	--E2: SIN, E3:SOUT,\n
 *	--E4: SCK, E5:CS.\n
 *	-PORT H (medium speed), pins 0-3:\n
 *	--H0: SIN, H4:SOUT,\n
 *	--H2: SCK, H3:CS.\n
 *
 *	DSPI2 has two possible ports:\n
 *	-PORT C (slow), pins 12-15:\n
 *	--C12: SIN, C13:SOUT,\n
 *	--C14: SCK, C15:CS.\n
 *	-PORT E (slow), pins 12-15:\n
 *	--C12: SIN, C13:SOUT,\n
 *	--C14: SCK, C15:CS.\n
 *
*/
/**Port definition for DSPI0, there is no alternative.
*/
#define DSPI0_PORT 'A'
/**Port definition for DSPI1, alternatives are\n
 * \code
 *#define DSPI1_PORT 'E'
 *#define DSPI1_PORT 'C' 
 *\endcode
*/
#define DSPI1_PORT 'H'
/**Port definition for DSPI2, alternative is\n
 *\code
 *#define DSPI2_PORT 'C'
 *\endcode
*/
#define DSPI2_PORT 'E'
/**
 *  \}
*/

struct _SPI_DRV
{
	uint16_t* RX_Data;	/*!< A pointer to the received data (array or not).*/
	uint16_t RX_end_data;	/*!< A value used as the terminating character of the RX_array while listening/sniffing
							  	 to an undetermined amount of data. (Limited to SPI_MAX_DATA_SIZE)*/
	uint8_t RX_Data_Size; /*!< A variable that holds RX_Data's size once a transfer is completed.*/
	uint8_t RX_Index;	/*!< An internal index used for writing data to the RX array.*/
	uint16_t* TX_Data; /*!< A pointer to the transmitted data (array or not).*/
	uint8_t TX_Data_Size; /*!<A variable that holds TX_Data's size once a transfer is started.*/
	uint8_t TX_Index;	/*!<An internal index used for writing data to the TX array.*/
	uint8_t Completed;	/*!<A flag to indicate transfer status:\n 1: transfer completed,\n 0: ongoing transfer(or never happened).*/
	uint8_t State; /*!<An internal state variable used in Transfer Complete interrupts:\n 0xFF: idle,\n 
							0x01: master/slave tx\n 0x02: slave rx(known array size)\n 0x03: slave rx(known terminating data)\n*/
	uint8_t Error;		/*!<An error flag. (Not used in this version.)*/
	volatile struct DSPI_tag * DSPI; /*!< A pointer to the DSPI module for accesing peripheral registers.*/
	//Basic init/get/set
	void (*init)(int8_t, int32_t); /*!< \brief Initiatlisation method.
										Must be called before using the driver.\n
										
										Example: SPI[0].init(SPI_BAUD_62500, SPI_DELAY_DEFAULT);
										
										\param int8_t baud_rate : use an 8-bit baud-rate macro,\n
										\param int32_t delay : use a 32-bit delay attributes macro.\n
										*/
	//Basic Communication
	void (*exchange)(const uint16_t*, uint16_t*);  /*!< \brief Exchange data (Master).
														Allows a full-duplex 16-bit data transfer where the module
														is the master.\n
														
														Example: SPI[0].exchange(&command, &status); 
														A command is sent and status of the slave is received.
														
														
														\param int16_t* TX_data : give the adress of the TX data to be sent,\n
														\param int16_t* RX_data : give the adress where RX data will be stored.\n
														*/
	void (*write)(const uint16_t*);  /*!< \brief Write data (Master).
										Allows a half-duplex data transmission where the module will transmit a 16-bit
										data to a slave.\n
										
										Example:    	uint16_t i=0xD6E1;
   														SPI[0].write(&i);
										0xD6E1 is sent to a slave.
										
										\param uint16_t* TX_data : give the adress of the TX data to be sent.\n
										*/	
	void (*write_p)(const uint16_t*);  /*!< \brief Write data CS1 (Master).
											Allows a half-duplex data transmission where the module will transmit a 16-bit
											data to a slave, with another chip select (PCS1).\n
											
											Example:    	uint16_t i=0xD6E1;
	   														SPI[0].write(&i);
											0xD6E1 is sent to a slave.
											
											\param uint16_t* TX_data : give the adress of the TX data to be sent.\n
											*/	
	void (*read)(uint16_t*);	/*!< \brief Read data (Master).
										Allows a half-duplex data transmission where the module will receive a 16-bit
										data from a slave and send it an empty frame.\n
										
										Example:    	uint16_t i;
														SPI[0].read(&i);
										Received data is stored in i.
										
										\param uint16_t* RX_data : give the adress where RX data will be stored\n
										*/
	
	void (*read_p)(uint16_t*);	/*!< \brief Read data CS1 (Master).
											Allows a half-duplex data transmission where the module will receive a 16-bit
											data from a slave and send it an empty frame. With another chip select (PCS1)\n
											
											Example:    	uint16_t i;
															SPI[0].read(&i);
											Received data is stored in i.
											
											\param uint16_t* RX_data : give the adress where RX data will be stored\n
											*/
	void (*show)(const uint16_t*, int8_t);  /*!< \brief Write data (Slave).
										The module will write the data to its TX_Buffer as a slave, ready to be read by a
										master. It can either run on foreground, in which case the program will wait for
										the data to be transferred, or it can also run in background, but calling another 
										method of the driver before this data is read will result in its loss. 
										Therefore always wait for the Completed flag before moving on.\n
										
										Example:    	uint16_t i=0xD6E1;
   														SPI[0].show(&i,1);
										0xD6E1 is ready to be read by a master.
										
										\param uint16_t* TX_data : give the adress of the TX data to be sent.\n
										\param int8_t  intrpt_en: if not null the method will run in the background, else foreground.\n
										*/
	//Array Transfering
	void (*exchange_array)(const uint16_t*, uint16_t*, int8_t, int8_t); /*!< \brief Exchange data array (Master).
															Allows a full-duplex data transmission where the module will transmit an array of
															16-bit data to a slave and receive another. The size of the array is limited by the MAX_DATA_SIZE macro.
															It can either run on foreground, in which case the program will wait for
															the data to be transferred, or it can also run in background, but calling another 
															method of the driver before this data is read will result in its loss. 
															Therefore always wait for the Completed flag before moving on.\n
																	
															Example: where SPI1 and SPI0 are connected
															   	SPI[1].show_array((uint16_t*)"PWM enabled.\0\0",7,1);
														  		SPI[0].exchange_array((uint16_t*)"Show me your UART status.\0\0\0", RX_data,14,1);
														     	while (!(SPI[1].Completed && SPI[0].Completed)){}
														    	
														    Result:
														    TX_data =  "Show me your UART status.\0\0\0"
															RX_data =  "PWM enabled.\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
															
															\param const uint16_t* TX_data: give the adress of the TX data array to be sent.\n
															\param uint16_t* RX_data : address of RX data storage array.\n
															\param int8_t size: size of the data array\n
															\param int8_t intrpt_en: if not null the method will run in the background, else foreground.\n
														  */		
	void (*write_array)(const uint16_t*, int8_t, int8_t); /*!< \brief Write data array (Master).
															Allows a half-duplex data transmission where the module will transmit an array of
															16-bit data to a slave. The size of the array is limited by the MAX_DATA_SIZE macro.
															It can either run on foreground, in which case the program will wait for
															the data to be transferred, or it can also run in background, but calling another 
															method of the driver before this data is read will result in its loss. 
															Therefore always wait for the Completed flag before moving on.\n
																	
															Example: where SPI1 and SPI0 are connected
															  	SPI[1].listen_till((RxData+60), 0,1);
														  		SPI[0].write_array((uint16_t*)"The night is dark, and full of terror.\0\0",20,1);
														     	while (!(SPI[1].Completed && SPI[0].Completed)){}
															
															\param uint16_t* TX_data: give the adress of the TX data array to be sent.\n
															\param int8_t size: size of the data array
															\param int8_t intrpt_en: if not null the method will run in the background, else foreground.\n
														  */	
	void (*read_array)(uint16_t*, int8_t, int8_t);	/*!< \brief Read data array (Master).
														Allows a half-duplex data transmission where the module will receive an array of
														16-bit data from a slave and send it empty frames. The size of the array is limited by the MAX_DATA_SIZE macro.
															It can either run on foreground, in which case the program will wait for
															the data to be transferred, or it can also run in background, but calling another 
															method of the driver before this data is read will result in its loss. 
															Therefore always wait for the Completed flag before moving on.\n
														
														Example: where SPI1 and SPI0 are connected      	
															   	SPI[1].show_array((uint16_t*)"Lannisters send their regards.",16,1);
															   	SPI[0].read_array(RxData+85,16,0);															   	
															   	while (!(SPI[0].Completed && SPI[1].Completed)){}
														
														\param uint16_t* RX_data : give the adress where RX data will be stored\n
														\param int8_t size: size of the data array
														\param int8_t intrpt_en: if not null the method will run in the background, else foreground.\n
													*/	
	void (*listen)(uint16_t*, int8_t, int8_t);	/*!< \brief Read data array, given size (Slave).
														Allows a half-duplex data transmission where the module will receive an array of
														16-bit data from a master. Can be used for data sniffing.
														The size of the array is limited by the MAX_DATA_SIZE macro.
														It can either run on foreground, in which case the program will wait for
														the data to be transferred, or it can also run in background, but calling another 
														method of the driver before this data is read will result in its loss. 
														Therefore always wait for the Completed flag before moving on.\n
														
														Example: where SPI1 and SPI0 are connected      	
															  	SPI[1].write_array((uint16_t*)"Coucou!\0",4,1);															   	
															   	while (!(SPI[0].Completed && SPI[1].Completed)){}
														
														\param uint16_t* RX_data : give the adress where RX data will be stored\n
														\param int8_t size: size of the data array
														\param int8_t intrpt_en: if not null the method will run in the background, else foreground.\n
												*/	
	void (*listen_till)(uint16_t*, uint16_t, int8_t); /*!< \brief Read data array, given terminating data (Slave).
														Allows a half-duplex data transmission where the module will receive an array of
														16-bit data from a master until it receives a terminating data. Can be used for data sniffing.
														The size of the array is limited by the MAX_DATA_SIZE macro.
														It can either run on foreground, in which case the program will wait for
														the data to be transferred, or it can also run in background, but calling another 
														method of the driver before this data is read will result in its loss. 
														Therefore always wait for the Completed flag before moving on.\n
																					
														Example: where SPI1 and SPI0 are connected
														  	SPI[1].listen_till((RxData+60), 0,1);
													  		SPI[0].write_array((uint16_t*)"The night is dark, and full of terror.\0\0",20,1);
													     	while (!(SPI[1].Completed && SPI[0].Completed)){}
														
														\param uint16_t* RX_data : give the adress where RX data will be stored\n
														\param uint16_t end_data: the RX data that will put and end to the transfer
														\param int8_t intrpt_en: if not null the method will run in the background, else foreground.\n
														*/	
	
	void (*show_array)(const uint16_t*, int8_t, int8_t); /*!< \brief Write data array (Slave).
															The module will write the data to its TX_Buffer as a slave, ready to be read by a
															master.The size of the array is limited by the MAX_DATA_SIZE macro. It can either 
															run on foreground, in which case the program will wait for the data to be transferred, 
															or it can also run in background, but calling another 
															method of the driver before this data is read will result in its loss. 
															Therefore always wait for the Completed flag before moving on.\n
															
														
														Example: where SPI1 and SPI0 are connected      	
															   	SPI[1].show_array((uint16_t*)"Lannisters send their regards.",16,1);
															   	SPI[0].read_array(RxData+85,16,0);															   	
															   	while (!(SPI[0].Completed && SPI[1].Completed)){}
															
															\param uint16_t* TX_data : give the adress of the TX data to be sent.\n
															\param int8_t size: size of the data array
															\param int8_t  intrpt_en: if not null the method will run in the background, else foreground.\n
															*/
	//Handlers
	void (*EOQI_Handler)(void);	 /*!< \brief End of Queue Interrupt Handler (Unused).
										The handler is not vectored to the INTC in this version. The user can
										activate it by modifying initialise_SPI_DRIVER function and by adding
										a EOQ command to the final transmission in previous methods.
								*/
	void (*TCI_Handler)(void);	 /*!< \brief Transfer Complete Interrupt Handler.
										An interrupt handler that clears the flag and the proceeds on doing a treatment
										depending on the state of the driver. The user can customise and add new states
										if needed, current states are:\n 0xFF: idle,\n 
										0x01: master/slave tx\n 0x02: slave rx(knowing array size)\n 0x03: slave rx(knowing terminating data)\n
								*/
};
/**
 *	\defgroup group5 SPI Module Driver
 *	\{
 * 	\brief A structure to drive DSPI modules of MPC5604B.
 * 
 *	This structure regroups the DSPI registers (volatile struct DSPI_tag),
 *  some flags and information about RX/TX data (variables), and some high level
 *	functions for easy data transfer.\n
 *
 *	After each transfer function is called, Completed flag is reset and it gets Set once
 *	the transfer is completed. A transfer can be on foreground (blocking the program, no interrupts)
 *	or on the background (the program will run normally with interrupts to keep the transfer ongoing).
 *
 *	\struct _SPI_DRV
 *
 *
*/
void initialise_SPI_DRIVER(void);  /*!< \brief Initialisation function for SPI driver.
										Initializes the SPI variable with appropriate assingments on
										function pointers and activating TCI handler etc. Must be called
										before doing anything with the driver.
									*/
extern struct _SPI_DRV SPI[3];		/*!< \brief SPI driver instances.
										Variables defined on the driver structure, providing an Object Oriented
										user interface for using the driver.\n 
									*/
/**
 *	\}
*/



/**
 * \cond
*/
//Public methods

//Basic init/get/set
void _spi_drv_init_dspi0(int8_t baud_rate, int32_t delay);
void _spi_drv_init_dspi1(int8_t baud_rate, int32_t delay);
void _spi_drv_init_dspi2(int8_t baud_rate, int32_t delay);
void _spi_drv_init(int8_t i, int8_t baud_rate, int32_t delay);

//Basic Communication
void _spi_drv_exchange_dspi0(const uint16_t* TX_data, uint16_t* RX_data);
void _spi_drv_exchange_dspi1(const uint16_t* TX_data, uint16_t* RX_data);
void _spi_drv_exchange_dspi2(const uint16_t* TX_data, uint16_t* RX_data);
void _spi_drv_exchange(uint8_t i, const uint16_t* TX_data, uint16_t* RX_data);

void _spi_drv_write_dspi0(const uint16_t* TX_data);	
void _spi_drv_write_p_dspi0(const uint16_t* TX_data);	
void _spi_drv_write_dspi1(const uint16_t* TX_data);	
void _spi_drv_write_dspi2(const uint16_t* TX_data);	
void _spi_drv_write(uint8_t i, const uint16_t* TX_data);
void _spi_drv_write_p(uint8_t i, const uint16_t* TX_data);

void _spi_drv_read_dspi0(uint16_t* RX_data);
void _spi_drv_read_p_dspi0(uint16_t* RX_data);
void _spi_drv_read_dspi1(uint16_t* RX_data);
void _spi_drv_read_dspi2(uint16_t* RX_data);
void _spi_drv_read(uint8_t i, uint16_t* RX_data);
void _spi_drv_read_p(uint8_t i, uint16_t* RX_data);

void _spi_drv_show_dspi0(const uint16_t* TX_data, int8_t intrpt_en);
void _spi_drv_show_dspi1(const uint16_t* TX_data, int8_t intrpt_en);
void _spi_drv_show_dspi2(const uint16_t* TX_data, int8_t intrpt_en);

//Array Transfering
void _spi_drv_exchange_array_dspi0(const uint16_t* TX_data, uint16_t* RX_data, int8_t size, int8_t intrpt_en);
void _spi_drv_exchange_array_dspi1(const uint16_t* TX_data, uint16_t* RX_data, int8_t size, int8_t intrpt_en);
void _spi_drv_exchange_array_dspi2(const uint16_t* TX_data, uint16_t* RX_data, int8_t size, int8_t intrpt_en);
void _spi_drv_exchange_array(uint8_t i, const uint16_t* TX_data, uint16_t* RX_data, int8_t size, int8_t intrpt_en);

void _spi_drv_write_array_dspi0(const uint16_t* TX_data ,int8_t size, int8_t intrpt_en);
void _spi_drv_write_array_dspi1(const uint16_t* TX_data ,int8_t size, int8_t intrpt_en);
void _spi_drv_write_array_dspi2(const uint16_t* TX_data ,int8_t size, int8_t intrpt_en);
void _spi_drv_write_array(uint8_t i, const uint16_t* TX_data ,int8_t size, int8_t intrpt_en);

void _spi_drv_read_array_dspi0(uint16_t* RX_data, int8_t size, int8_t intrpt_en);
void _spi_drv_read_array_dspi1(uint16_t* RX_data, int8_t size, int8_t intrpt_en);
void _spi_drv_read_array_dspi2(uint16_t* RX_data, int8_t size, int8_t intrpt_en);
void _spi_drv_read_array(uint8_t i, uint16_t* RX_data, int8_t size, int8_t intrpt_en);

void _spi_drv_listen_dspi0(uint16_t* RX_data, int8_t size, int8_t intrpt_en);
void _spi_drv_listen_dspi1(uint16_t* RX_data, int8_t size, int8_t intrpt_en);
void _spi_drv_listen_dspi2(uint16_t* RX_data, int8_t size, int8_t intrpt_en);
void _spi_drv_listen(uint8_t i, uint16_t* RX_data, int8_t size, int8_t intrpt_en);

void _spi_drv_listen_till_dspi0(uint16_t* RX_data, uint16_t end_data, int8_t intrpt_en);
void _spi_drv_listen_till_dspi1(uint16_t* RX_data, uint16_t end_data, int8_t intrpt_en);
void _spi_drv_listen_till_dspi2(uint16_t* RX_data, uint16_t end_data, int8_t intrpt_en);
void _spi_drv_listen_till(uint8_t i, uint16_t* RX_data, uint16_t end_data, int8_t intrpt_en);

void _spi_drv_show_array_dspi0(const uint16_t* TX_data, int8_t size, int8_t intrpt_en);
void _spi_drv_show_array_dspi1(const uint16_t* TX_data, int8_t size, int8_t intrpt_en);
void _spi_drv_show_array_dspi2(const uint16_t* TX_data, int8_t size, int8_t intrpt_en);
void _spi_drv_show_array(uint8_t i, const uint16_t* TX_data, int8_t size, int8_t intrpt_en);

//'Private' methods

void _spi_drv_set_masterslave(uint8_t i, uint8_t master);

void _spi_drv_clr_flags(uint8_t i);

//Interrupt Handlers

void _spi_drv_tci_dspi0(void);
void _spi_drv_tci_dspi1(void);
void _spi_drv_tci_dspi2(void);
void _spi_drv_tci(uint8_t i);
/**
 * \endcond
*/

#endif
