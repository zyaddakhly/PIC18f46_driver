#include "hal_i2c.h"




/**
 * 
 * @param i2c_obj
 * @return 
 */

#if MSSP_I2C_NTERRUPT_FEATURE  == FEATURE_ENALE
static void (*MSSP_I2C_InterruptHandler) (void) = NULL;  
static void (*MSSP_I2C_BUS_COL_InterruptHandler) (void) = NULL;      
static void (*MSSP_I2C_OVERFLOW_InterruptHandler) (void) = NULL;      

#endif



static inline void I2C_Slave_Mode_Configurations(const mssp_i2c_t *i2c_obj);

static inline void I2C_Master_Mode_Clock(const mssp_i2c_t *i2c_obj);

Std_ReturnType MSSP_I2C_Init(const mssp_i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_OK;
    if(i2c_obj != NULL)
    {
        MSSP_MODULE_DISABLE();
        
        if(i2c_obj->i2c_cfg.i2c_mode == MSSP_I2C_MASTER_MODE)
        {
            I2C_Master_Mode_Clock(i2c_obj);
        }
        else if (i2c_obj->i2c_cfg.i2c_mode == MSSP_I2C_SLAVE_MODE)
        {
            if(i2c_obj->i2c_cfg.i2c_general_call == I2C_GENERAL_CALL_ENABLE)
            {
                I2C_GENERAL_CALL_ENABLE_CFG();
            }
            else if(i2c_obj->i2c_cfg.i2c_general_call == I2C_GENERAL_CALL_DISABLE)
            {
                I2C_GENERAL_CALL_DISABLE_CFG();
            }
            else
            {
                
            }
             SSPCON1bits.WCOL = 0; /* No Collision */
            /* Clear the Receive Overflow Indicator */
            SSPCON1bits.SSPOV = 0; /* No Overflow */
            /* Release the clock */
            SSPCON1bits.CKP = 1;
            /* Assign the I2C Slave Address */
            SSPADD = i2c_obj->i2c_cfg.i2c_slave_address;
            /* I2C Slave Mode Configurations */
            I2C_Slave_Mode_Configurations(i2c_obj);
            
            
            
        }
        else
        {
            
        }
        TRISCbits.TRISC3 = 1;
        TRISCbits.TRISC4 = 1;
        if(i2c_obj->i2c_cfg.i2c_slew_rate == I2C_SLEW_RATE_ENABLE )
            {
                I2C_SLEW_RATE_ENABLE_CFG();
            }
            else if(i2c_obj->i2c_cfg.i2c_slew_rate == I2C_SLEW_RATE_DISABLE)
            {
                I2C_SLEW_RATE_DISABLE_CFG();
            }
            else
            {
                
            }
            #if MSSP_I2C_NTERRUPT_FEATURE  == FEATURE_ENALE
            #if INTERUPT_PRIORITY_LEVELS_ENABLE == FEATURE_ENALE
             INTERRUPT_PriorityLevelEnable();
             INTERRUPT_GlobalInterruptLowEnable();
             INTERRUPT_GlobalInterruptHighEnable();
             MSSP_I2C_InterruptEnable();
             MSSP_I2C_BUS_COL_InterruptEnable();
             if(i2c_obj->i2c_cfg.mssp_priority == INTERRUPT_HIGH_PRIORITY)
             {
                 MSSP_I2C_HighPrioritySet();  

             }
             else if(i2c_obj->i2c_cfg.mssp_priority == INTERRUPT_LOW_PRIORITY)
             {
                 MSSP_I2C_LowPrioritySet(); 

             }
             else
             {

             }
             if(i2c_obj->i2c_cfg.mssp_col_priority == INTERRUPT_HIGH_PRIORITY)
             {
                 MSSP_I2C_BUS_COL_HighPrioritySet();  

             }
             else if(i2c_obj->i2c_cfg.mssp_col_priority  == INTERRUPT_LOW_PRIORITY)
             {
                 MSSP_I2C_BUS_COL_LowPrioritySet(); 

             }
             else
             {

             }
             MSSP_I2C_InterruptHandler =i2c_obj->I2C_Report_DefaultInterruptHandler;
             MSSP_I2C_BUS_COL_InterruptHandler =i2c_obj->I2C_Report_Write_Collision;
             MSSP_I2C_OVERFLOW_InterruptHandler =i2c_obj->I2C_Report_Receieve_Overflow;
             #else
             INTERRUPT_GlobalInterruptEnable();
             INTERRUPT_PeripheralInterruptEnable();
             MSSP_I2C_InterruptEnable();
             MSSP_I2C_BUS_COL_InterruptEnable();
             MSSP_I2C_InterruptFlagClear();
             MSSP_I2C_BUS_COL_InterruptFlagClear();

             MSSP_I2C_InterruptHandler =i2c_obj->I2C_Report_DefaultInterruptHandler;
             MSSP_I2C_BUS_COL_InterruptHandler =i2c_obj->I2C_Report_Write_Collision;
             MSSP_I2C_OVERFLOW_InterruptHandler =i2c_obj->I2C_Report_Receieve_Overflow;


            #endif
            #endif
            
            
            if(i2c_obj->i2c_cfg.i2c_SMBus_control == I2C_SMBus_ENABLE )
            {
                I2C_SMBus_ENABLE_CFG();
            }
            else if(i2c_obj->i2c_cfg.i2c_SMBus_control  == I2C_SMBus_DISABLE )
            {
                I2C_SMBus_DISABLE_CFG();
            }
            else
            {
                
            }
 
 
        
        
        
        
        MSSP_MODULE_ENABLE();
    }
    else
    {
        ret = E_NOT_OK;
    }
    
    
    
    
    return ret;
}
/**
 * 
 * @param i2c_obj
 * @return 
 */
