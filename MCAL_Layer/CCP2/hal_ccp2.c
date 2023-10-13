#include "hal_cpp2.h"

#if CCP2_INTERRUPT_FEATURE == FEATURE_ENALE
static void (*CCP2_InterruptHandler) (void) = NULL;      
#endif


Std_ReturnType CCP2_Init(const ccp2_t *ccp_obj)
{
    Std_ReturnType ret = E_OK;
    if(ccp_obj != NULL)
    {
        CCP2_SET_MODE(CCP2_MODULE_DISABLE);
        if(ccp_obj->ccp2_mode == CCP2_CAPTURE_MODE_SELECT)
        {
            switch(ccp_obj->ccp2_mode_variant)
            {
                case CCP2_CAPUTURE_MOCDE_1_FALLING_EDGE :CCP2_SET_MODE(CCP2_CAPUTURE_MOCDE_1_FALLING_EDGE);break;
                case CCP2_CAPUTURE_MOCDE_1_RISING_EDGE :CCP2_SET_MODE(CCP2_CAPUTURE_MOCDE_1_RISING_EDGE);break;
                case CCP2_CAPUTURE_MOCDE_4_RISING_EDGE  :CCP2_SET_MODE(CCP2_CAPUTURE_MOCDE_4_RISING_EDGE );break;
                case CCP2_CAPUTURE_MOCDE_16_RISING_EDGE :CCP2_SET_MODE(CCP2_CAPUTURE_MOCDE_16_RISING_EDGE);break;

            }
            ret = gpio_pin_direction_intialize(&(ccp_obj->pin));
        }
        else if(ccp_obj->ccp2_mode == CCP2_COMPARE_MODE_SELECT )
        {
            switch(ccp_obj->ccp2_mode_variant)
            {
                case CCP2_COMPARE_MODE_SET_PIN_LOW  :CCP2_SET_MODE(CCP2_COMPARE_MODE_SET_PIN_LOW );break;
                case CCP2_COMPARE_MODE_SET_PIN_HIGH :CCP2_SET_MODE(CCP2_COMPARE_MODE_SET_PIN_HIGH);break;
                case CCP2_COMPARE_MODE_TOGGLE_ON_MATCH  :CCP2_SET_MODE(CCP2_COMPARE_MODE_TOGGLE_ON_MATCH );break;
                case CCP2_COMPARE_MODE_GEN_SW_INTERRUPT :CCP2_SET_MODE(CCP2_COMPARE_MODE_GEN_SW_INTERRUPT);break;
                case CCP2_COMPARE_MODE_GEN_EVENT :CCP2_SET_MODE(CCP2_COMPARE_MODE_GEN_EVENT);break;
                default:ret = E_NOT_OK;break;

            }
            #if (CCP2_CFG_SELECTED_MODE == CCP2_CFG_CAPTURE_MODE_SELECTED)
            if(ccp_obj->ccp2_capture_timer == _CCP1_CCP2_TIMER3)
            {
                T3CONbits.T3CCP1 = 0;
                T3CONbits.T3CCP2 = 1;
            }
            else if(ccp_obj->ccp2_capture_timer == _CCP1_TIMER1_CCP2_TIMER3)
            {
                T3CONbits.T3CCP1 = 1;
                T3CONbits.T3CCP2 = 0;
            }
            else if(ccp_obj->ccp2_capture_timer == _CCP1_CCP2_TIMER1)
            {
                T3CONbits.T3CCP1 = 0;
                T3CONbits.T3CCP2 = 0;
            }
            else
            {
                
            }
           #endif
            ret = gpio_pin_initalize(&(ccp_obj->pin));

            
        }
        else if(ccp_obj->ccp2_mode ==CCP2_PWM_MODE_SELECT )
        {
            ret = gpio_pin_initalize(&(ccp_obj->pin));
            switch(ccp_obj->ccp2_mode_variant)
            {
                case CCP2_PWM_MODE  :CCP2_SET_MODE(CCP2_PWM_MODE);break;
                default:ret = E_NOT_OK;break;

            }
            #if (CCP2_CFG_SELECTED_MODE == CCP2_CFG_PWM_MODE_SELECTED)

            PR2 = (uint8)((_XTAL_FREQ / (ccp_obj->timer2_postscaler_vlaue*ccp_obj->timer2_postscaler_vlaue * 4.0 * ccp_obj->PWM_Frequency))-1);
            #endif
        }
        else
        {
            ret = E_NOT_OK;

        }
        #if CCP2_INTERRUPT_FEATURE == FEATURE_ENALE
        #if INTERUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENALE
         INTERRUPT_PriorityLevelEnable();
         INTERRUPT_GlobalInterruptHighEnable();
         INTERRUPT_GlobalInterruptLowEnable();
         CCP2_InterruptEnable();
         CCP2_InterruptFlagClear();
         if(ccp_obj->priority == INTERRUPT_HIGH_PRIORITY)
         {
             CCP2_HighPrioritySet();  
         }
         else if(ccp_obj->priority == INTERRUPT_LOW_PRIORITY)
         {
             CCP2_LowPrioritySet(); 
         }
         else
         {
             
         }
         CCP2_InterruptHandler = ccp_obj->CCP2_INterruptHandler;
        #else
         INTERRUPT_GlobalInterruptEnable();
         INTERRUPT_PeripheralInterruptEnable();
         CCP2_InterruptEnable();
         CCP2_InterruptFlagClear();
         CCP2_InterruptHandler = ccp_obj->CCP2_INterruptHandler;


        #endif
        #endif
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}
Std_ReturnType CCP2_DeInit(const ccp2_t *ccp_obj)
{
    Std_ReturnType ret = E_OK;
    if(ccp_obj != NULL)
    {
        CCP2_SET_MODE(CCP2_MODULE_DISABLE);
        #if CCP2_INTERRUPT_FEATURE == FEATURE_ENALE
        CCP2_InterruptDisable();
        #endif


    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret ;
}

#if (CCP2_CFG_SELECTED_MODE == CCP2_CFG_CAPTURE_MODE_SELECTED)

/**
 * 
 * @param capture_state
 * @return 
 */
Std_ReturnType CCP2_IsCapturedDataReady(uint8 *capture_state)
{
    Std_ReturnType ret = E_OK;
    if(capture_state != NULL)
    {
        if(CCP2_CAPTURE_READY == PIR2bits.CCP2IF)
        {
            *capture_state = CCP2_CAPTURE_READY;
            CCP2_InterruptFlagClear(); 

        }
        else if(CCP2_CAPTURE_NOT_READY == PIR2bits.CCP2IF)
        {
            *capture_state = CCP2_CAPTURE_NOT_READY;
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
Std_ReturnType CCP2_Capture_Mode_Read_Value(uint16 *Cap_Value)
{
    Std_ReturnType ret = E_OK;
    if(Cap_Value != NULL)
    {
        CCP2_PEROD_REG_T ccp_reg = {.ccpr2_16Bit = 0} ;
        ccp_reg.ccpr2_low = CCPR2L;
        ccp_reg.ccpr2_high = CCPR2H;
        *Cap_Value = ccp_reg.ccpr2_16Bit;
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}

#endif
#if (CCP1_CFG_SELECTED_MODE == CCP1_CFG_COMPARE_MODE_SELECTED)

Std_ReturnType CCP2_IsComparedDataReady(uint8 *Compare_state)
{
    Std_ReturnType ret = E_OK;
    if(Compare_state != NULL)
    {
        if(CCP2_COMPARE_READY == PIR2bits.CCP2IF)
        {
            *Compare_state = CCP2_COMPARE_READY;
            CCP2_InterruptFlagClear(); 

        }
        else if(CCP2_COMPARE_NOT_READY == PIR2bits.CCP2IF)
        {
            *Compare_state = CCP2_COMPARE_NOT_READY;
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
Std_ReturnType CCP2_Compare_Mode_Set_Value(uint16 Com_Value)
{
    Std_ReturnType ret = E_OK;
        CCP2_PEROD_REG_T ccp_reg = {.ccpr2_high = 0,.ccpr2_low = 0} ;
        ccp_reg.ccpr2_16Bit  = Com_Value;
        CCPR2L = ccp_reg.ccpr2_low;
        CCPR2H = ccp_reg.ccpr2_high;
        
    return ret;
}
    
#endif
#if (CCP2_CFG_SELECTED_MODE == CCP2_CFG_PWM_MODE_SELECTED)
Std_ReturnType CCP2_PWM2_SET_DUTY(const uint8 duty)
{
    Std_ReturnType ret = E_OK;
    
    ret = E_OK;
    uint16 l_duty_temp = 0;
    l_duty_temp = (uint16)(PR2 + 1) *(duty /100.0) * 4;
    CCP2CONbits.DC2B = (uint8)(l_duty_temp & 0x0003);
    CCPR2L = (uint8)(l_duty_temp >> 2);;
    
    return ret;
}
Std_ReturnType CCP2_PWM2_Start(void )
{
    Std_ReturnType ret = E_OK;
    CCP2_SET_MODE(CCP2_PWM_MODE);
    ret = E_OK;
    return ret;
}
Std_ReturnType CCP2_PWM2_Stop(void)
{
    Std_ReturnType ret = E_NOT_OK;
    
    CCP2_SET_MODE(CCP2_MODULE_DISABLE);
    
    ret = E_OK;
    return ret;
}

#endif

#if CCP2_INTERRUPT_FEATURE == FEATURE_ENALE
 void CCP2_ISR(void)
 {
    CCP2_InterruptFlagClear();
  
    if(CCP2_InterruptHandler != NULL)
    {
        CCP2_InterruptHandler();
    }

 }
 #endif

 