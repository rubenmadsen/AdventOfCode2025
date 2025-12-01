CC = clang
CFLAGS = -std=c99 -Wall -Wextra -g -I$(LIB_INCLUDE)

SRC_DIR = src
BUILD_DIR = build
LIB_DIR = ../libs
LIB_INCLUDE = ../libs/include

SRC = \
	$(wildcard $(SRC_DIR)/*.c) \
	$(wildcard ../stdlib/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

# All .a files in ../../libs
LIBS = $(wildcard $(LIB_DIR)/*.a)

OUT = $(BUILD_DIR)/app

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(OUT)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: all
	./$(OUT)

clean:
	rm -rf $(BUILD_DIR)