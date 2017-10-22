# include "bsp.h"
# include "stdio.h"
#include <stdarg.h>
//# include "string.h"
uint8_t isUartRxCompleted;





/* ���ʹ�ܴ���1�����崮��1������ */
# if USART1_EN > 0u
	static Usart_Str Usart1_Info;
	static uint8_t Usart1TxBuff[USART1_TX_BUFF_SIZE];
	static uint8_t Usart1RxBuff[USART1_RX_BUFF_SIZE];
# endif

/* ���ʹ�ܴ���2�����崮��2������ */
# if USART2_EN > 0u
	static Usart_Str Usart2_Info;
	static uint8_t Usart2TxBuff[USART2_TX_BUFF_SIZE];
	static uint8_t Usart2RxBuff[USART2_RX_BUFF_SIZE];
# endif
/* ���ʹ�ܴ���3�����崮��3������ */
# if USART3_EN > 0u
	static Usart_Str Usart3_Info;
	static uint8_t Usart3TxBuff[USART3_TX_BUFF_SIZE];
	static uint8_t Usart3RxBuff[USART3_RX_BUFF_SIZE];
# endif
/* ���ʹ�ܴ���4�����崮��4������ */
# if USART4_EN > 0u
	static Usart_Str Usart4_Info;
	static uint8_t Usart4TxBuff[USART4_TX_BUFF_SIZE];
	static uint8_t Usart4RxBuff[USART4_RX_BUFF_SIZE];
# endif
/* ���ʹ�ܴ���6�����崮��5������ */
# if USART5_EN > 0u
	static Usart_Str Usart5_Info;
	static uint8_t Usart5TxBuff[USART5_TX_BUFF_SIZE];
	static uint8_t Usart5RxBuff[USART5_RX_BUFF_SIZE];
# endif
/* ���ʹ�ܴ���6�����崮��6������ */
# if USART6_EN > 0u
	static Usart_Str Usart6_Info;
	static uint8_t Usart6TxBuff[USART6_TX_BUFF_SIZE];
	static uint8_t Usart6RxBuff[USART6_RX_BUFF_SIZE];
# endif




USART_TypeDef * bsp_UsartGetPort(COM_PORT_ENUM Port)
{	
	if(Port == COM1)
	{
		# if USART1_EN > 0u
			return USART1;
		# else
			return 0;
		# endif
	}
	else 	if(Port == COM2)
	{
		# if USART2_EN > 0u
			return USART2;
		# else
			return 0;
		# endif
	}
	else 	if(Port == 3)
	{
		# if USART3_EN > 0u
			return USART3;
		# else
			return 0;
		# endif
	}
	else 	if(Port == COM4)
	{
		# if USART4_EN > 0u
			return USART4;
		# else
			return 0;
		# endif
	}
	else 	if(Port == COM5)
	{
		# if USART5_EN > 0u
			return USART5;
		# else
			return 0;
		# endif
	}
	else 	if(Port == COM6)
	{
		# if USART6_EN > 0u
			return USART6;
		# else
			return 0;
		# endif
	}
	
	return 0;
}

