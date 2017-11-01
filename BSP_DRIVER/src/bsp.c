# include "bsp.h"


void bsp_Config(void)
{	
	bsp_TimerSoftConfig();
	
	
# if USE_KEY > 0u
	bsp_KeyConfig();
# endif
	
# if USE_LED > 0u
	bsp_LedConfig();		        //³õÊ¼»¯LED¶Ë¿Ú
# endif
	
# if USE_USART > 0u
	bsp_UsartConfig();
# endif
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
uint32_t bsp_GetTIMRCC(TIM_TypeDef *TIMx)
{
	uint32_t rcc = 0;
	
	if(TIMx == TIM1)	rcc = RCC_APB2Periph_TIM1;
	else if(TIMx == TIM2) rcc = RCC_APB1Periph_TIM2;
	else if(TIMx == TIM3) rcc = RCC_APB1Periph_TIM3;
	else if(TIMx == TIM4) rcc = RCC_APB1Periph_TIM4;
	else if(TIMx == TIM5) rcc = RCC_APB1Periph_TIM5;
	else if(TIMx == TIM6) rcc = RCC_APB1Periph_TIM6;
	else if(TIMx == TIM7) rcc = RCC_APB1Periph_TIM7;
	else if(TIMx == TIM8) rcc = RCC_APB2Periph_TIM8;
	else if(TIMx == TIM9) rcc = RCC_APB2Periph_TIM9;
	else if(TIMx == TIM10) rcc = RCC_APB2Periph_TIM10;
	else if(TIMx == TIM11) rcc = RCC_APB2Periph_TIM11;
	else if(TIMx == TIM12) rcc = RCC_APB1Periph_TIM12;
	else if(TIMx == TIM13) rcc = RCC_APB1Periph_TIM13;
	else if(TIMx == TIM14) rcc = RCC_APB1Periph_TIM14;
	
	return rcc;
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
uint32_t bsp_GetGPIORCC(GPIO_TypeDef* GPIOx)
{
	uint32_t rcc = 0;
	
# ifdef VECTOR_F1
	if(GPIOx == GPIOA) rcc = RCC_APB2Periph_GPIOA;
	else if(GPIOx == GPIOB) rcc = RCC_APB2Periph_GPIOB;
	else if(GPIOx == GPIOC) rcc = RCC_APB2Periph_GPIOC;
	else if(GPIOx == GPIOD) rcc = RCC_APB2Periph_GPIOD;
	else if(GPIOx == GPIOE) rcc = RCC_APB2Periph_GPIOE;
	else if(GPIOx == GPIOF) rcc = RCC_APB2Periph_GPIOF;
	else if(GPIOx == GPIOG) rcc = RCC_APB2Periph_GPIOG;
# elif defined VECTOR_F4
	if(GPIOx == GPIOA) rcc = RCC_AHB1Periph_GPIOA;
	else if(GPIOx == GPIOB) rcc = RCC_AHB1Periph_GPIOB;
	else if(GPIOx == GPIOC) rcc = RCC_AHB1Periph_GPIOC;
	else if(GPIOx == GPIOD) rcc = RCC_AHB1Periph_GPIOD;
	else if(GPIOx == GPIOE) rcc = RCC_AHB1Periph_GPIOE;
	else if(GPIOx == GPIOF) rcc = RCC_AHB1Periph_GPIOF;
	else if(GPIOx == GPIOH) rcc = RCC_AHB1Periph_GPIOH;
	else if(GPIOx == GPIOI) rcc = RCC_AHB1Periph_GPIOI;
	else if(GPIOx == GPIOG) rcc = RCC_AHB1Periph_GPIOG;
# endif
	return rcc;
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
# ifdef VECTOR_F4
uint8_t bsp_GetTIMPinAF(TIM_TypeDef *TIMx)
{
	uint8_t pinAF = 0;
	if(TIMx == TIM1)	pinAF = GPIO_AF_TIM1;
	else if(TIMx == TIM2) pinAF = GPIO_AF_TIM2;
	else if(TIMx == TIM3) pinAF = GPIO_AF_TIM3;
	else if(TIMx == TIM4) pinAF = GPIO_AF_TIM4;
	else if(TIMx == TIM5) pinAF = GPIO_AF_TIM5;
	else if(TIMx == TIM8) pinAF = GPIO_AF_TIM8;
	else if(TIMx == TIM9) pinAF = GPIO_AF_TIM9;
	else if(TIMx == TIM10) pinAF = GPIO_AF_TIM10;
	else if(TIMx == TIM11) pinAF = GPIO_AF_TIM11;
	else if(TIMx == TIM12) pinAF = GPIO_AF_TIM12;
	else if(TIMx == TIM13) pinAF = GPIO_AF_TIM13;
	else if(TIMx == TIM14) pinAF = GPIO_AF_TIM14;
	
	return pinAF;
}

uint8_t bsp_GetSPIPinAF(SPI_TypeDef* SPIx)
{
	uint8_t pinAF = 0;
	if(SPIx == SPI1)	pinAF = GPIO_AF_SPI1;
	else if(SPIx == SPI2) pinAF = GPIO_AF_SPI2;
	else if(SPIx == SPI3) pinAF = GPIO_AF_SPI3;
	else if(SPIx == SPI4) pinAF = GPIO_AF_SPI4;
	else if(SPIx == SPI5) pinAF = GPIO_AF_SPI5;
	else if(SPIx == SPI6) pinAF = GPIO_AF_SPI6;
}


# endif
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
uint16_t bsp_GetPinSource(uint16_t GPIO_Pin)
{
	uint16_t PinSource = 0;
	switch(GPIO_Pin)
	{
		case GPIO_Pin_0:PinSource = GPIO_PinSource0;break;
		case GPIO_Pin_1:PinSource = GPIO_PinSource1;break;
		case GPIO_Pin_2:PinSource = GPIO_PinSource2;break;
		case GPIO_Pin_3:PinSource = GPIO_PinSource3;break;
		case GPIO_Pin_4:PinSource = GPIO_PinSource4;break;
		case GPIO_Pin_5:PinSource = GPIO_PinSource5;break;
		case GPIO_Pin_6:PinSource = GPIO_PinSource6;break;
		case GPIO_Pin_7:PinSource = GPIO_PinSource7;break;
		case GPIO_Pin_8:PinSource = GPIO_PinSource8;break;
		case GPIO_Pin_9:PinSource = GPIO_PinSource9;break;
		case GPIO_Pin_10:PinSource = GPIO_PinSource10;break;
		case GPIO_Pin_11:PinSource = GPIO_PinSource11;break;
		case GPIO_Pin_12:PinSource = GPIO_PinSource12;break;
		case GPIO_Pin_13:PinSource = GPIO_PinSource13;break;
		case GPIO_Pin_14:PinSource = GPIO_PinSource14;break;
		case GPIO_Pin_15:	PinSource = GPIO_PinSource15;break;		
	}
	return PinSource;
}

void bsp_TIMClockCmd(TIM_TypeDef *TIMx)
{
	if(TIMx == TIM2 || TIMx == TIM3) RCC_APB1PeriphClockCmd(bsp_GetTIMRCC(TIMx), ENABLE);
# if defined (STM32F10X_HD)|| defined (STM32F10X_MD) || defined (VECTOR_F4)
	else if(TIMx == TIM4 || TIMx == TIM5 || TIMx == TIM6) RCC_APB1PeriphClockCmd(bsp_GetTIMRCC(TIMx), ENABLE);
# endif
	
# ifdef VECTOR_F4
	else if(TIMx == TIM12 || TIMx == TIM13 || TIMx == TIM14 ) RCC_APB1PeriphClockCmd(bsp_GetTIMRCC(TIMx), ENABLE);
	else if(TIMx == TIM8 || TIMx == TIM9 || TIMx == TIM10 || TIMx == TIM11)
		 RCC_APB2PeriphClockCmd(bsp_GetTIMRCC(TIMx), ENABLE);
# endif
		
}

void bsp_GPIOClcokCmd(GPIO_TypeDef* GPIOx)
{
# ifdef VECTOR_F1
	RCC_APB2PeriphClockCmd(bsp_GetGPIORCC(GPIOx), ENABLE);
# elif defined VECTOR_F4
	RCC_AHB1PeriphClockCmd(bsp_GetGPIORCC(GPIOx), ENABLE);
# endif
}

void bsp_ADCClockCmd(ADC_TypeDef* ADCx)
{
	
}


uint32_t bsp_GetSPIRCC(SPI_TypeDef *SPIx)
{
	uint32_t rcc = 0;
	if(SPIx == SPI1) rcc = RCC_APB2Periph_SPI1;
	else if(SPIx == SPI2) rcc = RCC_APB1Periph_SPI2;
	else if(SPIx == SPI3) rcc = RCC_APB1Periph_SPI3;
# ifdef VECTOR_F4
	else if(SPIx == SPI4) rcc = RCC_APB2Periph_SPI4;
	else if(SPIx == SPI5) rcc = RCC_APB2Periph_SPI5;
	else if(SPIx == SPI6) rcc = RCC_APB2Periph_SPI6;
# endif
	return rcc;
}


void bsp_SPIClockCmd(SPI_TypeDef* SPIx)
{
# ifdef VECTOR_F1
	if(SPIx == SPI1)
		RCC_APB2PeriphClockCmd(bsp_GetSPIRCC(SPIx), ENABLE);
	else if(SPIx == SPI2 || SPIx == SPI3)
		RCC_APB1PeriphClockCmd(bsp_GetSPIRCC(SPIx), ENABLE);
# elif defined VECTOR_F4
	if(SPIx == SPI1 || SPIx == SPI4 || SPIx == SPI5 || SPIx == SPI6)
		RCC_APB2PeriphClockCmd(bsp_GetSPIRCC(SPIx), ENABLE);
	else if(SPIx == SPI2 || SPIx == SPI3)
		RCC_APB1PeriphClockCmd(bsp_GetSPIRCC(SPIx), ENABLE);
# endif
}



