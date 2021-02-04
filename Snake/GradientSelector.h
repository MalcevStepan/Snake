#pragma once
#include "View.h"
#include "WrongParameterException.h"

class GradientSelector : public View {
private:
	sf::Vertex* rectangle;
	sf::RectangleShape* slider;
	int sliderSize, colorsCount;
	float sliderPos;
	bool isVertical;
	Delegate<int>* clickAction;
public:
	GradientSelector(int x, int y, float sliderPos, int width, int height, int colorsCount);
	~GradientSelector();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setSliderPos(float pos);
	void setColor(int colorsCount, sf::Color* color);
	// Унаследовано через Clickable
	virtual void onClick() const override;
	virtual void setClickAction(Delegate<int>* clickAction) override;
};