# include "bsp.h"
# include "robot.h"

int main(void)
{ 	
	bsp_Config();
	bsp_TimerSoftStart(1,20,TIMER_MODE_AUTO);
	bsp_TimerSoftSetCallBack(1,bsp_KeyScan);
	
	bsp_TimerSoftStart(2,100,TIMER_MODE_AUTO);
	bsp_TimerSoftSetCallBack(2,robot_ShowState);
	
	robot_Config();
	
	robot_UpPlatform();
	
	while(1)
	{
//		if((ADC1ConvValue[ROBOT_GRAY] >> 2) < 80)
//		{
//			M1_Stop();
//			M2_Stop();
//		}else
//		{
			robot_Detect();
//		}
	}
}





