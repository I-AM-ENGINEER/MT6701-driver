#include "mt6701_interface.h"

// Write your I2C memory byte write implementation, return 0 on seccess, else return 1
uint8_t mt6701_interface_i2c_write( uint8_t reg, uint8_t data ){
    
    return 0;
}

// Write your I2C memory byte read implementation, return 0 on seccess, else return 1
uint8_t mt6701_interface_i2c_read( uint8_t reg, uint8_t *data ){
    
    return 0;
}

// Write your SSI (SPI) read implementation, return 0 on seccess, else return 1
uint8_t mt6701_interface_ssi_read( uint8_t *data, uint8_t len ){
    
    return 0;
}

// Write your delay implementation
void mt6701_interface_delay( uint32_t ms ){

}

// If need, you can set debug printf function
void mt6701_interface_debug_print( const char *const fmt, ... ){

}
