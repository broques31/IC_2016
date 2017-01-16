/*
 * spi_can.c
 *
 *  Created on: Jan 16, 2017
 *      Author: Benjamin
 */

#include "IntcInterrupts.h"
#include "port.h"
#include "spi_can.h"

extern struct _SPI_DRV SPI[3];

//--------------------------------------
//DSPI 0 encapsulation------------------
//--------------------------------------

void _spi_drv_init_dspi0(int8_t baud_rate, int32_t delay){
	_spi_drv_init(0, baud_rate, delay);
}

void _spi_drv_exchange_dspi0(const uint16_t* TX_data, uint16_t* RX_data)
{
	_spi_drv_exchange(0,TX_data,RX_data);
}

void _spi_drv_write_dspi0(const uint16_t* TX_data)
{
	_spi_drv_write(0,TX_data);
}

void _spi_drv_write_p_dspi0(const uint16_t* TX_data)
{
	_spi_drv_write_p(0,TX_data);
}

void _spi_drv_read_dspi0(uint16_t* RX_data)
{
	_spi_drv_read(0,RX_data);
}

void _spi_drv_read_p_dspi0(uint16_t* RX_data)
{
	_spi_drv_read(0,RX_data);
}

void _spi_drv_show_dspi0(const uint16_t* TX_data, int8_t intrpt_en)
{
	_spi_drv_show_array(0, TX_data, 1, intrpt_en);
}

void _spi_drv_exchange_array_dspi0(const uint16_t* TX_data, uint16_t* RX_data, int8_t size, int8_t intrpt_en)
{
	_spi_drv_exchange_array(0,TX_data, RX_data, size, intrpt_en);
}

void _spi_drv_write_array_dspi0(const uint16_t* TX_data ,int8_t size, int8_t intrpt_en)
{
	_spi_drv_write_array(0, TX_data, size, intrpt_en);
}

void _spi_drv_read_array_dspi0(uint16_t* RX_data, int8_t size, int8_t intrpt_en)
{
	_spi_drv_read_array(0, RX_data, size, intrpt_en);	
}

void _spi_drv_listen_dspi0(uint16_t* RX_data, int8_t size, int8_t intrpt_en)
{
	_spi_drv_listen(0, RX_data, size, intrpt_en);
}

void _spi_drv_listen_till_dspi0(uint16_t* RX_data, uint16_t end_data, int8_t intrpt_en)
{
	_spi_drv_listen_till(0, RX_data, end_data, intrpt_en);
}

void _spi_drv_show_array_dspi0(const uint16_t* TX_data, int8_t size, int8_t intrpt_en)
{
	_spi_drv_show_array(0, TX_data, size, intrpt_en);
}

void _spi_drv_tci_dspi0(void)
{
	_spi_drv_tci(0);
}

//--------------------------------------
//DSPI 1 encapsulation------------------
//--------------------------------------

void _spi_drv_init_dspi1(int8_t baud_rate, int32_t delay)
{
	_spi_drv_init(1, baud_rate, delay);
}

void _spi_drv_exchange_dspi1(const uint16_t* TX_data, uint16_t* RX_data)
{
	_spi_drv_exchange(1,TX_data,RX_data);
}

void _spi_drv_write_dspi1(const uint16_t* TX_data)
{
	_spi_drv_write(1,TX_data);
}

void _spi_drv_read_dspi1(uint16_t* RX_data)
{
	_spi_drv_read(1,RX_data);
}

void _spi_drv_show_dspi1(const uint16_t* TX_data, int8_t intrpt_en)
{
	_spi_drv_show_array(1, TX_data, 1, intrpt_en);
}

void _spi_drv_exchange_array_dspi1(const uint16_t* TX_data, uint16_t* RX_data, int8_t size, int8_t intrpt_en)
{
	_spi_drv_exchange_array(1,TX_data, RX_data, size, intrpt_en);
}

void _spi_drv_write_array_dspi1(const uint16_t* TX_data ,int8_t size, int8_t intrpt_en)
{	
	_spi_drv_write_array(1, TX_data, size, intrpt_en);
}

void _spi_drv_read_array_dspi1(uint16_t* RX_data, int8_t size, int8_t intrpt_en)
{
	_spi_drv_read_array(1, RX_data, size, intrpt_en);
}

void _spi_drv_listen_dspi1(uint16_t* RX_data, int8_t size, int8_t intrpt_en)
{
	_spi_drv_listen(1,RX_data, size, intrpt_en);
}

void _spi_drv_listen_till_dspi1(uint16_t* RX_data, uint16_t end_data, int8_t intrpt_en)
{
	_spi_drv_listen_till(1, RX_data, end_data, intrpt_en);	
}

void _spi_drv_show_array_dspi1(const uint16_t* TX_data, int8_t size, int8_t intrpt_en)
{
	_spi_drv_show_array(1,TX_data, size, intrpt_en);
}

void _spi_drv_tci_dspi1(void)
{
	_spi_drv_tci(1);
}

//--------------------------------------
//DSPI 2 encapsulation------------------
//--------------------------------------

