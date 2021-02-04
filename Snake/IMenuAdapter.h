#pragma once
#include <SFML/Graphics.hpp>
#include "TextView.h"
#include <vector>

class IMenuAdapter {
public:
	virtual std::vector<TextView*> getItems() = 0;
	virtual int getItemCount() = 0;
};