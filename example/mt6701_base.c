#include <stdlib.h>
#include <stdbool.h>
#include "mt6701_interface.h"
#include "mt6701_base.h"

// If need, you can set debug printf function
void mt6701_print( const char *const fmt, ... ){

}

uint8_t mt6701_simple_i2c_init( mt6701_handle_t *handle ){
	uint8_t res = 0;

	if(handle == NULL){
		return MT6701_ERR_HANDLER_NULL;
	}

	handle->delay = mt6701_interface_delay;
	handle->i2c_read = mt6701_interface_i2c_read;
	handle->i2c_write = mt6701_interface_i2c_write;

	res = mt6701_interface_set(handle, MT6701_INTERFACE_I2C);
	if(res != MT6701_OK){
		mt6701_print("mt6701: Cannot set interface: %d\n", res);
		return res + 100;
	}

	res = mt6701_init(handle);
	if(res != MT6701_OK){
		mt6701_print("mt6701: Cannot init: %d\n", res);
		return res + 200;
	}

	res = mt6701_mode_set(handle, MT6701_MODE_ABZ);
	if(res != MT6701_OK){
		mt6701_print("mt6701: Cannot set mode: %d\n", res);
		return res + 300;
	}

	res = mt6701_abz_pulse_per_round_set(handle, 16);
	if(res != MT6701_OK){
		mt6701_print("mt6701: Cannot set rounds per rotation: %d\n", res);
		return res + 400;
	}

	return MT6701_OK;
}

uint8_t mt6701_simple_read_angle( mt6701_handle_t *handle, float *angle ){
	uint8_t res;

	res = mt6701_read(handle, &angle, NULL, NULL, NULL);

	if(res != MT6701_OK){
		mt6701_print("mt6701: Read fault: %d\n", res);
		return res;
	}
	
	return MT6701_OK;
}

uint8_t mt6701_simple_ssi_init( mt6701_handle_t *handle ){
	uint8_t res = 0;

	if(handle == NULL){
		return MT6701_ERR_HANDLER_NULL;
	}

	handle->delay = mt6701_interface_delay;
	handle->ssi_read = mt6701_interface_ssi_read;

	if(mt6701_print == NULL){
		return MT6701_ERR_GENERAL;
	}

	res = mt6701_interface_set(handle, MT6701_INTERFACE_SSI);
	if(res != MT6701_OK){
		mt6701_print("mt6701: Cannot set interface: %d\n", res);
		return res;
	}

	res = mt6701_init(handle);
	if(res != MT6701_OK){
		mt6701_print("mt6701: Cannot init: %d\n", res);
		return res;
	}

	return MT6701_OK;
}
