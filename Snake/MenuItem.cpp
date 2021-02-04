#include "MenuItem.h"

void MenuItem::onClick()
{
	clickAction->invoke();
}

void MenuItem::setClickAction(Delegate* clickAction)
{
	MenuItem::clickAction = clickAction;
}
