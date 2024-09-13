#include "stm32f10x.h"                  
#include "SG90.h"

void Servo_Init(void)
{
	SG90_Init();
}

void Servo_SetAngle(float Angle)
{
	PWM_SetCompare2(Angle / 180 * 2000 + 500);
}
