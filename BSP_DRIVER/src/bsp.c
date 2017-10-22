# include "bsp.h"
# include "robot.h"



void bsp_Config(void)
{
	bsp_TimerSoftConfig();
	
	bsp_TimerSoftStart(1,20,TIMER_MODE_AUTO);
	bsp_TimerSoftSetCallBack(1,bsp_KeyScan);
	
	bsp_TimerSoftStart(2,100,TIMER_MODE_AUTO);
	bsp_TimerSoftSetCallBack(2,robot_ShowState);
	
//	bsp_TimerSoftStart(3, 400, TIMER_MODE_AUTO);
//	bsp_TimerSoftSetCallBack(3, robot_IsPosChange);
	
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

