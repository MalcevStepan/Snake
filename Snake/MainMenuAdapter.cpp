#include "MainMenuAdapter.h"

int MainMenuAdapter::getItemCount()
{
	return items.size();
}

sf::Font* MainMenuAdapter::getFont() {
	if (!textFont) {
		textFont = new sf::Font();
		textFont->loadFromFile("pixel_sans.ttf");
	}
	return textFont;
}

TextView* MainMenuAdapter::getStartText() {
	if (!startText) {
		startText = new TextView("Start", *getFont(), textSize);
		startText->setFillColor(sf::Color::White);
		startText->setStyle(sf::Text::Bold);
	}
	return startText;
}

TextView* MainMenuAdapter::getSettingsText() {
	if (!settingsText) {
		settingsText = new TextView("Settings", *getFont(), textSize);
		settingsText->setFillColor(sf::Color::White);
		settingsText->setStyle(sf::Text::Bold);
	}
	return settingsText;
}

std::vector<TextView*> MainMenuAdapter::getItems()
{
	return items;
}
