CFLAGS=-g
all: a trslt convtest texthdr

a: gst.o utf8.o utf8file.o
	ar rcs libpedit.a gst.o utf8.o

trslt: utf8.o utf8file.o
convtest: utf8.o utf8file.o

clean:
	rm -f *.o trslt utf8file convtest texthdr

install: a
	mkdir -pv ~/bin ~/lib ~/include
	cp trslt texthdr ~/bin
	cp libpedit.a ~/lib
	cp pedit.h ~/include