#include "VMEngine2D/GameObjects/Components/PhysicsComponent.h"
#include "VMEngine2D/GameObject.h"
#include "VMEngine2D/Game.h"
#include <iostream>
using namespace std;

PhysicsComponent::PhysicsComponent(GameObject* OwnerToAttach) : Components(OwnerToAttach)
{
	MaxVelocity = 150.0f;
	Drag = 1.0f;
}

void PhysicsComponent::Update()
{
	//increase velocity by the current acceleration
	Velocity += Acceleration * Game::GetGameInstance().GetFDeltaTime();


	if (Velocity.Length() > MaxVelocity) {
		//setting veloctity to itself normalised which will return a value between -1 and 1 in the x and y
		//multiplying the normalised value by the max velocity to set the x and y to max
		Velocity = Velocity.Normalised() * MaxVelocity;
	}

	//min() will choose the smaller number
	//if drag * DeltaTime is greater than 1 for some reason min() will correct the number and cap it at 1.0f
	//because we are multiplying by delta time we wont know what number will reach above 1
	float DragScale = min(Drag * Game::GetGameInstance().GetFDeltaTime(), 1.0f);

	//multiplying velocity by a number below 1 and above 0 to make velocity smaller over time
	Vector2 DragVelocity = Velocity * DragScale;

	//remove velocity from DragVelocity
	Velocity -= DragVelocity;

	//move the gameobject based on velocity
	OwnerObject->Position += Velocity * Game::GetGameInstance().GetFDeltaTime();

	//reset Acceleration each frame
	Acceleration = Vector2::Zero();
}

void PhysicsComponent::AddForce(Vector2 Direction, float Force)
{
	//normalise the direction and miltiply it by force
	Acceleration = Direction.Normalised() * Force;
}
