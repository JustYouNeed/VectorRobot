# ifndef __ROBOT_DEBUG_H
# define __ROBOT_DEBUG_H

# include "bsp.h"

# define ROBOT_DEBUG_USART		USART1
# define robot_debug		printf


# define ROBOT_DEBUG 								1u

/* 是否开启传感器数据上传功能  */
# define DEBUG_SENSOR_REPORT				0u

/* 是否开启电机  */
# define DEBUG_MOTOR								1u

/* 是否开启目标检测  */
# define DEBUG_PERI_DETECT					1u

/* 是否开启左前方目标检测 */
# define DEBUG_RANG_FRONT_LEFT			1u

/* 是否开启右前方目标检测 */
# define DEBUG_RANG_FRONT_RIGHT			1u

/* 是否开启正前方目标检测 */
# define DEBUG_RANG_FRONT						1u

/* 是否开启左边目标检测 */
# define DEBUG_RANG_LEFT						1u

/* 是否开启右边目标检测  */
# define DEBUG_RANG_RIGHT						1u

/* 是否开启左后方目标检测  */
# define DEBUG_RANG_BACK_LEFT				1u

/* 是否开启右后方目标检测  */
# define DEBUG_RANG_BACK_RIGHT			1u


# define DEBUG_RANG_BACK						1u


void robot_DebugConfig(void);
void robot_DebugRanging(void);
void robot_DebugPho(void);
void robot_DebugGray(void);

void robot_DebugTimerConfig(void);
void robot_DataReport(void);
# endif