void _spi_drv_init_dspi2(int8_t baud_rate, int32_t delay)
{
	_spi_drv_init(2, baud_rate, delay);
}

void _spi_drv_exchange_dspi2(const uint16_t* TX_data, uint16_t* RX_data)
{
	_spi_drv_exchange(2,TX_data,RX_data);
}

void _spi_drv_write_dspi2(const uint16_t* TX_data)
{
	_spi_drv_write(2,TX_data);
}

void _spi_drv_read_dspi2(uint16_t* RX_data)
{
	_spi_drv_read(2,RX_data);
}

void _spi_drv_show_dspi2(const uint16_t* TX_data, int8_t intrpt_en)
{
	_spi_drv_show_array(2, TX_data, 1, intrpt_en);
}

void _spi_drv_exchange_array_dspi2(const uint16_t* TX_data, uint16_t* RX_data, int8_t size, int8_t intrpt_en)
{
	_spi_drv_exchange_array(2,TX_data, RX_data, size, intrpt_en);
}

void _spi_drv_write_array_dspi2(const uint16_t* TX_data ,int8_t size, int8_t intrpt_en)
{	
	_spi_drv_write_array(2, TX_data, size, intrpt_en);
}

void _spi_drv_read_array_dspi2(uint16_t* RX_data, int8_t size, int8_t intrpt_en)
{
	_spi_drv_read_array(2, RX_data, size, intrpt_en);
}

void _spi_drv_listen_dspi2(uint16_t* RX_data, int8_t size, int8_t intrpt_en)
{
	_spi_drv_listen(2,RX_data, size, intrpt_en);
}

void _spi_drv_listen_till_dspi2(uint16_t* RX_data, uint16_t end_data, int8_t intrpt_en)
{
	_spi_drv_listen_till(2, RX_data, end_data, intrpt_en);	
}

void _spi_drv_show_array_dspi2(const uint16_t* TX_data, int8_t size, int8_t intrpt_en)
{
	_spi_drv_show_array(2,TX_data, size, intrpt_en);
}

void _spi_drv_tci_dspi2(void)
{
	_spi_drv_tci(2);
}

//--------------------------------------
//CORE Methods,  Common Algorithms ------------------
//--------------------------------------

