CC := gcc
OBJDIR := objs
objects := main.o connections.o tcanvas.o

build_linux: $(objects)
	${CC} -static $(patsubst %,$(OBJDIR)/%,$^) -o ./bin/linux_bin -lncurses -ltinfo

$(objects): %.o: src/%.c | $(OBJDIR)
	${CC} -c $^ -o $(OBJDIR)/$@ -lncurses -ltinfo

$(OBJDIR):
	mkdir $@

clean:
	rm -rf $(OBJDIR) ./bin/*