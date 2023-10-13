#include "mcal_interrupt_manager.h"



#if INTERUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENALE

void __interrupt() InterruptManagerHigh(void)
{
    if((INTCONbits.INT0IE == INTERRUPT_ENABLE) && (INTCONbits.INT0F  == INTERRUPT_OCCUR  ))
    {
        INT0_ISR();
    }
    else
    {
        
    }
    

    /**
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIE  == INTERRUPT_OCCUR  )&&(PORTBbits.RB5 == 1))
    {
        RB1_ISR();
    }
    else
    {
        
    }
    
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIE  == INTERRUPT_OCCUR  )&&(PORTBbits.RB6 == 1))
    {
        RB2_ISR();
    }
    else
    {
        
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIE  == INTERRUPT_OCCUR  )&&(PORTBbits.RB7 == 1))
    {
        RB3_ISR();
    }
    else
    {
        
    }
    **/
    
    if((INTCON3bits.INT1E == INTERRUPT_ENABLE) && (INTCON3bits.INT1IF  == INTERRUPT_OCCUR  ) )
    {
        INT1_ISR();
    }
    else
    {
        
    }
    if((INTCON3bits.INT2E == INTERRUPT_ENABLE) && (INTCON3bits.INT2F  == INTERRUPT_OCCUR  ))
    {
        INT2_ISR();
    }
    else
    {
        
    }
    
     if((INTCON3bits.INT1E == INTERRUPT_ENABLE) && (INTCON3bits.INT1IF  == INTERRUPT_OCCUR  ) )
    {
        INT1_ISR();
    }
    else
    {
        
    }
    /*ADC*/
    if((PIE1bits.ADIE == INTERRUPT_ENABLE) && (PIR1bits.ADIF  == INTERRUPT_OCCUR  ))
    {
        ADC_ISR();
    }
    else
    {
        
    }
    if((INTCONbits.TMR0IE == INTERRUPT_ENABLE) && (INTCONbits.TMR0IF  == INTERRUPT_OCCUR  ))
    {
        TIMER0_ISR();
    }
    else
    {
        
    }
    /*TIMER0*/
    if((INTCONbits.TMR0IE == INTERRUPT_ENABLE) && (INTCONbits.TMR0IF  == INTERRUPT_OCCUR  ))
    {
        TIMER0_ISR();
    }
    else
    {
        
    }
        /*TIMER1*/
    if((PIE1bits.TMR1IE == INTERRUPT_ENABLE) && (PIR1bits.TMR1IF  == INTERRUPT_OCCUR  ))
    {
        TIMER1_ISR();
    }
    else
    {
        
    }
    /*TIMER2*/
    if((PIE1bits.TMR2IE == INTERRUPT_ENABLE) && (PIR1bits.TMR2IF  == INTERRUPT_OCCUR  ))
    {
        TIMER2_ISR();
    }
    else
    {
        
    }
        /*TIMER3*/

    if((PIE2bits.TMR3IE == INTERRUPT_ENABLE) && (PIR2bits.TMR3IF  == INTERRUPT_OCCUR  ))
    {
        TIMER3_ISR();
    }
    else
    {
        
    }
           /*CCP1*/

    if((PIE1bits.CCP1IE == INTERRUPT_ENABLE) && (PIR1bits.CCP1IF  == INTERRUPT_OCCUR  ))
    {
        CCP1_ISR();
    }
    else
    {
        
    }
               /*CCP2*/

    if((PIE2bits.CCP2IE == INTERRUPT_ENABLE) && (PIR2bits.CCP2IF  == INTERRUPT_OCCUR  ))
    {
        CCP2_ISR();
    }
    else
    {
        
    }
                   /*TX*/

    if((PIE1bits.TXIE == INTERRUPT_ENABLE) && (PIR1bits.TXIF  == INTERRUPT_OCCUR  ))
    {
        USART_TX_ISR();
    }
    else
    {
        
    }
                       /*RX*/

    if((PIE1bits.RCIE == INTERRUPT_ENABLE) && (PIR1bits.RCIF  == INTERRUPT_OCCUR  ))
    {
        USART_RX_ISR();
    }
    else
    {
        
    }
    /*MSSP I2C*/
    if((PIE1bits.SSPIE == INTERRUPT_ENABLE) && (PIR1bits.SSPIF  == INTERRUPT_OCCUR  ))
    {
        MSSP_I2C_ISR();
    }
    else
    {
        
    }
    
        /*MSSP I2C Bus Col*/
    if((PIE2bits.BCLIE == INTERRUPT_ENABLE) && (PIR2bits.BCLIF  == INTERRUPT_OCCUR  ))
    {
        MSSP_I2C_COL_ISR();
    }
    else
    {
        
    }
    
    
}

