#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_dvorak.h"
#include <sendstring_dvorak.h>

#define BASE 0
#define SYMB 1
#define NAV 2

// Shift keys on the home row
#define SH_DV_U SFT_T(DV_U)
#define SH_DV_H SFT_T(DV_H)

// Symbol layer on the home row
#define SYM_I LT(SYMB, DV_I)
#define SYM_D LT(SYMB, DV_D)

// Navigation layer / arrow keys
#define NAVLEFT LT(NAV, KC_LEFT)
#define NAVRGHT LT(NAV, KC_RGHT)

#define NAV_E LT(NAV, DV_E)

// Ctrl+Shift+C and Ctrl+Shift+V
#define SH_CT_C LCTL(LSFT(DV_C))
#define SH_CT_V LCTL(LSFT(DV_V))

// Alt + Win combination
#define GUI_ALT(x) GUI_T(ALT_T((x)))

#define WN_UP GUI_T(KC_UP)
#define WN_DOWN GUI_T(KC_DOWN)

#define MACRO_1 DYN_MACRO_PLAY1
#define MACRO_2 DYN_MACRO_PLAY2

#define RCMAC_1 DYN_REC_START1
#define RCMAC_2 DYN_REC_START2

enum custom_keycodes {
  KC_MAKE = SAFE_RANGE, // can always be here
  KC_FLSH,
  DYNAMIC_MACRO_RANGE,
};

#include "dynamic_macro.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_GRV,   DV_1,    DV_2,    DV_3,    DV_4,    DV_5,  KC_ESC,
        KC_TILD,  DV_QUOT, DV_COMM, DV_DOT,  DV_P,    DV_Y,  DV_BSLS,
        KC_TAB,   DV_A,    DV_O,    NAV_E,   SH_DV_U, SYM_I,
        KC_LSFT,  DV_SCLN, DV_Q,    DV_J,    DV_K,    DV_X,  KC_PIPE,
        MO(SYMB), KC_MPLY, KC_VOLD, KC_VOLU, WN_UP,
                                                   MACRO_1,  MACRO_2,
                                                    GUI_ALT(KC_PGUP),
                       CTL_T(KC_BSPC), ALT_T(KC_DEL), GUI_T(KC_PGDN),
        // right hand
        KC_NO,   DV_6,    DV_7,    DV_8,  DV_9,    DV_0,    KC_NO,
        DV_SLSH, DV_F,    DV_G,    DV_C,  DV_R,    DV_L,    DV_SLSH,
                 SYM_D,   SH_DV_H, DV_T,  DV_N,    DV_S,    DV_MINS,
        DV_EQL,  DV_B,    DV_M,    DV_W,  DV_V,    DV_Z,    KC_RSFT,
                          WN_DOWN, KC_UP, SH_CT_C, SH_CT_V, MO(SYMB),
        KC_LEFT, KC_RGHT,
        GUI_ALT(KC_UP),
        GUI_T(KC_DOWN), ALT_T(KC_ENT), CTL_T(KC_SPC)
    ),
[SYMB] = LAYOUT_ergodox(
         // left hand
         KC_ESC,  KC_F1, KC_F2,   KC_F3,   KC_F4,   KC_F5,   RESET,
         KC_NO,   KC_NO, KC_NO,   KC_EXLM, KC_AT,   KC_HASH, KC_NO,
         KC_TRNS, KC_NO, KC_NO,   KC_DLR,  KC_PERC, KC_TRNS,
         KC_TRNS, KC_NO, KC_NO,   KC_CIRC, KC_AMPR, KC_ASTR, KC_NO,
         KC_TRNS, KC_NO, KC_NO,   KC_NO,   KC_NO,
                                                    RCMAC_1, RCMAC_2,
                                                             KC_TRNS,
                               CTL_T(KC_SPC), ALT_T(KC_ENT), KC_TRNS,
         // right hand
         KC_INS, KC_F6,   KC_F7,   KC_F8,   KC_F9, KC_F10, KC_F11,
         KC_NO,  DV_QUES, KC_LPRN, KC_RPRN, KC_NO, KC_NO,  KC_F12,
                 KC_TRNS, DV_LCBR, DV_RCBR, KC_NO, KC_NO,  KC_NO,
         KC_NO,  DV_PLUS, DV_LBRC, DV_RBRC, KC_NO, KC_NO,  KC_TRNS,
                          KC_NO,   KC_NO,   KC_NO, KC_NO,  KC_TRNS,
         KC_TRNS, KC_TRNS,
         KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS
    ),
[NAV] = LAYOUT_ergodox(
         // left hand
         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                        KC_TRNS, KC_TRNS,
                                                 KC_TRNS,
                               KC_TRNS, KC_TRNS, KC_TRNS,
         // right hand
         KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
         KC_NO, KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_NO, KC_NO,
                KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO,
         KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
                KC_NO,   KC_NO,   KC_NO,   KC_MAKE, KC_FLSH,
         KC_TRNS, KC_TRNS,
         KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS
    ),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_record_dynamic_macro(keycode, record)) {
    return false;
  }
  
   switch (keycode) {
    case KC_MAKE:
      if (record->event.pressed) {
        SEND_STRING("make ergodox_ez:kesslern"SS_TAP(X_ENTER));
      }
      break;
   case KC_FLSH:
      if (record->event.pressed) {
        SEND_STRING("sleep 2s && sudo teensy-loader-cli -mmcu=atmega32u4 ergodox_ez_kesslern.hex"SS_TAP(X_ENTER));
        reset_keyboard();
      }
      break;
   }
  
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #else
        #ifdef RGBLIGHT_ENABLE
          rgblight_init();
        #endif
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      default:
        break;
    }

  return state;
};
