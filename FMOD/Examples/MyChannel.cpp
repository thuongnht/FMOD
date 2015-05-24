#include <iostream>
#include <sstream>
#include <cstdint>
#include "MyChannel.h"

void MyChannel::Play(MySound* mySound) 
{
	sound = mySound;
	position = 0;
}

void MyChannel::Stop() 
{
	sound = 0;
}

void MyChannel::SetVolume(float value)
{
	if (value < 0.0f) volume = 0.0f;
	else if (value > 1.0f) volume = 1.0f;
	else volume = value;
}

void MyChannel::SetPitch(float value)
{
	if (value < 0.25f) pitch = 0.25f;
	else if (value > 4.0f) pitch = 4.0f;
	else pitch = value;
}

void MyChannel::WriteSoundData(PCM16* data, int count) 
{
	// If there is no sound assigned to the channel do nothing  
	if (sound == 0 || paused) return;
	// We need to write "count" samples to the "data" array
	// Since output is stereo it is easier to advance in pairs
	for (int i = 0; i < count; i += 2) 
	{
		// If we have reached the end of the sound, stop and return
		if (position >= sound->count) 
		{
			if (loop) { position = 0; }
			else 
			{
				Stop();
				return;
			}
		}
		// Read value from the sound data at the current position 
		//with volume
		PCM16 value = (PCM16)(sound->data[(int)position] * 1.0f);

		// Write value to both the left and right channels
		data[i] = value;
		data[i + 1] = value;

		// Advance the position by one sample, 
		//increment the position variable by the pitch amount.
		++position;
	}
}
