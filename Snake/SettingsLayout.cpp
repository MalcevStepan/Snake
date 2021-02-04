#include "SettingsLayout.h"

void SettingsLayout::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	SettingsLayout* sl = const_cast<SettingsLayout*>(this);
	target.draw(*(sl->getColorSelector()));
	target.draw(*(sl->getSpeedSelector()));
	target.draw(*(sl->getBrightnessSelector()));
	target.draw(*((sf::Text*)sl->getColorText()));
	target.draw(*((sf::Text*)sl->getSpeedText()));
	target.draw(*((sf::Text*)sl->getBrightnessText()));
	target.draw(*(sl->getColorExample(sl->getSettings()->getColor(), sl->getSettings()->getBrightness())));
	target.draw(*((sf::Text*)sl->getBackText()));
}

TextView* SettingsLayout::getSpeedText() {
	if (!speedText) {
		speedText = new TextView("Speed", *getFont(), getWidth() / 20);
		speedText->setFillColor(sf::Color::White);
		speedText->setStyle(sf::Text::Bold);
		sf::FloatRect bounds = colorText->getGlobalBounds();
		((sf::Text*)speedText)->setPosition(sf::Vector2f(getWidth() / 2 - bounds.width / 2, getSpeedSelector()->getY() - bounds.height * 3));
	}
	return speedText;
}

TextView* SettingsLayout::getBrightnessText() {
	if (!brightnessText) {
		brightnessText = new TextView("Brightness", *getFont(), getWidth() / 20);
		brightnessText->setFillColor(sf::Color::White);
		brightnessText->setStyle(sf::Text::Bold);
		sf::FloatRect bounds = brightnessText->getGlobalBounds();
		((sf::Text*)brightnessText)->setPosition(sf::Vector2f(getWidth() / 2 - bounds.width / 2, getBrightnessSelector()->getY() - bounds.height * 3));
	}
	return brightnessText;
}

TextView* SettingsLayout::getBackText()
{
	if (!backText) {
		backText = new TextView("<-", *getFont(), getWidth() / 20);
		backText->setFillColor(sf::Color::Yellow);
		backText->setStyle(sf::Text::Bold);
		sf::FloatRect bounds = backText->getGlobalBounds();
		((sf::Text*)backText)->setPosition(sf::Vector2f(bounds.width / 2, -bounds.height / 2));

		std::function<int(int)> fn = [&](int) {
			int i = indexOf(backText);
			clickAction->invoke(i);
			return i;
		};

		backText->setClickAction(new Delegate<int>(fn));
	}
	return backText;
}


void SettingsLayout::setFont(sf::Font* font)
{
	this->font = font;
}

sf::Font* SettingsLayout::getFont() {
	if (!font) {
		font = new sf::Font();
		font->loadFromFile("pixel_sans.ttf");
	}
	return font;
}

TextView* SettingsLayout::getColorText() {
	if (!colorText) {
		colorText = new TextView("Color", *getFont(), getWidth() / 20);
		colorText->setFillColor(sf::Color::White);
		colorText->setStyle(sf::Text::Bold);
		sf::FloatRect bounds = colorText->getGlobalBounds();
		((sf::Text*)colorText)->setPosition(sf::Vector2f(getWidth() / 2 - bounds.width / 2, getColorSelector()->getY() - bounds.height * 3));
	}
	return colorText;
}

Cell* SettingsLayout::getColorExample(float color, float brightness)
{
	if (!colorExample) {
		GradientSelector* selector = getColorSelector();
		colorExample = new Cell(selector->getX() + selector->getWidth() + selector->getHeight(), selector->getY(), selector->getHeight());
	}
	float b = brightness;
	float p1 = 1 / 3.f, p2 = 2 / 3.f;
	if (color <= p1)
		colorExample->setColor(sf::Color((1 - color / p1) * 255 * b, 0, color / p1 * 255 * b));
	else if (color > p1 && color <= p2)
		colorExample->setColor(sf::Color(0, (color / p2) * 255 * b, (1 - color) / p2 * 255 * b));
	else if (color > p2)
		colorExample->setColor(sf::Color(color * 255 * b, (1 - color) * 255 * b, 0));
	return colorExample;
}