Usart_Str *bsp_UsartGetStr(COM_PORT_ENUM Port)
{
		if(Port == COM1)
	{
		# if USART1_EN > 0u
			return &Usart1_Info;
		# else
			return 0;
		# endif
	}
	else 	if(Port == COM2)
	{
		# if USART2_EN > 0u
			return &Usart1_Info;
		# else
			return 0;
		# endif
	}
	else 	if(Port == COM3)
	{
		# if USART3_EN > 0u
			return &Usart1_Info;
		# else
			return 0;
		# endif
	}
	else 	if(Port == COM4)
	{
		# if USART4_EN > 0u
			return &Usart1_Info;
		# else
			return 0;
		# endif
	}
	else 	if(Port == COM5)
	{
		# if USART5_EN > 0u
			return &Usart1_Info;
		# else
			return 0;
		# endif
	}
	else 	if(Port == COM6)
	{
		# if USART6_EN > 0u
			return &Usart1_Info;
		# else
			return 0;
		# endif
	}
	
	return 0;
}

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
void bsp_UsartSendDataToBuff(COM_PORT_ENUM Port, uint8_t *pBuff, uint16_t Lenght)
{
	Usart_Str * SendUsart;
	uint16_t i = 0;
	SendUsart = bsp_UsartGetStr(Port);
	if(SendUsart == 0) return ;
	
	for (i = 0; i < Lenght; i++)
	{
			/* ������ͻ�������Ϊ�յĻ����ȴ����ͻ��������� */
		while(1)
		{
			__IO uint16_t Count;
			
			DISABLE_INT();
			Count = SendUsart->TxCount;
			ENABLE_INT();
			
			if(Count < SendUsart->TxBuffSize) break;
		}
		
		SendUsart->pTxBuff[SendUsart->TxWrite] = pBuff[i];
		
		DISABLE_INT();
		if(++ SendUsart->TxWrite >= SendUsart->TxBuffSize)
		{
			SendUsart->TxWrite = 0;
		}
		SendUsart->TxCount ++;
		ENABLE_INT();
	}
	USART_ITConfig(SendUsart->uart, USART_IT_TXE, ENABLE);
}
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
uint8_t bsp_UsartGetChar(COM_PORT_ENUM Port, uint8_t *pByte)
{
	Usart_Str * pUsart;
	
	uint16_t Count;
	pUsart = bsp_UsartGetStr(Port);
	
	DISABLE_INT();
	Count = pUsart->RxCount;
	ENABLE_INT();
	
	if(Count == 0)	return 0;
	else
	{
		*pByte = pUsart->pRxBuff[pUsart->RxRead];
		//printf("%c",*pByte);
		DISABLE_INT();
		if(++ pUsart->RxRead >= pUsart->RxBuffSize)
			pUsart->RxRead = 0;
		
		pUsart->RxCount -- ;
		ENABLE_INT();
		return 1;
	}
}

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
void bsp_UsartClearTxBuff(COM_PORT_ENUM Port)
{
	Usart_Str *pUsart;
	pUsart = bsp_UsartGetStr(Port);
	
	if(pUsart == 0) return ;
	pUsart->TxCount = 0;
	pUsart->TxRead = 0;
	pUsart->TxWrite = 0;
}

