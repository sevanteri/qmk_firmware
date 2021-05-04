#include QMK_KEYBOARD_H
#include "sevanteri.h"
#include "casemodes.h"
#include "pimoroni_trackball.h"

static uint8_t mods = 0;
#define MODS (get_mods() | get_oneshot_mods())

#define INSERT NULL
#define NORMAL leader_start_func

#define TO_INSERT return reset_to(INSERT)
#define TO_NORMAL return reset_to(NORMAL)

void* leader_start_func(uint16_t keycode, bool pressed);
static void* leader_g(uint16_t keycode, bool pressed);

bool select_on = false;
uint16_t pending_operator = 0;
// the mode to return to after the pending operator
void* return_to = NORMAL;

static void tap(uint16_t kc, bool pressed) {
    pressed ? register_code16(kc) : unregister_code16(kc);
}

static void stap(uint16_t kc, bool pressed) {
    if (select_on) kc = S(kc);
    tap(kc, pressed);
}

#define do_(code) do { \
    code \
} while (0)

#define h do_( \
    stap(KC_LEFT, pressed); \
)
#define l do_( \
    stap(KC_RIGHT, pressed); \
)

#define j stap(KC_DOWN, pressed)
#define k stap(KC_UP, pressed)

#define e do_( \
    stap(LCTL(KC_RIGHT), pressed); \
)
#define b do_( \
    stap(LCTL(KC_LEFT), pressed); \
)
#define end do_( \
    stap(KC_END, pressed); \
)
#define home do_( \
    stap(KC_HOME, pressed); \
)

#define vdn do_(select_on = true;)
#define vup do_(select_on = false;)
#define v(s) do_( \
    vdn; s; vup; \
)

#define V do_( \
    home; vdn; end; \
)

#define _X tap(KC_BSPC, pressed)
#define x tap(KC_DEL, pressed)

static void reset(void) {
    if (select_on) {
        vup;
    }
    if (mods) {
        set_mods(mods);
        mods = 0;
    }
    select_on = false;
    pending_operator = 0;
    return_to = NORMAL;
}

static void* reset_to(void* f) {
    reset();
    return f;
}

static void* resolve_pending_operator(void) {
    if (!pending_operator) return NORMAL;
    if (select_on) pending_operator = S(pending_operator);
    tap_code16(pending_operator);
    return reset_to(return_to);
}

static void* await_operator(uint16_t oper, void* ret) {
    pending_operator = oper;
    return_to = ret;
    vdn;
    return NORMAL;
}

static void* leader_g(uint16_t keycode, bool pressed) {
    if (pressed) return leader_g;
    switch (keycode) {
        case KC_G:
            tap_code16(KC_HOME); TO_NORMAL;
        case FI_QUOT:
            layer_on(_GAME);
            break;
        case KC_S:
            enable_xcase_with(FI_UNDS);
            if (MODS & MOD_MASK_SHIFT)
                enable_caps_word();
            break;
        case KC_A:
            enable_xcase();
            break;
        case KC_C:
            enable_caps_word();
            break;

        case KC_J:
            tap_code16(KC_VOLD);
            return leader_g;
        case KC_K:
            tap_code16(KC_VOLU);
            return leader_g;
    }
    return INSERT;
}

void* leader_start_func(uint16_t keycode, bool pressed) {
    mods = get_mods() & MOD_MASK_CS;
    /* if (MODS & MOD_MASK_SHIFT) { */
    /*     keycode = LSFT(keycode); */
    /*     del_mods(MOD_MASK_SHIFT); */
    /*     del_oneshot_mods(MOD_MASK_SHIFT); */
    /* } */
    /* if (MODS & MOD_MASK_CTRL) { */
    /*     keycode = LCTL(keycode); */
    /*     del_mods(MOD_MASK_CTRL); */
    /*     del_oneshot_mods(MOD_MASK_CTRL); */
    /* } */

    // keys that do care about `press`
    // mostly movement keys, nothing that changes to another mode.
    switch (keycode) {
        // movement {{{
        case KC_H: stap(KC_LEFT, pressed); break;
        case KC_J: stap(KC_DOWN, pressed); break;
        case KC_K: stap(KC_UP, pressed); break;
        case KC_L: stap(KC_RIGHT, pressed); break;

        case KC_W:
        case KC_E: e; break;
        case KC_B: b; break;
        case FI_DLR: end; break;
        case FI_UNDS:
        case FI_DIAE:
        case KC_0:
            home;
            break;
        case C(KC_U):
        case C(KC_Y):
        case C(KC_B):
            tap(KC_PGUP, pressed);
            TO_NORMAL;
        case C(KC_E):
        case C(KC_F):
        case C(KC_D):
            tap(KC_PGDOWN, pressed);
            TO_NORMAL;

        // }}}

        case KC_X:
            (mods & MOD_MASK_SHIFT) ? x: _X;
            TO_NORMAL;

    }

    // other keys work only on release
    if (pressed) return NORMAL;

    switch (keycode) {
        // general {{{
        case KC_ESC:
            TO_NORMAL;
        case KC_U:
            tap_code16(LCTL(KC_Z));
            TO_NORMAL;

        case KC_G:
        case S(KC_G):
            reset();
            return leader_g;
        // }}}

        case S(KC_S): V; x; TO_INSERT;
        case KC_S: x; TO_INSERT;

        case S(KC_C): vdn; end; x; TO_INSERT;
        case KC_C:
            if (!pending_operator) {
                if (select_on) {
                    x;
                    TO_INSERT;
                } else {
                    return await_operator(KC_BSPC, INSERT);
                }
            } else {
                vup; V;
            }
            break;

        case S(KC_D): vdn; end; x; TO_NORMAL;
        case KC_D:
            if (!pending_operator) {
                if (select_on) {
                    x;
                    TO_NORMAL;
                } else {
                    return await_operator(KC_BSPC, NORMAL);
                }
            } else {
                vup; V;
            }
            break;

        case KC_V:
            if (select_on) vup;
            else vdn;
            break;
        case S(KC_V): V; break;

        case KC_A:
        case KC_I:
            TO_INSERT;


        case S(KC_A):
            vup; end; TO_INSERT;
        case S(KC_I):
            vup; home; TO_INSERT;

        case KC_O:
            vup; end;
            tap_code(KC_ENTER);
            TO_INSERT;
        case S(KC_O):
            vup; home;
            tap_code(KC_ENTER);
            k;
            TO_INSERT;

    }
    return resolve_pending_operator();
}

void leader_end(void) {
    reset();
    trackball_set_hsv(rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val());
}

void leader_start(void) {
    trackball_set_rgbw(0, rgblight_get_val(), 0, 0);
}
