// Nordic layout for Ergodox infinity

#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_nordic.h"
#include "keymap_german.h"

// Layer names
#define BASE 0 // default layer
#define NUMP 2 // numpad layer
#define GAME 3 // gaming layer
#define FUNCL 15 // function layer

// keys
#define ESCCTRL LCTL_T(KC_ESC) // hold esc for ctrl
#define ENTLGUI LGUI_T(KC_ENT) // hold enter for super
#define SPCRSFT RSFT_T(KC_SPC) // hold space for shift
#define SPCLALT LALT_T(KC_SPC) // hold space for alt (left hand)
#define CTRLTAB LCTL(KC_TAB)
#define CSFTTAB LCTL(LSFT(KC_TAB))

enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE, // can always be here
    VRSN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
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
 *                                        | HOME | END  |       | PgUp |RCTRL |
 *                                 ,------+------+------|       |------+--------+------.
 *                                 | Space|  SPC |FUNCL |       | PgDn |  LGUI  | Shift|
 *                                 | LALT | LGUI |------|       |------|  Enter | Space|
 *                                 |      |      | LCTRL|       |FUNCL |        |      |
 *                                 `--------------------'       `----------------------'
 */

// layer 0 : default
[BASE] = LAYOUT_ergodox_pretty(

    KC_NUBS,  KC_1,   KC_2,   KC_3,    KC_4,    KC_5,    TG(NUMP),  /*****/ TG(NUMP),  KC_6,    KC_7,   KC_8,     KC_9,   KC_0,    KC_MINS,
    KC_TAB,   KC_Q,   KC_W,   KC_E,    KC_R,    KC_T,    KC_RBRC,   /*****/ KC_LBRC,   KC_Y,    KC_U,   KC_I,     KC_O,   KC_P,    KC_NUHS,
    ESCCTRL,  KC_A,   KC_S,   KC_D,    KC_F,    KC_G,    /**/       /*****/ /**/       KC_H,    KC_J,   KC_K,     KC_L,   KC_SCLN, KC_QUOT,
    KC_LSFT,  KC_Z,   KC_X,   KC_C,    KC_V,    KC_B,    KC_DELT,   /*****/ KC_BSPC,   KC_N,    KC_M,   KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
    KC_LCTRL, KC_EQL, KC_GRV, KC_BTN2, KC_BTN1, /**/     /**/       /*****/ KC_RALT,   KC_PSCR, KC_INS, KC_RCTRL, KC_RGUI,

    /**/      /**/    /**/    /**/     /**/     KC_HOME, KC_END,    /*****/ KC_PGUP,   KC_RCTRL,
    /**/      /**/    /**/    /**/     /**/     /**/     MO(FUNCL), /*****/ KC_PGDN,
    /**/      /**/    /**/    /**/     SPCLALT, KC_LGUI, KC_LCTRL,  /*****/ MO(FUNCL), ENTLGUI, SPCRSFT

),

/* Keymap 1: Basic layer with functions
 *
 *
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F11 |           | F12  |  F6  |  F7  |  F8  |  F9  | F10  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | PLAY |      |VOLUP |      | GAME |           |      |BRBAK | CTAB |CSTAB |BRFWD |      | AS_UP  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | PREV | STOP | NEXT |VOLDN |      |------|           |------| LEFT | DOWN |  UP  |RIGHT |      | AS_DN  |
 * |--------+------+------+------+------+------| BASE |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      | AS_RP  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |       |     |      |                                       |      |      |      |      | AS_T |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |BLTOG |       |      |      |
 *                                 ,------+------+------|       |------+--------+------.
 *                                 |      |      | BL+  |       |      |        |      |
 *                                 |      |      |------|       |------|        |      |
 *                                 |      |      | BL-  |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */

