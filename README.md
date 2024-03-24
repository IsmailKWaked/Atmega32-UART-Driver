# Atmega32-UART-Driver

This repository contains an UART (Universal Asynchronous Receiver-Transmitter) driver for the Atmega32 microcontroller. The driver provides functions for initializing the UART communication, sending and receiving data, and handling interrupts.

# Features
Configurable baud rates (2400, 4800, 9600, 14400, 19200)
Polling mode for simple data transmission and reception
Interrupt-based mode for efficient communication
Support for sending and receiving strings
# Usage
Include the UART_interface.h header file in your project.
Initialize the UART module using UART_voidInit(u16 copy_u8BaudRate), where copy_u8BaudRate is the desired baud rate.
Send data using UART_voidSendByte_poll(u8 copy_u8Data) or UART_voidSendString_poll(u8* copy_u8str).
Receive data using UART_u8RecieveByte_poll() or UART_u8ReceiveStrINT().
Set a callback function for transmit complete event using UART_voidSetCallbackTx(void(*copy_pTxCompleteAction)(void))
