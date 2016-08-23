CC=clang++ -std=c++11
SRC=src/*.cpp

IDIR=/usr/include/rtaudio
LDIR=/usr/local/lib

DEPS=src/*.h $(IDIR)/*.h
LIBS=-lrtaudio -lmonome

CFLAGS=-I$(IDIR) -L$(LDIR)

all: Molisam

debug: CFLAGS+=-ggdb3 -Wall
debug: Molisam

Molisam:$(OBJ) $(DEPS)
	$(CC) -o $@ $(SRC) $(CFLAGS) $(LIBS)

run:
	./Molisam

clean:
	rm Molisam
