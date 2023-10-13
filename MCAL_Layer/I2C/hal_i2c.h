/* 
 * File:   hal_i2c.h
 * Author: zyadi
 *
 * Created on October 8, 2023, 7:10 AM
 */

#ifndef HAL_I2C_H
#define	HAL_I2C_H

/*Section : Include */
#include "../../pic/include/proc/pic18f4620.h"
#include "../interrupt/mcal_internal_interrupt.h"
#include "../GPIO/hall_gpio.h"


/*Section macro declaration*/
#define I2C_SLEW_RATE_DISABLE     1
#define I2C_SLEW_RATE_ENABLE      0

#define I2C_SMBus_ENABLE      1
#define I2C_SMBus_DISABLE     0


#define I2C_ACK_REC_FROM_SLAVE  0
#define I2C_ACK_NOT_REC_FROM_SLAVE  1


#define I2C_LAST_BYTE_DATA      1
#define I2C_LAST_BYTE_ADDRESS   0

#define STOP_BIT_DETECTED           1
#define STOP_BIT_NOT_DETECTED       0


#define START_BIT_DETECTED           1
#define START_BIT_NOT_DETECTED       0



#define MSSP_I2C_MASTER_MODE        1
#define MSSP_I2C_SLAVE_MODE         0

#define I2C_GENERAL_CALL_ENABLE     1
#define I2C_GENERAL_CALL_DISABLE    0


#define I2C_MASTER_RECEIVE_ENABLE       1
#define I2C_MASTER_RECEIVE_ENABLE       0



#define I2C_SLAVE_MODE_7BIT_ADDRESS                       0x06U
#define I2C_SLAVE_MODE_10BIT_ADDRESS                      0x07U
#define I2C_SLAVE_MODE_7BIT_ADDRESS_INTURRUTP_ENABLE      0x0EU
#define I2C_SLAVE_MODE_10BIT_ADDRESS_INTURRUTP_ENABLE     0x0FU
#define I2C_MASTER_MODE_DEFINED_CLOCK                     0x08U
#define I2C_MASTER_MODE_FIRMWARE_CONTROLLED               0x0BU





/*Section : macro function declaration */

#define MSSP_MODULE_ENABLE()        (SSPCON1bits.SSPEN = 1)
#define MSSP_MODULE_DISABLE()       (SSPCON1bits.SSPEN = 0)

#define I2C_SLEW_RATE_DISABLE_CFG()     (SSPSTATbits.SMP = 1)
#define I2C_SLEW_RATE_ENABLE_CFG()      (SSPSTATbits.SMP = 0)

#define I2C_SMBus_DISABLE_CFG()         (SSPSTATbits.CKE = 0)
#define I2C_SMBus_ENABLE_CFG()          (SSPSTATbits.CKE = 1)


#define I2C_GENERAL_CALL_ENABLE_CFG()   (SSPCON2bits.GCEN = 0)
#define I2C_GENERAL_CALL_DISABLE_CFG()  (SSPCON2bits.GCEN = 1)


#define I2C_MASTER_RECEIVE_DISABLE_CFG() (SSPCON2bits.RCEN = 0)
#define I2C_MASTER_RECEIVE_ENABLE_CFG()  (SSPCON2bits.RCEN = 1)

#define I2C_CLOCK_STRETCH_ENABLE()        (SSPCON1bits.CKP = 0)
#define I2C_CLOCK_STRETCH_DISABLE()        (SSPCON1bits.CKP = 1)

#define I2C_MASTER_SEND_ACK  0
#define I2C_MASTER_SEND_NOT_ACK  1



/*Section : User data type declaration*/
typedef struct
{
    uint8 i2c_mode_cfg;
    uint8 i2c_slave_address;
    uint8 i2c_mode : 1;
    uint8 i2c_slew_rate :1;
    uint8 i2c_SMBus_control : 1;
    uint8 i2c_general_call  : 1;
    uint8 i2c_master_rec_mode : 1;
    uint8 i2c_reserved : 3;
    #if MSSP_I2C_NTERRUPT_FEATURE  == FEATURE_ENALE
    uint8 mssp_priority;
    uint8 mssp_col_priority;
    #endif
    

    
}i2c_config_t;

typedef struct 
{
    uint64 i2c_clock;
    #if MSSP_I2C_NTERRUPT_FEATURE  == FEATURE_ENALE
    void(*I2C_Report_Write_Collision) (void);
    void(*I2C_Report_DefaultInterruptHandler) (void);
    void(*I2C_Report_Receieve_Overflow) (void);

    #endif 

    i2c_config_t i2c_cfg;

}mssp_i2c_t;

/*Section : fuction declaration*/


Std_ReturnType MSSP_I2C_Init(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_DeInit(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_Master_Send_Start(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_Master_Send_Repeated_Start(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_Master_Send_Stop(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_Write(const mssp_i2c_t *i2c_obj,uint8 data,uint8 * ack);
Std_ReturnType MSSP_I2C_Read(const mssp_i2c_t *i2c_obj,uint8 ack,uint8 * data);

#endif	/* HAL_I2C_H */

