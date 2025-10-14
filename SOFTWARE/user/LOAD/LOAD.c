/*****************************************************************************
* filename
* LOAD.c
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
#define TIM_50US_DIV 50*36UL  //36Mhz的时钟频率
//---------------------------------------------------------------------------
u32 FLASH_PARAMETER_GAS[FLASH_GAS_PARAMETER_POINT];// 4ma,20ma ,RELAY_ALARML_OR_ALARMH，485_ID

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void YOR_JC_IN(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	/* work_led configration */	
	GPIO_InitStructure.GPIO_Pin = JC_IN_PIN_PORTBS;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(JC_IN_CONTROLL_PORTB, &GPIO_InitStructure);			
	JC_IN_INPUT();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//以下是LED初始化
//---------------------------------------------------------------------------
void LED_INIT(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	/* work_led configration */	
	GPIO_InitStructure.GPIO_Pin = LED_PIN_PORTAS;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_CONTROLL_PORTA, &GPIO_InitStructure);					 
	GPIO_InitStructure.GPIO_Pin = LED_PIN_PORTCS;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_CONTROLL_PORTC, &GPIO_InitStructure);		
//	LED_WORK_ON();
}
//---------------------------------------------------------------------------
//以下是MODBUS初始化
//-----------------------------------------------------------
void ModbusTimersEnable( void ){
  	TIM_ClearFlag(TIM6, TIM_FLAG_Update); //清除溢出中断标志
  	TIM_SetCounter(TIM6,0x00);			//清零计数器值
  	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
  	TIM_Cmd(TIM6,ENABLE);
}
//-----------------------------------------------------------

//-----------------------------------------------------------
void ModbusTimersDisable( void ){
  	TIM_ITConfig(TIM6,TIM_IT_Update,DISABLE);
  	TIM_Cmd(TIM6,DISABLE);
}
//-----------------------------------------------------------

//------------------------------------------------------------------------------
void USART_NVIC_Configuration(void)
{
  	NVIC_InitTypeDef NVIC_InitStructure;
   	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
   	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void USART_InitConfig(USART_TypeDef * USARTx,u32 BaudRate)
{
  	USART_InitTypeDef USART_InitStructure; 
  	USART_InitStructure.USART_BaudRate = BaudRate;
  	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  	USART_InitStructure.USART_StopBits = USART_StopBits_1;
  	USART_InitStructure.USART_Parity = USART_Parity_No;
  	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  	/* Configure USARTx */
  	USART_Init(USARTx, &USART_InitStructure);
  	/* Enable the USARTx */
  	USART_Cmd(USARTx, ENABLE);
}
//------------------------------------------------------------------

//------------------------------------------------------------------
void USART1_Init(u32 BaudRate){
  	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_USART1  | RCC_APB2Periph_AFIO, ENABLE);  //enable the WDG
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  	GPIO_InitStructure.GPIO_Pin = MODBUS_DIO_PIN;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  	GPIO_Init(MODBUS_DIO_PORT, &GPIO_InitStructure); 
	MODBUS_READ_DATA(); //初始化为接收状态
  	/* Configure USART1 Tx (PA.09) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 	/* Configure USART1 Rx (PA.10) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	USART_InitConfig(USART1,BaudRate);
 	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
}
//-----------------------------------------------------------

//------------------------------------------------------------------
void UART4_Init(u32 BaudRate){
  	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_UART4, ENABLE);  //enable the WDG
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
 
  	/* Configure UART4 Rx (PC.11) as alternate function push-pull */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  	GPIO_Init(GPIOC, &GPIO_InitStructure);
 
  	/* Configure UART4 Tx (PC.10) as alternate function push-pull */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_Init(GPIOC, &GPIO_InitStructure);
	USART_InitConfig(UART4,BaudRate);
 	USART_ClearITPendingBit(UART4, USART_IT_RXNE);
	USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);
	USART_NVIC_Configuration();

	//传感器变量初始化
}
//-----------------------------------------------------------

