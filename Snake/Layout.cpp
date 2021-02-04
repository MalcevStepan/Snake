#include "Layout.h"
#include <iostream>

void Layout::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (std::vector<const View*>::const_iterator itr = childs.begin(); itr != childs.end(); itr++)
		target.draw(**itr, states);
}

void Layout::addView(const View* view)
{
	childs.push_back(view);
}

void Layout::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

const View* Layout::getChildAt(int index)
{
	return childs[index];
}

int Layout::indexOf(const View* view)
{
	int i = 0;
	for (std::vector<const View*>::iterator itr = childs.begin(); itr != childs.end(); itr++, i++)
		if ((*itr)->getId() == view->getId())
			return i;
	return -1;
}

int Layout::getX()
{
	return x;
}

int Layout::getY()
{
	return y;
}

int Layout::getWidth()
{
	return width;
}

int Layout::getHeight()
{
	return height;
}
