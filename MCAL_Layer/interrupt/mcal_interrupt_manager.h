#ifndef _MCAL_INTERRUPT_MANAGER_H_
#define _MCAL_INTERRUPT_MANAGER_H_


/*Section : Include */
#include "mcal_interrupt_config.h"

/*Section : Function Decleration*/
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);

void RB0_ISR(void);
void RB1_ISR(void);
void RB2_ISR(void);
void RB3_ISR(void);



 void ADC_ISR(void);
 void TIMER0_ISR(void);
 void TIMER1_ISR(void);
 void TIMER2_ISR(void);
 void TIMER3_ISR(void);
 void CCP1_ISR(void);
 void CCP2_ISR(void);
 void USART_TX_ISR(void);
 void USART_RX_ISR(void);
 
 void MSSP_I2C_ISR(void);
 void MSSP_I2C_COL_ISR(void);

#endif