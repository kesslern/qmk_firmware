/* Copyright 2017 Baris Tosun
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public Lic212 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "katana60.h"
#include "keymap_dvorak.h"

#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define BASE 0 // Default
#define SYMB 1 // Symbols

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = KEYMAP( /* Base */
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MPLY, DF(1),   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  DV_LBRC, DV_RBRC,
  KC_TAB,  DV_QUOT, DV_COMM, DV_DOT,  DV_P,    DV_Y,    KC_LCTL,          KC_RCTL, DV_F,    DV_G,    DV_C,    DV_R,  DV_L,    DV_SLSH,
  KC_LCTL, DV_A,    DV_O,    DV_E,    DV_U,    DV_I,    DV_BSLS,          DV_EQL,  DV_D,    DV_H,    DV_T,    DV_N,  DV_S,    DV_MINS,
  KC_LSFT, DV_SCLN, DV_Q,    DV_J,    DV_K,    DV_X,    KC_HOME, KC_LALT, KC_END,  DV_B,    DV_M,    DV_W,    DV_V,  DV_Z,    KC_RSFT,
  MO(1),   XXXXXXX, KC_LGUI, KC_LALT,          CTL_T(KC_BSPC), KC_ENT,  KC_SPC,       ALT_T(KC_LEFT), KC_DOWN, KC_UP, KC_RGHT, MO(1)
    ),
[SYMB] = KEYMAP(
  KC_ESC,  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,          _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_VOLD,          KC_VOLU, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, RESET,
  _______, DV_PLUS, DV_MINS, DV_EQL,  DV_LCBR, DV_RCBR, KC_MPRV, KC_MPLY, KC_MNXT, DV_LBRC, DV_RBRC, DV_SCLN, DV_COLN, KC_BSLS, _______,
  _______, _______, _______, _______,                    KC_DEL,  _______, KC_ENT,           _______, _______, _______, _______, _______
    )
};


const uint16_t PROGMEM fn_actions[] = {
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};


void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}
