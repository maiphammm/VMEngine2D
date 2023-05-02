#include "VMEngine2D/GameObjects/Characters/Player.h"
#include "VMEngine2D/Input.h"
#include "VMEngine2D/AnimStateMachine.h"
#include "VMEngine2D/Game.h"
#include "VMEngine2D/GameObjects/Components/PhysicsComponent.h"
#include "VMEngine2D/GameObjects/Components/CollisionComponent.h"
#include "VMEngine2D/GameObjects/Projectile.h"
#include "VMEngine2D/GameState.h"
#include "SDL2/SDL_mixer.h"

using namespace std;

Player::Player(Vector2 StartPosition, SDL_Renderer* Renderer)
	: Character(StartPosition)
{
	BoostersIndex = PlayerAnims::BOOSTERS_IDLE;
	Scale = 1.5f;
	Physics->MaxVelocity = 300.0f;
	Physics->Drag = 5.0f;
	ShootSFXIndex = 0;
	Lives = 3;

	Collision->Dimensions.Height = 45.0f;
	Collision->Dimensions.Width = 45.0f;

	Collision->Dimensions.Offset = Vector2(13.0f, 13.0f);

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

	//load our audio files into their variables
	sfx_Shoot[0] = Mix_LoadWAV("Content/Audio/SFX/Shoot_01.wav");

	//error check
	if (sfx_Shoot[0] == NULL) {
		cout << "Couldnt load Shoot 1" << endl;
	}
	
	sfx_Shoot[1] = Mix_LoadWAV("Content/Audio/SFX/Shoot_02.wav");

	//error check
	if (sfx_Shoot[1] == NULL) {
		cout << "Couldnt load Shoot 2" << endl;
	}

	//adjust volume chunk of each chunk
	Mix_VolumeChunk(sfx_Shoot[0], 25);
	Mix_VolumeChunk(sfx_Shoot[1], 25);
}

Player::~Player()
{
	//remove the audio files from the game
	if (sfx_Shoot[0] != nullptr) {
		Mix_FreeChunk(sfx_Shoot[0]);
	}
	if (sfx_Shoot[1] != nullptr) {
		Mix_FreeChunk(sfx_Shoot[1]);
	}
}

void Player::ProcessInput(Input* PlayerInput)
{
	//set the boosters to idle by default
	BoostersIndex = PlayerAnims::BOOSTERS_IDLE;

	//set the player to idle movements by default
	MovementDir = Vector2::Zero(); //Vector2(0.0f, 0.0f)

	//Default idle rotation at up
	Rotation = 0.0;

	//Update the iput direction based on the inputs being pressed
	if (PlayerInput->IsKeyDown(SDL_SCANCODE_W)) {
		//set input y to up
		MovementDir.y = -1.0f;
	}
	if (PlayerInput->IsKeyDown(SDL_SCANCODE_S)) {
		//set input y to down
		MovementDir.y = 1.0f;
	}
	if (PlayerInput->IsKeyDown(SDL_SCANCODE_A)) {
		//set input x to left
		MovementDir.x = -1.0f;
	}
	if (PlayerInput->IsKeyDown(SDL_SCANCODE_D)) {
		//set input x to right
		MovementDir.x = 1.0f;
	}

	//if we are moving
	if (MovementDir.Length() > 0.0f) {
		BoostersIndex = PlayerAnims::BOOSTERS_POWER;
	}

	static float FireTimer = 0.25f;
	FireTimer += Game::GetGameInstance().GetFDeltaTime();

	if (PlayerInput->IsKeyDown(SDL_SCANCODE_SPACE) && FireTimer >= 0.1f) {
		Projectile* P = new Projectile();

		P->Position = Position;
		P->Position.x += 15.0f;
		P->Position.y += 10.0f;
		P->Acceleration = 2500.0f;
		P->Direction = Vector2(0.0f, -1.0f);
		P->TargetTag = "Enemy";

		Game::GetGameInstance().GetGameState()->GetCurrentState()->SpawnGameObject(P);

		P = new Projectile();

		P->Position = Position;
		P->Position.x += 45.0f;
		P->Position.y += 10.0f;
		P->Acceleration = 2500.0f;
		P->Direction = Vector2(0.0f, -1.0f);
		P->TargetTag = "Enemy";

		Game::GetGameInstance().GetGameState()->GetCurrentState()->SpawnGameObject(P);

		FireTimer = 0.0f;

		//plays a single sfx (Mix_Chunk*)
		//@param 1 - Channel. if this is -1 then it will play in the next available channel
		//@param 2 - the sfx (Mix_Chunk*)
		//@param 3 - how many loops should the sfx play, 0 means none
		if (Mix_PlayChannel(-1, sfx_Shoot[ShootSFXIndex], 0) == -1) {
			cout << "Shoot sfx failed to play" << endl;
		}

		//increment the index by 1
		ShootSFXIndex++;

		//if th index goes to 2 or higher then set the index to 0
		if (ShootSFXIndex > 1) {
			ShootSFXIndex = 0;
		}
	}
}

void Player::Update()
{
	//call to the parent function
	Character::Update();

	Physics->AddForce(MovementDir, 10000.0f);

	if (Collision->IsOverlappingTag("Enemy")) {
		bOverlapDetected = true;

		//getting all overlapped enemies and destroy them
		for (CollisionComponent* Enemy : Collision->GetOverlappedByTag("Enemy")) {
			//if the enemy is not being destroyed
			if (!Enemy->GetOwner()->ShouldDestroy()) {
				//destroy the enemy
				dynamic_cast<Character*>(Enemy->GetOwner())->RemoveLives(1);
				
				//remove life from the player
				RemoveLives(1);
			}
		}
	}
	else if (Collision->IsOverlappingTag("Collectable")) {
		bOverlapDetected = true;

		//getting all overlapped collectables and destroy them
		for (CollisionComponent* Collectable : Collision->GetOverlappedByTag("Collectable")) {
			//if the enemy is not being destroyed
			if (!Collectable->GetOwner()->ShouldDestroy()) {
				//destroy the collectable
				Collectable->GetOwner()->DestroyGameObject();
				//added point to the game
				Game::GetGameInstance().GameScore += 5;
			}
		}
	}
	else {
		bOverlapDetected = false;
	}

	float WallBot = 440.0f;
	float WallTop = 0.0f;
	float WallLeft = 0.0f;
	float WallRight = 920.0f;

	if (Position.x > WallRight) {
		Position.x = WallRight;
	}
	if (Position.x < WallLeft) {
		Position.x = WallLeft;
	}
	if (Position.y < WallTop) {
		Position.y = WallTop;
	}
	if (Position.y > WallBot) {
		Position.y = WallBot;
	}
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
