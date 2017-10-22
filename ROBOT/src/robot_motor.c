# include "robot.h"


extern uint32_t EdgeTime;

/*
*********************************************************************************************************
*                                          robot_MotorConfig
*
* Description: 机器人电机初始化函数
*             
* Arguments : 无
*
* Note(s)   : 无
*********************************************************************************************************
*/
void robot_MotorConfig(void)
{
	robot_MotorControlConfig();
	robot_MotorPWMConfig();
	robot_MotorStrConfig();
}

/*
*********************************************************************************************************
*                                   robot_MotorStrConfig       
*
* Description: 机器人结构体初始化函数
*             
* Arguments : 无
*
* Note(s)   : 无
*********************************************************************************************************
*/
void robot_MotorStrConfig(void)
{
	uint8_t mode = 0x00;
	
	Robot.dirction = POSITIVE;		/* 机器人初始方向为正方向 */
	Robot.M1_Dirction = POSITIVE; /* 电机正转 */
	Robot.M2_Dirction = POSITIVE; /* 电机正转 */
	Robot.M1_pwm = 0;             /* 初速度为零 */
	Robot.M2_pwm = 0;							 /**/
	Robot.IsChess = 0;						 /* 标志没有检测到棋子 */
	Robot.IsEdge = 0;							 /* 模块没有检测到边缘 */
	Robot.HandDirction = 0x00; 		 /* 上边身子默认正方向 */
	
	mode = robot_GetMode();
	
	switch(mode)
	{
		case 0x01:Robot.RobotMode = CHESS_MODE;break;
		case 0x02:Robot.RobotMode = ATTACK_MODE;break;
		default:Robot.RobotMode = CHESS_MODE;break;
	}
	if(Robot.RobotMode == CHESS_MODE)
		Robot.ModeSpeed = 200;
	else if(Robot.RobotMode == ATTACK_MODE)
		Robot.ModeSpeed = 300;
	
	
}

/*
*********************************************************************************************************
*                                      robot_MotorPWMConfig
*
* Description: 初始化电机PWM，频率为10K 
*             
* Arguments : 无
*
* Note(s)   : 无
*********************************************************************************************************
*/
void robot_MotorPWMConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 1000 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 6 - 1;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 50;
	
	TIM_OC1Init(TIM4,&TIM_OCInitStructure);	
	TIM_OC2Init(TIM4,&TIM_OCInitStructure);	
	
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_Cmd(TIM4,ENABLE);
}

/*
*********************************************************************************************************
*                                        robot_MotorControlConfig  
*
* Description: 电机控制端口初始化函数
*             
* Arguments : 无
*
* Note(s)   : 无
*********************************************************************************************************
*/
void robot_MotorControlConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOB, ENABLE); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

/*
*********************************************************************************************************
*                                       robot_SetDirction   
*
* Description: 机器人设置电机转动方向
*             
* Arguments : 无
*
* Note(s)   : 无
*********************************************************************************************************
*/
void robot_SetDirction(void)
{
	/* 设置电机1方向 */
	switch(Robot.M1_Dirction)
	{
		case POSITIVE:M1_Ahead();break;
		case NEGETIVE:M1_Backward();break;
	}
	/* 设置电机2方向 */
	switch(Robot.M2_Dirction)
	{
		case POSITIVE:M2_Ahead();break;
		case NEGETIVE:M2_Backward();break;
	}
}


/*
 *********************************************************************************************************
 *                                         robot_OutOfBounds 
 *
 * Description: 机器人边缘处理函数
 *             
 * Arguments : RobotPos,机器人检测到的边缘位置
 *
 * Note(s)   : 无
 *********************************************************************************************************
 */						 
