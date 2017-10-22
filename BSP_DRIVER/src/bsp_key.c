# include "bsp.h"


# ifdef	VECTOR_F1
	static uint8_t IsKeyUpPress(void) { return ((KEY_UP_PORT->IDR & KEY_UP_PIN) == 0)?1:0;}
	static uint8_t IsKeyOkPress(void) { return ((KEY_OK_PORT->IDR & KEY_OK_PIN) == 0)?1:0;}
	static uint8_t IsKeyDownPress(void) { return ((KEY_DOWN_PORT->IDR & KEY_DOWN_PIN) == 0)?1:0;}
# else
	static uint8_t IsKeyUpPress(void) { return ((KEY_UP_PORT->IDR & KEY_UP_PIN) == 0)?1:0;}
	static uint8_t IsKeyOkPress(void) { return ((KEY_OK_PORT->IDR & KEY_OK_PIN) == 0)?1:0;}
	static uint8_t IsKeyDownPress(void) { return ((KEY_DOWN_PORT->IDR & KEY_DOWN_PIN) == 0)?1:0;}
# endif


static Key_Fifo_Str		 bsp_key_fifo;   /* the key fifo struct */
static Key_Str		     bsp_key[BSP_KEY_COUNT];  /* struct of each key */

/*
*********************************************************************************************************
*                                        bsp_KeyConfig  
*
* Description: Configure the key
*             
* Arguments : None.
*
* Note(s)   : None. 
*********************************************************************************************************
*/
void bsp_KeyConfig(void)
{
	bsp_KeyGPIOConfig();/*  Configure the GPIO port for the key  */
	bsp_KeyFifoConfig();/*  Initialize the key FIFO   */
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
void bsp_KeyGPIOConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*If you are using the F1 series of chips*/
# ifdef	VECTOR_F1
	RCC_APB2PeriphClockCmd(RCC_KEY_ALL, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	/*If you are using the F4 series of chips*/
# elif defined	VECTOR_F4
	/*Enable the clock*/
	RCC_AHB1PeriphClockCmd(RCC_KEY_ALL, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
# endif
	GPIO_InitStructure.GPIO_Pin = KEY_UP_PIN;
	GPIO_Init(KEY_UP_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = KEY_OK_PIN;
	GPIO_Init(KEY_OK_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = KEY_DOWN_PIN;
	GPIO_Init(KEY_DOWN_PORT, &GPIO_InitStructure);	
}


/*
*********************************************************************************************************
*                                       bsp_KeyFifoConfig   
*
* Description: Initialize the key FIFO
*             
* Arguments : None.
*
* Note(s)   : The function is called by bsp_KeyConfig and can not be called by the user individually
*********************************************************************************************************
*/
void bsp_KeyFifoConfig(void)
{
	uint8_t i = 0;
	
	bsp_key_fifo.Read = 0;  /* Clear the read fifo pointer */
	bsp_key_fifo.Write = 0; /* Clear the write fifo pointer */
	
	bsp_key_fifo.IsConfig = 1;  /* button has been initialized */
	/* Configure a default value for each key structure */
	for(i = 0; i < BSP_KEY_COUNT; i++)
	{
		bsp_key[i].LongTime = KEY_LONG_TIME;
		bsp_key[i].Count = KEY_FILTER_TIME / 2;
		bsp_key[i].State = KEY_NONE;
		bsp_key[i].RepeatCount = 0;
		bsp_key[i].RepeatSpeed = 0;
	}
	
	bsp_key[KEY_ID_UP].IsKeyPressDunc = IsKeyUpPress;
	bsp_key[KEY_ID_OK].IsKeyPressDunc = IsKeyOkPress;
	bsp_key[KEY_ID_DOWN].IsKeyPressDunc = IsKeyDownPress;
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
uint8_t bsp_GetKey(void)
{
	uint8_t key;
	if(!bsp_key_fifo.IsConfig)
	{
		while(1);
	}
	
	if(bsp_key_fifo.Read == bsp_key_fifo.Write) 
	{
	//	LED0 = ~LED0;
		return KEY_NONE;
	}
	else
	{
		key = bsp_key_fifo.Fifo[bsp_key_fifo.Read];
		if( ++bsp_key_fifo.Read >= KEY_FIFO_SIZE) bsp_key_fifo.Read = 0;
		return key;
	}
}

/*
*********************************************************************************************************
*                                bsp_PutKey          
*
* Description: 
*             
* Arguments : 
*
* Note(s)   : 
*********************************************************************************************************
*/
void bsp_PutKey(uint8_t KeyValue)
{
	bsp_key_fifo.Fifo[bsp_key_fifo.Write] = KeyValue;
	
	if(++bsp_key_fifo.Write >= KEY_FIFO_SIZE)
		bsp_key_fifo.Write = 0;
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
uint8_t bsp_GetKeyState(KEY_ID_ENUM KeyId)
{
	return bsp_key[KeyId].State;
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
void bsp_KeyClear(void)
{
	bsp_key_fifo.Read = bsp_key_fifo.Write;
}

/*
*********************************************************************************************************
*                               bsp_KeyDetect           
*
* Description: 
*             
* Arguments : 
*
* Note(s)   : 
*********************************************************************************************************
*/
void bsp_KeyDetect(uint8_t Id)
{
	Key_Str *pKey;
	
	pKey = &bsp_key[Id];
	
	if(pKey->IsKeyPressDunc())
	{
		
		if(pKey->Count < KEY_FILTER_TIME) 
			pKey->Count  = KEY_FILTER_TIME;
		else if(pKey->Count < 2 * KEY_FILTER_TIME) 
			pKey->Count ++;
		else
		{
			if(pKey->State == 0)
			{
				
				pKey->State = 1;
				bsp_PutKey((uint8_t)(3 * Id + 1));
			}
			
			/*  If this variable is greater than 0, 
					it means that long press detection is on
			*/
			if(pKey->LongTime > 0)
			{
				/*  Long press detection time has arrived  */
				if(++pKey->LongCount == pKey->LongTime)
				{
					/* Put the button value into fifo of long press */
					bsp_PutKey((uint8_t)(3 * Id + 3));
				}
			}
			else  /*  it means that long press detection is off */
			{
				if(pKey->RepeatSpeed > 0)
				{
					if( ++ pKey->RepeatCount >= pKey->RepeatSpeed)
					{
						pKey->RepeatCount = 0;
						bsp_PutKey((uint8_t)(3 * Id + 1));
					}
				}
			}
		}
	}
	else
	{
		if(pKey->Count > KEY_FILTER_TIME)
			pKey->Count  = KEY_FILTER_TIME;
		else if(pKey->Count != 0)
			pKey->Count -- ;
		else
		{
			if(pKey->State == 1)
			{
				pKey->State = 0;
				bsp_PutKey((uint8_t)(3 * Id + 2));
			}
		}
		
		pKey->RepeatCount = 0;
		pKey->LongCount = 0;
	}
}

/*
*********************************************************************************************************
*                                bsp_KeyScan         
*
* Description: 
*             
* Arguments : 
*
* Note(s)   : 
*********************************************************************************************************
*/
void bsp_KeyScan(void)
{
	uint8_t i = 0;
//	bsp_LedToggle(1);
	if(!bsp_key_fifo.IsConfig)
	{
		while(1);
	}
	for(i = 0; i < BSP_KEY_COUNT; i++)
	{
		bsp_KeyDetect(i);
	}
}










