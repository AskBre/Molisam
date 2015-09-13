#include "SamplerSample.h"

void SamplerSample::record(double *inBuffer) {
	if(rechead < bufferSize-bufferFrames) {
		for(unsigned i=0; i<bufferFrames*2; i+=2) {
			unsigned j = rechead + (i/2);
			buffer[j] = inBuffer[i];
			buffer[j+1] = inBuffer[i+1];
		}
		rechead += bufferFrames;
	} else {
		state = STOP;
		rechead = 0;
		isRecorded = true;
	}

}

void SamplerSample::play(double *outBuffer) {
	if(playhead < bufferSize-bufferFrames) {
		for(unsigned i=0; i<bufferFrames*2; i+=2) {
			unsigned j = playhead + (i/2);
			outBuffer[i] += buffer[j] * 0.5;
			outBuffer[i+1] += buffer[j+1] * 0.5;
		}
		playhead += bufferFrames;
	} else {
		state = STOP;
		playhead = 0;
	}
}
