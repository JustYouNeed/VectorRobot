# ifndef __BSP_KEY_H
# define __BSP_KEY_H


# include "bsp.h"



# ifdef	VECTOR_F1
	# define RCC_KEY_ALL	(RCC_APB2Periph_GPIOE)
	
	# define KEY_UP_PORT	GPIOE
	# define KEY_UP_PIN		GPIO_Pin_4
	
	# define KEY_OK_PORT	GPIOE
	# define KEY_OK_PIN		GPIO_Pin_5
	
	# define KEY_DOWN_PORT	GPIOE
	# define KEY_DOWN_PIN	GPIO_Pin_6
# else
	# define RCC_KEY_ALL	(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOA)
	
	# define KEY_UP_PORT	GPIOA
	# define KEY_UP_PIN		GPIO_Pin_8
	
	# define KEY_OK_PORT	GPIOC
	# define KEY_OK_PIN		GPIO_Pin_9
	
	# define KEY_DOWN_PORT	GPIOC
	# define KEY_DOWN_PIN	GPIO_Pin_8
# endif


# define BSP_KEY_COUNT		3
# define KEY_LONG_TIME		10
# define KEY_FILTER_TIME	1

typedef enum{
	KEY_ID_UP = 0x00,
	KEY_ID_OK,
	KEY_ID_DOWN,
}KEY_ID_ENUM;

typedef enum
{
	KEY_NONE = 0x00,
	
	KEY_UP_PRESS,
	KEY_UP_UP,
	KEY_UP_LONG,
	
	KEY_OK_PRESS,
	KEY_OK_UP,
	KEY_OK_LONG,
	
	KEY_DOWN_PRESS,
	KEY_DOWN_UP,
	KEY_DOWN_LONG
}KEY_STAT_ENUM;

# define KEY_FIFO_SIZE	10

typedef struct 
{
	uint8_t Fifo[KEY_FIFO_SIZE];
	uint8_t Read;
	uint8_t Write;
	
	uint8_t IsConfig;
}Key_Fifo_Str;

/*
	每个按键对应1个全局的结构体变量。
*/
typedef struct
{
	uint8_t (*IsKeyPressDunc)(void);
	
	uint8_t Count;
	uint16_t LongCount;
	uint16_t LongTime;
	uint8_t  State;
	uint8_t RepeatSpeed;
	uint8_t RepeatCount;
}Key_Str;


void bsp_KeyConfig(void);
void bsp_KeyGPIOConfig(void);
void bsp_KeyFifoConfig(void);
void bsp_KeyScan(void);
void bsp_KeyDetect(uint8_t Id);
void bsp_KeyClear(void);

void bsp_PutKey(uint8_t KeyValue);
uint8_t bsp_GetKey(void);
uint8_t bsp_GetKeyState(KEY_ID_ENUM KeyId);


# endif