void _spi_drv_set_masterslave(uint8_t i, uint8_t master)
{
	//Set the configuration register
	if(master)
	{
		SPI[i].DSPI->MCR.R |= 0x80000000; 
	}
	else
	{
		SPI[i].DSPI->MCR.R &= 0x7FFFFFFF; 
	}

	if(i==0)
	{
		//Set I/O pads
		if(DSPI0_PORT=='A')
		{
			SIU.PCR[PB7].R = 0x0103;  /* MPC56xxB: A12 as DSPI_0 SIN input */
			SIU.PCR[PB8].R = 0x0604;  /* MPC56xxB: A13 as DSPI_0 SOUT output */
			if(master)
			{
				SIU.PCR[PB9].R = 0x0604;  /* MPC56xxB: A14 as DSPI_0 SCK output */
				SIU.PCR[PH4].R = 0x0604;  /* MPC56xxB: A15 as DSPI_0 PCS0 output */
				SIU.PCR[PB13].R = 0x0604;  /* MPC56xxB: B12 as DSPI_0 PCS1 output */
			}
			else
			{
				SIU.PCR[PB9].R = 0x0503;  /* MPC56xxB: A14 as DSPI_0 SCK input */
				SIU.PSMI[42].R = 0;             /* MPC56xxB: Select PCR 14 for DSPI_0 SCK input */
				SIU.PCR[PH4].R = 0x0503;  /* MPC56xxB: A15 as DSPI_0 PCS0 input */
				SIU.PSMI[45].R = 1;             /* MPC56xxB: Select PCR 15 for DSPI_0 CS input */
				SIU.PCR[PB13].R = 0x0503;  /* MPC56xxB: B12 as DSPI_0 PCS1 input */
				SIU.PSMI[35].R = 0;             /* MPC56xxB: Select PCR 28 for DSPI_0 CS1 input */
			}
		}
		else
		{
			SPI_ERROR();
		}
	}
	else if(i==1)
	{
		//Set I/O Pads
		if(DSPI1_PORT=='C')
		{
			SIU.PCR[36].R = 0x0103;  /* MPC56xxB: C4 as DSPI_1 SIN input */
				SIU.PSMI[8].R = 0;             /* MPC56xxB: Select PCR 36 for DSPI_1 SIN input */	  	
			SIU.PCR[37].R = 0x0600;  /* MPC56xxB: C5 as DSPI_1 SOUT output */
			if (master)
			{
				SIU.PCR[34].R = 0x0600;  /* MPC56xxB: C2 as DSPI_1 SCK output */
				SIU.PCR[35].R = 0x0600;  /* MPC56xxB: C3 as DSPI_1 PCS0 output */
			}
			else
			{
				SIU.PCR[34].R = 0x0503;  /* MPC56xxB: C2 as DSPI_1 SCK input */
				SIU.PSMI[7].R = 0;             /* MPC56xxB: Select PCR 34 for DSPI_1 SCK input */
				SIU.PCR[35].R = 0x0503;  /* MPC56xxB: C3 as DSPI_1 PCS0 input */
				SIU.PSMI[9].R = 0;             /* MPC56xxB: Select PCR 35 for DSPI_1 CS input */	  	
			}
		}
		else if(DSPI1_PORT=='H')
		{
			SIU.PCR[112].R = 0x0103;  /* MPC56xxB: H0 as DSPI_1 SIN input */
				SIU.PSMI[8].R = 2;             /* MPC56xxB: Select PCR 36 for DSPI_1 SIN input */	  	
			SIU.PCR[113].R = 0x0A04;  /* MPC56xxB: H1 as DSPI_1 SOUT output */
			if (master)
			{
				SIU.PCR[114].R = 0x0A04;  /* MPC56xxB: H2 as DSPI_1 SCK output */
				SIU.PCR[115].R = 0x0A04;  /* MPC56xxB: H3 as DSPI_1 PCS0 output */
			}
			else
			{
				SIU.PCR[114].R = 0x0903;  /* MPC56xxB: H2 as DSPI_1 SCK input */
				SIU.PSMI[7].R = 2;             /* MPC56xxB: Select PCR 34 for DSPI_1 SCK input */ 	
				SIU.PCR[115].R = 0x0903;  /* MPC56xxB: H3 as DSPI_1 PCS0 input */
				SIU.PSMI[9].R = 3;             /* MPC56xxB: Select PCR 115 for DSPI_1 CS input */	 
			}
		}
		else if(DSPI1_PORT=='E')
		{
			SIU.PCR[66].R = 0x0103;  /* MPC56xxB: E2 as DSPI_1 SIN input */
				SIU.PSMI[8].R = 1;             /* MPC56xxB: Select PCR 66 for DSPI_1 SIN input */	  	
			SIU.PCR[67].R = 0x0A04;  /* MPC56xxB: E3 as DSPI_1 SOUT output */
			if (master)
			{
				SIU.PCR[68].R = 0x0A04;  /* MPC56xxB: E4 as DSPI_1 SCK output */
				SIU.PCR[69].R = 0x0A04;  /* MPC56xxB: E5 as DSPI_1 PCS0 output */
			}
			else
			{
				SIU.PCR[68].R = 0x0903;  /* MPC56xxB: E4 as DSPI_1 SCK input */
				SIU.PSMI[7].R = 1;             /* MPC56xxB: Select PCR 64 for DSPI_1 SCK input */
				SIU.PCR[69].R = 0x0903;  /* MPC56xxB: E5 as DSPI_1 PCS0 input */
				SIU.PSMI[9].R = 2;             /* MPC56xxB: Select PCR 65 for DSPI_1 CS input */	  	
			}
		}
		else
		{
			SPI_ERROR();
		}
	}
	else if(i==2)
	{
		//Set I/O Pads
		if(DSPI2_PORT=='C')
		{
			SIU.PCR[44].R = 0x0103;  /* MPC56xxB: C12 as DSPI_2 SIN input */
				SIU.PSMI[11].R = 0;             /* MPC56xxB: Select PCR 44 for DSPI_2 SIN input */	  	
			SIU.PCR[45].R = 0x0A00;  /* MPC56xxB: C13 as DSPI_2 SOUT output */
			if (master)
			{
				SIU.PCR[46].R = 0x0A00;  /* MPC56xxB: C14 as DSPI_2 SCK output */
				SIU.PCR[47].R = 0x0A00;  /* MPC56xxB: C15 as DSPI_2 PCS0 output */
			}
			else
			{
				SIU.PCR[46].R = 0x0903;  /* MPC56xxB: C14 as DSPI_2 SCK input */
				SIU.PSMI[10].R = 0;             /* MPC56xxB: Select PCR 46 for DSPI_2 SCK input */
				SIU.PCR[47].R = 0x0903;  /* MPC56xxB: C15 as DSPI_2 PCS0 input */
				SIU.PSMI[12].R = 0;             /* MPC56xxB: Select PCR 47 for DSPI_2 CS input */	  	
			}
		}
		else if(DSPI2_PORT=='E')
		{
			SIU.PCR[76].R = 0x0103;  /* MPC56xxB: E12 as DSPI_2 SIN input */
				SIU.PSMI[11].R = 1;             /* MPC56xxB: Select PCR 76 for DSPI_2 SIN input */	  	
			SIU.PCR[77].R = 0x0600;  /* MPC56xxB: E13 as DSPI_2 SOUT output */
			if (master)
			{
				SIU.PCR[78].R = 0x0600;  /* MPC56xxB: E14 as DSPI_2 SCK output */
				SIU.PCR[79].R = 0x0600;  /* MPC56xxB: E15 as DSPI_2 PCS0 output */
			}
			else
			{
				SIU.PCR[78].R = 0x0503;  /* MPC56xxB: E14 as DSPI_2 SCK input */
				SIU.PSMI[10].R = 1;             /* MPC56xxB: Select PCR 78 for DSPI_2 SCK input */
				SIU.PCR[79].R = 0x0503;  /* MPC56xxB: E15 as DSPI_2 PCS0 input */
				SIU.PSMI[12].R = 1;             /* MPC56xxB: Select PCR 79 for DSPI_2 CS input */	  	
			}
		}
		else
		{
			SPI_ERROR();
		}
	}
}

