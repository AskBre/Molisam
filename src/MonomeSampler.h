#pragma once

#include <unistd.h>
#include <monome.h>
#include <vector>

#include "Sampler.h"

using namespace std;

struct buttons_t {
	bool isNew;
	vector< vector<bool>> isPressed;
	vector< vector<bool>> isLight;
};

class MonomeSampler {
	public:
		void setup();

		const unsigned sampleCount = 8;
		const unsigned sampleLength = 4;

		buttons_t buttons;
	private:
		void openMonome();
		static void pressHandler(const monome_event_t *e, void *user_data);
		static void releaseHandler(const monome_event_t *e, void *user_data);

		void setLight(unsigned x, unsigned y);

		monome_t *monome;
		Sampler sampler;

		vector<monome_event_t> eventList;

};
