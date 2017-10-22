# ifndef __BSP_LED_H
# define __BSP_LED_H

# include "bsp.h"

# ifdef VECTOR_F1
	# define RCC_LED_ALL	(RCC_APB2Periph_GPIOE)

	# define LED0_GPIO_PORT		GPIOE
	# define LED0_GPIO_PIN		GPIO_Pin_2
	# define LED0_GPIO_MODE		GPIO_Mode_Out_PP

	# define LED1_GPIO_PORT		GPIOE
	# define LED1_GPIO_PIN		GPIO_Pin_3
	# define LED1_GPIO_MODE		GPIO_Mode_Out_PP
# else
	# define RCC_LED_ALL	(RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOG)

	# define LED0_GPIO_PORT		GPIOE
	# define LED0_GPIO_PIN		GPIO_Pin_8
	# define LED0_GPIO_MODE		GPIO_PuPd_UP

	# define LED1_GPIO_PORT		GPIOE
	# define LED1_GPIO_PIN		GPIO_Pin_7
	# define LED1_GPIO_MODE		GPIO_PuPd_UP
	
	# define LED2_GPIO_PORT		GPIOG
	# define LED2_GPIO_PIN		GPIO_Pin_1
	# define LED2_GPIO_MODE		GPIO_PuPd_UP
# endif

void bsp_LedConfig(void);
void bsp_LedGPIOConfig(void);
void bsp_LedToggle(uint8_t LedId);
void bsp_LedOn(uint8_t LedId);
void bsp_LedOff(uint8_t LedId);
uint8_t bsp_LedGetState(uint8_t LedId);
# endif

