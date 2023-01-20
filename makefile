MAKEFLAGS += --silent

CC=g++
CFLAGS = -g -lncurses -lpthread -I.

compile: 
	@echo "Compile from source."
	$(CC) main.cpp $(CFLAGS) -o main

run: compile
	@echo "Running main"
	./main

clean:
	rm main
