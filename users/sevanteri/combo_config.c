#include QMK_KEYBOARD_H
#ifdef COMBO_ENABLE

#include "sevanteri.h"
#include "keymap_finnish.h"

#include "action_tapping.h"
/* #include "combos.h" */
#include "g/keymap_combo.h"

bool get_combo_must_tap(uint16_t combo_idx, combo_t* combo) { // {{{
    switch (combo_idx) {
        case C_CODEBLK:
        case C_THUMB_CTL_SFT:
        case C_THUMB_ALT_SFT:
        case C_THUMB_ALT_CTL:
            return false;
        case C_EXCLAMATIONP:
        case C_ACUT:
            return true;
    }
    switch (combo->keycode) {
        case QK_TAP_DANCE...QK_TAP_DANCE_MAX:
            return false;
    }

    // if any underlying key is a MT/LT/MO key, then our combo is tap-only.
    uint16_t key;
    uint8_t idx = 0;
    while ((key = pgm_read_word(&combo->keys[idx])) != COMBO_END) {
        switch (key) {
            case QK_MOD_TAP...QK_MOD_TAP_MAX:
            case QK_LAYER_TAP...QK_LAYER_TAP_MAX:
            case QK_MOMENTARY...QK_MOMENTARY_MAX:
                return true;
        }
        idx += 1;
    }
    return false;
} // }}}

// custom combo terms {{{
uint16_t get_combo_term(uint16_t index, combo_t *combo) {

    // ctrl6 is the first vertical combo
    if (index >= C_CTRLSIX) return 100;


    if (KEYCODE_IS_MOD(combo->keycode)) return COMBO_HOLD_TERM;
    /* if (get_combo_tap_only(index, combo)) return 20; */

    /* switch(combo->keycode) { */
    /*     case RESET: */
    /*         return COMBO_HOLD_TERM; */
    /* } */

    switch(index) {
        case C_QUOT:
        case C_WE_TAB:
            return 20;
        case C_ACUT:
            return 15;
    }

    // Longer term for THUMB+alpha
    /* if (combo->keys[0] == MY_THR3 || */
    /*     combo->keys[0] == MY_THR2) { */
    /*     return 100; */
    /* } */

    return COMBO_TERM;
}
// }}}

bool get_combo_must_hold(uint16_t index, combo_t *combo) { // {{{
    switch(index) {
        case C_THUMB_CTL_SFT:
        case C_THUMB_ALT_SFT:
        case C_THUMB_ALT_CTL:
            return true;
    }
    switch(combo->keycode) {
        case RESET:
            return true;
    }
    if (KEYCODE_IS_MOD(combo->keycode)) return true;

    return false;
} // }}}

// process_combo_key_release {{{
#ifdef COMBO_PROCESS_KEY_RELEASE
bool process_combo_key_release(uint16_t combo_index, combo_t *combo, uint8_t key_index, uint16_t keycode) {
    switch (combo_index) {
        case C_THUMB_CTL_SFT:
        case C_THUMB_ALT_SFT:
        case C_THUMB_ALT_CTL:
            switch(keycode) {
                case MY_A:
                case MY_THL1:
                    unregister_mods(MOD_MASK_CTRL);
                    break;
                case MY_S:
                    unregister_mods(MOD_MASK_SHIFT);
                    break;
                case MY_THL2:
                    unregister_mods(MOD_MASK_ALT);
                    break;
            }
            break;
        case C_GMAIL:
            // true releases the combo immediately.
            return true;
    }
    return false;
}
#endif
// }}}
#endif
