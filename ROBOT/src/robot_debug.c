# include "robot.h"

void robot_DebugConfig(void)
{
# if DEBUG_SENSOR_REPORT > 0u
	robot_DebugTimerConfig();
	ANO_Init(115200);
# endif
}

void robot_DebugRanging(void)
{
	robot_debug("\r\n");
	robot_debug("======== Robot Raging Debug Infomation ========\t\r\n");
	robot_debug("==            A:%d      B:%d      C:%d      ==\t\r\n ",ADC1ConvValue[ROBOT_RANG_A] >> 4, ADC1ConvValue[ROBOT_RANG_B] >> 4,ADC1ConvValue[ROBOT_RANG_C] >> 4);
	robot_debug("==                                           ==\r\n");
	robot_debug("==          H:%d                      D:%d     ==\r\n ",ADC1ConvValue[ROBOT_RANG_H] >> 4, ADC1ConvValue[ROBOT_RANG_D] >> 4);
	robot_debug("==                                           ==\r\n");
	robot_debug("==            I:%d      J:%d      K:%d      ==\r\n ",ADC1ConvValue[ROBOT_RANG_I] >> 4, ADC1ConvValue[ROBOT_RANG_J] >> 4,ADC1ConvValue[ROBOT_RANG_K] >> 4);
	robot_debug("\r\n");
	robot_debug("\r\n");
}

void robot_DebugGray(void)
{
	robot_debug("\r\n");
	robot_debug("======== Robot Gray Debug Infomation ========\t\r\n");
	robot_debug("===    Robot Gray:%d                      ===\r\n",ADC1ConvValue[ROBOT_GRAY]>>4);
	robot_debug("\r\n");
	robot_debug("\r\n");
}

void robot_DebugPho(void)
{
	robot_debug("\r\n");
	robot_debug("======== Robot Pho Debug Infomation ========\t\r\n");
	robot_debug("==       B:%d      C:%d      D:%d         ==\r\n", IsPhoDetected(ROBOT_PHO_B),IsPhoDetected(ROBOT_PHO_C), IsPhoDetected(ROBOT_PHO_D));
	robot_debug("==                                        ==\r\n");
	robot_debug("==  A:%d                            E:%d  ==\r\n", IsPhoDetected(ROBOT_PHO_A),IsPhoDetected(ROBOT_PHO_E));
	robot_debug("==                                        ==\r\n");
	robot_debug("==  H:%d                            L:%d  ==\r\n", IsPhoDetected(ROBOT_PHO_H),IsPhoDetected(ROBOT_PHO_L));
	robot_debug("==                                        ==\r\n");
	robot_debug("==       I:%d      J:%d      K:%d         ==\r\n", IsPhoDetected(ROBOT_PHO_I),IsPhoDetected(ROBOT_PHO_J), IsPhoDetected(ROBOT_PHO_K));
}

void robot_DataReport(void)
{
//					ANO_SenserDataUpload(ADC1ConvValue[ROBOT_RANG_A]>>4, ADC1ConvValue[ROBOT_RANG_B]>>4, ADC1ConvValue[ROBOT_RANG_C]>>4,
//		                     ADC1ConvValue[ROBOT_RANG_D]>>4, ADC1ConvValue[ROBOT_RANG_H]>>4, ADC1ConvValue[ROBOT_RANG_I]>>4,
//		                     ADC1ConvValue[ROBOT_RANG_J]>>4, ADC1ConvValue[ROBOT_RANG_K]>>4, 0);
}

# if DEBUG_SENSOR_REPORT > 0u
void robot_DebugTimerConfig(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = 5000-1; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = 8400 - 1;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

//��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�
	{
	//	printf("hello\r\n");

		LED1=~LED1;//DS1��ת
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ
}
# endif


