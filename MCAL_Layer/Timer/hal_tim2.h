/* 
 * File:   hal_tim2.h
 * Author: zyadi
 *
 * Created on September 17, 2023, 1:32 PM
 */

#ifndef HAL_TIM2_H
#define	HAL_TIM2_H
/*Section Include*/
#include "../../pic/include/proc/pic18f4620.h"
#include "../interrupt/mcal_internal_interrupt.h"
#include "../GPIO/hall_gpio.h"
#include "../mcal_std_type.h"



/*Section Macro Decleration*/




/*Section Macro function declaration*/
#define TIMER2_MODE_ENABLE()    (T2CONbits.TMR2ON = 1)
#define TIMER2_MODE_DISABLE()   (T2CONbits.TMR2ON = 0)

#define TIMER2_PRECCALER_SELECT(_PRESCALER_) (T2CONbits.T2CKPS = _PRESCALER_)
#define TIMER2_POSTSCALER_SELECT(_POSTSCALER_) (T2CONbits.TOUTPS = _POSTSCALER_)



/*Section : User data type defianation*/


#define TIMER2_POSTSCALER_DIV_BY_1  0
#define TIMER2_POSTSCALER_DIV_BY_2  1
#define TIMER2_POSTSCALER_DIV_BY_3  2
#define TIMER2_POSTSCALER_DIV_BY_4  3
#define TIMER2_POSTSCALER_DIV_BY_5  4
#define TIMER2_POSTSCALER_DIV_BY_6  5
#define TIMER2_POSTSCALER_DIV_BY_7  6
#define TIMER2_POSTSCALER_DIV_BY_8  7
#define TIMER2_POSTSCALER_DIV_BY_9  8
#define TIMER2_POSTSCALER_DIV_BY_10 9
#define TIMER2_POSTSCALER_DIV_BY_11 10
#define TIMER2_POSTSCALER_DIV_BY_12 11
#define TIMER2_POSTSCALER_DIV_BY_13 12
#define TIMER2_POSTSCALER_DIV_BY_14 13
#define TIMER2_POSTSCALER_DIV_BY_15 14
#define TIMER2_POSTSCALER_DIV_BY_16 15


#define TIMER2_PRESCALER_DIV_BY_1  0
#define TIMER2_PRESCALER_DIV_BY_4  1
#define TIMER2_PRESCALER_DIV_BY_16 2

typedef struct 
{
    #if TIMER1_INTERRUPT_FEATURE == FEATURE_ENALE
    void (*TIMER2_INterruptHandler) (void);
    interrupt_prioity_t priority;
    #endif
    uint8 timer2_preload_value;
    uint8 timer2_postscaler_vlaue : 4;
    uint8 timer2_prescaler_value  : 2;
    uint8 timer2_reserved : 2;
}timer2_t;

/*Section Function Declereation*/

Std_ReturnType Timer2_Init(const timer2_t *_timer);
Std_ReturnType Timer2_DeInit(const timer2_t *_timer);
Std_ReturnType Timer2_Write_Value(const timer2_t *_timer,uint8 value);
Std_ReturnType Timer2_Read_Value(const timer2_t *_timer,uint8 *value);
















#endif	/* HAL_TIM2_H */

