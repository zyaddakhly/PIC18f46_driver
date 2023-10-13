#include "hal_tim3.h"



static inline void Timer3_Mode_Config(const timer3_t *_timer);


#if TIMER3_INTERRUPT_FEATURE == FEATURE_ENALE
static void (*TIMER3_InterruptHandler) (void) = NULL;      
#endif

static uint16 var_tim3 ;





/**
 * 
 * @param _timer
 * @return 
 */
Std_ReturnType Timer3_Init(const timer3_t *_timer)
{
    Std_ReturnType ret = E_OK;
    if(_timer != NULL )
    {
        TIMER3_MODE_DISABLE();
        TIMER3_PRECCALER_SELECT(_timer->prescaler_vlaue);
        Timer3_Mode_Config(_timer);
        #if TIMER3_INTERRUPT_FEATURE == FEATURE_ENALE
        #if INTERUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENALE
         INTERRUPT_PriorityLevelEnable();
         INTERRUPT_GlobalInterruptHighEnable();
         INTERRUPT_GlobalInterruptLowEnable();
         TIMER3_InterruptEnable();
         TIMER3_InterruptFlagClear();
         if(_timer->priority == INTERRUPT_HIGH_PRIORITY)
         {
             TIMER3_HighPrioritySet();  
         }
         else if(_timer->priority == INTERRUPT_LOW_PRIORITY)
         {
             TIMER3_LowPrioritySet(); 
         }
         else
         {
             
         }
         TIMER3_InterruptHandler = _timer->TIMER3_INterruptHandler;
        #else
         INTERRUPT_GlobalInterruptEnable();
         INTERRUPT_PeripheralInterruptEnable();
         TIMER1_InterruptEnable();
         TIMER1_InterruptFlagClear();
         TIMER3_InterruptHandler = _timer->TIMER3_INterruptHandler;


        #endif
        #endif
         
        TMR1H = (uint8)((_timer->timer3_preload_value)>> 8);
        TMR1L = (uint8)((_timer->timer3_preload_value));
        var_tim3 = _timer->timer3_preload_value;
        
        TIMER3_MODE_ENABLE();
                
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}
/**
 * 
 * @param _timer
 * @return 
 */
Std_ReturnType Timer3_DeInit(const timer3_t *_timer)
{
    Std_ReturnType ret = E_OK;
    if(_timer != NULL )
    {
        TIMER3_MODE_DISABLE();
        #if TIMER1_INTERRUPT_FEATURE == FEATURE_ENALE
        TIMER3_InterruptDisable();
        #endif
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}
/**
 * 
 * @param _timer
 * @param value
 * @return 
 */
Std_ReturnType Timer3_Write_Value(const timer3_t *_timer,uint16 value)
{
    Std_ReturnType ret = E_OK;
    if(_timer != NULL )
    {
        TMR3H = (uint8)((value)>> 8);
        TMR3L = (uint8)((value));
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}
/**
 * 
 * @param _timer
 * @param value
 * @return 
 */
Std_ReturnType Timer3_Read_Value(const timer3_t *_timer,uint16 *value)
{
    Std_ReturnType ret = E_OK;
    uint8 low_timer = 0;
    uint8 high_timer = 0;
    if((_timer != NULL) && (value != NULL) )
    {
        low_timer = TMR3L;
        high_timer = TMR3H;
        *value = (uint16)((high_timer << 8) + low_timer);
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}




/**
 * 
 * @param _timer
 */
static inline void Timer3_Mode_Config(const timer3_t *_timer)
 {
     if(_timer->timer3_mode == TIMER3_TIMER_MODE )
     {
         TIMER3_TIMER_MODE_ENABLE();
         
     }
     else if(_timer->timer3_mode == TIMER3_COUNTER_MODE )
     {
         TIMER3_COUNTER_MODE_ENABLE();
         if(_timer->timer3_counter_mode == TIMER3_ASYNC_COUNTER_MODE)
         {
             TIMER3_ASYNC_COUNTER_MODE_ENABLE();
         }
         else if(_timer->timer3_counter_mode == TIMER3_SYNC_COUNTER_MODE)
         {
             TIMER3_SYNC_COUNTER_MODE_ENABLE();
         }
         else
         {
             
         }
         
     }
 }


 #if TIMER3_INTERRUPT_FEATURE == FEATURE_ENALE
 void TIMER3_ISR(void)
 {
     TIMER3_InterruptFlagClear();
     TMR3H = (uint8)((var_tim3)>> 8);
     TMR3L = (uint8)((var_tim3));
    if(TIMER3_InterruptHandler != NULL)
    {
        TIMER3_InterruptHandler();
    }

 }
 #endif

 
