CC      ?= cc
CFLAGS  ?= -O2 -Wall -Wextra
BIN_DIR := bin
SRC_DIR := src

BINS := $(BIN_DIR)/cpu_job $(BIN_DIR)/io_job $(BIN_DIR)/burst

all: $(BINS)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/%: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean
