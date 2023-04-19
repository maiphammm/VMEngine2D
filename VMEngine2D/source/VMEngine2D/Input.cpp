#include "VMEngine2D/Input.h"
#include "VMEngine2D/Game.h"
#include <iostream>
#include "VMEngine2D/WindowMenu.h"
#include "SDL2/SDL_syswm.h"
#include "../resource.h"

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
		case SDL_SYSWMEVENT:
			HandleWMEvents(&PollEvent);
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

void Input::HandleWMEvents(SDL_Event* Event)
{
	//listen out for the system window menu button presses
	switch (Event->syswm.msg->msg.win.wParam) {
	case ID_FILE_RESTARTGAME:
		Game::GetGameInstance().RestartGame();
		break;
	case ID_FILE_CLOSEAPP:
		Game::GetGameInstance().CloseApp();
		break;
	case ID_GAME_CONTROLS:
		Game::GetGameInstance().GetTopMenu()->ActivatePopup(
			"Game Controls", //title
			"WASD - Move Player.\n Space - Shoot \n Q - Activate Shield"  //message
		);
		break;
	case ID_HELP_ABOUTVMENGINE2D:
		Game::GetGameInstance().GetTopMenu()->ActivatePopup(
			"About VMEngine2D", //title
			"BGEngine is an SDL2-based C++ 2D game engine created by Vasilios Moutafis in 2023"  //message
		);
		break;
	default:
		break;

	}
}