//---------------------------------------------------------------------------
//以下是定时器初始化
//------------------------------------------------------------------------------
void TIM6_Init(void){
	//理论上采用APB1时钟为18Mhz，但是倍频了，实际频率为36Mhz
	//9600bps的3.5个字符的时间为(11*3.5/9600)*1000ms = 4010us超时,11bit包括起始位，数据位，停止位和校验位
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM6 , ENABLE);  //enable the WDG
  	TIM_TimeBaseStructure.TIM_Period = 80; // 80 = 220000*7/2*9600
  	TIM_TimeBaseStructure.TIM_Prescaler = TIM_50US_DIV;
  	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

  	/* Prescaler configuration */
  	TIM_PrescalerConfig(TIM6, TIM_50US_DIV, TIM_PSCReloadMode_Immediate);

  	/* TIM IT enable */
  	TIM_ClearFlag(TIM6, TIM_FLAG_Update); //清除溢出中断标志
  	TIM_ITConfig(TIM6, TIM_IT_Update, DISABLE);
}
//-----------------------------------------------------------

//------------------------------------------------------------------------------
void TIM2_Init(void){
	//理论上采用APB1时钟为18Mhz，100ms 中断一次
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM2 , ENABLE);  //enable the WDG
  	TIM_TimeBaseStructure.TIM_Period = 599;
  	TIM_TimeBaseStructure.TIM_Prescaler = 5999;
  	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  	/* Prescaler configuration */
  	TIM_PrescalerConfig(TIM2, 6000, TIM_PSCReloadMode_Immediate);

  	/* TIM IT enable */
  	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
}
//-----------------------------------------------------------

//-----------------------------------------------------------
void TIMER_NVIC_Configuration(void)
{
 	 NVIC_InitTypeDef NVIC_InitStructure;

   	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
   	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
 }
//-----------------------------------------------------------

//------------------------------------------------------------------------------
void TIMER_Init(void){
	TIM2_Init();
	TIM6_Init();
	TIMER_NVIC_Configuration();
}
//-----------------------------------------------------------

//---------------------------------------------------------------------------
//以下是定时器初始化
void KEY_INPUT_GPIO_Init(void){
// GPIO 初始化函数
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_KEY_INPUT_PORTA_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIO_KEY_INPUT_PORTA , &GPIO_InitStructure);					 
}
//------------------------------------------------------------------

//------------------------------------------------------------------
u8 KEY_CHECK(void){
	u8 key_value =0;
	u8 key_return = 0;
	u8 key_last = 0;
	u8 i;
	key_value = GPIO_KEY_INPUT1() | GPIO_KEY_INPUT3();
	key_value = ~key_value;
	key_value = key_value & 0x03;
	switch(key_value){
		case 0x01:
			key_return = KEY_2;
		break;
		case 0x02:
			key_return = KEY_1;
		break;
		default:
			return 0;
	}
	key_last = key_value;
	Delay_ms(20);
	key_value = 0;
	key_value = GPIO_KEY_INPUT1()| GPIO_KEY_INPUT3();
	key_value = ~key_value;
	key_value = key_value & 0x03;
	if(key_value != key_last){
		return 0;
	}
	i = 0;
	while((key_value != 0x00)&&(i<GPIO_KEY_TIMEOUT)){
		key_value = 0;
		key_value = GPIO_KEY_INPUT1() | GPIO_KEY_INPUT3();
		key_value = ~key_value;
		key_value = key_value & 0x03;
		Delay_ms(100);
		i++;
	}
	if( i == GPIO_KEY_TIMEOUT){
		if(key_return == KEY_1){
			key_return = KEY_3;
		}//校准
		else if(key_return == KEY_2){
			key_return = KEY_4;
		}
	}
	while((key_value != 0x00)){
		key_value = 0;
		key_value = GPIO_KEY_INPUT1() | GPIO_KEY_INPUT3();
		key_value = ~key_value;
		key_value = key_value & 0x03;
	}
	return  key_return;
}
//------------------------------------------------------------------

