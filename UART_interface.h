/*
 * UART_interface.h
 *
 * Created: 22/03/2024 10:44:11 am
 *  Author: Ismail
 */ 


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#define UART_PRESCALER2400	416
#define UART_PRESCALER4800	207
#define UART_PRESCALER9600	103
#define UART_PRESCALER14400	68
#define UART_PRESCALER19200	51


void UART_voidInit(u16 copy_u8BaudRate);
void UART_voidSendByte_poll(u8 copy_u8Data);
u8 UART_u8RecieveByte_poll(void);
void UART_voidSendString_poll(u8* copy_u8str);

void UART_voidSendStrINT	(u8* copy_u8Data);
u8* UART_u8ReceiveStrINT	(void);
u8 UART_u8RecieveByteINT	(void);

void UART_voidTransmitByteINT	(u8 copy_u8Data);
Bool UART_isMSG_received(void);
void UART_voidSetCallbackTx(void(*copy_pTxCompleteAction)(void));
#endif /* UART_INTERFACE_H_ */