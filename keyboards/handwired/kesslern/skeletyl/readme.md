# Skeletyl (handwired)

A handwired build of the [BastardKB Skeletyl](https://github.com/Bastardkb/Skeletyl)
3x5+3 split keyboard, driven by two Pro Micro (ATmega32U4) controllers wired
directly to the switches.

* Keyboard Maintainer: [kesslern](https://github.com/kesslern)
* Hardware Supported: Pro Micro / compatible ATmega32U4 boards, one per half

## Wiring

Pin labels below are the Pro Micro silkscreen numbers; the QMK name is the AVR pin.

| Role     | AVR pins            | Pro Micro labels |
| -------- | ------------------- | ---------------- |
| Rows (4) | D4, C6, D7, E6      | 4, 5, 6, 7       |
| Cols (5) | B4, B5, B6, B2, B3  | 8, 9, 10, 16, 14 |
| Serial   | D1                  | 2                |

Diodes are wired ROW2COL (stripe toward the column).

Handedness is stored in EEPROM (`EE_HANDS`). Flash each half with the matching
handedness once:

    make handwired/kesslern/skeletyl:default:flash

then set handedness per half, e.g.:

    qmk flash -kb handwired/kesslern/skeletyl -km default -bl avrdude-split-left
    qmk flash -kb handwired/kesslern/skeletyl -km default -bl avrdude-split-right

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix and plug in the keyboard
* **Physical reset**: Short the RST and GND pins on the Pro Micro

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools)
and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for
more information. Brand new to QMK? Start with our
[Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
