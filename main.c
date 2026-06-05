/**
 *******************************************************************************
 * @file 	main.c
 * @author 	jjo
 * @date 	Mar 29, 2024
 * @brief	Fichier principal de votre projet sur carte Nucléo STM32G431KB
 *******************************************************************************
 */

#include "config.h"
#include "TFT_ili9341/stm32g4_ili9341.h"
#include "TFT_ili9341/stm32g4_fonts.h"
#include "stm32g4_sys.h"
#include "WS2812/stm32g4_ws2812.h"

#include "stm32g4_sys.h"
#include "stm32g4_timer.h"
#include "stm32g4_adc.h"
#include "stm32g4_systick.h"
#include "stm32g4_gpio.h"
#include "stm32g4_uart.h"
#include "stm32g4_utils.h"

#include <stdio.h>

#include "servo.h"
#include "afficheur.h"
#include "photo.h"
#include "ledsws.h"
#include "button.h"


static void state_machine(void);
void process_test_photoresistor(void);
void process_test_afficheur(void);
void process_servo_moteur(void);
void process_test_ws2812(void);
void process_test_bouton(void);
void process_test(void);





int main(void) {
	HAL_Init();
	SystemClock_Config();
	BSP_GPIO_enable();
	ILI9341_Init();
	BSP_WS2812_init();
	BSP_UART_init(UART2_ID,115200);
	BSP_SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);
	memset(leds,0,sizeof(leds));


	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, SET);
	//process_test_bouton();
	//process_test_photoresistor();
	//process_servo_moteur();
	//process_test_ws2812();
	//process_test_afficheur();
	//process_test();
	while (1)
	{
	state_machine();
	}

}

void state_machine(void){
	typedef enum {
	INIT =0,
	INSTAL,
	ON,
	HAUT,
	BAS,
	GAUCHE,
	DROITE,
	OFF
	}state_e;
	static state_e state = INIT;
	static state_e previous_state = INIT;
	bool entry = (state!=previous_state)?true:false;
	static uint32_t entry_time = 0;
	if (entry) {
	       entry_time = HAL_GetTick();
	       previous_state = state;
	    }

	recu_adc();
	calcul_barre();
	BSP_TIMER_run_us(TIMER3_ID, 20000, false);
	BSP_TIMER_run_us(TIMER4_ID, 20000, false);

	BSP_TIMER_enable_PWM(TIMER3_ID, TIM_CHANNEL_1, 75, true, false);
	BSP_TIMER_enable_PWM(TIMER4_ID, TIM_CHANNEL_1, 75, true, false);

	button_event_t btn = BUTTON_state_machine();
	switch(state){
		case INIT:
			ILI9341_demo();
			BSP_ADC_init();
			BUTTON_init(GPIOA, GPIO_PIN_9);
			state=INSTAL;
			break;

		case INSTAL:
			if (entry){
				affiche_installation();
				leds_install();
			}
			if (HAL_GetTick() - entry_time >= 5000) state = ON;

			break;

		case ON:
			if (entry){
				ILI9341_Fill(ILI9341_COLOR_BLACK);
				ILI9341_Puts(200, 10, "ON", &Font_16x26, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
			}
			affiche_on();
			leds_on();
			servo_install();
			if (HAL_GetTick() - entry_time >= 10000) {
				if(nuit()==true) state = OFF;
				else if (max(haut, bas, gauche, droite) == haut) state = HAUT;
				else if(max(haut, bas, gauche, droite) == bas) state = BAS;
				else if(max(haut, bas, gauche, droite) == droite) state = DROITE;
				else state=GAUCHE;
			 }
			if (btn == BUTTON_EVENT_LONG_PRESS) state=OFF;
		break;

		case HAUT:
			if (entry){
				ILI9341_Fill(ILI9341_COLOR_BLACK);
			}
			affiche_haut();
			leds_axe_x();
			servo_haut();
			if (HAL_GetTick() - entry_time >= 15000) {
				calcul_max();
				if (valeur_max != haut) state=ON;
			}
			if (btn == BUTTON_EVENT_SHORT_PRESS) state=ON;
			break;

		case BAS:
			if (entry){
				ILI9341_Fill(ILI9341_COLOR_BLACK);
			}
			affiche_bas();
			leds_axe_x();
			servo_bas();
			if (HAL_GetTick() - entry_time >= 15000) {
				calcul_max();
				if (valeur_max != bas) state=ON;;
				}
			if (btn == BUTTON_EVENT_SHORT_PRESS) state=ON;
			break;

		case GAUCHE:
			if (entry){
				ILI9341_Fill(ILI9341_COLOR_BLACK);
			}
			affiche_droite();
			leds_axe_y();
			servo_gauche();

			if (HAL_GetTick() - entry_time >= 15000) {
				calcul_max();
				if (valeur_max != gauche) state=ON;
				}
			if (btn == BUTTON_EVENT_SHORT_PRESS) state=ON;
			break;

		case DROITE:
			if (entry){
				ILI9341_Fill(ILI9341_COLOR_BLACK);
			}
			affiche_droite();
			servo_droite();
			leds_axe_y();
			if (HAL_GetTick() - entry_time >= 15000) {
				calcul_max();
				if (valeur_max != droite) state=ON;
				}
			if (btn == BUTTON_EVENT_SHORT_PRESS) state=ON;
			break;
		case OFF:
			if (entry){
				ILI9341_Fill(ILI9341_COLOR_BLUE);
			}
			affiche_nuit();
			leds_off();
			if (btn == BUTTON_EVENT_LONG_PRESS) state=ON;
			break;
		default:
			break;

	}

	}







process_test(void){
	BSP_TIMER_run_us(TIMER3_ID, 20000, false);
	BSP_TIMER_run_us(TIMER4_ID, 20000, false);

	BSP_TIMER_enable_PWM(TIMER3_ID, TIM_CHANNEL_1, 75, true, false);
	BSP_TIMER_enable_PWM(TIMER4_ID, TIM_CHANNEL_1, 75, true, false);
	while(1){
		//HAUT
		BSP_TIMER_set_duty(TIMER3_ID, TIM_CHANNEL_1, 75);
		BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 75);

		BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 50);
		//BAS
		BSP_TIMER_set_duty(TIMER3_ID, TIM_CHANNEL_1, 75);
		BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 75);

		BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 100);
		//GAUCHE
		BSP_TIMER_set_duty(TIMER3_ID, TIM_CHANNEL_1, 75);
		BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 75);

		BSP_TIMER_set_duty(TIMER3_ID, TIM_CHANNEL_1, 25);
		BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 100);
		//DROITE
		BSP_TIMER_set_duty(TIMER3_ID, TIM_CHANNEL_1, 75);
		BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 75);

		BSP_TIMER_set_duty(TIMER3_ID, TIM_CHANNEL_1, 125);
		BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 100);

	}
}


