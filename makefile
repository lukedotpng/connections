CC := gcc
CFLAGS := -g
LINKFLAGS := -lncurses -lcurl

OBJDIR := objs
BINDIR := bin
objects := main.o connections.o tcanvas.o http_request.o connections_json_parser.o

OS := $(shell uname)

build: $(objects) | ${BINDIR}
	${CC} ${CFLAGS} $(patsubst %,$(OBJDIR)/%,$^) -o ${BINDIR}/${OS}_build ${LINKFLAGS}

$(objects): %.o: src/%.c | $(OBJDIR)
	${CC} ${CFLAGS} -c $^ -o $(OBJDIR)/$@ ${LINKFLAGS}

$(OBJDIR):
	mkdir $@

${BINDIR}:
	mkdir $@

clean:
	rm -rf $(OBJDIR) ./bin/*