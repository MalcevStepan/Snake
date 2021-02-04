#pragma once

#include <iostream>

class Settings {
private:
	float color = 0, speed = 0.1, brightness = 1;
public:
	Settings() {}

	float getColor() { return color; }
	void setColor(float color) { this->color = color; }

	float getSpeed() { return speed; }
	void setSpeed(float speed) { this->speed = speed; }

	float getBrightness() { return brightness; }
	void setBrightness(float brightness) { this->brightness = brightness; }

	friend std::istream& operator>>(std::istream& in, Settings& p) {
		in >> p.color;
		in >> p.brightness;
		in >> p.speed;
		return in;
	}

	friend std::ostream& operator<<(std::ostream& os, const Settings& p) {
		os << p.color << std::endl << p.brightness << std::endl << p.speed << std::endl;
		return os;
	}
};