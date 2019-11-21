PROJECT = blink_libopencm3_test
BUILD_DIR = bin

SHARED_DIR = ./src
SHARED_DIR += ./lib

CFILES = blink.c
CFILES += timing.c
#AFILES += api-asm.S

#this will auto-generate an ld file for the chip
DEVICE=stm32f070f6
#this will allow upload to the chip using a blackmagic probe
BMP_PORT=/dev/ttyS4

#this sets the optimization of the code:
OPT = -Os

#set this to 0 for default, 1 for verbose, and to 99 for extremely verbose:
V = 0

# You shouldn't have to edit anything below here.
VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
OPENCM3_DIR=./libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ./rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk