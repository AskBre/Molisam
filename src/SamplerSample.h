#pragma once

#include <iostream>
#include <string.h>

enum state_t {STOP, REC, PLAY};

using namespace std;

class SamplerSample {
	public:
		char name;
		state_t state = STOP;
		unsigned iteration = 0;

		double *buffer;
		unsigned bufferSize;
		unsigned sampleRate;
		unsigned bufferFrames;
		float sampleLengthInFrames;
		bool isRecorded = false;

		void record(double *inBuffer);
		void play(double *outBuffer);
		void stop();
};
