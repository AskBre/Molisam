#include "Sampler.h"
#include <monome.h>

struct button_t {
	unsigned x;
	unsigned y;
	bool pressed;
	bool led;
};

class MonomeSampler {
	public:
		void setup();
	private:
		Sampler sampler;

		vector<button_t> buttons;
};
