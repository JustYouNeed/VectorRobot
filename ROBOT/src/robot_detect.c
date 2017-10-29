# include "robot.h"

#define SWITCH1 PGin(5)
#define SWITCH2 PGin(3)
#define SWITCH3 PDin(13)
#define SWITCH4 PDin(11)

uint16_t ADC1ConvValue[ROBOT_RANG_COUNT];
uint8_t IsActionCompelete = 0x00;
uint8_t flag = 0x00;
 uint32_t EdgeTime = 0x0000;






/*
*********************************************************************************************************
*                                          robot_Detect
*
* Description: 
*             
* Arguments : 
*
* Note(s)   : 
*********************************************************************************************************
*/
void robot_Detect(void)
{
	robot_EgdeDetect();
# if DEBUG_PERI_DETECT > 0u  /* 宏开关，选择是否开启棋子检测功能，调试时使用 */
	if(!Robot.IsEdge && ((ADC1ConvValue[ROBOT_GRAY] >> 2) > 80) )
		robot_PeriDetect();
# endif
}




/*
*********************************************************************************************************
*                                        IsPhoDetected  
*
* Description: 检测光电开关是否检测到边缘
*             
* Arguments : 无，返回1，检测到边缘。0，没有检测到
*							
* Note(s)   : 无
*********************************************************************************************************
*/
uint8_t IsPhoDetected(uint8_t PhoId)
{
	uint8_t result = 0x00;
	switch(PhoId)
	{
		case ROBOT_PHO_A:result = ((ROBOT_PHO_A_GPIO_PORT->IDR & ROBOT_PHO_A_GPIO_PIN) == 0)?0:1;break;
		case ROBOT_PHO_B:result = ((ROBOT_PHO_B_GPIO_PORT->IDR & ROBOT_PHO_B_GPIO_PIN) == 0)?0:1;break;
		case ROBOT_PHO_C:result = ((ROBOT_PHO_C_GPIO_PORT->IDR & ROBOT_PHO_C_GPIO_PIN) == 0)?0:1;break;
		case ROBOT_PHO_D:result = ((ROBOT_PHO_D_GPIO_PORT->IDR & ROBOT_PHO_D_GPIO_PIN) == 0)?0:1;break;
//		case ROBOT_PHO_E:result = PFin(12);break;
//	
//	  case ROBOT_PHO_H:result = PCin(3);break;
//		case ROBOT_PHO_I:result = PCin(1);break;
//		case ROBOT_PHO_J:result = PCin(0);break;
//		case ROBOT_PHO_K:result = PEin(6);break;
//		case ROBOT_PHO_L:result = PEin(5);break;
		default:break;
	}
	return result;
}











/*
*********************************************************************************************************
*                                          robot_PeriDetect
*
* Description: 机器人周边环境检测函数
*             
* Arguments : 无
*
* Note(s)   : 无
*********************************************************************************************************
*/

