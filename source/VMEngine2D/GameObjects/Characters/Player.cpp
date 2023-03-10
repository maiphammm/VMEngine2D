#include "VMEngine2D/GameObjects/Characters/Player.h"
#include "VMEngine2D/Input.h"
#include "VMEngine2D/AnimStateMachine.h"
#include "VMEngine2D/Game.h"

using namespace std;

Player::Player(Vector2 StartPosition, SDL_Renderer* Renderer)
	: Character(StartPosition)
{
	BoostersIndex = PlayerAnims::BOOSTERS_IDLE;
	Scale = 3.0f;
	MaxMoveSpeed = 300.0f;

	STAnimationData AnimData = STAnimationData();
	AnimData.FPS = 0;

	//Add ship texture into AnimState - 0
	AddAnimation(Renderer,
		"Content/Images/MainShip/Bases/Base - Full health.png",
		AnimData);

	//Add the engine to the ship into AnimState - 1
	AddAnimation(Renderer,
		"Content/Images/MainShip/Engines/Engines - Supercharged Engine.png",
		AnimData);

	//Update AnimData to handle engine animations - 2
	AnimData.FPS = 24;
	AnimData.MaxFrames = 4;
	AnimData.EndFrame = 3;

	//Add the boosters idle animation to AnimState - 3
	AddAnimation(Renderer,
		"Content/Images/MainShip/EngineEffects/Supercharged Engine - Idle.png",
		AnimData);
	
	//Add the boosters powered animation to AnimState - 4
	AddAnimation(Renderer,
		"Content/Images/MainShip/EngineEffects/Supercharged Engine - Powering.png",
		AnimData);

}

Player::~Player()
{
}

void Player::ProcessInput(Input* PlayerInput)
{
	//set the boosters to idle by default
	BoostersIndex = PlayerAnims::BOOSTERS_IDLE;

	//set the player to idle movements by default
	InputDir = Vector2::Zero(); //Vector2(0.0f, 0.0f)

	//Default idle rotation at up
	Rotation = 0.0;

	//Update the iput direction based on the inputs being pressed
	if (PlayerInput->IsKeyDown(SDL_SCANCODE_W)) {
		//set input y to up
		InputDir.y = -1.0f;
	}
	if (PlayerInput->IsKeyDown(SDL_SCANCODE_S)) {
		//set input y to down
		InputDir.y = 1.0f;
	}
	if (PlayerInput->IsKeyDown(SDL_SCANCODE_A)) {
		//set input x to left
		InputDir.x = -1.0f;
		//make the player look right
		Rotation = -90.0;
	}
	if (PlayerInput->IsKeyDown(SDL_SCANCODE_D)) {
		//set input x to right
		InputDir.x = 1.0f;
		//make the player look left
		Rotation = 90.0;
	}

	//if we are moving
	if (InputDir.Length() > 0.0f) {
		BoostersIndex = PlayerAnims::BOOSTERS_POWER;
	}
}

void Player::Update()
{
	//set the direction based on input and move speed
	Vector2 Direction = InputDir.Normalised() * MaxMoveSpeed;

	//Move the player based on time
	Position += Direction * Game::GetGameInstance().GetFDeltaTime();
}

void Player::Draw(SDL_Renderer* Renderer)
{
	//Draw the engine to the screen
	CharacterAnimations->Draw(Renderer, PlayerAnims::ENGINE_SUPER, Position, Rotation, Scale, bFlipped);

	//Draw and play the relevent booster animation
	CharacterAnimations->Draw(Renderer, BoostersIndex, Position, Rotation, Scale, bFlipped);

	//Make sure the character draw method still runs
	Character::Draw(Renderer);

}
