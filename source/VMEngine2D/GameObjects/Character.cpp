#include "VMEngine2D/GameObjects/Character.h"
#include "VMEngine2D/AnimStateMachine.h"
#include <iostream>
#include "VMEngine2D/Input.h"
using namespace std;

Character::Character(Vector2 StartPosition)
{
	CharacterAnimations = new AnimStateMachine();
	AnimIndex = 0;
	MaxMoveSpeed = 150.0f;
	Scale = 2.0f;
	bFlipped = false;
	Position = StartPosition;

	cout << "Character created." << endl;
}

Character::~Character()
{
	//remove the anim state machine from memory
	delete CharacterAnimations;
	cout << "Character Destroyed." << endl;
}

void Character::ProcessInput(Input* PlayerInput)
{
	//set the AnimIndex to play first animation by default
	AnimIndex = 0;
	
	//if we are holding down W the play second animation instead
	if (PlayerInput->IsKeyDown(SDL_SCANCODE_W)) {
		AnimIndex = 1;
	}
}

void Character::Update()
{
}

void Character::Draw(SDL_Renderer* Renderer)
{
	//draw the animations for the character
	CharacterAnimations->Draw(Renderer, AnimIndex, Position, Scale, bFlipped);
}

void Character::AddAnimation(SDL_Renderer* Renderer, const char* SpriteSheetPath, STAnimationData AnimationData)
{
	//Add an animation to anim state machine using the anim scale machine function
	CharacterAnimations->AddAnimation(Renderer, SpriteSheetPath, AnimationData);
}
