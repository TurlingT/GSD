#ifndef _JIARE_H_
#define _JIARE_H_
//-----------------------------

//---------------------------------------------------------------------------
//加热定义区域
#define JIARE_OUT_PIN  GPIO_Pin_10 //PB10
#define JIARE_CONTROLL_PORTB GPIOB

#define JIARE_OPEN()             GPIO_SetBits(JIARE_CONTROLL_PORTB, JIARE_OUT_PIN)
#define JIARE_CLOSE()           GPIO_ResetBits(JIARE_CONTROLL_PORTB, JIARE_OUT_PIN)

//-----------------------------------------------------------------------


//-----------------------------------------------------------------------
void JIARE_INIT(void);
void JIARE_DIAOYONG(void);
//-----------------------------------------------------------------------
#endif
