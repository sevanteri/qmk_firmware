#include QMK_KEYBOARD_H
#include "sevanteri.h"
#include "casemodes.h"

#define INSERT NULL
#define NORMAL leader_start_func

#define TO_INSERT return reset_to(INSERT)
#define TO_NORMAL return reset_to(NORMAL)

void* leader_start_func(uint16_t keycode);

bool select_on = false;
uint16_t pending_operator = 0;
// the mode to return to after the pending operator
void* return_to = NORMAL;

void tap(uint16_t kc) {
    if (select_on) kc = S(kc);
    tap_code16(kc);
}

#define do_(code) do { \
    code \
} while (0)

#define h do_( \
    tap(KC_LEFT); \
)
#define l do_( \
    tap(KC_RIGHT); \
)

#define j tap(KC_DOWN)
#define k tap(KC_UP)

// w is pretty difficult to get working exactly right
#define w do_( \
    tap(LCTL(KC_RIGHT)); \
    tap(LCTL(KC_RIGHT)); \
    tap(LCTL(KC_LEFT)); \
)

#define e do_( \
    tap(LCTL(KC_RIGHT)); \
)
#define b do_( \
    tap(LCTL(KC_LEFT)); \
)
#define end do_( \
    tap(KC_END); \
)
#define home do_( \
    tap(KC_HOME); \
)

#define vdn do_(select_on = true;)
#define vup do_(select_on = false;)
#define v(s) do_( \
    vdn; s; vup; \
)

#define V do_( \
    home; vdn; end; \
)

#define X tap(KC_BSPC)
#define x tap(KC_DEL)

void reset(void) {
    if (select_on) {
        vup;
    }
    select_on = false;
    pending_operator = 0;
    return_to = NORMAL;
}

void* reset_to(void* f) {
    reset();
    return f;
}

void* resolve_pending_operator(void) {
    if (!pending_operator) return NORMAL;

    tap(pending_operator);
    return reset_to(return_to);
}

void* leader_text_obj(uint16_t keycode) {
    switch (keycode) {
        case KC_W: vup; e; v(b); break;
    }
    return resolve_pending_operator();
}

void* await_operator(uint16_t oper, void* ret) {
    pending_operator = KC_BSPC;
    return_to = ret;
    vdn;
    return NORMAL;
}

void* leader_g(uint16_t keycode) {
    switch (keycode) {
        case KC_S:
            enable_xcase_with(FI_UNDS);
            break;
        case S(KC_S):
            enable_caps_word();
            enable_xcase_with(FI_UNDS);
            break;

        case KC_C:
            enable_caps_word();
            break;
    }
    return INSERT;
}

void* leader_start_func(uint16_t keycode) {
    uint8_t mods = get_mods();
    if (mods & MOD_MASK_SHIFT) {
        keycode = LSFT(keycode);
        del_mods(MOD_MASK_SHIFT);
    }

    switch (keycode) {
        // general {{{
        case KC_ESC:
            TO_NORMAL;
        case KC_U:
            tap_code16(LCTL(KC_Z));
            TO_NORMAL;

        case KC_G:
            reset();
            return leader_g;
        // }}}
        // movement {{{
        case KC_H: tap(KC_LEFT); break;
        case KC_J: tap(KC_DOWN); break;
        case KC_K: tap(KC_UP); break;
        case KC_L: tap(KC_RIGHT); break;

        case KC_W:
        case KC_E: e; break;
        case KC_B: b; break;
        case FI_DLR: end; break;
        case FI_UNDS:
        case S(FI_DIAE):
        case KC_0:
            home;
            break;

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
            if (pending_operator) {
                return leader_text_obj;
            } else {
                TO_INSERT;
            }


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

        case KC_X:
            x; TO_NORMAL;
        case S(KC_X):
            X; TO_NORMAL;

    }
    return resolve_pending_operator();
}
