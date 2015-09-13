#pragma once

#include <unistd.h>
#include <monome.h>
#include <vector>

#include "Sampler.h"

using namespace std;

struct buttons_t {
	vector<vector<bool>> isPressed;
};

class MonomeSampler {
	public:
		void setup();

		const unsigned sampleCount = 8;
		const unsigned sampleLength = 4;

	private:
		void openMonome();

		static void pressHandler(const monome_event_t *e, void *user_data);
		static void releaseHandler(const monome_event_t *e, void *user_data);

		monome_t *monome;
		Sampler sampler;

		buttons_t buttons;

};
