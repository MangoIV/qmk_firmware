#pragma once

#include "config_common.h"

#define VENDOR_ID 0x4653
#define PRODUCT_ID 0x0001
#define DEVICE_VER 0x0001
#define MANUFACTURER mangoiv
#define PRODUCT space_ginny
#define DESCRIPTION an ASETNIOP device


#define MATRIX_ROWS 2
#define MATRIX_COLS 5

#define MATRIX_ROW_PINS {B5}
#define MATRIX_COL_PINS {D4, C6, D7, E6, B4}
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 5


#define USE_SERIAL
#define SOFT_SERIAL_PIN D2

#ifdef OLED_DRIVER_ENABLE
  #define OLED_DISPLAY_128X64
  #define OLED_TIMEOUT 30000
#endif


#define EE_HANDS