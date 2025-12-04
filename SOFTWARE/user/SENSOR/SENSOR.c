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

extern int result;
extern uint8_t uart4_recv_flag;
float temp =0;
//---------------------------------------------------------------------------------------
void SENSOR_DIAOYONG(void){
    if(wanchengjieshou_232 == TRUE){
        
//++++++++++++++++++++++++++++++++++++++++++CHANGE+++++++++++++++++++++++++++++++++++++++++
        
        
        result = (int)(parse_uart4_data()*10000);
        temp = ((float)(result*20))/10000;
        if(temp<3.0){
            qitinongdu = 0;
        }
        else{
            qitinongdu = temp;
        }
        
        if(qitinongdu >= JCXI_dibaojing && qitinongdu < JCXI_gaobaojing){
            chuanganqizhuangtai = 2;
        }
        else if(qitinongdu >= JCXI_gaobaojing && qitinongdu <= JCXI_zuidaliangcheng){
            chuanganqizhuangtai =3;
        }
        else if(qitinongdu < JCXI_dibaojing)
        {
            chuanganqizhuangtai =0;
        }
//+++++++++++++++++++++++++++++++++++++++++CHANGE_END+++++++++++++++++++++++++++++++++++++++++
//        lcd_shuzhixianshi();	
		wanchengjieshou_232 = FALSE;
		chuanganqijieshou =0;
    }
	else{
		  if(chuanganqijieshou > 3000 ){
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
//++++++++++++++++++++++++++++++++++++++++++++CHANGE++++++++++++++++++++++++++++++++++++++++++++++++
    JCXI_qitileixing = 0x01;			//甲烷
    JCXI_qitidanwei= 0x03;				//%LEL           00无01ppm02vol
//    JCXI_gaobaojing= 0x32;              //高报警50
//    JCXI_dibaojing= 0x19;               //低报警25
    JCXI_zuidaliangcheng= 0x64;          //最大量程100
	JCXI_zuixiaoliangcheng= 0x00;        //最小量程0
//++++++++++++++++++++++++++++++++++++++++++++CHANGE_END+++++++++++++++++++++++++++++++++++++++++++++  
 
}

//*******************************************************************************





