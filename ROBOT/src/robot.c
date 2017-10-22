# include "robot.h"

Robot_Dev Robot;	

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
void robot_Config(void)
{
	robot_DetectConfig();
	robot_MotorConfig();
# if ROBOT_DEBUG > 0u
	robot_DebugConfig();
# endif
}



void robot_ShowState(void)
{
	if(Robot.RobotMode == CHESS_MODE)
		bsp_LedToggle(0);
	else if(Robot.RobotMode == ATTACK_MODE)
		bsp_LedToggle(1);
}


void robot_SetMode(void)
{
	
}

