// Copyright 2026 Nathan Kessler
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_dvorak.h"

enum layers {
    _BASE,
    _SYM,
    _NAV,
    _FN,
};

// Home row mods on the ring, middle and index fingers, order ring -> index:
// GUI, Alt, Ctrl. Shift now lives on the outer thumbs, so the weak pinky is
// left as a plain letter and the mods sit on stronger fingers. Tap = the
// letter, hold = the modifier; mirrored so a shortcut is held with the hand
// opposite the key it modifies.
#define HM_O    LGUI_T(DV_O)
#define HM_E    LALT_T(DV_E)
#define HM_U    LCTL_T(DV_U)
#define HM_H    RCTL_T(DV_H)
#define HM_T    RALT_T(DV_T)
#define HM_N    RGUI_T(DV_N)

// Thumbs (left -> right): Bspc Del Tab Esc Enter Space. Every key is
// dual-function (tap / hold), no bare keys. NAV and SYM each sit on an inner
// and a mid thumb, so NAV+SYM -> _FN (tri-layer) is a comfortable inner-thumb
// chord. Outer thumbs add a Shift to take load off the pinky home-row shift.
#define BSP_SFT LSFT_T(KC_BSPC)   // tap Bspc  / hold Shift
#define DEL_SYM LT(_SYM, KC_DEL)  // tap Del   / hold SYM
#define TAB_NAV LT(_NAV, KC_TAB)  // tap Tab   / hold NAV
#define ESC_SYM LT(_SYM, KC_ESC)  // tap Esc   / hold SYM
#define ENT_NAV LT(_NAV, KC_ENT)  // tap Enter / hold NAV
#define SPC_SFT RSFT_T(KC_SPC)    // tap Space / hold Shift

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Base: Dvorak alphas in Dvorak order. DV_ codes -> correct letters on a
    // host whose keyboard layout is set to Dvorak.
    [_BASE] = LAYOUT_split_3x5_3(
        DV_QUOT, DV_COMM, DV_DOT,  DV_P,    DV_Y,    DV_F,    DV_G,    DV_C,    DV_R,    DV_L,
        DV_A,    HM_O,    HM_E,    HM_U,    DV_I,    DV_D,    HM_H,    HM_T,    HM_N,    DV_S,
        DV_SCLN, DV_Q,    DV_J,    DV_K,    DV_X,    DV_B,    DV_M,    DV_W,    DV_V,    DV_Z,
                          BSP_SFT, DEL_SYM, TAB_NAV, ESC_SYM, ENT_NAV, SPC_SFT
    ),

    // Symbols + numbers. Held via either thumb (SYM); home row mods stay
    // usable underneath for e.g. Ctrl+number.
    [_SYM] = LAYOUT_split_3x5_3(
        DV_1,    DV_2,    DV_3,    DV_4,    DV_5,    DV_6,    DV_7,    DV_8,    DV_9,    DV_0,
        DV_EXLM, DV_AT,   DV_HASH, DV_DLR,  DV_PERC, DV_CIRC, DV_AMPR, DV_ASTR, DV_LPRN, DV_RPRN,
        DV_GRV,  DV_TILD, DV_BSLS, DV_PIPE, DV_MINS, DV_EQL,  DV_LBRC, DV_RBRC, DV_LCBR, DV_RCBR,
                          _______, _______, _______, _______, _______, _______
    ),

    // Navigation and media. Left home row carries plain mods so the right hand
    // can drive Shift/Ctrl + arrows for select / word-jump. Mods sit on the same
    // fingers as the base layer (ring/middle/index = GUI/Alt/Ctrl) with Shift on
    // the otherwise-free pinky. System/reset keys now live on _FN.
    [_NAV] = LAYOUT_split_3x5_3(
        _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_DEL,
        KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, KC_MUTE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_INS,
        KC_VOLD, KC_VOLU, _______, _______, _______, KC_TAB,  KC_ESC,  KC_CAPS, _______, KC_PSCR,
                          _______, _______, _______, _______, _______, _______
    ),

    // Function + system. Reached by holding NAV + SYM together (tri-layer).
    // F1-F10 mirror the digit positions on _SYM; F11/F12 drop to the bottom row
    // under F1/F2. The home row carries a full GACS mod set on both hands
    // (mirrored, matching the base layer) so any F-key can be modified from the
    // opposite hand, including multi-mod chords. Reset keys sit in the
    // bottom-right corner, behind the deliberate combo.
    [_FN] = LAYOUT_split_3x5_3(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, _______, _______, KC_RCTL, KC_RALT, KC_RGUI, KC_RSFT,
        KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, EE_CLR,  QK_BOOT,
                          _______, _______, _______, _______, _______, _______
    ),
};

// Thumb keys are always deliberate chords (shortcut mods or layer holds), never
// part of a fast letter roll, so exempt them from Chordal Hold's same-hand veto:
// any tap-hold chorded with a thumb falls back to the normal tap/hold rules
// (PERMISSIVE_HOLD / tapping term). This is what lets same-hand combos like
// left-hand Alt+Tab and same-hand SYM/NAV layer use resolve as holds.
static bool is_thumb_key(uint16_t keycode) {
    switch (keycode) {
        case BSP_SFT:
        case DEL_SYM:
        case TAB_NAV:
        case ESC_SYM:
        case ENT_NAV:
        case SPC_SFT:
            return true;
        default:
            return false;
    }
}

bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record,
                      uint16_t other_keycode, keyrecord_t* other_record) {
    if (is_thumb_key(tap_hold_keycode) || is_thumb_key(other_keycode)) {
        return true;
    }
    return get_chordal_hold_default(tap_hold_record, other_record);
}

// Activate _FN when both NAV and SYM are held.
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYM, _NAV, _FN);
}
