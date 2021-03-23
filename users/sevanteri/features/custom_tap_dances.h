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

// common tap release function (see link to commit above)
void tap_release(qk_tap_dance_state_t* state, void* user_data);

// mod taps with any keycode
typedef struct {
    uint16_t keycode;
    uint8_t mods;
    bool held;
} mod_tap_t;
void mt_fin(qk_tap_dance_state_t* state, void* user_data);
void mt_reset(qk_tap_dance_state_t* state, void* user_data);
#define ACTION_TAP_DANCE_MOD_TAP(_mods, _keycode) \
    { .fn = {NULL, mt_fin, mt_reset, tap_release}, .user_data = (void*)&((mod_tap_t){.keycode=_keycode, .mods=_mods})}

// layer taps with any keycode
typedef struct {
    uint16_t keycode;
    uint8_t layer;
    bool held;
} layer_tap_t;
void lt_fin(qk_tap_dance_state_t* state, void* user_data);
void lt_reset(qk_tap_dance_state_t* state, void* user_data);
#define ACTION_TAP_DANCE_LAYER_TAP(_layer, _keycode) \
    { .fn = {NULL, lt_fin, lt_reset, tap_release}, .user_data = (void*)&((layer_tap_t){.keycode=_keycode, .layer=_layer})}


/* tap _keycode on tap, call _on_hold(void) when held, and call
 * _on_release(void) when released. */
typedef struct {
    uint16_t keycode;
    bool held;
    void(*on_hold)(void);
    void(*on_release)(void);
} tap_hold_release_t;
void thr_fin(qk_tap_dance_state_t* state, void* user_data);
void thr_reset(qk_tap_dance_state_t* state, void* user_data);
#define ACTION_TAP_DANCE_TAP_HOLD_RELEASE(_keycode, _on_hold, _on_release) { \
    .fn = {NULL, thr_fin, thr_reset, tap_release}, \
    .user_data = (void*)&((tap_hold_release_t){ \
            .keycode=_keycode, \
            .on_hold=_on_hold, \
            .on_release=_on_release \
            }) \
}


/* sentence ending */
typedef struct {
    uint16_t keycode;
} sentence_end_key;
void sentence_end_tap(qk_tap_dance_state_t *state, void *user_data);
void sentence_end_fin(qk_tap_dance_state_t *state, void *user_data);
#define SENTENCE_END_TAP_DANCE(on_tap, on_finished, on_reset, user_user_data) \
        { .fn = {on_tap, on_finished, on_reset}, .user_data = (void*)&((sentence_end_key){.keycode=user_user_data}), }
