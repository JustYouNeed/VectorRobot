# ifndef __ROBOT_H
# define __ROBOT_H

# include "bsp.h"


# include "robot_motor.h"
# include "robot_detect.h"
# include "robot_servo.h"
# include "robot_debug.h"
# include "robot_sensor.h"



# if ROBOT_DEBUG > 0u
	# if DEBUG_SENSOR_REPORT > 0u
		# include "ano.h"
	# endif
# endif


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
	
	uint16_t FrontLeft_TurnTime;
	uint16_t FrontRight_TurnTime;
	uint16_t Left_TurnTime;
	uint16_t Right_TurnTime;
	uint16_t BackLeft_TurnTime;
	uint16_t BackRight_TurnTime;

	uint16_t FrontLeft_TurnSpeed;
	uint16_t FrontRight_TurnSpeed;
	uint16_t Left_TurnSpeed;
	uint16_t Right_TurnSpeed;
	uint16_t BackLeft_TurnSpeed;
	uint16_t BackRight_TurnSpeed;
	
	uint16_t FrontLeft_EdgeTime;
	uint16_t FrontRight_EdgeTime;
	uint16_t BackLeft_EdgeTime;
	uint16_t BackRight_EdgeTime;
	
	uint16_t FrontLeft_EdgeSpeed;
	uint16_t FrontRight_EdgeSpeed;
	uint16_t BackLeft_EdgeSpeed;
	uint16_t BackRight_EdgeSpeed;
}Robot_Dev;
	

extern Robot_Dev Robot;	


void robot_ModeSwitchConfig(void);
uint8_t robot_GetMode(void);

void robot_Config(void);
void robot_ShowState(void);
# endif


