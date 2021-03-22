SRC += sevanteri.c \
       process_record.c \
       combo_config.c \
       features/casemodes.c \
       features/leader.c \
       tapping_config.c \
       casemodes_config.c \
       leader_config.c

VPATH += keyboards/gboards/ \
         users/sevanteri/features/

SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no


ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    SRC += tapdance.c
endif
ifeq ($(strip $(PIMORONI_TRACKBALL_ENABLE)), yes)
    SRC += features/pimoroni_trackball.c
    OPT_DEFS += -DPIMORONI_TRACKBALL_ENABLE
    POINTING_DEVICE_ENABLE := yes
endif
