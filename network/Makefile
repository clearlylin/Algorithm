
MAKE=make
SUBDIR=v1 test v2
CDIR=$(SUBDIR)

object=log.o readWrite.o sockwrap.o

sources = log.c readWrite.c sockwrap.c

all:$(object) $(SUBDIR)

$(SUBDIR):ECHO
	$(MAKE) -C $@

$(object):
	gcc -c $(sources)

ECHO:
	@echo $(SUBDIR)

REClean = @for subdir in $(SUBDIR); \
	do \
	echo "clean in $$subdir"; \
	$(MAKE) -C $$subdir clean; \
	done

clean:
	rm *.o
	$(REClean)