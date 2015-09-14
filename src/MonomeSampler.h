#pragma once

#include <unistd.h>
#include <monome.h>
#include <vector>

#include "Sampler.h"

using namespace std;

struct buttonTrack_t {
	unsigned long isPressed;
	unsigned long counter = 0;
	state_t state = STOP;
	unsigned playhead = 0;
	vector<vector<vector<bool>>> wasPressed;
};

struct buttons_t {
	vector<vector<bool>> isPressed;
	vector<vector<bool>> wasPressed;
	vector<vector<bool>> isLight;
	vector<vector<bool>> oldLights;
};

class MonomeSampler {
	public:
		void setup();

		const unsigned sampleCount = 8;
		const unsigned sampleLength = 4;

	private:
		void openMonome();
		void updateLights();
		void buttonBlink(unsigned x, unsigned y, unsigned speed);
		void updateButtonRecord();

		static void pressHandler(const monome_event_t *e, void *user_data);
		static void releaseHandler(const monome_event_t *e, void *user_data);

		unsigned long counter;

		const unsigned recBlinkSpeed = 100;
		const unsigned playBlinkSpeed= 50;

		monome_t *monome;
		Sampler sampler;

		buttons_t buttons;

		vector<buttonTrack_t> buttonTracks;
};
