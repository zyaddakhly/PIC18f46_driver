#include "hal_usart.h"


#if USART_TX_INTERRUPT_FEATURE == FEATURE_ENALE
static void (*USART_TX_InterruptHandler) (void) = NULL;      
#endif

#if USART_RX_INTERRUPT_FEATURE == FEATURE_ENALE
static void (*USART_RX_InterruptHandler) (void) = NULL;
static void (*USART_Framing_ERROR_InterruptHandler) (void) = NULL;      
static void (*USART_overrun_error_InterruptHandler) (void) = NULL;  
#endif
    

static void EUSART_Baud_Rate_Caculation(const usart_t * usart);
static void EUSART_ASYNC_TX_Init(const usart_t *usart);
static void EUSART_ASYNC_RX_Init(const usart_t *usart);
/**
 * 
 * @param usart
 * @return 
 */
Std_ReturnType EUSART_Init(const usart_t * usart)
{
    Std_ReturnType ret = E_OK;
    if(usart != NULL)
    {
        RCSTAbits.SPEN = EUSART_DISABLE;
        TRISCbits.RC7 = 1;
        TRISCbits.RC6 = 1;
        EUSART_Baud_Rate_Caculation( usart);
        EUSART_ASYNC_TX_Init(usart);
        EUSART_ASYNC_RX_Init(usart);
        
        
        
        
        RCSTAbits.SPEN = EUSART_ENABLE;

    }
    else
    {
        ret = E_NOT_OK;
                
                
    }
    return ret ;
    
}
/**
 * 
 * @param usart
 * @return 
 */
Std_ReturnType EUSART_DeInit(const usart_t * usart)
{
    Std_ReturnType ret = E_OK;
    if(usart != NULL)
    {
       RCSTAbits.SPEN = EUSART_DISABLE;
    }
    else
    {
        ret = E_NOT_OK;
                
                
    }
    return ret ;
    
}
/**
 * 
 * @param usart
 * @param data
 * @return 
 */
Std_ReturnType EUSART_ReadByeBlocking(uint8 *data)
{
    Std_ReturnType ret = E_OK;
    while(!PIR1bits.RCIF);
    *data = RCREG ;
    return ret ;
    
}   
/**
 * 
 * @param usart
 * @param data
 * @return 
 */
Std_ReturnType EUSART_WriteByeBlocking(uint8 data)
{
    Std_ReturnType ret = E_OK;
   
        while(!TXSTAbits.TRMT);
        #if USART_TX_INTERRUPT_FEATURE == FEATURE_ENALE
        USART_TX_InterruptEnable();
        #endif
       
        TXREG = data;
   
    return ret ;
    
}

Std_ReturnType EUSART_ReadByeNonBlocking(uint8 *data)
{
    Std_ReturnType ret = E_OK;
    if(PIR1bits.RCIF == 1)
    {
        *data = RCREG ;
        ret = E_OK;
    }
    else
    {
        ret = E_NOT_OK;
    }
    
    
    return ret ;


}

/**********************************************/

static void EUSART_Baud_Rate_Caculation(const usart_t * usart)
{
    float Baud_Rate_Temp = 0;
    switch (usart->baudrate_gen_config)
    {
        case BAUDRATE_ASYN_8BIT_LOW_SPEED: 
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED ;
            BAUDCONbits.BRG16 = EUSART_8BIT_BAUD_RATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ/(float)usart->baudrate)/64) - 1;
            break;
        case BAUDRATE_ASYN_8BIT_HIGH_SPEED: 
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED ;
            BAUDCONbits.BRG16 = EUSART_8BIT_BAUD_RATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ/(float)usart->baudrate)/16) - 1;

            break;
        case BAUDRATE_ASYN_16BIT_LOW_SPEED:                  
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED ;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUD_RATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ/(float)usart->baudrate)/16) - 1;
            break;
        case BAUDRATE_ASYN_16BIT_HIGH_SPEED:                  
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED ;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUD_RATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ/(float)usart->baudrate)/4) - 1;
            break;
        case BAUDRATE_SYN_8BIT:          
            TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_8BIT_BAUD_RATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ/(float)usart->baudrate)/4) - 1;
            break;
        case BAUDRATE_SYN_16BIT:  
            TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUD_RATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ/(float)usart->baudrate)/4) - 1;

            break;
        default : break;

    }
    SPBRG = (uint8)((uint32) Baud_Rate_Temp);
    SPBRGH = (uint8)(((uint32) Baud_Rate_Temp)>>8);

}

Std_ReturnType EUSART_WriteStringBlocking(uint8 *data)
{
    uint8 count = 0;
    while(*(data + count) != '\0')
    {
        EUSART_WriteByeBlocking((*(data + count)));
        count++;
    }
}

