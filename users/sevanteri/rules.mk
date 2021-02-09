SRC += sevanteri.c \
       casemodes.c

SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no


VPATH += keyboards/gboards/

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    SRC += tapdance.c
endif
ifeq ($(strip $(PIMORONI_TRACKBALL_ENABLE)), yes)
    SRC += pimoroni_trackball.c
    OPT_DEFS += -DPIMORONI_TRACKBALL_ENABLE
    POINTING_DEVICE_ENABLE := yes
endif
