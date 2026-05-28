/*
 * ledsws.c
 *
 *  Created on: May 12, 2026
 *      Author: USER
 */
#include "ledsws.h"

uint32_t leds[64];

void leds_on(){
	leds[0]=0;
	leds[1]=0;
	BSP_WS2812_display(leds,2);
	leds[0] =WS2812_COLOR_LIGHT_WHITE;
	BSP_WS2812_display(leds,1);
}
void leds_off(){
	leds[0]=0;
	leds[1]=0;
	BSP_WS2812_display(leds,2);
}
void leds_install(){
	leds[0]=0;
	leds[1]=0;
	BSP_WS2812_display(leds,2);
	leds[0] =WS2812_COLOR_LIGHT_RED;
	leds[1] =WS2812_COLOR_LIGHT_RED;
	BSP_WS2812_display(leds,2);
}
void leds_axe_x(){
	leds[0]=0;
	leds[1]=0;
	BSP_WS2812_display(leds,2);
	leds[0] =WS2812_COLOR_LIGHT_WHITE;
	leds[1] =WS2812_COLOR_LIGHT_GREEN;
	BSP_WS2812_display(leds,2);
}
void leds_axe_y(){
	leds[0]=0;
	leds[1]=0;
	BSP_WS2812_display(leds,2);
	leds[0] =WS2812_COLOR_LIGHT_WHITE;
	leds[1] =WS2812_COLOR_LIGHT_BLUE;
	BSP_WS2812_display(leds,2);
}
