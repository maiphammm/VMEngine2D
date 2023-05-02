#include "VMEngine2D/GameStates/PlayState.h"
#include "VMEngine2D/GameObjects/Characters/Enemy.h"
#include "VMEngine2D/GameObjects/Characters/Player.h"
#include "VMEngine2D/GameObjects/Characters/Collectable.h"
#include "VMEngine2D/Text.h"
#include "VMEngine2D/Game.h"
#include "VMEngine2D/GameStates/GameOverState.h"
#include "VMEngine2D/AnimStateMachine.h"

PlayState::PlayState(SDL_Window* Window, SDL_Renderer* Renderer) : GameState(Window, Renderer)
{
	ScoreText = nullptr;

	SpawnTimer = 0.0;
	SpawnTime = 5.0;
	PlayerCharacter = nullptr;
	LivesText = nullptr;
	BGAnims = nullptr;

	//create the state machine to hold the animations
	BGAnims = new AnimStateMachine();

	//create the anim data
	STAnimationData AnimData;
	AnimData.FPS = 24;
	AnimData.MaxFrames = 9;
	AnimData.EndFrame = 8;

	//add the animations
	BGAnims->AddAnimation(Renderer, "Content/Images/Background/BG_Void.png", AnimData);
	BGAnims->AddAnimation(Renderer, "Content/Images/Background/BG_Stars1.png", AnimData);
	BGAnims->AddAnimation(Renderer, "Content/Images/Background/BG_Stars2.png", AnimData);

	//load a music file using mixer
	BGM = Mix_LoadMUS("Content/Audio/BGMusic/Play_BGMusic.wav");
}

void PlayState::BeginState()
{
	//this run the parent function
	GameState::BeginState();

	//set the volume for music play from mixer
	Mix_VolumeMusic(25);

	//play the music file
	if (Mix_PlayMusic(BGM, -1) == -1) {
		cout << "Couldnt play BGM in play state." << endl;
	}

	//create player
	PlayerCharacter = new Player(Vector2(470.0f, 400.0f), StateRenderer);

	//Add the character into the game object stack
	SpawnGameObject(PlayerCharacter);

	//creat an empty text object
	ScoreText = new Text(StateRenderer);

	//adjust the text setting
	STTextInfo ScoreInfo;
	ScoreInfo.TextStr = "Hello World";
	ScoreInfo.Size = 30;
	ScoreInfo.Position = Vector2(25.0f, 25.0f);

	//initilise the text with a font and settings
	ScoreText->InitText("Content/Fonts/GameOfSquids.ttf", ScoreInfo);

	//add the text to the game state
	ActivateTextObject(ScoreText);

	//Create a new text element for the lives text
	LivesText = new Text(StateRenderer);

	//initialise a width and height int
	int w, h = 0;

	//get the window size and set the width and height
	SDL_GetWindowSize(StateWindow, &w, &h);

	//adjust the starting setting
	STTextInfo LivesInfo;
	LivesInfo.TextStr = "Lives: ##";
	LivesInfo.Size = 30;
	//set the h position of the text using the height of the window
	LivesInfo.Position = Vector2(25.0f, static_cast<float>(h));

	LivesText->InitText("Content/Fonts/GameOfSquids.ttf", LivesInfo);

	//create a new position for the text accounting foe the height of the text then offsetting
	Vector2 NewTextPos;
	NewTextPos.x = LivesText->GetTextInfo().Position.x;
	NewTextPos.y = LivesText->GetTextInfo().Position.y - LivesText->GetTextInfo().Dimensions.y - 20.0f;

	//update to the new pos
	LivesText->SetTextPosision(NewTextPos);

	//add the lives text to the game state
	ActivateTextObject(LivesText);
}

void PlayState::ProcessInput(Input* PlayerInput)
{
	GameState::ProcessInput(PlayerInput);
}

void PlayState::Update(float DeltaTime)
{
	GameState::Update(DeltaTime);

	SpawnTimer += DeltaTime;


	//after 5sec spawm enemy then reset timer
	if (SpawnTimer > SpawnTime) {
		//set up variables to receive the app window width & height
		int WinWidth, WinHeight = 0;

		//use SDL function to set the dimentions
		SDL_GetWindowSize(StateWindow, &WinWidth, &WinHeight);

		//increase window width by 1
		WinWidth += 1;
		WinWidth -= 128;
		WinHeight += 1;

		//get a randon number between 0 and Window Width
		//rand() get random number between 0 and number after %
		int SpawnX = rand() % WinWidth;
		int SpawnY = rand() % WinHeight;

		//RANDOM ENEMIES
		//spawn an enemy based on a random screen x location
		Enemy* NewEnemy = new Enemy(Vector2(SpawnX, -128.0f), StateRenderer);

		//add the enemy to the game object stack
		SpawnGameObject(NewEnemy);

		//RANDOM COLECTABLES
		//spawn an collectable based on a random screen x location
		Collectable* NewCollectable = new Collectable(Vector2(SpawnX, SpawnY), StateRenderer);

		//add the collectable to the game object stack
		SpawnGameObject(NewCollectable);


		//reset timer to 0 and start again
		SpawnTimer = 0.0;
		SpawnTime *= 0.99;

		//wont let spawn timer spawn faster than 1 second
		if (SpawnTime < 1.0) {
			SpawnTime = 1.0;
		}
	}

	//update the score each frame
	ScoreText->SetText("Score: " + to_string(Game::GetGameInstance().GameScore));

	//update the lives text
	LivesText->SetText("Lives: " + to_string(PlayerCharacter->GetLives() - 1));

	//after score is obtained switch to game over
	if (Game::GetGameInstance().GameScore >= 600 || PlayerCharacter->GetLives() == 0){
		GameOverState* NewState = new GameOverState(StateWindow, StateRenderer);

		Game::GetGameInstance().GetGameState()->SwitchState(NewState);
	}
}

void PlayState::Draw(SDL_Renderer* Renderer)
{
	//draw void
	BGAnims->Draw(Renderer, 0, Vector2::Zero(), 0.0, 1.6f, false);
	//draw stars1
	BGAnims->Draw(Renderer, 1, Vector2::Zero(), 0.0, 1.6f, false);
	//draw star2
	BGAnims->Draw(Renderer, 2, Vector2::Zero(), 0.0, 1.6f, false);

	GameState::Draw(Renderer);
}

void PlayState::EndState()
{
	GameState::EndState();
	ScoreText = nullptr;

	//if BGM was assigned then stop music
	if (BGM != nullptr) {
		Mix_HaltMusic();
		Mix_FreeMusic(BGM);
	}
}
