#include "hal_timr0.h"

static inline void Timer0_Prescaler_Config(const timer0_t *_timer);
static inline void Timer0_Mode_Config(const timer0_t *_timer);
static inline void Timer0_Register_Size_Config(const timer0_t *_timer);



#if TIMER0_INTERRUPT_FEATURE == FEATURE_ENALE
static void (*TIMER0_InterruptHandler) (void) = NULL;      
#endif

static uint16 var_tim0 ;












Std_ReturnType Timer0_Init(const timer0_t *_timer)
{
    Std_ReturnType ret = E_OK;
    if(_timer != NULL )
    {
        
        
        TIMER0_MODE_DISABLE(); 
        Timer0_Prescaler_Config(_timer);
        Timer0_Mode_Config(_timer);
        Timer0_Register_Size_Config(_timer);
        
        #if TIMER0_INTERRUPT_FEATURE == FEATURE_ENALE
        #if INTERUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENALE
         INTERRUPT_PriorityLevelEnable();
         INTERRUPT_GlobalInterruptHighEnable();
         INTERRUPT_GlobalInterruptLowEnable();
         TIMER0_InterruptEnable();
         TIMER0_InterruptFlagClear();
         if(_timer->priority == INTERRUPT_HIGH_PRIORITY)
         {
             TIMER0_HighPrioritySet();  
         }
         else if(_timer->priority == INTERRUPT_LOW_PRIORITY)
         {
             TIMER0_LowPrioritySet(); 
         }
         else
         {
             
         }
         TIMER0_InterruptHandler = _timer->TIMER0_INterruptHandler;
        #else
         INTERRUPT_GlobalInterruptEnable();
         INTERRUPT_PeripheralInterruptEnable();
         TIMER0_InterruptEnable();
         TIMER0_InterruptFlagClear();
         TIMER0_InterruptHandler = _timer->TIMER0_INterruptHandler;


        #endif
        #endif
         
        TMR0H = (uint8)((_timer->timer0_preload_value)>> 8);
        TMR0L = (uint8)((_timer->timer0_preload_value));
        var_tim0 = _timer->timer0_preload_value;
        
        TIMER0_MODE_ENABLE();

    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
    
}

#if TIMER0_INTERRUPT_FEATURE == FEATURE_ENALE
        



#endif
Std_ReturnType Timer0_DeInit(const timer0_t *_timer)
{
    Std_ReturnType ret = E_OK;
    if(_timer != NULL )
    {
        TIMER0_MODE_DISABLE();
        #if TIMER0_INTERRUPT_FEATURE == FEATURE_ENALE
        TIMER0_InterruptDisable();
        #endif
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
    
}
Std_ReturnType Timer0_Write_Value(const timer0_t *_timer,uint16 value)
{
    Std_ReturnType ret = E_OK;
    if(_timer != NULL )
    {
        TMR0H = (uint8)((value)>> 8);
        TMR0L = (uint8)((value));
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
    
}
Std_ReturnType Timer0_Read_Value(const timer0_t *_timer,uint16 *value)
{
    Std_ReturnType ret = E_OK;
    uint8 low_timer = 0;
    uint8 high_timer = 0;
    if((_timer != NULL) && (value != NULL) )
    {
        low_timer = TMR0L;
        high_timer = TMR0H;
        *value = (uint16)((high_timer << 8) + low_timer);
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
    
}
 #if TIMER0_INTERRUPT_FEATURE == FEATURE_ENALE
 void TIMER0_ISR(void)
 {
     TIMER0_InterruptFlagClear();
     TMR0H = (uint8)((var_tim0)>> 8);
     TMR0L = (uint8)((var_tim0));
    if(TIMER0_InterruptHandler != NULL)
    {
        TIMER0_InterruptHandler();
    }

 }
 #endif

 
 
 static inline void Timer0_Prescaler_Config(const timer0_t *_timer)
 {
     if(_timer->prescaler_enable == TIMER0_PRESCALER_ENABLE_CFG)
     {
         TIMER0_PRESCALER_ENABLE();
         T0CONbits.T0PS = _timer->prescaler_vlaue;
         
     }
     else if(_timer->prescaler_enable == TIMER0_PRESCALER_DISABLE_CFG)
     {
         TIMER0_PRESCALER_DISABLE();
     }
     else
     {
         
     }
 }
 
  static inline void Timer0_Mode_Config(const timer0_t *_timer)
 {
     if(_timer->timer0_mode == TIMER0_TIMER_MODE )
     {
         TIMER0_TIMER_MODE_ENABLE();
         
     }
     else if(_timer->timer0_mode == TIMER0_COUNTER_MODE )
     {
         TIMER0_COUNTER_MODE_ENABLE();
         if(_timer->time0_counter_edge == TIMER0_RISING_CFG)
         {
             TIMER0_RISING_EDGE_ENABLE();
         }
         else if(_timer->time0_counter_edge == TIMER0_FALLING_CFG)
         {
             TIMER0_FALLING_EDGE_ENABLE();
         }
         else
         {
             
         }
         
     }
 }
  
  
   static inline void Timer0_Register_Size_Config(const timer0_t *_timer)
 {
     if(_timer->timer0_register_size == TIMER0_8BIT_REGISTER_MODE)
     {
        TIMER0_8BIT_REGISTER_MODE_ENABLE();       
     }
     else if(_timer->timer0_register_size == TIMER0_16BIT_REGISTER_MODE)
     {
         TIMER0_16BIT_REGISTER_MODE_ENABLE();
     }
     else
     {
         
     }
 }