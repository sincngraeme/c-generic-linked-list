CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic
STD := c23
LFLAGS :=
SRC_DIRS := src
BUILD_DIR := build
PROGRAM := ll_test

OUT := $(BUILD_DIR)/$(PROGRAM)
SRC := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
OBJ := $(foreach file,$(SRC:.c=.o),$(BUILD_DIR)/obj/$(file))
OBJ_DIRS := $(foreach dir,$(SRC_DIRS),$(BUILD_DIR)/obj/$(dir))

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(LFLAGS) $(OBJ) -o $(OUT)

$(BUILD_DIR)/obj/%.o: %.c | $(BUILD_DIR) $(OBJ_DIRS)
	$(CC) $(CFLAGS) -std=$(STD) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ_DIRS):
	mkdir -p $(OBJ_DIRS)

.PHONY: clean log run
clean: 
	rm $(OUT) $(OBJ)

log:
	@echo $(OBJ)

run:
	make && $(OUT)
