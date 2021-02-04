#include "GameWindow.h"
#include <string>

GameWindow::GameWindow(int width = 640, int height = 480) : sf::RenderWindow(sf::VideoMode(width, height), "Snake", sf::Style::Titlebar | sf::Style::Close) {
	setFramerateLimit(getSettings()->getSpeed() * 100);
}

GameWindow::~GameWindow()
{
	delete mainAdapter, stopGameAction, menuLayoutActions, settingsLayoutActions, gameLayoutActions, gameLayout, menuLayout, settingsLayout;
}

int GameWindow::getWidth() {
	return getSize().x;
}

int GameWindow::getHeight() {
	return getSize().y;
}

Delegate<int>* GameWindow::getStopGameAction() {
	if (!stopGameAction) {
		std::function<int(int)> fn = [=](int) {
			mode = GameMode::STOP;
			getGameLayout()->deleteSnake();
			return 0;
		};
		stopGameAction = new Delegate<int>(fn);
	}
	return stopGameAction;
}

Delegate<int>* GameWindow::getGameLayoutActions()
{
	if (!gameLayoutActions) {
		std::function<int(int)> fn = [=](int x) {
			switch (x) {
			case 0:
				mode = GameMode::PAUSE;
				getGameLayout()->deleteSnake();
				break;
			}
			return 0;
		};
		gameLayoutActions = new Delegate<int>(fn);
	}
	return gameLayoutActions;
}

Delegate<int>* GameWindow::getSettingsLayoutActions()
{
	if (!settingsLayoutActions) {
		std::function<int(int)> fn = [=](int x) mutable {
			sf::Color color = getSettingsLayout()->getSnakeColor();
			switch (x) {
			case 0:
				mode = GameMode::PAUSE;
				getGameLayout()->deleteSnake();
				break;
			case 1:
				((GradientSelector*)getSettingsLayout()->getChildAt(1))->setSliderPos(getSettings()->getColor());
				((GradientSelector*)getSettingsLayout()->getChildAt(2))->setColor(4, getSettingsLayout()->getBrightnessColor(getSettings()->getColor()));
				break;
			case 2:
				((GradientSelector*)getSettingsLayout()->getChildAt(2))->setSliderPos(getSettings()->getBrightness());
				((GradientSelector*)getSettingsLayout()->getChildAt(1))->setColor(12, getSettingsLayout()->getGradientColor(getSettings()->getBrightness()));
				break;
			case 3:
				((GradientSelector*)getSettingsLayout()->getChildAt(3))->setSliderPos(getSettings()->getSpeed());
				break;
			}
			return 0;
		};
		settingsLayoutActions = new Delegate<int>(fn);
	}
	return settingsLayoutActions;
}

Delegate<int>* GameWindow::getMenuLayoutActions()
{
	if (!menuLayoutActions) {
		std::function<int(int)> fn = [=](int x) {
			switch (x) {
			case 0:
				mode = GameMode::START;
				getGameLayout()->deleteSnake();
				getGameLayout()->setSnakeColor(&getSettingsLayout()->getSnakeColor());
				setFramerateLimit(getSettings()->getSpeed() * 100);
				break;
			case 1:
				mode = GameMode::SETTINGS;
				setFramerateLimit(60);
				break;
			}
			return 0;
		};
		menuLayoutActions = new Delegate<int>(fn);
	}
	return menuLayoutActions;
}

void GameWindow::saveSettings() {
	std::fstream stream;
	try {
		stream.open("settings.txt", std::ios_base::in | std::ios_base::out | std::ios_base::trunc);
		stream << *getSettings();
		stream.close();
	}
	catch (std::exception& e) {
		std::cout << e.what();
	}
}

Settings* GameWindow::getSettings()
{
	if (!settings) {
		settings = new Settings();
		std::fstream stream;
		try {
			stream.open("settings.txt", std::ios_base::in | std::ios_base::out);
			stream >> *settings;
			stream.close();
		}
		catch (std::exception& e) {
			std::cout << e.what();
		}
	}
	return settings;
}

