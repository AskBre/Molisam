CC=clang++ -std=c++11
OBJ=src/main.cpp src/MonomeSampler.cpp src/Sampler.cpp src/SamplerSample.cpp

SDIR=src
IDIR=/usr/include/rtaudio
ODIR=obj
LDIR=/usr/local/lib

DEPS=$(SDIR)/%.h $(IDIR)/%.h
LIBS=-lrtaudio -lmonome

CFLAGS=-I$(IDIR) -L$(LDIR)

all: Molisam

debug: CFLAGS+=-ggdb3 -Wall
debug: Molisam

$(ODIR)/%.o:$(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Molisam:$(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

run:
	./Molisam

clean:
	rm main
