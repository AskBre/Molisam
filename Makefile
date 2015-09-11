CC=clang++ -std=c++11
OBJ=src/main.cpp src/Sampler.cpp src/SamplerSample.cpp

SDIR=src
IDIR=include
ODIR=obj
LDIR=lib

DEPS=$(SDIR)/%.h $(IDIR)/%.h
LIBS=-lrtaudio -lmonome

CFLAGS=-I$(IDIR) -L$(LDIR) -g

$(ODIR)/%.o:$(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main:$(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

run:
	./main
