#pragma once
#include "keymap_finnish.h"
#include "tap_dance_config.h"

enum customKeycodes {
    // custom tap-hold keys
    // QK_LAYER_TAP + n results into LT(0, n) which is fine as long as layer-taps to base layer aren't used anywhere.
    LEADER_ENTER = QK_LAYER_TAP + 1,
    FUNC_HASH,
    LCTL_SLASH,
    LGUI_QUOT,

    CODEBLK = SAFE_RANGE, // `code`
    WORDCAPS, // caps lock for one word
    LEADER,
    MY_PARENSBOTH,
    MY_SQUAREBRACEBOTH,
    MY_CURLYBRACEBOTH,

};

enum my_layers {
    _BASE = 0, // default layer
    _GAME, // gaming layer
    _NUM, // numbers and f-keys
    _MOUS,
    _FUNC, // function layer
    _STUF, // reset and maybe some other stuff
};


// other keys
#define CTRLTAB LCTL(KC_TAB)
#define CSFTTAB LCTL(LSFT(KC_TAB))
#define CTRLESC CTL_T(KC_ESC)

// left thumb keys (no ignore_mod_tap_interrupt)
#define  MY_THL1  LCTL_T(KC_BSPC)
#define  MY_THL2  LALT_T(KC_SPC)
#define  MY_THL3  KC_LGUI
#define  MY_THL4  KC_BTN2

#define  MY_THUL1  MO(_FUNC)
#define  MY_THUL2  TG(_GAME)

// right thumb keys
/* #define  MY_THR1  LT(_FUNC, KC_ENT) */
/* #define  MY_THR1  TD(TD_LEADER_ENTER) */
/* #define  MY_THR1  TD(TD_ENTER_FUNCL) */
#define  MY_THR1  LEADER_ENTER
#define  MY_THR2  OSM(MOD_LSFT)
#define  MY_THR3  MO(_NUM)
#define  MY_THR4  RALT_T(KC_INS)

#define  MY_THUR1  KC_SPACE

// basic alpha keys {{{
#define  MY_TAB KC_BTN1
#define  MY_Q  KC_Q
#define  MY_W  KC_W
#define  MY_E  KC_E
#define  MY_R  KC_R
#define  MY_T  KC_T
#define  MY_Y  KC_Y
#define  MY_U  KC_U
#define  MY_I  KC_I
#define  MY_O  KC_O
#define  MY_P  KC_P
#define  MY_QUOT FI_QUOT

#define MY_ESC CTRLESC
#define MY_A  KC_A
#define MY_S  KC_S
#define MY_D  KC_D
#define MY_F  KC_F
#define MY_G  KC_G
#define MY_H  KC_H
#define MY_J  KC_J
#define MY_K  KC_K
#define MY_L  KC_L
#define MY_OE FI_ODIA
#define MY_AE LCTL_T(FI_ADIA)

#define  MY_LSFT  KC_LSFT
#define  MY_Z     KC_Z
#define  MY_X     KC_X
#define  MY_C     KC_C
#define  MY_V     KC_V
#define  MY_B     KC_B
#define  MY_N     KC_N
#define  MY_M     KC_M
#define  MY_COMM  KC_COMM
#define  MY_DOT   KC_DOT
/* #define  MY_DOT   TD(TD_SEEND_DOT) */
#define  MY_MINS  FI_MINS
#define  MY_RSFT  KC_RSFT
//}}}


#include "action_tapping.h"
void trigger_tapping(void);

// SEND_STRING shortcuts
#define SLEFT SS_TAP(X_LEFT)
