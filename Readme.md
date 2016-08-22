# Molisam
Minimal live sampler for Monome, based on a mlrv-like user interface.

###Installation
Install [RTAudio](https://www.music.mcgill.ca/~gary/rtaudio/) and [libmonome](https://github.com/monome/libmonome) using your favourite package manager/compiler.

Clone this repo:  
  `$ git clone https://github.com/AskBre/Molisam`
  
In the directory, type:  
  `$ make`  
  `$ ./Molisam`
  
###Usage
As of now, it's not really written for anyone else than myself and my own use, so if you want to configure stuff, you need to dive in the code itself (mainly `Sampler.h`). The default audio backend is used, which will depend on what is running on your system. I personally recommend and have used jack, but in theory it should support ALSA, PulseAudio, CoreAudio and OSS too.

The six topmost rows are sample-banks, which can be recorded to using the six first buttons on the seventh row (first button is first row, and so on). When filled, button X correspond to position X/8 in the sample. The buttons on the eight row can be used to record button-presses. First press starts recording, second press stops recording, third starts playback, fourth stops playback. Reset if held for 2 seconds. I'll make a fancy diagram and video demo soon.
