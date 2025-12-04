#include "includes.h"

//*******************************************************************************
char NUM_MABIAO_ZHENG[] = {0x00,0xf9,0x09,0xbc,0x9d,0x4d,0xd5,0xf5,0x89,0xfd,0xdd,0xed,0x75,0xf0,0x3d,0xf4,0xe4,0x6d,0x35,0x70,0xd5,0xe9,0x04,0xff,0x24,0xe0,0x19};
//dat:                    null   0   1  2    3   4   5   6   7    8   9  a  b   c  d   e  f  h      o  l  s n  - FULL  R   T   J
						  //0    1   2  3    4   5   6   7   8    9   10 11 12  13 14  15 16 17    18  19 2021 22  23  24  25  26
char NUM_MABIAO_FAN[] =  {0x00,0x9f,0x90,0xcb,0xd9,0xd4,0x5d,0x5f,0x98,0xdf,0xdd,0xde,0x57,0x0f,0xd3,0x4f,0x4e,0xd6,0x53,0x07,0x5d,0x9e,0x40,0xff,0x42,0x0e,0x91};
//dat:                    null  0   1  2    3   4   5   6   7    8   9  a  b   c  d   e  f   h    o   l  s n  -  FULL  R  T    J 
                         //0    1   2  3    4   5   6   7   8    9   10 11 12  13 14  15 16 17    18  19 2021 22  23  24  25   26 
char yipaishuzi[] ={0xf9,0x09,0xbc,0x9d,0x4d,0xd5,0xf5,0x89,0xfd,0xdd,0x00};
//第一排数字 注意最后为空

char erpaishuzi[] ={0x9f,0x90,0xcb,0xd9,0xd4,0x5d,0x5f,0x98,0xdf,0xdd,0x00};
//第二排数字 注意最后为空

char QITIleixing1[] ={2,0,0,0,0,0,0,0,0,0,0,0,0,0,13,0,0,0,0,13,0,0,0};
char QITIleixing2[] ={20,13,0,0,20,17,21,17,17,13,0,21,0,0,7,0,0,0,17,19,12,0,0};
char QITIleixing3[] ={1,17,1,13,1,3,17,13,13,19,1,1,21,17,17,17,26,17,13,1,24,26,26};
char QITIleixing4[] ={12,5,3,1,3,20,4,19,17,3,4,3,1,17,7,3,11,16,21,3,3,12,13};
// ISOB CH4 O2 CO SO2 H2S NH3 HCL HCH CL2 O3 NO2 NO HH C6H6 H2 JA HF HCN CLO2 BR2 JB JC

char baweima_1_dianzhizhi[]={0x40,0x20,0x10};//第一行3个点
char baweima_2_dianzhizhi[]={0x80,0x40,0x20,0x10};//第二行3个点
char zhuangtaizhi[] = {0x80,0x40,0x20,0x10} ;//状态地址
char anjiantishizhi[] ={0x80,0x40,0x20};//按键提示地址
char danweizhi[]= {0x00,0x80,0x20,0x40,0x10};//单位地址


u8 baweima_1_1_1 = 0<<2;
u8 baweima_1_1_2 = 1<<2;
u8 baweima_1_2_1 = 2<<2;
u8 baweima_1_2_2 = 3<<2;
u8 baweima_1_3_1 = 4<<2;
u8 baweima_1_3_2 = 5<<2;
u8 baweima_1_4_1 = 7<<2;
u8 baweima_1_4_2 = 8<<2;
//第一排地址
u8 baweima_1_dian=  6<<2;
//第一行点
u8 baweima_2_1_1 = 21<<2;
u8 baweima_2_1_2 = 22<<2;
u8 baweima_2_2_1 = 19<<2;
u8 baweima_2_2_2 = 20<<2;
u8 baweima_2_3_1 = 17<<2;
u8 baweima_2_3_2 = 18<<2;
u8 baweima_2_4_1 = 15<<2;
u8 baweima_2_4_2 = 16<<2;
u8 baweima_2_5_1 = 12<<2;
u8 baweima_2_5_2 = 11<<2;
//第二行位置
u8 baweima_2_dian = 14<<2;
//第二行点
u8 zhuangtai  = 9<<2;
//状态地址
u8 anjiantishi = 10<<2;
//按键提示地址
u8 danwei = 13<<2;
//单位地址


