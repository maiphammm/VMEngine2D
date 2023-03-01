#include "VMEngine2D/Game.h"
#include "VMEngine2D/Vector2.h"
#include "VMEngine2D/AnimStateMachine.h"

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
	ASM1 = nullptr;
	
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
	Run();
}

void Game::ProcessInput()
{
	//this stored the inputs as an event
	SDL_Event PollEvent;
	
	//this will listen to the event and end the loop after all inputs are detected
	while(SDL_PollEvent(&PollEvent)) {
		//detec the type of event that was input
		switch (PollEvent.type) {
		case SDL_QUIT :
			bIsGameOver = true;
			break;
		default : 
			break;
		}
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
}

void Game::Draw()
{
	//set background color of app
	SDL_SetRenderDrawColor(SdlRenderer, 100, 0, 0, 255);
	//clear the previous frame
	SDL_RenderClear(SdlRenderer);

	//Do anything that needs to be drawn to the screen here
	ASM1->Draw(SdlRenderer, 0, Vector2(50.0f, 100.0f), 4.0f, false);
	ASM1->Draw(SdlRenderer, 1, Vector2(200.0f, 200.0f), 6.0f, false);
	ASM1->Draw(SdlRenderer, 2, Vector2(500.0f, 300.0f), 6.0f, false);
	ASM1->Draw(SdlRenderer, 3, Vector2(600.0f, 100.0f), 4.0f, false);
	ASM1->Draw(SdlRenderer, 4, Vector2(350.0f, 100.0f), 5.0f, false);

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
	cout << "Destroyed Animation..." << endl;
	delete ASM1;

	//Handle SDL unintilisation
	cout << "Cleaning up SDL" << endl;
	SDL_DestroyWindow(SdlWindow);
	SDL_Quit();
}

void Game::BeginPlay()
{
	cout << "Load Game Assets!" << endl;

	ASM1 = new AnimStateMachine();

	STAnimationData AnimData = STAnimationData();
	
	//First sprite 
	AnimData.FPS = 24;
	AnimData.MaxFrames = 12;
	//the frame should be assumed as index by array values
	AnimData.StartFrame = 0;
	AnimData.EndFrame = 11;

	ASM1->AddAnimation(SdlRenderer,
		"Content/Images/MainShip/Main Ship - Shields - Round Shield.png",
		AnimData);

	//Second sprite 
	AnimData.FPS = 24;
	AnimData.MaxFrames = 10;
	//the frame should be assumed as index by array values
	AnimData.StartFrame = 0;
	AnimData.EndFrame = 9;

	ASM1->AddAnimation(SdlRenderer,
		"Content/Images/MainShip/Main Ship - Shields - Invincibility Shield.png",
		AnimData);

	//Third sprite 
	AnimData.FPS = 24;
	AnimData.MaxFrames = 10;
	//the frame should be assumed as index by array values
	AnimData.StartFrame = 0;
	AnimData.EndFrame = 9;

	ASM1->AddAnimation(SdlRenderer,
		"Content/Images/MainShip/Main Ship - Shields - Front Shield.png",
		AnimData);

	//Fourth sprite 
	AnimData.FPS = 24;
	AnimData.MaxFrames = 6;
	//the frame should be assumed as index by array values
	AnimData.StartFrame = 0;
	AnimData.EndFrame = 5;

	ASM1->AddAnimation(SdlRenderer,
		"Content/Images/MainShip/Main Ship - Shields - Front and Side Shield.png",
		AnimData);

	//FIFth sprite 
	AnimData.FPS = 24;
	AnimData.MaxFrames = 7;
	//the frame should be assumed as index by array values
	AnimData.StartFrame = 0;
	AnimData.EndFrame = 6;

	ASM1->AddAnimation(SdlRenderer,
		"Content/Images/MainShip/Main Ship - Weapons - Auto Cannon.png",
		AnimData);
}
