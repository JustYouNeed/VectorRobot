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
# if DEBUG_PERI_DETECT > 0u  /* �꿪�أ�ѡ���Ƿ������Ӽ�⹦�ܣ�����ʱʹ�� */
	if(!Robot.IsEdge && ((ADC1ConvValue[ROBOT_GRAY] >> 2) > 80) )
		robot_PeriDetect();
# endif
}




/*
*********************************************************************************************************
*                                        IsPhoDetected  
*
* Description: ����翪���Ƿ��⵽��Ե
*             
* Arguments : �ޣ�����1����⵽��Ե��0��û�м�⵽
*							
* Note(s)   : ��
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
* Description: �������ܱ߻�����⺯��
*             
* Arguments : ��
*
* Note(s)   : ��
*********************************************************************************************************
*/

uint32_t DetectCount = 0;
void robot_PeriDetect(void)
{
# if DEBUG_RANG_FRONT > 0u
	if(IsRangDetected(ROBOT_RANG_B)) /* �����������ǰ����⵽Ŀ�� */
	{
		/* �����ϸ�ʱ�̻����˷�����Σ��ı�Ϊ������ */
		Robot.dirction = POSITIVE;  
		Robot.M1_Dirction = POSITIVE; 
		Robot.M2_Dirction = POSITIVE; 
		/*  ���õ��ת���ٶ�Ϊ������ģʽ�ٶ� */
		
		if(Robot.RobotMode == CHESS_MODE)  /* ������ģʽ */
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
		}else   /* ս��ģʽ */
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
					/* �ٶȱ���Ҫ��һ������ */
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

		/* �ԻҶȽ����жϣ�ֻ��������һȦ�Ž��ж��� */
		if((ADC1ConvValue[ROBOT_GRAY]>>2) <= 200)
		{
			if(Robot.RobotMode == CHESS_MODE)  /* �����������ģʽ */
			{
				/* �������Ϊ�� */
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
	if(IsRangDetected(ROBOT_RANG_J))   /* ������������󷽼�⵽Ŀ�� */
	{
		/* ���ۻ������ϸ�ʱ�̷�����Σ��ı�Ϊ������ */
		Robot.dirction = NEGETIVE; 
		Robot.M1_Dirction = NEGETIVE; 
		Robot.M2_Dirction = NEGETIVE;  
		
		/*  ���õ��ת���ٶ�Ϊ������ģʽ�ٶ� */
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
					/* �ٶȱ���Ҫ��һ������ */
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
			/* ���ݻ����˵Ĳ�ͬģʽ��������Ķ��� */
			if(Robot.RobotMode == ATTACK_MODE)   /* ս��ģʽ */
			{
				/* ��������˳���Ϊ��������û��ִ�г���Ϊ���Ķ���ʱ */
				if(Robot.dirction == POSITIVE && IsActionCompelete != 0x01)
				{
					runActionGroup(2,1);   /* ִ�ж��� */
					Robot.HandDirction = 0x01;  /* ���������� */
					IsActionCompelete = 0x01;   /* �ñ�־Ϊ��ֹ�ظ�ִ�ж��� */
				}
				else if(Robot.dirction == NEGETIVE && IsActionCompelete != 0x02)
				{
					runActionGroup(4,1);
					Robot.HandDirction = 0x02;
					IsActionCompelete = 0x02;
				}
			}else if(Robot.RobotMode == CHESS_MODE)  /* ������ģʽ */
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
	if(IsRangDetected(ROBOT_RANG_A))  /* �����������ǰ����⵽Ŀ��  */
	{
		/* ���ܻ�������һ��ʱ�̵ķ�����Σ��ı䳵�ӷ���Ϊ������  */
		Robot.dirction = POSITIVE;
		/* ͬʱ������ת��Ŀ�귽�򣬻�������Ҫ��ʱ��ת�� */
		Robot.M1_Dirction = NEGETIVE;   /* ��ߵ����ת */
		Robot.M2_Dirction = POSITIVE;		/* �ұߵ����ת */

		/* ���û����˵��ת���ٶ� */
		Robot.M1_pwm = 300;  
		Robot.M2_pwm = 300;  
		robot_MotorMove(100);
	}else 
# endif
# if DEBUG_RANG_FRONT_RIGHT > 0u
	if(IsRangDetected(ROBOT_RANG_C))  /* �����������ǰ����⵽Ŀ�� */
	{
		/* ���ܻ�������һ��ʱ�̵ķ�����Σ��ı䷽��Ϊ������ */
		Robot.dirction = POSITIVE;
		
		/* ͬʱ������ת��Ŀ�귽����Ҫ˳ʱ��ת�� */
		Robot.M1_Dirction = POSITIVE; /* ��ߵ����ת */
		Robot.M2_Dirction = NEGETIVE; /* �ұߵ����ת */
		
		/* ���û����˵��ת���ٶ� */
		Robot.M1_pwm = 400;
		Robot.M2_pwm = 400;
		robot_MotorMove(60);
	}else 
# endif
# if DEBUG_RANG_BACK_LEFT > 0u
	if(IsRangDetected(ROBOT_RANG_I)) /* �����������󷽼�⵽Ŀ�� */
	{
		/* ���ܻ�������һ��ʱ�̵ķ������,�ı䳵�ӷ���Ϊ������ */
		Robot.dirction = NEGETIVE;
		
		/* ��������Ҫ˳ʱ��ת������ߵ����ת���ұߵ����ת	*/
		Robot.M1_Dirction = POSITIVE;
		Robot.M2_Dirction = NEGETIVE;
		
		/* ���û����˵��ת���ٶ� */
		Robot.M1_pwm = 360;
		Robot.M2_pwm = 360;
		robot_MotorMove(60);
	}else 
# endif
# if DEBUG_RANG_BACK_RIGHT > 0u
	if(IsRangDetected(ROBOT_RANG_K)) /* ����������Һ󷽼�⵽Ŀ�� */
	{
		/* ���ܻ�������һ��ʱ�̷�����Σ����÷���Ϊ������	*/
		Robot.dirction = NEGETIVE;
		
		/* ͬʱ��������Ҫ��ʱ��ת����ת��Ŀ�귽�� */
		Robot.M1_Dirction = NEGETIVE;  /* ��ߵ����ת */
		Robot.M2_Dirction = POSITIVE;  /* �ұߵ����ת*/
		
		/* ���û����˵��ת���ٶ� */
		Robot.M1_pwm = 360;
		Robot.M2_pwm = 360;
		
		robot_MotorMove(60);
	}else 
# endif
# if DEBUG_RANG_LEFT > 0u
	if(IsRangDetected(ROBOT_RANG_H))	/* �����������߼�⵽Ŀ�� */
	{
		/* ���ܻ�������һ��ʱ�̵ķ�����Σ��ı䷽��Ϊ������	*/
		Robot.dirction = POSITIVE;
		
		/* ͬʱ��������ʱ��ת����ʹ��������Ŀ�� */
		Robot.M1_Dirction = NEGETIVE; /* ��ߵ����ת */
		Robot.M2_Dirction = POSITIVE; /* �ұߵ����ת */	

		/* ���õ��ת���ٶ� */
		Robot.M1_pwm = 400;
		Robot.M2_pwm = 400;
		robot_MotorMove(150);
	}else 
# endif
# if DEBUG_RANG_RIGHT > 0u
	if(IsRangDetected(ROBOT_RANG_D)) /* ����������ұ߼�⵽Ŀ�� */
	{
		/* ���ܻ�������һ��ʱ�̵ķ�����Σ��ı䷽��Ϊ������	*/
		Robot.dirction = NEGETIVE;
		
		/* ͬʱ������˳ʱ��ת����ʹ��������Ŀ�� */
		Robot.M1_Dirction = POSITIVE; /* ��ߵ����ת */
		Robot.M2_Dirction = NEGETIVE; /* �ұߵ����ת */	

		/* ���õ��ת���ٶ� */
		Robot.M1_pwm = 400;
		Robot.M2_pwm = 400;
		robot_MotorMove(100);
	}else  /* ����������ܱ߶�û��Ŀ�� */
# endif
	{
		/* �����˱��ֵ�ǰ�н����� */
		Robot.M1_Dirction = Robot.M2_Dirction = Robot.dirction;
		robot_SetDirction();
//		robot_MotorMove(0);
		/* ͷ������ָ���ʼֵ */
		Robot.HandDirction = 0x00;
			runActionGroup(1,1);
	}
}

/*
*********************************************************************************************************
*                                     robot_EgdeDetect     
*
* Description: ��Ե��⺯��
*             
* Arguments : ��
*
* Note(s)   : ��
*********************************************************************************************************
*/
void robot_EgdeDetect(void)
{
	
	if(ADC1ConvValue[ROBOT_GRAY]>>2 < 200)
	{
			if(IsPhoDetected(ROBOT_PHO_A) && !Robot.IsEdge)  /* �����ǰ������ */
			{
				Robot.IsEdge = FRONT_LEFT;
				if(Robot.RobotMode == CHESS_MODE)
				{
					robot_OutOfBounds(FRONT_LEFT);  /* ִ�лس̺��� */

					if(flag != 1)
					{
						EdgeTime++;
						flag = 1;
					}
				}else
				{
					if((ADC1ConvValue[ROBOT_RANG_B] >> 4) < 110)
					{
						robot_OutOfBounds(FRONT_LEFT);  /* ִ�лس̺��� */

					if(flag != 1)
					{
						EdgeTime++;
						flag = 1;
					}
					}
				}
			}else if(IsPhoDetected(ROBOT_PHO_B) && !Robot.IsEdge)  /* �����ǰ������ */
			{
				if( Robot.RobotMode == CHESS_MODE)
				{
					Robot.IsEdge = FRONT_RIGHT;
					robot_OutOfBounds(FRONT_RIGHT);  /* ��ǰ������ */

					if(flag != 1)
					{
						EdgeTime++;
						flag = 1;
					}
			}else
				{
					if((ADC1ConvValue[ROBOT_RANG_B] >> 4) < 110)
					{
						robot_OutOfBounds(FRONT_RIGHT);  /* ִ�лس̺��� */

					if(flag != 1)
					{
						EdgeTime++;
						flag = 1;
					}
					}
				}
			}else if(IsPhoDetected(ROBOT_PHO_C) && !Robot.IsEdge)  /* �����󷽳��� */
			{
				if(Robot.RobotMode == CHESS_MODE)
				{
					Robot.IsEdge = BACK_LEFT;
					robot_OutOfBounds(BACK_LEFT);  /* ��󷽳��� */
					

					if(flag != 1)
					{
						EdgeTime++;
						flag = 1;
					}
				}else
				{
					if((ADC1ConvValue[ROBOT_RANG_J] >> 4) < 110)
					{
						robot_OutOfBounds(BACK_LEFT);  /* ִ�лس̺��� */

					if(flag != 1)
					{
						EdgeTime++;
						flag = 1;
					}
					}
				}
			}	else if(IsPhoDetected(ROBOT_PHO_D) && !Robot.IsEdge)		/* ����Һ󷽳��� */
			{		
				if(Robot.RobotMode == CHESS_MODE)
				{
					Robot.IsEdge = BACK_RIGHT;
					robot_OutOfBounds(BACK_RIGHT);  /* �Һ󷽳��� */
					

					if(flag != 1)
					{
						EdgeTime++;
						flag = 1;
					}
				}else
				{
					if((ADC1ConvValue[ROBOT_RANG_J] >> 4) < 110)
					{
						robot_OutOfBounds(BACK_RIGHT);  /* ִ�лس̺��� */

					if(flag != 1)
					{
						EdgeTime++;
						flag = 1;
					}
					}
				}
			}else  /* û�г��� */
			{
				Robot.M1_Dirction = Robot.dirction;
				Robot.M2_Dirction = Robot.dirction;

				if(EdgeTime % 2 == 0)/*  ÿ�����л�һ�η��� */
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
				robot_MotorMove(0);  /* ���ֵ��ת��������Ҫ��ʱ */
				Robot.IsEdge = 0;    /* �����Ե����־ */
				flag = 0;            /* �����Ե������־ */
			}
	}else  /* û�г��� */
	{
//		Robot.M1_Dirction = Robot.M2_Dirction = Robot.dirction;
		
//		/*  ÿ�����л�һ�η��� */
//		if(EdgeTime % 2 == 0)
//		{
//			Robot.M1_pwm = 220;
//			Robot.M2_pwm = 160;
//		}else
//		{
//			Robot.M1_pwm = 160;
//			Robot.M2_pwm = 220;
//		}
		
//		robot_MotorMove(0);  /* ���ֵ��ת��������Ҫ��ʱ */
//		Robot.IsEdge = 0;    /* �����Ե����־ */
//		flag = 0;            /* �����Ե������־ */
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
	if(GrayDiff >5) /* ��ǰ�Ҷ�ֵ�����ϴλҶ�ֵ��˵������������ */
		Robot.IsPosChange = 1;
	else if(GrayDiff < -5) /* ��ǰ�Ҷ�ֵС���ϴλҶ�ֵ��˵���������� */
		Robot.IsPosChange = -1;  
	else if(GrayDiff >= -5 && GrayDiff <= 5)
		Robot.IsPosChange = 0;
	
		
	LastGrayValue = CurGrayValue;
	
}

