CC = g++
CPPFLAGS := -Wall -Wextra -pedantic
SRC=diceware.cpp
BIN=diceware

$(BIN): $(SRC)
	$(CC) $(CPPFLAGS) $^ -o $@
clean:
	rm -f $(BIN)
