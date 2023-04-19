#pragma once
#include "SDL2/SDL.h"
class Input {
public:
	Input();
	~Input();

	//Run all the input detection logic
	void ProcessInput();

	//Return wherer or not the key is down
	bool IsKeyDown(SDL_Scancode Key);

private:
	//Hold all the states of each key on the keyboard (pressed or released)
	const Uint8* KeyboardState;

	//run the listeners for the windows menu events
	void HandleWMEvents(SDL_Event* Event);
};