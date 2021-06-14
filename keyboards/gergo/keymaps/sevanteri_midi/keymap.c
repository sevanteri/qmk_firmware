/* vim: set fdm=marker */
/* Good on you for modifying your layout! if you don't have
 * time to read the QMK docs, a list of keycodes can be found at
 *
 * https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
 *
 * There's also a template for adding new layers at the bottom of this file!
 */

#include QMK_KEYBOARD_H
#include "sevanteri.h"
#include "keymap_finnish.h"
#include "pointing_device.h"
#include "qmk_midi.h"
#include "process_midi.h"
#ifdef PIMORONI_TRACKBALL_ENABLE
#include "pimoroni_trackball.h"
# if defined(RAW_ENABLE)
# include "raw_hid.h"
# include "usb_descriptor.h"
# endif
#endif

enum gergo_layer {
    _NOTES,
    _CHANNELS,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer {{{ */
[_NOTES] = LAYOUT_gergo(
    MI_OCTU,  _______, MI_Cs,   MI_Ds,   _______, MI_Fs,   /**/     /**/     /**/ /**/     /**/     MI_Gs,   MI_As,   _______, MI_Cs_1, MI_Ds_1, _______,
    MI_OCTD,  MI_C,    MI_D,    MI_E,    MI_F,    MI_G,    XXXXXXX, /**/     /**/ /**/     XXXXXXX, MI_A,    MI_B,    MI_C_1,  MI_D_1,  MI_E_1,  MI_F_1,
    _______, _______, _______, _______, _______, MI_MOD, XXXXXXX, XXXXXXX, /**/ XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______,
    /******/  /******/ /******/ /******/ MI_BENDD, MI_BENDU, MI_SUS,  MI_PORT, /**/ MI_SOST, MI_SOFT, MI_LEG,  MO(_CHANNELS)
    )
// }}}
,[_CHANNELS] = LAYOUT_gergo(
    MI_TRNSU, MI_CH1,  MI_CH2,  MI_CH3,  MI_CH4,  MI_CH5,  /**/     /**/     /**/ /**/     /**/     MI_CH6,  MI_CH7,  MI_CH8,  MI_CH9,  MI_CH10, KC_TRNS,
    MI_TRNSD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, /**/     /**/ /**/     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, /**/ KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    /******/ /******/ /******/ /******/ _______, _______, _______, _______, /**/ _______, _______, _______, _______
    )
};

/* Keymap template {{{ */
/*
,[SYMB] = LAYOUT_gergo(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
//   }}}
 */

#ifdef PIMORONI_TRACKBALL_ENABLE
// {{{
#include "timer.h"
#include "quantum/quantum.h"

static int16_t mouse_auto_layer_timer = 0;
#define MOUSE_TIMEOUT 600
#define TRACKBALL_TIMEOUT 5

#define SIGN(x) ((x > 0) - (x < 0))
// user config EEPROM stuff {{{
typedef union {
  uint32_t raw;
  struct {
    uint8_t tb_brightness :8;
  };
} user_config_t;

user_config_t user_config;

void keyboard_post_init_user(void) {
  user_config.raw = eeconfig_read_user();
  tb_brightness = user_config.tb_brightness;
  trackball_set_brightness(tb_brightness);
}

void eeconfig_init_user(void) {
  user_config.raw = 0;
  user_config.tb_brightness = 32;
  eeconfig_update_user(user_config.raw);
}
// }}}

void matrix_init_user() {
    trackball_init();
}

void suspend_power_down_user(void) {
    trackball_set_brightness(0);
    /* trackball_sleep(); */
}

__attribute__((weak)) void pointing_device_init(void) { trackball_set_rgbw(0,0,0,tb_brightness); }

void update_member(int8_t* member, int16_t* offset) {//{{{
    if (*offset > 127) {
        *member = 127;
        *offset -= 127;
    } else if (*offset < -127) {
        *member = -127;
        *offset += 127;
    } else {
        *member = *offset;
        *offset = 0;
    }
}//}}}

static int16_t x_offset = 0;
static int16_t y_offset = 0;
static int16_t v_offset = 0;
static int16_t h_offset = 0;
static int16_t tb_timer = 0;
void pointing_device_task() {
    if (trackball_get_interrupt() && (!tb_timer || timer_elapsed(tb_timer) > TRACKBALL_TIMEOUT)) {
        tb_timer = timer_read() | 1;

        trackball_state_t state = trackball_get_state();

        __attribute__((unused))
        uint8_t mods = 0;
        if (state.x || state.y) {
            trigger_tapping();
            mods = get_mods();
        }

        if (state.button_triggered) {
            if(state.button_down) {
            } else {
            }
        } else {

            if (layer_state_is(_STUF)) {
                tb_brightness += state.y * 4;
                trackball_set_brightness(tb_brightness | 1);

            } else if (layer_state_is(_FUNC)) {
                h_offset += state.x;
                v_offset -= state.y;

            } else if (state.x || state.y) {

                if (!mouse_auto_layer_timer && !layer_state_is(_FUNC)) {
                    layer_on(_MOUS);
                }
                mouse_auto_layer_timer = timer_read() | 1;
                uint8_t scale = 3;
                if (mods & MOD_MASK_CTRL) scale = 2;
                x_offset += state.x * state.x * SIGN(state.x) * scale;
                y_offset += state.y * state.y * SIGN(state.y) * scale;

            }
        }

        /* xprintf("%d, %d, %d, %d, %d\n", */
        /*         s[0], s[1], */
        /*         s[2], s[3], */
        /*         s[4]); */

    }

    while (x_offset || y_offset || h_offset || v_offset) {
        /* update_member(&mouse.x, &x_offset); */
        /* update_member(&mouse.y, &y_offset); */

        midi_send_pitchbend(&midi_device, midi_config.channel, y_offset);

    }
}

void matrix_scan_user(void) {/*{{{*/
    if (mouse_auto_layer_timer && timer_elapsed(mouse_auto_layer_timer) > MOUSE_TIMEOUT) {
        report_mouse_t rep = pointing_device_get_report();
        if (rep.buttons) { return; }
        layer_off(_MOUS);
        mouse_auto_layer_timer = 0;
    }
}/*}}}*/

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {/*{{{*/
    if ((keycode < KC_BTN1 || keycode > KC_BTN5)
            && layer_state_is(_MOUS)
            && record->event.pressed) {
        layer_off(_MOUS);
        mouse_auto_layer_timer = 0;
    }
    return true;
}/*}}}*/

static uint8_t last_layer = _BASE;
layer_state_t layer_state_set_user(layer_state_t state) {/*{{{*/
    uint8_t layer = get_highest_layer(state);
    switch(layer) {
        case _FUNC:
            trackball_set_rgbw(0, tb_brightness, 0, 0);
            break;
        case _STUF:
            trackball_set_rgbw(tb_brightness, 0, tb_brightness, 0);
            break;
        case _MOUS:
            trackball_set_rgbw(0, tb_brightness, tb_brightness, 0);
            break;
        default:
            trackball_set_rgbw(0, 0, 0, tb_brightness);
            break;
    }

    // if layer *was* STUF, save eeprom
    if (
            last_layer == _STUF
            && last_layer != layer
            && tb_brightness != user_config.tb_brightness
       ) {
        user_config.tb_brightness = tb_brightness;
        eeconfig_update_user(user_config.raw);
    }

    last_layer = layer;
    return state;
}/*}}}*/

//}}}
#endif
