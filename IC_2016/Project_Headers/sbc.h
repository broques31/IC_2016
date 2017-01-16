/*
 * SBC.h
 *
 *  Created on: Jan 18, 2015
 *      Author: Antoine
 */

#ifndef SBC_H_
#define SBC_H_
#define IC

#include "MPC5645S.h"

/*
 * Initialisation du CAN 1
 * Buffer 0 pour émission, buffer 1 pour réception
 * Interruption configurée sur réception
 */
void initCAN1 (void);

/*
 * Fonction d'interruption activée à chaque réception de message, à écrire dans le main.
 */
void Interrupt_Rx_CAN1 ();

/*
 * Extraction des données d'un message. A utiliser dans Interrupt_Rx_CAN1().
 * Renvoie la donnée transmise. Voir define.h pour la structure des trames.
 */
uint8_t ReceiveMsg(void);

// Pour SPI
uint8_t get_flag_frame_received(void);
void reset_flag_frame_received(void);
uint16_t Read_voltage_value(void);
void Init_SBC_DBG(void);

#endif /* SBC_H_ */