uint32_t DetectCount = 0;
void robot_PeriDetect(void)
{
# if DEBUG_RANG_FRONT > 0u
	if(IsRangDetected(ROBOT_RANG_B)) /* 如果机器人正前方检测到目标 */
	{
		/* 不管上个时刻机器人方向如何，改变为正方向 */
		Robot.dirction = POSITIVE;  
		Robot.M1_Dirction = POSITIVE; 
		Robot.M2_Dirction = POSITIVE; 
		/*  设置电机转动速度为机器人模式速度 */
		
		if(Robot.RobotMode == CHESS_MODE)  /* 推棋子模式 */
		{
			if(ADC1ConvValue[ROBOT_GRAY]>>2 <= 190)
			{
				Robot.M1_pwm = 100;
				Robot.M2_pwm = 100;
			}else
			{
				Robot.M1_pwm = Robot.ModeSpeed;
				Robot.M2_pwm = Robot.ModeSpeed;
			}
		}else   /* 战斗模式 */
		{
			if(Robot.dirction == POSITIVE)
			{
				if((ADC1ConvValue[ROBOT_RANG_B] >> 4) >130) 
					runActionGroup(2,1);
//				else
//					runActionGroup(0,1);
			}
			else if(Robot.dirction == NEGETIVE)
			{
				if((ADC1ConvValue[ROBOT_RANG_J] >> 4) >130) 
					runActionGroup(4,1);
//				else
//					runActionGroup(0,1);
			}
			
			if((ADC1ConvValue[ROBOT_RANG_B] >>4) > 120)
			{
				DetectCount ++;
				if(DetectCount > 3) 
				{
					/* 速度必须要有一个上限 */
					if(Robot.M1_pwm < 900)
						Robot.M1_pwm += 50 ;
					if(Robot.M2_pwm < 900)
						Robot.M2_pwm += 50;
					DetectCount = 0;
				}
			}else
			{
				Robot.M1_pwm = 200;
				Robot.M2_pwm = 200;
			}
		}

		/* 对灰度进行判断，只有在外面一圈才进行动作 */
		if((ADC1ConvValue[ROBOT_GRAY]>>2) <= 200)
		{
			if(Robot.RobotMode == CHESS_MODE)  /* 如果是推棋子模式 */
			{
				/* 如果方向为正 */
				if(Robot.dirction == POSITIVE )
				{
					runActionGroup(2,1);
					Robot.HandDirction = 0x01;
				}else if(Robot.dirction == NEGETIVE)
				{
					runActionGroup(4,1);
					Robot.HandDirction = 0x02;
				}
			}
		}
		robot_MotorMove(200);
	}else 
# endif
# if DEBUG_RANG_BACK > 0u
	if(IsRangDetected(ROBOT_RANG_J))   /* 如果机器人正后方检测到目标 */
	{
		/* 无论机器人上个时刻方向如何，改变为负方向 */
		Robot.dirction = NEGETIVE; 
		Robot.M1_Dirction = NEGETIVE; 
		Robot.M2_Dirction = NEGETIVE;  
		
		/*  设置电机转动速度为机器人模式速度 */
		if(Robot.RobotMode == CHESS_MODE)
		{
			if(ADC1ConvValue[ROBOT_GRAY]>>2 <= 180)
			{
				Robot.M1_pwm = 100;
				Robot.M2_pwm = 100;
			}else
			{
				Robot.M1_pwm = Robot.ModeSpeed;
				Robot.M2_pwm = Robot.ModeSpeed;
			}
		}else
		{
			if(Robot.dirction == POSITIVE)
			{
				if((ADC1ConvValue[ROBOT_RANG_B] >> 4) >130) 
					runActionGroup(3,1);
//				else
//					runActionGroup(0,1);
			}
			else if(Robot.dirction == NEGETIVE)
			{
				if((ADC1ConvValue[ROBOT_RANG_J] >> 4) >130) 
					runActionGroup(4,1);
//				else
//					runActionGroup(0,1);
			}
			
			
			if((ADC1ConvValue[ROBOT_RANG_J] >>4) > 120)
			{
				DetectCount ++;
				if(DetectCount > 4) 
				{
					/* 速度必须要有一个上限 */
					if(Robot.M1_pwm < 900)
						Robot.M1_pwm += 50 ;
					if(Robot.M2_pwm < 900)
						Robot.M2_pwm += 50;
					DetectCount = 0;
				}
			}else
			{
				Robot.M1_pwm = 200;
				Robot.M2_pwm = 200;
			}
		}
		
		if(ADC1ConvValue[ROBOT_GRAY]>>2 <= 200)
		{
			/* 根据机器人的不同模式设置上身的动作 */
			if(Robot.RobotMode == ATTACK_MODE)   /* 战斗模式 */
			{
				/* 如果机器人朝向为正，并且没有执行朝向为正的动作时 */
				if(Robot.dirction == POSITIVE && IsActionCompelete != 0x01)
				{
					runActionGroup(2,1);   /* 执行动作 */
					Robot.HandDirction = 0x01;  /* 设置上身朝向 */
					IsActionCompelete = 0x01;   /* 该标志为防止重复执行动作 */
				}
				else if(Robot.dirction == NEGETIVE && IsActionCompelete != 0x02)
				{
					runActionGroup(4,1);
					Robot.HandDirction = 0x02;
					IsActionCompelete = 0x02;
				}
			}else if(Robot.RobotMode == CHESS_MODE)  /* 推棋子模式 */
			{
				if(Robot.dirction == POSITIVE)
				{
					runActionGroup(2,1);
					Robot.HandDirction = 0x01;
				}else if(Robot.dirction == NEGETIVE)
				{
					runActionGroup(4,1);
					Robot.HandDirction = 0x02;
				}
			}
		}
		robot_MotorMove(200);
	}else	
# endif
# if DEBUG_RANG_FRONT_LEFT > 0u
	if(IsRangDetected(ROBOT_RANG_A))  /* 如果机器人左前方检测到目标  */
	{
		/* 不管机器人上一个时刻的方向如何，改变车子方向为正方向  */
		Robot.dirction = POSITIVE;
		/* 同时机器人转向目标方向，机器人需要逆时针转动 */
		Robot.M1_Dirction = NEGETIVE;   /* 左边电机反转 */
		Robot.M2_Dirction = POSITIVE;		/* 右边电机正转 */

		/* 设置机器人电机转动速度 */
		Robot.M1_pwm = 300;  
		Robot.M2_pwm = 300;  
		robot_MotorMove(100);
	}else 
# endif
# if DEBUG_RANG_FRONT_RIGHT > 0u
	if(IsRangDetected(ROBOT_RANG_C))  /* 如果机器人右前方检测到目标 */
	{
		/* 不管机器人上一个时刻的方向如何，改变方向为正方向 */
		Robot.dirction = POSITIVE;
		
		/* 同时机器人转向目标方向，需要顺时针转动 */
		Robot.M1_Dirction = POSITIVE; /* 左边电机正转 */
		Robot.M2_Dirction = NEGETIVE; /* 右边电机反转 */
		
		/* 设置机器人电机转动速度 */
		Robot.M1_pwm = 400;
		Robot.M2_pwm = 400;
		robot_MotorMove(60);
	}else 
# endif
# if DEBUG_RANG_BACK_LEFT > 0u
	if(IsRangDetected(ROBOT_RANG_I)) /* 如果机器人左后方检测到目标 */
	{
		/* 不管机器人上一个时刻的方向如何,改变车子方向为负方向 */
		Robot.dirction = NEGETIVE;
		
		/* 机器人需要顺时针转动，左边电机正转，右边电机反转	*/
		Robot.M1_Dirction = POSITIVE;
		Robot.M2_Dirction = NEGETIVE;
		
		/* 设置机器人电机转动速度 */
		Robot.M1_pwm = 360;
		Robot.M2_pwm = 360;
		robot_MotorMove(60);
	}else 
# endif
# if DEBUG_RANG_BACK_RIGHT > 0u
	if(IsRangDetected(ROBOT_RANG_K)) /* 如果机器人右后方检测到目标 */
	{
		/* 不管机器人上一个时刻方向如何，设置方向为负方向	*/
		Robot.dirction = NEGETIVE;
		
		/* 同时机器人需要逆时针转动，转向目标方向 */
		Robot.M1_Dirction = NEGETIVE;  /* 左边电机反转 */
		Robot.M2_Dirction = POSITIVE;  /* 右边电机正转*/
		
		/* 设置机器人电机转动速度 */
		Robot.M1_pwm = 360;
		Robot.M2_pwm = 360;
		
		robot_MotorMove(60);
	}else 
# endif
# if DEBUG_RANG_LEFT > 0u
	if(IsRangDetected(ROBOT_RANG_H))	/* 如果机器人左边检测到目标 */
	{
		/* 不管机器人上一个时刻的方向如何，改变方向为正方向	*/
		Robot.dirction = POSITIVE;
		
		/* 同时机器人逆时针转动，使正方向朝向目标 */
		Robot.M1_Dirction = NEGETIVE; /* 左边电机反转 */
		Robot.M2_Dirction = POSITIVE; /* 右边电机正转 */	

		/* 设置电机转动速度 */
		Robot.M1_pwm = 400;
		Robot.M2_pwm = 400;
		robot_MotorMove(150);
	}else 
# endif
# if DEBUG_RANG_RIGHT > 0u
	if(IsRangDetected(ROBOT_RANG_D)) /* 如果机器人右边检测到目标 */
	{
		/* 不管机器人上一个时刻的方向如何，改变方向为负方向	*/
		Robot.dirction = NEGETIVE;
		
		/* 同时机器人顺时针转动，使负方向朝向目标 */
		Robot.M1_Dirction = POSITIVE; /* 左边电机正转 */
		Robot.M2_Dirction = NEGETIVE; /* 右边电机反转 */	

		/* 设置电机转动速度 */
		Robot.M1_pwm = 400;
		Robot.M2_pwm = 400;
		robot_MotorMove(100);
	}else  /* 如果机器人周边都没有目标 */
# endif
	{
		/* 机器人保持当前行进方向 */
		Robot.M1_Dirction = Robot.M2_Dirction = Robot.dirction;
		robot_SetDirction();
//		robot_MotorMove(0);
		/* 头部方向恢复初始值 */
		Robot.HandDirction = 0x00;
			runActionGroup(1,1);
	}
}

