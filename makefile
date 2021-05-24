# minimalist makefile
# use together with run.mk or lib.mk
#
# github.com/toranova
# mailto:chia_jason96@live.com

# TODO: project name
PROJECT := hello-starter

# TODO: source directories
#SRC_DIR := src
SRC_DIR := examples/basic

# TODO: example cflags
CFLAGS += \
	-DHELLO \

# source file locations
SRC_C := $(wildcard  $(SRC_DIR)/*.c)

# TODO: include locations
INC := $(SRC_DIR)

# TODO: libraries to link
#LIBS := -lpam -lpam_misc -lm \
	#build/libhello.a
	#-Lbuild -lhello

# TODO: select a build method
# for executables (user run programs)
include run.mk
# for static libraries
#include static.mk
# for dynamic (shared) libraries
#include shared.mk
