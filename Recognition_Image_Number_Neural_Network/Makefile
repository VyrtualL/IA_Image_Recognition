# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -std=c99 -fsanitize=address -g
LDFLAGS= -fsanitize=address
LDLIBS= -lm `pkg-config --libs sdl SDL_image`

SRC = main.c gen.c init.c ite.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: main

main: ${OBJ}

clean:
	${RM} *.o
	${RM} *.d

# END