void robot_OutOfBounds(uint8_t RobotPos)
{
	switch(RobotPos)
	{
		case FRONT_LEFT:  /* 左前方出界 */
		{
			Robot.dirction = NEGETIVE;  /* 车子换向 */
			Robot.M1_Dirction = NEGETIVE; 
			Robot.M2_Dirction = NEGETIVE;
			if(Robot.RobotMode == ATTACK_MODE)  /*  攻击模式和推棋子模式的回退速度不一样 */
			{
				Robot.M1_pwm = 120;
				Robot.M2_pwm = 120;
				robot_MotorMove(100);
			}else if(Robot.RobotMode == CHESS_MODE)
			{
				//if()
				Robot.M1_pwm = 110;   /* 首先往后退一点 */
				Robot.M2_pwm = 110;
				robot_MotorMove(100);  
				
//				Robot.M2_Dirction = POSITIVE;  /* 然后转动一个角度 */
//				robot_MotorMove(100);
//				Robot.M2_Dirction = NEGETIVE;  /* 恢复电机转动方向 */
			}
		}break;
		case FRONT_RIGHT:  /* 右前方出界 */
		{
			Robot.dirction = NEGETIVE;
			Robot.M1_Dirction = NEGETIVE;
			Robot.M2_Dirction = NEGETIVE;
			
			if(Robot.RobotMode == ATTACK_MODE)
			{
				Robot.M1_pwm = 120;
				Robot.M2_pwm = 120;
				robot_MotorMove(100);
			}
			else if(Robot.RobotMode == CHESS_MODE)
			{
				
				Robot.M1_pwm = 110;
				Robot.M2_pwm = 110;
				robot_MotorMove(100);
				
	
//				Robot.M2_Dirction = POSITIVE;  /* 然后转动一个角度 */
//				robot_MotorMove(100);
//				Robot.M2_Dirction = NEGETIVE;  /* 恢复电机转动方向 */
			}
		}break;
		case BACK_LEFT:  /* 左后方出界 */
		{
			Robot.dirction = POSITIVE;
			Robot.M1_Dirction = POSITIVE;
			Robot.M2_Dirction = POSITIVE;
			if(Robot.RobotMode == ATTACK_MODE)
			{
				Robot.M1_pwm = 120;
				Robot.M2_pwm = 120;
				robot_MotorMove(100);
			}
			else if(Robot.RobotMode == CHESS_MODE)
			{
				Robot.M1_pwm = 110;
				Robot.M2_pwm = 110;
				robot_MotorMove(100);
				
			}
		}break;
		case BACK_RIGHT:   /* 右后方出界 */
		{
			Robot.dirction = POSITIVE;
			Robot.M1_Dirction = POSITIVE;
			Robot.M2_Dirction = POSITIVE;
			if(Robot.RobotMode == ATTACK_MODE)
			{
				Robot.M1_pwm = 120;
				Robot.M2_pwm = 120;
				robot_MotorMove(100);
			}else if(Robot.RobotMode == CHESS_MODE)
			{
				Robot.M1_pwm = 110;
				Robot.M2_pwm = 110;
				robot_MotorMove(100);
				
//				Robot.M1_Dirction = NEGETIVE;
//				robot_MotorMove(100);
//				Robot.M1_Dirction = POSITIVE;
			}
		}break;
		default:break;
	}
}


/*
*********************************************************************************************************
*                                          robot_UpPlatform
*
* Description: 机器人上台函数
*             
* Arguments : 无
*
* Note(s)   : 无
*********************************************************************************************************
*/
void robot_UpPlatform(void)
{
	
//	Robot.M1_Dirction = NEGETIVE;
//	Robot.M1_pwm = 100;
//	robot_MotorMove(500);
//	
//	M1_Stop();
	M2_Stop();
		runActionGroup(0,1);
//	bsp_TimerDelayMs(500);
//	runActionGroup(1,1);
	while((ADC1ConvValue[ROBOT_RANG_H]>>4) < 130 || (ADC1ConvValue[ROBOT_RANG_D]>>4) <130)
	{
//		printf("Ranging H:%d       D:%d\r\n",ADC1ConvValue[ROBOT_RANG_H]>>4, ADC1ConvValue[ROBOT_RANG_D]>>4);
		bsp_LedToggle(4);
		bsp_TimerDelayMs(50);
	}
	Robot.M1_pwm = 340;
	Robot.M2_pwm = 280;
	robot_MotorMove(800);
	robot_MotorMove(300);
	
	runActionGroup(1,1);
	
//	M1_Stop();
//	M2_Stop();
//	runActionGroup(1,1);
	
//	Robot.M1_pwm = 240;
//	Robot.M2_pwm = 200;
//	robot_MotorMove(800);
}
/*
*********************************************************************************************************
*                                        robot_MotorMove  
*
* Description: 机器人电机转动函数
*             
* Arguments : time,电机转动时间，当time = 0时，表示不需要延时
*
* Note(s)   : 无
*********************************************************************************************************
*/
void robot_MotorMove(uint16_t time)
{	
	robot_SetDirction();
	
	TIM_SetCompare2(TIM4, Robot.M1_pwm);

	TIM_SetCompare1(TIM4, Robot.M2_pwm);
	
	if(time >0)
		bsp_TimerDelayMs(time);
}