void __interrupt(low_priority) InterruptManagerLow(void)
{
        /*ADC*/
    if((PIE1bits.ADIE == INTERRUPT_ENABLE) && (PIR1bits.ADIF  == INTERRUPT_OCCUR  ))
    {
        ADC_ISR();
    }
    else
    {
        
    }
            /*TIMER0*/
    if((INTCONbits.TMR0IE == INTERRUPT_ENABLE) && (INTCONbits.TMR0IF  == INTERRUPT_OCCUR  ))
    {
        TIMER0_ISR();
    }
    else
    {
        
    }
    /*TIMER1*/
    if((PIE1bits.TMR1IE == INTERRUPT_ENABLE) && (PIR1bits.TMR1IF  == INTERRUPT_OCCUR  ))
    {
        TIMER1_ISR();
    }
    else
    {
        
    }
        /*TIMER2*/
     if((PIE1bits.TMR2IE == INTERRUPT_ENABLE) && (PIR1bits.TMR2IF  == INTERRUPT_OCCUR  ))
    {
        TIMER2_ISR();
    }
    else
    {
        
    }
    /*TIMER3*/
    if((PIE2bits.TMR3IE == INTERRUPT_ENABLE) && (PIR2bits.TMR3IF  == INTERRUPT_OCCUR  ))
    {
        TIMER3_ISR();
    }
    else
    {
        
    }
               /*CCP1*/

    if((PIE1bits.CCP1IE == INTERRUPT_ENABLE) && (PIR1bits.CCP1IF  == INTERRUPT_OCCUR  ))
    {
        CCP1_ISR();
    }
    else
    {
        
    }
               /*CCP2*/

    if((PIE2bits.CCP2IE == INTERRUPT_ENABLE) && (PIR2bits.CCP2IF  == INTERRUPT_OCCUR  ))
    {
        CCP2_ISR();
    }
    else
    {
        
    }
                       /*TX*/

    if((PIE1bits.TXIE == INTERRUPT_ENABLE) && (PIR1bits.TXIF  == INTERRUPT_OCCUR  ))
    {
        USART_TX_ISR();
    }
    else
    {
        
    }
                       /*RX*/

    if((PIE1bits.RCIE == INTERRUPT_ENABLE) && (PIR1bits.RCIF  == INTERRUPT_OCCUR  ))
    {
        USART_RX_ISR();
    }
    else
    {
        
    }
        /*MSSP I2C*/
    if((PIE1bits.SSPIE == INTERRUPT_ENABLE) && (PIR1bits.SSPIF  == INTERRUPT_OCCUR  ))
    {
        MSSP_I2C_ISR();
    }
    else
    {
        
    }
    
        /*MSSP I2C Bus Col*/
    if((PIE2bits.BCLIE == INTERRUPT_ENABLE) && (PIR2bits.BCLIF  == INTERRUPT_OCCUR  ))
    {
        MSSP_I2C_COL_ISR();
    }
    else
    {
        
    }


        

}
#else

