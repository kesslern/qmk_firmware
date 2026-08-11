// Copyright 2026 Nathan Kessler
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// --- Home row mod tuning ---
// Chordal Hold applies the "opposite hands" rule: a same-hand roll resolves as
// a tap, a cross-hand chord resolves as a hold. Handedness is derived
// automatically from the split layout.
#define CHORDAL_HOLD

// Hold triggers early when another key is fully tapped inside the term -> snappy
// modifiers without waiting out the tapping term.
#define PERMISSIVE_HOLD

// Hold triggers on the *press* of another key, not just a full tap -- but only
// for the thumb keys (see get_hold_on_other_key_press() in keymap.c). Needed
// for chords like Ctrl (home row) + SYM (thumb) + a number key: without this,
// a same-hand mod+thumb pair held together (both exempted from Chordal Hold's
// same-hand veto) only resolves to a hold once TAPPING_TERM elapses or the
// third key is released, so a quick chord can register as a tapped letter
// instead of Ctrl+number. Scoped to thumb keys only, since applying this
// globally also made cross-hand home-row-mod rolls (e.g. H then E) resolve to
// a mod on the mere press of the second letter instead of a full tap, causing
// frequent misfires during normal typing; those keys keep the gentler
// PERMISSIVE_HOLD behavior above.
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

// How long a key must be held to count as a mod. Lower = faster mods but more
// misfires while typing; raise toward 220-250 if you get accidental mods.
#define TAPPING_TERM 190

// Suppress the hold action entirely when a tap-hold key is pressed within this
// many ms of the *previous* keystroke -- a direct typing-speed signal, unlike
// Chordal Hold's same-hand/cross-hand heuristic. By default this only covers
// alpha keys, comma/dot/semicolon/slash, and space (see is_flow_tap_key() in
// action_tapping.c), which lines up with the home row mods (all letters
// underneath the Dvorak remap) and SPC_SFT -- it leaves the SYM/NAV thumb
// keys alone since their tap keycodes (Del/Tab/Esc/Enter) aren't in that set.
#define FLOW_TAP_TERM 150

// Never treat "hold then tap the same key" as a mod (avoids mods when you type
// a home-row letter twice quickly, e.g. the "ss" in "less").
#define QUICK_TAP_TERM 0

// Enable the get_quick_tap_term() override in keymap.c. Without this define the
// callback is compiled out and QUICK_TAP_TERM 0 applies to every key, which
// disables tap-then-hold auto-repeat on the thumb keys (hold Bspc to delete-
// repeat, etc.).
#define QUICK_TAP_TERM_PER_KEY
