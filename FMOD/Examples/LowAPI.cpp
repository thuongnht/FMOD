#include "fmod.hpp"
#include <SFML/Window.hpp>
#include "MyChannel.h"

MyChannel channel;

FMOD_RESULT F_CALLBACK WriteSoundData(FMOD_SOUND *sound, void *data, unsigned int length) {
	// Clear output
	memset(data, 0, length);
	// Get data in the correct format and calculate sample count
	PCM16* pcmData = (PCM16*)data;
	int pcmDataCount = length/2;

	// Tell the channel to write to the stream data

	//DO SOMETHING HERE

	return FMOD_OK;
}

int main()
{
	//start window and clock
	sf::Window window;
	window.create(sf::VideoMode(200, 200), "Simple");
	sf::Clock clock;

	//start system pointer
	FMOD::System* system;
	FMOD::System_Create(&system);
	system->init(100, FMOD_INIT_NORMAL, 0);

	//start sound pointer for the sound data

	//DO SOME CODEs HERE


	// Create and initialize a sound info structure
	FMOD_CREATESOUNDEXINFO info;
	memset(&info, 0, sizeof(FMOD_CREATESOUNDEXINFO));
	info.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
	// Size of the entire sound in bytes. Since the sound will be
	// looping, it does not need to be too long. In this example
	// we will be using the equivalent of a 5 seconds sound.
	// i.e. sampleRate * channels * bytesPerSample * durationInSeconds
	info.length = 44100 * 2 * sizeof(signed short) * 5;
	// Specify sampling rate, format, and number of channels to use
	// In this case, 44100 Hz, signed 16-bit PCM, Stereo
	info.defaultfrequency = 44100;
	info.format = FMOD_SOUND_FORMAT_PCM16;
	info.numchannels = 2;
	// Number of samples we will be submitting at a time
	// A smaller value results in less latency between operations
	// but if it is too small we get problems in the sound
	// In this case we will aim for a latency of 100ms
	// i.e. sampleRate * durationInSeconds = 44100 * 0.1 = 4410
	info.decodebuffersize = 4410;
	// Specify the callback function that will provide the audio data
	info.pcmreadcallback = WriteSoundData;
	// Create a looping stream with FMOD_OPENUSER and the info we filled 
	FMOD::Sound* sound1;
	FMOD_MODE mode = FMOD_LOOP_NORMAL | FMOD_OPENUSER;
	system->createStream(0, mode, &info, &sound1);

	// Start the game loop
	while (window.isOpen())
	{
		// Only run approx 60 times per second
		float elapsed = clock.getElapsedTime().asSeconds();
		if (elapsed < 1.0f / 60.0f) continue;
		clock.restart();
		// start the event listener on the window
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Handle window events
			if (event.type == sf::Event::Closed)
			window.close();
			// Handle user input
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
					case sf::Keyboard::Q:
					{
						//e.g for playing
						
						//DO SOME CODEs HERE

						break;
					}
					case sf::Keyboard::W:
					{
						//DO SOME CODEs HERE

						break;
					}
					case sf::Keyboard::E:
					{
						//DO SOME CODEs HERE

						break;
					}
					case sf::Keyboard::R:
					{
						//DO SOME CODEs HERE

						break;
					}
					case sf::Keyboard::T:
					{
						//DO SOME CODEs HERE

						break;
					}
					case sf::Keyboard::Y:
					{
						//DO SOME CODEs HERE

						break;
					}
				}
			}
		}
	}

	return 0;
}