/* Copyright 2019 kesslern
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
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
#include QMK_KEYBOARD_H
#include "keymap_dvorak.h"
#include <sendstring_dvorak.h>

// Defines names for use in layer keycodes and the keymap
enum layer_names {
                  _BASE,
                  _NUMFN,
                  _BETA,
                  _NAV
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL
};

// Shift keys on the home row
#define SH_DV_U SFT_T(DV_U)
#define SH_DV_H SFT_T(DV_H)
#define SH_DV_A SFT_T(DV_A)
#define SH_DV_S SFT_T(DV_S)
#define SH_F4   SFT_T(KC_F4)
#define SH_F7   SFT_T(KC_F7)
#define SH_LCBR SFT_T(DV_LCBR)

#define CTLBSPC CTL_T(KC_BSPC)
#define ALT_DEL ALT_T(KC_DEL)
#define WINSLSH WIN_T(DV_SLSH)

#define TABBETA LT(_BETA, KC_TAB)
#define ENTRF09 LT(_NUMFN, KC_ENT)
#define BETA_I  LT(_BETA, DV_I)
#define BETA_D  LT(_BETA, DV_D)
#define SH_SPC  SFT_T(KC_SPC)

#define NAV_E   LT(_NAV, DV_E)

#define F09_K  LT(_NUMFN, DV_K)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
                     DV_QUOT, DV_COMM, DV_DOT,  DV_P,    DV_Y,    DV_F,    DV_G,    DV_C,    DV_R,    DV_L,    \
                     SH_DV_A, DV_O,    NAV_E,   SH_DV_U, BETA_I,  BETA_D,  SH_DV_H, DV_T,    DV_N,    SH_DV_S, \
                     DV_SCLN, DV_Q,    DV_J,    F09_K,   DV_X,    DV_B,    DV_M,    DV_W,    DV_V,    DV_Z,    \
                                       CTLBSPC, ALT_DEL, WINSLSH, TABBETA, ENTRF09, SH_SPC                     \
                     ),
    [_NUMFN] = LAYOUT(
                     DV_1,    DV_2,    DV_3,    DV_4,    DV_5,    DV_6,    DV_7,    DV_8,    DV_9,    DV_0,    \
                     KC_F1,   KC_F2,   KC_F3,   SH_F4,   KC_F5,   KC_F6,   SH_F7,   KC_F8,   KC_F9,   KC_F10,  \
                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F11,  KC_F12,  DV_W,    DV_V,    DV_Z,    \
                                       _______, _______, _______, _______, _______, _______                    \
                     ),
    [_BETA] = LAYOUT(
                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DV_PLUS, KC_LPRN, KC_RPRN, KC_TILD, KC_PIPE, \
                     _______, XXXXXXX, XXXXXXX, _______, _______, DV_EQL,  DV_LCBR, DV_RCBR, DV_MINS, DV_UNDS, \
                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ESC,  KC_BSLS, DV_LBRC, DV_RBRC, DV_SLSH, DV_EQL,  \
                                       _______, _______, _______, _______, _______, _______                    \
                     ),
    [_NAV] = LAYOUT(
                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_HOME, KC_UP,   KC_END,  XXXXXXX, \
                     _______, XXXXXXX, XXXXXXX, _______, _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, \
                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                                       _______, _______, _______, _______, _______, _______                    \
                     )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QMKBEST:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("QMK is the best thing ever!");
            } else {
                // when keycode QMKBEST is released
            }
            break;
        case QMKURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
            } else {
                // when keycode QMKURL is released
            }
            break;
    }
    return true;
}

/*
void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool led_update_user(led_t led_state) {
    return true;
}
*/