//*******************************************************************************

//---------------------------------------------------------------------------
void LCD_CLEAR(void)
{
	LCD_wr_dat(baweima_1_1_1,baweima_1_1_2,0x00);
	LCD_wr_dat(baweima_1_2_1,baweima_1_2_2,0x00);
	LCD_wr_dat(baweima_1_3_1,baweima_1_3_2,0x00);
	LCD_wr_dat(baweima_1_4_1,baweima_1_4_2,0x00);
	
	LCD_wr_dat(baweima_2_1_1,baweima_2_1_2,0x00);
	LCD_wr_dat(baweima_2_2_1,baweima_2_2_2,0x00);
	LCD_wr_dat(baweima_2_3_1,baweima_2_3_2,0x00);
	LCD_wr_dat(baweima_2_4_1,baweima_2_4_2,0x00);
	LCD_wr_dat(baweima_2_5_1,baweima_2_5_2,0x00);
	
	LCD_wr_BIT4(danwei,0x00);
	//关闭气体单位
	LCD_wr_BIT4(baweima_2_dian,0x00);
	//关闭第二行小数点
	LCD_wr_BIT4(baweima_1_dian,0x00);
	//关闭第一行小数点	
	 LCD_wr_BIT4(zhuangtai,0X00);
	//当前状态
	LCD_wr_BIT4(anjiantishi,0X00);
	//关闭按键

}
//------------------------------------------------------------------

//------------------------------------------------------------------------------
void LCD_LOADERR(void){
	LCD_CLEAR();

	LCD_wr_dat(baweima_1_1_1,baweima_1_1_2,NUM_MABIAO_ZHENG[19]);
	LCD_wr_dat(baweima_1_2_1,baweima_1_2_2,NUM_MABIAO_ZHENG[18]);
	LCD_wr_dat(baweima_1_3_1,baweima_1_3_2,NUM_MABIAO_ZHENG[11]);
	LCD_wr_dat(baweima_1_4_1,baweima_1_4_2,NUM_MABIAO_ZHENG[14]);

	LCD_wr_dat(baweima_2_1_1,baweima_2_1_2,NUM_MABIAO_FAN[0]);
	LCD_wr_dat(baweima_2_2_1,baweima_2_2_2,NUM_MABIAO_FAN[15]);
	LCD_wr_dat(baweima_2_3_1,baweima_2_3_2,NUM_MABIAO_FAN[24]);
	LCD_wr_dat(baweima_2_4_1,baweima_2_4_2,NUM_MABIAO_FAN[24]);
	LCD_wr_dat(baweima_2_5_1,baweima_2_5_2,NUM_MABIAO_FAN[0]); 

}
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
void LCD_chushihua(u8 temp){
	if(temp >50){	
		if(temp%2==0)
		{
			LCD_wr_dat(baweima_1_1_1,baweima_1_1_2,0xff);
			LCD_wr_dat(baweima_1_2_1,baweima_1_2_2,0xff);
			LCD_wr_dat(baweima_1_3_1,baweima_1_3_2,0xff);
			LCD_wr_dat(baweima_1_4_1,baweima_1_4_2,0xff);
				
			LCD_wr_BIT4(baweima_1_dian,0xff);
			//关闭第一行小数点	
			LCD_wr_dat(baweima_2_1_1,baweima_2_1_2,0xff);
			LCD_wr_dat(baweima_2_2_1,baweima_2_2_2,0xff);
			LCD_wr_dat(baweima_2_3_1,baweima_2_3_2,0xff);
			LCD_wr_dat(baweima_2_4_1,baweima_2_4_2,0xff);
			LCD_wr_dat(baweima_2_5_1,baweima_2_5_2,0xff);
			LCD_wr_BIT4(baweima_2_dian,0xff);
			//关闭第二行小数点
			LCD_wr_BIT4(danwei,0xff);
			//关闭气体单位			
			LCD_wr_BIT4(zhuangtai,0xff);
			//当前状态
			LCD_wr_BIT4(anjiantishi,0xff);
			//关闭按键
		}
		else
		{
			LCD_CLEAR();
		}
	}
	else{
		LCD_CLEAR();
		LCD_wr_dat(baweima_1_1_1,baweima_1_1_2,NUM_MABIAO_ZHENG[19]);
		LCD_wr_dat(baweima_1_2_1,baweima_1_2_2,NUM_MABIAO_ZHENG[18]);
		LCD_wr_dat(baweima_1_3_1,baweima_1_3_2,NUM_MABIAO_ZHENG[11]);
		LCD_wr_dat(baweima_1_4_1,baweima_1_4_2,NUM_MABIAO_ZHENG[14]);	
			
		LCD_wr_dat(baweima_2_1_1,baweima_2_1_2,erpaishuzi[10]);
		LCD_wr_dat(baweima_2_2_1,baweima_2_2_2,erpaishuzi[10]);
		LCD_wr_dat(baweima_2_3_1,baweima_2_3_2,erpaishuzi[10]);
		LCD_wr_dat(baweima_2_4_1,baweima_2_4_2,erpaishuzi[(temp/10)]);
		LCD_wr_dat(baweima_2_5_1,baweima_2_5_2,erpaishuzi[(temp%10)]);		
	}
	
}
//------------------------------------------------------------------------------

