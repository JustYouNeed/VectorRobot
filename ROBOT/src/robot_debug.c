# include "robot.h"

void robot_DebugConfig(void)
{
}





void robot_DataReport(void)
{
//	uint8_t temp1, temp2, temp3 = 0x00;
//	bsp_UsartSendDataToBuff(COM1,(uint8_t*)"RANG A:",strlen("RANG A:"));
//	temp = (ADC1ConvValue[ROBOT_RANG_A]>>4);
//	bsp_UsartSendDataToBuff(COM1, &temp, 1);
//	
//	bsp_UsartSendDataToBuff(COM1,(uint8_t*)"    RANG B:",strlen("    RANG B:"));
//	temp = (ADC1ConvValue[ROBOT_RANG_B]>>4);
//	bsp_UsartSendDataToBuff(COM1, &temp, 1);
//	
//	bsp_UsartSendDataToBuff(COM1,(uint8_t*)"    RANG C:",strlen("    RANG C:"));
//	temp = (ADC1ConvValue[ROBOT_RANG_C]>>4);
//	bsp_UsartSendDataToBuff(COM1, &temp, 1);
//	bsp_UsartSendDataToBuff(COM1, (uint8_t*)"\r\n",2);
//	
//	bsp_UsartSendDataToBuff(COM1,(uint8_t*)"RANG H:",strlen("RANG H:"));
//	temp = (ADC1ConvValue[ROBOT_RANG_H]>>4);
//	bsp_UsartSendDataToBuff(COM1, &temp, 1);
//	
//	bsp_UsartSendDataToBuff(COM1,(uint8_t*)"    RANG I:",strlen("    RANG I:"));
//	temp = (ADC1ConvValue[ROBOT_RANG_I]>>4);
//	bsp_UsartSendDataToBuff(COM1, &temp, 1);
//	
//	bsp_UsartSendDataToBuff(COM1,(uint8_t*)"    RANG J:",strlen("    RANG J:"));
//	temp = (ADC1ConvValue[ROBOT_RANG_J]>>4);
//	bsp_UsartSendDataToBuff(COM1, &temp, 1);
//	bsp_UsartSendDataToBuff(COM1, (uint8_t*)"\r\n",2);
	
	bsp_UsartPrintf(COM1, "A:%d   B:%d   C:%d\r\nH:%d  I:%d   J:%d\r\n\r\n",
								(ADC1ConvValue[ROBOT_RANG_A]>>4), 
								(ADC1ConvValue[ROBOT_RANG_B]>>4), 
								(ADC1ConvValue[ROBOT_RANG_C]>>4),
								(ADC1ConvValue[ROBOT_RANG_H]>>4),
								(ADC1ConvValue[ROBOT_RANG_I]>>4),
								(ADC1ConvValue[ROBOT_RANG_J]>>4));
	
}



