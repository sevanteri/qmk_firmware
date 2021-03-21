#include QMK_KEYBOARD_H
#include "sevanteri.h"

bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) { // {{{
    switch (keycode) {
        case LCTL_T(KC_ESC):
        case MY_THL1:
        /* case MY_THL2: */
        case MY_THL3:
        case MY_THR2:
            return false;
        default:
            return true;
    }
}
// }}}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) { // {{{
    switch (keycode) {
        case MY_A:
        case MY_S:
        case MY_D:
        case MY_F:
        case MY_G:
        case MY_J:
        case MY_K:
        case MY_L:
        case MY_OE:
        case MY_AE:
            return false;
        default:
            return true;
    }
}
// }}}

// custom tapping terms for keys {{{
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MY_A:
        case MY_S:
            return 250;
    }
    return TAPPING_TERM;
}
// }}}
