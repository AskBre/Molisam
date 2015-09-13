#pragma once

#include "RtAudio.h"
#include <iostream>
#include <string.h>
#include <algorithm>

#include "SamplerSample.h"

#define SAMPLE_RATE 48000
#define BUFFER_FRAMES 256
#define IN_CHANNELS 4
#define OUT_CHANNELS 2

using namespace std;

struct audioData_t {
	vector<SamplerSample> samples;
	double *inBuffer;
};

class Sampler {
	public:
		void setup();
		void openStream();
		void closeStream();

		void newSample(const char name, const float lengthInSec);

		void record(const char name);
		void play(const char name, const float positionInSec);


		bool isRecorded(const char &name);
		state_t getSampleState(const char &name);
		float getSamplePlayhead(const char &name);
		double getAmplitude();

		audioData_t audioData;

	private:
		int getSampleIndex(const char &name);


		RtAudio audio;
		RtAudio::StreamParameters iParams, oParams;
};

int recAndPlay(void *outputBuffer, void *inputBuffer,
		unsigned int nBufferFrames, double streamTime,
		RtAudioStreamStatus status, void *userData);
