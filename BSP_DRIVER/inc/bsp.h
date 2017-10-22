# ifndef __BSP_H
# define __BSP_H

# include "stdio.h"
# include "string.h"

# define VECTOR_F4		1u


# ifdef VECTOR_F1
	# include "stm32f10x.h"
# else
	# include "stm32f4xx.h"
# endif

/* 开关全局中断的宏 */
#define ENABLE_INT()	__set_PRIMASK(0)	/* 使能全局中断 */
#define DISABLE_INT()	__set_PRIMASK(1)	/* 禁止全局中断 */

//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).M4同M3类似,只是寄存器地址变了.
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+20) //0x40020014
#define GPIOB_ODR_Addr    (GPIOB_BASE+20) //0x40020414 
#define GPIOC_ODR_Addr    (GPIOC_BASE+20) //0x40020814 
#define GPIOD_ODR_Addr    (GPIOD_BASE+20) //0x40020C14 
#define GPIOE_ODR_Addr    (GPIOE_BASE+20) //0x40021014 
#define GPIOF_ODR_Addr    (GPIOF_BASE+20) //0x40021414    
#define GPIOG_ODR_Addr    (GPIOG_BASE+20) //0x40021814   
#define GPIOH_ODR_Addr    (GPIOH_BASE+20) //0x40021C14    
#define GPIOI_ODR_Addr    (GPIOI_BASE+20) //0x40022014     

#define GPIOA_IDR_Addr    (GPIOA_BASE+16) //0x40020010 
#define GPIOB_IDR_Addr    (GPIOB_BASE+16) //0x40020410 
#define GPIOC_IDR_Addr    (GPIOC_BASE+16) //0x40020810 
#define GPIOD_IDR_Addr    (GPIOD_BASE+16) //0x40020C10 
#define GPIOE_IDR_Addr    (GPIOE_BASE+16) //0x40021010 
#define GPIOF_IDR_Addr    (GPIOF_BASE+16) //0x40021410 
#define GPIOG_IDR_Addr    (GPIOG_BASE+16) //0x40021810 
#define GPIOH_IDR_Addr    (GPIOH_BASE+16) //0x40021C10 
#define GPIOI_IDR_Addr    (GPIOI_BASE+16) //0x40022010 
 
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入

#define PHout(n)   BIT_ADDR(GPIOH_ODR_Addr,n)  //输出 
#define PHin(n)    BIT_ADDR(GPIOH_IDR_Addr,n)  //输入

#define PIout(n)   BIT_ADDR(GPIOI_ODR_Addr,n)  //输出 
#define PIin(n)    BIT_ADDR(GPIOI_IDR_Addr,n)  //输入


/* 宏开关，选择是否使用按键模块，默认开启*/
# define USE_KEY	1u

/* 宏开关，选择是否使用LED模块，默认开启 */
# define USE_LED	1u

/* 宏开关，选择是否使用SPI模块，默认关闭 */
# define USE_SPI	0u

/* 宏开关，选择是否使用串口模块，默认开启 */
# define USE_USART	1u

/* 宏开关，选择是否使用SDIO模块，默认关闭 */
# define USE_SDIO	0

/* 宏开关，选择是否使用LCD模块，默认关闭 */
# define USE_LCD	0

/* 宏开关，选择是否使用SRAM模块，默认关闭 */
# define USE_SRAM	0

/* 宏开关，选择是否使用ADC模块，默认关闭 */
# define USE_ADC	0

/* 宏开关，选择是否使用ADC模块，默认关闭 */
# define USE_DAC	0

/* 宏开关，选择是否使用看门狗，默认关闭 */
# define USE_WWDG	0

/* 宏开关，选择是否使用窗口看门狗模块，默认关闭 */
# define USE_IWDG	0

/* 宏开关，选择是否使用定时器模块，默认开启 */
/* 当关闭这一模块时，将无法使用软件定时器以及延时函数 */
# define USE_TIM	1u

/* 宏开关，选择是否使用PWM模块，默认关闭 */
# define USE_PWM	0

/* 宏开关，选择是否使用USB模块，默认关闭 */
# define USE_USB	0




# if	USE_KEY > 0u
	# include "bsp_key.h"
# endif


# if USE_LED > 0u
	# include "bsp_led.h"
# endif

# if USE_USART > 0u
	# include "bsp_usart.h"
# endif

# if USE_TIM > 0u
	# include "bsp_timer.h"
# endif

void bsp_Config(void);

# endif


