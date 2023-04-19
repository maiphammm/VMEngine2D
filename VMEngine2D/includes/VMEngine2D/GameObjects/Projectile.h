#pragma once
#include "VMEngine2D/GameObject.h"
#include "VMEngine2D/Vector2.h"

class AnimStateMachine;
class PhysicsComponent;
class CollisionComponent;

class Projectile :
	public GameObject {
public:
	Projectile();
	virtual ~Projectile();

	virtual void Update() override;

	virtual void Draw(SDL_Renderer* Renderer) override;

	//time until the death of the projectile
	float DeathTimer;

	//how fast the projectile achieves it's max speed
	float Acceleration;

	//which direction the projectile moves in
	Vector2 Direction;

	//rolate the image
	double Rotation;

	//scale image
	float Scale;

	//any character that has this tag will take damage
	const char* TargetTag;

protected:
	//store the main texture/animation for the projectile
	AnimStateMachine* Animations;

	//store the collision for the projectile
	CollisionComponent* Collision;

	//driver or the position of the projectile
	PhysicsComponent* Physics;


};