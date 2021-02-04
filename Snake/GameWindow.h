#pragma once
#include "GameMode.h"
#include <SFML/Graphics.hpp>
#include "MainMenuAdapter.h"
#include "GameLayout.h"
#include "SettingsLayout.h"
#include "MenuLayout.h"
#include "Delegate.h"
#include "GradientSelector.h"
#include "Settings.h"
#include <exception>
#include <fstream>

class GameWindow : sf::RenderWindow {
private:
	std::fstream stream;
	Settings* settings;
	GameMode mode = GameMode::PAUSE;
	MainMenuAdapter* mainAdapter;
	sf::Text* gameOverText, *anyKeyText;
	sf::Font* textFont;
	Delegate<int>* stopGameAction, *gameLayoutActions, *settingsLayoutActions, *menuLayoutActions;
	GameLayout* gameLayout;
	MenuLayout* menuLayout;
	SettingsLayout* settingsLayout;

	bool isMousePressed = false, isMouseMoved = false;

	int NOD(int a, int b)
	{
		return b == 0 ? a : NOD(b, a % b);
	}

	void checkActionEvent();
	void saveSettings();

public:
	GameWindow(int width, int height);
	~GameWindow();

	sf::Font* getFont();

	sf::Text* getGameOverText();
	sf::Text* getAnyKeyText();

	Delegate<int>* getStopGameAction();
	Delegate<int>* getGameLayoutActions();
	Delegate<int>* getSettingsLayoutActions();
	Delegate<int>* getMenuLayoutActions();

	Settings* getSettings();

	MainMenuAdapter* getMainAdapter();

	GameLayout* getGameLayout();
	SettingsLayout* getSettingsLayout();
	MenuLayout* getMenuLayout();

	int getWidth();
	int getHeight();

	void start();
};