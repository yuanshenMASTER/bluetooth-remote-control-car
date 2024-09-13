#include "stm32f10x.h"   // Device header
#include "Delay.h"
#include "SR04.h"
#include "OLED.h"

void SR04_Init(void){

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//开GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//开AFIO时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;//脉冲触发端口 Trig=PB0
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//回波接收端口 Echo=PB1
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM3);//使用内部时钟
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 5000;		//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler=7200-1;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//CNT到达ARR中断一次
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

}
float UltrasonicWave_Distance; 

float SR04_Start(void){
	float sum = 0;
//	int i = 0;
	
//	while(i!=5){
		TIM_SetCounter(TIM3,0);//清零计时
		GPIO_SetBits(GPIOB,GPIO_Pin_0);//B0置1大于10us
		Delay_us(20);
		GPIO_ResetBits(GPIOB,GPIO_Pin_0);
		
	while(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1));
		TIM_Cmd(TIM3,ENABLE);  //
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1));
		TIM_Cmd(TIM3, DISABLE);//                                  
		UltrasonicWave_Distance=TIM_GetCounter(TIM3)*340/200.0;
		TIM_SetCounter(TIM3,0);//清零计时
		sum = UltrasonicWave_Distance + sum ;
//		i++;
//	 }

	return sum;
//	 return sum/5.0;
		
}

//void EXTI1_IRQHandler(void){

//	if(EXTI_GetITStatus(EXTI_Line1) != RESET)
//	{	
//		TIM_Cmd(TIM2,ENABLE);//开始计时
//		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1));//A1高电平循环
//		Counter = TIM_GetCounter(TIM2);
//		TIM_Cmd(TIM2,DISABLE);//计时停
//		TIM_SetCounter(TIM2,0);//CNT值清0
//		
//		EXTI_ClearITPendingBit(EXTI_Line1);
//	}
//}


