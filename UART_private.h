/*
 * UART_private.h
 *
 * Created: 22/03/2024 10:44:34 am
 *  Author: Ismail
 */ 


#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_



#define UCSRA   *((volatile u8 *)(0x2B))  // control A
#define UCSRB   *((volatile u8 *)(0x2A))  // control B
#define UCSRC   *((volatile u8 *)(0x40))  // control C
#define UDR		*((volatile u8 *)(0x2C))  // data register
#define UBRRH   *((volatile u8 *)(0x40))  // BR high
#define UBRRL   *((volatile u8 *)(0x29))   // BR low

//UCSRC_REG

#define UCSRC_URSEL     7  // register select
#define UCSRC_UMSEL     6  // UART mode select
#define UCSRC_UPM1      5  // parity bit
#define UCSRC_UPM0      4  // parity bit
#define UCSRC_USBS      3  // stop bit
#define UCSRC_UCSZ1     2  // msg size
#define UCSRC_UCSZ0     1  // msg size
#define UCSRC_UCPOL     0  // clock polarity in synchronous mode

//UCSRA_REG

#define UCSRA_RXC	    7   // RX complete flag
#define UCSRA_TXC		6   // TX complete flag
#define UCSRA_UDRE		5   // data register empty
#define UCSRA_FE		4   // frame error
#define UCSRA_DOR		3   // data overrun error
#define UCSRA_PE		2   // parity error
#define UCSRA_U2X		1   // double speed mode
#define UCSRA_MPCM		0

//UCSRB_REG

#define  UCSRB_RXCIE	7   // RX complete Interrupt Enable
#define  UCSRB_TXCIE	6   // Tx complete Interrupt Enable
#define  UCSRB_UDRIE	5   // data register empty Interrupt Enable
#define  UCSRB_RXEN		4   // Enable Rx
#define  UCSRB_TXEN		3   // Enable Tx
#define  UCSRB_UCSZ2	2   // msg size
#define  UCSRB_RXB8		1   // bit8 in 9 bit mode (Rx)
#define  UCSRB_TXB8		0   // bit8 in 9 bit mode (Tx)

#define NO_PARITY				1
#define	EVEN_PARITY_BITS		2
#define	ODD_PARITY_BITS			3

#define	STOP_BITS1		5
#define	STOP_BITS2		9

#endif /* UART_PRIVATE_H_ */