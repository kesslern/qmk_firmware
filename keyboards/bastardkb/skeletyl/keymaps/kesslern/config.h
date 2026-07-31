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

// How long a key must be held to count as a mod. Lower = faster mods but more
// misfires while typing; raise toward 220-250 if you get accidental mods.
#define TAPPING_TERM 190

// Never treat "hold then tap the same key" as a mod (avoids mods when you type
// a home-row letter twice quickly, e.g. the "ss" in "less").
#define QUICK_TAP_TERM 0
