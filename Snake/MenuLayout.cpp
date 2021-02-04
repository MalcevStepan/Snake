#include "MenuLayout.h"

void MenuLayout::setAdapter(MainMenuAdapter* adapter)
{
	this->adapter = adapter;
	for (int i = 0; i < adapter->getItemCount(); i++) {
		const TextView* view = (TextView*)adapter->getItems()[i];
		sf::FloatRect bounds = view->getGlobalBounds();
		((sf::Text*)view)->setPosition(getWidth() / 2 - bounds.width / 2, getHeight() / 2 + bounds.height * 2 * (i - adapter->getItemCount()));
		addView(view);

		std::function<int(int)> fn = [=](int) mutable {
			clickAction->invoke(Layout::indexOf(view));
			return 0;
		};

		adapter->getItems()[i]->setClickAction(new Delegate<int>(fn));
	}
}

void MenuLayout::setClickAction(Delegate<int>* clickAction)
{
	this->clickAction = clickAction;
}

MainMenuAdapter* MenuLayout::getAdapter()
{
	return adapter;
}

void MenuLayout::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	MenuLayout* layout = const_cast<MenuLayout*>(this);
	for (int i = 0; i < layout->getAdapter()->getItemCount(); i++)
		target.draw(*((sf::Text*)layout->getAdapter()->getItems()[i]));
}
