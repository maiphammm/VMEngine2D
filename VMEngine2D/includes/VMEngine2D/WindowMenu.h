#pragma once

struct SDL_Window;
struct SDL_SysWMinfo;

class WindowMenu {
public:
	WindowMenu(SDL_Window* Window);
	~WindowMenu();

	//create the menu and add it to the window using a visual studio resources
	void CreateMenuFromResource();


	//Restart the game without closing the app
	void RestartGame();

	//close the app competely
	void ExitApp();

	//load a dialog box that will provide a message
	void ActivatePopup(const char* Title, const char* Message);

private:
	//SDL window for the menu
	SDL_Window* Window;
	//system version of the qindow
	SDL_SysWMinfo* WindowInfo;
};