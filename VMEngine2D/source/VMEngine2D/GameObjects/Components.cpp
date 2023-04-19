#include "VMEngine2D/GameObjects/Components.h"
#include "VMEngine2D/GameObject.h"


Components::Components(GameObject* OwnerToAttach)
{
	bHasAvtivated = false;

	//set the game object that owns this component and save it
	OwnerObject = OwnerToAttach;
	//attach this component to the owner gameobject
	OwnerObject->AddComponent(this);
}

Components::~Components()
{
	if (OwnerObject != nullptr) {
		OwnerObject = nullptr;
	}
}

void Components::Update()
{
	//check if this component has been activated, 
	//if not then set it to activated and run the activated function
	//this will only run once per spawn
	if (!bHasAvtivated) {
		bHasAvtivated = true;
		OnActivated();
	}
}




