CC := gcc
CFLAGS := -g
LINKFLAGS := -lncurses -lcurl

BINDIR := bin
SRCDIR := src
src_files := main.c connections.c tcanvas.c http_request.c connections_json_parser.c

build: ${BINDIR}
	${CC} ${CFLAGS} $(patsubst %,$(SRCDIR)/%,${src_files}) -o ${BINDIR}/connections ${LINKFLAGS}

${BINDIR}:
	mkdir $@

clean:
	rm -rf ./bin/*