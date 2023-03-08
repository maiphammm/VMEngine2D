#include "VMEngine2D/Input.h"
#include "VMEngine2D/Game.h"
#include <iostream>
using namespace std;

Input::Input()
{
	//Assigning all the states of the keys to the keyboard state
	//NULL mwans get all the keys
	KeyboardState = SDL_GetKeyboardState(NULL);
}

Input::~Input()
{
	cout << "Input Destroyed." << endl;
}

void Input::ProcessInput()
{
	//this stored the inputs as an event
	SDL_Event PollEvent;

	//this will listen to the event and end the loop after all inputs are detected
	while (SDL_PollEvent(&PollEvent)) {
		//detec the type of event that was input
		switch (PollEvent.type) {
		case SDL_KEYDOWN:
			//set the keyboard state
			KeyboardState = SDL_GetKeyboardState(NULL);
			break;
		case SDL_KEYUP:
			//set the keyboard state
			KeyboardState = SDL_GetKeyboardState(NULL);
			break;
		case SDL_QUIT:
			//Go into the game instance and run the CloseApp function
			Game::GetGameInstance().CloseApp();
			break;
		default:
			break;
		}
	}
}

bool Input::IsKeyDown(SDL_Scancode Key)
{
	//if the keystate doesn't exist then dont run the fuction
	if (KeyboardState == nullptr) {
		cout << "No keyboard state detected." << endl;
		return false;
	}

	//return value of the key : true or false
	return KeyboardState[Key];
}
