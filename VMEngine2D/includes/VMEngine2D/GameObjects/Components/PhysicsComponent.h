#pragma once

#include "VMEngine2D/GameObjects/Components.h"
#include "VMEngine2D/Vector2.h"

class PhysicsComponent :
	public Components {
public:
	PhysicsComponent(GameObject* OwnerToAttach);
	
	void Update() override;

	//Add acceleration in a direction multiplied by a strength force
	void AddForce(Vector2 Direction, float Force);
public:
	//Current speed
	Vector2 Velocity;

	//maximum possible speed for the Velocity
	float MaxVelocity;

	//How fast are we going to reach max velocity
	Vector2 Acceleration;

	//How fast the Velocity decelerates
	float Drag;
};