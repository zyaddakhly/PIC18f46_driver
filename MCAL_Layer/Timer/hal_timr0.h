/* 
 * File:   hal_timr0.h
 * Author: zyadi
 *
 * Created on September 15, 2023, 5:44 PM
 */

#ifndef HAL_TIMR0_H
#define	HAL_TIMR0_H

/*Section Include*/
#include "../../pic/include/proc/pic18f4620.h"
#include "../interrupt/mcal_internal_interrupt.h"
#include "../GPIO/hall_gpio.h"
#include "../mcal_std_type.h"



/*Section Macro Decleration*/

#define TIMER0_PRESCALER_ENABLE_CFG  1
#define TIMER0_PRESCALER_DISABLE_CFG 0

#define TIMER0_RISING_CFG  1
#define TIMER0_FALLING_CFG 0


#define TIMER0_TIMER_MODE  1
#define TIMER0_COUNTER_MODE 0


#define TIMER0_8BIT_REGISTER_MODE 1
#define TIMER0_16BIT_REGISTER_MODE 0
/*Section Macro function declaration*/

#define TIMER0_MODE_ENABLE()    (T0CONbits.TMR0ON = 1)
#define TIMER0_MODE_DISABLE()   (T0CONbits.TMR0ON = 0)

/*for enable the prescaler*/
#define TIMER0_PRESCALER_ENABLE()    (T0CONbits.PSA = 0)
/*for disable the prescaler*/
#define TIMER0_PRESCALER_DISABLE()   (T0CONbits.PSA = 1)

/*Enable the risign edge to count*/
#define TIMER0_RISING_EDGE_ENABLE()  (T0CONbits.T0SE = 0)
/*Enbale the falling edge to count*/
#define TIMER0_FALLING_EDGE_ENABLE() (T0CONbits.T0SE = 1)

#define TIMER0_TIMER_MODE_ENABLE()  (T0CONbits.T0CS = 0)
#define TIMER0_COUNTER_MODE_ENABLE() (T0CONbits.T0CS = 1)

#define TIMER0_8BIT_REGISTER_MODE_ENABLE()  (T0CONbits.T08BIT = 1)
#define TIMER0_16BIT_REGISTER_MODE_ENABLE()  (T0CONbits.T08BIT = 0)
/*Section : User data type defianation*/

typedef enum
{
    TIMER0_PRESCALER_DIV_BY_2 = 0,
    TIMER0_PRESCALER_DIV_BY_4,
    TIMER0_PRESCALER_DIV_BY_8,
    TIMER0_PRESCALER_DIV_BY_16,
    TIMER0_PRESCALER_DIV_BY_32,
    TIMER0_PRESCALER_DIV_BY_64,
    TIMER0_PRESCALER_DIV_BY_128,
    TIMER0_PRESCALER_DIV_BY_256,
}timer0_prescaler_select_t;


typedef struct 
{
    #if TIMER0_INTERRUPT_FEATURE == FEATURE_ENALE
    void (*TIMER0_INterruptHandler) (void);
    interrupt_prioity_t priority;
    #endif
    timer0_prescaler_select_t prescaler_vlaue ;
    uint16 timer0_preload_value;
    uint8 prescaler_enable : 1 ;
    uint8 time0_counter_edge : 1;
    uint8 timer0_mode : 1;
    uint8 timer0_register_size : 1;
    uint8 timer0_reserved : 4;
}timer0_t;

/*Section Function Declereation*/

Std_ReturnType Timer0_Init(const timer0_t *_timer);
Std_ReturnType Timer0_DeInit(const timer0_t *_timer);
Std_ReturnType Timer0_Write_Value(const timer0_t *_timer,uint16 value);
Std_ReturnType Timer0_Read_Value(const timer0_t *_timer,uint16 *value);



#endif	/* HAL_TIMR0_H */

