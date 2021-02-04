#include "GameLayout.h"

void GameLayout::setFont(sf::Font* font)
{
	this->font = font;
}

void GameLayout::setSnakeColor(sf::Color* color)
{
	snakeColor = color;
}

sf::Color* GameLayout::getSnakeColor()
{
	if (!snakeColor)
		snakeColor = new sf::Color(255, 255, 255);
	return snakeColor;
}

Delegate<int>* GameLayout::getRandomizeAppleAction()
{
	if (!randomizeApple) {
		std::function<int(int)> fn = [&](int) {
			int x, y;
			bool isRandomized = false;
			while (!isRandomized) {
				x = rand() % (cellCountWidth - 1);
				y = rand() % (cellCountHeight - 1);
				bool isEqual = false;
				std::list<Cell> snakeCells = getSnake()->getCells();
				for (std::list<Cell>::iterator itr = snakeCells.begin(); itr != snakeCells.end(); itr++)
					if (itr->getX() == x && itr->getY() == y) {
						isEqual = true;
						break;
					}
				if (isRandomized = !isEqual)
					getApple()->setPosition(x, y);
			}
			return 0;
		};
		randomizeApple = new Delegate<int>(fn);
	}
	return randomizeApple;
}

TextView* GameLayout::getCounterText()
{
	if (!counterText) {
		counterText = new TextView("0", *getFont(), getWidth() / 20);
		counterText->setFillColor(sf::Color::Yellow);
		counterText->setStyle(sf::Text::Bold);
		sf::FloatRect bounds = counterText->getGlobalBounds();
		((sf::Text*)counterText)->setPosition(sf::Vector2f(bounds.width * 5, -bounds.height / 2));
	}
	return counterText;
}

TextView* GameLayout::getBackText()
{
	if (!backText) {
		backText = new TextView("<-", *getFont(), getWidth() / 20);
		backText->setFillColor(sf::Color::Yellow);
		backText->setStyle(sf::Text::Bold);
		sf::FloatRect bounds = backText->getGlobalBounds();
		((sf::Text*)backText)->setPosition(sf::Vector2f(bounds.width / 2, -bounds.height / 2));

		std::function<int(int)> fn = [=](int) {
			clickAction->invoke(0);
			return 0;
		};

		backText->setClickAction(new Delegate<int>(fn));
	}
	return backText;
}

void GameLayout::setClickAction(Delegate<int>* clickAction)
{
	this->clickAction = clickAction;
}

void GameLayout::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	GameLayout* game = const_cast<GameLayout*>(this);
	game->getCounterText()->setString(std::to_string(game->getSnake()->getCells().size() - 1));
	game->getSnake()->move(game->getApple()->getX(), game->getApple()->getY(), cellCountWidth, cellCountHeight, game->getRandomizeAppleAction(), stopGameAction);
	target.draw(*(game->getSnake()));
	target.draw(*(game->getApple()));
	target.draw(*((sf::Text*)game->getCounterText()));
	target.draw(*((sf::Text*)game->getBackText()));
}

sf::Font* GameLayout::getFont() {
	if (!font) {
		font = new sf::Font();
		font->loadFromFile("pixel_sans.ttf");
	}
	return font;
}

Snake* GameLayout::getSnake() {
	if (!snake)
		snake = new Snake(cellCountWidth / 2, cellCountHeight / 2, cellSize, getSnakeColor());
	return snake;
}

Cell* GameLayout::getApple() {
	if (!apple)
		apple = new Cell(cellSize, appleColor);
	return apple;
}
