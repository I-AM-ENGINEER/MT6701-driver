# Driver for MT6701

The MT6701 is an easy to program magnetic rotary position sensor with a high-resolution 12-bit analog, PWM, UVW, ABZ. With SPI and I2C output is 14 bit. They should provide magnetic button functionality, but datasheet is messy and i cant get this mode work.

This library provide simple API for configure module with I2C and flash EEPROM. Also lib provide interface for read angle and magnetic pole status (too strong/too low/nornal) throught SPI and I2C (with I2C only angle read possible)

### Project tree:
```
Root
│
├───example - example for init and read angle from encoder (I2C or SPI)
│
├───interface - interface template, you need impement I2C or SSI interface read/write
│
└───mt6701 - main driver folder, should be included
```

### Install

- add "mt6701" folder to include, add mt6701.c file in this folder to build
- copy interface header and source template to you src folder
- write implementation for delay, SSI or I2C in interface
- copy example init and read function for selected interface in your code
- call example init functon after initializing selected interface in yout code
- now you can use example read function for read angle in degrees [0.f...360.f) or write your own

### Examples

Read:
```c
uint8_t res;
mt6701_handle_t encoder;

res = mt6701_simple_ssi_init(&encoder);
if (res != 0){
    return 1;
}

while(1){
    float angle;
    res = mt6701_simple_read_angle(&encoder, &angle);
    if (res != 0){
        return 1;
    }
    printf("%f", angle);
}
```

If connection interface is I2C, these configurations functions can be used after initialization:
```c
uint8_t mt6701_nanbnz_enable( mt6701_handle_t *handle, bool nanbnz_enable ); // Only in QFN package
uint8_t mt6701_abz_pulse_per_round_set( mt6701_handle_t *handle, uint16_t pulses );
uint8_t mt6701_uvw_pole_pair_set( mt6701_handle_t *handle, uint8_t pole_pairs );
uint8_t mt6701_mode_set( mt6701_handle_t *handle, mt6701_mode_t mode ); // MT6701_MODE_UVW or MT6701_MODE_ABZ
uint8_t mt6701_zero_set_raw( mt6701_handle_t *handle, uint16_t zero_angle );
uint8_t mt6701_zero_set( mt6701_handle_t *handle, float zero_angle );
uint8_t mt6701_hyst_set( mt6701_handle_t *handle, mt6701_hyst_t hysteresis ); // MT6701_HYST_x
uint8_t mt6701_a_start_stop_set_raw( mt6701_handle_t *handle, uint16_t start, uint16_t stop );
uint8_t mt6701_a_start_stop_set( mt6701_handle_t *handle, float start, float stop );
uint8_t mt6701_direction_set( mt6701_handle_t *handle, mt6701_direction_t direction ); // MT6701_DIRECTION_CW or MT6701_DIRECTION_CCW
uint8_t mt6701_pulse_width_set( mt6701_handle_t *handle, mt6701_pulse_width_t pulse_width ); // MT6701_PULSE_WIDTH_xLSB
uint8_t mt6701_pwm_freq_set( mt6701_handle_t *handle, mt6701_pwm_freq_t pwm_freq ); // pwm_freq MT6701_PWM_FREQ_994_4 or MT6701_PWM_FREQ_497_2
uint8_t mt6701_pwm_polarity_set( mt6701_handle_t *handle, mt6701_pwm_pol_t pwm_polarity ); // MT6701_PWM_POL_HIGH or MT6701_PWM_POL_LOW
uint8_t mt6701_out_mode_set( mt6701_handle_t *handle, mt6701_out_mode_t out_mode ); // MT6701_OUT_MODE_ANALOG or MT6701_OUT_MODE_PWM
uint8_t mt6701_programm_eeprom( mt6701_handle_t *handle );
```

Configuration example:
```c
uint8_t res;
mt6701_handle_t encoder;

res = mt6701_simple_i2c_init(&encoder);
if (res != 0){
    return 1;
}

// You could check for result of every function, for simplification i didnt do this

mt6701_direction_set(&encoder, MT6701_DIRECTION_CCW);
mt6701_out_mode_set(&encoder, MT6701_OUT_MODE_PWM);
mt6701_pwm_polarity_set(&encoder, MT6701_PWM_POL_HIGH);
mt6701_pwm_freq_set(&encoder, MT6701_PWM_FREQ_994_4);

mt6701_programm_eeprom(&encoder);
```
