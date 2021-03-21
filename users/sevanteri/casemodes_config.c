#include QMK_KEYBOARD_H

bool terminate_case_modes(uint16_t keycode, const keyrecord_t *record) { // {{{
    switch (keycode) {
        // Keycodes to ignore (don't disable caps word)

        case KC_A ... KC_Z:
        case KC_1 ... KC_0:
            // If mod chording disable the mods
            if (record->event.pressed && (get_mods() != 0)) {
                return true;
            }
            return false;

        case KC_ESC:
        case KC_ENT:
        case KC_TAB:
        case KC_SPC:
            return true;
    }

    return false;
} // }}}
