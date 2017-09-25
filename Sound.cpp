#include "Sound.h"

Sound::Sound()
{
	step = NULL;
	menu_select = NULL;
	menu_bgm = NULL;
	ingame_bgm = NULL;
	m_volume = 128;
	m_menu_volume = 128;
}

bool Sound::Init()
{
	//Initialize SDL_mixer
	if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{	
		return false;
	}
	return true;
}

bool Sound::Load()
{
	menu_bgm = Mix_LoadMUS("Sound/menu.mp3");
	ingame_bgm = Mix_LoadMUS("Sound/ingame.mp3");

	if ((menu_bgm == NULL) || (ingame_bgm == NULL))
	{
		return false;
	}

	step = Mix_LoadWAV("Sound/grass_run_04.wav");
	menu_select = Mix_LoadWAV("Sound/selection.wav");
	get_trapped = Mix_LoadWAV("Sound/trap1.wav");
	player_death = Mix_LoadWAV("Sound/trap2.wav");

	if ((step == NULL) || (menu_select == NULL) || (get_trapped == NULL) || (player_death == NULL))
	{
		return false;
	}
	return true;
}

void Sound::PlaySteps()
{
	Mix_PlayChannel(0, step, 0);
	Mix_Volume(0, m_volume * 0.15);
}

void Sound::PlayIngameMusic()
{
	Mix_PlayMusic(ingame_bgm, -1);
	Mix_VolumeMusic(m_volume * 0.6);
}

void Sound::PlayMenuMusic()
{
	Mix_PlayMusic(menu_bgm, -1);
	Mix_VolumeMusic(m_menu_volume);
}

void Sound::PlayTrappedSound()
{
	Mix_PlayChannel(2, get_trapped, 0);
	Mix_Volume(2, m_volume);
}

void Sound::PlayPlayerDieSound()
{
	Mix_PlayChannel(3, player_death, 0);
	Mix_Volume(3, m_volume * 0.8);
}

void Sound::StopMusic()
{
	Mix_HaltMusic();
}

void Sound::VolumeUp()
{
	if (m_volume < 128)
	{
		m_volume += 4;
		Mix_VolumeMusic(m_volume * 0.6);
		Mix_Volume(0, m_volume * 0.15);
		cout << m_volume << endl;
	}
}

void Sound::VolumeDown()
{
	if (m_volume > 0)
	{
		m_volume -= 4;
		Mix_VolumeMusic(m_volume * 0.6);
		Mix_Volume(0, m_volume * 0.15);
		cout << m_volume << endl;
	}
}

void Sound::MenuVolumeUp()
{
	if (m_menu_volume < 128)
	{
		m_menu_volume += 4;
		Mix_VolumeMusic(m_menu_volume);
		Mix_Volume(1, m_menu_volume * 0.25);
		cout << m_menu_volume << endl;
	}
}

void Sound::MenuVolumeDown()
{
	if (m_menu_volume > 0)
	{
		m_menu_volume -= 4;
		Mix_VolumeMusic(m_menu_volume);
		Mix_Volume(1, m_menu_volume * 0.25);
		cout << m_menu_volume << endl;
	}
}

void Sound::PlayMenuSelectSound()
{
	Mix_PlayChannel(1, menu_select, 0);
	Mix_Volume(1, m_menu_volume * 0.25);
}
