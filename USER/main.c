# include "bsp.h"
# include "robot.h"

int main(void)
{ 	
	bsp_Config();
	robot_Config();
	
//	robot_RangingConfig();
//	robot_ModeSwitchConfig();
//	robot_PhotoelectricConfig();
//	robot_MotorConfig();
	
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





