/* 
 * File:   hal_usart.h
 * Author: zyadi
 *
 * Created on September 30, 2023, 4:51 PM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H
/*Section : Include */
#include "hal_usart_config.h"
#include "../../pic/include/proc/pic18f4620.h"
#include "../interrupt/mcal_internal_interrupt.h"
#include "../GPIO/hall_gpio.h"

/*Section Macro Declaration*/
/*Enable disable usart module*/
#define EUSART_ENABLE                   1
#define EUSART_DISABLE                  0

/*Selecting USART Mode*/
#define EUSART_SYNCHRONOUS_MODE         1
#define EUSART_ASYNCHRONOUS_MODE        0

/*Baud Rate Generator Asynchronous Mode*/
#define EUSART_ASYNCHRONOUS_HIGH_SPEED  1
#define EUSART_ASYNCHRONOUS_LOW_SPEED   0

/*Baud Rate Generator register size*/
#define EUSART_16BIT_BAUD_RATE_GEN      1
#define EUSART_8BIT_BAUD_RATE_GEN       0

/*EUSART Transim Enable */
#define EUSART_ASYNCHRONOUS_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_TX_DISABLE  0

/*EUSART Transmit interrupt Enable*/

#define EUSART_ASYNCCHRONOUS_INTERRUPT_TX_ENABLE 1
#define EUSART_ASYNCCHRONOUS_INTERRUPT_TX_DISABLE 0

/*EUSART 9-Bit Transit Enable */
#define EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE      1
#define EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE     0


/*EUSART Receiver Enable */
#define EUSART_ASYNCHRONOUS_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_RX_DISABLE  0

/*EUSART Receiver interrupt Enable*/

#define EUSART_ASYNCCHRONOUS_INTERRUPT_RX_ENABLE 1
#define EUSART_ASYNCCHRONOUS_INTERRUPT_RX_DISABLE 0

/*EUSART 9-Bit Receiver Enable */
#define EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE      1
#define EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE     0


/*EUSART Framing Error*/
#define EUSART_FRAMING_ERROR_DETECTED   1
#define EUSART_FRAMING_ERROR_CLEARED    0
/*EUSART Overrun Error*/
#define EUSART_Overrun_ERROR_DETECTED   1
#define EUSART_Overrun_ERROR_CLEARED    0

/*----------Section User Data Type Declaration-------------*/

typedef enum {
    BAUDRATE_ASYN_8BIT_LOW_SPEED,
    BAUDRATE_ASYN_8BIT_HIGH_SPEED,      
    BAUDRATE_ASYN_16BIT_LOW_SPEED,
    BAUDRATE_ASYN_16BIT_HIGH_SPEED,
    BAUDRATE_SYN_8BIT,
    BAUDRATE_SYN_16BIT,
}baudrate_gen_t;



typedef struct {
    uint8 usart_tx_reserved :5;
    uint8_t usart_tx_enable : 1;
    uint8_t usart_tx_interrupt_enable : 1;
    uint8_t usart_tx_9bit_enable : 1;
    interrupt_prioity_t tx_priority;


}usart_tx_cfg_t;

typedef struct 
{
    uint8 usart_rx_reserved : 5;
    uint8_t usart_rx_enable : 1;
    uint8_t usart_rx_interrupt_enable : 1;
    uint8_t usart_rx_9bit_enable : 1;
    interrupt_prioity_t rx_priority;

}usart_rx_cfg_t;


typedef union 
{
    struct {
        uint8 usart_tx_reserved :6;
        uint8 usart_ferrd   : 1;
        uint8 usart_oerr    : 1;

    };
    uint8 status;
}usart_error_status_t;


typedef struct 
{
    uint32 baudrate;
    baudrate_gen_t baudrate_gen_config;
    usart_tx_cfg_t usart_tx_cfg;
    usart_rx_cfg_t usart_rx_cfg;
    usart_error_status_t error_status;
    void(*ESART_TxDefaultInterruptHandler) (void);
    void(*ESART_RxDefaultInterruptHandler) (void);
    void(*ESART_FramingErrorInterruptHandler) (void);
    void(*ESART_OverrunErrorInterruptHandler) (void);
}usart_t;
/*----------------------Section Function Declaration*/

Std_ReturnType EUSART_Init(const usart_t * usart);
Std_ReturnType EUSART_DeInit(const usart_t * usart);
Std_ReturnType EUSART_ReadByeBlocking(uint8 *data);
Std_ReturnType EUSART_WriteByeBlocking(uint8 data);
Std_ReturnType EUSART_WriteStringBlocking(uint8 *data);
Std_ReturnType EUSART_ReadByeNonBlocking(uint8 *data);
Std_ReturnType EUSART_ASYNC_RX_Restart(void);


#endif	/* HAL_USART_H */

