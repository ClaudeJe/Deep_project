/*
 * servo.h
 *
 *  Created on: May 21, 2026
 *      Author: USER
 */

#ifndef SERVO_H_
#define SERVO_H_
#include "stm32g4_timer.h"

void servo_haut(void);
void servo_bas(void);
void servo_gauche(void);
void servo_droite(void);
void servo_install(void);

#endif /* SERVO_H_ */
