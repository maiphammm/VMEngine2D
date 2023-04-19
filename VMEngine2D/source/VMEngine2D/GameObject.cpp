#include "VMEngine2D/GameObject.h"
#include <iostream>
#include "VMEngine2D/GameObjects/Components.h"
using namespace std;

GameObject::GameObject()
{
	Scale = 1.0f;
	Rotation = 0.0;
	Tag = "";
	bShouldDestroy = false;

	cout << "GameProject created" << endl;
}

GameObject::~GameObject()
{
	//delete all the components from memory
	for (Components* SingleComponent : AllComponents) {
		delete SingleComponent;
	}

	//resize the array
	AllComponents.clear();

	cout << "GameObject Destroyed" << endl;
}

void GameObject::AddComponent(Components* NewComponent)
{
	//make sure the component is not null
	if (NewComponent != nullptr) {
		AllComponents.push_back(NewComponent);
	}
	else {
		//error log
		cout << "Attempted to add nullptr component to the component stack" << endl;
	}
}

void GameObject::Update() {
	//update all the components logic for ach component attached to the gameobject
	for (Components* SingleComponent : AllComponents) {
		SingleComponent->Update();
	}
}