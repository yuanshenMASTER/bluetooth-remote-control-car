#ifndef __SG90_h
#define __SG90_h
#include "stm32f10x.h"

void SG90_Init(void); 
//void Leme_lelf(void);
//void Leme_right(void);
//void Leme_mid(void);
//void Servo_SetAngle(float Angle);
void PWM_SetCompare2(uint16_t Compare);
	
#endif