void process_test_ws2812(void){
		BSP_WS2812_init();
	    uint32_t leds[64];
	    memset(leds,0,sizeof(leds));
	    while(1){
	    	leds[0] =WS2812_COLOR_RED;
	    	leds[1] =WS2812_COLOR_BLUE;
	    	BSP_WS2812_display(leds,2);
	    	HAL_Delay(500);


	    	leds[0] =WS2812_COLOR_GREEN;
	    	leds[1] =WS2812_COLOR_GREEN;
	    	BSP_WS2812_display(leds,2);
	    	HAL_Delay(500);
	    }
}


void process_test_photoresistor(void){
	int16_t value1, value2, value3, value4;
	BSP_ADC_init();
	while(1)
	{
		value1 = BSP_ADC_getValue(ADC_1);
		value2 = BSP_ADC_getValue(ADC_2);
		value3 = BSP_ADC_getValue(ADC_17);
		value4 = BSP_ADC_getValue(ADC_4);
		printf("Raw ADC value: %d\n",value1);
		printf("Raw ADC value: %d\n",value2);
		printf("Raw ADC value: %d\n",value3);
		printf("Raw ADC value: %d\n",value4);
		printf("___________________%d\n");
		HAL_Delay(5000);
	}

}


void process_test_afficheur(void){
	ILI9341_Init();
	ILI9341_Rotate(ILI9341_Orientation_Landscape_2);
	ILI9341_Fill(ILI9341_COLOR_BLACK);
	ILI9341_Puts(10, 10, "TEST SYSTEME", &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
	ILI9341_Puts(10, 40, "Jean Claude Badlane", &Font_7x10, ILI9341_COLOR_YELLOW, ILI9341_COLOR_BLACK);
	while (1) {

	}

}


void process_servo_moteur(void){
	HAL_Init();
	SystemClock_Config();
	BSP_TIMER_run_us(TIMER3_ID, 20000, false);
	BSP_TIMER_run_us(TIMER4_ID, 20000, false);

	BSP_TIMER_enable_PWM(TIMER3_ID, TIM_CHANNEL_1, 75, true, false);
	BSP_TIMER_enable_PWM(TIMER4_ID, TIM_CHANNEL_1, 75, true, false);
		while(1){


		BSP_TIMER_set_duty(TIMER3_ID, TIM_CHANNEL_1, 30);
		BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 50);

		HAL_Delay(1000);
		BSP_TIMER_set_duty(TIMER3_ID, TIM_CHANNEL_1, 75);
		BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 75);

		HAL_Delay(1000);

		BSP_TIMER_set_duty(TIMER3_ID, TIM_CHANNEL_1, 120);
		BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 100);
		HAL_Delay(1000);

		BSP_TIMER_set_duty(TIMER3_ID, TIM_CHANNEL_1, 50); // 0° (1ms)
		BSP_TIMER_set_duty(TIMER4_ID, TIM_CHANNEL_1, 50);
		HAL_Delay(1000);
		}
	}

void process_test_bouton(void){
	while(1){
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)== 0){
			printf("Bouton appuyé !!!\n");
			HAL_Delay(500);
		}
		else{
			printf("Non actif\n");
			HAL_Delay(500);

			}
		}
	}