//---------------------------------------------------------------------------
//菜单显示
void lcd_caidanxianshi(void)
{
	u8 temp3, temp4;
	temp3 = (u8)(caidanweizhi /10);
	temp4 = (u8)(caidanweizhi %10);
	LCD_wr_BIT4(danwei,0x00);
	//关闭气体单位
	LCD_wr_BIT4(baweima_2_dian,0x00);
	//关闭第二行小数点
	 LCD_wr_BIT4(zhuangtai,zhuangtaizhi[3]);
	//当前状态

	 LCD_wr_dat(baweima_1_1_1,baweima_1_1_2,NUM_MABIAO_ZHENG[20]);
	 LCD_wr_dat(baweima_1_2_1,baweima_1_2_2,NUM_MABIAO_ZHENG[22]);
	 LCD_wr_dat(baweima_1_3_1,baweima_1_3_2,yipaishuzi[temp3]);
	 LCD_wr_dat(baweima_1_4_1,baweima_1_4_2,yipaishuzi[temp4]);
			
	 LCD_wr_dat(baweima_2_1_1,baweima_2_1_2,0x00);
	 LCD_wr_dat(baweima_2_2_1,baweima_2_2_2,0x00);
	 LCD_wr_dat(baweima_2_3_1,baweima_2_3_2,0x00);
	 LCD_wr_dat(baweima_2_4_1,baweima_2_4_2,0x00);
	 LCD_wr_dat(baweima_2_5_1,baweima_2_5_2,0x00);

}
//------------------------------------------------------------------


