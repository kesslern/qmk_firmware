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

// Home row mods across all four fingers. Ring adds GUI; middle is now a NAV
// layer-tap (not a mod) on both hands, giving a second route into NAV
// alongside the inner thumbs -- Alt moved off the home row entirely, down to
// the left mid thumb (see TAB_ALT below). The index finger's two columns
// (outer U/H and inner I/D) both add Shift; the pinky keeps its second Ctrl
// for easier Ctrl+key reach. Tap = the letter, hold = the modifier (or NAV,
// for middle); mirrored so a shortcut is held with the hand opposite the key
// it modifies.
#define HM_A    LCTL_T(DV_A)
#define HM_O    LGUI_T(DV_O)
#define HM_E    LT(_NAV, DV_E)
#define HM_U    LSFT_T(DV_U)
#define HM_I    LSFT_T(DV_I)
#define HM_D    RSFT_T(DV_D)
#define HM_H    RSFT_T(DV_H)
#define HM_T    LT(_NAV, DV_T)
#define HM_N    RGUI_T(DV_N)
#define HM_S    RCTL_T(DV_S)

// Thumbs (left -> right): Bspc Tab / Esc Enter Space. Every key is
// dual-function (tap / hold), no bare keys. SYM now lives only on the right
// mid thumb (ENT_SYM) -- the left mid thumb (TAB_ALT) holds Alt instead (see
// above), so reaching _FN (the SYM+NAV tri-layer) means chording ENT_SYM with
// any NAV source: either inner thumb, or the HM_E/HM_T home-row layer-taps.
// Outer thumbs add a Ctrl (swapped down from the outer index column, which
// now carries Shift instead).
//
// Delete lives on the Bspc position of the _SYM layer (DEL_CTL).
#define BSP_CTL LCTL_T(KC_BSPC)    // tap Bspc  / hold Ctrl
#define TAB_ALT LALT_T(KC_TAB)     // tap Tab   / hold Alt
#define SLS_NAV LT(_NAV, DV_SLSH)  // tap /     / hold NAV
#define ESC_NAV LT(_NAV, KC_ESC)   // tap Esc   / hold NAV
#define ENT_SYM LT(_SYM, KC_ENT)   // tap Enter / hold SYM
#define SPC_CTL RCTL_T(KC_SPC)     // tap Space / hold Ctrl

// _SYM left outer thumb: tap Delete (the old inner-thumb Del), hold Ctrl. The
// hold restores the left Ctrl that BSP_CTL provides on the base layer, so
// Ctrl stays available on both thumbs while SYM is active.
#define DEL_CTL LCTL_T(KC_DEL)

