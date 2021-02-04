#pragma once
#include "Cell.h"
#include "Delegate.h"
#include <list>
#include <SFML/Graphics.hpp>

class Snake : public sf::Drawable {
private:
	std::list<Cell> snake;
	Cell cellToAdd;
	int speedX = 1, speedY = 0, prevSpeedX = 0, prevSpeedY = 0;
public:
	Snake() {}
	Snake(int x, int y, int cellSize, sf::Color* color);

	std::list<Cell> getCells();

	void move(int appleX, int appleY, int cellCountWidth, int cellCountHeight, Delegate<int>* randomizer, Delegate<int>* stopGameAction);

	int getSpeedX() { return speedX; }
	int getSpeedY() { return speedY; }

	int getPrevSpeedX() { return prevSpeedX; }
	int getPrevSpeedY() { return prevSpeedY; }

	void setSpeed(int speedX, int speedY) {
		this->speedX = speedX;
		this->speedY = speedY;
	}

	void setPrevSpeed(int speedX, int speedY) {
		prevSpeedX = speedX;
		prevSpeedY = speedY;
	}
	
	// Унаследовано через Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