void _spi_drv_clr_flags(uint8_t i)
{
	SPI[i].RX_Data_Size = 0;
	SPI[i].RX_Index = 0;
	SPI[i].TX_Data_Size = 0;
	SPI[i].TX_Index = 0;
	SPI[i].Completed = 0;
	SPI[i].Error = 0;
	SPI[i].RX_end_data = 0;
	SPI[i].DSPI->RSER.B.EOQF_RE = 0;
	SPI[i].DSPI->RSER.B.TCF_RE = 0;
	SPI[i].DSPI->MCR.B.CLR_RXF = 1;
	SPI[i].DSPI->MCR.B.CLR_TXF = 1;
	SPI[i].DSPI->SR.R |= 0x8A0A0000;   // 
}

void _spi_drv_init(int8_t i, int8_t baud_rate, int32_t delay)
{
	SPI[i].DSPI->MCR.R = 0x00010001;   /* There will be no overwriting,
									FRZ enabled for debugging,
									only one chip select for the moment*/
	
	SPI[i].DSPI->CTAR[0].B.DBR = (baud_rate & 0x40)>>6;
	
	if(SPI_FRAMESIZE > 16)
	{
		SPI[i].DSPI->CTAR[0].B.FMSZ=0xF;
	}
	else if(SPI_FRAMESIZE < 4)
	{
		SPI[i].DSPI->CTAR[0].B.FMSZ=0x3;
	}
	else
	{
		SPI[i].DSPI->CTAR[0].B.FMSZ=(SPI_FRAMESIZE-1);
	}
	//By reset:
	/*
	SPI[i].DSPI->CTAR[0].B.CPOL = 0;
	SPI[i].DSPI->CTAR[0].B.CPHA = 0;
	SPI[i].DSPI->CTAR[0].B.LSBFE = 0;*/
	
	SPI[i].DSPI->CTAR[0].B.PBR = (baud_rate & 0x30)>>4;
	SPI[i].DSPI->CTAR[0].B.BR =  (baud_rate & 0x0F);

	SPI[i].DSPI->CTAR[0].B.PCSSCK = (delay & 0x300000)>> 20;
	SPI[i].DSPI->CTAR[0].B.CSSCK =  (delay & 0x0F0000) >> 16;

	SPI[i].DSPI->CTAR[0].B.PASC = (delay & 0x3000)>>12;
	SPI[i].DSPI->CTAR[0].B.ASC =  (delay & 0x0F00)>>8;

	SPI[i].DSPI->CTAR[0].B.PDT = (delay & 0x30)>>4;
	SPI[i].DSPI->CTAR[0].B.DT =  (delay & 0x0F);

	_spi_drv_set_masterslave(i, 0);

	SPI[i].DSPI->MCR.B.HALT = 0x0;
}

void _spi_drv_exchange(uint8_t i, const uint16_t* TX_data, uint16_t* RX_data)
{
	SPI[i].DSPI->MCR.B.HALT = 0x1;
	_spi_drv_clr_flags(i);
	if (!SPI[i].DSPI->MCR.B.MSTR) _spi_drv_set_masterslave(i, 1);
	SPI[i].DSPI->MCR.B.HALT = 0x0;

	SPI[i].TX_Data = (uint16_t*) TX_data;
	SPI[i].RX_Data = (uint16_t*) RX_data;
	while(!SPI[i].DSPI->SR.B.TFFF) {}
	SPI[i].DSPI->PUSHR.R = 0x00010000 | (int32_t) *TX_data;
	while(!SPI[i].DSPI->SR.B.TCF) {}
	SPI[i].DSPI->SR.B.TCF = 1;
	while(!SPI[i].DSPI->SR.B.RFDF) {}
	*RX_data = (uint16_t) SPI[i].DSPI->POPR.R;
	SPI[i].Completed = 1;
}

void _spi_drv_write(uint8_t i, const uint16_t* TX_data)
{
	SPI[i].DSPI->MCR.B.HALT = 0x1;
	_spi_drv_clr_flags(i);
	if (!SPI[i].DSPI->MCR.B.MSTR) _spi_drv_set_masterslave(i,1);
	SPI[i].DSPI->MCR.B.HALT = 0x0;

	SPI[i].TX_Data = (uint16_t*) TX_data;
	while(!SPI[i].DSPI->SR.B.TFFF) {}
	SPI[i].DSPI->PUSHR.R = 0x00010000 | *TX_data;
	while(!SPI[i].DSPI->SR.B.TCF) {}
	SPI[i].DSPI->SR.B.TCF = 1;
	SPI[i].Completed = 1;
}