Std_ReturnType MSSP_I2C_DeInit(const mssp_i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_OK;
    if(i2c_obj != NULL)
    {
        MSSP_MODULE_DISABLE();

        #if MSSP_I2C_NTERRUPT_FEATURE  == FEATURE_ENALE
           MSSP_I2C_InterruptDisable();
           MSSP_I2C_BUS_COL_InterruptDisable();
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
 * @param i2c_obj
 * @return 
 */
Std_ReturnType MSSP_I2C_Master_Send_Start(const mssp_i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_OK;
    if(i2c_obj != NULL)
    {
        SSPCON2bits.SEN = 1;
        while(SSPCON2bits.SEN);
        PIR1bits.SSPIF = 0;
        if(START_BIT_DETECTED  == SSPSTATbits.S )
        {
            ret = E_OK;
        }
        else
        {
            ret = E_NOT_OK;
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
 * @param i2c_obj
 * @return 
 */
Std_ReturnType MSSP_I2C_Master_Send_Repeated_Start(const mssp_i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_OK;
    if(i2c_obj != NULL)
    {
        SSPCON2bits.RSEN = 1;
        while (SSPCON2bits.RSEN);
        PIR1bits.SSPIF = 0;
        
    }
    else
    {
        ret = E_NOT_OK;
    }
    
    
    
    
    return ret;
}
/**
 * 
 * @param i2c_obj
 * @return 
 */
Std_ReturnType MSSP_I2C_Master_Send_Stop(const mssp_i2c_t *i2c_obj)
{
    Std_ReturnType ret = E_OK;
    if(i2c_obj != NULL)
    {
        SSPCON2bits.PEN = 1;
        while(SSPCON2bits.PEN);
        PIR1bits.SSPIF = 0;
        if(STOP_BIT_DETECTED  == SSPSTATbits.P )
        {
            ret = E_OK;
        }
        else
        {
            ret = E_NOT_OK;
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
 * @param i2c_obj
 * @param data
 * @return 
 */
Std_ReturnType MSSP_I2C_Write(const mssp_i2c_t *i2c_obj,uint8 data,uint8 * ack)
{
    Std_ReturnType ret = E_OK;
    if(i2c_obj != NULL && ack != NULL )
    {
        SSPBUF = data;
        while(SSPSTATbits.BF);
        PIR1bits.SSPIF = 0;
        if(I2C_ACK_REC_FROM_SLAVE  == SSPCON2bits.ACKSTAT)
        {
            *ack = I2C_ACK_REC_FROM_SLAVE;
        }
        else
        {
            *ack = I2C_ACK_NOT_REC_FROM_SLAVE;

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
 * @param i2c_obj
 * @param ack
 * @param data
 * @return 
 */
Std_ReturnType MSSP_I2C_Read(const mssp_i2c_t *i2c_obj,uint8 ack,uint8 * data)
{
    Std_ReturnType ret = E_OK;
    if(i2c_obj != NULL && data != NULL)
    {
        I2C_MASTER_RECEIVE_ENABLE_CFG();
        while(!SSPSTATbits.BF);
        *data = SSPBUF;
        if(ack == I2C_MASTER_SEND_ACK )
        {
            SSPCON2bits.ACKDT = 0;
            SSPCON2bits.ACKEN = 1;

        }
        else if(ack == I2C_MASTER_SEND_NOT_ACK )
        {
            SSPCON2bits.ACKDT = 1;
            SSPCON2bits.ACKEN = 1;


        }
        else
        {
            
        }
        
    }
    else
    {
        ret = E_NOT_OK;
    }
    
    
    
    
    return ret;
}

static inline void I2C_Master_Mode_Clock(const mssp_i2c_t *i2c_obj)
{
    SSPCON1bits.SSPM = I2C_MASTER_MODE_DEFINED_CLOCK ;
    SSPADD = (uint8)(((_XTAL_FREQ / 4.0) / i2c_obj->i2c_clock)-1);
}


#if MSSP_I2C_NTERRUPT_FEATURE  == FEATURE_ENALE
 void MSSP_I2C_ISR(void)
 {
    MSSP_I2C_InterruptFlagClear();
    if(MSSP_I2C_InterruptHandler != NULL)
    {
        MSSP_I2C_InterruptHandler();
    }

 }
 #endif
#if MSSP_I2C_NTERRUPT_FEATURE  == FEATURE_ENALE
 void MSSP_I2C_COL_ISR(void)
 {
    MSSP_I2C_BUS_COL_InterruptFlagClear();
    if(MSSP_I2C_BUS_COL_InterruptHandler != NULL)
    {
        MSSP_I2C_BUS_COL_InterruptHandler();
    }

 }
 #endif

static inline void I2C_Slave_Mode_Configurations(const mssp_i2c_t *i2c_obj){
    SSPCON1bits.SSPM = i2c_obj->i2c_cfg.i2c_mode_cfg;
}