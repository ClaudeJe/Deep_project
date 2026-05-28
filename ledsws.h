/*
 * ledsws.h
 *
 *  Created on: May 21, 2026
 *      Author: USER
 */

#ifndef LEDSWS_H_
#define LEDSWS_H_

#include "WS2812/stm32g4_ws2812.h"
extern uint32_t leds[64];

void leds_on(void);
void leds_off(void);
void leds_install(void);
void leds_axe_x(void);
void leds_axe_y(void);

#endif /* LEDSWS_H_ */
