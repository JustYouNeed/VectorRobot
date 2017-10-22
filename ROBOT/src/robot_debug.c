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
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///使能TIM3时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = 5000-1; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 8400 - 1;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM3,ENABLE); //使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

//定时器3中断服务函数
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
	{
	//	printf("hello\r\n");

		LED1=~LED1;//DS1翻转
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位
}
# endif


