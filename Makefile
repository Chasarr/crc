SOURCES = crc.c
PROGRAM_NAME = crc
CFLAGS ?= -std=c2x -O2 -pedantic -Wextra -march=native
all: test

build:
	@gcc $(CFLAGS) $(SOURCES) -o $(PROGRAM_NAME) 
test: build
	@./$(PROGRAM_NAME)

clean:
	@rm $(PROGRAM_NAME)
	@echo "Removed crc binary file"

