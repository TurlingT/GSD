/*****************************************************************************
* filename
* KEY.c
*
*
* 描述
* 这个文件实现主程序相关功能函数.
*
*
* (c) 2007 Jiwen Su
*****************************************************************************/
#include "includes.h"

//-------------------------------------------------------------
void KEY_MAIN_FUNC(void){
	u16 temp2;
	switch(KEY_CHECK()){
		//按键检测
		case KEY_1:
			if(xianshimoshi == 1)
			{
			  if(caidanweizhi <= zuixiaocaidanshu)
				{
					caidanweizhi = zuidacaidanshu;
				}
			  else{
				  caidanweizhi--;
			
				}
			}
			if(xianshimoshi == 2)
			{
			   if(jiaozhunbuzhou ==2){}
			   else{
				   if(shuruzu[shuruweizhi] >= 9)
					{
						shuruzu[shuruweizhi] = 0;
					}
					else{
					  shuruzu[shuruweizhi]++;
					}
					if(dianliubuzhou ==1)
					{
						temp2 = shuruzu[0]*10000+ shuruzu[1]*1000+ shuruzu[2]*100+ shuruzu[3]*10+ shuruzu[4];	
						DIANLIU_420MA_SET(temp2);
					}
				}
			}
		break;
		case KEY_2:
			if(xianshimoshi == 1)
			{
			  if(caidanweizhi >= zuidacaidanshu)
				{
					caidanweizhi = zuixiaocaidanshu;
				}
			  else{
				  caidanweizhi++;
			
				}
			}	
			if(xianshimoshi == 2)
			{
			   if(jiaozhunbuzhou ==2){}
			   else{
				   if(shuruweizhi <= 0)
					{
						shuruweizhi = 4;
					}
				  else{
					  shuruweizhi--;
					}
				}
			}
		break;
		case KEY_3:
			switch(xianshimoshi)
				{
				   case 1:
					 if((caidanweizhi ==4)||(caidanweizhi ==5)||(caidanweizhi ==6)||(caidanweizhi ==8)||(caidanweizhi ==9)||(caidanweizhi ==10)){
						 Shezhi_DY();
					 }
					 else{
					 	if(caidanweizhi == 7){
							shuruzu[0] = 0;
							shuruzu[1] = 0;
							shuruzu[2] = JCXI_485_ID/100;
							shuruzu[3] = (JCXI_485_ID%100)/10;
							shuruzu[4] = JCXI_485_ID%10;
					 	}
						//设置ID
						xianshimoshi = 2;
					 }
					break;
				   case 2:
						Shezhi_DY();
					break;
					case 0:
						//设置按键
							xianshimoshi = 1;
							caidanweizhi = 1;
							shuruzu[0] = 0;
							shuruzu[1] = 0;
							shuruzu[2] = 0;
							shuruzu[3] = 0;
							shuruzu[4] = 0;
							shuruweizhi =4; 							
							jiaozhunbuzhou =0;
							dianliubuzhou =0;
					break;
				   default: 						
					break;
				   
				}		

		break;
		case KEY_4:
			xianshimoshi = 0;				
			dianliubuzhou =0;	
		    if(jiaozhunbuzhou >0)
		    {
		     	fasong_232[0] =0x5a;
				fasong_232[1] =0xa5;
				fasong_232[2] =0x00;
				fasong_232[3] =0xFe;
				fasong_232[4] =0x00;
				fasong_232[5] =0x00;
				fasong_232[6] =0x00;
				fasong_232[7] =0x00;
				fasong_232[8] =0x00;
				fasong_232[9] =0x01;
				fasongweizhi= 0;
				SENSOR_KAISHIFASONG();
		    }	
			jiaozhunbuzhou =0;
		break;
	}
}
//-------------------------------------------------------------

/********************************************************************
					KEY.c的程序到此结束。
*********************************************************************/
