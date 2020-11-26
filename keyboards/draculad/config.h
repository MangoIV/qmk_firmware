#pragma once

#define VENDOR_ID 0x0000
#define PRODUCT_ID 0x0001
#define DEVICE_VER 0x0001
#define MANUFACTURER mangoiv
#define PRODUCT draculad
#define DESCRIPTION a < 40 - key input device

#define MATRIX_ROWS 4
#define MATRIX_COLS 5

#define MATRIX_ROW_PINS {D4, C6, D7, E6}
#define MATRIX_COL_PINS {F4, F5,F6, F7, B1}
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 5


#define USE_SERIAL
#define SOFT_SERIAL_PIN D2

#ifdef OLED_DRIVER_ENABLE
  #define OLED_DISPLAY_128X64
  #define OLED_TIMEOUT 30000
#endif


#define RGB_DI_PIN D3
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 20
#define RGBLED_SPLIT 10
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_SLEEP
#endif

#define ENCODERS_ PAD_A {B2 , B4}
#define ENCODERS_ PAD_A {B6 , B5}


#define EE_HANDS