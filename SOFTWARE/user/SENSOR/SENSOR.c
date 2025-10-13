#include "includes.h"

/*******************************************************************************


*******************************************************************************/

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configures the different GPIO ports.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

//---------------------------------------------------------------------------------------
void SENSOR_KAISHIFASONG(void){
	//将需要发送的数据填写好，调用这个方法进行发送
	fasongweizhi= 0;
	USART_ClearITPendingBit(UART4, USART_IT_TXE);
	USART_ClearFlag(UART4, USART_FLAG_TXE);
	USART_ITConfig(UART4, USART_IT_TXE,ENABLE);
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
void SENSOR_DIAOYONG(void){
    if(wanchengjieshou_232){
		switch(jieshou_232[3]){
						case 0xA0:
							//接收浓度
							chuanganqizhuangtai = 0;
							qitinongdu = *((float*)(&(jieshou_232[4])));
							break;
						case 0xA1:
							//接收浓度
							chuanganqizhuangtai = 2;
							qitinongdu = *((float*)(&(jieshou_232[4])));
							break;
						case 0xA2:
						//接收浓度
							chuanganqizhuangtai = 3;
							qitinongdu = *((float*)(&(jieshou_232[4])));
							break;
						case 0xA3:
						//接收浓度
							chuanganqizhuangtai = 1;
							qitinongdu = 100;
							break;
						case 0xC0://气体类型
							JCXI_qitileixing =(jieshou_232[4]);
							jcxibuzhou = 5;
							break;	
						case 0xC1://气体单位
							JCXI_qitidanwei=(jieshou_232[4]);
							jcxibuzhou = 6;
							break;
						case 0xC2://高报警
							JCXI_gaobaojing=(jieshou_232[4]<<8)+(jieshou_232[5]);
							jcxibuzhou = 3;
							break;
						case 0xC3://低报警
							JCXI_dibaojing=(jieshou_232[4]<<8)+(jieshou_232[5]);
							jcxibuzhou = 4;
							break;
						case 0xC4://最大量程
							JCXI_zuidaliangcheng=(jieshou_232[4]<<8)+(jieshou_232[5]);
							jcxibuzhou = 1;
							break;
					    case 0xC5://最小量程
							JCXI_zuixiaoliangcheng=(jieshou_232[4]<<8)+(jieshou_232[5]);
							jcxibuzhou = 2;
							break;
						case 0xe1://高报警
							 xianshimoshi =3;
							break;
						case 0xe2://低报警
							 xianshimoshi =3;
							break;
						case 0xFF://清空系数表
							 xianshimoshi =3;							
							break;
						case 0xAA://读取温度							 							
							break;	
						case 0xF0://校准接收	
						      jiaozhunbuzhou = 1;
							break;
						case 0xF3://校准接收
							  jiaozhunxianshi= (jieshou_232[7]<<24)+(jieshou_232[6]<<16)+(jieshou_232[5]<<8)+(jieshou_232[4]);
							  shuruzu[0] = (u8)(jiaozhunxianshi/10000);
							  shuruzu[1] = (u8)((jiaozhunxianshi - shuruzu[0] *10000)/1000);
							  shuruzu[2] = (u8)((jiaozhunxianshi - shuruzu[0] *10000 - shuruzu[1]*1000)/100);
							  shuruzu[3] = (u8)((jiaozhunxianshi - shuruzu[0] *10000 - shuruzu[1]*1000 - shuruzu[2] *100)/10);
							  shuruzu[4] = (u8)((u32)(jiaozhunxianshi)%10);							  
							jiaozhunbuzhou = 2;
							break;
						case 0xF2://确认校准
								xianshimoshi =3;	
							break;
						case 0xFe://确认校准
								xianshimoshi =0;	
							break;

							
						default :
							
						return;
				}	
			wanchengjieshou_232 = FALSE;
			chuanganqijieshou =0;
    	}
	else{
		  if(chuanganqijieshou > 10000 ){
				chuanganqizhuangtai = 1;				
		  	}else
		  		{
		  		chuanganqijieshou++;
		  		}
						
		}
	
}
//---------------------------------------------------------------------------------------


//*******************************************************************************
void sensor_chushihuachuanganqi(void){
  	switch(jcxibuzhou){
					case 0:
						fasong_232[0] =0x5a;
						fasong_232[1] =0xa5;
						fasong_232[2] =0x00;
						fasong_232[3] =0xc4;
						fasong_232[4] =0x00;
						fasong_232[5] =0x00;
						fasong_232[6] =0x00;
						fasong_232[7] =0x00;
						fasong_232[8] =0x00;
						fasong_232[9] =0x01;
						fasongweizhi= 0;
						SENSOR_KAISHIFASONG();

						break;
					case 1:
						fasong_232[0] =0x5a;
						fasong_232[1] =0xa5;
						fasong_232[2] =0x00;
						fasong_232[3] =0xc5;
						fasong_232[4] =0x00;
						fasong_232[5] =0x00;
						fasong_232[6] =0x00;
						fasong_232[7] =0x00;
						fasong_232[8] =0x00;
						fasong_232[9] =0x01;
						fasongweizhi= 0;
						SENSOR_KAISHIFASONG();

						break;
					case 2:
						fasong_232[0] =0x5a;
						fasong_232[1] =0xa5;
						fasong_232[2] =0x00;
						fasong_232[3] =0xc2;
						fasong_232[4] =0x00;
						fasong_232[5] =0x00;
						fasong_232[6] =0x00;
						fasong_232[7] =0x00;
						fasong_232[8] =0x00;
						fasong_232[9] =0x01;
						fasongweizhi= 0;
						SENSOR_KAISHIFASONG();

						break;
					case 3:
						fasong_232[0] =0x5a;
						fasong_232[1] =0xa5;
						fasong_232[2] =0x00;
						fasong_232[3] =0xc3;
						fasong_232[4] =0x00;
						fasong_232[5] =0x00;
						fasong_232[6] =0x00;
						fasong_232[7] =0x00;
						fasong_232[8] =0x00;
						fasong_232[9] =0x01;
						fasongweizhi= 0;
						SENSOR_KAISHIFASONG();

						break;	
					case 4:
						fasong_232[0] =0x5a;
						fasong_232[1] =0xa5;
						fasong_232[2] =0x00;
						fasong_232[3] =0xc0;
						fasong_232[4] =0x00;
						fasong_232[5] =0x00;
						fasong_232[6] =0x00;
						fasong_232[7] =0x00;
						fasong_232[8] =0x00;
						fasong_232[9] =0x01;						
						fasongweizhi= 0;
						SENSOR_KAISHIFASONG();

						break;
					case 5:
						fasong_232[0] =0x5a;
						fasong_232[1] =0xa5;
						fasong_232[2] =0x00;
						fasong_232[3] =0xc1;
						fasong_232[4] =0x00;
						fasong_232[5] =0x00;
						fasong_232[6] =0x00;
						fasong_232[7] =0x00;
						fasong_232[8] =0x00;
						fasong_232[9] =0x01;
						fasongweizhi= 0;
						SENSOR_KAISHIFASONG();

						break;
					case 6:
						fasongweizhi= 6;
						break;
				  	default :
					return;
	}
}

//*******************************************************************************





