#pragma once
#include "SDL2/SDL.h"
#include <iostream>

class Texture;
class Game {
public:
	//Get the game singleton class
	//This will allow us to access global functions and variables in the game class
	static Game& GetGameInstance();

	//Destoy the game class
	static void DestroyGameInstance();

	//Initialise the game before the loop runs
	void Start(const char* WTitle, bool bFullscreen, int WWidth, int WHeight);

private:
	Game();
	~Game();
		
	//Handle the input of the user
	void ProcessInput();

	//Handle the game logic
	void Update();

	//Render the graphics to the screen
	void Draw();

	//Run the game loop
	void Run();

	//Clean up any memory we need to clean
	void CloseGame();

private:
	//Handle the game loop condition
	//On true end game
	bool bIsGameOver;

	//Store the app window
	SDL_Window* SdlWindow;

	//store the rendere to render graphics
	SDL_Renderer* SdlRenderer;

	//store a texture object
	Texture* Texture1;
	Texture* Texture2;
	Texture* Texture3;
};