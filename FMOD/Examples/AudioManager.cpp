#include <SFML/Window.hpp>
#include "AudioManager.h"
#include <iostream>
#include <sstream>
#include <cstdint>

AudioManager::AudioManager() : currentSong(0), fade(FADE_NONE) 
{
	// Initialize system
	FMOD::System_Create(&system);
	system->init(100, FMOD_INIT_NORMAL, 0);
	// Create channels groups for each category
	system->getMasterChannelGroup(&master);
	for (int i = 0; i < CATEGORY_COUNT; ++i) 
	{
		system->createChannelGroup(0, &groups[i]);
		master->addGroup(groups[i]);
	}
	// Set up modes for each category
	modes[CATEGORY_SFX] = FMOD_DEFAULT | FMOD_LOOP_NORMAL;
	modes[CATEGORY_SONG] = FMOD_DEFAULT | FMOD_CREATESTREAM |
		FMOD_LOOP_NORMAL;
	// Seed random number generator for SFXs
	srand(time(0));
}

AudioManager::~AudioManager() 
{
	// Release sounds in each category
	SoundMap::iterator iter;
	for (int i = 0; i < CATEGORY_COUNT; ++i) 
	{
		for (iter = sounds[i].begin(); iter != sounds[i].end(); ++iter)
			iter->second->release();
		sounds[i].clear();
	}
	// Release system
	system->release();
}

void AudioManager::LoadSFX(const std::string& path) 
{
	Load(CATEGORY_SFX, path);
}

void AudioManager::LoadSong(const std::string& path) 
{
	Load(CATEGORY_SONG, path);
}

void AudioManager::Load(Category type, const std::string& path) 
{
	if (sounds[type].find(path) != sounds[type].end()) return;
	FMOD::Sound* sound;
	system->createSound(path.c_str(), modes[type], 0, &sound);
	sounds[type].insert(std::make_pair(path, sound));
}

void AudioManager::PlaySFX(const std::string& path,
	float minVolume, float maxVolume,
	float minPitch, float maxPitch, int loopcount) 
{
	// Try to find sound effect and return if not found
	SoundMap::iterator sound = sounds[CATEGORY_SFX].find(path);
	if (sound == sounds[CATEGORY_SFX].end()) return;
	// Calculate random volume and pitch in selected range
	float volume = RandomBetween(minVolume, maxVolume);
	float pitch = RandomBetween(minPitch, maxPitch);
	// Play the sound effect with these initial values
	FMOD::Channel* channel;
	system->playSound(FMOD_CHANNEL_FREE, sound->second,true, &channel);
	channel->setChannelGroup(groups[CATEGORY_SFX]);
	
	//set new volume
	//DO SOME CODEs HERE

	//set new pitch to frequency based on changeOctave or ChangeSemitone
	float frequency;
	//DO SOME CODEs HERE
	
	//set pause = false
	channel->setPaused(false);
	
	//set loopcount
	//DO SOME CODEs HERE
}

void AudioManager::PauseSFXs() 
{
	bool paused;
	groups[CATEGORY_SFX]->getPaused(&paused);
	groups[CATEGORY_SFX]->setPaused(!paused);
}

void AudioManager::StopSFXs() 
{
	groups[CATEGORY_SFX]->stop();
}

void AudioManager::PlaySong(const std::string& path) 
{
	// Ignore if this song is already playing
	if (currentSongPath == path) return;
	// If a song is playing stop them and set this as the next song
	if (currentSong != 0) 
	{
		StopSongs();
		nextSongPath = path;
		return;
	}
	// Find the song in the corresponding sound map
	SoundMap::iterator sound = sounds[CATEGORY_SONG].find(path);
	if (sound == sounds[CATEGORY_SONG].end()) return;
	// Start playing song with volume set to 0 and fade in
	currentSongPath = path;
	//system->playSound(FMOD_CHANNEL_FREE,sound->second, true, &currentSong);
	
	currentSong->setChannelGroup(groups[CATEGORY_SONG]);
	
	currentSong->setVolume(0.0f);
	currentSong->setPaused(false);
	fade = FADE_IN;
}

void AudioManager::PauseSongs() 
{
	bool paused;
	if (currentSong != 0)
	{
		currentSong->getPaused(&paused);
		currentSong->setPaused(!paused);;
	}		
}

void AudioManager::Pause()
{
	bool paused;
	master->getPaused(&paused);
	master->setPaused(!paused);;
}

void AudioManager::StopSongs() 
{
	if (currentSong != 0)
		fade = FADE_OUT;
	nextSongPath.clear();
}

void AudioManager::Update(float elapsed) 
{
	const float fadeTime = 1.0f; // in seconds
	if (currentSong != 0 && fade == FADE_IN) 
	{
		float volume;
		currentSong->getVolume(&volume);
		float nextVolume = volume + elapsed / fadeTime;
		if (nextVolume >= 1.0f) 
		{
			currentSong->setVolume(1.0f);
			fade = FADE_NONE;
		}
		else 
		{
			currentSong->setVolume(nextVolume);
		}
	}
	else if (currentSong != 0 && fade == FADE_OUT) 
	{
		float volume;
		currentSong->getVolume(&volume);
		float nextVolume = volume - elapsed / fadeTime;
		if (nextVolume <= 0.0f) 
		{
			currentSong->stop();
			currentSong = 0;
			currentSongPath.clear();
			fade = FADE_NONE;
		}
		else 
		{
			currentSong->setVolume(nextVolume);
		}
	}
	else if (currentSong == 0 && !nextSongPath.empty()) 
	{
		PlaySong(nextSongPath);
		nextSongPath.clear();
	}
	system->update();
}

void AudioManager::SetMasterVolume(float volume) 
{
	master->setVolume(volume);
}
void AudioManager::SetSFXsVolume(float volume) 
{
	groups[CATEGORY_SFX]->setVolume(volume);
}
void AudioManager::SetSongsVolume(float volume) 
{
	groups[CATEGORY_SONG]->setVolume(volume);
}



int main() 
{
	// start window and clock
	sf::Window window;
	window.create(sf::VideoMode(50, 50), "Simple Play-back System");
	sf::Clock clock;

	// Place your initialization logic here
	AudioManager audio;

	//Load Sound datas to SFX, Sound categories
	//DO SOME CODEs HERE
	// Start the game loop
	while (window.isOpen()) 
	{
		// Only run approx 60 times per second
		float elapsed = clock.getElapsedTime().asSeconds();
		if (elapsed < 1.0f / 60.0f) continue;
		clock.restart();

		//start the event listener
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
		// Place your update and draw logic here
		audio.Update(elapsed);
	}
	// Place your shutdown logic here
	return 0;
}