void GameWindow::checkActionEvent() {
	sf::Event event;
	while (pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			saveSettings();
			close();
		}

		if (event.type == sf::Event::MouseButtonPressed)
			isMousePressed = true;
		if (event.type == sf::Event::MouseMoved)
			isMouseMoved = true;

		if (event.type == sf::Event::KeyPressed) {

			if (mode == GameMode::START) {
				Snake* snake = getGameLayout()->getSnake();
				snake->setPrevSpeed(snake->getSpeedX(), snake->getSpeedY());
				if (event.key.code == sf::Keyboard::Up && snake->getSpeedY() != 1)
					snake->setSpeed(0, -1);
				else if (event.key.code == sf::Keyboard::Down && snake->getSpeedY() != -1)
					snake->setSpeed(0, 1);
				else if (event.key.code == sf::Keyboard::Left && snake->getSpeedX() != 1)
					snake->setSpeed(-1, 0);
				else if (event.key.code == sf::Keyboard::Right && snake->getSpeedX() != -1)
					snake->setSpeed(1, 0);
				else if (event.key.code == sf::Keyboard::Escape)
					mode = GameMode::PAUSE;
			}
			else if (mode == GameMode::STOP)
				mode = GameMode::PAUSE;
			else if (mode == GameMode::SETTINGS && event.key.code == sf::Keyboard::Escape)
				mode == GameMode::PAUSE;

		}
		else if (event.type == sf::Event::MouseButtonReleased) {
			isMousePressed = false;
			int x = event.mouseButton.x, y = event.mouseButton.y;
			if (mode == GameMode::PAUSE)
				for (int i = 0; i < getMenuLayout()->getAdapter()->getItemCount(); i++) {
					TextView* view = (TextView*)getMenuLayout()->getAdapter()->getItems()[i];
					sf::FloatRect rect = view->getGlobalBounds();
					if (x >= rect.left && x <= rect.left + rect.width && y >= rect.top && y <= rect.top + rect.height)
						view->onClick();
				}
			else if (mode == GameMode::SETTINGS) {
				const TextView* view = (TextView*)getSettingsLayout()->getChildAt(0);
				sf::FloatRect rect = view->getGlobalBounds();
				if (x >= rect.left && x <= rect.left + rect.width && y >= rect.top && y <= rect.top + rect.height)
					getSettingsLayout()->getChildAt(0)->onClick();
			}
			else if (mode == GameMode::START) {
				const TextView* view = (TextView*)getGameLayout()->getChildAt(0);
				sf::FloatRect rect = view->getGlobalBounds();
				if (x >= rect.left && x <= rect.left + rect.width && y >= rect.top && y <= rect.top + rect.height)
					getGameLayout()->getChildAt(0)->onClick();
			}
		}
		else if ((event.type == sf::Event::MouseMoved && isMousePressed) || isMousePressed && mode == GameMode::SETTINGS) {
			int x = isMouseMoved ? event.mouseMove.x : event.mouseButton.x, y = isMouseMoved ? event.mouseMove.y : event.mouseButton.y;
			for (int i = 1; i < 4; i++) {
				GradientSelector* selector = (GradientSelector*)getSettingsLayout()->getChildAt(i);
				if (x >= selector->getX() && x <= selector->getX() + selector->getWidth() && y >= selector->getY() && y <= selector->getY() + selector->getHeight()) {
					float pos = (float)((x - selector->getX()) / (float)selector->getWidth());
					if (i == 1) getSettings()->setColor(pos);
					if (i == 2) getSettings()->setBrightness(pos);
					if (i == 3) getSettings()->setSpeed(pos);
					selector->onClick();
				}
			}
		}

		isMouseMoved = false;
	}
}

sf::Font* GameWindow::getFont() {
	if (!textFont) {
		textFont = new sf::Font();
		textFont->loadFromFile("pixel_sans.ttf");
	}
	return textFont;
}

sf::Text* GameWindow::getGameOverText() {
	if (!gameOverText) {
		gameOverText = new sf::Text("Game Over", *getFont(), getWidth() / 10);
		gameOverText->setFillColor(sf::Color::Red);
		gameOverText->setStyle(sf::Text::Bold);
		sf::FloatRect bounds = gameOverText->getGlobalBounds();
		gameOverText->setPosition(sf::Vector2f(getWidth() / 2 - bounds.width / 2, getHeight() / 2 - bounds.height * 2));
	}
	return gameOverText;
}

sf::Text* GameWindow::getAnyKeyText() {
	if (!anyKeyText) {
		anyKeyText = new sf::Text("Press any key to continue", *getFont(), getWidth() / 15);
		anyKeyText->setFillColor(sf::Color::White);
		anyKeyText->setStyle(sf::Text::Bold);
		sf::FloatRect bounds = anyKeyText->getGlobalBounds();
		anyKeyText->setPosition(sf::Vector2f(getWidth() / 2 - bounds.width / 2, getHeight() / 2));
	}
	return anyKeyText;
}

MainMenuAdapter* GameWindow::getMainAdapter() {
	if (!mainAdapter)
		mainAdapter = new MainMenuAdapter(getWidth() / 20, getFont());
	return mainAdapter;
}

GameLayout* GameWindow::getGameLayout()
{
	if (!gameLayout) {
		gameLayout = new GameLayout(getStopGameAction(), getWidth(), getHeight());
		gameLayout->setFont(getFont());
		gameLayout->setClickAction(getGameLayoutActions());
		gameLayout->setPosition(0, 0);
	}
	return gameLayout;
}

SettingsLayout* GameWindow::getSettingsLayout()
{
	if (!settingsLayout) {
		settingsLayout = new SettingsLayout(getSettings(), getWidth(), getHeight(), getSettingsLayoutActions());
		settingsLayout->setFont(getFont());
		settingsLayout->setPosition(0, 0);
	}
	return settingsLayout;
}

MenuLayout* GameWindow::getMenuLayout()
{
	if (!menuLayout) {
		menuLayout = new MenuLayout(getWidth(), getHeight());
		menuLayout->setClickAction(getMenuLayoutActions());
		menuLayout->setAdapter(getMainAdapter());
		menuLayout->setPosition(0, 0);
	}
	return menuLayout;
}

void GameWindow::start() {
	getGameLayout()->getRandomizeAppleAction()->invoke(NULL);

	while (isOpen()) {
		checkActionEvent();

		switch (mode) {
		case GameMode::START:
			getGameLayout()->draw(*this, sf::RenderStates::Default);
			break;
		case GameMode::PAUSE:
			getMenuLayout()->draw(*this, sf::RenderStates::Default);
			break;
		case GameMode::STOP:
			draw(*getGameOverText());
			draw(*getAnyKeyText());
			break;
		case GameMode::SETTINGS:
			getSettingsLayout()->draw(*this, sf::RenderStates::Default);
			break;
		}
		display();
		clear();
	}
}