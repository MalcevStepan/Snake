#pragma once
#include <SFML/Graphics.hpp>
#include "Clickable.h"
#include "View.h"

class TextView : public sf::Text, public View {
private:
	Delegate<int>* clickAction;
public:
	TextView(const sf::String& string, const sf::Font& font, unsigned int characterSize = 30) : Text(string, font, characterSize) {}

	// Унаследовано через View
	virtual void onClick() const override {
		clickAction->invoke(NULL);
	}

	virtual void setClickAction(Delegate<int>* clickAction) override {
		this->clickAction = clickAction;
	}

};