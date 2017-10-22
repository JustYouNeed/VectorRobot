# ifndef __MOTOR_H
# define __MOTOR_H

# include "bsp.h"

# define CHESS_MODE		0x01
# define ATTACK_MODE	0x02

/* Definition of motor control pin */
# define ROBOT_MOTOR_EN_RCC_ALL		(RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOB)

# define ROBOT_M1_ENA_GPIO_PORT		GPIOB
# define ROBOT_M1_ENA_GPIO_PIN		GPIO_Pin_9
# define ROBOT_M1_ENB_GPIO_PORT		GPIOE
# define ROBOT_M1_ENB_GPIO_PIN		GPIO_Pin_1

# define ROBOT_M2_ENA_GPIO_PORT		GPIOB
# define ROBOT_M2_ENA_GPIO_PIN		GPIO_Pin_8
# define ROBOT_M2_ENB_GPIO_PORT		GPIOE
# define ROBOT_M2_ENB_GPIO_PIN		GPIO_Pin_0



//# define M1_ENA	

# define M2_ENA		PBout(8)
# define M2_ENB		PEout(0)

# define M1_ENA		PBout(9)
# define M1_ENB		PEout(1)

# define M1_Stop()				{	M1_ENA = 1;	M1_ENB = 1;}

# define M2_Stop()				{	M2_ENA = 1;	M2_ENB = 1;}
								
# define M1_Ahead()				{	M1_ENA = 0;	M1_ENB = 1;}

# define M2_Ahead()				{	M2_ENA = 1;	M2_ENB = 0;}

# define M1_Backward()		{	M1_ENA = 1;	M1_ENB = 0;}

# define M2_Backward()		{	M2_ENA = 0;	M2_ENB = 1;}
																													

# define Robot_Ahead()		{	M1_Ahead();	M2_Ahead();}

														
# define Robot_Backward()	{	M1_Backward(); M2_Backward();}

/* Direction definition */
typedef enum{POSITIVE = 0x00,
						 NEGETIVE, 
						 FRONT_LEFT, 
						 FRONT_RIGHT,
						 BACK_LEFT,
						 BACK_RIGHT}ROBOT_POS_ENUM;
/* The robot structure defines the basic properties of the robot */
typedef struct{
	uint8_t dirction;			/* dirctio of Robot */
	uint8_t RobotMode;    /* Robot mode */
	uint8_t M1_Dirction, M2_Dirction; /* The direction of rotation of the motor */
	uint32_t M1_pwm,M2_pwm;  /* Motor PWM */
	uint8_t HandDirction;    /* Head direction, indicating upper body movements */
	uint32_t ModeSpeed;      /* Mode speed, different mode forward speed is different */
	
	uint8_t IsChess;  /* Whether the chess is detected, the variable is only valid for the push chess mode */
	uint8_t IsEdge;  /* Whether the edge is detected */
	
	int IsPosChange;
}Robot_Dev;
	
											
void robot_MotorConfig(void);
void robot_MotorPWMConfig(void);
void robot_MotorControlConfig(void);
void robot_MotorStrConfig(void);


void robot_MotorMove(uint16_t time);

void robot_OutOfBounds(uint8_t RobotPos);

//void robot_FrontLeftOut(void);
//void robot_FrontRightOut(void);
//void robot_BackLeftOut(void);
//void robot_BackRightOut(void);
void robot_UpPlatform(void);
									
//void robot_WaitChessFail(uint8_t ChessPos);

void robot_SetDirction(void);


# endif
