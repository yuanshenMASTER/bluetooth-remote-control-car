#ifndef __SR04_H
#define __SR04_H

extern float UltrasonicWave_Distance;

#define TRIG_PORT      GPIOB  
#define ECHO_PORT      GPIOB  
#define TRIG_PIN       GPIO_Pin_0   
#define ECHO_PIN       GPIO_Pin_1

void SR04_Init(void);
float SR04_Start(void);

#endif
