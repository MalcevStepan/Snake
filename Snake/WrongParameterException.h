#pragma once

#include "GameException.h"

class WrongParameterException : GameException {
private:
	std::string message;
public:
	WrongParameterException() {}
	WrongParameterException(std::string message) : message(message) {}
	virtual std::string what() override {
		return "WrongParameterException: " + message;
	}
};