//write with another chip select (PCS1)
void _spi_drv_write_p(uint8_t i, const uint16_t* TX_data)
{
	SPI[i].DSPI->MCR.B.HALT = 0x1;
	_spi_drv_clr_flags(i);
	if (!SPI[i].DSPI->MCR.B.MSTR) _spi_drv_set_masterslave(i,1);
	SPI[i].DSPI->MCR.B.HALT = 0x0;

	SPI[i].TX_Data = (uint16_t*) TX_data;
	while(!SPI[i].DSPI->SR.B.TFFF) {}
	SPI[i].DSPI->PUSHR.R = 0x00020000 | *TX_data;
	while(!SPI[i].DSPI->SR.B.TCF) {}
	SPI[i].DSPI->SR.B.TCF = 1;
	SPI[i].Completed = 1;
}

void _spi_drv_read(uint8_t i, uint16_t* RX_data)
{
	SPI[i].DSPI->MCR.B.HALT = 0x1;
	_spi_drv_clr_flags(i);
	if (!SPI[i].DSPI->MCR.B.MSTR) _spi_drv_set_masterslave(i,1);
	SPI[i].DSPI->MCR.B.HALT = 0x0;

	SPI[i].RX_Data = (uint16_t*) RX_data;
	while(!SPI[i].DSPI->SR.B.TFFF) {}
	SPI[i].DSPI->PUSHR.R = 0x00010000;
	while(!SPI[i].DSPI->SR.B.TCF) {}
	SPI[i].DSPI->SR.B.TCF = 1;
	while(!SPI[i].DSPI->SR.B.RFDF) {}
	*RX_data = (uint16_t) SPI[i].DSPI->POPR.R;
	SPI[i].Completed = 1;
}

//read with another chip select (PCS1)
void _spi_drv_read_p(uint8_t i, uint16_t* RX_data)
{
	SPI[i].DSPI->MCR.B.HALT = 0x1;
	_spi_drv_clr_flags(i);
	if (!SPI[i].DSPI->MCR.B.MSTR) _spi_drv_set_masterslave(i,1);
	SPI[i].DSPI->MCR.B.HALT = 0x0;

	SPI[i].RX_Data = (uint16_t*) RX_data;
	while(!SPI[i].DSPI->SR.B.TFFF) {}
	SPI[i].DSPI->PUSHR.R = 0x00020000;
	while(!SPI[i].DSPI->SR.B.TCF) {}
	SPI[i].DSPI->SR.B.TCF = 1;
	while(!SPI[i].DSPI->SR.B.RFDF) {}
	*RX_data = (uint16_t) SPI[i].DSPI->POPR.R;
	SPI[i].Completed = 1;
}

void _spi_drv_exchange_array(uint8_t i, const uint16_t* TX_data, uint16_t* RX_data, int8_t size, int8_t intrpt_en)
{
	if (size<=SPI_MAX_DATA_SIZE)
	{
		SPI[i].DSPI->MCR.B.HALT = 0x1;
		_spi_drv_clr_flags(i);
		if (!SPI[i].DSPI->MCR.B.MSTR) _spi_drv_set_masterslave(i,1);
		SPI[i].DSPI->MCR.B.HALT = 0x0;

		SPI[i].TX_Data = (uint16_t*) TX_data;
		SPI[i].TX_Data_Size = size;
		SPI[i].RX_Data = (uint16_t*) RX_data;
		SPI[i].RX_Data_Size = size;
		
		if(intrpt_en)
		{
			SPI[i].DSPI->RSER.B.EOQF_RE=1;
			SPI[i].DSPI->RSER.B.TCF_RE=1;
			
			SPI[i].State=0x4;
			while(!SPI[i].DSPI->SR.B.TFFF) {}
			SPI[i].DSPI->PUSHR.R = 0x00010000 | SPI[i].TX_Data[SPI[i].TX_Index];
		}
		else
		{
			for(;SPI[i].TX_Index < SPI[i].TX_Data_Size; SPI[i].TX_Index++)
			{
				while(!SPI[i].DSPI->SR.B.TFFF) {}
				SPI[i].DSPI->PUSHR.R = 0x00010000 | SPI[i].TX_Data[SPI[i].TX_Index];
				while(!SPI[i].DSPI->SR.B.TCF) {}
				SPI[i].DSPI->SR.R |= 0x90000000;
				while(!SPI[i].DSPI->SR.B.RFDF) {}
				SPI[i].RX_Data[SPI[i].RX_Index++] = (uint16_t) SPI[i].DSPI->POPR.R;
				SPI[i].DSPI->SR.B.TCF = 1;
			}
			SPI[i].Completed = 1;
		}
	}
	else
	{
		SPI_ERROR();
	}
}

