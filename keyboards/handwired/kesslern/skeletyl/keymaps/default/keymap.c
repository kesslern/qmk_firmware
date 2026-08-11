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

// Home row mods across all four fingers. Ring/middle/index (order ring ->
// index) are GUI/Alt/Ctrl; the inner index column (I/D) adds Shift (a home-row
// Shift alongside the outer thumbs); the pinky adds a second Ctrl for easier
// Ctrl+key reach. Tap = the letter, hold = the modifier; mirrored so a shortcut
// is held with the hand opposite the key it modifies.
#define HM_A    LCTL_T(DV_A)
#define HM_O    LGUI_T(DV_O)
#define HM_E    LALT_T(DV_E)
#define HM_U    LCTL_T(DV_U)
#define HM_I    LSFT_T(DV_I)
#define HM_D    RSFT_T(DV_D)
#define HM_H    RCTL_T(DV_H)
#define HM_T    RALT_T(DV_T)
#define HM_N    RGUI_T(DV_N)
#define HM_S    RCTL_T(DV_S)

// Thumbs (left -> right): Bspc SYM Tab Esc Enter Space. Every key is
// dual-function (tap / hold), no bare keys. NAV and SYM each sit on an inner
// and a mid thumb, so NAV+SYM -> _FN (tri-layer) is a comfortable inner-thumb
// chord. Outer thumbs add a Shift to take load off the pinky home-row shift.
//
// The left inner thumb used to tap Del; Del is rarely used, so its tap now
// fires a one-shot SYM layer instead (handled in process_record_user), while
// its hold still holds SYM momentarily -- the latter is load-bearing as the
// left half of the SYM+NAV->_FN tri-layer chord. Delete itself now lives on
// the Bspc position of the _SYM layer.
#define BSP_SFT LSFT_T(KC_BSPC)   // tap Bspc / hold Shift
#define SYM_OSL LT(_SYM, KC_DEL)  // tap one-shot SYM / hold SYM (tap -> OSL in process_record_user)
#define TAB_NAV LT(_NAV, KC_TAB)  // tap Tab   / hold NAV
#define ESC_NAV LT(_NAV, KC_ESC)  // tap Esc   / hold NAV
#define ENT_SYM LT(_SYM, KC_ENT)  // tap Enter / hold SYM
#define SPC_SFT RSFT_T(KC_SPC)    // tap Space / hold Shift

// _SYM left outer thumb: tap Delete (the old inner-thumb Del), hold Shift. The
// hold restores the left Shift that BSP_SFT provides on the base layer, so
// Shift stays available on both thumbs while SYM is active.
#define DEL_SFT LSFT_T(KC_DEL)

// _SYM home-row symbols. Symbols sit on the home row (moved up from the bottom
// row for easier reach), each keeping its finger's home-row mod on hold (GACS +
// inner-index Shift + pinky Ctrl, matching the base layer): tap = symbol, hold
// = mod. The bottom row has no mods, so those symbols are plain keys below.
//
// Mod-tap can only store an 8-bit *basic* keycode on its tap, so shifted symbols
// (~ and both |) can't ride a mod-tap directly: their defines wrap the mod over
// the underlying basic key and emit the real shifted symbol on tap in
// process_record_user (same override trick as SYM_OSL). Basic symbols use plain
// mod-taps; plain (non-mod) keys can hold shifted keycodes directly.
#define SM_GRV  LCTL_T(DV_GRV)   // left pinky:  tap ` / hold LCTL
#define SM_TILD LGUI_T(DV_GRV)   // left home:   tap ~ (tap override) / hold LGUI
#define SM_PIPE LALT_T(DV_BSLS)  // left home:   tap | (tap override) / hold LALT
#define SM_SLSH LCTL_T(DV_SLSH)  // left home:   tap / / hold LCTL
#define SM_MINS LSFT_T(DV_MINS)  // left home:   tap - / hold LSFT
#define SM_EQL  RSFT_T(DV_EQL)   // right home:  tap = / hold RSFT
#define SM_LBRC RCTL_T(DV_LBRC)  // right home:  tap [ / hold RCTL
#define SM_RBRC RALT_T(DV_RBRC)  // right home:  tap ] / hold RALT
#define SM_RPIP RGUI_T(DV_BSLS)  // right home:  tap | (tap override) / hold RGUI
#define SM_RMIN RCTL_T(DV_MINS)  // right pinky: tap - / hold RCTL

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Base: Dvorak alphas in Dvorak order. DV_ codes -> correct letters on a
    // host whose keyboard layout is set to Dvorak.
    [_BASE] = LAYOUT_split_3x5_3(
        DV_QUOT, DV_COMM, DV_DOT,  DV_P,    DV_Y,    DV_F,    DV_G,    DV_C,    DV_R,    DV_L,
        HM_A,    HM_O,    HM_E,    HM_U,    HM_I,    HM_D,    HM_H,    HM_T,    HM_N,    HM_S,
        DV_SCLN, DV_Q,    DV_J,    DV_K,    DV_X,    DV_B,    DV_M,    DV_W,    DV_V,    DV_Z,
                          BSP_SFT, SYM_OSL, TAB_NAV, ESC_NAV, ENT_SYM, SPC_SFT
    ),

    // Symbols + numbers. Held via either thumb (SYM) or entered for one keypress
    // by tapping SYM_OSL. Number row on top. Symbols sit on the home row (moved
    // up from the bottom row for easier reach) as SM_* mod-taps: tap = symbol,
    // hold = that finger's base mod (GACS + inner-index Shift preserved), so a
    // modified symbol needs no press order. The right hand carries a second set
    // of symbols on its bottom row as plain keys (no mods there); the left
    // bottom row stays transparent. The old shifted-number symbols (!@#$%^&*())
    // are gone -- type them as Shift+number. Shift is also on both thumbs
    // (DEL_SFT hold + SPC_SFT passthrough); the left outer thumb taps Delete, so
    // a tap of SYM_OSL then that thumb gives Delete.
    [_SYM] = LAYOUT_split_3x5_3(
        DV_1,    DV_2,    DV_3,    DV_4,    DV_5,    DV_6,    DV_7,    DV_8,    DV_9,    DV_0,
        SM_GRV,  SM_TILD, SM_PIPE, SM_SLSH, SM_MINS, SM_EQL,  SM_LBRC, SM_RBRC, SM_RPIP, SM_RMIN,
        _______, _______, _______, _______, _______, DV_PLUS, DV_LCBR, DV_RCBR, DV_QUES, DV_SLSH,
                          DEL_SFT, _______, _______, _______, _______, _______
    ),

    // Navigation and media. Left home row carries plain mods so the right hand
    // can drive Shift/Ctrl + arrows for select / word-jump. Mods sit on the same
    // fingers as the base layer (ring/middle/index = GUI/Alt/Ctrl) with Shift on
    // the otherwise-free pinky. System/reset keys now live on _FN. Since these
    // are plain (non-tap) mods once NAV is held, any combination of them can be
    // chorded reliably -- combined with the Tab key on the ring finger (which
    // is never needed for a mod alongside Tab), this gives left-hand-only
    // Ctrl/Alt/Shift+Tab: hold TAB_NAV, hold index/middle/pinky for the mod(s)
    // you want, tap ring. (Ctrl+Tab and Alt+Tab alone are simpler: just hold
    // HM_U/HM_E from the base layer and tap TAB_NAV.)
    [_NAV] = LAYOUT_split_3x5_3(
        _______, KC_TAB,  KC_MPRV, KC_MPLY, KC_MNXT, KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_DEL,
        KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, KC_MUTE, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_INS,
        KC_VOLD, KC_VOLU, _______, DV_BSLS, DV_UNDS, KC_TAB,  KC_ESC,  KC_CAPS, _______, KC_PSCR,
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
        case SYM_OSL:
        case TAB_NAV:
        case ESC_NAV:
        case ENT_SYM:
        case SPC_SFT:
        case DEL_SFT:
            return true;
        default:
            return false;
    }
}

