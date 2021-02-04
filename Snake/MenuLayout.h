#pragma once
#include "Layout.h"
#include "MainMenuAdapter.h"

class MenuLayout : public Layout {
private:
	MainMenuAdapter* adapter;
	Delegate<int>* clickAction;
public:

	MenuLayout(int width, int height) : Layout(width, height) {}

	void setAdapter(MainMenuAdapter* adapter);
	void setClickAction(Delegate<int>* clickAction);

	MainMenuAdapter* getAdapter();

	// Унаследовано через Layout
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
