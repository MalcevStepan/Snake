#pragma once
#include "Delegate.h"

class Clickable {
public:
	virtual void onClick() const = 0;
	virtual void setClickAction(Delegate<int>* clickAction) = 0;
};