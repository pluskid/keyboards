#pragma once

//#define USE_MATRIX_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

// Enable sync of LED state to the slave side,
// so that display of caps-lock on slave side works properly.
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_OLED_ENABLE

#define USE_SERIAL_PD2

#define OLED_FONT_H "keyboards/crkbd/keymaps/crkbd-kid/glcdfont.c"

#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 130
