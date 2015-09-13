#include "MonomeSampler.h"

void MonomeSampler::setup() {
	sampler.setup();

	for(int i=0; i<sampleCount; i++) {
		sampler.newSample(i,sampleLength);
	}

	sampler.openStream();

	buttons.isPressed.resize(8);
	for(unsigned i=0; i<buttons.isPressed.size(); i++) {
		buttons.isPressed[i].resize(8);
	}

	cout << "Size " << buttons.isPressed.size() << " " << buttons.isPressed[0].size() << endl;

	openMonome();

	monome_register_handler(monome, MONOME_BUTTON_DOWN, pressHandler, static_cast<void*> (&buttons));
	monome_register_handler(monome, MONOME_BUTTON_UP, releaseHandler, static_cast<void*> (&buttons));


	while(1) {
		if(monome_event_handle_next(monome)) {
			for(unsigned x=0; x<8; x++) {
				for(unsigned y=0; y<8; y++) {
					if(buttons.isPressed[x][y]) {
						monome_led_on(monome, x, y);
					} else {
						monome_led_off(monome, x, y);
					}
				}
			}
		}
	}
}

void MonomeSampler::openMonome() {
	if(!(monome = monome_open("/dev/ttyUSB0"))) {
		cerr << "No Monome found" << endl;
		exit(1);
	}

	monome_set_rotation(monome, MONOME_ROTATE_0);

	for(int y=0; y<8; y++) {
		for(int x=0; x<8; x++) {
			monome_led_on(monome, x, y);
			usleep(10000);
		}
	}

	for(int x=0; x<8; x++) {
		for(int y=0; y<8; y++) {
			monome_led_off(monome, x, y);
			usleep(10000);
		}
	}
}

void MonomeSampler::pressHandler(const monome_event_t *e, void *user_data) {
	buttons_t *buttons = static_cast<buttons_t*> (user_data);
	buttons->isPressed[e->grid.x][e->grid.y] = true;
}

void MonomeSampler::releaseHandler(const monome_event_t *e, void *user_data) {
	buttons_t *buttons = static_cast<buttons_t*> (user_data);
	buttons->isPressed[e->grid.x][e->grid.y] = false;
}
