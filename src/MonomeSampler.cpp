#include "Sampler.h"

void setup() {
	const unsigned sampleNum = 8;
	const unsigned sampleLengths = 4;
	sampler.setup();

	for(int i=0; i<sampleNum; i++) {
		sampler.newSample(i,sampleLengths);
	}

	sampler.openStream();
}

void buttonPressed(unsigned x, unsigned y) {
}
