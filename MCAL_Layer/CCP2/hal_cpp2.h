/* 
 * File:   hal_cpp1.h
 * Author: zyadi
 *
 * Created on September 21, 2023, 11:07 AM
 */

#ifndef HAL_CPP2_H
#define	HAL_CPP2_H

/*Section : Include */
#include "ccp2_config.h.h"
#include "../../pic/include/proc/pic18f4620.h"
#include "../interrupt/mcal_internal_interrupt.h"
#include "../GPIO/hall_gpio.h"
#include "../mcal_std_type.h"
#include "../Timer/hal_tim1.h"
#include "../Timer/hal_tim2.h"
#include "../Timer/hal_tim3.h"
/*Section : macro decleration section*/

#define CCP2_MODULE_DISABLE                        ((uint8) 0x00)
#define CCP2_CAPUTURE_MOCDE_1_FALLING_EDGE         ((uint8) 0x04)
#define CCP2_CAPUTURE_MOCDE_1_RISING_EDGE          ((uint8) 0x05)
#define CCP2_CAPUTURE_MOCDE_4_RISING_EDGE          ((uint8) 0x06)
#define CCP2_CAPUTURE_MOCDE_16_RISING_EDGE          ((uint8) 0x07)
#define CCP2_COMPARE_MODE_SET_PIN_LOW              ((uint8) 0x08)
#define CCP2_COMPARE_MODE_SET_PIN_HIGH             ((uint8) 0x09)
#define CCP2_COMPARE_MODE_TOGGLE_ON_MATCH          ((uint8) 0x02)
#define CCP2_COMPARE_MODE_GEN_SW_INTERRUPT         ((uint8) 0x0A)
#define CCP2_COMPARE_MODE_GEN_EVENT                ((uint8) 0x0B)
#define CCP2_PWM_MODE                              ((uint8) 0x0C)


/*CCP1 Capture Mode State*/
#define CCP2_CAPTURE_NOT_READY 0x00
#define CCP2_CAPTURE_READY     0x01
/*CCP1 Compare Mode State*/
#define CCP2_COMPARE_NOT_READY 0x00
#define CCP2_COMPARE_READY     0x01



/*Section : Macro function Declaration*/

#define CCP2_SET_MODE(MODE)     (CCP2CONbits.CCP2M = MODE)


/*Section : User Data Type Declaration*/

typedef enum
{
    CCP2_CAPTURE_MODE_SELECT,
    CCP2_COMPARE_MODE_SELECT,
    CCP2_PWM_MODE_SELECT

}ccp2_mode_t;

typedef enum 
{
    _CCP1_CCP2_TIMER3 = 0,
    _CCP1_TIMER1_CCP2_TIMER3,
    _CCP1_CCP2_TIMER1,
     
            
}ccp2_capture_timer_t;
typedef struct
{
    #if CCP2_INTERRUPT_FEATURE == FEATURE_ENALE
    void (*CCP2_INterruptHandler) (void);
    interrupt_prioity_t priority;
    #endif
    ccp2_mode_t ccp2_mode;
    uint8 ccp2_mode_variant;
    pin_config_t pin;
    #if (CCP2_CFG_SELECTED_MODE == CCP2_CFG_CAPTURE_MODE_SELECTED)
    ccp2_capture_timer_t ccp2_capture_timer;
    #endif
    #if (CCP2_CFG_SELECTED_MODE == CCP2_CFG_PWM_MODE_SELECTED)
    uint32 PWM_Frequency; 
    uint8 timer2_postscaler_vlaue : 4;
    uint8 timer2_prescaler_value  : 2;
    
    #endif
    
}ccp2_t;

typedef union 
{
    struct{
        uint8 ccpr2_low;
        uint8 ccpr2_high;
    };
    struct
    {
        uint16 ccpr2_16Bit;
    };
    
}CCP2_PEROD_REG_T;


/*Section : Function Declaration*/
Std_ReturnType CCP2_Init(const ccp2_t *ccp_obj);
Std_ReturnType CCP2_DeInit(const ccp2_t *ccp_obj);

#if (CCP2_CFG_SELECTED_MODE == CCP2_CFG_CAPTURE_MODE_SELECTED)

Std_ReturnType CCP2_IsCapturedDataReady(uint8 *capture_state);
Std_ReturnType CCP2_Capture_Mode_Read_Value(uint16 *Cap_Value);

#endif
#if (CCP2_CFG_SELECTED_MODE == CCP2_CFG_COMPARE_MODE_SELECTED)
Std_ReturnType CCP2_IsComparedDataReady(uint8 *Compare_state);
Std_ReturnType CCP2_Compare_Mode_Set_Value(uint16 Com_Value);
    
#endif
#if (CCP2_CFG_SELECTED_MODE == CCP2_CFG_PWM_MODE_SELECTED)
Std_ReturnType CCP2_PWM2_SET_DUTY(const uint8 duty);
Std_ReturnType CCP2_PWM2_Start(void );
Std_ReturnType CCP2_PWM2_Stop(void);

#endif

#endif	/* HAL_CPP1_H */

