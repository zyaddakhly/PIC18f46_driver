#include "hal_adc.h"


#if ADC_INTERRUPT_FEATURE == FEATURE_ENALE
static void (*ADC_InterruptHandler) (void) = NULL;      
#endif


static inline void adc_input_channel_port_confiure(adc_channel_select_t channel);
static inline void select_result_format(const adc_conf_t *_adc);
static inline void select_voltage_refrence(const adc_conf_t *_adc);
static inline void adc_select_channel_confiure(adc_channel_select_t channel);


/**
 * 
 * @param _adc
 * @return 
 */
 Std_ReturnType ADC_Init(const adc_conf_t *_adc)
 {
     Std_ReturnType ret = E_OK;
     
     if(_adc != NULL)
     {
         /*Disable the ADC*/
         ADC_CONVERTOR_DISABLE();
         /*aquisition time*/
         ADC_ACUISITION_SET((_adc->acquisition_time));
         /*Configure the converfsion closck*/
         ADC_CONVERSION_SET(_adc->conversion_clock);
         /*Configure the defalutl channel*/
         ADC_SELECT_CHANNEL(_adc->adc_channel);
         adc_input_channel_port_confiure(_adc->adc_channel);
         /*Interrupt Feature*/
        #if ADC_INTERRUPT_FEATURE == FEATURE_ENALE
        #if INTERUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENALE
         
         INTERRUPT_PriorityLevelEnable();
         INTERRUPT_GlobalInterruptHighEnable();
         INTERRUPT_GlobalInterruptLowEnable();
         ADC_InterruptEnable();
         ADC_InterruptFlagClear();
         if(_adc->priority == INTERRUPT_HIGH_PRIORITY)
         {
             ADC_HighPrioritySet();  
         }
         else if(_adc->priority == INTERRUPT_LOW_PRIORITY)
         {
             ADC_LowPrioritySet(); 
         }
         else
         {
             
         }
         ADC_InterruptHandler = _adc->ADC_INterruptHandler;
        #else
         INTERRUPT_GlobalInterruptEnable();
         INTERRUPT_PeripheralInterruptEnable();
         ADC_InterruptEnable();
         ADC_InterruptFlagClear();
         ADC_InterruptHandler = _adc->ADC_INterruptHandler;

        #endif
        #endif
         /*Configure the result format*/
         select_result_format(_adc);
         /*Configure the voltage referece*/
         select_voltage_refrence(_adc);
         /*Enalbe the ADC*/
         ADC_CONVERTOR_ENABLE();
     }
     else
     {
         ret = E_NOT_OK;

     }
     return ret;
     
 }
 /**
  * 
  * @param _adc
  * @return 
  */
 Std_ReturnType ADC_DeInit(const adc_conf_t *_adc)
 {
     Std_ReturnType ret = E_OK;
     if(_adc != NULL)
     {
         ADC_CONVERTOR_DISABLE();
         #if ADC_INTERRUPT_FEATURE == FEATURE_ENALE
         ADC_InterruptDisable();
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
  * @param _adc
  * @param channel
  * @return 
  */
 Std_ReturnType ADC_SelectChannel(const adc_conf_t *_adc,adc_channel_select_t channel)
 {
     Std_ReturnType ret = E_OK;
     if(_adc != NULL)
     {
         ADC_SELECT_CHANNEL(channel);
         adc_input_channel_port_confiure(channel);
     }
     else
     {
         ret = E_NOT_OK;
     }
     return ret;
     
 }
 /**
  * 
  * @param _adc
  * @return 
  */
 
 Std_ReturnType ADC_StartConversion(const adc_conf_t *_adc)
 {
    Std_ReturnType ret = E_OK;
     if(_adc != NULL)
     {
         ADC_START_CONVERSION();
     }
     else
     {
         ret = E_NOT_OK;
     }
     return ret;
 }
 /**
  * 
  * @param _adc
  * @param conversion_status
  * @return 
  */
 Std_ReturnType ADC_IsConversionDone(const adc_conf_t *_adc,uint8 *conversion_status)
 {
    Std_ReturnType ret = E_OK;
     if(_adc != NULL && conversion_status != NULL)
     {
         *conversion_status = (uint8)!(ADC_CONVERSION_STATUS());
     }
     else
     {
         ret = E_NOT_OK;
     }
     return ret;
 }
 /**
  * 
  * @param _adc
  * @param conversion_result
  * @return 
  */
 Std_ReturnType ADC_GetConversionResult(const adc_conf_t *_adc,adc_result_t *conversion_result)
 {
     Std_ReturnType ret = E_OK;
     if(_adc != NULL && conversion_result != NULL)
     {
           if((_adc->result_format) == (ADC_RESULT_RIGHT))
           {
               *conversion_result = (adc_result_t)((ADRESH << 8 ) + ADRESL);
           }
           else if((_adc->result_format) == (ADC_RESULT_LEFT))
           {
               *conversion_result = (adc_result_t)(((ADRESH << 8 ) + ADRESL) >> 6);
           }
           else
           {
               *conversion_result = (adc_result_t)((ADRESH << 8 ) + ADRESL);
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
  * @param _adc
  * @param channel
  * @param conversion_result
  * @return 
  */
 Std_ReturnType ADC_GetConversion_Blocking(const adc_conf_t *_adc,adc_channel_select_t channel,adc_result_t *conversion_result)
 {
     Std_ReturnType ret = E_OK;
     uint8 conversion_status = 0;
     if(_adc != NULL && conversion_result != NULL)
     {
        ret =  ADC_SelectChannel(_adc,channel);
        ret = ADC_StartConversion(_adc);
        ret = ADC_IsConversionDone(_adc,&conversion_status);
        while(ADC_CONVERSION_STATUS());
        ret  = ADC_GetConversionResult(_adc,conversion_result);
        
    
     }
     else
     {
         ret = E_NOT_OK;
     }
     return ret;
     
 }

 

 
 static inline void adc_input_channel_port_confiure(adc_channel_select_t channel)
 {
     switch( channel)
     {
        case ADC_CHANNEL_AN0:
            SET_BIT(TRISA,_TRISA_RA0_POSN);
             break;
       case ADC_CHANNEL_AN1:
            SET_BIT(TRISA,_TRISA_RA1_POSN);
             break;
        case ADC_CHANNEL_AN2:
            SET_BIT(TRISA,_TRISA_RA2_POSN);
            break;
       case ADC_CHANNEL_AN3:
            SET_BIT(TRISA,_TRISA_RA3_POSN);
             break;
       case ADC_CHANNEL_AN4:
            SET_BIT(TRISA,_TRISA_RA5_POSN);
             break;
       case ADC_CHANNEL_AN5:
            SET_BIT(TRISE,_TRISE_RE0_POSN);
             break;
        case ADC_CHANNEL_AN6:
            SET_BIT(TRISE,_TRISE_RE1_POSN);
            break;
       case ADC_CHANNEL_AN7:
            SET_BIT(TRISE,_TRISE_RE2_POSN);
             break;
       case ADC_CHANNEL_AN8:
            SET_BIT(TRISB,_TRISB_RB2_POSN);
             break;
       case ADC_CHANNEL_AN9:
            SET_BIT(TRISB,_TRISB_RB3_POSN);
             break;
        case ADC_CHANNEL_AN10:
            SET_BIT(TRISB,_TRISB_RB1_POSN);
            break;
       case ADC_CHANNEL_AN11:
            SET_BIT(TRISB,_TRISB_RB4_POSN);
             break;
             
         case ADC_CHANNEL_AN12:
            SET_BIT(TRISB,_TRISB_RB0_POSN);
             break;
         default: ;
     }
    
 }
   static inline void select_result_format(const adc_conf_t *_adc)
   {
       if((_adc->result_format) == (ADC_RESULT_RIGHT))
       {
           ADC_RESULT_RIGHT_FORMAT();
       }
       else if((_adc->result_format) == (ADC_RESULT_LEFT))
       {
           ADC_RESULT_LEFT_FORMAT();
       }
       else
       {
           
       }
               
           
   }

   
   static inline void select_voltage_refrence(const adc_conf_t *_adc)
   {
       if((_adc->voltage_referenc) == (ADC_VOLTAGE_REFERENCE_ENABLE))
       {
           ADC_ENABLE_VOLTAGE_REFERECE();
       }
       else if((_adc->voltage_referenc) == (ADC_VOLTAGE_REFERENCE_DISABLE))
       {
           ADC_DISABLE_VOLTAGE_REFERECE();
       }
       else
       {
           
       }
               
           
   }
  static inline void adc_select_channel_confiure(adc_channel_select_t channel)
 {
     switch(channel)
     {
        case ADC_CHANNEL_AN0:
            ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN0_ANALOG_FUNCTIONALITY);
             break;
       case ADC_CHANNEL_AN1:
            ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN1_ANALOG_FUNCTIONALITY);
             break;
        case ADC_CHANNEL_AN2:
            ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN2_ANALOG_FUNCTIONALITY);
            break;
       case ADC_CHANNEL_AN3:
            ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN3_ANALOG_FUNCTIONALITY);
             break;
       case ADC_CHANNEL_AN4:
            ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN4_ANALOG_FUNCTIONALITY);
             break;
       case ADC_CHANNEL_AN5:
            ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN5_ANALOG_FUNCTIONALITY);
             break;
        case ADC_CHANNEL_AN6:
            ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN6_ANALOG_FUNCTIONALITY);
            break;
       case ADC_CHANNEL_AN7:
            ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN7_ANALOG_FUNCTIONALITY);
             break;
       case ADC_CHANNEL_AN8:
            ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN8_ANALOG_FUNCTIONALITY);
             break;
       case ADC_CHANNEL_AN9:
            ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN9_ANALOG_FUNCTIONALITY);
             break;
        case ADC_CHANNEL_AN10:
            ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN10_ANALOG_FUNCTIONALITY);
            break;
       case ADC_CHANNEL_AN11:
            ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN11_ANALOG_FUNCTIONALITY);
             break;
             
         case ADC_CHANNEL_AN12:
            ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN12_ANALOG_FUNCTIONALITY);
             break;
     }
    
 }
  
  
 #if ADC_INTERRUPT_FEATURE == FEATURE_ENALE
 void ADC_ISR(void)
 {
     ADC_InterruptFlagClear();
    if(ADC_InterruptHandler != NULL)
    {
        ADC_InterruptHandler();
    }

 }
 #endif

 
 #if ADC_INTERRUPT_FEATURE == FEATURE_ENALE
/**
 * 
 * @param _adc
 * @param channel
 * @param conversion_result
 * @return 
 */
Std_ReturnType ADC_GetConversion_Interrupt(const adc_conf_t *_adc,adc_channel_select_t channel)
{
     Std_ReturnType ret = E_OK;
     uint8 conversion_status = 0;
     if(_adc != NULL )
     {
        ret =  ADC_SelectChannel(_adc,channel);
        ret = ADC_StartConversion(_adc);
    
     }
     else
     {
         ret = E_NOT_OK;
     }
     return ret;
}
#endif