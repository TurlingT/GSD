/*
********************************************************************************
*                                  uC/OS-III
*							
*                              ARM Cortex-M3 Port
*
* File      	: Config.C
* Version   	: V1.0
* By        	: 王宏强
*
* For       	: Stm32f10x
* Mode      	: Thumb2
* Toolchain 	: 
*             		RealView Microcontroller Development Kit (MDK)
*             		Keil uVision
* Description   : STM32F10x 内部 系统的配置
*
*					1，系统中断优先级模式设置
*					2，系统程序启动指定
*					3，系统时钟计时器配置
*					4，芯片引脚初始化
*					
* Date          : 2012.05.22
*******************************************************************************/

#include "includes.h" 

/*******************************************************************************
* Function Name :void SystemConfig(void)
* Description   :系统初始化
* Input         :
* Output        :
* Other         :
* Date          :2011.10.27  13:14:59
*******************************************************************************/
void BSP_Init(void)
{
/* System Clocks Configuration */
  	RCC_Configuration(); 
	Load_Init();
	NVIC_Configuration();	
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 * Function Name  : RCC_Configuration
 * Description    : Configures the different system clocks.
 * Input          : None
 * Output         : None
 * Return         : None
 */

void RCC_Configuration(void)
{
	ErrorStatus HSEStartUpStatus;     
	/* RCC system reset(for debug purpose) */
	RCC_DeInit();
	/* Enable HSE */
	RCC_HSEConfig(RCC_HSE_ON);
	/* Wait till HSE is ready */
	HSEStartUpStatus = RCC_WaitForHSEStartUp();
	if(HSEStartUpStatus == SUCCESS){
		/* Enable Prefetch Buffer */
    	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		/* Flash 2 wait state */
		FLASH_SetLatency(FLASH_Latency_2); 
		/* HCLK = SYSCLK */
	    RCC_HCLKConfig(RCC_SYSCLK_Div1); 	  
	    /* PCLK2 = HCLK/16 = 4.5Mhz*/
	    RCC_PCLK2Config(RCC_HCLK_Div1); 	
	    /* PCLK1 = HCLK=18Mhz ,由于分频系数不为1 ，所以TIMER时钟为36Mhz*/
	    RCC_PCLK1Config(RCC_HCLK_Div4);	
	    /* PLLCLK = 8MHz * 2 = 18 MHz */
	    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);	
	   /* USBCLK = PLLCLK */
	 //  RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);
	    /* Enable PLL */ 
	    RCC_PLLCmd(ENABLE);	
	    /* Wait till PLL is ready */
	    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET){
	    	;
		}	
	    /* Select PLL as system clock source */
	    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);	
	    /* Wait till PLL is used as system clock source */
	    while(RCC_GetSYSCLKSource() != 0x08){
	    	;
		}
	}
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);
  	/* Enable clock */
}

/*******************************************************************************
* Function Name :void InterruptOrder(void)
* Description   :中断向量，优先级
* Input         :
* Output        :
* Other         :
* Date          :2011.10.27  11:50:05
*******************************************************************************/
void NVIC_Configuration(void)
{
#if defined (VECT_TAB_RAM)
	/* Set the Vector Table base location at 0x20000000 */ 
	NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#elif defined(VECT_TAB_FLASH_IAP)
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x2000);
#else  /* VECT_TAB_FLASH  */
	/* Set the Vector Table base location at 0x08000000 */ 
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif 

	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_3);//优先级设置  全为抢占式优先级
}

/*******************************************************************************/





