# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working in this
directory.

## What this is

The `default` keymap for a personal handwired split keyboard,
`keyboards/handwired/kesslern/skeletyl/`, inside an otherwise stock upstream QMK
checkout. Nearly all work happens in this directory; the rest of the tree is
stock QMK and shouldn't need changes for typical tasks.

The keyboard: a handwired 3x5+3 split (BastardKB Skeletyl form factor) driven
by two Pro Micro (ATmega32U4) halves, one keymap (`default`), Dvorak-based.
Handedness is stored in EEPROM (`EE_HANDS`), so each half must be flashed with
matching handedness — see
`keyboards/handwired/kesslern/skeletyl/readme.md` for wiring and the
per-half flash/handedness commands.

## Commands

Build and flash (run from the repo root):

```
make handwired/kesslern/skeletyl:default
make handwired/kesslern/skeletyl:default:flash
qmk flash -kb handwired/kesslern/skeletyl -km default -bl avrdude-split-left
qmk flash -kb handwired/kesslern/skeletyl -km default -bl avrdude-split-right
```

Lint/validate the keyboard's data-driven config:

```
qmk lint -kb handwired/kesslern/skeletyl
qmk format-json -i keyboards/handwired/kesslern/skeletyl/keyboard.json
```

Render the KLE layout JSONs (`layout*.json`) to SVGs for visual review, from
this directory:

```
./render-layouts.sh
```

This runs `node render-kle.js <layout>.json out/<layout>.svg` for every
`layout*.json` in the directory (`out/` is gitignored). `render-kle.js`
vendors `kle-serial.js` — a copy of keyboard-layout-editor.com's own
`serial.js` — because the published `@ijprest/kle-serial` npm package
mis-places rotated keys; don't swap it for the npm package.

## Architecture

### Keymap logic (`keymap.c`)

Four layers: `_BASE` (Dvorak alphas), `_SYM` (numbers/symbols), `_NAV`
(navigation/media), `_FN` (function keys/system, reached as a tri-layer when
NAV+SYM are both held via `update_tri_layer_state()`).

Every home-row key is a mod-tap (GACS mods mirrored across both hands) and
every thumb key is dual-function (tap a key / hold a layer or shift) — there
are no bare keys on the home row or thumbs. The comments in `keymap.c` and
`config.h` document the tap-hold tuning in detail
(`CHORDAL_HOLD`, `PERMISSIVE_HOLD`, `HOLD_ON_OTHER_KEY_PRESS_PER_KEY`,
`FLOW_TAP_TERM`, `QUICK_TAP_TERM_PER_KEY`, `SPECULATIVE_HOLD`) and *why* each is set — read those
before changing tap-hold behavior, since the settings interact (e.g.
`get_hold_on_other_key_press_user()` is scoped to layer-tap thumbs only,
because applying it globally broke cross-hand home-row-mod rolls).

Several `_SYM` home-row mod-taps (`SM_TILD`, `SM_PIPE`, `SM_RPIP`, `SM_LCBR`,
`SM_RCBR`) need a *shifted* symbol on tap, which a mod-tap can't carry
directly (it can only store an 8-bit basic keycode on its tap): their tap is
overridden in `process_record_user()` to fire `tap_code16()` with the real
shifted keycode, while the hold still resolves natively as the modifier.

`is_thumb_key()` / `is_layer_thumb_key()` are the two key-classification
helpers other callbacks branch on — check them first when adding a new thumb
key or changing chording behavior.

### Layout JSON files (`layout*.json`)

Raw keyboard-layout-editor.com exports: `layout-main.json` (`_BASE` only),
`layout-sym.json`/`layout-nav.json`/`layout-fn.json` (one per other layer),
and `layout.json` (a combined overview with every layer's label baked into
each key's multi-position legend, one legend line per layer). Used purely as
documentation/visual reference for `keymap.c` — rendered to SVG via
`render-layouts.sh`. Not consumed by QMK or the build, and there's no
generator: whenever a `keymap.c` change alters a key's tap/hold behavior,
update the matching legend line(s) (and `t` color-per-line string, if present)
in every layout file that shows that key — `render-layouts.sh` is the way to
check the edit rendered correctly.

### Keyboard-level data (`keyboards/handwired/kesslern/skeletyl/`)

One directory up from this keymap: standard QMK data-driven config —
`keyboard.json` (pins, matrix, `LAYOUT_split_3x5_3` physical layout, USB IDs)
and `config.h` (just `EE_HANDS`). No `<keyboard>.c`/`.h` — this keyboard has no
custom hardware code beyond pin/matrix declaration.

## Conventions from `.github/copilot-instructions.md`

That file targets an automated PR-review bot and is scoped to `keyboards/**`,
but its content reflects real QMK PR-acceptance rules worth following when
editing this keymap:
- License headers (`// Copyright <year> <name>` + SPDX identifier) are
  required on `.c`/`.h` files — `keymap.c` and `config.h` here already follow
  this pattern; match it in any new file.
- `config.h` must not contain `#define DESCRIPTION`, explanatory comment
  blocks about *what* a feature is, commented-out unused defines, or
  `#include "config_common.h"`.
- The default keymap folder is conventionally kept minimal (just the
  `keymaps[]` array) upstream; this repo's `default` keymap intentionally
  goes beyond that (custom tap-hold callbacks, layout JSON, render scripts)
  since it's a personal fork, not an upstream contribution — don't strip that
  out to match upstream's "pristine default keymap" convention.
