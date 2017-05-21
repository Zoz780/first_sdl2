#pragma once
#include "VboDrawer.h"
#include <iostream>
#include <SOIL.h>

using namespace std;

enum class MenuState
{
	DEFAULT,
	START,
	LOADING,
	QUIT
};

class MainMenu
{
public:
	MainMenu();

	void Init();

	void Load();

	void Draw();

	void OnStartButton();
	void OnQuitButton();
	void LoadingScene();
	void DefaultState();

private:
	VboDrawer menu;
	VboDrawer loading_scene;
	VboDrawer marker;

	MenuState m_menu_state;

};