sf::Color* SettingsLayout::getGradientColor(float b)
{
	gradientColor[0] = sf::Color(255 * b, 0, 0);
	gradientColor[1] = sf::Color(0, 0, 255 * b);
	gradientColor[2] = sf::Color(0, 0, 255 * b);
	gradientColor[3] = sf::Color(255 * b, 0, 0);

	gradientColor[4] = sf::Color(0, 0, 255 * b);
	gradientColor[5] = sf::Color(0, 255 * b, 0);
	gradientColor[6] = sf::Color(0, 255 * b, 0);
	gradientColor[7] = sf::Color(0, 0, 255 * b);

	gradientColor[8] = sf::Color(0, 255 * b, 0);
	gradientColor[9] = sf::Color(255 * b, 0, 0);
	gradientColor[10] = sf::Color(255 * b, 0, 0);
	gradientColor[11] = sf::Color(0, 255 * b, 0);
	return gradientColor;
}

sf::Color* SettingsLayout::getBrightnessColor(float color)
{
	int r, g, b;
	float p1 = 1 / 3.f, p2 = 2.f / 3.f;
	if (color <= p1) {
		r = (1 - color / p1) * 255;
		g = 0;
		b = color / p1 * 255;
	}
	else if (color > p1 && color <= p2) {
		r = 0;
		g = (color / p2) * 255;
		b = (1 - color) / p2 * 255;
	}
	else if (color > p2) {
		r = color * 255;
		g = (1 - color) * 255;
		b = 0;
	}
	brightnessColor[0] = sf::Color(0, 0, 0);
	brightnessColor[1] = sf::Color(r, g, b);
	brightnessColor[2] = sf::Color(r, g, b);
	brightnessColor[3] = sf::Color(0, 0, 0);
	return brightnessColor;
}

sf::Color SettingsLayout::getSnakeColor()
{
	return getColorExample(getSettings()->getColor(), getSettings()->getBrightness())->getColor();
}

GradientSelector* SettingsLayout::getColorSelector()
{
	if (!colorSelector) {
		try {
			sf::Color* gradient = getGradientColor(getSettings()->getBrightness());
			colorSelector = new GradientSelector(getWidth() / 3, getHeight() / 4, getSettings()->getColor(), getWidth() / 3, getHeight() / 20, 12);
			colorSelector->setColor(12, gradient);

			std::function<int(int)> fn = [=](int) {
				clickAction->invoke(indexOf(colorSelector));
				return 0;
			};

			colorSelector->setClickAction(new Delegate<int>(fn));
		}
		catch (WrongParameterException& e) {
			std::cout << e.what();
		}
		catch (GameException& e) {
			std::cout << e.what();
		}
	}
	return colorSelector;
}

GradientSelector* SettingsLayout::getBrightnessSelector()
{
	if (!brightnessSelector) {
		sf::Color color = getColorExample(getSettings()->getColor(), getSettings()->getBrightness())->getColor();
		sf::Color* colors = getBrightnessColor(getSettings()->getColor());
		try {
			brightnessSelector = new GradientSelector(getWidth() / 3, getHeight() * 2 / 4, getSettings()->getBrightness(), getWidth() / 3, getHeight() / 20, 4);
			brightnessSelector->setColor(4, colors);

			std::function<int(int)> fn = [=](int) mutable {
				clickAction->invoke(indexOf(brightnessSelector));
				return 0;
			};

			brightnessSelector->setClickAction(new Delegate<int>(fn));
		}
		catch (WrongParameterException& e) {
			std::cout << e.what();
		}
		catch (GameException& e) {
			std::cout << e.what();
		}
	}
	return brightnessSelector;
}

GradientSelector* SettingsLayout::getSpeedSelector()
{
	if (!speedSelector) {

		sf::Color colors[4]{
			sf::Color(0, 255, 0),
			sf::Color(255, 0, 0),
			sf::Color(255, 0, 0),
			sf::Color(0, 255, 0)
		};
		try {
			speedSelector = new GradientSelector(getWidth() / 3, getHeight() * 3 / 4, getSettings()->getSpeed(), getWidth() / 3, getHeight() / 20, sizeof(colors) / sizeof(sf::Color));
			speedSelector->setColor(sizeof(colors) / sizeof(sf::Color), colors);

			std::function<int(int)> fn = [=](int) {
				clickAction->invoke(indexOf(speedSelector));
				return 0;
			};

			speedSelector->setClickAction(new Delegate<int>(fn));
		}
		catch (WrongParameterException& e) {
			std::cout << e.what();
		}
		catch (GameException& e) {
			std::cout << e.what();
		}
	}
	return speedSelector;
}

Settings* SettingsLayout::getSettings()
{
	return settings;
}

void SettingsLayout::setSettings(Settings* settings)
{
	this->settings = settings;
}
