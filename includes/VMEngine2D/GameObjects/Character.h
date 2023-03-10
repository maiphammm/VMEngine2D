#pragma once
#include "VMEngine2D/GameObject.h"

class AnimStateMachine;
struct STAnimationData;

class Character :
public GameObject{
public:
	Character(Vector2 StartPosition);
	~Character();

	//Virtual allows for derived callses to override
	//override changes the definition of the parent method to this class
	virtual void Draw(SDL_Renderer* Renderer) override;

	//Add an animation into the Animation State Machine
	void AddAnimation(SDL_Renderer* Renderer, const char* SpriteSheetPath, STAnimationData AnimationData);

protected:
	//Store all animarions
	AnimStateMachine* CharacterAnimations;

	//Animation index used by the amin state machine
	unsigned int AnimIndex;

	//flip the animation
	bool bFlipped;

	//Maximum velocity/speed
	float MaxMoveSpeed;

};