# include "robot.h"


const uint32_t SampleFreqTable[][2] =
{
	{2800000,  1},     //2.8Msps
	{2000000,  1},     //2Msps
	{1000000,  1},     //1Msps
	{500000,   1},     //500Ksps
	{200000,   1},     //200Ksps
	
	{100000,   1},     //100Ksps
	{50000,    1},     //50Ksps
	{20000,    1},     //20Ksps
	{10000,    1},     //10Ksps
	{5000,     1},     //5Ksps
	
	{16800,      5},    //2Ksps
	{16800,     10},    //1Ksps
	{16800,     20},    //500sps
	{16800,     50},    //200sps
	{16800,     100},   //100sps
	
	{16800,     200},   //50sps
	{16800,     500},   //20sps
	{16800,     1000},  //10sps
	{16800,     2000},  //5sps
	{16800,     5000},  //2sps
	{16800,     10000}, //1sps
};

uint8_t SampleTime = 3;

/*
*********************************************************************************************************
*                                        robot_PhoADC_CHConfig  
*
* Description: 
*             
* Arguments : 
*
* Note(s)   : 
*********************************************************************************************************
*/
void robot_PhoADC_CHConfig(void)
{
	ADC_InitTypeDef	ADC_InitStructure;
	ADC_CommonInitTypeDef	ADC_CommonInitStructre;
	
	RCC_APB2PeriphClockCmd(ROBOT_RANG_RCC_ADC, ENABLE); 
	
	ADC_CommonInitStructre.ADC_Mode = ADC_Mode_Independent;//
	ADC_CommonInitStructre.ADC_Prescaler = ADC_Prescaler_Div4;  //
	ADC_CommonInitStructre.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//
	ADC_CommonInitStructre.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;//DMA
	ADC_CommonInit(&ADC_CommonInitStructre);
	
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1¸´Î»
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//¸´Î»½áÊø	 
 
	
	//ADC2???
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;  //????12?
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;   //????????
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;  //????????
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;  //?????
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;//??????,???????
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;//???1???1??
	ADC_InitStructure.ADC_NbrOfConversion = ROBOT_RANG_COUNT;//????14?
	ADC_Init(ADC1,&ADC_InitStructure);
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0, 1, ADC_SampleTime_480Cycles); //
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1, 2, ADC_SampleTime_480Cycles); //
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2, 3, ADC_SampleTime_480Cycles); //
	ADC_RegularChannelConfig(ADC1,ADC_Channel_3, 4, ADC_SampleTime_480Cycles); //
	ADC_RegularChannelConfig(ADC1,ADC_Channel_4, 5, ADC_SampleTime_480Cycles); //
	ADC_RegularChannelConfig(ADC1,ADC_Channel_5, 6, ADC_SampleTime_480Cycles); //
	ADC_RegularChannelConfig(ADC1,ADC_Channel_6, 7, ADC_SampleTime_480Cycles); //
	ADC_RegularChannelConfig(ADC1,ADC_Channel_7, 8, ADC_SampleTime_480Cycles); //
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_12, 9, ADC_SampleTime_3Cycles); //
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_8, 9, ADC_SampleTime_3Cycles); //
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_9, 10, ADC_SampleTime_3Cycles); //
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_10, 11, ADC_SampleTime_3Cycles); //
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_11, 12, ADC_SampleTime_3Cycles); //
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_12, 13, ADC_SampleTime_3Cycles); //
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_13, 14, ADC_SampleTime_3Cycles); //
	ADC_RegularChannelConfig(ADC1,ADC_Channel_14, 9, ADC_SampleTime_3Cycles); //
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_15, 16, ADC_SampleTime_3Cycles); //
	
	ADC_DMARequestAfterLastTransferCmd(ADC1,ENABLE);//
	ADC_DMACmd(ADC1,ENABLE);//??DMA
	ADC_Cmd(ADC1,ENABLE);	//??ADC1
}
/*
*********************************************************************************************************
*                                          
*
* Description: 
*             
* Arguments : 
*
* Note(s)   : 
*********************************************************************************************************
*/
void robot_PhoADC_GPIOConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOB ,ENABLE);	//
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	//
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	//

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
																GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
																
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
//	GPIO_InitStructure.GPIO_Pin = ROBOT_RANG_B_GPIO_PIN;
//	GPIO_Init(ROBOT_RANG_B_GPIO_PORT, &GPIO_InitStructure);	
//	
//	GPIO_InitStructure.GPIO_Pin = ROBOT_RANG_C_GPIO_PIN;
//	GPIO_Init(ROBOT_RANG_C_GPIO_PORT, &GPIO_InitStructure);	
//	
//	GPIO_InitStructure.GPIO_Pin = ROBOT_RANG_D_GPIO_PIN;
//	GPIO_Init(ROBOT_RANG_D_GPIO_PORT, &GPIO_InitStructure);	
//	
//	GPIO_InitStructure.GPIO_Pin = ROBOT_RANG_H_GPIO_PIN;
//	GPIO_Init(ROBOT_RANG_H_GPIO_PORT, &GPIO_InitStructure);	
//	
//	GPIO_InitStructure.GPIO_Pin = ROBOT_RANG_I_GPIO_PIN;
//	GPIO_Init(ROBOT_RANG_I_GPIO_PORT, &GPIO_InitStructure);	
//	
//	GPIO_InitStructure.GPIO_Pin = ROBOT_RANG_J_GPIO_PIN;
//	GPIO_Init(ROBOT_RANG_J_GPIO_PORT, &GPIO_InitStructure);	
//	
//	GPIO_InitStructure.GPIO_Pin = ROBOT_RANG_K_GPIO_PIN;
//	GPIO_Init(ROBOT_RANG_K_GPIO_PORT, &GPIO_InitStructure);	
	
