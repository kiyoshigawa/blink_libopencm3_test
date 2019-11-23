PROJECT = blink_libopencm3_test
BUILD_DIR = bin

SHARED_DIR = ./src
SHARED_DIR += ./lib

CFILES = blink.c
CFILES += timing.c
#AFILES += api-asm.S

#this will auto-generate an ld file for the chip
DEVICE=stm32f070f6

#this will allow upload to the chip using openOCD:
#this will only work if the BMP_PORT value below is not set.
#OOCD_INTERFACE=jlink
#OOCD_TARGET=stm32f0x
#if you specify an OOCD_FILE, it will override the OOCD_INTERFACE AND OCCD_TARGET defined above.
#OOCD_FILE=./stm32f4discovery.cfg

#this will allow upload to the chip using a blackmagic probe
#this takes priority over OOCD if BMP_PORT is defined
BMP_PORT=/dev/ttyS4
BMP_SCR=./bmp_load.scr

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