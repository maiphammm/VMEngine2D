#pragma once
#include "VMEngine2D/GameObject.h"

class AnimStateMachine;
struct STAnimationData;
class PhysicsComponent;
class CollisionComponent;

class Character :
public GameObject{
public:
	Character(Vector2 StartPosition);
	~Character();

	//override parent Update
	virtual void Update() override;

	//Virtual allows for derived callses to override
	//override changes the definition of the parent method to this class
	virtual void Draw(SDL_Renderer* Renderer) override;

	//Add an animation into the Animation State Machine
	void AddAnimation(SDL_Renderer* Renderer, const char* SpriteSheetPath, STAnimationData AnimationData);

	//get the lives of the player
	unsigned int GetLives() const { return Lives; }

	//set the characters lives
	void SetLives(unsigned int NewLives) { Lives = NewLives; }

	//increse the lives by the amount added
	void AddLives(int Amount);

	//decrese the lives by the amount added
	void RemoveLives(int Amount);

protected:
	//Store all animarions
	AnimStateMachine* CharacterAnimations;

	//direction
	Vector2 MovementDir;

	//Animation index used by the amin state machine
	unsigned int AnimIndex;

	//flip the animation
	bool bFlipped;

	//store a reference to the physics component
	PhysicsComponent* Physics;

	//store a reference to the Collision component
	CollisionComponent* Collision;

	//register the overlap as detected and change to green
	bool bOverlapDetected;

	//show collision if true
	bool bDebugCollision;

	//lives for player when 0 game ends
	unsigned int Lives;
};