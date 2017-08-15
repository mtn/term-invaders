CC = gcc
CXXFLAGS  = -Wall
FRAMEWORK = -framework sdl2

src = $(wildcard src/*.c)
lib = $(wildcard src/lib/*.h)
obj = $(src:.c=.o)

invader: $(obj) $(lib)
	$(CC) -o $@ $(obj) $(CXXFLAGS) $(FRAMEWORK)

.PHONY: clean
clean:
	rm -f $(obj) invader

