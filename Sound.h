#pragma once
#include <SDL2/SDL_mixer.h>
#include <fstream>
#include <iostream>

using namespace std;
class Sound
{
public:
	Sound();

	bool Init();

	bool Load();

	void PlayMenuMusic();

	void PlayIngameMusic();

	void StopMusic();

	void PlaySteps();

	void VolumeUp();

	void VolumeDown();

	void MenuVolumeUp();

	void MenuVolumeDown();

	void PlayMenuSelectSound();

private:

	int m_volume;
	int m_menu_volume;

	Mix_Music *menu_bgm;
	Mix_Music *ingame_bgm;

	Mix_Chunk *step;
	Mix_Chunk *menu_select;
};

