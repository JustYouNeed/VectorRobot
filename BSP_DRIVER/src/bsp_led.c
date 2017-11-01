# include "bsp.h"

/*  This variable indicates whether the LED is initialized   */
static uint8_t IsLedConfig = 0;

/*
*********************************************************************************************************
*                                          bsp_LedConfig
*
* Description: Initialize the LED
*             
* Arguments : None.
*
* Note(s)   : None.
*********************************************************************************************************
*/
void bsp_LedConfig(void)
{
	bsp_LedGPIOConfig();
	IsLedConfig = 1;
}

/*
*********************************************************************************************************
*                                        bsp_LedGPIOConfig  
*
* Description: Initialize the GPIO of LED
*             
* Arguments : None. 
*
* Note(s)   : None.
*********************************************************************************************************
*/
void bsp_LedGPIOConfig(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

# ifdef VECTOR_F1
	RCC_APB2PeriphClockCmd(RCC_LED_ALL, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = LED0_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = LED0_GPIO_MODE;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED0_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = LED1_GPIO_MODE;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);
# else
//	RCC_AHB1PeriphClockCmd(RCC_LED_ALL, ENABLE);
	bsp_GPIOClcokCmd(LED0_GPIO_PORT);
	bsp_GPIOClcokCmd(LED1_GPIO_PORT);
	bsp_GPIOClcokCmd(LED2_GPIO_PORT);
	
	
  GPIO_InitStructure.GPIO_Pin = LED0_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = LED0_GPIO_MODE;
  GPIO_Init(LED0_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;
  GPIO_InitStructure.GPIO_PuPd = LED1_GPIO_MODE;
  GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;
  GPIO_InitStructure.GPIO_PuPd = LED2_GPIO_MODE;
  GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);
	
	
	GPIO_SetBits(LED0_GPIO_PORT, LED0_GPIO_PIN);
	GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);
	GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO_PIN);
# endif
}


/*
*********************************************************************************************************
*                                        bsp_LedToggle  
*
* Description: Switch the status of the LED
*             
* Arguments : the ID of LED
*							0:LED0
*							1:LED1
*							2:LED0 and LED1
*
* Note(s)   : None.
*********************************************************************************************************
*/
void bsp_LedToggle(uint8_t LedId)
{
	if(IsLedConfig == 1)
	{
		switch(LedId)
		{
			case 0:LED0_GPIO_PORT->ODR ^= LED0_GPIO_PIN;break;
			case 1:LED1_GPIO_PORT->ODR ^= LED1_GPIO_PIN;break;
			case 2:LED2_GPIO_PORT->ODR ^= LED2_GPIO_PIN;break;
			default:LED0_GPIO_PORT->ODR ^= LED0_GPIO_PIN;
							LED1_GPIO_PORT->ODR ^= LED1_GPIO_PIN;
							LED2_GPIO_PORT->ODR ^= LED2_GPIO_PIN;break;
		}
	}
}
/*
*********************************************************************************************************
*                                       bsp_LedOn   
*
* Description: 
*             
* Arguments : 
*
* Note(s)   : 
*********************************************************************************************************
*/
void bsp_LedOn(uint8_t LedId)
{
	if(IsLedConfig == 1)
	{
		switch(LedId)
		{
		# ifdef VECTOR_F4
			case 0:LED0_GPIO_PORT->BSRRH = LED0_GPIO_PIN;break;
			case 1:LED1_GPIO_PORT->BSRRH = LED1_GPIO_PIN;break;
			case 2:LED0_GPIO_PORT->BSRRH = LED0_GPIO_PIN;
						 LED1_GPIO_PORT->BSRRH = LED1_GPIO_PIN;
						 break;
		# else
			case 0:LED0_GPIO_PORT->ODR &= ~LED0_GPIO_PIN;break;
			case 1:LED1_GPIO_PORT->ODR &= ~LED1_GPIO_PIN;break;
			case 2:LED0_GPIO_PORT->ODR &= ~LED0_GPIO_PIN;
						 LED1_GPIO_PORT->ODR &= ~LED1_GPIO_PIN;
						 break;
		# endif
			default:break;
		}
	}
}
/*
*********************************************************************************************************
*                                         bsp_LedOff 
*
* Description: 
*             
* Arguments : 
*
* Note(s)   : 
*********************************************************************************************************
*/
void bsp_LedOff(uint8_t LedId)
{
	if(IsLedConfig == 1)
	{
		switch(LedId)
		{
		# ifdef VECTOR_F4
			case 0:LED0_GPIO_PORT->BSRRL = LED0_GPIO_PIN;break;
			case 1:LED1_GPIO_PORT->BSRRL = LED1_GPIO_PIN;break;
			case 2:LED0_GPIO_PORT->BSRRL = LED0_GPIO_PIN;
						 LED1_GPIO_PORT->BSRRL = LED1_GPIO_PIN;
						 break;
		# else
			case 0:LED0_GPIO_PORT->ODR = LED0_GPIO_PIN;break;
			case 1:LED1_GPIO_PORT->ODR = LED1_GPIO_PIN;break;
			case 2:LED0_GPIO_PORT->ODR = LED0_GPIO_PIN;
						 LED1_GPIO_PORT->ODR = LED1_GPIO_PIN;
						 break;
		# endif
			default:break;
		}
	}
}
