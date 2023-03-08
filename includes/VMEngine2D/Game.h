#pragma once
#include "SDL2/SDL.h"
#include <iostream>
#include <vector>
using namespace std;

class AnimStateMachine;
class Input;
class GameObject;

class Game {
public:
	//Get the game singleton class
	//This will allow us to access global functions and variables in the game class
	static Game& GetGameInstance();

	//Destoy the game class
	static void DestroyGameInstance();

	//Initialise the game before the loop runs
	void Start(const char* WTitle, bool bFullscreen, int WWidth, int WHeight);

	//For precise timing
	double GetDeltaTime() const { return DeltaTime; };

	//For average timing
	//convert from precise double to less precise float
	float GetFDeltaTime() const { return static_cast<float>(DeltaTime); }

	//sets the gameover to true which closes the app
	void CloseApp() { bIsGameOver = true; }

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

	//Load game logic when game loop starts
	void BeginPlay();

private:
	//Handle the game loop condition
	//On true end game
	bool bIsGameOver;

	//Store the app window
	SDL_Window* SdlWindow;

	//store the rendere to render graphics
	SDL_Renderer* SdlRenderer;

	//hold the time between each frame
	double DeltaTime;
	//Detection for player input
	Input* PlayerInput;

	//GameObject Stack
	vector<GameObject*> AllGameObjects;

};