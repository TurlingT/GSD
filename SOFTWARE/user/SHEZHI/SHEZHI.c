/*****************************************************************************
* filename
* SHEZHI.c
*
*
* 描述
* 这个文件实现主程序相关功能函数.
*
*
* (c) 2007 Jiwen Su
*****************************************************************************/
#include "includes.h"


//---------------------------------------------------------------------------
void Shezhi_DY(void){
u8 i;
u16 temp1;
u16 temp2;
	switch(caidanweizhi){
		case 1://低报警设置			
			temp1 = shuruzu[0]*10000+ shuruzu[1]*1000+ shuruzu[2]*100+ shuruzu[3]*10+ shuruzu[4];
			if((temp1>JCXI_zuixiaoliangcheng)&&(temp1<JCXI_zuidaliangcheng*10)&&(temp1<JCXI_gaobaojing))
			{
				JCXI_dibaojing = temp1;
				fasong_232[0] =0x5a;
				fasong_232[1] =0xa5;
				fasong_232[2] =0x00;
				fasong_232[3] =0xe2;
				fasong_232[4] =temp1/256;
				fasong_232[5] =temp1%256;
				fasong_232[6] =0x00;
				fasong_232[7] =0x00;
				fasong_232[8] =0x00;
				fasong_232[9] =0x01;				
				SENSOR_KAISHIFASONG();
				xianshimoshi =3;
			}
			else
			{
				xianshimoshi = 4;
			}
		break;
		case 2://高报警设置
			temp1 = shuruzu[0]*10000+ shuruzu[1]*1000+ shuruzu[2]*100+ shuruzu[3]*10+ shuruzu[4];
			if((temp1>JCXI_zuixiaoliangcheng)&&(temp1<JCXI_zuidaliangcheng*10.0)&&(temp1>JCXI_dibaojing))
			{
				JCXI_gaobaojing= temp1;
						
				fasong_232[0] =0x5a;
				fasong_232[1] =0xa5;
				fasong_232[2] =0x00;
				fasong_232[3] =0xe1;
				fasong_232[4] =temp1/256;
				fasong_232[5] =temp1%256;
				fasong_232[6] =0x00;
				fasong_232[7] =0x00;
				fasong_232[8] =0x00;
				fasong_232[9] =0x01;				
				SENSOR_KAISHIFASONG();
						
							
				
				xianshimoshi =3;
			}
			else
			{
				xianshimoshi = 4;
			}
			break;
		case 3://校准	
			switch(jiaozhunbuzhou)
				{
					case 0:
						//确认校准值
						temp1 = shuruzu[0]*10000+ shuruzu[1]*1000+ shuruzu[2]*100+ shuruzu[3]*10+ shuruzu[4];	
						if(temp1<=JCXI_zuidaliangcheng)
						{
							fasong_232[0] =0x5a;
							fasong_232[1] =0xa5;
							fasong_232[2] =0x00;
							fasong_232[3] =0xF0;
							fasong_232[4] =temp1/256;
							fasong_232[5] =temp1%256;
							fasong_232[6] =0x00;
							fasong_232[7] =0x00;
							fasong_232[8] =0x00;
							fasong_232[9] =0x01;
							SENSOR_KAISHIFASONG();
							jiaozhunbuzhou=1;
						}
						else
						{
							xianshimoshi = 4;
						}
					break;
					case 1:	
						//空操作计算显示数值方法在传感器文件中
					break;	
					case 2:	
						//确认校准
						fasong_232[0] =0x5a;
						fasong_232[1] =0xa5;
						fasong_232[2] =0x00;
						fasong_232[3] =0xF2;
						fasong_232[4] =0x00;
						fasong_232[5] =0x00;
						fasong_232[6] =0x00;
						fasong_232[7] =0x00;
						fasong_232[8] =0x00;
						fasong_232[9] =0x01;
						SENSOR_KAISHIFASONG();
						jiaozhunbuzhou=0;
					break;	
					default:
					break;
				
				}
		break;
		case 4://清空系数表
			fasong_232[0] =0x5a;
			fasong_232[1] =0xa5;
			fasong_232[2] =0x00;
			fasong_232[3] =0xFF;
			fasong_232[4] =0x00;
			fasong_232[5] =0x00;
			fasong_232[6] =0x00;
			fasong_232[7] =0x00;
			fasong_232[8] =0x00;
			fasong_232[9] =0x01;
			SENSOR_KAISHIFASONG();
			xianshimoshi =3;	
		break;
		case 5://设置4-20ma 4
			dianliubuzhou++;
			switch(dianliubuzhou){
				case 1:
					          temp2 = JCXI_420ma4;
							  shuruzu[0] = (u8)(temp2/10000);
							  shuruzu[1] = (u8)((temp2 - shuruzu[0] *10000)/1000);
							  shuruzu[2] = (u8)((temp2 - shuruzu[0] *10000 - shuruzu[1]*1000)/100);
							  shuruzu[3] = (u8)((temp2 - shuruzu[0] *10000 - shuruzu[1]*1000 - shuruzu[2] *100)/10);
							  shuruzu[4] = (u8)((u32)(temp2)%10);	
							 DIANLIU_420MA_SET(temp2);
							  xianshimoshi = 2;
				break;
				case 2:
							temp2 = shuruzu[0]*10000+ shuruzu[1]*1000+ shuruzu[2]*100+ shuruzu[3]*10+ shuruzu[4];
							if(temp2<JCXI_420ma20)
								{
									JCXI_420ma4=temp2;
									FLASH_WRITE_PARAMETER();
									dianliubuzhou=0;
									xianshimoshi = 3;
								}
							else{
									xianshimoshi = 4;
							}
				break;
				default:
				break;
			}
		break;
		case 6://设置 4-20ma 20
		    dianliubuzhou++;
			switch(dianliubuzhou){
				case 1:
					          temp2 = JCXI_420ma20;
							  shuruzu[0] = (u8)(temp2/10000);
							  shuruzu[1] = (u8)((temp2 - shuruzu[0] *10000)/1000);
							  shuruzu[2] = (u8)((temp2 - shuruzu[0] *10000 - shuruzu[1]*1000)/100);
							  shuruzu[3] = (u8)((temp2 - shuruzu[0] *10000 - shuruzu[1]*1000 - shuruzu[2] *100)/10);
							  shuruzu[4] = (u8)((u32)(temp2)%10);
							  DIANLIU_420MA_SET(temp2);
							  xianshimoshi = 2;
				break;
				case 2:
							temp2 = shuruzu[0]*10000+ shuruzu[1]*1000+ shuruzu[2]*100+ shuruzu[3]*10+ shuruzu[4];
							if(temp2>JCXI_420ma4)
								{							
									JCXI_420ma20 = temp2;		
									FLASH_WRITE_PARAMETER();
									dianliubuzhou=0;
									xianshimoshi = 3;
								}
							else{
								xianshimoshi = 4;
							}
				break;
				default:
				break;
			}
		break;
		case 7://设置ID
			temp1 = shuruzu[0]*10000+ shuruzu[1]*1000+ shuruzu[2]*100+ shuruzu[3]*10+ shuruzu[4];
			if((temp1 < 250)&&(temp1> 0)){
				JCXI_485_ID = temp1;
				FLASH_WRITE_PARAMETER();	
				xianshimoshi = 3;
			}
			else{
				xianshimoshi = 4;
			}
		break;
		case 8://重启
			Delay_ms(2000);
			__set_FAULTMASK(1); 
			NVIC_SystemReset();
		break;
		case 9://测试继电器
			JIDIANQI_ALARML_ON();
			JIDIANQI_ALARMH_ON();
			Delay_ms(3000);
			JIDIANQI_ALARML_OFF();
			JIDIANQI_ALARMH_OFF();
			Delay_ms(3000);
			JIDIANQI_ALARML_ON();
			JIDIANQI_ALARMH_ON();
			Delay_ms(3000);
			JIDIANQI_ALARML_OFF();
			JIDIANQI_ALARMH_OFF();
			Delay_ms(3000);
			JIDIANQI_ALARML_ON();
			JIDIANQI_ALARMH_ON();
			Delay_ms(3000);
			JIDIANQI_ALARML_OFF();
			JIDIANQI_ALARMH_OFF();
			Delay_ms(3000);
			xianshimoshi =3;
		break;
		case 10://4-20MA测试
			  for(i=0;i<2;i++)
			  {
			   	DIANLIU_420MA_SET((JCXI_420ma4/2));
				Delay_ms(4000);
				DIANLIU_420MA_SET(JCXI_420ma4);
				Delay_ms(4000);
				DIANLIU_420MA_SET((JCXI_420ma4*2));
				Delay_ms(4000);
				DIANLIU_420MA_SET((JCXI_420ma4*3));
				Delay_ms(4000);
				DIANLIU_420MA_SET((JCXI_420ma4*4));
				Delay_ms(4000);
				DIANLIU_420MA_SET(JCXI_420ma20);
				Delay_ms(4000);
			  }			  
			  xianshimoshi =3;
		break;
		case 11://低报继电器瞬间输出
			temp1 = shuruzu[0]*10000+ shuruzu[1]*1000+ shuruzu[2]*100+ shuruzu[3]*10+ shuruzu[4];
			if((temp1 == 0)||(temp1 == 1)){
				if(temp1 == 0){
					JCXI_jidianqigenshuiDIBAO= 0;
				}
				else{
					JCXI_jidianqigenshuiDIBAO = 1;
				}		
				FLASH_WRITE_PARAMETER();
			       xianshimoshi = 3;// 正确		  	
			}	
			else{
				xianshimoshi = 4;// 失败			
			}			  
		break;
		case 12://高爆继电器瞬间输出
			temp1 = shuruzu[0]*10000+ shuruzu[1]*1000+ shuruzu[2]*100+ shuruzu[3]*10+ shuruzu[4];
			if((temp1 == 0)||(temp1 == 1)){
				if(temp1 == 0){
					JCXI_jidianqigenshuigaobao = 0;
				}
				else{
					JCXI_jidianqigenshuigaobao = 1;
				}			
				FLASH_WRITE_PARAMETER();
			       xianshimoshi = 3;// 正确		  	
			}	
			else{
				xianshimoshi = 4;// 失败			
			}				
			 
		break;
												
	}
}

//---------------------------------------------------------------------------





/********************************************************************
					SHEZHI.c的程序到此结束。
*********************************************************************/
