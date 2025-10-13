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
	for(i=60;i>0;i--)
	{
	 	LCD_chushihua(i);
		if(i<50)
		{
			sensor_chushihuachuanganqi();//初始化传感器信息
		}
		Delay_ms(100);
		SENSOR_DIAOYONG();
		Delay_ms(900);
		if(JCXI_qitileixing == 2){
			//如果是氧气输出15.15ma
			DIANLIU_420MA_SET((u16)((JCXI_420ma20-JCXI_420ma4)/JCXI_zuidaliangcheng*20.9 + JCXI_420ma4));
		}
	}
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



//------------------------------------------------------------------
int main(void){	  
    BSP_Init();
    SYS_INIT();
	device_load();
	while(1)
	{
		JIARE_DIAOYONG();//加热器
		SHOW_PANDUAN();//判断有显无显
		SENSOR_DIAOYONG();//传感器
		SHUCHU_DIAOYONG();//信号输出
		LCD_shuchu();//显示输出
		KEY_MAIN_FUNC();//按键处理
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

