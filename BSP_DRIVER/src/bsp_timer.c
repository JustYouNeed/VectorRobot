# include "bsp.h"
static volatile uint32_t s_uiDelayCount = 0;
static volatile uint8_t s_ucTimeOutFlag = 0;

__IO int32_t g_iRunTime = 0;

/*已使用定时器标志位，变量的8个位对应着8个定时器*/
static uint8_t s_ucUsedTIM = 0x00;
SoftTimer_Str SoftTimer[SOFT_TIMER_COUNT];

static _cbTimerCallBack TIM1_CallBack = 0;
static _cbTimerCallBack TIM2_CallBack = 0;
static _cbTimerCallBack TIM3_CallBack = 0;
static _cbTimerCallBack TIM4_CallBack = 0;
static _cbTimerCallBack TIM5_CallBack = 0;
static _cbTimerCallBack TIM6_CallBack = 0;

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
void bsp_TimerSoftConfig(void)
{
	uint8_t i = 0;
	
	for(i = 0; i < SOFT_TIMER_COUNT; i++)
	{
		SoftTimer[i].v_uiCount = 0;
		SoftTimer[i].v_uiPreLoad = 0;
		SoftTimer[i].v_ucFlag = 0;
		SoftTimer[i].v_ucMode = 0;
		SoftTimer[i]._cbTimer = 0;
	}
	
	SysTick_Config(SystemCoreClock / 1000);
}

/*
*********************************************************************************************************
*                                        bsp_TimerSoftDec  
*
* Description: 
*             
* Arguments : 
*
* Note(s)   : 
*********************************************************************************************************
*/
static void bsp_TimerSoftDec(SoftTimer_Str * pTimer)
{
	if(pTimer->v_uiCount >0)
	{
		if(--pTimer->v_uiCount ==0 )
		{
			pTimer->v_ucFlag = 1;
			
			
			if(pTimer->v_ucMode == TIMER_MODE_AUTO)
			{
				pTimer->v_uiCount = pTimer->v_uiPreLoad;
			}
			
			if(pTimer->_cbTimer)
			{
				pTimer->_cbTimer();
			}
		}
	}
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
void SysTick_ISR(void)
{
//	static uint8_t s_ucCount = 0;
	uint8_t i = 0;
	
	if(s_uiDelayCount > 0)
	{
		if(-- s_uiDelayCount == 0) s_ucTimeOutFlag = 1;
	}
	
	g_iRunTime ++;
	if(g_iRunTime == 0x7fffffff) g_iRunTime = 0;
	
	
	for(i = 0; i < SOFT_TIMER_COUNT; i++)
	{
		bsp_TimerSoftDec(&SoftTimer[i]);
	}
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
void SysTick_Handler(void)
{
	SysTick_ISR();
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
void bsp_TimerDelayMs(uint32_t ui_nMs)
{
	if(ui_nMs == 0) return ;
	else if(ui_nMs == 1) ui_nMs = 2;
	
	DISABLE_INT();
	
	s_uiDelayCount = ui_nMs;
	s_ucTimeOutFlag = 0;
	
	ENABLE_INT();
	
	while(1)
	{
		if(s_ucTimeOutFlag == 1) break;
	}
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
void bsp_TimerDelayUs(uint32_t ui_nUs)
{
		uint32_t ticks;
    uint32_t told;
    uint32_t tnow;
    uint32_t tcnt = 0;
    uint32_t reload;
       
		reload = SysTick->LOAD;                
    ticks = ui_nUs * (SystemCoreClock / 1000000);	 /* 需要的节拍数 */  
    
    tcnt = 0;
    told = SysTick->VAL;             /* 刚进入时的计数器值 */

    while (1)
    {
			tnow = SysTick->VAL;    
			if (tnow != told)
			{    
				/* SYSTICK是一个递减的计数器 */    
				if (tnow < told)
				{
						tcnt += told - tnow;    
				}
				/* 重新装载递减 */
				else
				{
						tcnt += reload - tnow + told;    
				}        
				told = tnow;

				/* 时间超过/等于要延迟的时间,则退出 */
				if (tcnt >= ticks)
				{
					break;
				}
			}  
    }
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
int8_t bsp_TimerSoftStart(uint8_t ucTimerId, uint32_t uiPeriod, TIMER_MODE_ENUM eMode)
{
	if(ucTimerId > SOFT_TIMER_COUNT) return -1;
	
	DISABLE_INT();
	SoftTimer[ucTimerId].v_uiCount = uiPeriod;
	SoftTimer[ucTimerId].v_ucFlag = 0;
	SoftTimer[ucTimerId].v_ucMode = eMode;
	SoftTimer[ucTimerId].v_uiPreLoad = uiPeriod;
	ENABLE_INT();
	return 0;
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
int8_t bsp_TimerSoftStop(uint8_t ucTimerId)
{
	if(ucTimerId > SOFT_TIMER_COUNT) return -1;
	
	DISABLE_INT();
	
	SoftTimer[ucTimerId].v_ucMode = 0;
	SoftTimer[ucTimerId].v_uiPreLoad = 0;
	SoftTimer[ucTimerId].v_uiCount = 0;
	
	ENABLE_INT();
	
	return 0;
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
int8_t bsp_TimerSoftCheck(uint8_t ucTimerId)
{
	if(ucTimerId > SOFT_TIMER_COUNT) return -1;
	
	return (SoftTimer[ucTimerId].v_ucFlag == 1)?0:1;
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
int32_t bsp_TimerSoftGetRunTime(void)
{
	int32_t runTime;
	DISABLE_INT();
	
	runTime = g_iRunTime;
	
	ENABLE_INT();
	
	return runTime;
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
int32_t bsp_TimerSoftCheckRunTime(int32_t iLastTime)
{
	int32_t nowTime;
	int32_t timeDiff;
	
	DISABLE_INT();
	
	nowTime = g_iRunTime;
	
	ENABLE_INT();
	
	if (nowTime >= iLastTime)
	{
		timeDiff = nowTime - iLastTime;
	}
	else
	{
		timeDiff = 0x7FFFFFFF - iLastTime + nowTime;
	}
	
	return timeDiff;
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
_cbTimerCallBack  bsp_TimerSoftSetCallBack(uint8_t TimerId, _cbTimerCallBack  _cbTimer)
{
	_cbTimerCallBack _cbTimerTemp;
	_cbTimerTemp = SoftTimer[TimerId]._cbTimer;
	
	SoftTimer[TimerId]._cbTimer = _cbTimer;
	
	return _cbTimerTemp;
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
int8_t bsp_TimerHardConfig(uint8_t TIMx, uint32_t uiPeriod)
{
	if(TIMx < 2 || TIMx > 5) return -1;
	
	if(TIMx == 2)
	{
		
	}else if(TIMx == 3)
	{
		
	}else if(TIMx == 4)
	{
		
	}else if(TIMx == 5)
	{
		
	}
	return 0;
}


void TIM2_IRQHandler(void)
{
	
}

void TIM3_IRQHandler(void)
{
	
}

void TIM4_IRQHandler(void)
{
	
}

void TIM5_IRQHandler(void)
{
	
}

