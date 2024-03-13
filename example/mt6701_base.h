#include <stdint.h>
#include "mt6701.h"

uint8_t mt6701_simple_ssi_init( mt6701_handle_t *handle );
uint8_t mt6701_simple_i2c_init( mt6701_handle_t *handle );
uint8_t mt6701_simple_read_angle( mt6701_handle_t *handle, float *angle );
