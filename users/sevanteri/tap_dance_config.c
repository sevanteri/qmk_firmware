#include "sevanteri.h"
#include "keymap_finnish.h"

#include "custom_tap_dances.h"
#include "leader.h"

qk_tap_dance_action_t tap_dance_actions[] = {
  /* [TD_HOME_END]     = ACTION_TAP_DANCE_DOUBLE(KC_HOME, KC_END), */
  /* [TD_PSCR_INS]     = ACTION_TAP_DANCE_DOUBLE(KC_PSCR, KC_INS), */

  /*
   * Custom tap dances below (/features/custom_tap_dances.h)
   */

  /* [TD_SEEND_DOT] = SENTENCE_END_TAP_DANCE(sentence_end_tap, sentence_end_fin, NULL, FI_DOT), */
  /* [TD_SEEND_QUES] = SENTENCE_END_TAP_DANCE(sentence_end_tap, sentence_end_fin, NULL, FI_QUES), */
  /* [TD_SEEND_EXLM] = SENTENCE_END_TAP_DANCE(sentence_end_tap, sentence_end_fin, NULL, FI_EXLM), */
    /* [TD_FUNC_HASH] = ACTION_TAP_DANCE_LAYER_TAP(_FUNC, FI_HASH), */
    /* [TD_LCTL_SLASH] = ACTION_TAP_DANCE_MOD_TAP(MOD_LCTL, FI_SLSH), */
    /* [TD_LGUI_RABK] = ACTION_TAP_DANCE_MOD_TAP(MOD_LGUI, FI_RABK), */
    /* [TD_ENTER_FUNCL] = ACTION_TAP_DANCE_LAYER_TAP(_FUNC, KC_ENTER), */
    /* [TD_LEADER_ENTER] = ACTION_TAP_DANCE_TAP_HOLD_RELEASE(KC_ENTER, start_leading, stop_leading), */
};
