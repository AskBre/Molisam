#pragma once

#include <iostream>
#include <string.h>

enum state_t {STOP, REC, PLAY, IDLE};

using namespace std;

class SamplerSample {
	public:
		char name;
		unsigned index;
		state_t state = STOP;
		unsigned rechead = 0;
		unsigned playhead = 0;
		unsigned pPlayhead = 0;

		bool isFade = false;
		bool isFadeDown = true;
		float fadeVol = 1;

		double *buffer;
		unsigned bufferSize;
		unsigned sampleRate;
		unsigned bufferFrames;
		unsigned inChannels;
		unsigned outChannels;
		float positionInFrames;
		bool isRecorded = false;

		void record(double *inBuffer);
		void play(double *outBuffer);
		void fade();
};
