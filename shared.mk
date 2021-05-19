# run.mk
# minimalist makefile base for user-run programs (app)
# to use, add following line in your makefile
# include run.mk
#
# github.com/toranova
# mailto:chia_jason96@live.com

CFLAGS += -fPIC

include core.mk

# default target (all)
.PHONY: all
all: $(BIN_DIR)/$(PROJECT).so

# main target
$(BIN_DIR)/$(PROJECT).so: $(OBJ)
	@echo LINK $@
	@$(CC) -shared -o $@ $^ $(LIBS)
