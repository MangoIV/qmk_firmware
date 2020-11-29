#include "draculad.h"

extern uint8_t is_master;

enum layer_number {
  _BASE = 0,
  _NUM,
  _SYMB,
  _ADJ
};


char wpm_as_str[8];
extern uint8_t is_master;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] =  LAYOUT( \
    KC_Q,         KC_W, KC_E,    KC_R,    KC_T,                             KC_Y, KC_U, KC_I,    KC_O,   KC_P, \
    LCTL_T(KC_A), KC_S, KC_D,    KC_F,    KC_G,                             KC_H, KC_J, KC_K ,   KC_L ,  KC_SCLN, \
    LSFT_T(KC_Z), KC_X, KC_C,    KC_V,    KC_B,                             KC_N, KC_M, KC_COMM, KC_DOT, RSFT_T(KC_SLSH), \
                        KC_MUTE, KC_LALT, KC_BSPC, KC_SPC, LT(_NUM,KC_DEL), LT(_SYMB, KC_ENT), KC_CAPS, TG(_ADJ) \
                    ), 
  [_NUM] = LAYOUT( \
    KC_1,         KC_2, KC_3,    KC_4,    KC_5,                             KC_6, KC_7, KC_8,    KC_9,   KC_0, \
    KC_LCTL, XXXXXXX, KC_VOLD,    KC_VOLU,    XXXXXXX,                      KC_LEFT, KC_DOWN, KC_UP ,   KC_RIGHT ,  KC_QUOT, \
    KC_LSFT, XXXXXXX, XXXXXXX,    KC_MUTE,    RESET,                        KC_HOME, KC_END, KC_PGUP, KC_PGDN, KC_RSFT, \
                        XXXXXXX, KC_LALT, XXXXXXX, XXXXXXX, _______, KC_ENT, KC_NO, KC_NO \
    ), 
  [_SYMB] = LAYOUT( \
    KC_ESC,         KC_F1, KC_F2,    KC_F3,    KC_F4,                             KC_6, KC_7, KC_8,    KC_9,   KC_0, \
    XXXXXXX, KC_F5, KC_F6,    KC_F7,    KC_F8,                      KC_LBRC, KC_RBRC, XXXXXXX ,   KC_GRV ,  KC_BSLS, \
    KC_LSFT, KC_F9, KC_F10,    KC_F11,    KC_F12,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT, \
                        XXXXXXX, KC_LALT, XXXXXXX, XXXXXXX, XXXXXXX, _______, KC_NO, KC_NO \
    ),
    [_ADJ] = LAYOUT( \
    RESET,         XXXXXXX, XXXXXXX,    XXXXXXX,    XXXXXXX,                XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,   XXXXXXX, \
    EEP_RST, XXXXXXX, XXXXXXX,    XXXXXXX,    XXXXXXX,                        RGB_MOD, RGB_HUI, RGB_SAI ,   RGB_VAI ,  XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,    XXXXXXX,                        RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, _______, \
                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
    ) \
};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}

#ifdef OLED_DRIVER_ENABLE

bool is_keyboard_left(void);

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
  oled_write_P(PSTR("This is\n\nDracul\nLad\n\nv1.0\n\n"), false);
  sprintf(wpm_as_str, "wpm:%03d", get_current_wpm());
  oled_write(wpm_as_str,false);
  led_t led_state = host_keyboard_led_state();
  oled_write_P(PSTR("\n\ncaps: "), false);
  oled_write_P(led_state.caps_lock ? PSTR("on ") : PSTR("off"), false);
  switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("Base   "), false);
            break;
        case _NUM:
            oled_write_P(PSTR("Numbers"), false);
            break;
        case _SYMB:
            oled_write_P(PSTR("Symbols"), false);
            break;
        case _ADJ:
            oled_write_P(PSTR("Adjust "), false);
            break;
        default:
            oled_write_P(PSTR("Unkn "), false);
            break;
    }
}

void oled_task_user(void) {
      if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_qmk_logo();
    }
}

#endif

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 2) {
      if(clockwise) {
        rgblight_increase_hue_noeeprom();
      }
      else{
        rgblight_decrease_hue_noeeprom();
      }
    }
    else if (index == 3  ) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }

}
#endif