// Subset of is_thumb_key() that only covers the layer-tap thumbs (SYM/NAV),
// not the shift thumbs (BSP_SFT/SPC_SFT). Used to scope HOLD_ON_OTHER_KEY_PRESS:
// the layer taps want instant resolution for chords like Ctrl+SYM+number, but
// applying that to SPC_SFT made ordinary typing rollover (the next letter's
// key-down landing before space is released, which happens on nearly every
// word) capitalize the letter instead of producing a space.
static bool is_layer_thumb_key(uint16_t keycode) {
    switch (keycode) {
        case SYM_OSL:
        case TAB_NAV:
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
// the tapped key (auto-repeat) instead of engaging the hold (Shift / layer).
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
// and the Shift thumbs stay on plain PERMISSIVE_HOLD. Home row mods need this
// so a cross-hand letter roll (e.g. H then E) needs a full tap of the second
// letter, not just a press, before it's read as a mod. Shift thumbs need it so
// ordinary typing rollover onto the next letter doesn't capitalize it instead
// of producing a space/backspace. Layer taps still get instant resolution, for
// snappy chords like Ctrl+SYM+number.
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t* record) {
    return is_layer_thumb_key(keycode);
}

// Turn a *tap* of SYM_OSL into a one-shot SYM layer (next keypress lands on
// _SYM, then it clears), instead of sending the LT's Del tap keycode. A *hold*
// (tap.count == 0) is left untouched so the LT still holds SYM momentarily --
// that hold is the left half of the SYM+NAV->_FN tri-layer chord. The two
// set/clear calls mirror what QMK's core OSL keycode does on press/release.
//
// Also emit the shifted symbols ~ | (both hands' pipe) on the tap of their _SYM
// home-row mod-taps: a mod-tap can only store an 8-bit basic keycode, so
// tap_code16 sends the real shifted keycode here while the mod-tap's hold (the
// modifier) is still handled natively -- keeping the full tapping-term / Chordal
// Hold behavior on the hold.
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    // Both the arm and disarm happen here, on release, rather than mirroring
    // core's press-then-release split. If ONESHOT_START were set on press,
    // returning false would make process_record() treat that same press as an
    // "other key was pressed while one-shot is active" event (since the
    // one-shot layer is already active by the time that check runs) and
    // immediately clear ONESHOT_OTHER_KEY_PRESSED -- collapsing the one-shot
    // before the thumb key is even released. Doing both calls on release
    // sidesteps that: that check only fires on press events.
    if (keycode == SYM_OSL && record->tap.count) {
        if (!record->event.pressed) {
            set_oneshot_layer(_SYM, ONESHOT_START);
            clear_oneshot_layer_state(ONESHOT_PRESSED);
        }
        return false;
    }

    if (record->tap.count && record->event.pressed) {
        switch (keycode) {
            case SM_TILD: tap_code16(DV_TILD); return false;
            case SM_PIPE: tap_code16(DV_PIPE); return false;
            case SM_RPIP: tap_code16(DV_PIPE); return false;
        }
    }
    return true;
}

// Activate _FN when both NAV and SYM are held.
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYM, _NAV, _FN);
}
