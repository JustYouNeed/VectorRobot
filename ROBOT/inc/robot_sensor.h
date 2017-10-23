# ifndef __ROBOT_SENSOR_H
# define __ROBOT_SENSOR_H

# include "bsp.h"

#	define ADC1_DR_ADDRESS    ((uint32_t)0x4001204C)

# define ROBOT_RANG_COUNT		9


/*    Photoelectric switch pin clock  */
# define ROBOT_PHO_RCC_ALL			(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF)

/*    Photoelectric switch pin definition    */
# define ROBOT_PHO_A_GPIO_PORT	GPIOF
# define ROBOT_PHO_A_GPIO_PIN		GPIO_Pin_14

# define ROBOT_PHO_B_GPIO_PORT	GPIOF
# define ROBOT_PHO_B_GPIO_PIN		GPIO_Pin_13

# define ROBOT_PHO_C_GPIO_PORT	GPIOE
# define ROBOT_PHO_C_GPIO_PIN		GPIO_Pin_5

# define ROBOT_PHO_D_GPIO_PORT	GPIOE
# define ROBOT_PHO_D_GPIO_PIN		GPIO_Pin_3

# define ROBOT_PHO_E_GPIO_PORT	GPIOF
# define ROBOT_PHO_E_GPIO_PIN		GPIO_Pin_12

# define ROBOT_PHO_H_GPIO_PORT	GPIOC
# define ROBOT_PHO_H_GPIO_PIN		GPIO_Pin_3

# define ROBOT_PHO_I_GPIO_PORT	GPIOC
# define ROBOT_PHO_I_GPIO_PIN		GPIO_Pin_1

# define ROBOT_PHO_J_GPIO_PORT	GPIOC
# define ROBOT_PHO_J_GPIO_PIN		GPIO_Pin_0

# define ROBOT_PHO_K_GPIO_PORT	GPIOE
# define ROBOT_PHO_K_GPIO_PIN		GPIO_Pin_6

# define ROBOT_PHO_L_GPIO_PORT	GPIOE
# define ROBOT_PHO_L_GPIO_PIN		GPIO_Pin_5

/*    Robot Ranging Module Pin Clock   */
# define ROBOT_RANG_RCC_ALL   	(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC)

/*    Robot Ranging Module ADC Clock   */
# define ROBOT_RANG_RCC_ADC			(RCC_APB2Periph_ADC1)

/*    Robot Ranging Module Pin Definitions  */
# define ROBOT_RANG_A_GPIO_PORT GPIOA
# define ROBOT_RANG_A_GPIO_PIN	GPIO_Pin_4

# define ROBOT_RANG_B_GPIO_PORT GPIOA
# define ROBOT_RANG_B_GPIO_PIN	GPIO_Pin_5

# define ROBOT_RANG_C_GPIO_PORT GPIOA
# define ROBOT_RANG_C_GPIO_PIN	GPIO_Pin_6

# define ROBOT_RANG_D_GPIO_PORT GPIOA
# define ROBOT_RANG_D_GPIO_PIN	GPIO_Pin_7

# define ROBOT_RANG_H_GPIO_PORT GPIOA
# define ROBOT_RANG_H_GPIO_PIN	GPIO_Pin_2

# define ROBOT_RANG_I_GPIO_PORT GPIOA
# define ROBOT_RANG_I_GPIO_PIN	GPIO_Pin_3

# define ROBOT_RANG_J_GPIO_PORT GPIOA
# define ROBOT_RANG_J_GPIO_PIN	GPIO_Pin_0

# define ROBOT_RANG_K_GPIO_PORT GPIOA
# define ROBOT_RANG_K_GPIO_PIN	GPIO_Pin_1

# define ROBOT_GRAY_GPIO_PORT		GPIOC
# define ROBOT_GRAY_GPIO_PIN		GPIO_Pin_4


/*   Robot photoelectric switch module ID  */
typedef enum{
	ROBOT_PHO_A = 0x00,
	ROBOT_PHO_B,
	ROBOT_PHO_C,
	ROBOT_PHO_D,
	ROBOT_PHO_E,
	
	ROBOT_PHO_H,
	ROBOT_PHO_I,
	ROBOT_PHO_J,
	ROBOT_PHO_K,
	ROBOT_PHO_L
}ROBOT_PHO_ID;


/*  Robot Infrared Ranging Module ID  */
typedef enum
{
	ROBOT_RANG_H = 2,
	ROBOT_RANG_I = 3,
	ROBOT_RANG_J = 0,
	ROBOT_RANG_K = 1,
	
	ROBOT_RANG_A = 4,
	ROBOT_RANG_B = 5,
	ROBOT_RANG_C = 6,
	ROBOT_RANG_D = 7,
	
	ROBOT_GRAY = 8
}ROBOT_RANG_ID;

void robot_SensorConfig(void);

void robot_PhotoelectricConfig(void);

void robot_PhoADC_CHConfig(void);
void robot_PhoADC_GPIOConfig(void);
void robot_PhoADC_DMAConfig(void);
void robot_PhoADC_TIMConfig(void);

void robot_RangingConfig(void);

extern uint16_t ADC1ConvValue[ROBOT_RANG_COUNT];
# endif

