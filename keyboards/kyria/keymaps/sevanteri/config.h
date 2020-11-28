/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

#pragma once

#define EE_HANDS

#ifdef OLED_DRIVER_ENABLE
  #define OLED_DISPLAY_128X64
#endif

#define PI 3.14159265358979323846
/* #define TRACKBALL_ANGLE_OFFSET PI/2 */
#define TRACKBALL_ORIENTATION 3

#ifdef RGBLIGHT_ENABLE
  /* #define RGBLIGHT_ANIMATIONS */
  /* #define TRACKBALL_NO_MATH */
  /* #define RGBLIGHT_MODE_BREATHING */
  #define RGBLIGHT_EFFECT_STATIC_GRADIENT
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_DISABLE_KEYCODES
#endif

#define F_SCL 240000UL  // SCL frequency
#include "sevanteri_config.h"

// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
/* #define SPLIT_USB_DETECT */
/* #define NO_USB_STARTUP_CHECK */

/* #define COMBO_NO_TIMER */

// basic alpha keys {{{
#define POS_Q KPOS(0, 6)
#define POS_W KPOS(0, 5)
#define POS_E KPOS(0, 4)
#define POS_R KPOS(0, 3)
#define POS_T KPOS(0, 2)

#define POS_Y KPOS(4, 2)
#define POS_U KPOS(4, 3)
#define POS_I KPOS(4, 4)
#define POS_O KPOS(4, 5)
#define POS_P KPOS(4, 6)

#define POS_A  KPOS(1, 6)
#define POS_S  KPOS(1, 5)
#define POS_D  KPOS(1, 4)
#define POS_F  KPOS(1, 3)
#define POS_G  KPOS(1, 2)

#define POS_H  KPOS(5, 2)
#define POS_J  KPOS(5, 3)
#define POS_K  KPOS(5, 4)
#define POS_L  KPOS(5, 5)
#define POS_OE KPOS(5, 6)
#define POS_AE KPOS(4, 7)

#define  POS_Z     KPOS(2, 6)
#define  POS_X     KPOS(2, 5)
#define  POS_C     KPOS(2, 4)
#define  POS_V     KPOS(2, 3)
#define  POS_B     KPOS(2, 2)

#define  POS_N     KPOS(6, 2)
#define  POS_M     KPOS(6, 3)
#define  POS_COMM  KPOS(6, 4)
#define  POS_DOT   KPOS(6, 5)
#define  POS_MINS  KPOS(6, 6)

// left thumb keys (no ignore_mod_tap_interrupt)
#define  POS_THL1  KPOS(3,0)
#define  POS_THL2  KPOS(3,1)
#define  POS_THL3  KPOS(3,2)
#define  POS_THL4  KPOS(3,3)

// right thumb keys
#define  POS_THR1  KPOS(7, 0)
#define  POS_THR2  KPOS(7, 1)
#define  POS_THR3  KPOS(7, 2)
#define  POS_THR4  KPOS(7, 3)