void bsp_UsartClearRxBuff(COM_PORT_ENUM Port)
{
	Usart_Str *pUsart;
	pUsart = bsp_UsartGetStr(Port);
	
	if(pUsart == 0) return ;
	pUsart->RxCount = 0;
	pUsart->RxRead = 0;
	pUsart->RxWrite = 0;
}

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
void bsp_UsartConfig(void)
{
	bsp_UsartStructConfig();   /* �����ȳ�ʼ����ؽṹ������ */
	bsp_UsartGPIOConfig();   /* �������ų�ʼ�� */
	bsp_UsartNVICConfig();   /* �����жϳ�ʼ�� */
}

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
void bsp_UsartStructConfig(void)
{
# if USART1_EN > 0u
	Usart1_Info.uart = USART1;
	Usart1_Info.pTxBuff = Usart1TxBuff;
	Usart1_Info.pRxBuff = Usart1RxBuff;
	Usart1_Info.RxBuffSize = USART1_RX_BUFF_SIZE;
	Usart1_Info.TxBuffSize = USART1_TX_BUFF_SIZE;
	Usart1_Info.RxWrite = 0;
	Usart1_Info.RxRead = 0;
	Usart1_Info.RxCount  = 0;
	Usart1_Info.TxCount = 0;
	Usart1_Info._cbRecvData = 0;
	Usart1_Info._cbSendBefor = 0;
	Usart1_Info._cbSendOver = 0;
# endif

# if USART2_EN > 0u
	Usart2_Info.uart = USART2;
	Usart2_Info.pTxBuff = Usart2TxBuff;
	Usart2_Info.pRxBuff = Usart2RxBuff;
	Usart2_Info.RxBuffSize = USART2_RX_BUFF_SIZE;
	Usart2_Info.TxBuffSize = USART2_TX_BUFF_SIZE;
	Usart2_Info.RxWrite = 0;
	Usart2_Info.RxRead = 0;
	Usart2_Info.RxCount  = 0;
	Usart2_Info.TxCount = 0;
	Usart2_Info._cbRecvData = 0;
	Usart2_Info._cbSendBefor = 0;
	Usart2_Info._cbSendOver = 0;
# endif
	
# if USART3_EN > 0u
	Usart3_Info.uart = USART3;
	Usart3_Info.pTxBuff = Usart3TxBuff;
	Usart3_Info.pRxBuff = Usart3RxBuff;
	Usart3_Info.RxBuffSize = USART3_RX_BUFF_SIZE;
	Usart3_Info.TxBuffSize = USART3_TX_BUFF_SIZE;
	Usart3_Info.RxWrite = 0;
	Usart3_Info.RxRead = 0;
	Usart3_Info.RxCount  = 0;
	Usart3_Info.TxCount = 0;
	Usart3_Info._cbRecvData = 0;
	Usart3_Info._cbSendBefor = 0;
	Usart3_Info._cbSendOver = 0;
# endif
	
# if USART4_EN > 0u
	Usart4_Info.uart = USART4;
	Usart4_Info.pTxBuff = Usart4TxBuff;
	Usart4_Info.pRxBuff = Usart4RxBuff;
	Usart4_Info.RxBuffSize = USART4_RX_BUFF_SIZE;
	Usart4_Info.TxBuffSize = USART4_TX_BUFF_SIZE;
	Usart4_Info.RxWrite = 0;
	Usart4_Info.RxRead = 0;
	Usart4_Info.RxCount  = 0;
	Usart4_Info.TxCount = 0;
	Usart4_Info._cbRecvData = 0;
	Usart4_Info._cbSendBefor = 0;
	Usart4_Info._cbSendOver = 0;
# endif
	
# if USART5_EN > 0u
	Usart5_Info.uart = USART5;
	Usart5_Info.pTxBuff = Usart5TxBuff;
	Usart5_Info.pRxBuff = Usart5RxBuff;
	Usart5_Info.RxBuffSize = USART5_RX_BUFF_SIZE;
	Usar5_Info.TxBuffSize = USART5_TX_BUFF_SIZE;
	Usart5_Info.RxWrite = 0;
	Usart5_Info.RxRead = 0;
	Usart5_Info.RxCount  = 0;
	Usart5_Info.TxCount = 0;
	Usart5_Info._cbRecvData = 0;
	Usart5_Info._cbSendBefor = 0;
	Usart5_Info._cbSendOver = 0;
# endif
	
# if USART6_EN > 0u
	Usart6_Info.uart = USART6;
	Usart6_Info.pTxBuff = Usart6TxBuff;
	Usart6_Info.pRxBuff = Usart6RxBuff;
	Usart6_Info.RxBuffSize = USART6_RX_BUFF_SIZE;
	Usart6_Info.TxBuffSize = USART6_TX_BUFF_SIZE;
	Usart6_Info.RxWrite = 0;
	Usart6_Info.RxRead = 0;
	Usart6_Info.RxCount  = 0;
	Usart6_Info.TxCount = 0;
	Usart6_Info._cbRecvData = 0;
	Usart6_Info._cbSendBefor = 0;
	Usart6_Info._cbSendOver = 0;
# endif
}

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
void bsp_UsartGPIOConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
# if USART1_EN > 0u
	# if USART1_AF_EN < 1u
		# ifdef VECTOR_F1			 
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
			
			//USART1_TX   GPIOA.9
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
			GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
			 
			//USART1_RX	  GPIOA.10��ʼ��
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
			GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  
		# else
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
			
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
			GPIO_PinAFConfig(GPIOA, GPIO_PinSource9,  GPIO_AF_USART1);
			GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
			
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	/* �������Ϊ���� */
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	/* �ڲ���������ʹ�� */
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	/* ����ģʽ */

			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOA, &GPIO_InitStructure);

			/* ���� USART Rx Ϊ���ù��� */
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
	  # endif
	# else
		# ifdef VECTOR_F1
		# else
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
			GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
			GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
			
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	/* �������Ϊ���� */
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	/* �ڲ���������ʹ�� */
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	/* ����ģʽ */

			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOB, &GPIO_InitStructure);

			/* ���� USART Rx Ϊ���ù��� */
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
			GPIO_Init(GPIOB, &GPIO_InitStructure);
		# endif
	# endif
	
		/* ��2���� ���ô���Ӳ������ */
	USART_InitStructure.USART_BaudRate = USART1_BAUD;	/* ������ */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	/* ʹ�ܽ����ж� */
	/*
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		ע��: ��Ҫ�ڴ˴��򿪷����ж�
		�����ж�ʹ����SendUart()������
	*/
	USART_Cmd(USART1, ENABLE);		/* ʹ�ܴ��� */

	/* CPU��Сȱ�ݣ��������úã����ֱ��Send�����1���ֽڷ��Ͳ���ȥ
		�����������1���ֽ��޷���ȷ���ͳ�ȥ������ */
	USART_ClearFlag(USART1, USART_FLAG_TC);     /* �巢����ɱ�־��Transmission Complete flag */
# endif
	
