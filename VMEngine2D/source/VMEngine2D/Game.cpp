#include "VMEngine2D/Game.h"
#include "VMEngine2D/Vector2.h"
#include "VMEngine2D/Input.h"
#include "VMEngine2D/GameObject.h"
#include "VMEngine2D/GameState.h"
#include "VMEngine2D/GameStates/PlayState.h"
#include "VMEngine2D/WindowMenu.h"

#include "SDL2/SDL_ttf.h"

using namespace std;

Game& Game::GetGameInstance()
{
	//Create a game instance only if there isn't one already
	//Local static variables can only be created once
	static Game* GameInstance = new Game();
	return *GameInstance;
}

void Game::DestroyGameInstance()
{
	//Store the game instance in a static variable
	static Game* GameInstance = &GetGameInstance();
	//Remove the game instance from memory
	delete GameInstance;
}

vector<CollisionComponent*> Game::GetGameColliders() const
{
	//return the collisions of the current state
	return GameStates->GetCurrentState()->GetStateCollisions();
}

void Game::RestartGame()
{
	//reset the game score
	GameScore = 0;

	//create a new starting state
	PlayState* NewState = new PlayState(SdlWindow, SdlRenderer);
	GetGameState()->SwitchState(NewState);
}

Game::Game()
{
	cout << "Initialised Game Instance!" << endl;
	bIsGameOver = false;
	SdlWindow = nullptr;
	SdlRenderer = nullptr;
	DeltaTime = 0.0;
	PlayerInput = nullptr;
	GameStates = nullptr;
	GameScore = 0;
	TopMenu = nullptr;
}

Game::~Game()
{
	cout << "Destroyed Game Instance..." << endl;
}

void Game::Instantiate()
{
	//run the game states instantiate
	GetGameState()->GetCurrentState()->Instantiate();
}

void Game::Start(const char* WTitle, bool bFullscreen, int WWidth, int WHeight)
{
	//Initilise SDL and end the game if it fails
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		//Error handle
		cout << "SDL Failed to load: " << SDL_GetError() << endl;
		return;
	}

	//Default to window mode
	int FullscreenFlag = SDL_WINDOW_SHOWN;
	
	//of fullscreen is true then overwrite to fullscreen
	if (bFullscreen) {
		FullscreenFlag = SDL_WINDOW_FULLSCREEN;
	}
	SdlWindow = SDL_CreateWindow(
		WTitle,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WWidth, WHeight,
		FullscreenFlag
		);

	//if window wasn't created
	if (SdlWindow == nullptr) {
		//Error log
		cout << "SDL Window creation failed: " << SDL_GetError() << endl;
		
		CloseGame();
		return;
	}

	//set up the renderer
	SdlRenderer = SDL_CreateRenderer(SdlWindow, 0, -1);
	if (SdlRenderer == nullptr) {
		cout << "SDL Renderer creation failed: " << SDL_GetError() << endl;
		
		CloseGame();
		return;
	}

	//Uninitialise TTF and if it = -1 then it failed 0 means it succeeded
	if (TTF_Init() < 0) {
		cout << "SDL TTF failed to initialise." << TTF_GetError() << endl;
		
		CloseGame();
		return;
	}

	//create a menu for the window
	TopMenu = new WindowMenu(SdlWindow);
	//add the menu to the window
	TopMenu->CreateMenuFromResource();
	

	//Create the input in initialisation stage
	PlayerInput = new Input();

	//randomise the seed using time so we always have a different random seed
	srand(time(NULL));

	Run();
}

void Game::ProcessInput()
{
	//this must run before all other process input detection
	PlayerInput->ProcessInput();

	//run the input of the current game state
	GameStates->GetCurrentState()->ProcessInput(PlayerInput);
}

void Game::Update()
{
	//static variables in methods will only intialise once
	//update with the previous frames time passed
	static double LastTickTime = 0.0;
	
	//get the current time in miiliseconds that hass passed since the game has started
	//GetTicks64 returns a Unit64 which means we need to convert it into the double
	double CurrentTickTime = static_cast<double>(SDL_GetTicks64());

	//get the difference between last tick time and current tick time
	double DeltaMil = CurrentTickTime - LastTickTime;
	
	//set Delta time but convert it to seconds
	DeltaTime = DeltaMil / 1000.0;

	//set the last tick time as the current time for the next frame
	LastTickTime = CurrentTickTime;
	
	//run the update of the current dtate and pass in float delta time
	GameStates->GetCurrentState()->Update(GetFDeltaTime());

}

void Game::Draw()
{
	//set background color of app
	SDL_SetRenderDrawColor(SdlRenderer, 100, 0, 0, 255);
	//clear the previous frame
	SDL_RenderClear(SdlRenderer);

	//Do anything that needs to be drawn to the screen here
	
	//run the current game state draw and pass in the renderer
	GameStates->GetCurrentState()->Draw(SdlRenderer);

	//show the new frame
	SDL_RenderPresent(SdlRenderer);
}

void Game::Run()
{
	if (!bIsGameOver) {
		BeginPlay();
	}
	while (!bIsGameOver) {
		Instantiate();

		ProcessInput();

		Update();

		Draw();

		HandleGarbage();
	}

	CloseGame();
}

void Game::CloseGame()
{
	//clean up any values that were initialised into memory
	if (GameStates != nullptr) {
		//handle game asset detection
		cout << "Deleting game assets..." << endl;
		delete GameStates;
	}
	
	if (PlayerInput != nullptr) {
		cout << "Deleting top level systems..." << endl;
		//delete player from memory
		delete PlayerInput;
	}
	
	//Handle SDL unintilisation
	cout << "Cleaning up SDL..." << endl;

	if (SdlWindow != nullptr) {
		SDL_DestroyWindow(SdlWindow);
	}
	if (SdlRenderer != nullptr) {
		SDL_DestroyRenderer(SdlRenderer);
	}

	SDL_Quit();
}

void Game::BeginPlay()
{
	cout << "Load Game Assets!" << endl;

	//create a game state for the starting state
	PlayState* StartingState = new PlayState(SdlWindow, SdlRenderer);
	//create a game state machine and add the starting state
	GameStates = new GameStateMachine(StartingState);

}

void Game::HandleGarbage()
{
	GameStates->GetCurrentState()->HandleGarbage();
}
