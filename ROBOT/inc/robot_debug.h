# ifndef __ROBOT_DEBUG_H
# define __ROBOT_DEBUG_H

# include "bsp.h"

# define ROBOT_DEBUG_USART		USART1
# define robot_debug		printf


# define ROBOT_DEBUG 								1u

/* �Ƿ��������������ϴ�����  */
# define DEBUG_SENSOR_REPORT				0u

/* �Ƿ������  */
# define DEBUG_MOTOR								1u

/* �Ƿ���Ŀ����  */
# define DEBUG_PERI_DETECT					1u

/* �Ƿ�����ǰ��Ŀ���� */
# define DEBUG_RANG_FRONT_LEFT			1u

/* �Ƿ�����ǰ��Ŀ���� */
# define DEBUG_RANG_FRONT_RIGHT			1u

/* �Ƿ�����ǰ��Ŀ���� */
# define DEBUG_RANG_FRONT						1u

/* �Ƿ������Ŀ���� */
# define DEBUG_RANG_LEFT						1u

/* �Ƿ����ұ�Ŀ����  */
# define DEBUG_RANG_RIGHT						1u

/* �Ƿ������Ŀ����  */
# define DEBUG_RANG_BACK_LEFT				1u

/* �Ƿ����Һ�Ŀ����  */
# define DEBUG_RANG_BACK_RIGHT			1u


# define DEBUG_RANG_BACK						1u


void robot_DebugConfig(void);
void robot_DebugRanging(void);
void robot_DebugPho(void);
void robot_DebugGray(void);

void robot_DebugTimerConfig(void);
void robot_DataReport(void);
# endif