// layer 1 : functions
[FUNCL] = LAYOUT_ergodox_pretty(

    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,   /*****/ KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  _______,
    _______, _______, KC_MPLY, _______, KC_VOLU, _______, TG(GAME), /*****/ _______, KC_WBAK, CTRLTAB, CSFTTAB, KC_WFWD,  _______, KC_ASUP,
    _______, KC_MPRV, KC_MSTP, KC_MNXT, KC_VOLD, _______, /**/      /*****/ /**/     KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, KC_ASDN,
    _______, _______, _______, _______, _______, _______, TG(BASE), /*****/ _______, _______, _______, _______, _______,  _______, KC_ASRP,
    _______, _______, _______, _______, _______, /**/     /**/      /*****/ /**/     /**/     _______, _______, _______,  _______, KC_ASTG,

    /**/     /**/     /**/     /**/     /**/     _______, BL_TOGG,  /*****/ _______, _______,
    /**/     /**/     /**/     /**/     /**/     /**/     BL_INC,   /*****/ _______,
    /**/     /**/     /**/     /**/     _______, _______, BL_DEC,   /*****/ _______, _______, _______

),

/* Keymap 2: Numpad Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | RESET  |      |      |      |      |      |      |           |      |      |NUMLCK|  P/  |  P*  |  P-  | RESET  |
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
[NUMP] = LAYOUT_ergodox_pretty(

    RESET,   _______, _______, _______, _______, _______, _______, /*****/ _______, _______, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, RESET,
    _______, _______, _______, _______, _______, _______, _______, /*****/ _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, _______,
    _______, _______, _______, _______, _______, _______, /**/     /*****/ /**/     _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______,
    _______, _______, _______, _______, _______, _______, _______, /*****/ KC_BSPC, _______, KC_P1,   KC_P2,   KC_P3,   KC_PENT, _______,
    _______, _______, _______, _______, _______, /**/     /**/     /*****/ /**/     /**/     _______, _______, KC_PDOT, KC_PENT, _______,

    /**/     /**/     /**/     /**/     /**/     _______, _______, /*****/ _______, _______,
    /**/     /**/     /**/     /**/     /**/     /**/     _______, /*****/ _______,
    /**/     /**/     /**/     /**/     _______, _______, _______, /*****/ _______, KC_ENT,  KC_P0

),

/* Keymap 3: Gaming (no windows button)
 *
 *
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | ESC    |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LCTRL  |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |       |     |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------+------+------|       |------+--------+------.
 *                                 | Space| Space|      |       |      |        |      |
 *                                 |      |      |------|       |------|        |      |
 *                                 |      |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */

// gaming layer
[GAME] = LAYOUT_ergodox_pretty(

    KC_ESC,   _______, _______, _______, _______, _______, _______, /*****/ _______, _______, _______, _______, _______, _______, _______,
    _______,  _______, _______, _______, _______, _______, _______, /*****/ _______, _______, _______, _______, _______, _______, _______,
    KC_LCTRL, _______, _______, _______, _______, _______, /**/     /*****/ /**/     _______, _______, _______, _______, _______, _______,
    _______,  _______, _______, _______, _______, _______, _______, /*****/ _______, _______, _______, _______, _______, _______, _______,
    _______,  _______, _______, _______, _______, /**/     /**/     /*****/ /**/     /**/     _______, _______, _______, _______, _______,

    /**/      /**/     /**/     /**/     /**/     _______, _______, /*****/ _______, _______,
    /**/      /**/     /**/     /**/     /**/     /**/     _______, /*****/ _______,
    /**/      /**/     /**/     /**/     KC_SPC,  KC_SPC,  _______, /*****/ _______, _______, _______

)

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
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
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
    ergodox_right_led_3_off();
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

// custom tapping terms for keys
uint16_t get_tapping_term(uint16_t keycode) {
    switch (keycode) {
        case SPCRSFT:
        case ENTLGUI:
            return TAPPING_TERM + 350;
        default:
            return TAPPING_TERM;
    }
}
