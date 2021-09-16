CC=clang++
CFLAGS=-std=c++17 -Werror -Wall -Wextra

TARGET=main
BIN=bin

OBJS=$(BIN)/main.o

$(BIN)/%.o: %.cpp
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
