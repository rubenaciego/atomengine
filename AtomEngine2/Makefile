C_SOURCES = $(shell find . -name "*.c")
CPP_SOURCES = $(shell find . -name "*.cpp")
OBJ = ${C_SOURCES:.c=.o}
CPPOBJ = ${CPP_SOURCES:.cpp=.o}

CPPC = g++
CC = gcc
NAME = test
CPPFLAGS = -std=gnu++17 -O0 -Iinclude -Isrc -g -Wall
CFLAGS = -std=c11 -O0 -Iinclude -Isrc -g -Wall
LDFLAGS = -lSDL2 -lGL -lGLEW

all: bin/${NAME}

bin/${NAME}: ${OBJ} ${CPPOBJ}
	${CPPC} -o bin/${NAME} ${OBJ} ${CPPOBJ} ${LDFLAGS}

%.o: %.c
	${CC} ${CFLAGS} -o $@ -c $<

%.o: %.cpp
	${CPPC} ${CPPFLAGS} -o $@ -c $<

run: bin/${NAME}
	./bin/${NAME}

clean-obj:
	find . -name \*.o -type f -delete

clean: clean-obj
	rm bin/${NAME}
