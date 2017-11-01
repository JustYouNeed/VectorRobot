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
	robot_SensorConfig();
	robot_ModeSwitchConfig();
	robot_ParaConfig();
	robot_MotorConfig();
}


void robot_ParaConfig(void)
{
	uint8_t mode = 0x00;
	
	Robot.dirction = POSITIVE;		/* �����˳�ʼ����Ϊ������ */
	Robot.M1_Dirction = POSITIVE; /* �����ת */
	Robot.M2_Dirction = POSITIVE; /* �����ת */
	Robot.M1_pwm = 0;             /* ���ٶ�Ϊ�� */
	Robot.M2_pwm = 0;							 /**/
	Robot.IsChess = 0;						 /* ��־û�м�⵽���� */
	Robot.IsEdge = 0;							 /* ģ��û�м�⵽��Ե */
	Robot.HandDirction = 0x00; 		 /* �ϱ�����Ĭ�������� */
	Robot.FrontLeft_TurnTime = 100;
	Robot.FrontRight_TurnTime = 100;
	
	mode = robot_GetMode();  /* ��ȡ����������ģʽ */
	
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


void robot_ShowState(void)
{
	if(Robot.RobotMode == CHESS_MODE)
		bsp_LedToggle(0);
	else if(Robot.RobotMode == ATTACK_MODE)
		bsp_LedToggle(1);
}

void robot_ModeSwitchConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG | RCC_AHB1Periph_GPIOD, ENABLE); 
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOG,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_11 | GPIO_Pin_9;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOD, GPIO_Pin_9);
	GPIO_ResetBits(GPIOG,GPIO_Pin_5 | GPIO_Pin_3);
	GPIO_ResetBits(GPIOD,GPIO_Pin_13 | GPIO_Pin_11);
}

uint8_t robot_GetMode(void)
{
	uint8_t result = 0x00;
	
	result |= PDin(11) << 0;
	result |= PDin(13) << 1;
	result |= PGin(3)  << 2;
	result |= PGin(5)  << 3;	
	
	return result;
}

void robot_SetMode(void)
{
	
}