// _SYM home-row symbols. Symbols sit on the home row (moved up from the bottom
// row for easier reach), each keeping its finger's home-row hold from the base
// layer (GUI/Ctrl mods, inner-index Shift, pinky Ctrl, or NAV on the middle
// finger): tap = symbol, hold = that hold -- holding a middle-finger symbol
// key while already in SYM reaches _FN, the same as chording ENT_SYM with a
// NAV source. The bottom row has no mods, so those symbols are plain keys
// below.
//
// Mod-tap can only store an 8-bit *basic* keycode on its tap, so shifted symbols
// (~, ( ), | on the right, and { }) can't ride a mod-tap directly: their defines
// wrap the mod over an underlying basic key (its shifted counterpart, where one
// exists) and emit the real shifted symbol on tap in process_record_user. Basic
// symbols use plain mod-taps; plain (non-mod) keys can hold shifted keycodes
// directly.
#define SM_GRV  LCTL_T(DV_GRV)     // left pinky:  tap ` / hold LCTL
#define SM_TILD LGUI_T(DV_GRV)     // left home:   tap ~ (tap override) / hold LGUI
#define SM_LPRN LT(_NAV, DV_9)     // left home:   tap ( (tap override) / hold NAV
#define SM_RPRN LSFT_T(DV_0)       // left home:   tap ) (tap override) / hold LSFT
#define SM_MINS LSFT_T(DV_MINS)    // left home:   tap - / hold LSFT
#define SM_EQL  RSFT_T(DV_EQL)     // right home:  tap = / hold RSFT
#define SM_LCBR RSFT_T(DV_LBRC)    // right home:  tap { (tap override) / hold RSFT
#define SM_RCBR LT(_NAV, DV_RBRC)  // right home:  tap } (tap override) / hold NAV
#define SM_RPIP RGUI_T(DV_BSLS)    // right home:  tap | (tap override) / hold RGUI
#define SM_RMIN RCTL_T(DV_MINS)    // right pinky: tap - / hold RCTL

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Base: Dvorak alphas in Dvorak order. DV_ codes -> correct letters on a
    // host whose keyboard layout is set to Dvorak.
    [_BASE] = LAYOUT_split_3x5_3(
        DV_QUOT, DV_COMM, DV_DOT,  DV_P,    DV_Y,    DV_F,    DV_G,    DV_C,    DV_R,    DV_L,
        HM_A,    HM_O,    HM_E,    HM_U,    HM_I,    HM_D,    HM_H,    HM_T,    HM_N,    HM_S,
        DV_SCLN, DV_Q,    DV_J,    DV_K,    DV_X,    DV_B,    DV_M,    DV_W,    DV_V,    DV_Z,
                          BSP_CTL, TAB_ALT, SLS_NAV, ESC_NAV, ENT_SYM, SPC_CTL
    ),

    // Symbols + numbers. Held via either thumb (SYM). Number row on top. Symbols sit on the home row (moved
    // up from the bottom row for easier reach) as SM_* mod-taps: tap = symbol,
    // hold = that finger's base mod (GACS + inner-index Shift preserved), so a
    // modified symbol needs no press order. { and } ride the same two home-row
    // fingers as [ and ] used to (tap override, like ~), swapped down to the
    // bottom row as plain keys -- braces get the easier reach since they're used
    // more often than brackets. ( and ) ride the middle/index fingers (tap
    // override, like { }), duplicating the same two symbols already on the left
    // bottom row -- easier-reach parens are worth the duplication since they're
    // used far more than brackets or braces. The right hand carries a second set
    // of symbols on its bottom row as plain keys (no mods there); the left
    // bottom row is mostly transparent except for that ( ) pair on the
    // ring/middle fingers, mirroring [ ] on the right. The old shifted-number
    // symbols (!@#$%^&*()) are gone -- type them as Shift+number, except ( )
    // which now have dedicated spots. Ctrl is also on both thumbs (DEL_CTL
    // hold + SPC_CTL passthrough); the left outer thumb taps Delete whenever
    // SYM is held -- now only reachable via ENT_SYM on the right, so this is a
    // cross-hand chord.
    [_SYM] = LAYOUT_split_3x5_3(
        DV_1,    DV_2,    DV_3,    DV_4,    DV_5,    DV_6,    DV_7,    DV_8,    DV_9,    DV_0,
        SM_GRV,  SM_TILD, SM_LPRN, SM_RPRN, SM_MINS, SM_EQL,  SM_LCBR, SM_RCBR, SM_RPIP, SM_RMIN,
        _______, DV_LPRN, DV_RPRN, DV_BSLS, DV_UNDS, DV_PLUS, DV_LBRC, DV_RBRC, DV_QUES, DV_UNDS,
                          DEL_CTL, _______, _______, _______, _______, _______
    ),

    // Navigation and media. Left home row carries a full set of plain GACS
    // mods (Shift/GUI/Alt/Ctrl on pinky/ring/middle/index) so the right hand
    // can drive any mod + arrows for select / word-jump. System/reset keys now
    // live on _FN. Since these are plain (non-tap) mods once NAV is held, any
    // combination of them can be chorded reliably -- combined with the Tab key
    // on the ring finger (which is never needed for a mod alongside Tab), this
    // gives left-hand-only Ctrl/Alt/Shift+Tab: hold SLS_NAV (or HM_E/HM_T,
    // which reach NAV directly), hold index/middle/pinky for the mod(s) you
    // want, tap ring.
    [_NAV] = LAYOUT_split_3x5_3(
        _______, KC_TAB,  KC_MPRV, KC_MPLY, KC_MNXT, KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_DEL,
        KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, KC_MUTE, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_INS,
        KC_VOLD, KC_VOLU, _______, _______, _______, KC_TAB,  KC_ESC,  KC_CAPS, _______, KC_PSCR,
                          _______, _______, _______, _______, _______, _______
    ),

    // Function + system. Reached by holding NAV + SYM together (tri-layer) --
    // via ENT_SYM (the only SYM source) chorded with any NAV source: either
    // inner thumb, or the HM_E/HM_T/SM_LPRN/SM_RCBR layer-taps. F1-F10 mirror
    // the digit positions on _SYM; F11/F12 drop to the bottom row under F1/F2.
    // The home row carries its own full GACS mod set on both hands (mirrored)
    // so any F-key can be modified from the opposite hand, including multi-mod
    // chords. Reset keys sit in the bottom-right corner, behind the deliberate
    // combo.
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
// left-hand Ctrl+Tab (hold HM_A, tap TAB_ALT) and same-hand SYM/NAV layer use
// resolve as holds.
static bool is_thumb_key(uint16_t keycode) {
    switch (keycode) {
        case BSP_CTL:
        case TAB_ALT:
        case SLS_NAV:
        case ESC_NAV:
        case ENT_SYM:
        case SPC_CTL:
        case DEL_CTL:
            return true;
        default:
            return false;
    }
}

