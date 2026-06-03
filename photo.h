/*
 * photo.h
 *
 *  Created on: May 21, 2026
 *      Author: USER
 */

#ifndef PHOTO_H_
#define PHOTO_H_
#include "stm32g4_adc.h"
#include <stdio.h>

extern int16_t haut, bas, gauche, droite, valeur_max;
extern uint16_t barre_haut, barre_bas, barre_gauche, barre_droite;

void recu_adc(void);
void calcul_barre(void);
void calcul_max(void);
bool nuit(void);
int16_t max(int16_t a, int16_t b, int16_t c, int16_t d);

#endif /* PHOTO_H_ */
