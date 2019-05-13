// Nordic layout for Ergodox infinity

#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_nordic.h"
#include "keymap_german.h"

// Layer names
#define BASE 0 // default layer
#define FUNCL 1 // function layer
#define NUMP 2 // numpad layer
#define MDIA 3 // media keys

enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE, // can always be here
    EPRM,
    VRSN,
    RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 *
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  ISO/  |   1  |   2  |   3  |   4  |   5  | NUMP |           | NUMP |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |  ¨^  |           |  Å   |   Y  |   U  |   I  |   O  |   P  |   '    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  ESC   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   Ö  |   Ä    |
 * |--------+------+------+------+------+------| DEL  |           | BSPC |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |  -   | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Ctrl |  ´`  |  §½  | RBTN | LBTN |                                       | RALT | PRSC | INS  |RCTRL | RGui |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | LEFT |RIGHT |       | PgUp |RCTRL |
 *                                 ,------+------+------|       |------+--------+------.
 *                                 |      |      | Home |       | PgDn |        |      |
 *                                 | LALT | LGUI |------|       |------|  Enter | Space|
 *                                 |      |      | End  |       |FUNCL |        |      |
 *                                 `--------------------'       `----------------------'
 */

[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_NUBS,  KC_1,    KC_2,   KC_3,    KC_4, KC_5, TG(NUMP),
        KC_TAB,   KC_Q,    KC_W,   KC_E,    KC_R, KC_T, KC_RBRC,
        KC_CAPS,  KC_A,    KC_S,   KC_D,    KC_F, KC_G,
        KC_LSFT,  KC_Z,    KC_X,   KC_C,    KC_V, KC_B, KC_DELT,
        KC_LCTRL, KC_BSLS, KC_GRV, KC_BTN2, KC_BTN1,

                                          /**/     KC_HOME, KC_END,
                                          /**/     /**/     MO(FUNCL),
                                          KC_LALT, KC_LGUI, KC_LCTRL,

        // right hand
        TG(NUMP), KC_6, KC_7,    KC_8,    KC_9,   KC_0,     KC_MINS,
        KC_LBRC,  KC_Y, KC_U,    KC_I,    KC_O,   KC_P,     KC_LBRC,
        /**/      KC_H, KC_J,    KC_K,    KC_L,   KC_SCLN,  KC_QUOT,
        KC_BSPC,  KC_N, KC_M,    KC_COMM, KC_DOT, KC_SLSH,  KC_RSFT,
        /**/      /**/  KC_RALT, KC_PSCR, KC_INS, KC_RCTRL, KC_RGUI,

        KC_PGUP,   KC_RCTRL,
        KC_PGDN,
        MO(FUNCL), KC_ENT, KC_BSPC
    ),

/* Keymap 1: Basic layer with functions
 *
 *
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F11 |           | F12  |  F6  |  F7  |  F8  |  F9  | F10  |  F11   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      | LEFT | DOWN |  UP  |RIGHT |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |       |     |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |BLTOG |       |      |      |
 *                                 ,------+------+------|       |------+--------+------.
 *                                 |      |      | BL+  |       |      |        |      |
 *                                 |      |      |------|       |------|        |      |
 *                                 |      |      | BL-  |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */

[FUNCL] = LAYOUT_ergodox(  // layer 1 : functions

  // left hand
  _______,  KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F11,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,

                                         /**/     _______, BL_TOGG,
                                         /**/     /**/     BL_INC,
                                         _______, _______, BL_DEC,

  // right hand
  KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  _______,
  _______, _______, _______, _______, _______,  _______, _______,
  /**/     KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______,
  _______, _______, _______, _______, _______,  _______, _______,
  /**/     /**/     _______, _______, _______,  _______, _______,

  _______, _______,
  _______,
  _______, _______, _______
),

/* Keymap 2: Numpad Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |NUMLCK|  P/  |  P*  |  P-  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |   7  |   8  |   9  |  P+  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |   4  |   5  |   6  |  P+  |        |
 * |--------+------+------+------+------+------|      |           | BSPC |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |   1  |   2  |   3  |Penter|        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |       |     |      |                                       |      |      |  P.  |Penter|      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|Enter |  P0  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// NUMPAD
[NUMP] = LAYOUT_ergodox(

// left hand
    _______,  KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F11,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,

                                             /**/     _______, _______,
                                             /**/     /**/     _______,
                                             _______, _______, _______,

// right hand
   _______, _______, KC_NLCK, KC_PSLS, KC_PAST, KC_PMSN, _______,
   _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, _______,
   /**/     _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______,
   KC_BSPC, _______, KC_P1,   KC_P2,   KC_P3,   KC_PENT, _______,
   /**/     /**/     _______, _______, KC_PDOT, KC_PENT, _______,

   _______, _______,
   _______,
   _______, KC_ENT,  KC_P0

),

/* Keymap 3: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | RESET  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | Lclk | MsUp | Rclk |      |      |           |      |      |VolDwn| Mute |VolUp |      |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | Btn4 |MsLeft|MsDown|MsRght| Btn5 |------|           |------|      | Prev | Stop | Play | Next |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |WhRght|WhDown| WhUp |WhLeft|WhClk |      |           |      |BwSrch|BwBack|BwHome|BwRefr|BwFwd |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |MsAcl0|MsAcl1|MsAcl2|                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |Brwser|Brwser|
 *                                 | Lclk | Rclk |------|       |------|Back  |Forwd |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
       RESET, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_TRNS,
       KC_TRNS, KC_TRNS, KC_BTN1, KC_MS_U, KC_BTN2, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_BTN4, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN5,
       KC_TRNS, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_BTN3, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_ACL0, KC_ACL1, KC_ACL2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_BTN1, KC_BTN2, KC_TRNS,
    // right hand
       KC_TRNS, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11,
       KC_TRNS, KC_TRNS, KC_VOLD, KC_MUTE, KC_VOLU, KC_TRNS, KC_F12,
                KC_TRNS, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, KC_TRNS,
       KC_TRNS, KC_WSCH, KC_WBAK, KC_WHOM, KC_WREF, KC_WFWD, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_WBAK, KC_WFWD
),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
        case 1:
        if (record->event.pressed) { // For resetting EEPROM
          eeconfig_init();
        }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    /* ergodox_right_led_3_off(); */
    switch (layer) {
        case FUNCL:
            ergodox_right_led_1_on();
            break;
        case NUMP:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }
};
