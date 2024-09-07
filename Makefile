CC := gcc
CFLAGS = -g
LINKFLAGS := -lncurses -lcurl

BINDIR := bin

all: ${BINDIR} build

build: 
	${CC} ${CFLAGS} ./src/*.c -o ${BINDIR}/connections ${LINKFLAGS}

${BINDIR}:
	mkdir $@

clean:
	rm -rf ./bin/* 