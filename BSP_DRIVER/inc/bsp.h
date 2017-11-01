# ifndef __BSP_H
# define __BSP_H

# include "stdio.h"
# include "string.h"

# if defined (STM32F10X_HD)|| defined (STM32F10X_MD)|| defined (STM32F10X_LD)
	# define VECTOR_F1		1u
# elif defined (STM32F40_41xxx)
	# define VECTOR_F4		1u
# endif

# ifdef VECTOR_F1
	# include "stm32f10x.h"
# else
	# include "stm32f4xx.h"
# endif


# include "bsp_key.h"
# include "bsp_led.h"
# include "bsp_usart.h"
# include "bsp_timer.h"

/* 开关全局中断的宏 */
#define ENABLE_INT()	__set_PRIMASK(0)	/* 使能全局中断 */
#define DISABLE_INT()	__set_PRIMASK(1)	/* 禁止全局中断 */

# ifdef VECTOR_F1
  //	位带操作,实现51类似的GPIO控制功能
  //	具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
	//  IO口操作宏定义
	#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
	#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
	#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
	//IO口地址映射
	#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
	#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
	#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
	#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
	#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
	#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
	#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

	#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
	#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
	#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
	#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
	#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
	#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
	#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
# elif defined (VECTOR_F4)
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
# endif

 
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









typedef enum
{
	TIM = 0x00,
	USART,
	SPI
}PERIPH_ENUM;



void bsp_Config(void);
# ifdef VECTOR_F4
uint8_t bsp_GetTIMPinAF(TIM_TypeDef *TIMx);
uint8_t bsp_GetSPIPinAF(SPI_TypeDef* SPIx);
uint8_t bsp_GetADCPinAF(ADC_TypeDef* ADCx);
# endif
uint32_t bsp_GetTIMRCC(TIM_TypeDef *TIMx);
uint32_t bsp_GetGPIORCC(GPIO_TypeDef* GPIOx);
uint32_t bsp_GetSPIRCC(SPI_TypeDef *SPIx);
uint32_t bsp_GetUSARTRCC(USART_TypeDef* USARTx);
uint32_t bsp_GetADCRCC(ADC_TypeDef* ADCx);

uint16_t bsp_GetPinSource(uint16_t GPIO_Pin);

void bsp_PeriphClockCmd(void* Periph);

void bsp_TIMClockCmd(TIM_TypeDef *TIMx);
void bsp_ADCClockCmd(ADC_TypeDef* ADCx);
void bsp_USARTClockCmd(USART_TypeDef* USARTx);
void bsp_DACClcokCmd(DAC_TypeDef* DACx);
void bsp_SPIClockCmd(SPI_TypeDef* SPIx);
void bsp_GPIOClcokCmd(GPIO_TypeDef* GPIOx);
void bsp_DMAClockCmd(DMA_TypeDef* DMAx);
void bsp_FLASHClockCmd(FLASH_TypeDef* FLASHx);
void bsp_CRCClockCmd(CRC_TypeDef *CRCx);
void bsp_EXTIClockCmd(EXTI_TypeDef *EXTIx);
void bsp_CANClockCmd(CAN_TypeDef* CANx);
void bsp_WWDGClockCmd(WWDG_TypeDef *WWDGx);
void bsp_IWDGClockCmd(IWDG_TypeDef *IWDGx);
void bsp_I2CClockCmd(I2C_TypeDef *I2Cx);

# ifdef VECTOR_F4
void bsp_DMA2DClockCmd(DMA2D_TypeDef *DMA2Dx);
# endif

# endif


