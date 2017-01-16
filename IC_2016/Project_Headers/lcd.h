/*
 * lcd.h
 *
 *  Created on: Nov 12, 2016
 *      Author: Benjamin
 */
#ifndef LCD_H_
#define LCD_H_

#include "MPC5645S.h"

//paramètres taille LCD et images (toutes les tailles sont en pixels)
#define RESO_VERT 272
#define RESO_HOR 30; // 480/16 - il faut un multiple de 30
#define PixelPerWord_Image 8 //8 pixels par mot de 32 bits --> 4 bpp pour toutes les images
#define W_Image_FORD 256
#define H_Image_FORD 256
#define W_Image_car_bird_eye 264
#define H_Image_car_bird_eye 264
#define W_Image_cadenas 48
#define H_Image_cadenas 48
#define W_Image_hijack 48
#define H_Image_hijack 48
#define W_Image_vitre 48
#define H_Image_vitre 48
#define W_Image_pinch 24
#define H_Image_pinch 24
#define W_Image_probleme 48
#define H_Image_probleme 48

//Définition des espaces mémoires des différentes couches graphiques (layer). 
//Attention à bien déterminer l'espace mémoire occupé par une couche pour éviter toute erreur d'affichage. 
//Veiller à ce que le début des adresses des layers soient des multiples de 64! (64 align memory)
//mémoire graphique SRAM : de 0x60000000 à 0x600FFFFF
//Ordre choisi
//- layer1 (Image FORD)
//- layer2 (Image car bird eye)
//- layer3 (Image cadenas_G)
//- layer4 (Image cadenas_D)
//- layer5 (Image hijack)
//- layer6 (Image vitre_G)
//- layer7 (Image vitre_D)
//- layer8 (Image pinch_G)
//- layer9 (Image pinch_D)
//- layer10 (Image probleme_G)
//- layer11 (Image probleme_D)
//- Image FORD
//- Image car bird eye
//- Image cadenas
//- Image hijack
//- Image vitre
//- Image pinch
//- Image probleme
//On met l'image FORD sur Layer1.
//Format 4 bpp --> (256*256p *4 /8-->32768 o)
#define Layer1_W 256  //multiple de 8 car format 4 bpp
#define Layer1_H 256  
#define Layer1_posX 112
#define Layer1_posY 0 
#define Adress1 0x60000000
//On met l'image car bird eye sur Layer2.
//Format 4 bpp --> (264*264p *4 /8--> 34848o)
#define Layer2_W 264  //multiple de 8 car format 4 bpp
#define Layer2_H 264
#define Layer2_posX 108
#define Layer2_posY 4 
#define Adress2 0x60008000 //32768 (256*256*4/8) apres debut layer1
//On met l'image cadenas_G sur Layer3.
//Format 4 bpp --> (48*48p *4 /8-->1152o)
#define Layer3_W 48  //multiple de 8 car format 4 bpp
#define Layer3_H 48  
#define Layer3_posX 280
#define Layer3_posY 20 
#define Adress3 0x60010840 //34848 (264*264*4/8)+ offset 32 apres debut layer2 pour etre 64 aligné
//On met l'image cadenas_D sur Layer4.
//Format 4 bpp --> (48*48p *4 /8-->1152o)
#define Layer4_W 48  //multiple de 8 car format 4 bpp
#define Layer4_H 48  
#define Layer4_posX 280
#define Layer4_posY 200 
// meme adresse layer3 (c'est la même image)
//On met l'image hijack sur Layer5.
//Format 4 bpp --> (48*48p *4 /8-->1152o)
#define Layer5_W 48  //multiple de 8 car format 4 bpp
#define Layer5_H 48 
#define Layer5_posX 215
#define Layer5_posY 110 
#define Adress5 0x60011140 //1152 (48*48*4/8) apres debut layer4
//On met l'image vitre_G sur Layer6.
//Format 4 bpp --> (48*48p *4 /8-->1152o)
#define Layer6_W 48  //multiple de 8 car format 4 bpp
#define Layer6_H 48  
#define Layer6_posX 220
#define Layer6_posY 20 
#define Adress6 0x600115C0 //1152 (48*48*4/8) apres debut layer5
//On met l'image vitre_D sur Layer7.
//Format 4 bpp --> (48*48p *4 /8-->1152o)
#define Layer7_W 48  //multiple de 8 car format 4 bpp
#define Layer7_H 48  
#define Layer7_posX 220
#define Layer7_posY 200 
//meme adresse layer6 (c'est la meme image)
//On met l'image pinch_G sur Layer8.
//Format 4 bpp --> (24*24p *4 /8-->288o)
#define Layer8_W 24  //multiple de 8 car format 4 bpp
#define Layer8_H 24  
#define Layer8_posX 330
#define Layer8_posY 40 
#define Adress8 0x60011B80 //288 (24*24*4/8)+ offset 32 apres debut layer 7
//On met l'image pinch_D sur Layer9.
//Format 4 bpp --> (24*24p *4 /8-->288o)
//attention, le contenu de la mémoire doit démarrer à une adresse multiple de 64 !
#define Layer9_W 24  //multiple de 8 car format 4 bpp
#define Layer9_H 24  
#define Layer9_posX 330
#define Layer9_posY 220 
//meme adresse layer8 (c'est la meme image)
//On met l'image probleme_G sur Layer10.
//Format 4 bpp --> (48*48p *4 /8-->1152o)
#define Layer10_W 48  //multiple de 8 car format 4 bpp
#define Layer10_H 48  
#define Layer10_posX 160
#define Layer10_posY 20 
#define Adress10 0x60012140 //1152 (48*48*4/8) apres debut layer9
//On met l'image probleme_D sur Layer11.
//Format 4 bpp --> (48*48p *4 /8-->1152o)
#define Layer11_W 48  //multiple de 8 car format 4 bpp
#define Layer11_H 48  
#define Layer11_posX 160
#define Layer11_posY 200 
//meme adresse layer10 (c'est la meme image)

