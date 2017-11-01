# ifndef __BSP_USART_H
# define __BSP_USART_H

# include "bsp.h"

# ifdef VECTOR_F1
	# define USART1_EN	1u
	# define USART2_EN  1u
	# define USART3_EN	1u
# else
	# define USART1_EN  1u
	# define USART2_EN  0u
	# define USART3_EN  1u
	# define USART4_EN  0u
	# define USART5_EN	0u
	# define USART6_EN	0u
# endif

# define USART1_AF_EN 0u
# define USART2_AF_EN 0u
# define USART3_AF_EN 0u
# define USART4_AF_EN 0u
# define USART5_AF_EN 0u
# define USART6_AF_EN 0u
	
# if USART1_EN > 0u
	# define USART1_BAUD						9600
	# define USART1_TX_BUFF_SIZE		1*1024
	# define USART1_RX_BUFF_SIZE		1*1024
# endif

# if USART2_EN > 0u
	# define USART2_BAUD						115200
	# define USART2_TX_BUFF_SIZE		1*1024
	# define USART2_RX_BUFF_SIZE		1*1024
# endif

# if USART3_EN > 0u
	# define USART3_BAUD						115200
	# define USART3_TX_BUFF_SIZE		1*1024
	# define USART3_RX_BUFF_SIZE		1*1024
# endif

# if USART4_EN > 0u
	# define USART4_BAUD						115200
	# define USART4_TX_BUFF_SIZE		1*1024
	# define USART4_RX_BUFF_SIZE		1*1024
# endif

# if USART5_EN > 0u
	# define USART5_BAUD						115200
	# define USART5_TX_BUFF_SIZE		1*1024
	# define USART5_RX_BUFF_SIZE		1*1024
# endif

# if USART6_EN > 0u
	# define USART6_BAUD						115200
	# define USART6_TX_BUFF_SIZE		1*1024
	# define USART6_RX_BUFF_SIZE		1*1024
# endif



typedef enum
{
	COM1 = 0x01,
	COM2 = 0x02,
	COM3 = 0x03,
	COM4 = 0x04,
	COM5 = 0x05,
	COM6 = 0x06
}COM_PORT_ENUM;



typedef struct
{
	USART_TypeDef *uart;
	uint8_t *pTxBuff;
	uint8_t *pRxBuff;
	uint16_t TxBuffSize;
	uint16_t RxBuffSize;
	
	__IO uint16_t TxWrite;
	__IO uint16_t TxRead;
	__IO uint16_t TxCount;
	
	__IO uint16_t RxWrite;
	__IO uint16_t RxRead;
	__IO uint16_t RxCount;
	
	void (*_cbSendBefor)(void *p_arg);
	void (*_cbSendOver)(void *p_arg);
	void (*_cbRecvData)(uint8_t byte);
}Usart_Str;


void bsp_UsartConfig(void);
void bsp_UsartGPIOConfig(void);
void bsp_UsartStructConfig(void);
void bsp_UsartNVICConfig(void);
void bsp_UsartPut(Usart_Str * pUsart, uint8_t byte);
void bsp_UsartIRQHandler(Usart_Str * pUsart);
void bsp_UsartClearTxBuff(COM_PORT_ENUM Port);
void bsp_UsartClearRxBuff(COM_PORT_ENUM Port);
void bsp_UsartSendDataToBuff(COM_PORT_ENUM Port, uint8_t *pBuff, uint16_t Lenght);
uint16_t bsp_UsartPrintf(COM_PORT_ENUM Port, const char *format, ...);
uint8_t bsp_UsartGetChar(COM_PORT_ENUM Port, uint8_t *pByte);


USART_TypeDef * bsp_UsartGetPort(COM_PORT_ENUM Port);
Usart_Str *bsp_UsartGetStr(COM_PORT_ENUM Port);
# endif