/*
*********************************************************************************************************
*                                     robot_EgdeDetect     
*
* Description: 边缘检测函数
*             
* Arguments : 无
*
* Note(s)   : 无
*********************************************************************************************************
*/
void robot_EgdeDetect(void)
{
	
	if(ADC1ConvValue[ROBOT_GRAY]>>2 < 200)
	{
			if(IsPhoDetected(ROBOT_PHO_A) && !Robot.IsEdge)  /* 如果左前方出界 */
			{
				Robot.IsEdge = FRONT_LEFT;
				if(Robot.RobotMode == CHESS_MODE)
				{
					robot_OutOfBounds(FRONT_LEFT);  /* 执行回程函数 */

					if(flag != 1)
					{
						EdgeTime++;
						flag = 1;
					}
				}else
				{
					if((ADC1ConvValue[ROBOT_RANG_B] >> 4) < 110)
					{
						robot_OutOfBounds(FRONT_LEFT);  /* 执行回程函数 */

					if(flag != 1)
					{
						EdgeTime++;
						flag = 1;
					}
					}
				}
			}else if(IsPhoDetected(ROBOT_PHO_B) && !Robot.IsEdge)  /* 如果右前方出界 */
			{
				if( Robot.RobotMode == CHESS_MODE)
				{
					Robot.IsEdge = FRONT_RIGHT;
					robot_OutOfBounds(FRONT_RIGHT);  /* 右前方出界 */

					if(flag != 1)
					{
						EdgeTime++;
						flag = 1;
					}
			}else
				{
					if((ADC1ConvValue[ROBOT_RANG_B] >> 4) < 110)
					{
						robot_OutOfBounds(FRONT_RIGHT);  /* 执行回程函数 */

					if(flag != 1)
					{
						EdgeTime++;
						flag = 1;
					}
					}
				}
			}else if(IsPhoDetected(ROBOT_PHO_C) && !Robot.IsEdge)  /* 如果左后方出界 */
			{
				if(Robot.RobotMode == CHESS_MODE)
				{
					Robot.IsEdge = BACK_LEFT;
					robot_OutOfBounds(BACK_LEFT);  /* 左后方出界 */
					

					if(flag != 1)
					{
						EdgeTime++;
						flag = 1;
					}
				}else
				{
					if((ADC1ConvValue[ROBOT_RANG_J] >> 4) < 110)
					{
						robot_OutOfBounds(BACK_LEFT);  /* 执行回程函数 */

					if(flag != 1)
					{
						EdgeTime++;
						flag = 1;
					}
					}
				}
			}	else if(IsPhoDetected(ROBOT_PHO_D) && !Robot.IsEdge)		/* 如果右后方出界 */
			{		
				if(Robot.RobotMode == CHESS_MODE)
				{
					Robot.IsEdge = BACK_RIGHT;
					robot_OutOfBounds(BACK_RIGHT);  /* 右后方出界 */
					

					if(flag != 1)
					{
						EdgeTime++;
						flag = 1;
					}
				}else
				{
					if((ADC1ConvValue[ROBOT_RANG_J] >> 4) < 110)
					{
						robot_OutOfBounds(BACK_RIGHT);  /* 执行回程函数 */

					if(flag != 1)
					{
						EdgeTime++;
						flag = 1;
					}
					}
				}
			}else  /* 没有出界 */
			{
				Robot.M1_Dirction = Robot.dirction;
				Robot.M2_Dirction = Robot.dirction;

				if(EdgeTime % 2 == 0)/*  每两次切换一次方向 */
				{
					Robot.M1_pwm = 200;
					Robot.M2_pwm = 160;
				}else
				{
					Robot.M1_pwm = 160;
					Robot.M2_pwm = 200;
				}			
				if((ADC1ConvValue[ROBOT_GRAY] >> 2) < 100)
				{
					Robot.M1_pwm = 140;
					Robot.M2_pwm = 140;
				}
				robot_MotorMove(0);  /* 保持电机转动，不需要延时 */
				Robot.IsEdge = 0;    /* 清除边缘检测标志 */
				flag = 0;            /* 清除边缘计数标志 */
			}
	}else  /* 没有出界 */
	{
//		Robot.M1_Dirction = Robot.M2_Dirction = Robot.dirction;
		
//		/*  每两次切换一次方向 */
//		if(EdgeTime % 2 == 0)
//		{
//			Robot.M1_pwm = 220;
//			Robot.M2_pwm = 160;
//		}else
//		{
//			Robot.M1_pwm = 160;
//			Robot.M2_pwm = 220;
//		}
		
//		robot_MotorMove(0);  /* 保持电机转动，不需要延时 */
//		Robot.IsEdge = 0;    /* 清除边缘检测标志 */
//		flag = 0;            /* 清除边缘计数标志 */
	}
}


static uint16_t LastGrayValue = 0x00;
static uint16_t CurGrayValue = 0x00;

void robot_IsPosChange(void)
{
	int result = 0x00;
	int GrayDiff = 0x00;
	CurGrayValue = ADC1ConvValue[ROBOT_GRAY] >> 2;
	
	GrayDiff = CurGrayValue - LastGrayValue;
	if(GrayDiff >5) /* 当前灰度值大于上次灰度值，说明正在向中心 */
		Robot.IsPosChange = 1;
	else if(GrayDiff < -5) /* 当前灰度值小于上次灰度值，说明在向外走 */
		Robot.IsPosChange = -1;  
	else if(GrayDiff >= -5 && GrayDiff <= 5)
		Robot.IsPosChange = 0;
	
		
	LastGrayValue = CurGrayValue;
	
}

