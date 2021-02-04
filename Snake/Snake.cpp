#include "Snake.h"

Snake::Snake(int x, int y, int cellSize, sf::Color* color) {
	cellToAdd = Cell(x, y, cellSize, *color);
	snake.push_back(cellToAdd);
}

std::list<Cell> Snake::getCells() {
	return snake;
}

void Snake::move(int appleX, int appleY, int cellCountWidth, int cellCountHeight, Delegate<int>* randomizer, Delegate<int>* stopGameAction) {
	std::list<Cell>::iterator head = snake.begin();
	int x = head->getX(), y = head->getY(), nextX = x + speedX, nextY = y + speedY;
	for (std::list<Cell>::iterator itr = (++snake.begin()); itr != snake.end(); itr++)
		if ((*head) == *itr) {
			stopGameAction->invoke(NULL);
			return;
		}
	cellToAdd.setPosition(nextX < 0 ? cellCountWidth : nextX > cellCountWidth - 1 ? 0 : nextX, nextY < 0 ? cellCountHeight : nextY > cellCountHeight - 1 ? 0 : nextY);
	snake.push_front(cellToAdd);
	nextX = cellToAdd.getX();
	nextY = cellToAdd.getY();
	if (nextX != appleX || nextY != appleY)
		snake.pop_back();
	else if (snake.size() == cellCountHeight * cellCountWidth)
		stopGameAction->invoke(NULL);
	else
		randomizer->invoke(NULL);
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (std::list<Cell>::const_iterator itr = snake.begin(); itr != snake.end(); itr++)
		target.draw(*itr, states);
}
