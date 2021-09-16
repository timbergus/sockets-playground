CC=clang++
CFLAGS=-std=c++17 -Werror -Wall -Wextra

TARGET=main
BIN=bin
SRC=src

OBJS=$(BIN)/main.o

$(BIN)/%.o: $(SRC)/%.cpp
	@mkdir -p $(BIN)
	$(CC) $(CFLAGS) -c -MD $< -o $@

$(TARGET): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(BIN)/$(TARGET)

-include $(BIN)/*.d

start:
	$(BIN)/$(TARGET)

.PHONY: clean

clean:
	rm -r $(BIN)