void __interrupt() InterruptManagerHigh(void)
{
    if((INTCONbits.INT0IE == INTERRUPT_ENABLE) && (INTCONbits.INT0F  == INTERRUPT_OCCUR  ))
    {
        INT0_ISR();
    }
    else
    {
        
    }
    

    /**
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIE  == INTERRUPT_OCCUR  )&&(PORTBbits.RB5 == 1))
    {
        RB1_ISR();
    }
    else
    {
        
    }
    
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIE  == INTERRUPT_OCCUR  )&&(PORTBbits.RB6 == 1))
    {
        RB2_ISR();
    }
    else
    {
        
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIE  == INTERRUPT_OCCUR  )&&(PORTBbits.RB7 == 1))
    {
        RB3_ISR();
    }
    else
    {
        
    }
    **/
    
    if((INTCON3bits.INT1E == INTERRUPT_ENABLE) && (INTCON3bits.INT1IF  == INTERRUPT_OCCUR  ) )
    {
        INT1_ISR();
    }
    else
    {
        
    }
    if((INTCON3bits.INT2E == INTERRUPT_ENABLE) && (INTCON3bits.INT2F  == INTERRUPT_OCCUR  ))
    {
        INT2_ISR();
    }
    else
    {
        
    }
    
     if((INTCON3bits.INT1E == INTERRUPT_ENABLE) && (INTCON3bits.INT1IF  == INTERRUPT_OCCUR  ) )
    {
        INT1_ISR();
    }
    else
    {
        
    }
    /*ADC*/
    if((PIE1bits.ADIE == INTERRUPT_ENABLE) && (PIR1bits.ADIF  == INTERRUPT_OCCUR  ))
    {
        ADC_ISR();
    }
    else
    {
        
    }
    if((INTCONbits.TMR0IE == INTERRUPT_ENABLE) && (INTCONbits.TMR0IF  == INTERRUPT_OCCUR  ))
    {
    }
    else
    {
        
    }
     /*TIMER1*/
    if((PIE1bits.TMR1IE == INTERRUPT_ENABLE) && (PIR1bits.TMR1IF  == INTERRUPT_OCCUR  ))
    {
        TIMER1_ISR();
    }
    else
    {
        
    }
    
            /*TIMER2*/
     if((PIE1bits.TMR2IE == INTERRUPT_ENABLE) && (PIR1bits.TMR2IF  == INTERRUPT_OCCUR  ))
    {
        TIMER2_ISR();
    }
    else
    {
        
    }
    
    /*TIMER3*/
    if((PIE2bits.TMR3IE == INTERRUPT_ENABLE) && (PIR2bits.TMR3IF  == INTERRUPT_OCCUR  ))
    {
        TIMER3_ISR();
    }
    else
    {
        
    }
               /*CCP1*/

    if((PIE1bits.CCP1IE == INTERRUPT_ENABLE) && (PIR1bits.CCP1IF  == INTERRUPT_OCCUR  ))
    {
        CCP1_ISR();
    }
    else
    {
        
    }
               /*CCP2*/

    if((PIE2bits.CCP2IE == INTERRUPT_ENABLE) && (PIR2bits.CCP2IF  == INTERRUPT_OCCUR  ))
    {
        CCP2_ISR();
    }
    else
    {
        
    }
                   /*TX*/

    if((PIE1bits.TXIE == INTERRUPT_ENABLE) && (PIR1bits.TXIF  == INTERRUPT_OCCUR  ))
    {
        USART_TX_ISR();
    }
    else
    {
        
    }
                       /*RX*/

    if((PIE1bits.RCIE == INTERRUPT_ENABLE) && (PIR1bits.RCIF  == INTERRUPT_OCCUR  ))
    {
        USART_RX_ISR();
    }
    else
    {
        
    }
        /*MSSP I2C*/
    if((PIE1bits.SSPIE == INTERRUPT_ENABLE) && (PIR1bits.SSPIF  == INTERRUPT_OCCUR  ))
    {
        MSSP_I2C_ISR();
    }
    else
    {
        
    }
    
        /*MSSP I2C Bus Col*/
    if((PIE2bits.BCLIE == INTERRUPT_ENABLE) && (PIR2bits.BCLIF  == INTERRUPT_OCCUR  ))
    {
        MSSP_I2C_COL_ISR();
    }
    else
    {
        
    }

    
}

    


#endif




