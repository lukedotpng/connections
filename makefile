CC := gcc
CFLAGS := -g -I${CURSES_BUILD_DIR}/include -L${CURSES_BUILD_DIR}/lib
LINKFLAGS := -lncurses -lcurl

BINDIR := bin
NCURSES_BUILD_DIR := external/ncurses-6.0/ncurses-link

build: ${BINDIR} ${CURSES_BUILD_DIR} install_ncurses
	${CC} ${CFLAGS} ./src/*.c -o ${BINDIR}/connections ${LINKFLAGS}

install_ncurses: configure_ncurses
	cd external/ncurses-6.0/ && make install

configure_ncurses:
	cd external/ncurses-6.0/ && ./configure --prefix=${PWD}/${NCURSES_BUILD_DIR}

${BINDIR}:
	mkdir $@

${NCURSES_BUILD_DIR}:
	mkdir $@

clean:
	rm -rf ./bin/* ./external/ncurses/