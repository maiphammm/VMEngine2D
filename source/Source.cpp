#include "VMEngine2D/Game.h"
using namespace std;

int main(int argc, char** argv) {
	//This will run until the game loop fails
	Game::GetGameInstance().Start("VMEngine2D | Powered By SDL2", false, 980, 540);

	//This will end the game
	Game::DestroyGameInstance();

	return 0;
}