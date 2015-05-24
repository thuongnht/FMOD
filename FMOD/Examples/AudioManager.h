#include <string>
#include <time.h>
#include <map>
#include <fmod.hpp>
#include "Calling.h"

/*
	Controlling the small play-back system
*/
class AudioManager 
{
	public:
		AudioManager();
		~AudioManager();

		/*
			If a song is playing and we are fading in, increase the volume of the current 
			song a bit. Once the volume reaches one, stop fading.
			If a song is playing and we are fading out, decrease the volume of the current 
			song a bit. Once the volume reaches zero, stop the song, and stop fading.
			If no song is playing, and there is a song set up to play next, start playing it:
		*/
		void Update(float elapsed);

		/*
			The public methods LoadSFX() and LoadSong() delegate their work to the private 
			Load() method which does the actual loading process. The only difference is that the
			Load() method needs to use the correct sound map and mode from the arrays, based
			on the value of the first parameter:
		*/
		//load sound to sound effect
		void LoadSFX(const std::string& path);
		//load main sound
		void LoadSong(const std::string& path);

		//play sound effects with the changing volume, pitch, loop
		/*
			The method takes the path of the sound, and a pair of minimum and maximum volume and 
			pitch values. Then it searches for the sound in the correct map, and plays it back like 
			before, except that it sets the volume and pitch of the sound using random values 
			generated within the selected ranges	
		*/
		void PlaySFX(const std::string& path,
			float minVolume, float maxVolume,
			float minPitch, float maxPitch, int loopcount);
		//play main sound
		/*
			If we are trying to play a song that is already playing, nothing should happen.
			If we are trying to play a song, but another song is already playing, we 
			cannot start immediately. Instead, we instruct the manager to begin stopping 
			the current song, and store the path of the song to play afterwards.
			If no song is playing, we can start the new song immediately, with its initial 
			volume set to zero, and the manager set to the fade in state. The song must 
			also be added to the correct channel group:
		*/
		void PlaySong(const std::string& path);

		void StopSFXs();
		/*
			fade out if a song is playing, and clear any pending song 
			request that was previously set
		*/
		void StopSongs();
		//Pause sound/ soundeffect or all of sounds
		void PauseSFXs();
		void PauseSongs();
		void Pause();

		//effect the volume to all of sounds
		void SetMasterVolume(float volume);
		//change the volume of sound effect
		void SetSFXsVolume(float volume);
		//change the volume of main sound
		void SetSongsVolume(float volume);

	private:
		using SoundMap = std::map<std::string, FMOD::Sound*>;
		enum Category { CATEGORY_SFX, CATEGORY_SONG, CATEGORY_COUNT };

		void Load(Category type, const std::string& path);

		FMOD::System* system;
		FMOD::ChannelGroup* master;
		FMOD::ChannelGroup* groups[CATEGORY_COUNT];
		SoundMap sounds[CATEGORY_COUNT];
		FMOD_MODE modes[CATEGORY_COUNT];

		FMOD::Channel* currentSong;
		std::string currentSongPath;
		std::string nextSongPath;

		enum FadeState { FADE_NONE, FADE_IN, FADE_OUT };
		FadeState fade;
};

