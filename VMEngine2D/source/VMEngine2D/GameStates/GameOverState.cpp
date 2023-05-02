#include "VMEngine2D/GameStates/GameOverState.h"
#include "VMEngine2D/Text.h"
#include "VMEngine2D/Game.h"
#include "VMEngine2D/Input.h"
#include "VMEngine2D/GameStates/PlayState.h"

GameOverState::GameOverState(SDL_Window* Window, SDL_Renderer* Renderer) : GameState (Window, Renderer)
{
	ScoreText = nullptr;
	RestartText = nullptr;

	//load background music
	BGM = Mix_LoadMUS("Content/Audio/BGMUsic/Menu_BGMUsic.wav");

	//check if loaded correctly
	if (BGM == NULL) {
		cout << "Menu background music couldnt load" << endl;
	}
}

void GameOverState::BeginState()
{
	GameState::BeginState();

	//set the volume
	Mix_VolumeMusic(25);

	//play the music
	if (Mix_PlayMusic(BGM, -1) == -1) {
		cout << "Couldn play menu music" << endl;
	}
	
	//create an empty text
	ScoreText = new Text(StateRenderer);

	//adjust the settings for the text
	STTextInfo TextSettings;
	TextSettings.Size = 60;
	TextSettings.Position = Vector2(25.0f, 25.0f);
	TextSettings.TextStr = "Final Score: " + to_string(Game::GetGameInstance().GameScore);

	//create the text with font and settings
	ScoreText->InitText("Content/Fonts/GameOfSquids.ttf", TextSettings);

	//add the score to the state
	ActivateTextObject(ScoreText);

	RestartText = new Text(StateRenderer);
	TextSettings.Size = 24;
	TextSettings.Position = Vector2(25.0f, 150.0f);
	TextSettings.TextStr = "Press Space to restart the game";

	RestartText->InitText("Content/Fonts/GameOfSquids.ttf", TextSettings);

	ActivateTextObject(RestartText);

}

void GameOverState::ProcessInput(Input* PlayerInput)
{
	GameState::ProcessInput(PlayerInput);

	if (PlayerInput->IsKeyDown(SDL_SCANCODE_SPACE)) {
		Game::GetGameInstance().GameScore = 0;

		PlayState* NewState = new PlayState(StateWindow, StateRenderer);

		Game::GetGameInstance().GetGameState()->SwitchState(NewState);
	}
}

void GameOverState::Update(float DeltaTime)
{
	GameState::Update(DeltaTime);
}

void GameOverState::Draw(SDL_Renderer* Renderer)
{
	GameState::Draw(Renderer);
}

void GameOverState::EndState()
{
	GameState::EndState();

	ScoreText = nullptr;
	RestartText = nullptr;

	if (BGM != nullptr) {
		//stop and free music from memory
		Mix_HaltMusic();
		Mix_FreeMusic(BGM);
	}
}