//------------------------------------------------------------------------------
// 输入模式
void LCD_shurumoshi(void){
	u8 temp3, temp4;
	temp3 = (u8)(caidanweizhi /10);
	temp4 = (u8)(caidanweizhi %10);
	 LCD_wr_BIT4(zhuangtai,zhuangtaizhi[3]);
	//当前状态		
	LCD_wr_dat(baweima_1_1_1,baweima_1_1_2,NUM_MABIAO_ZHENG[20]);
	LCD_wr_dat(baweima_1_2_1,baweima_1_2_2,NUM_MABIAO_ZHENG[22]);
	LCD_wr_dat(baweima_1_3_1,baweima_1_3_2,yipaishuzi[temp3]);
	LCD_wr_dat(baweima_1_4_1,baweima_1_4_2,yipaishuzi[temp4]);
	
//	if(jiaozhunbuzhou >0)
//		{
//				
//				LCD_wr_dat(baweima_2_1_1,baweima_2_1_2,erpaishuzi[shuruzu[0]]);
//				LCD_wr_dat(baweima_2_2_1,baweima_2_2_2,erpaishuzi[shuruzu[1]]);
//				LCD_wr_dat(baweima_2_3_1,baweima_2_3_2,erpaishuzi[shuruzu[2]]);
//				LCD_wr_dat(baweima_2_4_1,baweima_2_4_2,erpaishuzi[shuruzu[3]]);
//				LCD_wr_dat(baweima_2_5_1,baweima_2_5_2,erpaishuzi[shuruzu[4]]);		
//		}
//	else{
			switch(shuruweizhi)
				{
					case 0:
						if(Timer_1s%2 == 0)
						{
							LCD_wr_dat(baweima_2_1_1,baweima_2_1_2,0x00);
							LCD_wr_dat(baweima_2_2_1,baweima_2_2_2,erpaishuzi[shuruzu[1]]);
							LCD_wr_dat(baweima_2_3_1,baweima_2_3_2,erpaishuzi[shuruzu[2]]);
							LCD_wr_dat(baweima_2_4_1,baweima_2_4_2,erpaishuzi[shuruzu[3]]);
							LCD_wr_dat(baweima_2_5_1,baweima_2_5_2,erpaishuzi[shuruzu[4]]);
						}
						else
						{
							LCD_wr_dat(baweima_2_1_1,baweima_2_1_2,erpaishuzi[shuruzu[0]]);
							LCD_wr_dat(baweima_2_2_1,baweima_2_2_2,erpaishuzi[shuruzu[1]]);
							LCD_wr_dat(baweima_2_3_1,baweima_2_3_2,erpaishuzi[shuruzu[2]]);
							LCD_wr_dat(baweima_2_4_1,baweima_2_4_2,erpaishuzi[shuruzu[3]]);
							LCD_wr_dat(baweima_2_5_1,baweima_2_5_2,erpaishuzi[shuruzu[4]]);
						}
					break;
					case 1:
						if(Timer_1s%2 == 0)
						{
							LCD_wr_dat(baweima_2_1_1,baweima_2_1_2,erpaishuzi[shuruzu[0]]);
							LCD_wr_dat(baweima_2_2_1,baweima_2_2_2,0x00);
							LCD_wr_dat(baweima_2_3_1,baweima_2_3_2,erpaishuzi[shuruzu[2]]);
							LCD_wr_dat(baweima_2_4_1,baweima_2_4_2,erpaishuzi[shuruzu[3]]);
							LCD_wr_dat(baweima_2_5_1,baweima_2_5_2,erpaishuzi[shuruzu[4]]);
						}
						else
						{
							LCD_wr_dat(baweima_2_1_1,baweima_2_1_2,erpaishuzi[shuruzu[0]]);
							LCD_wr_dat(baweima_2_2_1,baweima_2_2_2,erpaishuzi[shuruzu[1]]);
							LCD_wr_dat(baweima_2_3_1,baweima_2_3_2,erpaishuzi[shuruzu[2]]);
							LCD_wr_dat(baweima_2_4_1,baweima_2_4_2,erpaishuzi[shuruzu[3]]);
							LCD_wr_dat(baweima_2_5_1,baweima_2_5_2,erpaishuzi[shuruzu[4]]);
						}
					break;
					case 2:
						if(Timer_1s%2 == 0)
						{
							LCD_wr_dat(baweima_2_1_1,baweima_2_1_2,erpaishuzi[shuruzu[0]]);
							LCD_wr_dat(baweima_2_2_1,baweima_2_2_2,erpaishuzi[shuruzu[1]]);
							LCD_wr_dat(baweima_2_3_1,baweima_2_3_2,0x00);
							LCD_wr_dat(baweima_2_4_1,baweima_2_4_2,erpaishuzi[shuruzu[3]]);
							LCD_wr_dat(baweima_2_5_1,baweima_2_5_2,erpaishuzi[shuruzu[4]]);
						}
						else
						{
							LCD_wr_dat(baweima_2_1_1,baweima_2_1_2,erpaishuzi[shuruzu[0]]);
							LCD_wr_dat(baweima_2_2_1,baweima_2_2_2,erpaishuzi[shuruzu[1]]);
							LCD_wr_dat(baweima_2_3_1,baweima_2_3_2,erpaishuzi[shuruzu[2]]);
							LCD_wr_dat(baweima_2_4_1,baweima_2_4_2,erpaishuzi[shuruzu[3]]);
							LCD_wr_dat(baweima_2_5_1,baweima_2_5_2,erpaishuzi[shuruzu[4]]);
						}
					break;
					case 3:
						if(Timer_1s%2 == 0)
						{
							LCD_wr_dat(baweima_2_1_1,baweima_2_1_2,erpaishuzi[shuruzu[0]]);
							LCD_wr_dat(baweima_2_2_1,baweima_2_2_2,erpaishuzi[shuruzu[1]]);
							LCD_wr_dat(baweima_2_3_1,baweima_2_3_2,erpaishuzi[shuruzu[2]]);
							LCD_wr_dat(baweima_2_4_1,baweima_2_4_2,0x00);
							LCD_wr_dat(baweima_2_5_1,baweima_2_5_2,erpaishuzi[shuruzu[4]]);
						}
						else
						{
							LCD_wr_dat(baweima_2_1_1,baweima_2_1_2,erpaishuzi[shuruzu[0]]);
							LCD_wr_dat(baweima_2_2_1,baweima_2_2_2,erpaishuzi[shuruzu[1]]);
							LCD_wr_dat(baweima_2_3_1,baweima_2_3_2,erpaishuzi[shuruzu[2]]);
							LCD_wr_dat(baweima_2_4_1,baweima_2_4_2,erpaishuzi[shuruzu[3]]);
							LCD_wr_dat(baweima_2_5_1,baweima_2_5_2,erpaishuzi[shuruzu[4]]);
						}
					break;
					default:
							if(Timer_1s%2 == 0)
							{
								LCD_wr_dat(baweima_2_1_1,baweima_2_1_2,erpaishuzi[shuruzu[0]]);
								LCD_wr_dat(baweima_2_2_1,baweima_2_2_2,erpaishuzi[shuruzu[1]]);
								LCD_wr_dat(baweima_2_3_1,baweima_2_3_2,erpaishuzi[shuruzu[2]]);
								LCD_wr_dat(baweima_2_4_1,baweima_2_4_2,erpaishuzi[shuruzu[3]]);
								LCD_wr_dat(baweima_2_5_1,baweima_2_5_2,0x00);
							}
							else
							{
								LCD_wr_dat(baweima_2_1_1,baweima_2_1_2,erpaishuzi[shuruzu[0]]);
								LCD_wr_dat(baweima_2_2_1,baweima_2_2_2,erpaishuzi[shuruzu[1]]);
								LCD_wr_dat(baweima_2_3_1,baweima_2_3_2,erpaishuzi[shuruzu[2]]);
								LCD_wr_dat(baweima_2_4_1,baweima_2_4_2,erpaishuzi[shuruzu[3]]);
								LCD_wr_dat(baweima_2_5_1,baweima_2_5_2,erpaishuzi[shuruzu[4]]);
							}
					break;
				}
//		}

 }
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// 输入正确
void LCD_OK(void){
	u8 temp3, temp4;
	temp3 = (u8)(caidanweizhi /10);
	temp4 = (u8)(caidanweizhi %10);
	LCD_CLEAR();
	 LCD_wr_BIT4(zhuangtai,zhuangtaizhi[3]);
	//当前状态

		
	LCD_wr_dat(baweima_1_1_1,baweima_1_1_2,NUM_MABIAO_ZHENG[20]);
	LCD_wr_dat(baweima_1_2_1,baweima_1_2_2,NUM_MABIAO_ZHENG[22]);
	LCD_wr_dat(baweima_1_3_1,baweima_1_3_2,yipaishuzi[temp3]);
	LCD_wr_dat(baweima_1_4_1,baweima_1_4_2,yipaishuzi[temp4]);
			
	LCD_wr_dat(baweima_2_1_1,baweima_2_1_2,NUM_MABIAO_FAN[16]);
	LCD_wr_dat(baweima_2_2_1,baweima_2_2_2,NUM_MABIAO_FAN[21]);
	LCD_wr_dat(baweima_2_3_1,baweima_2_3_2,NUM_MABIAO_FAN[2]);
	LCD_wr_dat(baweima_2_4_1,baweima_2_4_2,NUM_MABIAO_FAN[20]);
	LCD_wr_dat(baweima_2_5_1,baweima_2_5_2,NUM_MABIAO_FAN[17]);
		
	Delay_ms(2000);
	xianshimoshi = 0;


}

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// 输入错误
void LCD_ERR(void){
	u8 temp3, temp4;
	temp3 = (u8)(caidanweizhi /10);
	temp4 = (u8)(caidanweizhi %10);
	LCD_CLEAR();
	 LCD_wr_BIT4(zhuangtai,zhuangtaizhi[3]);
	//当前状态
	
	LCD_wr_dat(baweima_1_1_1,baweima_1_1_2,NUM_MABIAO_ZHENG[20]);
	LCD_wr_dat(baweima_1_2_1,baweima_1_2_2,NUM_MABIAO_ZHENG[22]);
	LCD_wr_dat(baweima_1_3_1,baweima_1_3_2,yipaishuzi[temp3]);
	LCD_wr_dat(baweima_1_4_1,baweima_1_4_2,yipaishuzi[temp4]);
			
	LCD_wr_dat(baweima_2_1_1,baweima_2_1_2,0x00);
	LCD_wr_dat(baweima_2_2_1,baweima_2_2_2,NUM_MABIAO_FAN[15]);
	LCD_wr_dat(baweima_2_3_1,baweima_2_3_2,NUM_MABIAO_FAN[24]);
	LCD_wr_dat(baweima_2_4_1,baweima_2_4_2,NUM_MABIAO_FAN[24]);
	LCD_wr_dat(baweima_2_5_1,baweima_2_5_2,0x00);
	
	Delay_ms(2000);
	xianshimoshi = 0;

 }