// Subset of is_thumb_key() that only covers the layer-tap thumbs (SYM/NAV),
// not the mod-tap thumbs (Ctrl on BSP_CTL/SPC_CTL, Alt on TAB_ALT). Used to
// scope HOLD_ON_OTHER_KEY_PRESS: the layer taps want instant resolution for
// chords like Ctrl+SYM+number, but applying that to a mod-tap thumb made
// ordinary typing rollover (the next letter's key-down landing before the
// thumb releases, which happens on nearly every word) mod-chord the letter
// instead of producing a space/backspace/tab.
static bool is_layer_thumb_key(uint16_t keycode) {
    switch (keycode) {
        case SLS_NAV:
        case ESC_NAV:
        case ENT_SYM:
            return true;
        default:
            return false;
    }
}

// Re-enable Quick Tap on the thumb keys only. QUICK_TAP_TERM is globally 0 so a
// doubled home-row letter never resolves as a mod; here we hand the thumb keys
// back the full tapping term so "tap, then tap-and-hold within the term" repeats
// the tapped key (auto-repeat) instead of engaging the hold (Ctrl / Alt / layer).
// This is what lets you hold Backspace to delete-repeat, hold Space, etc.
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t* record) {
    if (is_thumb_key(keycode)) {
        return TAPPING_TERM;
    }
    return QUICK_TAP_TERM;
}

bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record,
                      uint16_t other_keycode, keyrecord_t* other_record) {
    if (is_thumb_key(tap_hold_keycode) || is_thumb_key(other_keycode)) {
        return true;
    }
    return get_chordal_hold_default(tap_hold_record, other_record);
}

// Only the SYM/NAV layer-tap thumbs get instant hold-on-press; home row mods
// and the mod-tap thumbs stay on plain PERMISSIVE_HOLD. Home row mods need
// this so a cross-hand letter roll (e.g. H then E) needs a full tap of the
// second letter, not just a press, before it's read as a mod. The mod-tap
// thumbs need it so ordinary typing rollover onto the next letter doesn't
// mod-chord it instead of producing a space/backspace/tab. Layer taps still
// get instant resolution, for snappy chords like Ctrl+SYM+number.
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t* record) {
    return is_layer_thumb_key(keycode);
}

// Emit the shifted symbols ~ | (both hands' pipe) on the tap of their _SYM
// home-row mod-taps: a mod-tap can only store an 8-bit basic keycode, so
// tap_code16 sends the real shifted keycode here while the mod-tap's hold (the
// modifier) is still handled natively -- keeping the full tapping-term / Chordal
// Hold behavior on the hold.
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (record->tap.count && record->event.pressed) {
        switch (keycode) {
            case SM_TILD: tap_code16(DV_TILD); return false;
            case SM_LPRN: tap_code16(DV_LPRN); return false;
            case SM_RPRN: tap_code16(DV_RPRN); return false;
            case SM_RPIP: tap_code16(DV_PIPE); return false;
            case SM_LCBR: tap_code16(DV_LCBR); return false;
            case SM_RCBR: tap_code16(DV_RCBR); return false;
        }
    }
    return true;
}

// Activate _FN when both NAV and SYM are held.
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYM, _NAV, _FN);
}
