#ifndef __6612FNG_H
#define __6612FNG_H

#include "sys.h"

#define IN1 PBout(13)
#define IN2 PBout(12)
#define IN3 PBout(14)
#define IN4 PBout(15)

void FNG6612_Init(void);
void PWMPA8_Init(void);
void PWMPA11_Init(void);

void Front(void);
void Back(void);
void Lelf(void);
void Right(void);
void Stop(void);

#endif
