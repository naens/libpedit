CFLAGS=-g
all: clean a trslt texthdr lcs

a: gst.o utf8.o utf8file.o
	ar rcs libpedit.a gst.o utf8.o

trslt: utf8.o utf8file.o
lcs: utf8.o utf8file.o gst.o

clean:
	rm -f *.o trslt utf8file texthdr

install: a
	mkdir -pv ~/bin ~/lib ~/include
	cp trslt texthdr ~/bin
	cp libpedit.a ~/lib
	cp pedit.h ~/include
