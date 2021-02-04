#include "GradientSelector.h"

GradientSelector::GradientSelector(int x = 0, int y = 0, float sliderPos = 0.5f, int width = 0, int height = 0, int colorsCount = 1) : View(width, height)
{
	View::setPosition(x, y);
	this->sliderPos = sliderPos;
	this->colorsCount = colorsCount;
	isVertical = height > width;
	rectangle = new sf::Vertex[colorsCount];
	sliderSize = width > height ? height : width;
	slider = new sf::RectangleShape(sf::Vector2f(sliderSize, sliderSize));
	slider->setFillColor(sf::Color::Transparent);
	slider->setOutlineColor(sf::Color::White);
	slider->setOutlineThickness(sliderSize / 5);
}

GradientSelector::~GradientSelector()
{
	delete rectangle, slider;
}

void GradientSelector::setColor(int colorsCount, sf::Color* colors) {
	if (colorsCount >= 4 && colorsCount % 4 == 0) {
		int a = colorsCount / 4, vertexCount = 4;
		for (int i = 0; i < a; i++)
			for (int k = 0; k < vertexCount; k++)
				rectangle[i * vertexCount + k] = sf::Vertex(sf::Vector2f(getX() + (isVertical ? getWidth() * (k % 4 > 1 ? 1 : 0) : (getWidth() / a) * (i + (k % 3 == 0 ? 0 : 1))), getY() + (isVertical ? getHeight() / a * (i + (k % 3 == 0 ? 0 : 1)) / a : getHeight() * (k % 4 > 1 ? 1 : 0))), colors[i * vertexCount + k]);
	}
	else throw(WrongParameterException("Wrong  for all vertices(colorsCount < 4 or colorsCount % 4 != 0)"));
}

void GradientSelector::setSliderPos(float pos) {
	sliderPos = pos;
}

void GradientSelector::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	int x = getX(), y = getY(), height = getHeight(), width = getWidth();
	slider->setPosition(x, y);
	target.draw(*slider, states);
	slider->setPosition(x + (isVertical ? 0 : width - sliderSize), y + (isVertical ? height - sliderSize : 0));
	target.draw(*slider, states);
	target.draw(rectangle, colorsCount, sf::Quads, states);
	slider->setPosition(x + (isVertical ? 0 : (width * sliderPos <= sliderSize / 2 ? 0 : (width * sliderPos >= width - sliderSize ? width - sliderSize : width * sliderPos))), y + (isVertical ? (height * sliderPos <= sliderSize / 2 ? 0 : height * sliderPos) : 0));
	target.draw(*slider, states);
}

void GradientSelector::onClick() const
{
	clickAction->invoke(NULL);
}

void GradientSelector::setClickAction(Delegate<int>* clickAction)
{
	this->clickAction = clickAction;
}
