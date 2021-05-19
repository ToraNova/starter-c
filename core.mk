# core.mk
# main makefile with the core functionalities
# does not include the main build target (see run.mk or lib.mk)
#
# github.com/toranova
# mailto:chia_jason96@live.com

PROJECT ?= starterc.example
.DEFAULT_GOAL := all

# libraries to link
CFLAGS += -Wall

# directories
BIN_DIR ?= build

# expand filenames
OBJ += $(addprefix $(BIN_DIR)/obj/, $(SRC_C:.c=.o))

# expand includes
CFLAGS += $(addprefix -I,$(INC))

# map to sysutils (pls change if on windows)
RM := rm
MKDIR := mkdir

# compiler defines
CC ?= gcc
CXX ?= g++
AR ?= ar

# make obj directories
OBJ_DIRS = $(sort $(dir $(OBJ)))
$(OBJ): | $(OBJ_DIRS)
$(OBJ_DIRS):
	@$(MKDIR) -p $@

# compile object codes
$(BIN_DIR)/obj/%.o: %.c
	@echo CC $(notdir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<

# clean target
.PHONY: clean
clean:
	@$(RM) -rf $(BIN_DIR)

# print make variables (debugging)
.PHONY: pmv
pmv:
	@echo INC $(INC)
	@echo SRC $(SRC_C)
	@echo OBJS $(OBJ)
	@echo CFLAGS $(CFLAGS)
	@echo LDFLAGS $(LIBS)