# if USART2_EN > 0u
	# if USART2_AF_EN < 1u
		# ifdef VECTOR_F1
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
			
			//USART2_TX   GPIOA.2
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.9
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
			GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
			 
			//USART2_RX	  GPIOA.3��ʼ��
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
			GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  
		# else
				/* �� GPIO ʱ�� */
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

			/* �� UART ʱ�� */
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

			/* �� PD5 ӳ��Ϊ USART2_TX */
			GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);

			/* �� PD6 ӳ��Ϊ USART2_RX */
			GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);

			/* ���� USART Tx Ϊ���ù��� */
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	/* �������Ϊ���� */
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	/* �ڲ���������ʹ�� */
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	/* ����ģʽ */

			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOD, &GPIO_InitStructure);

			/* ���� USART Rx Ϊ���ù��� */
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
			GPIO_Init(GPIOD, &GPIO_InitStructure);
		# endif
	# else
		# ifdef VECTOR_F1
		# else
						/* �� GPIO ʱ�� */
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

			/* �� UART ʱ�� */
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

			/* �� PA2 ӳ��Ϊ USART2_TX. ��STM32-V5���У�PA2 �ܽ�������̫�� */
			//GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);

			/* �� PA3 ӳ��Ϊ USART2_RX */
			GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

			/* ���� USART Tx Ϊ���ù��� */
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	/* �������Ϊ���� */
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	/* �ڲ���������ʹ�� */
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	/* ����ģʽ */

			//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
			//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			//GPIO_Init(GPIOA, &GPIO_InitStructure);

			/* ���� USART Rx Ϊ���ù��� */
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
		# endif
	# endif
	
		/* ��2���� ���ô���Ӳ������ */
	USART_InitStructure.USART_BaudRate = USART2_BAUD;	/* ������ */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx;		/* ��ѡ�����ģʽ */
	USART_Init(USART2, &USART_InitStructure);

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	/* ʹ�ܽ����ж� */
	/*
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		ע��: ��Ҫ�ڴ˴��򿪷����ж�
		�����ж�ʹ����SendUart()������
	*/
	USART_Cmd(USART2, ENABLE);		/* ʹ�ܴ��� */

	/* CPU��Сȱ�ݣ��������úã����ֱ��Send�����1���ֽڷ��Ͳ���ȥ
		�����������1���ֽ��޷���ȷ���ͳ�ȥ������ */
	USART_ClearFlag(USART2, USART_FLAG_TC);     /* �巢����ɱ�־��Transmission Complete flag */
# endif
	
# if USART3_EN > 0u
	# ifdef VECTOR_F1
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//ʹ��USART1��GPIOAʱ��
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
		//USART3_TX   GPIOB.10
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PB.10
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
		GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB.9
		 
		//USART3_RX	  GPIOB.11��ʼ��
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PB11
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
		GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB.11 
	# else
		/* �� GPIO ʱ�� */
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

		/* �� UART ʱ�� */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

		/* �� PB10 ӳ��Ϊ USART3_TX */
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);

		/* �� PB11 ӳ��Ϊ USART3_RX */
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);

		/* ���� USART Tx Ϊ���ù��� */
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	/* �������Ϊ���� */
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	/* �ڲ���������ʹ�� */
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	/* ����ģʽ */

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);

		/* ���� USART Rx Ϊ���ù��� */
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	# endif
		/* ��2���� ���ô���Ӳ������ */
	USART_InitStructure.USART_BaudRate = USART3_BAUD;	/* ������ */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	/* ʹ�ܽ����ж� */
	/*
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		ע��: ��Ҫ�ڴ˴��򿪷����ж�
		�����ж�ʹ����SendUart()������
	*/
	USART_Cmd(USART3, ENABLE);		/* ʹ�ܴ��� */

	/* CPU��Сȱ�ݣ��������úã����ֱ��Send�����1���ֽڷ��Ͳ���ȥ
		�����������1���ֽ��޷���ȷ���ͳ�ȥ������ */
	USART_ClearFlag(USART3, USART_FLAG_TC);     /* �巢����ɱ�־��Transmission Complete flag */
# endif
	
