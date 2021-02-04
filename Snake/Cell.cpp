#include "Cell.h"

Cell::Cell(int xIndex, int yIndex, int cellSize, sf::Color color) : xIndex(xIndex), yIndex(yIndex), cellSize(cellSize), color(color) {
	rect = sf::RectangleShape(sf::Vector2f(cellSize, cellSize));
	rect.setFillColor(color);
	rect.setPosition(xIndex * cellSize, yIndex * cellSize);
}

Cell::Cell(int xPx, int yPx, int cellSize) : cellSize(cellSize) {
	rect = sf::RectangleShape(sf::Vector2f(cellSize, cellSize));
	rect.setFillColor(color);
	rect.setPosition(xPx, yPx);
}

void Cell::setColor(sf::Color color) {
	Cell::color = color;
	Cell::rect.setFillColor(color);
}

void Cell::setPosition(int x, int y) {
	Cell::xIndex = x;
	Cell::yIndex = y;
	Cell::rect.setPosition(x * cellSize, y * cellSize);
}

sf::Color& Cell::getColor()
{
	return color;
}

int Cell::getX() {
	return xIndex;
}

int Cell::getY() {
	return yIndex;
}

sf::RectangleShape Cell::getRect() {
	return rect;
}

void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(rect, states);
}

bool operator == (const Cell c1, const Cell c2) {
	return c1.xIndex == c2.xIndex && c1.yIndex == c2.yIndex;
}