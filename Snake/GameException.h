#pragma once

#include <iostream>
#include <cstdlib>

class GameException {
private:
	std::string message;
public:
	GameException() {}
	GameException(std::string message) : message(message) {}
	virtual std::string what() {
		return "GameException: " + message;
	}
};