#pragma once
#include "SDL2/SDL.h"
#include <iostream>
#include <vector>
using namespace std;

class Input;
class GameObject;
class CollisionComponent;
class GameStateMachine;
class WindowMenu;

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

	//return all colliders in the game
	vector<CollisionComponent*> GetGameColliders() const;

	//return the game state machine
	GameStateMachine* GetGameState() const { return GameStates; }

	//get the top levels
	WindowMenu* GetTopMenu() const { return TopMenu; }

	//restart the game as if the app was clsed and opened
	void RestartGame();

private:
	Game();
	~Game();

	//add things into the game
	void Instantiate();
		
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

	//remove things from memory at the end of game loop
	void HandleGarbage();

public:
	//store the current score to be shared across states
	unsigned int GameScore;

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

	//store the current game state
	GameStateMachine* GameStates;

	WindowMenu* TopMenu;
};
