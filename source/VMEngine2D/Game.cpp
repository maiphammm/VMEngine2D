#include "VMEngine2D/Game.h"
#include "VMEngine2D/Vector2.h"
#include "VMEngine2D/Texture.h"
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
	Texture1 = nullptr;
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
	
}

void Game::Draw()
{
	//set background color of app
	SDL_SetRenderDrawColor(SdlRenderer, 100, 0, 0, 255);
	//clear the previous frame
	SDL_RenderClear(SdlRenderer);

	//Draw texture
	if (Texture1 != nullptr) {
		Texture1->Draw(SdlRenderer, Vector2(100.0f, 100.0f), nullptr);
	}
	if (Texture2 != nullptr) {
		Texture2->Draw(SdlRenderer, Vector2(200.0f, 100.0f), nullptr);
	}

	//show the new frame
	SDL_RenderPresent(SdlRenderer);
}

void Game::Run()
{
	if (!bIsGameOver) {
		Texture1 = new Texture();
		if (!Texture1->LoadImageFromFile("Content/Images/Letters/LBlue.png", SdlRenderer)) {
			Texture1 = nullptr;
		}

		Texture2 = new Texture();
		if (!Texture2->LoadImageFromFile("Content/Images/Letters/ORed.png", SdlRenderer)) {
			Texture2 = nullptr;
		}
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
	//Handle SDL unintilisation
	cout << "Cleaning up SDL" << endl;
	SDL_DestroyWindow(SdlWindow);
	SDL_Quit();
}