void _spi_drv_write_array(uint8_t i, const uint16_t* TX_data ,int8_t size, int8_t intrpt_en)
{
	if (size<=SPI_MAX_DATA_SIZE)
	{
		SPI[i].DSPI->MCR.B.HALT = 0x1;
		_spi_drv_clr_flags(i);
		if (!SPI[i].DSPI->MCR.B.MSTR) _spi_drv_set_masterslave(i,1);
		SPI[i].DSPI->MCR.B.HALT = 0x0;

		SPI[i].TX_Data = (uint16_t*) TX_data;
		SPI[i].TX_Data_Size = size;

		if(intrpt_en)
		{
			SPI[i].DSPI->RSER.B.EOQF_RE=1;
			SPI[i].DSPI->RSER.B.TCF_RE=1;
			
			SPI[i].State=0x1;
			while(!SPI[i].DSPI->SR.B.TFFF) {}
			SPI[i].DSPI->PUSHR.R = 0x00010000 | SPI[i].TX_Data[SPI[i].TX_Index];
		}
		else
		{
			for(;SPI[i].TX_Index < SPI[i].TX_Data_Size; SPI[i].TX_Index++)
			{
				while(!SPI[i].DSPI->SR.B.TFFF) {}
				SPI[i].DSPI->PUSHR.R = 0x00010000 | SPI[i].TX_Data[SPI[i].TX_Index];
				while(!SPI[i].DSPI->SR.B.TCF) {}
				SPI[i].DSPI->SR.B.TCF = 1;
			}
			SPI[i].Completed = 1;
		}
	}
	else
	{
		SPI_ERROR();
	}	
}

void _spi_drv_read_array(uint8_t i, uint16_t* RX_data, int8_t size, int8_t intrpt_en)
{
	if (size<=SPI_MAX_DATA_SIZE)
	{
		SPI[i].DSPI->MCR.B.HALT = 0x1;
		_spi_drv_clr_flags(i);
		if (!SPI[i].DSPI->MCR.B.MSTR) _spi_drv_set_masterslave(i,1);
		SPI[i].DSPI->MCR.B.HALT = 0x0;

		SPI[i].RX_Data = (uint16_t*) RX_data;
		SPI[i].RX_Data_Size = size;

		if(intrpt_en)
		{
			SPI[i].DSPI->RSER.B.EOQF_RE=1;
			SPI[i].DSPI->RSER.B.TCF_RE=1;
			
			SPI[i].State=0x2;
			while(!SPI[i].DSPI->SR.B.TFFF) {}
			SPI[i].DSPI->PUSHR.R = 0x00010000;
		}
		else
		{
			while(SPI[i].RX_Index < SPI[i].RX_Data_Size)
			{
				while(!SPI[i].DSPI->SR.B.TFFF) {}
				SPI[i].DSPI->PUSHR.R = 0x00010000;
				while(!SPI[i].DSPI->SR.B.TCF) {}
				SPI[i].DSPI->SR.R |= 0x90000000;
				while(!SPI[i].DSPI->SR.B.RFDF) {}
				SPI[i].RX_Data[SPI[i].RX_Index++] = (uint16_t) SPI[i].DSPI->POPR.R;
			}
			SPI[i].Completed = 1;
		}
	}
	else
	{
		SPI_ERROR();
	}	
}

void _spi_drv_listen(uint8_t i, uint16_t* RX_data, int8_t size, int8_t intrpt_en)
{
	if (size<=SPI_MAX_DATA_SIZE)
	{
		SPI[i].DSPI->MCR.B.HALT = 0x1;
		_spi_drv_clr_flags(i);
		if (SPI[i].DSPI->MCR.B.MSTR) _spi_drv_set_masterslave(i,0);
		SPI[i].DSPI->MCR.B.HALT = 0x0;

		SPI[i].RX_Data = (uint16_t*) RX_data;
		SPI[i].RX_Data_Size = size;

		if(intrpt_en)
		{
			SPI[i].DSPI->RSER.B.EOQF_RE=1;
			SPI[i].DSPI->RSER.B.TCF_RE=1;
			
			SPI[i].State=0x2;
		}
		else
		{
			while(SPI[i].RX_Index < SPI[i].RX_Data_Size)
			{
				while(!SPI[i].DSPI->SR.B.TCF) {}
				SPI[i].DSPI->SR.R |= 0x90000000;
				while(!SPI[i].DSPI->SR.B.RFDF) {}
				SPI[i].RX_Data[SPI[i].RX_Index++] = (uint16_t) SPI[i].DSPI->POPR.R;
			}
			SPI[i].Completed = 1;
		}
	}
	else
	{
		SPI_ERROR();
	}	
}

void _spi_drv_listen_till(uint8_t i, uint16_t* RX_data, uint16_t end_data, int8_t intrpt_en)
{
	SPI[i].DSPI->MCR.B.HALT = 0x1;
	_spi_drv_clr_flags(i);
	if (SPI[i].DSPI->MCR.B.MSTR) _spi_drv_set_masterslave(i,0);
	SPI[i].DSPI->MCR.B.HALT = 0x0;

	SPI[i].RX_Data = (uint16_t*) RX_data;	
	SPI[i].RX_end_data = end_data;

	if(intrpt_en)
	{
		SPI[i].DSPI->RSER.B.EOQF_RE=1;
		SPI[i].DSPI->RSER.B.TCF_RE=1;
		
		SPI[i].State=0x3;
	}
	else
	{
		while((SPI[i].RX_Data[SPI[i].RX_Index-1] != SPI[i].RX_end_data)&&(SPI[i].RX_Index < SPI_MAX_DATA_SIZE))
		{
			while(!SPI[i].DSPI->SR.B.TCF) {}
			SPI[i].DSPI->SR.R |= 0x90000000;
			while(!SPI[i].DSPI->SR.B.RFDF) {}
			SPI[i].RX_Data[SPI[i].RX_Index++] = (uint16_t) SPI[i].DSPI->POPR.R;
		}
		SPI[i].Completed = 1;
	}
	
}