//-----------------------------------------------------------------------------

float temp6; 
extern int result;
//---------------------------------------------------------------------------
//显示气体浓度
void lcd_shuzhixianshi(void)
{
	u8 temp1,temp2,temp3,temp4,temp5;

	temp6 = qitinongdu;
		if(temp6>JCXI_zuidaliangcheng){
			temp6=JCXI_zuidaliangcheng;
		}			
	    temp1 = (u8)(temp6/1000);
		temp2 = (u8)((temp6 - temp1 *1000)/100);
		temp3 = (u8)((temp6 - temp1 *1000 - temp2*100)/10);
		temp4 = (u8)((temp6 - temp1 *1000 - temp2*100 - temp3*10));
		temp5 = (u8)((u32)(temp6*10)%10);
		if(temp1==0){
			if(temp2==0){
				if(temp3==0){
					LCD_wr_dat(baweima_2_1_1,baweima_2_1_2,erpaishuzi[10]);
					LCD_wr_dat(baweima_2_2_1,baweima_2_2_2,erpaishuzi[10]);
					LCD_wr_dat(baweima_2_3_1,baweima_2_3_2,erpaishuzi[10]);
					LCD_wr_dat(baweima_2_4_1,baweima_2_4_2,erpaishuzi[temp4]);
					LCD_wr_dat(baweima_2_5_1,baweima_2_5_2,erpaishuzi[temp5]);
				}
				else{
					LCD_wr_dat(baweima_2_1_1,baweima_2_1_2,erpaishuzi[10]);
					LCD_wr_dat(baweima_2_2_1,baweima_2_2_2,erpaishuzi[10]);
					LCD_wr_dat(baweima_2_3_1,baweima_2_3_2,erpaishuzi[temp3]);
					LCD_wr_dat(baweima_2_4_1,baweima_2_4_2,erpaishuzi[temp4]);
					LCD_wr_dat(baweima_2_5_1,baweima_2_5_2,erpaishuzi[temp5]);

				}			
			}
			else{
				LCD_wr_dat(baweima_2_1_1,baweima_2_1_2,erpaishuzi[10]);
				LCD_wr_dat(baweima_2_2_1,baweima_2_2_2,erpaishuzi[temp2]);
				LCD_wr_dat(baweima_2_3_1,baweima_2_3_2,erpaishuzi[temp3]);
				LCD_wr_dat(baweima_2_4_1,baweima_2_4_2,erpaishuzi[temp4]);
				LCD_wr_dat(baweima_2_5_1,baweima_2_5_2,erpaishuzi[temp5]);

			}		
		}
		else{
			LCD_wr_dat(baweima_2_1_1,baweima_2_1_2,erpaishuzi[temp1]);
			LCD_wr_dat(baweima_2_2_1,baweima_2_2_2,erpaishuzi[temp2]);
			LCD_wr_dat(baweima_2_3_1,baweima_2_3_2,erpaishuzi[temp3]);
			LCD_wr_dat(baweima_2_4_1,baweima_2_4_2,erpaishuzi[temp4]);
			LCD_wr_dat(baweima_2_5_1,baweima_2_5_2,erpaishuzi[temp5]);
		}	
		LCD_wr_BIT4(danwei,danweizhi[JCXI_qitidanwei]);
		//气体单位
		LCD_wr_BIT4(baweima_2_dian,baweima_2_dianzhizhi[3]);
		//打开第二行小数点
		LCD_wr_BIT4(anjiantishi,0X00);
		//关闭按键		

}
//------------------------------------------------------------------


