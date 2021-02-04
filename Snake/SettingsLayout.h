#pragma once
#include "Layout.h"
#include "GradientSelector.h"
#include "Cell.h"
#include "Settings.h"
#include "TextView.h"
#include <vector>

class SettingsLayout : public Layout {
private:
	GradientSelector* colorSelector, * brightnessSelector, * speedSelector;
	TextView* backText, * speedText, * colorText, * brightnessText;
	sf::Color gradientColor[12], brightnessColor[4];
	Settings* settings;
	Cell* colorExample;
	sf::Font* font;
	Delegate<int>* clickAction;

	TextView* getSpeedText();
	TextView* getColorText();
	TextView* getBrightnessText();
	TextView* getBackText();

	GradientSelector* getColorSelector();
	GradientSelector* getBrightnessSelector();
	GradientSelector* getSpeedSelector();


	Cell* getColorExample(float color, float brightness);

	sf::Font* getFont();

	Settings* getSettings();

public:
	SettingsLayout(Settings* settings, int width, int height, Delegate<int>* clickAction) : Layout(width, height) {
		this->clickAction = clickAction;
		this->settings = settings;

		addView(getBackText());
		addView(getColorSelector());
		addView(getBrightnessSelector());
		addView(getSpeedSelector());
	}
	// Унаследовано через Layout
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setSettings(Settings* settings);

	sf::Color* getGradientColor(float brightness);
	sf::Color* getBrightnessColor(float color);

	void setFont(sf::Font* font);

	sf::Color getSnakeColor();
};