CC=gcc
CFLAGS=-Wall -lMLV -lm -O1
SRC_DIR=src
INCLUDE_DIR=include
BIN_DIR=bin

SRC_FILES=$(wildcard $(SRC_DIR)/*.c)
OBJ_FILES=$(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRC_FILES))
EXECUTABLE=$(BIN_DIR)/towerdefense


all: $(EXECUTABLE)


$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^


$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@


clean:
	rm -f $(BIN_DIR)/*.o $(EXECUTABLE)
