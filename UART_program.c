/*
 * UART_program.c
 *
 * Created: 22/03/2024 10:45:15 am
 *  Author: Ismail
 */ 
#include "../../STD_TYPES.h"
#include "../../BIT_MATH.h"
#include "UART_config.h"
#include "UART_interface.h"
#include "UART_private.h"

static void (*PRV_pFunCallBackTx)(void)=NULL;

static Bool MSG_received=false;
static u8 Rxptr[100];
static u8 RxIndx=0;
static u8 txptr[100];
static u8 txIndx=0;

void UART_voidInit(u16 copy_u8BaudRate)
{
	//access the UBRR register 
	//CLR_BIT(UCSRC,UCSRC_URSEL);
	//set baud rate as 9600
	UBRRH=(u8)(copy_u8BaudRate>>8);
	UBRRL=(u8)copy_u8BaudRate;
	//enable receive and transmit
	SET_BIT(UCSRB,UCSRB_RXEN);
	SET_BIT(UCSRB,UCSRB_TXEN);
	
	
	SET_BIT(UCSRC,UCSRC_URSEL);
	//access the UCSRC register
	CLR_BIT(UCSRB,UCSRB_UCSZ2);
	SET_BIT(UCSRC,UCSRC_UCSZ1);
	SET_BIT(UCSRC,UCSRC_UCSZ0);
	
	#if UART_STOP_BITS==STOP_BITS1
	
		//one stop bit
		CLR_BIT(UCSRC,UCSRC_USBS);
	
	#elif UART_STOP_BITS==STOP_BITS2
	
		//two stop bits
		SET_BIT(UCSRC,UCSRC_USBS);
		
	#endif
	
	#if UART_PARITY_BITS==NO_PARITY
		//no parity bits
		CLR_BIT(UCSRC,UCSRC_UPM0);
		CLR_BIT(UCSRC,UCSRC_UPM1);
	
	#elif UART_PARITY_BITS==EVEN_PARITY_BITS
		//even parity bits
		CLR_BIT(UCSRC,UCSRC_UPM0);
		SET_BIT(UCSRC,UCSRC_UPM1);
	#elif UART_PARITY_BITS==ODD_PARITY_BITS
		//even parity bits
		SET_BIT(UCSRC,UCSRC_UPM0);
		SET_BIT(UCSRC,UCSRC_UPM1);	
	#endif
		
	//UART asynchronous 
	CLR_BIT(UCSRC,UCSRC_UMSEL);
	
	//enable transmission interrupt
	SET_BIT(UCSRB,UCSRB_TXCIE);
	SET_BIT(UCSRB,UCSRB_RXCIE);
	
	
}

void UART_voidSendByte_poll(u8 copy_u8Data)
{
	while(GET_BIT(UCSRA,UCSRA_UDRE)==0);
	UDR=copy_u8Data;
}

u8 UART_u8RecieveByte_poll(void)
{
	while(GET_BIT(UCSRA,UCSRA_RXC)==0);
	return UDR;
}


void UART_voidSendString_poll(u8* copy_u8str)
{
	for (u8 i=0;copy_u8str[i]!='\0';i++)
	{
		UART_voidSendByte_poll(copy_u8str[i]);
	}
}

void UART_voidSetCallbackTx(void(*copy_pTxCompleteAction)(void))
{
	if (copy_pTxCompleteAction!=NULL)
	{
		PRV_pFunCallBackTx=copy_pTxCompleteAction;
	}
}

void UART_voidTransmitByteINT	(u8 copy_u8Data)
{
	UDR=copy_u8Data;
}


void UART_voidSendStrINT	(u8* copy_u8Data)
{
	for (u8 i=0;i<sizeof(txptr);i++)
	{
		txptr[i]=copy_u8Data[i];
	}
	UART_voidTransmitByteINT(txptr[txIndx]);
}

Bool UART_isMSG_received(void)
{
	if (MSG_received==true)
	{
		MSG_received=false;
		return true;
	}
	else
	{
		return false;
	}
}
u8 UART_u8RecieveByteINT	(void)
{
	return UDR;
}


u8* UART_u8ReceiveStrINT	(void)
{
	return Rxptr;
}



void __vector_15(void) __attribute__((signal));
void __vector_15(void)
{
	txIndx++;
	if (txptr[txIndx]!='\0')
	{
		UART_voidTransmitByteINT(txptr[txIndx]);
	}
	else
	{
		txIndx=0;
	}
	
	if (PRV_pFunCallBackTx!=NULL)
	{
		PRV_pFunCallBackTx();
	}
}

void __vector_13(void) __attribute__((signal));
void __vector_13(void)
{
	Rxptr[RxIndx]=UART_u8RecieveByteINT();
	if (Rxptr[RxIndx]=='\r')
	{
		Rxptr[RxIndx]='\0';
		RxIndx=0;
		MSG_received=true;
	}
	else
	{
		RxIndx++;	
	}
}