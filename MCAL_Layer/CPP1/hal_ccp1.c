#include "hal_cpp1.h"

#if CCP1_INTERRUPT_FEATURE == FEATURE_ENALE
static void (*CCP1_InterruptHandler) (void) = NULL;      
#endif


Std_ReturnType CCP1_Init(const ccp1_t *ccp_obj)
{
    Std_ReturnType ret = E_OK;
    if(ccp_obj != NULL)
    {
        CCP1_SET_MODE(CCP1_MODULE_DISABLE);
        if(ccp_obj->ccp1_mode == CCP1_CAPTURE_MODE_SELECT)
        {
            switch(ccp_obj->ccp1_mode_variant)
            {
                case CCP1_CAPUTURE_MOCDE_1_FALLING_EDGE :CCP1_SET_MODE(CCP1_CAPUTURE_MOCDE_1_FALLING_EDGE);break;
                case CCP1_CAPUTURE_MOCDE_1_RISING_EDGE :CCP1_SET_MODE(CCP1_CAPUTURE_MOCDE_1_RISING_EDGE);break;
                case CCP1_CAPUTURE_MOCDE_4_RISING_EDGE  :CCP1_SET_MODE(CCP1_CAPUTURE_MOCDE_4_RISING_EDGE );break;
                case CCP1_CAPUTURE_MOCDE_16_RISING_EDGE :CCP1_SET_MODE(CCP1_CAPUTURE_MOCDE_16_RISING_EDGE);break;

            }
            #if (CCP1_CFG_SELECTED_MODE == CCP1_CFG_CAPTURE_MODE_SELECTED)
            if(ccp_obj->ccp1_capture_timer == CCP1_CCP2_TIMER3)
            {
                T3CONbits.T3CCP1 = 0;
                T3CONbits.T3CCP2 = 1;
            }
            else if(ccp_obj->ccp1_capture_timer == CCP1_TIMER1_CCP2_TIMER3)
            {
                T3CONbits.T3CCP1 = 1;
                T3CONbits.T3CCP2 = 0;
            }
            else if(ccp_obj->ccp1_capture_timer == CCP1_CCP2_TIMER1)
            {
                T3CONbits.T3CCP1 = 0;
                T3CONbits.T3CCP2 = 0;
            }
            else
            {
                
            }
        #endif
            ret = gpio_pin_direction_intialize(&(ccp_obj->pin));
        }
        else if(ccp_obj->ccp1_mode == CCP1_COMPARE_MODE_SELECT )
        {
            switch(ccp_obj->ccp1_mode_variant)
            {
                case CCP1_COMPARE_MODE_SET_PIN_LOW  :CCP1_SET_MODE(CCP1_COMPARE_MODE_SET_PIN_LOW );break;
                case CCP1_COMPARE_MODE_SET_PIN_HIGH :CCP1_SET_MODE(CCP1_COMPARE_MODE_SET_PIN_HIGH);break;
                case CCP1_COMPARE_MODE_TOGGLE_ON_MATCH  :CCP1_SET_MODE(CCP1_COMPARE_MODE_TOGGLE_ON_MATCH );break;
                case CCP1_COMPARE_MODE_GEN_SW_INTERRUPT :CCP1_SET_MODE(CCP1_COMPARE_MODE_GEN_SW_INTERRUPT);break;
                case CCP1_COMPARE_MODE_GEN_EVENT :CCP1_SET_MODE(CCP1_COMPARE_MODE_GEN_EVENT);break;
                default:ret = E_NOT_OK;break;

            }
            ret = gpio_pin_initalize(&(ccp_obj->pin));

            
        }
        else if(ccp_obj->ccp1_mode ==CCP1_PWM_MODE_SELECT )
        {
            ret = gpio_pin_initalize(&(ccp_obj->pin));
            switch(ccp_obj->ccp1_mode_variant)
            {
                case CCP1_PWM_MODE  :CCP1_SET_MODE(CCP1_PWM_MODE);break;
                default:ret = E_NOT_OK;break;

            }
            #if (CCP1_CFG_SELECTED_MODE == CCP1_CFG_PWM_MODE_SELECTED)

            PR2 = (uint8)((_XTAL_FREQ / (ccp_obj->timer2_postscaler_vlaue*ccp_obj->timer2_postscaler_vlaue * 4.0 * ccp_obj->PWM_Frequency))-1);
            #endif
        }
        else
        {
            ret = E_NOT_OK;

        }
        #if CCP1_INTERRUPT_FEATURE == FEATURE_ENALE
        #if INTERUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENALE
         INTERRUPT_PriorityLevelEnable();
         INTERRUPT_GlobalInterruptHighEnable();
         INTERRUPT_GlobalInterruptLowEnable();
         CCP1_InterruptEnable();
         CCP1_InterruptFlagClear();
         if(ccp_obj->priority == INTERRUPT_HIGH_PRIORITY)
         {
             CCP1_HighPrioritySet();  
         }
         else if(ccp_obj->priority == INTERRUPT_LOW_PRIORITY)
         {
             CCP1_LowPrioritySet(); 
         }
         else
         {
             
         }
         CCP1_InterruptHandler = ccp_obj->CCP1_INterruptHandler;
        #else
         INTERRUPT_GlobalInterruptEnable();
         INTERRUPT_PeripheralInterruptEnable();
         CCP1_InterruptEnable();
         CCP1_InterruptFlagClear();
         CCP1_InterruptHandler = ccp_obj->CCP1_INterruptHandler;


        #endif
        #endif
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}
Std_ReturnType CCP1_DeInit(const ccp1_t *ccp_obj)
{
    Std_ReturnType ret = E_OK;
    if(ccp_obj != NULL)
    {
        CCP1_SET_MODE(CCP1_MODULE_DISABLE);
        #if CCP1_INTERRUPT_FEATURE == FEATURE_ENALE
        CCP1_InterruptDisable();
        #endif


    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret ;
}

#if (CCP1_CFG_SELECTED_MODE == CCP1_CFG_CAPTURE_MODE_SELECTED)

/**
 * 
 * @param capture_state
 * @return 
 */
Std_ReturnType CCP1_IsCapturedDataReady(uint8 *capture_state)
{
    Std_ReturnType ret = E_OK;
    if(capture_state != NULL)
    {
        if(CCP1_CAPTURE_READY == PIR1bits.CCP1IF)
        {
            *capture_state = CCP1_CAPTURE_READY;
            CCP1_InterruptFlagClear(); 

        }
        else if(CCP1_CAPTURE_NOT_READY == PIR1bits.CCP1IF)
        {
            *capture_state = CCP1_CAPTURE_NOT_READY;
        }
        else
        {
            ret = E_NOT_OK;
        }
            
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}
/**
 * 
 * @param Cap_Value
 * @return 
 */
Std_ReturnType CCP1_Capture_Mode_Read_Value(uint16 *Cap_Value)
{
    Std_ReturnType ret = E_OK;
    if(Cap_Value != NULL)
    {
        CCP1_PEROD_REG_T ccp_reg = {.ccpr1_16Bit = 0} ;
        ccp_reg.ccpr1_low = CCPR1L;
        ccp_reg.ccpr1_high = CCPR1H;
        *Cap_Value = ccp_reg.ccpr1_16Bit;
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}

#endif
#if (CCP1_CFG_SELECTED_MODE == CCP1_CFG_COMPARE_MODE_SELECTED)

Std_ReturnType CCP1_IsComparedDataReady(uint8 *Compare_state)
{
    Std_ReturnType ret = E_OK;
    if(Compare_state != NULL)
    {
        if(CCP1_COMPARE_READY == PIR1bits.CCP1IF)
        {
            *Compare_state = CCP1_COMPARE_READY;
            CCP1_InterruptFlagClear(); 

        }
        else if(CCP1_COMPARE_NOT_READY == PIR1bits.CCP1IF)
        {
            *Compare_state = CCP1_COMPARE_NOT_READY;
        }
        else
        {
            ret = E_NOT_OK;
        }
        
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}
Std_ReturnType CCP1_Compare_Mode_Set_Value(uint16 Com_Value)
{
    Std_ReturnType ret = E_OK;
        CCP1_PEROD_REG_T ccp_reg = {.ccpr1_high = 0,.ccpr1_low = 0} ;
        ccp_reg.ccpr1_16Bit  = Com_Value;
        CCPR1L = ccp_reg.ccpr1_low;
        CCPR1H = ccp_reg.ccpr1_high;
        
    return ret;
}
    
#endif
#if (CCP1_CFG_SELECTED_MODE == CCP1_CFG_PWM_MODE_SELECTED)
Std_ReturnType CCP1_PWM1_SET_DUTY(const uint8 duty)
{
    Std_ReturnType ret = E_OK;
    
    ret = E_OK;
    uint16 l_duty_temp = 0;
    l_duty_temp = (uint16)(PR2 + 1) *(duty /100.0) *4;
    CCP1CONbits.DC1B = (uint8) (l_duty_temp & 0x0003);
    CCPR1L = (uint8)(l_duty_temp >> 2);
    
    return ret;
}
Std_ReturnType CCP1_PWM1_Start(void )
{
    Std_ReturnType ret = E_OK;
    CCP1_SET_MODE(CCP1_PWM_MODE);
    ret = E_OK;
    return ret;
}
Std_ReturnType CCP1_PWM1_Stop(void)
{
    Std_ReturnType ret = E_NOT_OK;
    
    CCP1_SET_MODE(CCP1_MODULE_DISABLE);
    
    ret = E_OK;
    return ret;
}

#endif

#if CCP1_INTERRUPT_FEATURE == FEATURE_ENALE
 void CCP1_ISR(void)
 {
     CCP1_InterruptFlagClear();
  
    if(CCP1_InterruptHandler != NULL)
    {
        CCP1_InterruptHandler();
    }

 }
 #endif
