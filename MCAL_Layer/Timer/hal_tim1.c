#include "hal_tim1.h"



static inline void Timer1_Mode_Config(const timer1_t *_timer);


#if TIMER1_INTERRUPT_FEATURE == FEATURE_ENALE
static void (*TIMER1_InterruptHandler) (void) = NULL;      
#endif

static uint16 var_tim1 ;





/**
 * 
 * @param _timer
 * @return 
 */
Std_ReturnType Timer1_Init(const timer1_t *_timer)
{
    Std_ReturnType ret = E_OK;
    
    if(_timer != NULL )
    {
        TIMER1_MODE_DISABLE();
        TIMER1_PRECCALER_SELECT(_timer->prescaler_vlaue);
        Timer1_Mode_Config(_timer);
        #if TIMER1_INTERRUPT_FEATURE == FEATURE_ENALE
        #if INTERUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENALE
         INTERRUPT_PriorityLevelEnable();
         INTERRUPT_GlobalInterruptHighEnable();
         INTERRUPT_GlobalInterruptLowEnable();
         TIMER1_InterruptEnable();
         TIMER1_InterruptFlagClear();
         if(_timer->priority == INTERRUPT_HIGH_PRIORITY)
         {
             TIMER1_HighPrioritySet();  
         }
         else if(_timer->priority == INTERRUPT_LOW_PRIORITY)
         {
             TIMER1_LowPrioritySet(); 
         }
         else
         {
             
         }
         TIMER1_InterruptHandler = _timer->TIMER1_INterruptHandler;
        #else
         INTERRUPT_GlobalInterruptEnable();
         INTERRUPT_PeripheralInterruptEnable();
         TIMER1_InterruptEnable();
         TIMER1_InterruptFlagClear();
         TIMER1_InterruptHandler = _timer->TIMER1_INterruptHandler;


        #endif
        #endif
         
        TMR1H = (uint8)((_timer->timer1_preload_value)>> 8);
        TMR1L = (uint8)((_timer->timer1_preload_value));
        var_tim1 = _timer->timer1_preload_value;
        
        TIMER1_MODE_ENABLE();
                
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
Std_ReturnType Timer1_DeInit(const timer1_t *_timer)
{
    Std_ReturnType ret = E_OK;
    if(_timer != NULL )
    {
        TIMER1_MODE_DISABLE();
        #if TIMER1_INTERRUPT_FEATURE == FEATURE_ENALE
        TIMER1_InterruptDisable();
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
Std_ReturnType Timer1_Write_Value(const timer1_t *_timer,uint16 value)
{
    Std_ReturnType ret = E_OK;
    if(_timer != NULL )
    {
        TMR1H = (uint8)((value)>> 8);
        TMR1L = (uint8)((value));
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
Std_ReturnType Timer1_Read_Value(const timer1_t *_timer,uint16 *value)
{
    Std_ReturnType ret = E_OK;
    uint8 low_timer = 0;
    uint8 high_timer = 0;
    if((_timer != NULL) && (value != NULL) )
    {
        low_timer = TMR1L;
        high_timer = TMR1H;
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
static inline void Timer1_Mode_Config(const timer1_t *_timer)
 {
     if(_timer->timer1_mode == TIMER1_TIMER_MODE )
     {
         TIMER1_TIMER_MODE_ENABLE();
         
     }
     else if(_timer->timer1_mode == TIMER1_COUNTER_MODE )
     {
         TIMER1_COUNTER_MODE_ENABLE();
         if(_timer->timer1_counter_mode == TIMER1_ASYNC_COUNTER_MODE)
         {
             TIMER1_ASYNC_COUNTER_MODE_ENABLE();
         }
         else if(_timer->timer1_counter_mode == TIMER1_SYNC_COUNTER_MODE)
         {
             TIMER1_SYNC_COUNTER_MODE_ENABLE();
         }
         else
         {
             
         }
         
     }
 }


 #if TIMER1_INTERRUPT_FEATURE == FEATURE_ENALE
 void TIMER1_ISR(void)
 {
     TIMER1_InterruptFlagClear();
     TMR1H = (uint8)((var_tim1)>> 8);
     TMR1L = (uint8)((var_tim1));
    if(TIMER1_InterruptHandler != NULL)
    {
        TIMER1_InterruptHandler();
    }

 }
 #endif

 