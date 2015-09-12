#pragma once

#include "RtAudio.h"
#include <iostream>
#include <string.h>
#include <algorithm>

#include "SamplerSample.h"

#define SAMPLE_RATE 48000
#define BUFFER_FRAMES 256

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
		void play(const char name, const float lengthInSec, const float positionInSec);

		bool isRecorded(const char &name);
		double getAmplitude();

	private:
		int getSampleIndex(const char &name);

		audioData_t audioData;

		RtAudio audio;
		RtAudio::StreamParameters iParams, oParams;
};

int recAndPlay(void *outputBuffer, void *inputBuffer,
		unsigned int nBufferFrames, double streamTime,
		RtAudioStreamStatus status, void *userData);
