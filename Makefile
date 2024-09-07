CC := gcc
CFLAGS = -g
LINKFLAGS := -lncurses -lcurl

BINDIR := bin
NCURSES_BUILD_DIR := external/ncurses-6.0/ncurses-link

all: ${BINDIR} build

build: 
	${CC} ${CFLAGS} ./src/*.c -o ${BINDIR}/connections ${LINKFLAGS}

${BINDIR}:
	mkdir $@

clean:
	rm -rf ./bin/* 