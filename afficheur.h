/*
 * afficheur.h
 *
 *  Created on: May 21, 2026
 *      Author: USER
 */

#ifndef AFFICHEUR_H_
#define AFFICHEUR_H_
#include "TFT_ili9341/stm32g4_ili9341.h"
#include "TFT_ili9341/stm32g4_fonts.h"

extern char Haut[30];
extern char Bas[30];
extern char Gauche [30];
extern char Droite[30];
extern char Luminosité[30];
extern char Ligne1[20];
extern char Ligne2[20];
extern char Ligne3[20];

void affiche_installation(void);
void affiche_on(void);
void affiche_haut(void);
void affiche_bas(void);
void affiche_gauche(void);
void affiche_droite(void);
void affiche_nuit(void);

#endif /* AFFICHEUR_H_ */
