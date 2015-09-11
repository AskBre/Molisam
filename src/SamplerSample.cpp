#include "SamplerSample.h"

void SamplerSample::record(double *inBuffer) {
	if(iteration < bufferSize-bufferFrames) {
		for(unsigned i=0; i<bufferFrames*2; i+=2) {
			unsigned j = iteration + (i/2);
			buffer[j] = inBuffer[i];
			buffer[j+1] = inBuffer[i+1];
		}
		iteration += bufferFrames;
	} else {
		state = STOP;
		iteration = 0;
		isRecorded = true;
	}

}

void SamplerSample::play(double *outBuffer) {
	if(iteration < sampleLengthInFrames-bufferFrames) {
		for(unsigned i=0; i<bufferFrames*2; i+=2) {
			unsigned j = iteration + (i/2);
			outBuffer[i] += buffer[j] * 0.5;
			outBuffer[i+1] += buffer[j+1] * 0.5;
		}
		iteration += bufferFrames;
	} else {
		state = STOP;
		iteration = 0;
	}
}
