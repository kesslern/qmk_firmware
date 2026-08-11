// Copyright 2026 Nathan Kessler
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Handedness is stored in EEPROM. Flash each half once with the matching
// target (`:flash` after writing handedness, or the -left / -right eeprom
// util) so the halves know which side they are.
#define EE_HANDS
