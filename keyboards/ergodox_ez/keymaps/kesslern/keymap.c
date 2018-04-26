#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_dvorak.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

#define SH_DV_U SFT_T(DV_U)
#define SH_DV_H SFT_T(DV_H)
#define SYM_I LT(SYMB, DV_I)
#define SYM_D LT(SYMB, DV_D)


enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  `/~   |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   ~    |  '/" |  ,/< |  ./> |   P  |   Y  |  \   |           |   /  |   F  |   G  |   C  |   R  |   L  |  //?   |
 * |--------+------+------+------+------+------|  |   |           |   ?  |------+------+------+------+------+--------|
 * |  TAB   |   A  |   O  |   E  |Shft/U|Symb/I|------|           |------|Symb/D|Shft/H|   T  |   N  |   S  |  -/_   |
 * |--------+------+------+------+------+------|      |           |   =  |------+------+------+------+------+--------|
 * | LShift |  ;/: |   Q  |   J  |   K  |   X  |      |           |   +  |   B  |   M  |   W  |   V  |   Z  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  L1  |      |      |      |      |                                       |      |      |      |      |  L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Home | End  |       | Left | Right|
 *                                 ,------|------|------|       |------+-------+-------.
 *                                 | Ctl/ | Alt  | PgUp |       | Up   |  Alt  | Ctrl  |
 *                                 | Back |  /   |------|       |------|   /   |   /   |
 *                                 | Space|Delete|G/PgDn|       |GUI/Dn| Enter | Space |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_GRV,   DV_1,    DV_2,    DV_3,   DV_4,    DV_5,  KC_ESC,
        KC_TILD,  DV_QUOT, DV_COMM, DV_DOT, DV_P,    DV_Y,  DV_BSLS,
        KC_TAB,   DV_A,    DV_O,    DV_E,   SH_DV_U, SYM_I,
        KC_LSFT,  DV_SCLN, DV_Q,    DV_J,   DV_K,    DV_X,  KC_NO,
        MO(SYMB), KC_NO,   KC_NO,   KC_NO,  KC_NO,
                                              KC_HOME,  KC_END,
                                                        KC_PGUP,
                         CTL_T(KC_BSPC), ALT_T(KC_DEL), GUI_T(KC_PGDN),
        // right hand
             KC_NO,   DV_6,    DV_7,  DV_8,  DV_9,  DV_0,  KC_NO,
             KC_SLSH, DV_F,    DV_G,  DV_C,  DV_R,  DV_L,  DV_SLSH,
             SYM_D,   SH_DV_H, DV_T,  DV_N,  DV_S,  DV_MINS,
             DV_EQL,  DV_B,    DV_M,  DV_W,  DV_V,  DV_Z,  KC_RSFT,
                            KC_NO, KC_NO, KC_NO, KC_NO, MO(SYMB),
             KC_LEFT, KC_RGHT,
             KC_UP,
             GUI_T(KC_DOWN), ALT_T(KC_ENT), CTL_T(KC_SPC)
    ),
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  F1  |  F2  |  F3  |  F4  |  F5  | RESET|           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |      |      |   *  |   #  |   |  |      |           |      |   ?  |   (  |   )  |      |      |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |   @  |   %  |   ~  |------|           |------|   +  |   {  |   }  |      |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |   $  |   ^  |   `  |      |           |      |   =  |   [  |   ]  |      |      |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       KC_ESC,  KC_F1, KC_F2, KC_F3,   KC_F4,   KC_F5,   RESET,
       KC_NO,   KC_NO, KC_NO, KC_ASTR, KC_HASH, KC_PIPE, KC_NO,
       KC_NO,   KC_NO, KC_NO, KC_AT,   KC_PERC, KC_TRNS,
       KC_TRNS, KC_NO, KC_NO, KC_DLR,  KC_CIRC, KC_GRV,  KC_NO,
       KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_TRNS,
                                                KC_TRNS, KC_TRNS,
                                                         KC_TRNS,
                           CTL_T(KC_SPC), ALT_T(KC_ENT), KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9, KC_F10, KC_F11,
       KC_TRNS, DV_QUES, KC_LPRN, KC_RPRN, KC_NO, KC_NO,  KC_F12,
                KC_TRNS, DV_LCBR, DV_RCBR, KC_NO, KC_NO,  KC_NO,
       KC_TRNS, KC_EQL,  DV_LBRC, DV_RBRC, KC_NO, KC_NO,  KC_TRNS,
                         KC_NO,   KC_NO,   KC_NO, KC_NO,  KC_TRNS,
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
