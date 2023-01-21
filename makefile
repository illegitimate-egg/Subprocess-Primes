MAKEFLAGS += --silent

CC=g++
CFLAGS = -g -lncurses -lpthread -I.

compile: 
	@echo "Compile from source."
	$(CC) main.cpp $(CFLAGS) -o linux-dynamic
	@echo "Done."

static-compile:
	@echo "Compile with static linking."
	$(CC) main.cpp $(CFLAGS) -ltinfo -I/usr/include/ncursesw --static -DNCURSES_STATIC -o linux-static
	@echo "Done."

windows:
	@echo "Compile for windows with static linking (forced for compaitibility). Note: It is likely that you will need to change your ncursesw directory for this to work with your install."
	$(CC) main.cpp $(CFLAGS) -ID:/msys64/mingw64/include/ncursesw -DNCURSES_STATIC --static -o windows-x86_64
	@echo "Done."

clean:
	rm -f linux-dynamic linux-static windows-x86_64
