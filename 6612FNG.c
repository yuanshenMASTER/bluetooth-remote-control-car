#include "stm32f10x.h"   // Device header
#include "sys.h"
#include "delay.h"
#include "6612FNG.h"

void FNG6612_Init(void){
//电机控制端口	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能PB12 13 14 15;
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}	
void PWMPA8_Init(void){
	//PWM控制端口PA8
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	
	GPIO_InitTypeDef GPIO_InitStructure;			
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//PA8->TIM1_CH1
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	TIM_InternalClockConfig(TIM1);						//内部时钟
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStructure.TIM_Period=100-1;			//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler=720-1;		//PSC	频率1kHz
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=0;		//CCR  0~100
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);  
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	
	TIM_Cmd(TIM1,ENABLE);
}	

void PWMPA11_Init(void){
	//PWM控制端口PA11
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	
	GPIO_InitTypeDef GPIO_InitStructure;		
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//PA11->TIM1_CH4
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	TIM_InternalClockConfig(TIM1);						//内部时钟
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStructure.TIM_Period=100-1;			//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler=720-1;		//PSC	频率1kHz
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=0;		//CCR  0~100
	TIM_OC4Init(TIM1,&TIM_OCInitStructure);
	
	TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Enable);  
    TIM_CtrlPWMOutputs(TIM1,ENABLE);
	
	TIM_Cmd(TIM1,ENABLE);
}



//前
void Front(void){
	TIM_SetCompare1(TIM1,30);
	TIM_SetCompare4(TIM1,30);
	               IN1=0;//
				   IN2=1;
			 
				   IN3=0;//
				   IN4=1;
}
//后
void Back(void){
	TIM_SetCompare1(TIM1,30);
	TIM_SetCompare4(TIM1,30);
	IN1=1;
	IN2=0;
	IN3=1;
	IN4=0;
}
//左
void Lelf(void){
	TIM_SetCompare1(TIM1,35);
	TIM_SetCompare4(TIM1,35);
	IN1=1;
	IN2=0;			 
	IN3=0;
	IN4=1;
	
}
//右
void Right(void){
	TIM_SetCompare1(TIM1,40);
	TIM_SetCompare4(TIM1,40);
	IN1=0;
	IN2=1;
	IN3=1;
	IN4=0;
}
//停
void Stop(void){
	TIM_SetCompare1(TIM1,0);
	TIM_SetCompare4(TIM1,0);
	         IN1=0;
				   IN2=0;
				   IN3=0;
				   IN4=0;
	
}
