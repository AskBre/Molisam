#include "SamplerSample.h"

void SamplerSample::record(double *inBuffer) {
	if(rechead < bufferSize-bufferFrames) {
		for(unsigned i=0; i<bufferFrames*inChannels; i+=inChannels) {
			unsigned j = rechead + (i/inChannels);
//			for(unsigned c=0; c<inChannels; c++) {
//				if(c == index) {
					buffer[j] = inBuffer[i];
//				} else if (index > 3) {
//					buffer[j] += inBuffer[i] * 0.25;
//				}
//			}
		}
		rechead += bufferFrames;
	} else {
		state = IDLE;
		rechead = 0;
		isRecorded = true;
	}
}

void SamplerSample::play(double *outBuffer) {
	if(playhead < bufferSize-bufferFrames) {
		float fStop = positionInFrames + ((bufferSize-bufferFrames) / 4);
		if(playhead < fStop) {
			for(unsigned i=0; i<bufferFrames*outChannels; i+=outChannels) {
				unsigned j = playhead + (i/outChannels);
				for(unsigned c=0; c<outChannels; c++) {
					outBuffer[i+c] += buffer[j];
				}
			}
			playhead += bufferFrames;
		} else {
			if(!isRecorded) {
				state = STOP;
			} else {
				state = IDLE;
			}
			playhead = 0;
		}
	}
}
