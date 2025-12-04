#ifndef _LOAD_H_
#define _LOAD_H_
/*****************************************************************************
* filename
* lcd.h
*
*
*
*
* (c) 2007 Jiwen Su
*****************************************************************************/
///---------------------------------------------------------------------------
//the head file define
#include "includes.h" /*头文件的包含*/
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//JC_IN定义区域
#define JC_IN_PIN  GPIO_Pin_2 //PB2
#define JC_IN_PIN_PORTBS JC_IN_PIN
#define JC_IN_CONTROLL_PORTB GPIOB

#define JC_IN_INPUT()        ((JC_IN_CONTROLL_PORTB->IDR & JC_IN_PIN)>>2) 

//-----------------------------------------------------------------------

//---------------------------------------------------------------------------
//LED定义区域
#define LED_ALARML_PIN  GPIO_Pin_1 //PA1
#define LED_ALARMH_PIN  GPIO_Pin_0 //PA0
#define LED_PIN_PORTAS LED_ALARML_PIN |LED_ALARMH_PIN
#define LED_CONTROLL_PORTA GPIOA

#define LED_ERROR_PIN  GPIO_Pin_4 //PC4
#define LED_WORK_PIN GPIO_Pin_5 //PC5
#define LED_PIN_PORTCS LED_ERROR_PIN | LED_WORK_PIN
#define LED_CONTROLL_PORTC GPIOC

#define LED_WORK_OFF()             GPIO_SetBits(LED_CONTROLL_PORTC, LED_WORK_PIN)
#define LED_WORK_ON()           GPIO_ResetBits(LED_CONTROLL_PORTC, LED_WORK_PIN)

#define LED_ERROR_OFF()             GPIO_SetBits(LED_CONTROLL_PORTC, LED_ERROR_PIN)
#define LED_ERROR_ON()           GPIO_ResetBits(LED_CONTROLL_PORTC, LED_ERROR_PIN)

#define LED_ALARML_ON()             GPIO_SetBits(LED_CONTROLL_PORTA, LED_ALARML_PIN)
#define LED_ALARML_OFF()           GPIO_ResetBits(LED_CONTROLL_PORTA, LED_ALARML_PIN)

#define LED_ALARMH_ON()             GPIO_SetBits(LED_CONTROLL_PORTA, LED_ALARMH_PIN)
#define LED_ALARMH_OFF()           GPIO_ResetBits(LED_CONTROLL_PORTA, LED_ALARMH_PIN)
//-----------------------------------------------------------------------

//---------------------------------------------------------------------------
//MODBUS定义区域
#define MODBUS_DIO_PORT GPIOA
#define MODBUS_DIO_PIN GPIO_Pin_8

#define MODBUS_WRITE_DATA()             (GPIO_SetBits(MODBUS_DIO_PORT, MODBUS_DIO_PIN)) // 高电平写数据
#define MODBUS_READ_DATA()            (GPIO_ResetBits(MODBUS_DIO_PORT, MODBUS_DIO_PIN))// 低电平读数据
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//KEY定义区域
#define GPIO_KEY_TIMEOUT 20
#define KEY_1 1
#define KEY_2 2
#define KEY_3 3
#define KEY_4 4
#define KEY_SETTING  0xf0
#define KEY_ERROR 0xfe

#define GPIO_KEY_1_PIN GPIO_Pin_6
#define GPIO_KEY_3_PIN GPIO_Pin_7
#define GPIO_KEY_INPUT_PORTA_PIN GPIO_KEY_1_PIN | GPIO_KEY_3_PIN
#define GPIO_KEY_INPUT_PORTA  GPIOA

#define GPIO_KEY_INPUT1() ((GPIO_KEY_INPUT_PORTA->IDR & GPIO_KEY_1_PIN)>>6) 
#define GPIO_KEY_INPUT3() ((GPIO_KEY_INPUT_PORTA->IDR & GPIO_KEY_3_PIN)>>6) 

//---------------------------------------------------------------------------
//LCD定义区域
#define		GPIO_CS       	 GPIO_Pin_2

#define LCD_CONTROLL_PINAS GPIO_CS
#define LCD_CONTROLL_PORTA GPIOA

