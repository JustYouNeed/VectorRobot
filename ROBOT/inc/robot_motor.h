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


											
void robot_MotorConfig(void);
void robot_MotorPWMConfig(void);
void robot_MotorControlConfig(void);
void robot_MotorStrConfig(void);


void robot_MotorMove(uint16_t time);

void robot_OutOfBounds(uint8_t RobotPos);

void robot_UpPlatform(void);

void robot_SetDirction(void);


# endif
