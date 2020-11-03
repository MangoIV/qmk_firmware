#include QMK_KEYBOARD_H
#include "keymap_steno.h"
#include "split_util.h"
#include <stdio.h>


char wpm_as_str[8];
extern uint8_t is_master;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( STN_N1, STN_N2, STN_N3, STN_N4, KC_F15, KC_F16, STN_N5, STN_N6, STN_N7, STN_N8)
};

uint16_t lastkeycode = 0;
uint8_t rightchord = 0;
bool process_steno_user(uint16_t keycode, keyrecord_t *record) {
    if (lastkeycode == 0) {
        switch (keycode) {
            case STN_N1:
            case STN_N2:
            case STN_N3:
            case STN_N4:
                rightchord = 0;
                break;
            default:
                rightchord = 1;
                break;
        }
    }
    lastkeycode = keycode;
    return true;
}

bool send_steno_chord_user(steno_mode_t mode, uint8_t chord[6]) {
    if (rightchord) {
        chord[2] = rightchord;
    }
    lastkeycode = 0;
    rightchord = 0;
    return true;
}

void matrix_init_user() {
  steno_set_mode(STENO_MODE_GEMINI); // or STENO_MODE_BOLT
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {

  if (is_keyboard_master()) {
    if(is_keyboard_left()){
      return OLED_ROTATION_270;
      }
      else {
        return OLED_ROTATION_90;
      }
    } else {
	    return OLED_ROTATION_0;
    }
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

static void render_status(void) {
  oled_write_P(PSTR("This is \n\nspace_ \nginny \n\nv1.0\n\n"), false);
  sprintf(wpm_as_str, "wpm:%03d", get_current_wpm());
  oled_write(wpm_as_str,false);
  led_t led_state = host_keyboard_led_state();
  oled_write_P(PSTR("\n\ncaps: "), false);
  oled_write_P(led_state.caps_lock ? PSTR("on ") : PSTR("off"), false);
}

void oled_task_user(void) {
      if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_qmk_logo();
    }
}

#endif