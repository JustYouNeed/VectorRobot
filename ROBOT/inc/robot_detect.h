# ifndef __ROBOT_CHESS_H
# define __ROBOT_CHESS_H

# include "bsp.h"



# define DISTANCE							110
# define IsRangDetected(RangId)  (((ADC1ConvValue[RangId]>>4) > DISTANCE)?1:0)




void robot_DetectConfig(void);


void robot_PeriDetect(void);
void robot_EgdeDetect(void);

void robot_Detect(void);

uint8_t IsPhoDetected(uint8_t PhoId);

void robot_UndetectEdge(void);
void robot_IsPosChange(void);
//uint8_t IsRangDetected(uint8_t RangId);



# endif
