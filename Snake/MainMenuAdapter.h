#pragma once
#include <SFML/Graphics.hpp>
#include "IMenuAdapter.h"

class MainMenuAdapter : public IMenuAdapter {
private:
	TextView* startText, * settingsText;
	sf::Font* textFont;
	int textSize;

	TextView* getStartText();
	TextView* getSettingsText();
	sf::Font* getFont();
	std::vector<TextView*> items;

public:
	MainMenuAdapter(int textSize, sf::Font* font) : textSize(textSize), textFont(font) {
		items.push_back(getStartText());
		items.push_back(getSettingsText());
	}
	~MainMenuAdapter() {
		delete startText, settingsText, textFont;
	}

	// Унаследовано через IMenuAdapter
	virtual int getItemCount() override;
	virtual std::vector<TextView*> getItems() override;
};