#include "SamplerSample.h"

void SamplerSample::record(double *inBuffer) {
	if(rechead < bufferSize-bufferFrames) {
		for(unsigned i=0; i<bufferFrames*inChannels; i+=inChannels) {
			unsigned j = rechead + (i/inChannels);
			for(unsigned c=0; c<inChannels; c++) {
				if(c == index) {
					buffer[j] += inBuffer[i+c];
					cout << "Recording index " << index << " on channel " << c << endl;
				} else if (index > 3) {
					buffer[j] += inBuffer[i+c] * 0.25;
				}
			}
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
		for(unsigned i=0; i<bufferFrames*outChannels; i+=outChannels) {
			unsigned j = playhead + (i/outChannels);
			for(unsigned c=0; c<outChannels; c++) {
				outBuffer[i+c] += buffer[j] * 0.5;
			}
		}
		playhead += bufferFrames;
	} else {
		state = STOP;
		playhead = 0;
	}
}
