/*
 * photo.c
 *
 *  Created on: Mars 21, 2026
 *      Author: USER
 */
#include "photo.h"
#include <stdbool.h>
int16_t l1, l2, l3, l4, haut, bas, gauche, droite;
uint16_t barre_haut, barre_bas, barre_gauche, barre_droite;
int16_t valeur_max;

void recu_adc(){
	l1 = BSP_ADC_getValue(ADC_1);
	l2 =  BSP_ADC_getValue(ADC_2);
	l3 =  BSP_ADC_getValue(ADC_17);
	l4	=  BSP_ADC_getValue(ADC_4);

	haut=(l1+l2)/2;
	bas=(l3+l4)/2;
	gauche=(l1+l3)/2;
	droite=(l2+l4)/2;
}
int16_t max(int16_t a, int16_t b, int16_t c, int16_t d) {
	    int16_t m = a;
	    if (b > m) m = b;
	    if (c > m) m = c;
	    if (d > m) m = d;
	    return m;
}
void calcul_barre(){
barre_haut   = (haut   * 100) / 4095;
barre_bas    = (bas    * 100) / 4095;
barre_gauche = (gauche * 100) / 4095;
barre_droite = (droite * 100) / 4095;

}
void calcul_max(){
	valeur_max=max(haut, bas, gauche, droite);
}
bool nuit(){
	if (haut<300 && bas<300 && gauche<300 && droite<300){
		return true;
	}
	return false;
}
