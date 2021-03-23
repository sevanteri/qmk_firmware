/* Copyright 2021 Pete Sevander pete.sevander@gmail.com @sevanteri
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


/* ALARM! HÄLYTYS! Some of these require modifications to tap dance processing
 * to handle tap releases in addition to handling tap presses.
 * The modifications can be found at https://github.com/sevanteri/qmk_firmware/commit/861cbd20303f5d93537a7904879a3f9f7e1ea5c5
 *
 * The changes are not big and should be easy to `git cherry-pick`.
 * */


#include QMK_KEYBOARD_H
#include "custom_tap_dances.h"

// common {{{
void tap_release(qk_tap_dance_state_t* state, void* user_data) {
    // immediately finish TD on first release.
    state->finished = true;
}
// }}}

// mod taps {{{
void mt_fin(qk_tap_dance_state_t* state, void* user_data) {
    // TAPPING_TERM has passed, register mods.
    mod_tap_t *data = (mod_tap_t*)user_data;
    if (state->pressed) {
        data->held = true;
        register_mods(data->mods);
    }
}
void mt_reset(qk_tap_dance_state_t* state, void* user_data) {
    // key was released, tap keycode or unregister mods.
    mod_tap_t *data = (mod_tap_t*)user_data;
    if (data->held) {
        data->held = false;
        unregister_mods(data->mods);
    } else {
        tap_code16(data->keycode);
    }
}
// }}}
// layer taps {{{
void lt_fin(qk_tap_dance_state_t* state, void* user_data) {
    // TAPPING_TERM has passed, activate layer.
    layer_tap_t *data = (layer_tap_t*)user_data;
    if (state->pressed) {
        data->held = true;
        layer_on(data->layer);
    }
}
void lt_reset(qk_tap_dance_state_t* state, void* user_data) {
    // key was released, tap keycode or deactivate layer.
    layer_tap_t *data = (layer_tap_t*)user_data;
    if (data->held) {
        data->held = false;
        layer_off(data->layer);
    } else {
        tap_code16(data->keycode);
    }
}
// }}}
// tap hold release {{{
void thr_fin(qk_tap_dance_state_t* state, void* user_data) {
    tap_hold_release_t *data = (tap_hold_release_t*)user_data;
    if (state->pressed) {
        data->held = true;
        data->on_hold();
    }
}
void thr_reset(qk_tap_dance_state_t* state, void* user_data) {
    tap_hold_release_t *data = (tap_hold_release_t*)user_data;
    if (data->held) {
        data->held = false;
        data->on_release();
    } else {
        tap_code16(data->keycode);
    }
}
// }}}
// sentence end {{{
void sentence_end_tap(qk_tap_dance_state_t *state, void *user_data) {
    tap_code16(((sentence_end_key*)user_data)->keycode);
}
void sentence_end_fin(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        // Double tapping produces
        // "<key> <one-shot-shift>" i.e. dot, space and capitalize next letter.
        // This helps to quickly end a sentence and begin another one
        // without having to hit shift.
        case 2:
            /* Check that Shift is inactive */
            if (!(get_mods() & MOD_MASK_SHIFT)) {
                tap_code(KC_BSPC);
                tap_code(KC_SPC);
                /* Internal code of OSM(MOD_LSFT) */
                set_oneshot_mods(MOD_LSFT | get_oneshot_mods());
            }
            break;
    }
};




