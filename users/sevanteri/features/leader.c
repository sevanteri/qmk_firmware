/* Copyright 2021 Andrew Rae ajrae.nv@gmail.com @andrewjrae
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

// https://github.com/andrewjrae/kyria-keymap/blob/master/leader.c

#include "leader.h"

#include <string.h>

#ifndef LEADER_ESC_KEY
#define LEADER_ESC_KEY KC_ESC
#endif

static bool leading = false;
static leader_func_t leader_func = NULL;

#ifdef LEADER_DISPLAY_STR

#ifndef LEADER_DISPLAY_LEN
#define LEADER_DISPLAY_LEN 19
#endif

static const char keycode_to_ascii_lut[58] = {0, 0, 0, 0, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 0, 0, 0, '\t', ' ', '-', '=', '[', ']', '\\', 0, ';', '\'', '`', ',', '.', '/'};

static uint8_t leader_display_size;
static const char space_ascii[] = "SPC";
static char leader_display[LEADER_DISPLAY_LEN + 1]; // add space for null terminator

static void update_leader_display(uint16_t keycode) {
    leader_display[leader_display_size] = ' ';
    ++leader_display_size;
    if (leader_display_size < LEADER_DISPLAY_LEN) {
        switch (keycode) {
            case KC_SPC:
                memcpy(leader_display + leader_display_size, space_ascii, sizeof(space_ascii));
                leader_display_size += sizeof(space_ascii);
                break;
            default:
                leader_display[leader_display_size] = keycode_to_ascii_lut[keycode];
                ++leader_display_size;
                break;
        }
        leader_display[leader_display_size] = '-';
    }
}

char *leader_display_str(void) {
    return leader_display;
}
#endif

// The entry point for leader sequenc functions
__attribute__ ((weak))
void *leader_start_func(uint16_t keycode, bool pressed) {
    return NULL;
}

// Check to see if we are leading
bool is_leading(void) {
    return leading;
}

// Hook to run custom code when leader mode starts
__attribute__ ((weak))
void leader_start(void) {}

// Hook to run custom code when leader mode ends
__attribute__ ((weak))
void leader_end(void) {}

// Start leader sequence
void start_leading(void) {
    leading = true;
    leader_func = leader_start_func;
    leader_start();
#ifdef LEADER_DISPLAY_STR
    memset(leader_display, 0, sizeof(leader_display));
    leader_display[0] = 'L';
    leader_display[1] = 'D';
    leader_display[2] = 'R';
    leader_display[3] = '-';
    leader_display_size = 3;
#endif
}
// Stop leader sequence
void stop_leading(void) {
    leading = false;
    leader_func = NULL;
    leader_end();
#ifdef LEADER_DISPLAY_STR
    leader_display[leader_display_size] = ' ';
#endif
}

// Process keycode for leader sequences
bool process_leader(uint16_t keycode, const keyrecord_t *record) {
    if (!leading || IS_MOD(keycode)) return true;
    const bool pressed = record->event.pressed;

    if (keycode > QK_MODS_MAX && pressed) {
        // special keys can go through on press
        return true;
    }

    /* if (!pressed) { */
        // Get the base keycode of a mod or layer tap key
        if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
            (keycode >= QK_LAYER_TAP && keycode < QK_LAYER_TAP_MAX)) {
                // Earlier return if this has not been considered tapped
                if (record->tap.count == 0)
                    return true;
                keycode = keycode & 0xFF;
        } else if (keycode > QK_MODS_MAX) {
            // early exit for other special key presses.
            return true;
        }
    /* } */
    // early exit if the esc key was hit
    if (keycode == LEADER_ESC_KEY) {
        stop_leading();
        return false;
    }

#ifdef LEADER_DISPLAY_STR
    update_leader_display(keycode);
#endif
    // update the leader function
    leader_func = (*leader_func)(keycode, pressed);
    if (leader_func == NULL) {
        stop_leading();
    }
    return false;
}