#define		GPIO_DATA          GPIO_Pin_1
#define		GPIO_WR       	 GPIO_Pin_0
#define LCD_CONTROLL_PINBS GPIO_DATA | GPIO_WR
#define LCD_CONTROLL_PORTB GPIOB


#define DELAY_TIME	25

#define		SET_WR()         GPIOB->BSRR |= GPIO_WR;Delay(DELAY_TIME)
#define		CLR_WR()         GPIOB->BRR |= GPIO_WR;Delay(DELAY_TIME)
#define		SET_CS()         GPIOA->BSRR |= GPIO_CS;Delay(DELAY_TIME)
#define		CLR_CS()         GPIOA->BRR |= GPIO_CS;Delay(DELAY_TIME)
#define		SET_DATA()       GPIOB->BSRR |= GPIO_DATA;Delay(DELAY_TIME)
#define		CLR_DATA()       GPIOB->BRR |= GPIO_DATA;Delay(DELAY_TIME)
//-----------------------------------------------------------------------
//DAC定义区域
//-----------------------------------------------------------------------

//---------------------------------------------------------------------------
//ADC定义区域
#define NAP55A_IN GPIO_Pin_0
#define ADC_PORTC_PIN NAP55A_IN |GPIO_Pin_1|GPIO_Pin_2

#define NAP55A_REF_IN GPIO_Pin_3
#define ADC_PORTA_PIN NAP55A_REF_IN

#define ADC_USED_CHANNEL  4
#define ADC_SAMPLE_NUM 512
#define ADC_VALUE_LENGTH ADC_USED_CHANNEL*ADC_SAMPLE_NUM*2

#define ADC1_DR_ADDRESS  ((uint32_t)0x4001244C)

//---------------------------------------------------------------------------
//继电器定义区域
#define JIDIANQI_ALARML_PIN  GPIO_Pin_14 //PC14
#define JIDIANQI_ALARMH_PIN  GPIO_Pin_13 //PC13
#define JIDIANQI_PIN_PORTCS JIDIANQI_ALARML_PIN |JIDIANQI_ALARMH_PIN
#define JIDIANQI_CONTROLL_PORTC GPIOC

#define JIDIANQI_ALARML_ON()             GPIO_SetBits(JIDIANQI_CONTROLL_PORTC, JIDIANQI_ALARML_PIN)
#define JIDIANQI_ALARML_OFF()           GPIO_ResetBits(JIDIANQI_CONTROLL_PORTC, JIDIANQI_ALARML_PIN)

#define JIDIANQI_ALARMH_ON()             GPIO_SetBits(JIDIANQI_CONTROLL_PORTC, JIDIANQI_ALARMH_PIN)
#define JIDIANQI_ALARMH_OFF()           GPIO_ResetBits(JIDIANQI_CONTROLL_PORTC, JIDIANQI_ALARMH_PIN)
//-----------------------------------------------------------------------

//----------------------------------------------------------------------
//FLASH定义区域
//#define FLASH_SENSOR_PARAMETRER  0x0807f800                //往前提了一页，这个不够用，后面低报警高报警修改后，重启恢复默认值
#define FLASH_SENSOR_PARAMETRER  0x0803F800                
//++++++++++++++++++++++++++++++++++++++++++CHANGE+++++++++++++++++++++++++++++++++++++++++
//#define FLASH_GAS_PARAMETER_POINT 5
#define FLASH_GAS_PARAMETER_POINT 7
//+++++++++++++++++++++++++++++++++++++++++CHANGE_END+++++++++++++++++++++++++++++++++++++++++
//----------------------------------------------------------------------

//----------------------------------------------------------------------
//define the function
u8 KEY_CHECK(void);
void ModbusTimersDisable( void );
void ModbusTimersEnable( void );
void LCD_wr_dat(u8 add1, u8 add2,u8 dat2);
void LCD_wr_BIT4(u8 add1,u8 dat1);
void LCD_DRIVER_Init(void);
void DIANLIU_420MA_SET(u16 vol);
void SENSOR_SET_JIZHUN(u16 vol);

void FLASH_READ_PARAMETER(void);
void FLASH_WRITE_PARAMETER(void);
void Load_Init(void);
//-----------------------------------------------------------------------
#endif
/********************************************************************
					lcd.h的程序到此结束。
*********************************************************************/
