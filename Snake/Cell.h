#pragma once
#include <SFML/Graphics.hpp>

class Cell : public sf::Drawable {
private:
	int xIndex, yIndex, cellSize;
	sf::Color color = sf::Color(0, 0, 0);
	sf::RectangleShape rect;

public:
	Cell() : Cell(0, 0, 15, sf::Color(0, 0, 0)) {}
	Cell(sf::Color color) : Cell(0, 0, 15, color) {}
	Cell(int cellSize, sf::Color color) : Cell(0, 0, cellSize, color) {}
	Cell(int xIndex, int yIndex, int cellSize, sf::Color color);
	Cell(int xPx, int yPx, int cellSize);

	void setColor(sf::Color color);
	void setPosition(int x, int y);

	sf::Color& getColor();

	int getX();
	int getY();

	sf::RectangleShape getRect();

	friend bool operator == (const Cell c1, const Cell c2);


	// Унаследовано через Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};