//---------------------------------------------------------------------------
//以下是lcd初始化
//---------------------------------------------------------------------------
void LCD_Init_GPIO(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* work_led configration */	
	GPIO_InitStructure.GPIO_Pin = LCD_CONTROLL_PINBS;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LCD_CONTROLL_PORTB,&GPIO_InitStructure);					 
   	/* 使能一些pin */
	GPIO_InitStructure.GPIO_Pin = LCD_CONTROLL_PINAS;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LCD_CONTROLL_PORTA,&GPIO_InitStructure);					 
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//!!!!!!!!!写N位数据!!!!!!!!
void LCD_HT1621_wr_nbit(u8  N,u8  dat){
  	u8 i;
  	for(i=0;i<N;i++){
		CLR_WR();
		if(dat&0x80)	
		{
			SET_DATA();
		}
		else
		{
			CLR_DATA(); 
		}	
		SET_WR();
		dat<<=1;
	}  	
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//!!!!!!!!!写9位数据!!!!!!!!!!
void LCD_HT1621_wr_9bit(u8 first_bit,u8  dat){ 	
  	if(first_bit==1){
    		CLR_WR();	//wr=0;
    		SET_DATA();	//lcd_data=1;
    		SET_WR();	//wr=1;
  	}
  	else	{
    		CLR_WR();	//wr=0;
    		CLR_DATA();	//lcd_data=0;
    		SET_WR();	//wr=1;	
  	}
  	LCD_HT1621_wr_nbit(8,dat);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//!!!!!!!满屏!!!!!!!!!!!!!
void LCD_HT1621_full(u8 dat){
  	u8 i;
  	CLR_CS();	//cs=0;
  	//delay(DELAY_TIME);
  	LCD_HT1621_wr_nbit(3,0xa0);//WRITE DATA 101
  	LCD_HT1621_wr_nbit(6,0x00);//SEG地址,高六位有效   101模式下SEG自动加一
  	for(i=0;i<32;i++)
  	{
    		LCD_HT1621_wr_nbit(4,dat);//COM地址，高四位有效，ACC.7-ACC.4对应D0-D3
  	}
  	SET_CS();	//cs=1;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void LCD_HT1621_INIT (void){ 
  	CLR_CS();	//cs=0;
  	//delay(DELAY_TIME);
  	LCD_HT1621_wr_nbit(3,0x80);   //WRITE INSTU 100
  	LCD_HT1621_wr_9bit(0,0x03);   //INI1 SYS ON
  	LCD_HT1621_wr_9bit(0,0x07);   //INI2 LCD ON
  	LCD_HT1621_wr_9bit(0,0x37);   //INI3 SET RC 256K OSC
  	LCD_HT1621_wr_9bit(0,0x57);   //INI4 SET BIAS 1/3
  	LCD_HT1621_wr_9bit(0,0x13);   //tone
  	LCD_HT1621_wr_9bit(0,0xc0);   //tone
  	SET_CS();	//cs=1;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//!!!!!!!!!写数据!!!!!!!!
void LCD_wr_dat(u8 add1, u8 add2,u8 dat1){
//显示数据，addr为显示数据的地址，dat为显示数据对应的关系如下:
//addr: 上排1、2、3、4下排5、6、7、8、9
//dat:null、0、1、2、3、4、5、6、7、8、9、A、b、C、d、E、F、H、o、L、S
  	CLR_CS();	//cs=0;
  	LCD_HT1621_wr_nbit(3,0xa0);//WRITE DATA 101
  	LCD_HT1621_wr_nbit(6,add1);//SEG地址,高六位有效   101模式下SEG自动加一
  	LCD_HT1621_wr_nbit(4,dat1); 
  	SET_CS();	//cs=1;
  	
  	CLR_CS();	//cs=0;
  	LCD_HT1621_wr_nbit(3,0xa0);//WRITE DATA 101
  	LCD_HT1621_wr_nbit(6,add2);//SEG地址,高六位有效   101模式下SEG自动加一
  	LCD_HT1621_wr_nbit(4,(dat1<<4)); 
  	SET_CS();	//cs=1;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//!!!!!!!!!写数据!!!!!!!!
void LCD_wr_BIT4(u8 add1,u8 dat1){
//显示数据，addr为显示数据的地址，dat为显示数据对应的关系如下:
//addr: 上排1、2、3、4下排5、6、7、8、9
//dat:null、0、1、2、3、4、5、6、7、8、9、A、b、C、d、E、F、H、o、L、S
  	CLR_CS();	//cs=0;
  	LCD_HT1621_wr_nbit(3,0xa0);//WRITE DATA 101
  	LCD_HT1621_wr_nbit(6,add1);//SEG地址,高六位有效   101模式下SEG自动加一
  	LCD_HT1621_wr_nbit(4,dat1); 
  	SET_CS();	//cs=1;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void LCD_DRIVER_Init(void)
{
	LCD_Init_GPIO();
	//管脚初始化
	Delay_ms(300);
	LCD_HT1621_INIT();
	//命令初始化
	LCD_HT1621_full(0x00);
	//清屏
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//以下是DAC初始化
//DAC通道1输出初始化
void Dac1_Init(void){
	 GPIO_InitTypeDef GPIO_InitStructure;
	 DAC_InitTypeDef DAC_InitType;
	 DAC_StructInit(&DAC_InitType);
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );	  //使能DAC通道时钟
	 
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				   // 端口配置
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;			//模拟输入
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
	 GPIO_SetBits(GPIOA,GPIO_Pin_4)    ;//PA.4 输出高
	 
	 DAC_InitType.DAC_Trigger=DAC_Trigger_None;    //不使用触发功能 TEN1=0
	 DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//不使用波形发生
	 DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Enable;    //DAC1输出缓存关闭 BOFF1=1
	 DAC_Init(DAC_Channel_1,&DAC_InitType); 	//初始化DAC通道1
	 
	 DAC_Cmd(DAC_Channel_1, ENABLE); //使能DAC1
	 DAC_SetChannel1Data(DAC_Align_12b_R, JCXI_420ma4); //12位右对齐数据格式设置DAC值
}
//---------------------------------------------------------------------------
 
//---------------------------------------------------------------------------
void DAC_stm_Init(void){
	Dac1_Init();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void DIANLIU_420MA_SET(u16 vol){
    DAC_SetChannel1Data(DAC_Align_12b_R,vol);//12位右对齐数据格式设置DAC值
} 
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//以下是ADC初始化
//------------------------------------------------------------------
void ADC_NVIC_Configuration(void)
{
  	NVIC_InitTypeDef NVIC_InitStructure;
   	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 10;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
 }
//-----------------------------------------------------------

//------------------------------------------------------------------
void ADC1_Init(void){
	ADC_InitTypeDef ADC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	//ADC input init PA0\1\2\3\4\5\6\7
	GPIO_InitStructure.GPIO_Pin = ADC_PORTC_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = ADC_PORTA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

 	/* DMA1 channel1 configuration ----------------------------------------------*/
  	DMA_DeInit(DMA1_Channel1);
  	DMA_InitStructure.DMA_PeripheralBaseAddr = DR_ADDRESS;//外设地址
  	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32)(&(STM_ADC_DATA[0]));//内存地址
  	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  	DMA_InitStructure.DMA_BufferSize = ADC_VALUE_LENGTH; // 4ms 采样一个数据
  	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  
  	/* Enable DMA1 channel1 */
  	DMA_Cmd(DMA1_Channel1, ENABLE);
 	/* ADC1 configuration ------------------------------------------------------*/
	//APB2 = 4.5Mhz
	ADC_TempSensorVrefintCmd(ENABLE);
	//打开温度传感器
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); //APB2 / 8 = 562.5khz
  	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	//独立工作模式
  	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	//扫描方式
  	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	//连续转换
  	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//外部触发禁止
  	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//数据右对齐
  	ADC_InitStructure.ADC_NbrOfChannel = ADC_USED_CHANNEL;//用于转换的通道数
  	ADC_Init(ADC1,&ADC_InitStructure);

  	/* ADC1 regular channels configuration [规则模式通道配置]*/ 
  	ADC_RegularChannelConfig(ADC1, ADC_Channel_10 , 1, ADC_SampleTime_239Cycles5); // 448us
  	ADC_RegularChannelConfig(ADC1, ADC_Channel_3 , 2, ADC_SampleTime_239Cycles5);// 448us
  	ADC_RegularChannelConfig(ADC1, ADC_Channel_Vrefint, 3, ADC_SampleTime_239Cycles5);// 448us
  	ADC_RegularChannelConfig(ADC1, ADC_Channel_TempSensor, 4, ADC_SampleTime_239Cycles5);// 448us
	// 3.58ms
  	/* Enable ADC1 DMA [使能ADC1 DMA]*/
  	ADC_DMACmd(ADC1, ENABLE);
  
  	/* Enable ADC1 [使能ADC1]*/
  	ADC_Cmd(ADC1, ENABLE); 


  	/* Enable ADC1 reset calibaration register */   
  	ADC_ResetCalibration(ADC1);
  	/* Check the end of ADC1 reset calibration register */
  	while(ADC_GetResetCalibrationStatus(ADC1));


 	 /* Start ADC1 calibaration */
  	ADC_StartCalibration(ADC1);
  	/* Check the end of ADC1 calibration */
  	while(ADC_GetCalibrationStatus(ADC1));
  
  	ADC_Cmd(ADC1, DISABLE); 
	ADC_NVIC_Configuration();
}
//------------------------------------------------------------------


//------------------------------------------------------------------
void ADC_START_SAMPLE(void){
  	ADC_Cmd(ADC1, ENABLE); 
	DMA_ITConfig(DMA1_Channel1, DMA1_IT_TC1|DMA1_IT_HT1, ENABLE);
	DMA_Cmd(DMA1_Channel1, ENABLE); //*/
	ADC_SoftwareStartConvCmd(ADC1, ENABLE); //enable the convert
	Delay_ms(2000);
}
//------------------------------------------------------------------

//------------------------------------------------------------------
//以下是继电器初始化
//---------------------------------------------------------------------------
void JIDIANQI_INIT(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	/* work_led configration */	
	JIDIANQI_ALARML_OFF();
	JIDIANQI_ALARMH_OFF();
	GPIO_InitStructure.GPIO_Pin = JIDIANQI_PIN_PORTCS;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(JIDIANQI_CONTROLL_PORTC, &GPIO_InitStructure);	
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//以下是FLASH部分
//------------------------------------------------------------
u32  Flash_Read_WORD(u32 flash_address){
	return *(u32 *)flash_address;
}
//------------------------------------------------------------------

//------------------------------------------------------------------
void FLASH_PARAMETER_TOREAD(void){
	JCXI_485_ID = FLASH_PARAMETER_GAS[0]; //485使用ID号码	
	JCXI_420ma4 = FLASH_PARAMETER_GAS[1];//4ma值
	JCXI_420ma20 = FLASH_PARAMETER_GAS[2];//20ma值
	JCXI_jidianqigenshuiDIBAO = FLASH_PARAMETER_GAS[3];//低报继电器瞬间输出0，长输出1
	JCXI_jidianqigenshuigaobao = FLASH_PARAMETER_GAS[4];//低报继电器瞬间输出0，长输出1
}
//------------------------------------------------------------------

//------------------------------------------------------------------
void FLASH_PARAMETER_TOWRITE(void){
	// 将需要保存的信息收集
		FLASH_PARAMETER_GAS[0] = JCXI_485_ID; //485使用ID号码	
		FLASH_PARAMETER_GAS[1] = JCXI_420ma4;//4ma值
		FLASH_PARAMETER_GAS[2] = JCXI_420ma20;//20ma值
		FLASH_PARAMETER_GAS[3] = JCXI_jidianqigenshuiDIBAO;//低报继电器瞬间输出0，长输出1
		FLASH_PARAMETER_GAS[4] = JCXI_jidianqigenshuigaobao;//低报继电器瞬间输出0，长输出1
}
//------------------------------------------------------------------

//------------------------------------------------------------------
void FLASH_CLEAR_GAS_PARAMETER(void){
		JCXI_485_ID = 0; //485使用ID号码	
		JCXI_420ma4 = 490;//4ma值
		JCXI_420ma20 = 2500;//20ma值
		JCXI_jidianqigenshuiDIBAO = 1;//低报继电器瞬间输出0，长输出1
		JCXI_jidianqigenshuigaobao = 1;//低报继电器瞬间输出0，长输出1
}
//------------------------------------------------------------------

//------------------------------------------------------------
void  Flash_WRITE_GAS(u32 flash_address,u32 *addr){
	FLASH_Status Status_temp;
	uint8 i;
	FLASH_Unlock();	//FLASH?a??
    	/* Clear All pending flags */
    	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);//??±ê????
	Status_temp = FLASH_ErasePage(flash_address); 
	while(Status_temp != FLASH_COMPLETE) {
		Status_temp = FLASH_WaitForLastOperation(1000);
	}
	for(i = 0;i<(FLASH_GAS_PARAMETER_POINT);i++){
		Status_temp = FLASH_ProgramWord(flash_address, (*addr));
		while(Status_temp != FLASH_COMPLETE) {
			Status_temp = FLASH_WaitForLastOperation(1000);
		}
		flash_address = flash_address + 4;
		addr++;
	}
	FLASH_Lock();
}
//------------------------------------------------------------------

//------------------------------------------------------------------
void FLASH_WRITE_PARAMETER(void){
	u32 *p_addr = (u32 *)(FLASH_PARAMETER_GAS);
	FLASH_PARAMETER_TOWRITE();
	__set_FAULTMASK(1); 
	Flash_WRITE_GAS(FLASH_SENSOR_PARAMETRER,p_addr);
	__set_FAULTMASK(0); 
}
//------------------------------------------------------------------

//------------------------------------------------------------
void  Flash_Read_GAS(u32 flash_address,u32 *addr){
	uint8 i;
	u32 data;
	u32 *p;
	for(i=0;i<((FLASH_GAS_PARAMETER_POINT));i++){
		data = Flash_Read_WORD(flash_address+ (i<<2));
		if(data == 0xffffffff){
			FLASH_CLEAR_GAS_PARAMETER();
			FLASH_WRITE_PARAMETER();
			return;
		}
		p = (u32 *)(&data);
		*addr= *p;
		addr++;
	}
}
//------------------------------------------------------------------

//------------------------------------------------------------------
void FLASH_READ_PARAMETER(void){
	u32 *p_addr = (u32 *)(FLASH_PARAMETER_GAS);
 	Flash_Read_GAS(FLASH_SENSOR_PARAMETRER,p_addr);

	FLASH_PARAMETER_TOREAD();
}
//------------------------------------------------------------------

//---------------------------------------------------------------------------
void Load_Init(void){
	TIMER_Init();
	FLASH_READ_PARAMETER();
	Delay_ms(1000);
	DAC_stm_Init();
	YOR_JC_IN();
	LED_INIT();
	KEY_INPUT_GPIO_Init();
	LCD_DRIVER_Init();
	ADC1_Init();
	ADC_START_SAMPLE();
	JIDIANQI_INIT();
	USART1_Init(9600);
	UART4_Init(115200);

	JIARE_INIT();
}
//---------------------------------------------------------------------------

/********************************************************************
					LOAD.c的程序到此结束。
*********************************************************************/
