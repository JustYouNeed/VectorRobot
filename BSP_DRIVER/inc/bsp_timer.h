# ifndef __BSP_TIMER_H
# define __BSP_TIMER_H

# include "bsp.h"

/* 定义软件定时器使用的定时器 */
# define USE_TIM2		1u
# define USE_TIM3   0u
# define USE_TIM4   0u
# define USE_TIM5   0u



# if USE_TIM2 > 0u
	# define BSP_TIMER				TIM2
	# define BSP_TIMER_IRQ		TIM2_IRQn
	# define BSP_TIM_RCC			RCC_APB1Periph_TIM2
#endif

# if USE_TIM3 > 0u
	# define BSP_TIMER				TIM3
	# define BSP_TIMER_IRQ		TIM3_IRQn
	# define BSP_TIM_RCC			RCC_APB1Periph_TIM3
#endif

# if USE_TIM4 > 0u
	# define BSP_TIMER				TIM4
	# define BSP_TIMER_IRQ		TIM4_IRQn
	# define BSP_TIM_RCC			RCC_APB1Periph_TIM4
#endif

# if USE_TIM5 > 0u
	# define BSP_TIMER				TIM5
	# define BSP_TIMER_IRQ		TIM5_IRQn
	# define BSP_TIM_RCC			RCC_APB1Periph_TIM5
#endif


# define SOFT_TIMER_COUNT			5

typedef void (*_cbTimerCallBack)(void);

typedef struct
{
	volatile uint8_t v_ucMode;	
	volatile uint8_t v_ucFlag;
	volatile uint32_t v_uiCount;
	volatile uint32_t v_uiPreLoad;
	
	_cbTimerCallBack _cbTimer;
	
}SoftTimer_Str;

typedef enum
{
	TIMER_MODE_ONCE = 0x00,
	TIMER_MODE_AUTO
}TIMER_MODE_ENUM;

void bsp_TimerSoftConfig(void);  /* 初始化软件定时器 */
int8_t bsp_TimerSoftStart(uint8_t ucTimerId, uint32_t uiPeriod, TIMER_MODE_ENUM eMode);
int8_t bsp_TimerSoftStop(uint8_t ucTimerId);
_cbTimerCallBack bsp_TimerSoftSetCallBack(uint8_t TimerId, _cbTimerCallBack  _cbTimer);
int8_t bsp_TimerSoftCheck(uint8_t ucTimerId);
int32_t bsp_TimerSoftGetRunTime(void);
int32_t bsp_TimerSoftCheckRunTime(int32_t iLastTime);
_cbTimerCallBack bsp_TimerSoftGetCallBack(uint8_t ucTimerId);

void bsp_TimerDelayMs(uint32_t ui_nMs);
void bsp_TimerDelayUs(uint32_t ui_nUs);

int8_t bsp_TimerHardConfig(uint8_t TIMx, uint32_t uiPeriod);
void bsp_TimerHardStart(uint8_t TIMx);
uint8_t bsp_TimerHardStop(uint8_t TIMx);
_cbTimerCallBack bsp_TimerHardSetCallBack(uint8_t TIMx, _cbTimerCallBack _cbTimer);

# endif

