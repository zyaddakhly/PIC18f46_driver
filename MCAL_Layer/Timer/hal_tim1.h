/* 
 * File:   hal_tim1.h
 * Author: zyadi
 *
 * Created on September 17, 2023, 11:09 AM
 */

#ifndef HAL_TIM1_H
#define	HAL_TIM1_H

/*Section Include*/
#include "../../pic/include/proc/pic18f4620.h"
#include "../interrupt/mcal_internal_interrupt.h"
#include "../GPIO/hall_gpio.h"
#include "../mcal_std_type.h"



/*Section Macro Decleration*/


#define TIMER1_TIMER_MODE  0
#define TIMER1_COUNTER_MODE 1
#define TIMER1_8BIT_REGISTER_MODE 0
#define TIMER1_16BIT_REGISTER_MODE 1
#define TIMER1_ASYNC_COUNTER_MODE 1 
#define TIMER1_SYNC_COUNTER_MODE 0 
#define TIMER1_OSC_ENABLE  1
#define TIMER1_OSC_DISABLE 0


/*Section Macro function declaration*/
#define TIMER1_MODE_ENABLE()    (T1CONbits.TMR1ON = 1)
#define TIMER1_MODE_DISABLE()   (T1CONbits.TMR1ON = 0)


#define TIMER1_TIMER_MODE_ENABLE()  (T1CONbits.TMR1CS = 0)
#define TIMER1_COUNTER_MODE_ENABLE() (T1CONbits.TMR1CS = 1)

#define TIMER1_ASYNC_COUNTER_MODE_ENABLE()  (T1CONbits.T1SYNC = 1)
#define TIMER1_SYNC_COUNTER_MODE_ENABLE()    (T1CONbits.T1SYNC = 0)


#define TIMER1_OSC_HW_ENABLE()    (T1CONbits.T1OSCEN = 1)
#define TIMER1_OSC_HW_DISABLE()    (T1CONbits.T1OSCEN = 0)

#define TIMER1_8BIT_REGISTER_MODE_ENABLE()  (T1CONbits.RD16 = 0 )
#define TIMER1_16BIT_REGISTER_MODE_ENABLE()  (T1CONbits.RD16 = 1)

#define TIMER1_SYSTEM_CLK_STATUS()      (T1CONbits.T1RUN)
#define TIMER1_PRECCALER_SELECT(_PRESCALER_) (T1CONbits.T1CKPS = _PRESCALER_)
/*Section : User data type defianation*/

typedef enum
{
    TIMER1_PRESCALER_DIV_BY_1 = 0,
    TIMER1_PRESCALER_DIV_BY_2,
    TIMER1_PRESCALER_DIV_BY_4,
    TIMER1_PRESCALER_DIV_BY_8,
 
}timer1_prescaler_select_t;


typedef struct 
{
    #if TIMER1_INTERRUPT_FEATURE == FEATURE_ENALE
    void (*TIMER1_INterruptHandler) (void);
    interrupt_prioity_t priority;
    #endif
    timer1_prescaler_select_t prescaler_vlaue ;
    uint16 timer1_preload_value;
    uint8 timer1_mode : 1;
    uint8 timer1_osc_cfg : 1;
    uint8 timer1_counter_mode : 1;
    uint8 timer1_register_rw_mode : 1;
    uint8 timer1_reserved : 4 ;
}timer1_t;

/*Section Function Declereation*/

Std_ReturnType Timer1_Init(const timer1_t *_timer);
Std_ReturnType Timer1_DeInit(const timer1_t *_timer);
Std_ReturnType Timer1_Write_Value(const timer1_t *_timer,uint16 value);
Std_ReturnType Timer1_Read_Value(const timer1_t *_timer,uint16 *value);



#endif	/* HAL_TIM1_H */

