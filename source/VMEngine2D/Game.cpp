#include "VMEngine2D/Game.h"
#include "VMEngine2D/Vector2.h"
#include "VMEngine2D/AnimStateMachine.h"
#include "VMEngine2D/Input.h"
#include "VMEngine2D/GameObjects/Characters/Player.h"
#include "VMEngine2D/GameObjects/Characters/Enemy.h"
#include"VMEngine2D/GameObject.h"
#include "VMEngine2D/Animation.h"

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

Game::Game()
{
	cout << "Initialised Game Instance!" << endl;
	bIsGameOver = false;
	SdlWindow = nullptr;
	SdlRenderer = nullptr;
	DeltaTime = 0.0;
	PlayerInput = nullptr;
	
}

Game::~Game()
{
	cout << "Destroyed Game Instance..." << endl;
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
		
		//Uninitialise SDL
		SDL_Quit();
		return;
	}

	//set up the renderer
	SdlRenderer = SDL_CreateRenderer(SdlWindow, 0, -1);
	if (SdlRenderer == nullptr) {
		cout << "SDL Renderer creation failed: " << SDL_GetError() << endl;
		//remove the window
		SDL_DestroyWindow(SdlWindow);
		//unintialise SDL
		SDL_Quit();
		return;
	}
	//Create the input in initialisation stage
	PlayerInput = new Input();

	Run();
}

void Game::ProcessInput()
{
	//this must run before all other process input detection
	PlayerInput->ProcessInput();

	//process the input of each GameObject
	for (GameObject* SingGameObject : AllGameObjects) {
		SingGameObject->ProcessInput(PlayerInput);
	}
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

	//run the game object logic
	for (GameObject* SingleGameObject : AllGameObjects) {
		SingleGameObject->Update();
	}
}

void Game::Draw()
{
	//set background color of app
	SDL_SetRenderDrawColor(SdlRenderer, 100, 0, 0, 255);
	//clear the previous frame
	SDL_RenderClear(SdlRenderer);

	//Do anything that needs to be drawn to the screen here
	
	//cycle through all of the game objects in the AllGameObjects
	//each loop reassign the SingleGameObject pointer with the next item in the array
	for (GameObject* SingleGameObject : AllGameObjects) {
		//each loop run the draw function for the assigned gameobject
		SingleGameObject->Draw(SdlRenderer);
	}

	//show the new frame
	SDL_RenderPresent(SdlRenderer);
}

void Game::Run()
{
	if (!bIsGameOver) {
		BeginPlay();
	}
	while (!bIsGameOver) {
		ProcessInput();

		Update();

		Draw();

		// SDL_Delay(1);
	}

	CloseGame();
}

void Game::CloseGame()
{
	//handle game asset detection
	cout << "Deleting game assets..." << endl;
	

	cout << "Deleting top level systems..." << endl;
	//delete player from memory
	delete PlayerInput;

	//Handle SDL unintilisation
	cout << "Cleaning up SDL" << endl;
	SDL_DestroyWindow(SdlWindow);
	SDL_Quit();
}

void Game::BeginPlay()
{
	cout << "Load Game Assets!" << endl;

	Player* MyCharacter = new Player(Vector2(100.0f, 108.0f), SdlRenderer);
	Enemy* Bomber = new Enemy(Vector2(300.0f, 108.0f), SdlRenderer);

	//Add the character into the game object stack
	
	AllGameObjects.push_back(Bomber);
	AllGameObjects.push_back(MyCharacter);
}
