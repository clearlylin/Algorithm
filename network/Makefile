
MAKE=make
SUBDIR=v1 test
CDIR=$(SUBDIR)

object=log.o readWrite.o tcpWrap.o

sources = log.c readWrite.c tcpWrap.c

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