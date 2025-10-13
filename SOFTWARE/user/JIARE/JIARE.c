#include "includes.h"


//以下是加热方法定义
//------------------------------------------------------------------------------
void JIARE_INIT(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	JIARE_CLOSE();
	/* work_led configration */	
	GPIO_InitStructure.GPIO_Pin = JIARE_OUT_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(JIARE_CONTROLL_PORTB, &GPIO_InitStructure);					 
	JIARE_CLOSE();
}
//-----------------------------------------------------------

//------------------------------------------------------------------
void JIARE_DUQUSHUJU(void){	
	u16 i;
	float wendu = 0;
	u16 *p;
	if(STM_ADC_NEW_DATA)
	{		
		p = (u16*)(&(STM_ADC_DATA[0]));
		if(STM_ADC_DATA_POS == FALSE){
			p += (ADC_VALUE_LENGTH>>1);
		}
		p+=3;
		wendu = *p++;
		for(i=1;i<(ADC_SAMPLE_NUM);i++){
			p+=3;
			wendu += *p++;
		}	
		STM_ADC_NEW_DATA =FALSE;

		//温度补偿
		wenducaijizhi = wendu/ADC_SAMPLE_NUM;
		//温度补偿结束
	}
}
//------------------------------------------------------------------

//-----------------------------------------------------------
void JIARE_DIAOYONG(void){
	JIARE_DUQUSHUJU();
	if(wenducaijizhi > (1880))
	{
		JIARE_OPEN();
	}
	else{
		JIARE_CLOSE();
	}
}
//-----------------------------------------------------------