void _spi_drv_show_array(uint8_t i, const uint16_t* TX_data, int8_t size, int8_t intrpt_en)
{
	SPI[i].DSPI->MCR.B.HALT = 0x1;
	_spi_drv_clr_flags(i);
	if (SPI[i].DSPI->MCR.B.MSTR) _spi_drv_set_masterslave(i,0);
	SPI[i].DSPI->MCR.B.HALT = 0x0;

	if (size<=SPI_MAX_DATA_SIZE)
	{
		SPI[i].TX_Data = (uint16_t*) TX_data;
		SPI[i].TX_Data_Size = size;
		if(intrpt_en)
		{
			SPI[i].DSPI->RSER.B.EOQF_RE=1;
			SPI[i].DSPI->RSER.B.TCF_RE=1;
			
			SPI[i].State=0x01;
			while(!SPI[i].DSPI->SR.B.TFFF) {}
			SPI[i].DSPI->PUSHR.R = 0x00010000 | SPI[i].TX_Data[SPI[i].TX_Index];
		}
		else
		{
			for(;SPI[i].TX_Index < SPI[i].TX_Data_Size; SPI[i].TX_Index++)
			{
				while(!SPI[i].DSPI->SR.B.TFFF) {}
				SPI[i].DSPI->PUSHR.R = 0x00010000 | SPI[i].TX_Data[SPI[i].TX_Index];
				while(!SPI[i].DSPI->SR.B.TCF) {}
				SPI[i].DSPI->SR.B.TCF = 1;
			}
			SPI[i].Completed = 1;
		}
	}
	else
	{
		SPI_ERROR();
	}	
}

void _spi_drv_tci(uint8_t i)
{
	SPI[i].DSPI->SR.B.TCF=1;
	if(SPI[i].State==0x1)
	{
		SPI[i].TX_Index++;
		if(SPI[i].TX_Index<SPI[i].TX_Data_Size)
		{
			while(!SPI[i].DSPI->SR.B.TFFF) {}
			SPI[i].DSPI->PUSHR.R = 0x00010000 | SPI[i].TX_Data[SPI[i].TX_Index];
		}
		else
		{
			SPI[i].DSPI->RSER.B.EOQF_RE = 0;
			SPI[i].DSPI->RSER.B.TCF_RE = 0;
			SPI[i].DSPI->MCR.B.CLR_RXF = 1;
			SPI[i].DSPI->MCR.B.CLR_TXF = 1;
			SPI[i].DSPI->SR.R |= 0x9A0A0000;
			SPI[i].Completed = 1;
			SPI[i].State = 0xFF;
		}
	}
	else if(SPI[i].State==0x2)
	{
		while(!SPI[i].DSPI->SR.B.RFDF) {}
		SPI[i].RX_Data[SPI[i].RX_Index++] = (uint16_t)SPI[i].DSPI->POPR.R;
		
		if(SPI[i].RX_Index>=SPI[i].RX_Data_Size)
		{
			SPI[i].DSPI->RSER.B.EOQF_RE = 0;
			SPI[i].DSPI->RSER.B.TCF_RE = 0;
			SPI[i].DSPI->MCR.B.CLR_RXF = 1;
			SPI[i].DSPI->MCR.B.CLR_TXF = 1;
			SPI[i].DSPI->SR.R |= 0x9A0A0000;
			SPI[i].RX_Data_Size = SPI[i].RX_Index;
			SPI[i].Completed = 1;
			SPI[i].State = 0xFF;
		}
		else
		{
			while(!SPI[i].DSPI->SR.B.TFFF) {}
			SPI[i].DSPI->PUSHR.R = 0x00010000;
		}
	}
	else if(SPI[i].State==0x3)
	{
		while(!SPI[i].DSPI->SR.B.RFDF) {}
		SPI[i].RX_Data[SPI[i].RX_Index++] = (uint16_t)SPI[i].DSPI->POPR.R;
		if((SPI[i].RX_Data[SPI[i].RX_Index-1] == SPI[i].RX_end_data)||(SPI[i].RX_Index >= SPI_MAX_DATA_SIZE))
		{
			SPI[i].DSPI->RSER.B.EOQF_RE = 0;
			SPI[i].DSPI->RSER.B.TCF_RE = 0;
			SPI[i].DSPI->MCR.B.CLR_RXF = 1;
			SPI[i].DSPI->MCR.B.CLR_TXF = 1;
			SPI[i].DSPI->SR.R |= 0x9A0A0000;
			SPI[i].RX_Data_Size = SPI[i].RX_Index;
			SPI[i].Completed = 1;
			SPI[i].State = 0xFF;
		}	
	}
	else if(SPI[i].State == 0x4)
	{
		SPI[i].TX_Index++;
		while(!SPI[i].DSPI->SR.B.RFDF) {}
		SPI[i].RX_Data[SPI[i].RX_Index++] = (uint16_t) SPI[i].DSPI->POPR.R;
		if(SPI[i].TX_Index<SPI[i].TX_Data_Size)
		{
			while(!SPI[i].DSPI->SR.B.TFFF) {}
			SPI[i].DSPI->PUSHR.R = 0x00010000 | SPI[i].TX_Data[SPI[i].TX_Index];
		}
		else
		{
			SPI[i].DSPI->RSER.B.EOQF_RE = 0;
			SPI[i].DSPI->RSER.B.TCF_RE = 0;
			SPI[i].DSPI->MCR.B.CLR_RXF = 1;
			SPI[i].DSPI->MCR.B.CLR_TXF = 1;
			SPI[i].DSPI->SR.R |= 0x9A0A0000;
			SPI[i].RX_Data_Size = SPI[i].RX_Index;
			SPI[i].Completed = 1;
			SPI[i].State = 0xFF;
		}
	}
}

