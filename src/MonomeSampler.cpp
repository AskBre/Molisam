#include "Sampler.h"

void setup() {
	sampler.setup();

	for(int i=0; i<4; i++) {
		sampler.newSample(i,4);
	}

	sampler.openStream();
}
