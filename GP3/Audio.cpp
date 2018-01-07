#include "Audio.h"

std::vector<AudioClip*> Audio::m_clips;

void Audio::Init()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
	}
}

void Audio::LoadSound(std::string name, std::string filename)
{
	AudioClip* clip = new AudioClip();
	clip->m_clip = Mix_LoadWAV(filename.c_str());
	clip->name = name;

	Audio::m_clips.push_back(clip);
}

void Audio::PlaySound(std::string name, bool loop)
{
	for (auto clip : m_clips)
	{
		if (clip->name == name)
		{
			clip->channel = Mix_PlayChannel(-1, clip->m_clip, loop ? -1 : 0);
			return;
		}
	}
	std::cout << "could not find audio clip called " << name << std::endl;
}

void Audio::StopSound(std::string name)
{
	for (auto clip : m_clips)
	{
		if (clip->name == name)
		{
			Mix_HaltChannel(clip->channel);
			return;
		}
	}
	std::cout << "could not find audio clip called " << name << std::endl;
}