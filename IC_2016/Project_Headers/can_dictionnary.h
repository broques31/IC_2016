/*
 * define.h
 *
 *  Created on: Janv, 16, 2017
 *      Author: Commun 
 */

#ifndef CAN_DICTIONNARY_H_
#define CAN_DICTIONNARY_H_

#include "MPC5645S.h"

/*
 * CAN ID : adresses des modules
 */
#define ID_BCM 111
#define ID_DCM 222
#define ID_IC 333

/*
 * Structure des trames CAN :
 * ID : destinataire
 * Data (1 octet) :
 * 		- premier bits :
 * 							0 -> Donnée binaire (pluie, porte verouillée, etc.)
 * 							1 -> Donnée numérique (vitesse uniquement)
 * 		- 7 derniers bits : information
 */
#define LENGTH_FRAME 1

// Codes des infos à transmettre par le CAN
// Attention ! : la fonction TransmitMsg(...) prend en paramètre un pointeur sur la donnée à transmettre,
// il faut donc définir une variable ayant la valeur définie par le #define (voir BCM_appli.c).

// Statut portes : de DCM vers IC
#define porte_G_verrouillee  		1
#define porte_G_deverouille 		2
#define probleme_porte_G 			3
#define pas_probleme_porte_G 		4

#define porte_D_verrouillee 		5
#define porte_D_deverouille 		6
#define probleme_porte_D 			7
#define pas_probleme_porte_D 		8

// De BCM vers IC
#define antihijacking_active 		9
#define antihijacking_desactive 	10

// Statut fenêtres : de DCM vers IC
#define vitres_en_fermeture 		11

#define vitre_G_fermee 				12
#define vitre_G_ouverte 			13
#define probleme_vitre_G 			14
#define pas_probleme_vitre_G 		15
#define pincement_vitre_G 			16
#define pas_pincement_vitre_G 		17

#define vitre_D_fermee 				18
#define vitre_D_ouverte 			19
#define probleme_vitre_D 			20
#define pas_probleme_vitre_D 		21
#define pincement_vitre_D 			22
#define pas_pincement_vitre_D 		23

// De DCM vers IC
#define probleme_batterie 			24
#define pas_probleme_batterie 		25


#endif /* DEFINE_H_ */
