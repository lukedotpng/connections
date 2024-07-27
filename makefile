CC := gcc
CFLAGS := -g
LINKFLAGS :=

OBJDIR := objs
BINDIR := bin
objects := main.o connections.o tcanvas.o

OS := $(shell uname)

ifeq ($(OS),Linux)
	CFLAGS += -static
	LINKFLAGS += -lncurses -ltinfo
else ifeq ($(shell uname),Darwin)
	OS = osx
	ifeq ($(NCURSESTATIC),)
		@echo $(error Please set NCURSESTATIC to path of libncurses.a file)
	else
		${NCURSESTATIC} = 
	endif
	CFLAGS += ${NCURSESTATIC} 
endif

build: $(objects) | ${BINDIR}
	${CC} ${CFLAGS} $(patsubst %,$(OBJDIR)/%,$^) -o ${BINDIR}/${OS}_build ${LINKFLAGS}

$(objects): %.o: src/%.c | $(OBJDIR)
	${CC} ${CFLAGS} -c $^ -o $(OBJDIR)/$@ -lncurses -ltinfo

$(OBJDIR):
	mkdir $@

${BINDIR}:
	mkdir $@

clean:
	rm -rf $(OBJDIR) ./bin/*