#include "hal_tim2.h"




#if TIMER2_INTERRUPT_FEATURE == FEATURE_ENALE
static void (*TIMER2_InterruptHandler) (void) = NULL;      
#endif

static uint16 var_tim2;





/**
 * 
 * @param _timer
 * @return 
 */
Std_ReturnType Timer2_Init(const timer2_t *_timer)
{
    Std_ReturnType ret = E_OK;
    if(_timer != NULL )
    {
        TIMER2_MODE_DISABLE();
        TIMER2_PRECCALER_SELECT(_timer->timer2_prescaler_value) ;
        TIMER2_POSTSCALER_SELECT(_timer->timer2_postscaler_vlaue);
        #if TIMER2_INTERRUPT_FEATURE == FEATURE_ENALE
        #if INTERUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENALE
         INTERRUPT_PriorityLevelEnable();
         INTERRUPT_GlobalInterruptHighEnable();
         INTERRUPT_GlobalInterruptLowEnable();
         TIMER2_InterruptEnable();
         TIMER2_InterruptFlagClear();
         if(_timer->priority == INTERRUPT_HIGH_PRIORITY)
         {
             TIMER2_HighPrioritySet();  
         }
         else if(_timer->priority == INTERRUPT_LOW_PRIORITY)
         {
             TIMER2_LowPrioritySet(); 
         }
         else
         {
             
         }
         TIMER2_InterruptHandler = _timer->TIMER2_INterruptHandler;
        #else
         INTERRUPT_GlobalInterruptEnable();
         INTERRUPT_PeripheralInterruptEnable();
         TIMER2_InterruptEnable();
         TIMER2_InterruptFlagClear();
         TIMER2_InterruptHandler = _timer->TIMER2_INterruptHandler;


        #endif
        #endif
        TMR2 = _timer->timer2_preload_value;
        var_tim2 = _timer->timer2_preload_value;
        
        TIMER2_MODE_ENABLE();
                
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
Std_ReturnType Timer2_DeInit(const timer2_t *_timer)
{
    Std_ReturnType ret = E_OK;
    if(_timer != NULL )
    {
        TIMER2_MODE_DISABLE();
        #if TIMER2_INTERRUPT_FEATURE == FEATURE_ENALE
        TIMER2_InterruptDisable();
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
Std_ReturnType Timer2_Write_Value(const timer2_t *_timer,uint8 value)
{
    Std_ReturnType ret = E_OK;
    if(_timer != NULL )
    {
        TMR2 = value;

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
Std_ReturnType Timer2_Read_Value(const timer2_t *_timer,uint8 *value)
{
    Std_ReturnType ret = E_OK;

    if((_timer != NULL) && (value != NULL) )
    {
       *value =  TMR2;
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
}






 #if TIMER2_INTERRUPT_FEATURE == FEATURE_ENALE
 void TIMER2_ISR(void)
 {
     TIMER2_InterruptFlagClear();
     TMR2 = var_tim2;
    if(TIMER2_InterruptHandler != NULL)
    {
        TIMER2_InterruptHandler();
    }

 }
 #endif

 