#include "MonomeSampler.h"
void MonomeSampler::setup() {
	sampler.setup();

	for(int i=0; i<sampleCount; i++) {
		sampler.newSample(i, sampleLength);
	}

	sampler.openStream();

	buttons.isPressed.resize(8);
	buttons.wasPressed.resize(8);
	buttons.isLight.resize(8);
	buttons.oldLights.resize(8);
	for(unsigned i=0; i<buttons.isPressed.size(); i++) {
		buttons.isPressed[i].resize(8);
		buttons.wasPressed[i].resize(6);
		buttons.isLight[i].resize(8);
		buttons.oldLights[i].resize(8);
	}

	buttonTracks.resize(8);

	openMonome();

	monome_register_handler(monome, MONOME_BUTTON_DOWN, pressHandler, static_cast<void*> (&buttons));
	monome_register_handler(monome, MONOME_BUTTON_UP, releaseHandler, static_cast<void*> (&buttons));

	while(1) {
		monome_event_handle_next(monome);

		updateLights();

		updateButtonRecord(); //<---------------- Probably too optimistic, should keep it on a timer somehow

//		if(monome_event_handle_next(monome)) {
			for(unsigned x=0; x<8; x++) {
				for(unsigned y=0; y<8; y++) {
					bool isPressed = buttons.isPressed[x][y];
					bool wasPressed = false;

					if(y<6) {
						for(auto &track : buttonTracks) {
							if(track.state == PLAY) {
								if(track.wasPressed[track.playhead][x][y]) {
									wasPressed = true;
									float p = ((float)sampleLength/8) * x;
									sampler.play(y, p);
								}
							}
						}
					}

					if(isPressed) {
						if(y<6) {
							float p = ((float)sampleLength/8) * x;
							sampler.play(y, p);
						} else if (y==6) {
							sampler.record(x);
						} else if (y==7) {
							if(!buttonTracks[x].isPressed) {
								switch(buttonTracks[x].state) {
									case STOP:
										buttonTracks[x].state = REC;
										buttonTracks[x].isPressed = true;
										break;
									case PLAY:
										buttonTracks[x].state = IDLE;
										buttonTracks[x].playhead = 0;
										buttonTracks[x].isPressed = true;
										break;
									case REC:
										buttonTracks[x].state = PLAY;
										buttonTracks[x].isPressed = true;
										break;
									case IDLE:
										buttonTracks[x].state = PLAY;
										buttonTracks[x].isPressed = true;
										break;
									default:
										break;
								}
							}
							buttonTracks[x].timeHeld++;
						}
					}

					// Delete buttontrack if held down
					if (y==7) {
						if(buttonTracks[x].timeHeld > 100) {
							cout << "DELETE" << endl;
							unsigned long tmpCounter = buttonTracks[x].timeHeld;
							buttonTracks[x] = buttonTrack_t();
							buttonTracks[x].isPressed = true;
						} else if (not isPressed) {
							buttonTracks[x].timeHeld = 0;
							buttonTracks[x].isPressed = false;
						}
					}
				}
			}
//		}
		usleep(10000);
		counter++;
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
			usleep(1000);
		}
	}

	for(int x=0; x<8; x++) {
		for(int y=0; y<8; y++) {
			monome_led_off(monome, x, y);
			usleep(10000);
		}
	}
}

void MonomeSampler::updateLights() {
	for(unsigned x=0; x<8; x++) {
		for(unsigned y=0; y<8; y++) {
			if(y < 6) {
				if(sampler.getSampleState(y) == PLAY) {
					float playhead = sampler.getSamplePlayhead(y);
					float p = (playhead/sampleLength)*sampleCount;
					float a = sampleLength * 0.01;

					for(unsigned _x=0; _x<8; _x++) {
						buttons.isLight[_x][y] = false;
					}

					// It doesn't really go up to 8, so needs a bit of help on the way
					if((p+a) < 8) buttons.isLight[p][y] = true;
				}
				else buttons.isLight[x][y] = false;
			}

			// Sample recording
			if(y==6) {
				switch(sampler.getSampleState(x)) {
					case STOP:
						buttons.isLight[x][y] = false;
						break;
					case REC:
						buttonBlink(x, y, recBlinkSpeed);
						break;
					case PLAY:
						break;
					case IDLE:
						buttons.isLight[x][y] = true;
						break;
					default:
						break;
				}
			}

			// Button recording
			if(y==7) {
				switch(buttonTracks[x].state) {
					case STOP:
						buttons.isLight[x][y] = false;
						break;
					case REC:
						buttonBlink(x, y, recBlinkSpeed);
						break;
					case PLAY:
						buttonBlink(x, y, playBlinkSpeed);
						break;
					case IDLE:
						buttons.isLight[x][y] = true;
						break;
					default:
						break;
				}
			}

			// Push the lights
			if(buttons.isLight[x][y] != buttons.oldLights[x][y]) {
				if(buttons.isLight[x][y]) monome_led_on(monome, x, y);
				else monome_led_off(monome, x, y);
			}

			buttons.oldLights[x][y] = buttons.isLight[x][y];
		}
	}
}

void MonomeSampler::buttonBlink(unsigned x, unsigned y, unsigned speed) {
	if(counter%speed == 0) {
		buttons.isLight[x][y] = true;
	}

	else if (counter%speed == speed/2) buttons.isLight[x][y] = false;
}

void MonomeSampler::updateButtonRecord() {
	for(auto &track : buttonTracks) {
		switch(track.state) {
			case STOP:
				break;
			case IDLE:
				break;
			case REC:
				// Only record rows 0-5
				track.wasPressed.push_back(buttons.isPressed);
				break;
			case PLAY:
				if(track.playhead < track.wasPressed.size()-1) {
					track.playhead++;
				} else {
					track.playhead = 0;
				}
				break;
			default:
				break;
		}
	}
}

//----------------------------------------------------------------
void MonomeSampler::pressHandler(const monome_event_t *e, void *user_data) {
	buttons_t *buttons = static_cast<buttons_t*> (user_data);
	buttons->isPressed[e->grid.x][e->grid.y] = true;
}

void MonomeSampler::releaseHandler(const monome_event_t *e, void *user_data) {
	buttons_t *buttons = static_cast<buttons_t*> (user_data);
	buttons->isPressed[e->grid.x][e->grid.y] = false;
}
