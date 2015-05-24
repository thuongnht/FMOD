#include "MySound.h"

class MyChannel 
{
	public:
		MyChannel() : sound(0), position(0) {}
		/*
			Like the channels in FMOD, we should be able to reuse a single channel object for 
			different sounds. Therefore, instead of taking a sound object in the constructor, we 
			only assign the sound object inside the Play() method. 
			This method also resets the position value
		*/
		void Play(MySound* mySound);
		//stop sound
		void Stop();
		/*
			This methos will be called from within the audio callback.
			This method takes two parameters, the array of PCM samples to write to and the
			size of this array.Notice that this method already expects the data array to be in
			the correct format, instead of the void* provided to the audio callback.The count
			also refers to the number of samples in the array, not the number of bytes
		*/
		void WriteSoundData(PCM16* data, int count);
		//pause?
		bool GetPaused() const { return paused; }
		void SetPaused(bool value) { paused = value; }
		//loop?
		bool GetLoop() const { return loop; }
		void SetLoop(bool value) { loop = value; }
		//change volume, floating point number between 0 (silence) and 1 (full volume)
		float GetVolume() const { return volume; }
		void SetVolume(float value);
		//change pitch
		//limit its value to the range between 0.25 (two octaves below the original sound) 
		//and 4 (two octaves above the original sound) :
		float GetPitch() const { return pitch; }
		void SetPitch(float value);
	private:
		MySound* sound;
		bool paused;
		bool loop;
		float volume;
		float position;
		float pitch;
};