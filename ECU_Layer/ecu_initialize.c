#include "ecu_initialize.h"

/*
ccp2_t _ccp2 = 
{
    .CCP2_INterruptHandler = NULL,
    .ccp2_mode = CCP2_PWM_MODE_SELECT,
    .PWM_Frequency = 20000,
    .pin.port = PORTC_INDEX,
    .pin.pin  = GPIO_PIN1,
    .pin.direction = GPIO_OUTPUT,
    .pin.logic = GPIO_HIGH,
    .timer2_postscaler_vlaue = 1,
    .timer2_prescaler_value = 1
    
};
ccp1_t _ccp1 = 
{
    .CCP1_INterruptHandler = NULL,
    .ccp1_mode = CCP1_PWM_MODE_SELECT,
    .PWM_Frequency = 20000,
    .pin.port = PORTC_INDEX,
    .pin.pin  = GPIO_PIN2,
    .pin.direction = GPIO_OUTPUT,
    .pin.logic = GPIO_HIGH,
    .timer2_postscaler_vlaue = 1,
    .timer2_prescaler_value = 1
    
};
timer2_t timer2 = 
{
    .TIMER2_INterruptHandler = NULL,
    .timer2_postscaler_vlaue = TIMER2_POSTSCALER_DIV_BY_1 ,
    .timer2_prescaler_value = TIMER2_PRESCALER_DIV_BY_1,
    .timer2_preload_value = 0
    
};


lcd_4bit_t lcd_1 = 
{
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN0,
    .lcd_rs.direction = GPIO_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,
    
    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = GPIO_PIN3,
    .lcd_en.direction = GPIO_OUTPUT,
    .lcd_en.logic = GPIO_LOW,
    
    
    .lcd_data[0].port = PORTC_INDEX,
    .lcd_data[0].pin = GPIO_PIN4,
    .lcd_data[0].direction = GPIO_OUTPUT,
    .lcd_data[0].logic= GPIO_LOW,
    
    
    .lcd_data[1].port = PORTC_INDEX,
    .lcd_data[1].pin = GPIO_PIN5,
    .lcd_data[1].direction = GPIO_OUTPUT,
    .lcd_data[1].logic= GPIO_LOW,
    
    .lcd_data[2].port = PORTC_INDEX,
    .lcd_data[2].pin = GPIO_PIN6,
    .lcd_data[2].direction = GPIO_OUTPUT,
    .lcd_data[2].logic= GPIO_LOW,
    
    
    .lcd_data[3].port = PORTC_INDEX,
    .lcd_data[3].pin = GPIO_PIN7,
    .lcd_data[3].direction = GPIO_OUTPUT,
    .lcd_data[3].logic= GPIO_LOW,
    
    
    
    
};*/
led_t led =
{
    .port = PORTD_INDEX,
    .pin = GPIO_PIN0,
    .led_status = LED_OFF,
    
};


void ecu_initialize(void)
{
    Std_ReturnType ret = E_NOT_OK;
    /*
  ret = CCP2_Init(&_ccp2);
  ret = CCP1_Init(&_ccp1);

  */
    /*
  lcd_4bit_initialize(&lcd_1);*/

    /*Seven Seg*/
    /*
    Std_ReturnType ret = E_NOT_OK;*/
    ret = led_initialize(&led);
    
  
}

