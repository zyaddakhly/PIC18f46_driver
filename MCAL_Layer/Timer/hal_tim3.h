/* 
 * File:   hal_tim3.h
 * Author: zyadi
 *
 * Created on September 17, 2023, 6:46 PM
 */

#ifndef HAL_TIM3_H
#define	HAL_TIM3_H

/*Section Include*/
#include "../../pic/include/proc/pic18f4620.h"
#include "../interrupt/mcal_internal_interrupt.h"
#include "../GPIO/hall_gpio.h"
#include "../mcal_std_type.h"
/*Section Macro Decleration*/

#define TIMER3_TIMER_MODE  0
#define TIMER3_COUNTER_MODE 1
#define TIMER3_8BIT_RW_REG_MODE 0
#define TIMER3_16BIT_RW_REG_MODE 1
#define TIMER3_ASYNC_COUNTER_MODE 1 
#define TIMER3_SYNC_COUNTER_MODE 0 




/*Section Macro function declaration*/
#define TIMER3_MODE_ENABLE()    (T3CONbits.TMR3ON = 1)
#define TIMER3_MODE_DISABLE()   (T3CONbits.TMR3ON = 0)


#define TIMER3_TIMER_MODE_ENABLE()  (T3CONbits.TMR3CS = 0)
#define TIMER3_COUNTER_MODE_ENABLE() (T3CONbits.TMR3CS = 1)

#define TIMER3_ASYNC_COUNTER_MODE_ENABLE()  (T3CONbits.T3SYNC = 1)
#define TIMER3_SYNC_COUNTER_MODE_ENABLE()    (T3CONbits.T3SYNC = 0)



#define TIMER3_8BIT_RW_REG_MODE_ENABLE()  (T3CONbits.RD16 = 0 )
#define TIMER3_16BIT_RW_REG_MODE_ENABLE()  (T3CONbits.RD16 = 1)

#define TIMER3_PRECCALER_SELECT(_PRESCALER_) (T3CONbits.T3CKPS = _PRESCALER_)
/*Section : User data type defianation*/
typedef enum
{
    TIMER3_PRESCALER_DIV_BY_1 = 0,
    TIMER3_PRESCALER_DIV_BY_2,
    TIMER3_PRESCALER_DIV_BY_4,
    TIMER3_PRESCALER_DIV_BY_8,
 
}timer3_prescaler_select_t;


typedef struct 
{
    #if TIMER3_INTERRUPT_FEATURE == FEATURE_ENALE
    void (*TIMER3_INterruptHandler) (void);
    interrupt_prioity_t priority;
    #endif
    timer3_prescaler_select_t prescaler_vlaue ;
    uint16 timer3_preload_value;
    uint8 timer3_mode : 1;
    uint8 timer3_counter_mode : 1;
    uint8 timer3_register_rw_mode : 1;
    uint8 timer3_reserved : 5 ;
}timer3_t;

/*Section Function Declereation*/

Std_ReturnType Timer3_Init(const timer3_t *_timer);
Std_ReturnType Timer3_DeInit(const timer3_t *_timer);
Std_ReturnType Timer3_Write_Value(const timer3_t *_timer,uint16 value);
Std_ReturnType Timer3_Read_Value(const timer3_t *_timer,uint16 *value);




#endif	/* HAL_TIM3_H */

