#ifndef _SYS_INIT_H_
#define _SYS_INIT_H_
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
extern u8	 Timer_100ms; 
extern bool Timer_100ms_state;
extern u8	 Timer_1s;
extern bool Timer_1s_state;

extern u16  STM_ADC_DATA[ADC_VALUE_LENGTH];
extern bool STM_ADC_NEW_DATA; 
extern bool STM_ADC_DATA_POS;
extern float wenducaijizhi;

extern u8 jieshou_485[8];
extern u8 fasong_485[13];
extern u8 jieshouweizhi_485;
extern u8 fasongweizhi_485;
extern bool wanchengjieshou_485;
extern u8 JCXI_485_ID;

extern u8 jieshou_232[10];
extern u8 fasong_232[13];
extern u8 jieshouweizhi;
extern u8 fasongweizhi;
extern bool wanchengjieshou_232;
extern float qitinongdu ;
extern u8 chuanganqizhuangtai ;
extern u16 JCXI_zuidaliangcheng ;
extern u16 JCXI_zuixiaoliangcheng ;
extern u16 JCXI_gaobaojing;
extern u16 JCXI_dibaojing;
extern u8	JCXI_qitileixing;
extern u8	JCXI_qitidanwei;
extern u8	jcxibuzhou;
extern u8 jiaozhunbuzhou;
extern u32 jiaozhunxianshi;
extern u16 chuanganqijieshou;

extern u8 uart4_recv_flag;

extern bool LCD_SHOW_YON;
extern bool upxianshimoshi;
extern bool shifouchushihualcd;

extern u8 xianshimoshi;
extern u8 caidanweizhi;

extern u8 shuruzu[];
extern u8 zuidacaidanshu;
extern u8 zuixiaocaidanshu;
extern u8 shuruweizhi;
extern u8 dianliubuzhou;

extern u16  JCXI_420ma4;
extern u16  JCXI_420ma20;
extern u8 JCXI_jidianqigenshuiDIBAO;
extern u8 JCXI_jidianqigenshuigaobao;
extern bool dibaojidianqishuchuwancheng ;
extern bool gaobaojidianqishuchuwancheng;

//---------------------------------------------------------------------------
void SYS_INIT(void);

#endif
/********************************************************************
					SYS_INIT.h的程序到此结束。
*********************************************************************/
