#pragma once

#include <stdbool.h>

static bool caps_word_enabled = false;
void caps_word_enable(void) {
    caps_word_enabled = true;
    if (!host_keyboard_led_state().caps_lock) {
        tap_code(KC_CAPS);
    }
}

void caps_word_disable(void) {
    caps_word_enabled = false;
    if (host_keyboard_led_state().caps_lock) {
        tap_code(KC_CAPS);
    }
}

void caps_word_toggle(void) {
    if (caps_word_enabled) {
        caps_word_disable();
    } else {
        caps_word_enable();
    }
}

static void process_caps_word(uint16_t keycode, keyrecord_t *record) {
    if (caps_word_enabled) {
        // first strip of the mod taps and layer taps if needed
        switch (keycode) {
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
                if (record->tap.count == 0)
                    return;
                keycode = keycode & 0xFF;
        }
        // we end caps word on one of the following keypresses
        switch (keycode & 0xFF) {
            case KC_ESC:
            case KC_SPC:
            case KC_ENT:
            case KC_TAB:
            case KC_DOT:
            case KC_COMM:
                if (record->event.pressed) {
                    caps_word_disable();
                }
        }
    }
}


