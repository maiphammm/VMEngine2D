#include "VMEngine2D/WindowMenu.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_syswm.h"
#include "../resource.h"
#include <Windows.h>
#include <iostream>
#include "VMEngine2D/Game.h"

using namespace std;

WindowMenu::WindowMenu(SDL_Window* Window)
{
	//initialise window menu value
	this->Window = Window;
	WindowInfo = new SDL_SysWMinfo();

	//update window info with the current version of SDL that we are using
	SDL_VERSION(&WindowInfo->version);

	//after we have the version SDL will allow us to assign the rest of the info using an SDL function
	SDL_GetWindowWMInfo(Window, WindowInfo);

}

WindowMenu::~WindowMenu()
{
	//set window to nullptr but dont delete as the Game.cpp handles that
	Window = nullptr;

	//delete the window info object
	delete WindowInfo;
	WindowInfo = nullptr;
}

void WindowMenu::CreateMenuFromResource()
{
	//we need to convert our SDL window info into a system window
	HWND SysWindow = WindowInfo->info.win.window;

	//get the resourse menu that we creates in visual studio
	//getModuleHandele(0) get the current instance of the window that we are actively in
	HINSTANCE WindowInstance = GetModuleHandle(0);

	//MAKEINTRESOURCE will convert the IDR_MENU1 into a LPCWSTR which has the index for the menu
	LPCWSTR VSMenu = MAKEINTRESOURCE(IDR_MENU1);

	//load the menu selected to the active window
	HMENU SysMenu = LoadMenu(WindowInstance, VSMenu);

	//this adds the menu to the window
	//if it failes then error log and stop the function
	if (!SetMenu(SysWindow, SysMenu)) {
		cout << "Menu couldn't be set." << endl;
		return;
	}

	//if the menu succesfully added then activates the listener for SDL events
	SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);

}

void WindowMenu::RestartGame()
{
	//run the restart game function built into the game logic
	Game::GetGameInstance().RestartGame();

}

void WindowMenu::ExitApp()
{
	//run the close app function built into the game logic
	Game::GetGameInstance().CloseApp();
}

void WindowMenu::ActivatePopup(const char* Title, const char* Message)
{
	//create a message box that will show on screen with the title and message
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, Title, Message, Window);
}
