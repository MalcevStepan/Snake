#pragma once
#include "Layout.h"
#include "Snake.h"
#include "GameMode.h"
#include "TextView.h"

class GameLayout : public Layout {
private:
	int cellSize, cellCountWidth, cellCountHeight, cellCount;
	Snake* snake;
	Cell* apple;
	sf::Font* font;
	TextView* counterText, * backText;
	Delegate<int>* randomizeApple, * stopGameAction;
	Delegate<int>* clickAction;
	sf::Color appleColor = sf::Color(255, 0, 0), * snakeColor;

	int NOD(int a, int b)
	{
		return b == 0 ? a : NOD(b, a % b);
	}

public:

	GameLayout(Delegate<int>* stopGameAction, int width, int height) : Layout(width, height) {
		cellSize = NOD(width, height);
		cellSize /= abs(36 - height / cellSize / 4) < abs(36 - height / cellSize / 8) ? 4 : abs(36 - height / cellSize / 8) < abs(36 - height / cellSize / 12) ? 8 : 12;
		cellCountWidth = width / cellSize;
		cellCountHeight = height / cellSize;
		cellCount = cellCountHeight * cellCountWidth;
		this->stopGameAction = stopGameAction;

		addView(getBackText());
		addView(getCounterText());
	}

	void setClickAction(Delegate<int>* clickAction);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setSnakeColor(sf::Color* color);
	sf::Color* getSnakeColor();

	Delegate<int>* getRandomizeAppleAction();

	TextView* getCounterText();
	TextView* getBackText();

	void deleteSnake() {
		if (snake)
			delete snake;
		snake = NULL;
	}

	sf::Font* getFont();
	void setFont(sf::Font* font);

	Snake* getSnake();

	Cell* getApple();
};