//------------------------------------------------------------------------------
//正常显示
void LCD_zhengchangmoshi(void){
	LCD_wr_BIT4(baweima_1_dian,0x00);
		//关闭第一行小数点		
		if((chuanganqizhuangtai == 0)||(chuanganqizhuangtai == 2)||(chuanganqizhuangtai == 3)){
				LCD_wr_dat(baweima_1_1_1,baweima_1_1_2,NUM_MABIAO_ZHENG[QITIleixing1[JCXI_qitileixing]]);
				LCD_wr_dat(baweima_1_2_1,baweima_1_2_2,NUM_MABIAO_ZHENG[QITIleixing2[JCXI_qitileixing]]);
				LCD_wr_dat(baweima_1_3_1,baweima_1_3_2,NUM_MABIAO_ZHENG[QITIleixing3[JCXI_qitileixing]]);
	   		    LCD_wr_dat(baweima_1_4_1,baweima_1_4_2,NUM_MABIAO_ZHENG[QITIleixing4[JCXI_qitileixing]]);	
				lcd_shuzhixianshi();
	   }else if(chuanganqizhuangtai ==1){
			LCD_wr_dat(baweima_1_1_1,baweima_1_1_2,NUM_MABIAO_ZHENG[22]);
			LCD_wr_dat(baweima_1_2_1,baweima_1_2_2,NUM_MABIAO_ZHENG[22]);
			LCD_wr_dat(baweima_1_3_1,baweima_1_3_2,NUM_MABIAO_ZHENG[22]);
			LCD_wr_dat(baweima_1_4_1,baweima_1_4_2,NUM_MABIAO_ZHENG[22]);

			LCD_wr_dat(baweima_2_1_1,baweima_2_1_2,0x00);
			LCD_wr_dat(baweima_2_2_1,baweima_2_2_2,0x00);
			LCD_wr_dat(baweima_2_3_1,baweima_2_3_2,0x00);
			LCD_wr_dat(baweima_2_4_1,baweima_2_4_2,0x00);
			LCD_wr_dat(baweima_2_5_1,baweima_2_5_2,0x00);

			LCD_wr_dat(baweima_2_1_1,baweima_2_1_2,NUM_MABIAO_FAN[22]);
			LCD_wr_dat(baweima_2_2_1,baweima_2_2_2,NUM_MABIAO_FAN[22]);
			LCD_wr_dat(baweima_2_3_1,baweima_2_3_2,NUM_MABIAO_FAN[22]);
			LCD_wr_dat(baweima_2_4_1,baweima_2_4_2,NUM_MABIAO_FAN[22]);
			LCD_wr_dat(baweima_2_5_1,baweima_2_5_2,NUM_MABIAO_FAN[22]);

			LCD_wr_BIT4(danwei,0x00);
			//关闭气体单位
			LCD_wr_BIT4(baweima_2_dian,0x00);
			//关闭第二行小数点
		}
	   LCD_wr_BIT4(zhuangtai,zhuangtaizhi[0]);

 }
//------------------------------------------------------------------------------


//---------------------------------------------------------------------------
void LCD_shuchu(void){
	switch(xianshimoshi){
		case 1://菜单模式
			lcd_caidanxianshi();
			break;
		case 2://输入模式
			LCD_shurumoshi();
			break;
		case 3://显示正确
			LCD_OK();
			break;
		case 4://显示错误
			LCD_ERR();
			break;
		 default:
			LCD_zhengchangmoshi();
		 break;	  
		}
 }

//------------------------------------------------------------------


