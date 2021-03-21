#include QMK_KEYBOARD_H
#include "sendstring_finnish.h"

// Only random utils here now.
// Configurations moved to their respective files.


void trigger_tapping(void) {
    action_tapping_process((keyrecord_t){});
}
