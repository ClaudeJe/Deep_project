/*
 * servo.c
 *
 *  Created on: Avril 04, 2026
 *      Author: USER
 */
#include "servo.h"

void servo_install(){
	BSP_TIMER_set_duty(TIMER3_ID, TIM_CHANNEL_1, 75);
	BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 75);
}

void servo_haut(){
	BSP_TIMER_set_duty(TIMER3_ID, TIM_CHANNEL_1, 75);
	BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 75);


	BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 50);
}

void servo_bas(){
	BSP_TIMER_set_duty(TIMER3_ID, TIM_CHANNEL_1, 75);
	BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 75);


	BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 100);
}
void servo_gauche(){
	BSP_TIMER_set_duty(TIMER3_ID, TIM_CHANNEL_1, 75);
	BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 75);

	BSP_TIMER_set_duty(TIMER3_ID, TIM_CHANNEL_1, 25);
	BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 100);

}

void servo_droite(){
	BSP_TIMER_set_duty(TIMER3_ID, TIM_CHANNEL_1, 75);
	BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 75);

	BSP_TIMER_set_duty(TIMER3_ID, TIM_CHANNEL_1, 125);
	BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 100);
}

