/******************************************************************************
* @file    bsp_TimBase.c
* @author  fire
* @version V1.0
* @date    2013-xx-xx
* @brief   TIM2 1ms 定时应用bsp
*******************************************************************************/ 
#include "bsp_TiMbase.h" 


//TIM2中断优先级配置
void TIM2_NVIC_Configuration(void)
{
	NVIC_InitTypeDef	NVIC_InitStructure; 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  

	NVIC_InitStructure.NVIC_IRQChannel 					 = TIM2_IRQn;	  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 2;	
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


/****************************************************************************************
	* TIM_Period / Auto Reload Register(ARR) = 1000   TIM_Prescaler--71 
	* 中断周期为 = 1/(72MHZ /72) * 1000 = 1ms
	*
	* TIMxCLK/CK_PSC --> TIMxCNT --> TIM_Period(ARR) --> 中断 且TIMxCNT重置为0重新计数 
*****************************************************************************************/
void TIM2_Configuration(void)
{
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);			//设置TIM2的时钟为72MHz
	
	TIM_TimeBaseStructure.TIM_Period		= 1000;					//自动重装载寄存器周期的值(计数值)
	TIM_TimeBaseStructure.TIM_Prescaler		= 71;					//时钟预分频数为72
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;			//对外部时钟进行采样的时钟分频,这里没有用到 
	TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;	//向上计数 
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);					//根据指定参数初始化TIM2

	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM2, ENABLE);																		

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, DISABLE);			//先关闭等待使用    
}







