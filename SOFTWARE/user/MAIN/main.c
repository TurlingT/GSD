/*****************************************************************************
* filename
* main.c
*
*
* 描述
* 这个文件实现主程序相关功能函数.
*
*
* (c) 2007 Jiwen Su
*****************************************************************************/
#include "includes.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void SHOW_PANDUAN(void){
	if(JC_IN_INPUT() == 1){
		LCD_SHOW_YON = TRUE;
	}
	else{
		LCD_SHOW_YON = FALSE;
	}
	if(upxianshimoshi == FALSE)
	{
		if(LCD_SHOW_YON == TRUE)
		{
			shifouchushihualcd =TRUE;
		}
	}
	if(shifouchushihualcd)
		{
			LED_ERROR_OFF();
			LED_WORK_ON();
			Delay_ms(3000);
			LCD_DRIVER_Init();
			shifouchushihualcd =FALSE;
		}
	upxianshimoshi =LCD_SHOW_YON;
}
//-----------------------------------------------------------

//------------------------------------------------------------------
void device_load(void){
 	u8 i;
 	bool temp =TRUE;
	for(i=6;i>0;i--)
	{
	 	LCD_chushihua(i);
//++++++++++++++++++++++++++++++++++++++++++CHANGE+++++++++++++++++++++++++++++++++++++++++
        Delay_ms(2200);               //Delay_ms(1000);
      
	}
    sensor_chushihuachuanganqi();
//+++++++++++++++++++++++++++++++++++++++++CHANGE_END+++++++++++++++++++++++++++++++++++++++++   
 	if((JCXI_dibaojing!=255)&&(JCXI_gaobaojing!=255)&&(JCXI_qitileixing!=255)&&(JCXI_qitidanwei!=255)&&(JCXI_zuidaliangcheng!=255)&&(JCXI_zuixiaoliangcheng!=255)){
		temp =FALSE;
	}
	while(temp)
	{
		LCD_LOADERR();
		LED_ERROR_ON();
		LED_WORK_OFF();
		DIANLIU_420MA_SET(JCXI_420ma4/2);
		Delay_ms(1000);
	}
}
//------------------------------------------------------------------

#include <stdlib.h>                     //atof

#define UART_RX_BUF_MAX_LEN 100 // 接收缓冲区的最大长度
uint8_t uart4_recv_buf[UART_RX_BUF_MAX_LEN]={0};

uint8_t data[UART_RX_BUF_MAX_LEN]={0};
uint8_t recv_cnt = 0;  // 接收计数
int result = 0;

char num_str[7];


// 数据解析函数：将接收缓冲区转换为浮点数
float parse_uart4_data(void) {
      // 存储 "0.0680"（6 个字符 + 结束符）
    
    // 提取个位（data[0]）和小数点后四位（data[2]~data[5]）
    num_str[0] = data[0];          // '0'
    num_str[1] = '.';                        // 小数点
    num_str[2] = data[2];          // '0'
    num_str[3] = data[3];          // '6'
    num_str[4] = data[4];          // '8'
    num_str[5] = data[5];          // '0'
    num_str[6] = '\0';                     // 字符串结束符
    
    // 字符串转浮点数
    return  atof(num_str);
   
}


//------------------------------------------------------------------
int main(void){	  
    BSP_Init();
    SYS_INIT();
	device_load();
	while(1)
	{     
		JIARE_DIAOYONG();           //加热器
		SHOW_PANDUAN();             //判断有显无显
		SENSOR_DIAOYONG();          //传感器
		SHUCHU_DIAOYONG();          //信号输出
		LCD_shuchu();               //显示输出    调用lcd_shuzhixianshi
		KEY_MAIN_FUNC();            //按键处理
	}
}
//------------------------------------------------------------------

//------------------------------------------------------------------
/**
 * 延迟函数
 */

void Delay(int Count)
{
	int i;
  for(i = 0; i < Count; i++);
}
//------------------------------------------------------------------
void Delay_1us(void)
{
	uint8 i;
  	for(i = 0; i < SYS_TIMER_1US; i++);
}
//------------------------------------------------------------------
//------------------------------------------------------------------
void Delay_us(u8 dat)
{
	uint8 i;
  	for(i = 0; i < dat; i++)Delay_1us();
}
//------------------------------------------------------------------
void Delay_1ms(void)
{
	uint16 i;
  	for(i = 0; i < SYS_TIMER_1MS; i++);
}
//------------------------------------------------------------------
void Delay_ms(u16 ms)
{
	u16 i;
  	for(i = 0; i < ms; i++)Delay_1ms();
}
//------------------------------------------------------------------


/********************************************************************
					main.c的程序到此结束。
*********************************************************************/