static void EUSART_ASYNC_TX_Init(const usart_t *usart)
{
    if(usart->usart_tx_cfg.usart_tx_enable == EUSART_ASYNCHRONOUS_TX_ENABLE )
    {
        TXSTAbits.TXEN = EUSART_ASYNCHRONOUS_TX_ENABLE;
        if(usart->usart_tx_cfg.usart_tx_interrupt_enable == EUSART_ASYNCCHRONOUS_INTERRUPT_TX_ENABLE)
        {
            #if USART_TX_INTERRUPT_FEATURE == FEATURE_ENALE
            #if INTERUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENALE
             INTERRUPT_PriorityLevelEnable();
             INTERRUPT_GlobalInterruptHighEnable();
             INTERRUPT_GlobalInterruptLowEnable();
             USART_TX_InterruptEnable();
            
             if(usart->usart_tx_cfg.tx_priority == INTERRUPT_HIGH_PRIORITY)
             {
                 USART_TX_HighPrioritySet();  
             }
             else if(usart->usart_tx_cfg.tx_priority == INTERRUPT_LOW_PRIORITY)
             {
                 USART_TX_LowPrioritySet(); 
             }
             else
             {

             }
             USART_TX_InterruptHandler = usart->ESART_TxDefaultInterruptHandler;
            #else
             INTERRUPT_GlobalInterruptEnable();
             INTERRUPT_PeripheralInterruptEnable();
             USART_TX_InterruptEnable();
             USART_TX_InterruptHandler = usart->ESART_TxDefaultInterruptHandler;


            #endif
            #endif
        }
        else if(usart->usart_tx_cfg.usart_tx_interrupt_enable == EUSART_ASYNCCHRONOUS_INTERRUPT_TX_DISABLE)

        {
            USART_TX_InterruptDisable();
        }
        else
        {

        }



        if(usart->usart_tx_cfg.usart_tx_9bit_enable == EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE)
        {
            TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE;
        }
        else if(usart->usart_tx_cfg.usart_tx_9bit_enable == EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE)

        {
            TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE;

        }
        else
        {
            

        }


    }
    else 
    {
        
    }
   

    
}
static void EUSART_ASYNC_RX_Init(const usart_t *usart)
{
    
    if(usart->usart_rx_cfg.usart_rx_enable == EUSART_ASYNCHRONOUS_RX_ENABLE )
    {
         USART_Framing_ERROR_InterruptHandler  = usart->ESART_FramingErrorInterruptHandler;  
         USART_overrun_error_InterruptHandler  = usart->ESART_OverrunErrorInterruptHandler;
        RCSTAbits.CREN = EUSART_ASYNCHRONOUS_RX_ENABLE;
         if(usart->usart_rx_cfg.usart_rx_interrupt_enable == EUSART_ASYNCCHRONOUS_INTERRUPT_RX_ENABLE)
         {
            #if USART_RX_INTERRUPT_FEATURE == FEATURE_ENALE
            #if INTERUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENALE
             INTERRUPT_PriorityLevelEnable();
             INTERRUPT_GlobalInterruptHighEnable();
             INTERRUPT_GlobalInterruptLowEnable();
             USART_RX_InterruptEnable();
            
             if(usart->usart_rx_cfg.rx_priority == INTERRUPT_HIGH_PRIORITY)
             {
                 USART_RX_HighPrioritySet();  
             }
             else if(usart->usart_rx_cfg.rx_priority == INTERRUPT_LOW_PRIORITY)
             {
                 USART_RX_LowPrioritySet(); 
             }
             else
             {

             }
             USART_RX_InterruptHandler = usart->ESART_RxDefaultInterruptHandler;
            #else
             INTERRUPT_GlobalInterruptEnable();
             INTERRUPT_PeripheralInterruptEnable();
             USART_RX_InterruptEnable();
             USART_RX_InterruptHandler = usart->ESART_RxDefaultInterruptHandler;


            #endif
            #endif
         }
         else  if(usart->usart_rx_cfg.usart_rx_interrupt_enable == EUSART_ASYNCCHRONOUS_INTERRUPT_RX_DISABLE)

         {
                 USART_RX_InterruptDisable();

         }
         else
         {

         }


         if(usart->usart_rx_cfg.usart_rx_9bit_enable == EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE)
         {
             RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE;
         }
         else if(usart->usart_rx_cfg.usart_rx_9bit_enable == EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE)

         {
             RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE;

         }
         else
         {

         }
    }
    else  
    {
        
    }
  

 
    
    
    
    
    
    
    
}



#if USART_TX_INTERRUPT_FEATURE == FEATURE_ENALE
 void USART_TX_ISR(void)
 {
     USART_TX_InterruptDisable();
    if(USART_TX_InterruptHandler != NULL)
    {
        USART_TX_InterruptHandler();
    }

 }
 #endif

 #if USART_RX_INTERRUPT_FEATURE == FEATURE_ENALE
 void USART_RX_ISR(void)
 {
    if(USART_RX_InterruptHandler != NULL)
    {
        uint8 temp = 0;
        USART_RX_InterruptHandler();
        temp = RCREG;
    }
    else
    {
        
    }        
                     
    if(USART_Framing_ERROR_InterruptHandler != NULL)
    {
           USART_Framing_ERROR_InterruptHandler();
    }
    else
    {
             
            
    }
    if(USART_overrun_error_InterruptHandler != NULL)
    {
             USART_overrun_error_InterruptHandler();
    }
    else
    {
             
            
    }

 }
 #endif

 
 Std_ReturnType EUSART_ASYNC_RX_Restart(void)
 {
     Std_ReturnType ret = E_OK;
     RCSTAbits.CREN = 0;
     RCSTAbits.CREN = 1;

     
     return ret;
 }