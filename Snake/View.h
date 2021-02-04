#pragma once
#include <SFML/Graphics.hpp>
#include "Clickable.h"
#include <iostream>

class View : public sf::Drawable, public Clickable {
private:
	int x = 0, y = 0, width = 0, height = 0, id = 0;
public:
	static int staticId;
	View() {
		id = staticId++;
	}
	View(int width, int height) {
		this->width = width;
		this->height = height;
		id = staticId++;
	}

	// Унаследовано через Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {};

	// Унаследовано через Clickable
	virtual void onClick() const override = 0;
	virtual void setClickAction(Delegate<int>* clickAction) override = 0;

	void setPosition(int x, int y) {
		this->x = x;
		this->y = y;
	}

	int getId() const { return id; }
	int getX() const { return x; }
	int getY() const { return y; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }
};