//	GPIO_InitStructure.GPIO_Pin = ROBOT_GRAY_GPIO_PIN;
//	GPIO_Init(ROBOT_GRAY_GPIO_PORT, &GPIO_InitStructure);	
}

/*
*********************************************************************************************************
*                                       robot_PhoADC_DMAConfig   
*
* Description: 
*             
* Arguments : 
*
* Note(s)   : 
*********************************************************************************************************
*/
void robot_PhoADC_DMAConfig(void)
{
	DMA_InitTypeDef DMA_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructrue;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);
		
	DMA_InitStructure.DMA_Channel = DMA_Channel_0; //
	DMA_InitStructure.DMA_BufferSize = ROBOT_RANG_COUNT;   //
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;//
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)(uint16_t *)ADC1ConvValue; 
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_ADDRESS;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_Init(DMA2_Stream0,&DMA_InitStructure);
	DMA_Cmd(DMA2_Stream0,ENABLE);//
	
//	NVIC_InitStructrue.NVIC_IRQChannel = DMA2_Stream0_IRQn;
//	NVIC_InitStructrue.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_InitStructrue.NVIC_IRQChannelPreemptionPriority = 
//	NVIC_InitStructrue.NVIC_IRQChannelSubPriority = 
//	NVIC_Init(&NVIC_InitStructrue);
}
/*
*********************************************************************************************************
*                                          robot_PhoADC_TIMConfig
*
* Description: 
*             
* Arguments : 
*
* Note(s)   : 
*********************************************************************************************************
*/
void robot_PhoADC_TIMConfig(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	
	
	TIM_Cmd(TIM1, DISABLE);
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStructure);
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 168000000/SampleFreqTable[SampleTime][0] - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = SampleFreqTable[SampleTime][1]-1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0x0000;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);
		
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_Pulse = TIM_TimeBaseInitStructure.TIM_Period/3;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);
	
	
	TIM_Cmd(TIM1,ENABLE);

	TIM_CtrlPWMOutputs(TIM1, ENABLE); 
}


