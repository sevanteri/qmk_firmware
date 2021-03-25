#pragma once

#include QMK_KEYBOARD_H
#ifdef TAP_DANCE_ENABLE
// tap dances {{{
enum tapdance_buttons {
    TD_HOME_END = 0,
    TD_PSCR_INS,
    TD_HOME_END_MOD,
    TD_SEEND_DOT,
    TD_SEEND_QUES,
    TD_SEEND_EXLM,

    TD_FUNC_HASH,
    TD_LCTL_SLASH,
    TD_LGUI_RABK,

    TD_LEADER_ENTER,

    TD_ENTER_FUNCL,
};
#define HOMEND TD(TD_HOME_END)
#define PSCRINS TD(TD_PSCR_INS)
#define TD_HEMD TD(TD_HOME_END_MOD)
// }}}
#endif
