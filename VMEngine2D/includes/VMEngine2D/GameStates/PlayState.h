#pragma once
#include "VMEngine2D/GameState.h"

class Text;
class Player;

class PlayState :
	public GameState {
public:
	PlayState(SDL_Window* Window, SDL_Renderer* Renderer);

	void BeginState() override;

	void ProcessInput(Input* PlayerInput) override;

	void Update(float DeltaTime) override;

	void Draw(SDL_Renderer* Renderer) override;

	void EndState() override;

protected:
	//store the text for the score
	Text* ScoreText;
	//Store the text for the lives
	Text* LivesText;

	//enemy spawn timer
	double SpawnTimer;

	//time to spawn enemies at
	double SpawnTime;

	//store the player character
	Player* PlayerCharacter;

};
