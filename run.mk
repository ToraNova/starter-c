# run.mk
# minimalist makefile base for user-run programs (app)
# to use, add following line in your makefile
# include run.mk
#
# github.com/toranova
# mailto:chia_jason96@live.com

include core.mk

# default target (all)
.PHONY: all
all: $(BIN_DIR)/$(PROJECT)

# main target
$(BIN_DIR)/$(PROJECT): $(OBJ)
	@echo LINK $@
	@$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