# if USART4_EN > 0u
	# ifdef VECTOR_F1
	# else
			/* �� GPIO ʱ�� */
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

		/* �� UART ʱ�� */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

		/* �� PC10 ӳ��Ϊ UART4_TX */
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART1);

		/* �� PC11 ӳ��Ϊ UART4_RX */
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART1);

		/* ���� USART Tx Ϊ���ù��� */
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	/* �������Ϊ���� */
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	/* �ڲ���������ʹ�� */
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	/* ����ģʽ */

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);

		/* ���� USART Rx Ϊ���ù��� */
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
	# endif
		/* ��2���� ���ô���Ӳ������ */
	USART_InitStructure.USART_BaudRate = UART1_BAUD;	/* ������ */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART4, &USART_InitStructure);

	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);	/* ʹ�ܽ����ж� */
	/*
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		ע��: ��Ҫ�ڴ˴��򿪷����ж�
		�����ж�ʹ����SendUart()������
	*/
	USART_Cmd(UART4, ENABLE);		/* ʹ�ܴ��� */

	/* CPU��Сȱ�ݣ��������úã����ֱ��Send�����1���ֽڷ��Ͳ���ȥ
		�����������1���ֽ��޷���ȷ���ͳ�ȥ������ */
	USART_ClearFlag(UART4, USART_FLAG_TC);     /* �巢����ɱ�־��Transmission Complete flag */
# endif

# if USART5_EN > 0u
	# ifdef VECTOR_F1
	# else
			/* �� GPIO ʱ�� */
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC |RCC_AHB1Periph_GPIOD, ENABLE);

		/* �� UART ʱ�� */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);

		/* �� PC12 ӳ��Ϊ UART5_TX */
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);

		/* �� PD2 ӳ��Ϊ UART5_RX */
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);

		/* ���� UART Tx Ϊ���ù��� */
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	/* �������Ϊ���� */
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	/* �ڲ���������ʹ�� */
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	/* ����ģʽ */

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);

		/* ���� UART Rx Ϊ���ù��� */
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
		GPIO_Init(GPIOD, &GPIO_InitStructure);
	# endif
		/* ��2���� ���ô���Ӳ������ */
	USART_InitStructure.USART_BaudRate = UART5_BAUD;	/* ������ */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART5, &USART_InitStructure);

	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);	/* ʹ�ܽ����ж� */
	/*
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		ע��: ��Ҫ�ڴ˴��򿪷����ж�
		�����ж�ʹ����SendUart()������
	*/
	USART_Cmd(UART5, ENABLE);		/* ʹ�ܴ��� */

	/* CPU��Сȱ�ݣ��������úã����ֱ��Send�����1���ֽڷ��Ͳ���ȥ
		�����������1���ֽ��޷���ȷ���ͳ�ȥ������ */
	USART_ClearFlag(UART5, USART_FLAG_TC);     /* �巢����ɱ�־��Transmission Complete flag */
# endif
	
# if USART6_EN > 0u
	# ifdef VECTOR_F1
	# else
			/* �� GPIO ʱ�� */
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC |RCC_AHB1Periph_GPIOG, ENABLE);

		/* �� UART ʱ�� */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

		/* �� PG14 ӳ��Ϊ USART6_TX */
		GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_USART6);

		/* �� PC7 ӳ��Ϊ USART6_RX */
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);

		/* �� PG8 ӳ��Ϊ USART6_RTS */
		GPIO_PinAFConfig(GPIOG, GPIO_PinSource8, GPIO_AF_USART6);

		/* �� PG15 ӳ��Ϊ USART6_CTS */
		GPIO_PinAFConfig(GPIOG, GPIO_PinSource15, GPIO_AF_USART6);

		/* ���� PG14/USART6_TX Ϊ���ù��� */
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	/* �������Ϊ���� */
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	/* �ڲ���������ʹ�� */
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	/* ����ģʽ */

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOG, &GPIO_InitStructure);

		/* ���� PC7/USART6_RX Ϊ���ù��� */
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
		GPIO_Init(GPIOC, &GPIO_InitStructure);

		/* ���� PG8/USART6_RTS Ϊ���ù��� */
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
		GPIO_Init(GPIOG, &GPIO_InitStructure);

		/* ���� PG15/USART6_CTS Ϊ���ù��� */
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
		GPIO_Init(GPIOG, &GPIO_InitStructure);
	# endif
		/* ��2���� ���ô���Ӳ������ */
	USART_InitStructure.USART_BaudRate = UART6_BAUD;	/* ������ */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	//USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS_CTS;	/* ѡ��Ӳ������ */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	/* ��ҪӲ������ */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART6, &USART_InitStructure);

	USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);	/* ʹ�ܽ����ж� */
	/*
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		ע��: ��Ҫ�ڴ˴��򿪷����ж�
		�����ж�ʹ����SendUart()������
	*/
	USART_Cmd(USART6, ENABLE);		/* ʹ�ܴ��� */

	/* CPU��Сȱ�ݣ��������úã����ֱ��Send�����1���ֽڷ��Ͳ���ȥ
		�����������1���ֽ��޷���ȷ���ͳ�ȥ������ */
	USART_ClearFlag(USART6, USART_FLAG_TC);     /* �巢����ɱ�־��Transmission Complete flag */
