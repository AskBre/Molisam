CC=clang++ -std=c++11
OBJ=src/main.cpp src/MonomeSampler.cpp src/Sampler.cpp src/SamplerSample.cpp

SDIR=src
IDIR=/usr/include/rtaudio
ODIR=obj
LDIR=/usr/local/lib

DEPS=$(SDIR)/%.h $(IDIR)/%.h
LIBS=-lrtaudio -lmonome

CFLAGS=-I$(IDIR) -L$(LDIR) -ggdb3

$(ODIR)/%.o:$(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main:$(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

run:
	./main

clean:
	rm main