//--------------------------------------------------------
//COMMON TO DSPI

void initialise_SPI_DRIVER(void)
{
	uint8_t i = 0;
	SPI[0].DSPI = &DSPI_0;
	SPI[1].DSPI = &DSPI_1;
	SPI[2].DSPI = &DSPI_2;
	
	for(i=0;i<3;i++)
	{
		SPI[i].RX_Data_Size = 0;
		SPI[i].RX_Index = 0;
		SPI[i].TX_Data_Size = 0;
		SPI[i].TX_Index = 0;
		SPI[i].Completed = 0;
		SPI[i].Error=0;
		SPI[i].State=0xFF;
		SPI[i].RX_end_data = 0;
	}
	
	SPI[0].init=_spi_drv_init_dspi0;
	SPI[0].exchange = _spi_drv_exchange_dspi0;
	SPI[0].write = _spi_drv_write_dspi0;
	SPI[0].write_p = _spi_drv_write_p_dspi0;
	SPI[0].read = _spi_drv_read_dspi0;
	SPI[0].read_p = _spi_drv_read_p_dspi0;
	SPI[0].show = _spi_drv_show_dspi0;
	SPI[0].exchange_array = _spi_drv_exchange_array_dspi0;
	SPI[0].write_array = _spi_drv_write_array_dspi0;
	SPI[0].read_array = _spi_drv_read_array_dspi0;
	SPI[0].listen=_spi_drv_listen_dspi0;
	SPI[0].listen_till=_spi_drv_listen_till_dspi0;
	SPI[0].show_array = _spi_drv_show_array_dspi0;
	//SPI[0].EOQI_Handler=_spi_drv_eoqi_dspi0;
	SPI[0].TCI_Handler=_spi_drv_tci_dspi0;
	
	//INTC_InstallINTCInterruptHandler(SPI[0].EOQI_Handler,75,5); 
	INTC_InstallINTCInterruptHandler(SPI[0].TCI_Handler,77,7); 
	
	SPI[1].init=_spi_drv_init_dspi1;
	SPI[1].exchange = _spi_drv_exchange_dspi1;
	SPI[1].write = _spi_drv_write_dspi1;
	SPI[1].read = _spi_drv_read_dspi1;
	SPI[1].show = _spi_drv_show_dspi1;
	SPI[1].exchange_array = _spi_drv_exchange_array_dspi1;
	SPI[1].write_array = _spi_drv_write_array_dspi1;
	SPI[1].read_array = _spi_drv_read_array_dspi1;
	SPI[1].listen=_spi_drv_listen_dspi1;
	SPI[1].listen_till=_spi_drv_listen_till_dspi1;
	SPI[1].show_array = _spi_drv_show_array_dspi1;
	//SPI[1].EOQI_Handler=_spi_drv_eoqi_dspi1;
	SPI[1].TCI_Handler=_spi_drv_tci_dspi1;
	
	//INTC_InstallINTCInterruptHandler(SPI[1].EOQI_Handler,95,5); 
	INTC_InstallINTCInterruptHandler(SPI[1].TCI_Handler,97,7); 	

	SPI[2].init=_spi_drv_init_dspi2;
	SPI[2].exchange = _spi_drv_exchange_dspi2;
	SPI[2].write = _spi_drv_write_dspi2;
	SPI[2].read = _spi_drv_read_dspi2;
	SPI[2].show = _spi_drv_show_dspi2;
	SPI[2].exchange_array = _spi_drv_exchange_array_dspi2;
	SPI[2].write_array = _spi_drv_write_array_dspi2;
	SPI[2].read_array = _spi_drv_read_array_dspi2;
	SPI[2].listen=_spi_drv_listen_dspi2;
	SPI[2].listen_till=_spi_drv_listen_till_dspi2;
	SPI[2].show_array = _spi_drv_show_array_dspi2;
	//SPI[2].EOQI_Handler=_spi_drv_eoqi_dspi2;
	SPI[2].TCI_Handler=_spi_drv_tci_dspi2;
	
	//INTC_InstallINTCInterruptHandler(SPI[2].EOQI_Handler,115,5); 
	INTC_InstallINTCInterruptHandler(SPI[2].TCI_Handler,117,7); 	
}
