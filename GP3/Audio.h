#ifndef AUDIO_H
#define AUDIO_H

#include <SDL/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <string>

struct AudioClip
{
	std::string name;
	Mix_Chunk* m_clip;
	int channel;
};

class Audio
{
public:
	static std::vector<AudioClip*> m_clips;

	static void Init();
	static void LoadSound(std::string name, std::string filename);
	static void PlaySound(std::string name, bool loop);
	static void StopSound(std::string name);

private:
	Audio() {}
};

#endif