#pragma once
#include "View.h"
#include <vector>

class Layout : sf::Drawable {
private:
	std::vector<const View*> childs;
	int x, y, width, height;
public:

	Layout(int width, int height) {
		this->width = width;
		this->height = height;
	}

	// Унаследовано через Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

	void addView(const View* view);

	void setPosition(int x, int y);

	const View* getChildAt(int index);
	int indexOf(const View* view);

	int getX();
	int getY();
	int getWidth();
	int getHeight();
};