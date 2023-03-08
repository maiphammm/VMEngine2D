#pragma once
#include "VMEngine2D/GameObject.h"

class AnimStateMachine;
struct STAnimationData;

class Character :
public GameObject{
public:
	Character(Vector2 StartPosition);
	~Character();

	//override he process input othod/function in the GameObject base class
	virtual void ProcessInput(Input* PlayerInput) override;

	virtual void Update() override;

	virtual void Draw(SDL_Renderer* Renderer) override;

	//Add an animation into the Animation State Machine
	void AddAnimation(SDL_Renderer* Renderer, const char* SpriteSheetPath, STAnimationData AnimationData);

protected:
	//Store all animarions
	AnimStateMachine* CharacterAnimations;

	//Animation index used by the amin state machine
	unsigned int AnimIndex;

	//Scale of the object
	float Scale;

	//flip the animation
	bool bFlipped;

	//Maximum velocity/speed
	float MaxMoveSpeed;

};