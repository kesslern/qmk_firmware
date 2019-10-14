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

#define NAV_E LT(NAV, DV_E)

// Navigation layer / arrow keys
#define NAVLEFT LT(NAV, KC_LEFT)
#define NAVRGHT LT(NAV, KC_RGHT)

// Ctrl+Shift+C and Ctrl+Shift+V
#define SH_CT_C LCTL(LSFT(DV_C))
#define SH_CT_V LCTL(LSFT(DV_V))

// Alt + Win combination
#define GUI_ALT(x) GUI_T(ALT_T((x)))

#define WN_UP GUI_T(KC_UP)
#define CT_BSPC CTL_T(KC_BSPC)
#define AL_DEL  ALT_T(KC_DEL)
#define AL_ENT  ALT_T(KC_ENT)
#define CT_SPC  CTL_T(KC_SPC)
#define WN_DOWN GUI_T(KC_DOWN)


// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    KC_MAKE = SAFE_RANGE,
    KC_FLSH                  
};

/*
        Template for a layer of the keymap. Copy/paste and customize.

        [LAYER] = LAYOUT(
              // XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
                 KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                 KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                 KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   
                 KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS,
                 KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,         KC_TRNS, KC_TRNS,

                          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                 KC_TRNS, KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                 KC_TRNS, KC_TRNS, KC_NO,         KC_NO,      KC_NO,   KC_NO,   KC_NO
        ),

*/


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [BASE] = LAYOUT(
              // XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
                 KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_ESC,
                 KC_TILD, DV_QUOT, DV_COMM, DV_DOT,  DV_P,    DV_Y,    DV_BSLS,
                 KC_TAB,  DV_A,    DV_O,    NAV_E,   SH_DV_U, SYM_I,
                 KC_LSFT, DV_SCLN, DV_Q,    DV_J,    DV_K,    DV_X,    XXXXXXX, KC_H,
                 MO(SYMB),KC_MPLY, KC_VOLD, KC_VOLU,    WN_UP,         CT_BSPC, AL_DEL,

                          KC_PSCR, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX,
                          DV_EQL,  DV_F,    DV_G,    DV_C,    DV_R,    DV_L,    DV_SLSH,
                                   SYM_D,   SH_DV_H, DV_T,    DV_N,    DV_S,    DV_MINS,
                 KC_A,    DV_E,    DV_B,    DV_M,    DV_W,    DV_V,    DV_Z,    KC_RSFT,
                 AL_ENT,  CT_SPC,     WN_DOWN,       TO(NAV), XXXXXXX, XXXXXXX, MO(SYMB)
        ),
        [SYMB] = LAYOUT(
              // XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
                 KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_INS,
                 KC_NO,   KC_NO,   KC_EXLM, KC_AT,   KC_HASH, KC_NO,   KC_SLSH,
                 KC_NO,   KC_NO,   KC_DLR,  KC_PERC, KC_PIPE, KC_TRNS,
                 KC_TRNS, KC_NO,   KC_CIRC, KC_AMPR, KC_ASTR, KC_NO,   KC_NO,   KC_NO,
                 KC_TRNS, KC_NO,   KC_NO,   KC_NO,      KC_LEFT,       KC_SPC,  KC_BSPC,

                          KC_NO,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
                          KC_NO,   KC_PIPE, KC_LPRN, KC_RPRN, KC_NO,   KC_NO,   KC_F12,
                                   KC_TRNS, DV_LCBR, DV_RCBR, KC_NO,   KC_NO,   KC_NO,
                 RESET,   KC_NO,   KC_PLUS, DV_LBRC, DV_RBRC, KC_NO,   KC_NO,   KC_TRNS,
                 KC_NO,   KC_NO,      KC_RGHT,       KC_NO,   KC_NO,   KC_NO,   KC_TRNS
        ),
        [NAV] = LAYOUT(
              // XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
                 KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                 KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                 KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_NO,   KC_NO,   
                 KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                 KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,         KC_NO,   KC_NO,

                          RESET,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                          KC_NO,   KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_NO,   KC_NO,
                                   KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_NO,
                 KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                 KC_NO,   KC_NO,      KC_NO,         TO(BASE),KC_NO,   KC_MAKE, KC_FLSH
        ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
   switch (keycode) {
    case KC_MAKE:
      if (record->event.pressed) {
        SEND_STRING("make kredox:kesslern"SS_TAP(X_ENTER));
      }
      break;
   case KC_FLSH:
      if (record->event.pressed) {
        SEND_STRING("sleep 2s && sudo teensy-loader-cli -mmcu=atmega32u4 kredox_kesslern.hex"SS_TAP(X_ENTER));
        reset_keyboard();
        
      }
      break;
   }
  
  return true;
}

void matrix_init_user(void) {}

void matrix_scan_user(void) {}

void led_set_user(uint8_t usb_led) {}

void keyboard_post_init_user(void) {}
