#pragma once
#include "VMEngine2D/GameState.h"

#include "SDL2/SDL_mixer.h"

class Text;
class Player;
class AnimStateMachine;


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

	//hold background music
	Mix_Music* BGM;

	//hold the anim required to play
	AnimStateMachine* BGAnims;
};
