#include "ecu_dc_motor.h"



/**
 * 
 * @param dc_motor
 * @return 
 */

Std_ReturnType dc_motor_initialize(const dc_motor_t *dc_motor)
{
    Std_ReturnType ret = E_OK;
    if(dc_motor != NULL)
    {
    
        ret = gpio_pin_initalize(&(dc_motor->dc_motor[0]));
        ret = gpio_pin_initalize(&(dc_motor->dc_motor[1]));
        
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
    
}
/**
 * 
 * @param dc_motor
 * @return 
 */
Std_ReturnType dc_motor_move_right(const dc_motor_t *dc_motor)
{
    Std_ReturnType ret = E_OK;
    if(dc_motor != NULL)
    {

        ret = gpio_pin_write_logic(&(dc_motor->dc_motor[0]),GPIO_HIGH);
        ret = gpio_pin_write_logic(&(dc_motor->dc_motor[1]),GPIO_LOW);
        
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
    
}
/**
 * 
 * @param dc_motor
 * @return 
 */
Std_ReturnType dc_motor_move_left(const dc_motor_t *dc_motor)
{
    Std_ReturnType ret = E_OK;
    if(dc_motor != NULL)
    {

        ret = gpio_pin_write_logic(&(dc_motor->dc_motor[0]),GPIO_LOW);
        ret = gpio_pin_write_logic(&(dc_motor->dc_motor[1]),GPIO_HIGH);
        
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
    
}
/**
 * 
 * @param dc_motor
 * @return 
 */
Std_ReturnType dc_motor_stop(const dc_motor_t *dc_motor)
{
    Std_ReturnType ret = E_OK;
    if(dc_motor != NULL)
    {

        ret = gpio_pin_write_logic(&(dc_motor->dc_motor[0]),GPIO_LOW);
        ret = gpio_pin_write_logic(&(dc_motor->dc_motor[0]),GPIO_LOW);
        
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;
    
}