# endif
}



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
void bsp_UsartNVICConfig(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
# if USART1_EN > 0u
		/* ʹ�ܴ���1�ж� */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 13;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
# endif
	
# if USART2_EN > 0u
		/* ʹ�ܴ���2�ж� */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 13;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
# endif

	
# if USART3_EN > 0u
	/* ʹ�ܴ���3�ж�t */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 13;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
# endif

	
# if USART4_EN > 0u
	/* ʹ�ܴ���4�ж�t */
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 13;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
# endif

	
# if USART5_EN > 0u
	/* ʹ�ܴ���5�ж�t */
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 13;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
# endif

	
# if USART6_EN > 0u
	/* ʹ�ܴ���6�ж�t */
	NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 13;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
# endif
}






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
void bsp_UsartPut(Usart_Str * pUsart, uint8_t byte)
{
	pUsart->pRxBuff[pUsart->RxWrite] = byte;
	if(++ pUsart->RxWrite >= pUsart->RxBuffSize)
		pUsart->RxWrite = 0;
	if(pUsart->RxCount < pUsart->RxBuffSize)
		pUsart->RxCount ++;
}
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
void bsp_UsartIRQHandler(Usart_Str * pUsart)
{
	uint8_t RecvByte;
	/* ������ڽ��յ����� */
	if(USART_GetITStatus(pUsart->uart, USART_IT_RXNE) == SET)
	{
		/* �Ӵ��ڻ������������� */
		RecvByte = USART_ReceiveData(pUsart->uart);
		bsp_UsartPut(pUsart, RecvByte);
	}
	
	if(USART_GetITStatus(pUsart->uart, USART_IT_TXE) != RESET)
	{
		if(pUsart->TxCount == 0)
		{
			USART_ITConfig(pUsart->uart, USART_IT_TXE, DISABLE);
			USART_ITConfig(pUsart->uart, USART_IT_TC, ENABLE);
		}
		else
		{
			USART_SendData(pUsart->uart, pUsart->pTxBuff[pUsart->TxRead]);
			if(++ pUsart->TxRead >= pUsart->TxBuffSize)
			{
				pUsart->TxRead = 0;
			}
			pUsart->TxCount --;
		}
	}
	else if(USART_GetITStatus(pUsart->uart, USART_IT_TC) != RESET)
	{
		if(pUsart->TxCount == 0)
		{
			USART_ITConfig(pUsart->uart, USART_IT_TC, DISABLE);
			if(pUsart->_cbSendOver)
				pUsart->_cbSendOver(0);
		}
		else
		{
			USART_SendData(pUsart->uart, pUsart->pTxBuff[pUsart->TxRead]);
			if(++ pUsart->TxRead >= pUsart->TxBuffSize)
				pUsart->TxRead = 0;
			pUsart->TxCount --;
		}
	}
	
}


# if USART1_EN > 0u
void USART1_IRQHandler(void)
{
	bsp_UsartIRQHandler(&Usart1_Info);
	
}
# endif

# if USART2_EN > 0u
void USART2_IRQHandler(void)
{
	bsp_UsartIRQHandler(&Usart2_Info);
	
}
# endif

# if USART3_EN > 0u
void USART3_IRQHandler(void)
{
	bsp_UsartIRQHandler(&Usart3_Info);
	
}
# endif

# if USART4_EN > 0u
void USART4_IRQHandler(void)
{
	bsp_UsartIRQHandler(&Usart4_Info);
	
}
# endif

# if USART5_EN > 0u
void USART5_IRQHandler(void)
{
	bsp_UsartIRQHandler(&Usart5_Info);
	
}
# endif

# if USART6_EN > 0u
void USART6_IRQHandler(void)
{
	bsp_UsartIRQHandler(&Usart6_Info);
	
}
# endif


uint16_t bsp_UsartPrintf(COM_PORT_ENUM Port, const char *format, ...)
{
	uint16_t i = 0;
	char buf[256];
	
	va_list arg;// = (va_list)((char *)(&format) + 4);
	va_start(arg ,format);
	
	i = vsprintf(buf, format, arg);
	
	bsp_UsartSendDataToBuff(Port, buf, i);
	
	va_end(arg);
	return i;
}