//Définition des espaces mémoires des différentes images. 
//Attention à bien déterminer l'espace mémoire occupé par une couche pour éviter toute erreur d'affichage. 
//Veiller à ce que le début des adresses des images soient des multiples de 64! (64 align memory)
//mémoire graphique SRAM : de 0x60000000 à 0x600FFFFF
//adresse de l'image FORD (On stocke donc l'image apres le dernier layer (1152o))
#define Adr_Image_FORD 0x60012A40;
//adresse de l'image car bird eye (On stocke l'image après la memoire necessaire pour l'image precedente (32768o))
#define Adr_Image_car_bird_eye 0x6001AA40;
//adresse de l'image cadenas (On stocke l'image après la memoire necessaire pour l'image precedente (34848o))
#define Adr_Image_cadenas 0x60023280;
//adresse de l'image hijack (On stocke l'image après la memoire necessaire pour l'image precedente (1152o))
#define Adr_Image_hijack 0x60023700;
//adresse de l'image vitre (On stocke l'image après la memoire necessaire pour l'image precedente (1152o))
#define Adr_Image_vitre 0x60023B80;
//adresse de l'image pinch (On stocke l'image après la memoire necessaire pour l'image precedente (1152o))
#define Adr_Image_pinch 0x60024000;
//adresse de l'image probleme (On stocke l'image après la memoire necessaire pour l'image precedente (288o))
#define Adr_Image_probleme 0x60024140;

//Définition de l'espaces mémoire CLUT: address from 0x2000 to 0x3FFF (adresse de base = 0xFFE5C000)
//capacité: 8192 octets --> 2048 mots de 32 bits
//format AARRGGBB
#define Start_CLUT 0xFFE5E000
#define Adress_Start_CLUT *(uint32_t *) Start_CLUT

//functions prototypes
void InitLayerMemory(void);

#endif /* LCD_H_ */
