#include "stm32f10x.h"   // Device header
#include "Delay.h"
#include "SR04.h"
#include "HC05.h"
#include "OLED.h"
#include "6612FNG.h"
#include "Servo.h"

//uint16_t Counter;
float lengthRight,lengthLeft,length,Angle;;
int count;
int main(void){
	
	OLED_Init();
	HC05_Init();
	FNG6612_Init();
	PWMPA8_Init();
	PWMPA11_Init();
	SR04_Init();
	Servo_Init();
	Servo_SetAngle(95); //中间
	Delay_ms(500);
	while(1){
		if(RXDATE=='f')	{		//避障模式
			length=SR04_Start();
			
			 if(length>=30)//无障碍
			{
				Front();
		    }
			 else if(length<30)//有障碍
			{
				Stop();  //停
				Servo_SetAngle(150);//舵机左 
				Delay_ms(500);
				lengthLeft=SR04_Start();
				Servo_SetAngle(95);//舵机中
				Delay_ms(500);
				Servo_SetAngle(50);//舵机右
				Delay_ms(500);
				lengthRight=SR04_Start();
				Servo_SetAngle(95);//舵机中
				Delay_ms(500);
				
				 if((lengthRight 
					 < 30)&&(lengthLeft <30))//左右都障碍
				 {
					 
					 Back();//退
					 Delay_ms(500);
					 
					 Servo_SetAngle(95);//舵机中
					 Delay_ms(500);
				 }
				 else if((lengthRight > 30)&&(lengthLeft < 30))//右边无障碍
					 {
					 Right();//右
					 
					 Servo_SetAngle(95);//舵机中
					 Delay_ms(500);
				 }
				 else if((lengthRight <30)&&(lengthLeft > 30))//左边无障碍
					 {
					 Lelf();//左
					 
					 Servo_SetAngle(95);//舵机中
					 Delay_ms(500);
				 }
				 else if ((lengthRight > 30)&&(lengthLeft >30))//左右都无障碍
					 {
					 
					if(lengthRight > lengthLeft)//右边宽
					{
						Right();//右
					 
						Servo_SetAngle(95);//舵机中
						Delay_ms(500);
					}
					 else{ //左边宽
						Lelf();//左
					 
						Servo_SetAngle(95);//舵机中
						Delay_ms(500);
					 }
				 }
			 }
				Delay_ms(50);
			
		 }
		//前
		if( RXDATE=='a'){           
			Front();
		}
		//停		 
		if( RXDATE=='b'){           
			Stop();
		}
		//后
		if( RXDATE=='c'){           
			Back();
		}
		//左
		if( RXDATE=='d'){          
			Right();
		}
		//右	
		if( RXDATE=='e'){         
			Lelf();
		}
		//舵机测试
		if( RXDATE=='g'){         
			Servo_SetAngle(50);//右
			Delay_ms(1000);
			Servo_SetAngle(95);//中
			Delay_ms(1000);
			Servo_SetAngle(140);//左
			Delay_ms(1000);
		}
		//测距测试
		if( RXDATE=='h'){         
			length=SR04_Start();
			 if(length>=30)//无障碍
			{
				USART_SendData(USART1,'1');
		    }
			 else if(length<30)//有障碍
			{
				USART_SendData(USART1,'2');
			}
			Delay_ms(1000);
		}
					
	}

}

//void EXTI1_IRQHandler(void){

//	if(EXTI_GetITStatus(EXTI_Line1) == SET)
//	{	
//		TIM_Cmd(TIM2,ENABLE);//开始计时
//		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1));//A1高电平循环
//		Counter = TIM_GetCounter(TIM2)*340/200;
//		TIM_Cmd(TIM2,DISABLE);//计时停
//		TIM_SetCounter(TIM2,0);//CNT值清0
//		OLED_ShowNum(1,1,Counter,3);
//		
//		EXTI_ClearITPendingBit(EXTI_Line1);
//	}
//}
