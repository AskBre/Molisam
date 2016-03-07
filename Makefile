CC=clang++ -std=c++11
OBJ=src/main.cpp src/MonomeSampler.cpp src/Sampler.cpp src/SamplerSample.cpp

SDIR=src
IDIR=include
ODIR=obj
LDIR=lib

DEPS=$(SDIR)/%.h $(IDIR)/%.h
LIBS=-lrtaudio -lmonome -pthread

CFLAGS=-I$(IDIR) -L$(LDIR) -ggdb3

$(ODIR)/%.o:$(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main:$(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

run:
	./main

clean:
	rm main
