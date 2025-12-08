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
// LRC计算函数（求和取反加1，符合工业常用标准）
static uint8_t calculate_lrc_correct(const uint8_t* data, uint32_t len) {
    uint16_t sum = 0; // 用16位避免求和溢出
    // 1. 所有待校验字节求和
    for (uint32_t i = 0; i < len; i++) {
        sum += data[i];
    }
    // 2. 取反 + 1（得到补码，即最终LRC值）
    uint8_t lrc_val = (uint8_t)(~sum + 1);
    return lrc_val;
}

// 辅助函数：将1个字节转换为2个ASCII字符（如0x3D → '3'（0x33）和 'D'（0x44））
static void byte_to_ascii(uint8_t byte, uint8_t* ascii_high, uint8_t* ascii_low) {
    // 高4位转换为ASCII
    uint8_t high_nibble = (byte >> 4) & 0x0F;
    *ascii_high = (high_nibble < 10) ? (high_nibble + '0') : (high_nibble - 10 + 'A');
    // 低4位转换为ASCII
    uint8_t low_nibble = byte & 0x0F;
    *ascii_low = (low_nibble < 10) ? (low_nibble + '0') : (low_nibble - 10 + 'A');
}
//extern uint8_t uart4_recv_flag;
//---------------------------------------------------------------------------
void Shezhi_DY(void){
u8 i;
u16 temp1;
u16 temp2;
	switch(caidanweizhi){
		case 1://低报警设置			
			temp1 = shuruzu[0]*10000+ shuruzu[1]*1000+ shuruzu[2]*100+ shuruzu[3]*10+ shuruzu[4];
			if((temp1>JCXI_zuixiaoliangcheng)&&(temp1<JCXI_zuidaliangcheng)&&(temp1<JCXI_gaobaojing))
			{
//++++++++++++++++++++++++++++++++++++++++++CHANGE+++++++++++++++++++++++++++++++++++++++++
				JCXI_dibaojing = temp1;
                FLASH_WRITE_PARAMETER();
//+++++++++++++++++++++++++++++++++++++++++CHANGE_END+++++++++++++++++++++++++++++++++++++++++				
				xianshimoshi =3;                  //显示模式：正确
			}
			else 
			{
				xianshimoshi = 4;                 //显示模式：错误
			}
		break;
		case 2://高报警设置
			temp1 = shuruzu[0]*10000+ shuruzu[1]*1000+ shuruzu[2]*100+ shuruzu[3]*10+ shuruzu[4];
			if((temp1>JCXI_zuixiaoliangcheng)&&(temp1<JCXI_zuidaliangcheng)&&(temp1>JCXI_dibaojing))
			{
//++++++++++++++++++++++++++++++++++++++++++CHANGE+++++++++++++++++++++++++++++++++++++++++
				JCXI_gaobaojing= temp1;
                FLASH_WRITE_PARAMETER();
//+++++++++++++++++++++++++++++++++++++++++CHANGE_END+++++++++++++++++++++++++++++++++++++++++
				xianshimoshi =3;                  //显示模式：正确
			}
			else
			{
				xianshimoshi = 4;                 //显示模式：错误
			}
			break;
		case 3://校准	
//			switch(jiaozhunbuzhou)
//				{
//					case 0:
						//确认校准值
						temp1 = shuruzu[0]*10000+ shuruzu[1]*1000+ shuruzu[2]*100+ shuruzu[3]*10+ shuruzu[4];
//++++++++++++++++++++++++++++++++++++++++++CHANGE+++++++++++++++++++++++++++++++++++++++++        
						if(temp1<=JCXI_zuidaliangcheng)
						{
                            if(temp1 == 0){
                                //55 31 47 30 30 30 30 30 09 34 32 0D 0A
                                fasong_232[0] =0x55;
                                fasong_232[1] =0x31;
                                fasong_232[2] =0x47;
                                fasong_232[3] =0x30;
                                fasong_232[4] =0x30;
                                fasong_232[5] =0x30;
                                fasong_232[6] =0x30;
                                fasong_232[7] =0x30;
                                fasong_232[8] =0x09;
                                fasong_232[9] =0x34;
                                fasong_232[10] = 0x33;
                                fasong_232[11] = 0x0D;
                                fasong_232[12] = 0x0A;
                                SENSOR_KAISHIFASONG();                                
//                                if((wanchengjieshou_232 == TRUE) && (uart4_recv_flag == 1)){
//                                    xianshimoshi =3;
//                                    uart4_recv_flag = 0;//重置接收数据类型
//                                }else{
//                                    xianshimoshi =4;
//                                }
                            }
                            else{
                                temp1 = (temp1 / 5) - 1;
                                //55 32 47 XX XX 30 30 30 09 YY YY 0D 0A
                                fasong_232[0] =0x55;
                                fasong_232[1] =0x32;
                                fasong_232[2] =0x47;
                                fasong_232[3] =(temp1 / 10) + '0';
                                fasong_232[4] =(temp1 % 10) + '0';
                                fasong_232[5] =0x30;
                                fasong_232[6] =0x30;
                                fasong_232[7] =0x30;
                                fasong_232[8] =0x09;
                                
                                // 计算LRC（校验09之前的8字节：索引0-7）
                                uint8_t lrc_val = calculate_lrc_correct(fasong_232, 8);
                                // 转换为2个ASCII字符（重点修正：如55 34 47 33 30 30 30 30的LRC计算）
                                byte_to_ascii(lrc_val, &fasong_232[9], &fasong_232[10]);
                                
                                fasong_232[11] = 0x0D;
                                fasong_232[12] = 0x0A;
                                
                                SENSOR_KAISHIFASONG();
                                Delay_ms(3000);
//                                if((wanchengjieshou_232 == TRUE) &&(uart4_recv_flag == 2)){
//                                    xianshimoshi =3;
//                                    uart4_recv_flag = 0;//重置接收数据类型
//                                }else{
//                                    xianshimoshi =4;
//                                }
                            }
						}
						else
						{
							xianshimoshi = 4;
						}
//+++++++++++++++++++++++++++++++++++++++++CHANGE_END+++++++++++++++++++++++++++++++++++++++++
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
