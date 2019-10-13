/* Copyright 2019 Nathan Kessler
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

// Ctrl+Shift+C and Ctrl+Shift+V
#define SH_CT_C LCTL(LSFT(DV_C))
#define SH_CT_V LCTL(LSFT(DV_V))

// Alt + Win combination
#define GUI_ALT(x) GUI_T(ALT_T((x)))

#define WIN_LEFT GUI_T(KC_LEFT)
#define CTL_BSPC CTL_T(KC_BSPC)
#define ALT_DEL  ALT_T(KC_DEL)
#define ALT_ENT  ALT_T(KC_ENT)
#define CTL_SPC  CTL_T(KC_SPC)
#define WIN_RGHT GUI_T(KC_RGHT)


// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes { NONE };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [BASE] = LAYOUT(
                 KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,  KC_ESC,                     DV_EQL,  KC_6,  KC_7,    KC_8,  KC_9,    KC_0,  KC_NO,
                 KC_TILD, DV_QUOT, DV_COMM, DV_DOT,  DV_P,    DV_Y,  DV_BSLS,                    DV_SLSH, DV_F,  DV_G,    DV_C,  DV_R,    DV_L,  DV_SLSH,
                 KC_TAB,  DV_A,    DV_O,    DV_E,    SH_DV_U, SYM_I,                                      SYM_D, SH_DV_H, DV_T,  DV_N,    DV_S,  DV_MINS,
                 KC_LSFT, DV_SCLN, DV_Q,    DV_J,    DV_K,    DV_X,  KC_NO,    KC_H,    KC_A,    DV_E,    DV_B,  DV_M,    DV_W,  DV_V,    DV_Z,  KC_RSFT,
                 MO(SYMB),KC_MPLY, KC_VOLD, KC_VOLU,    WIN_LEFT,    CTL_BSPC, ALT_DEL, ALT_ENT, CTL_SPC,    WIN_RGHT,    KC_UP, KC_DOWN, KC_NO, MO(SYMB)
                 ),
        [SYMB] = LAYOUT(
                 KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G,             RESET, KC_G,    KC_C,    KC_1, KC_E, KC_F, KC_G,
                 KC_A, KC_B, KC_C, KC_D, KC_H, KC_J, KC_K,             KC_D,  KC_NO,   KC_LPRN, KC_RPRN, KC_2, KC_E, KC_F,
                 KC_A, KC_B, KC_C, KC_A, KC_B, KC_C,                          KC_TRNS, DV_LCBR, DV_RCBR, KC_E, KC_F, KC_G,
                 KC_A, KC_B, KC_C, KC_L, KC_M, KC_A, KC_O, KC_H, KC_A, KC_E,  KC_J,    DV_LBRC, DV_RBRC, KC_E, KC_F, KC_G,
                 KC_A, KC_B, KC_C, KC_D, KC_E,       KC_G, KC_H, KC_B, KC_F,   KC_C,  KC_5, KC_E, KC_F, KC_G
                 ),
        [NAV] = LAYOUT(
                 KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G,             KC_C, KC_G, KC_C, KC_1, KC_E, KC_F, KC_G,
                 KC_A, KC_B, KC_C, KC_D, KC_H, KC_J, KC_K,             KC_D, KC_H, KC_C, KC_2, KC_E, KC_F, KC_G,
                 KC_A, KC_B, KC_C, KC_A, KC_B, KC_C,                         KC_I, KC_C, KC_3, KC_E, KC_F, KC_G,
                 KC_A, KC_B, KC_C, KC_L, KC_M, KC_A, KC_O, KC_H, KC_A, KC_E, KC_J, KC_C, KC_4, KC_E, KC_F, KC_G,
                 KC_A, KC_B, KC_C, KC_D, KC_E,       KC_G, KC_H, KC_B, KC_F,       KC_C, KC_5, KC_E, KC_F, KC_G
                 ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}

void matrix_init_user(void) {}

void matrix_scan_user(void) {}

void led_set_user(uint8_t usb_led) {}

void keyboard_post_init_user(void) {}