/*
*********************************************************************************************************
*                                        robot_WaitChessFail  
*
* Description: 等待棋子掉下台
*             
* Arguments : ChessPos，检测到的棋子位置
*
* Note(s)   : 该函数现在已经不用，因为仿人组规则已经改变
*********************************************************************************************************
*/
//void robot_WaitChessFail(uint8_t ChessPos)
//{
//	switch(ChessPos)
//	{
//		case FRONT_LEFT:
//		{
//				if(IsRangDetected(ROBOT_RANG_A) || IsRangDetected(ROBOT_RANG_B) || IsRangDetected(ROBOT_RANG_C))//????????,????????????????
//				{
//					while(IsPhoDetected(ROBOT_PHO_C))//???????????
//					{
//						Robot.M1_Dirction = NEGETIVE;
//						Robot.M2_Dirction = POSITIVE;
//						Robot.dirction = POSITIVE;
//						Robot.M1_pwm = 40;
//						Robot.M2_pwm = 80;
//						robot_MotorMove(10);
//						
//						count ++;
//						if(count >40) //???????????????????,?????,?????
//						{
//							count = 0; break;
//						}
//					}
//				}
//		}break;
//		case FRONT_RIGHT:
//		{
//				if(IsRangDetected(ROBOT_RANG_A) || IsRangDetected(ROBOT_RANG_B) || IsRangDetected(ROBOT_RANG_C))
//				{
//					while(!IsPhoDetected(ROBOT_PHO_A))
//					{
//						Robot.M1_Dirction = POSITIVE;
//						Robot.M2_Dirction = NEGETIVE;
//						Robot.dirction = POSITIVE;
//						Robot.M1_pwm = 80;
//						Robot.M2_pwm = 40;
//						robot_MotorMove(10);
//						
//						count ++;
//						if(count >40)
//						{
//							count = 0; break;
//						}
//					}
//				}
//		}break;
//		case BACK_LEFT:
//		{
//				if(IsRangDetected(ROBOT_RANG_I) || IsRangDetected(ROBOT_RANG_J) || IsRangDetected(ROBOT_RANG_K))
//				{
//					while(!IsPhoDetected(ROBOT_PHO_J))
//					{
//						Robot.M2_Dirction = NEGETIVE;
//						Robot.M1_Dirction = POSITIVE;
//						Robot.dirction = NEGETIVE;
//						Robot.M1_pwm = 40;
//						Robot.M2_pwm = 80;
//						robot_MotorMove(10);
//						
//						count ++;
//						if(count >40)
//						{
//							count = 0; break;
//						}
//					}
//				}
//		}break;
//		case BACK_RIGHT:
//		{
//				if(IsRangDetected(ROBOT_RANG_I) || IsRangDetected(ROBOT_RANG_J) || IsRangDetected(ROBOT_RANG_K))
//				{
//					while(!IsPhoDetected(ROBOT_PHO_H))
//					{
//						Robot.M2_Dirction = POSITIVE;
//						Robot.M1_Dirction = NEGETIVE;
//						Robot.dirction = NEGETIVE;
//						Robot.M2_pwm = 40;
//						Robot.M1_pwm = 80;
//						robot_MotorMove(10);
//						
//						count ++;
//						if(count >40)
//						{
//							count = 0; break;
//						}
//					}
//				}
//		}break;
//		default:break;
//	}
//}

