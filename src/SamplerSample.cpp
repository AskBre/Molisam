#include "SamplerSample.h"

void SamplerSample::record(double *inBuffer) {
	if(getAmplitude(inBuffer) > threshold) {
		state = REC;
	} else {
		cout << "amp is " << getAmplitude(inBuffer) << endl;;
	}

	if(state == REC) {
		cout << "Recording track " << name << endl;
		if(rechead < bufferSize-bufferFrames) {
			for(unsigned i=0; i<bufferFrames*inChannels; i+=inChannels) {
				unsigned j = rechead + (i/inChannels);
				buffer[j] = inBuffer[i];
			}
			rechead += bufferFrames;
		} else {
			state = IDLE;
			rechead = 0;
			isRecorded = true;
		}
	}
}

void SamplerSample::play(double *outBuffer) {
	if(playhead < bufferSize-bufferFrames) {
		float fStop = positionInFrames + ((bufferSize-bufferFrames) / 8);
		if(playhead < fStop) {
			for(unsigned i=0; i<bufferFrames*outChannels; i+=outChannels) {
				unsigned j = playhead + (i/outChannels);
				unsigned pj = pPlayhead + (i/outChannels);
				for(unsigned c=0; c<outChannels; c++) {
					outBuffer[i+c] += buffer[j] * fadeVol;
					if(isFade) {
						fade();
					}
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
	pPlayhead = playhead;
}

void SamplerSample::fade() {
	float step = 0.001;

	if(isFadeDown) {
		if(fadeVol > 0) {
			fadeVol -= step;
		}
		else {
			isFadeDown = false;
		}
	} else {
		if(fadeVol < 1) {
			fadeVol += step;
		}
		else {
			isFadeDown = true;
			isFade = false;
		}
	}
}

double SamplerSample::getAmplitude(double *inBuffer) {

	double amp = 0;
	for(int i=0; i<bufferFrames; i++) {
		if(inBuffer[i] > amp) amp = inBuffer[i];
	}

	return amp;
}

