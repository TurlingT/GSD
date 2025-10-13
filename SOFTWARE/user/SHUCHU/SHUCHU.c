/*****************************************************************************
* filename
* SHUCHU.c
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
//指示灯
void led_shuchu(void){
	if(JCXI_qitileixing == 2){
		//氧气
		if(chuanganqizhuangtai == 1)
		{
			LED_ERROR_ON();
			LED_WORK_OFF();
			LED_ALARMH_OFF();
			LED_ALARML_OFF();
		}
		else
		{
			if(chuanganqizhuangtai == 0)
			{
				LED_ERROR_OFF();
				LED_WORK_ON();
				LED_ALARMH_OFF();
				LED_ALARML_OFF();
			}
			if(chuanganqizhuangtai == 2)
			{
				LED_ERROR_OFF();
				LED_WORK_ON();
				LED_ALARMH_OFF();
				LED_ALARML_ON();
			}
			if(chuanganqizhuangtai >= 3)
			{
					LED_ERROR_OFF();
					LED_WORK_ON();
					LED_ALARMH_ON();
					LED_ALARML_OFF();
			}
		}
	}
	else{
		if(chuanganqizhuangtai == 1)
		{
			LED_ERROR_ON();
			LED_WORK_OFF();
			LED_ALARMH_OFF();
			LED_ALARML_OFF();
		}
		else
		{
			if(chuanganqizhuangtai == 0)
			{
				LED_ERROR_OFF();
				LED_WORK_ON();
				LED_ALARMH_OFF();
				LED_ALARML_OFF();
			}
			if(chuanganqizhuangtai == 2)
			{
				LED_ERROR_OFF();
				LED_WORK_ON();
				LED_ALARMH_OFF();
				LED_ALARML_ON();
			}
			if(chuanganqizhuangtai >= 3)
			{
					LED_ERROR_OFF();
					LED_WORK_ON();
					LED_ALARMH_ON();
					LED_ALARML_ON();
			}
		}
	}
}
//-----------------------------------------------------------

//------------------------------------------------------------------------------
//4-20MA
void Am4_20_shuchu(void){
float temp1 =0;
	if(dianliubuzhou>0)
	{
	}
	else
	{

		if(chuanganqizhuangtai ==1)
		{
			DIANLIU_420MA_SET(JCXI_420ma4/2);
		}
		else
		{
			if(qitinongdu<=JCXI_zuixiaoliangcheng)
			{
				DIANLIU_420MA_SET(JCXI_420ma4);
			}
			else if(qitinongdu>=JCXI_zuidaliangcheng)
			{
				DIANLIU_420MA_SET(JCXI_420ma20);
			}
			else
			{
				temp1 =  (JCXI_420ma20-JCXI_420ma4)/JCXI_zuidaliangcheng*qitinongdu+JCXI_420ma4;
				DIANLIU_420MA_SET((u16)temp1);
			}
		}
	}
}
//-----------------------------------------------------------

//------------------------------------------------------------------------------
//继电器
void jidianqi_shuchu(void){
	if(JCXI_qitileixing == 2){
		//氧气
		if(chuanganqizhuangtai == 2)
		{
			if(JCXI_jidianqigenshuiDIBAO == 0)
			{
				if(dibaojidianqishuchuwancheng)
				{
		   
				}
				else
				{
					//打开低报继电器 		   
					JIDIANQI_ALARML_ON();
					dibaojidianqishuchuwancheng = TRUE;
					Delay_ms(1000);
					//关闭低报继电器 			   
					JIDIANQI_ALARML_OFF();
				}
			}
			else
			{
				//打开低报继电器    
				JIDIANQI_ALARML_ON();
			}	
			JIDIANQI_ALARMH_OFF();
		}
		else if(chuanganqizhuangtai == 3 )
		{
			if(JCXI_jidianqigenshuigaobao== 0)
			{
				if(gaobaojidianqishuchuwancheng)
				{
		
				}
				else
				{
					//打开高爆继电器    
					JIDIANQI_ALARMH_ON();
					gaobaojidianqishuchuwancheng = TRUE;
					Delay_ms(1000);
					//关闭高爆继电器 		   
					JIDIANQI_ALARMH_OFF();
				}   
			}
			else
			{
				//打开高爆继电器
				JIDIANQI_ALARMH_ON();
			}   
			JIDIANQI_ALARML_OFF();
		}
		else
		{  
		   dibaojidianqishuchuwancheng=FALSE;
		   gaobaojidianqishuchuwancheng=FALSE;
		   //关闭所有继电器
		   JIDIANQI_ALARML_OFF();
		   JIDIANQI_ALARMH_OFF();
		}
	}
	else{
		if(chuanganqizhuangtai >= 2)
		{
			   if(JCXI_jidianqigenshuiDIBAO == 0)
			   {
				   if(dibaojidianqishuchuwancheng)
					   {
		   
					   }
				   else
					   {
						   //打开低报继电器 		   
						   JIDIANQI_ALARML_ON();
						   dibaojidianqishuchuwancheng = TRUE;
						   Delay_ms(1000);
						   //关闭低报继电器 			   
						   JIDIANQI_ALARML_OFF();
					   }
					   
			   }
			   else
			   {
				   //打开低报继电器    
				   JIDIANQI_ALARML_ON();
			   }			   
			if(chuanganqizhuangtai == 3 )
			{
			   if(JCXI_jidianqigenshuigaobao== 0)
			   {
				   if(gaobaojidianqishuchuwancheng)
					   {
		
					   }
				   else
					   {
						   //打开高爆继电器    
						   JIDIANQI_ALARMH_ON();
						   gaobaojidianqishuchuwancheng = TRUE;
						   Delay_ms(1000);
						   //关闭高爆继电器 		   
						   JIDIANQI_ALARMH_OFF();
					   }
					   
			   }
			   else
			   {
				   //打开高爆继电器
				   JIDIANQI_ALARMH_ON();
			   }   
			}
			else
			{
			   JIDIANQI_ALARMH_OFF();
			}
		}
		else
		{  
		   dibaojidianqishuchuwancheng=FALSE;
		   gaobaojidianqishuchuwancheng=FALSE;
		   //关闭所有继电器
		   JIDIANQI_ALARML_OFF();
		   JIDIANQI_ALARMH_OFF();
		}
	}
}
//-----------------------------------------------------------


//------------------------------------------------------------------------------
void SHUCHU_DIAOYONG(void){
	 led_shuchu();
	 Am4_20_shuchu();
	 jidianqi_shuchu();
	 MODBUS_SHUCHU();
}
//-----------------------------------------------------------

/********************************************************************
					SHUCHU.c的程序到此结束。
*********************************************************************/
