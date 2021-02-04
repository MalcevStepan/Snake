#include "GameWindow.h"
#include "MainMenuAdapter.h"

int View::staticId = 0;

int main() {
	int width = 1280, height = 720;
	GameWindow game(width, height);
	game.start();
	return 0;
}