#pragma once
#include "Vector2.h"
#include <iostream>
#include<vector>
using namespace std;

class Input;
struct SDL_Renderer;
class Components;

//change the name of the type to reuse simpler wording
//the complier will read "ComponentStack" as "vector<Components*>"
typedef vector<Components*> ComponentStack;

class GameObject {
public:
	GameObject();
	//Destructor needs to be virtual or the inherited class destructor wont run
	virtual ~GameObject();

	//handle the input detection for this game object
	virtual void ProcessInput(Input* PlayerInput){}

	//run the logic of the game object
	virtual void Update();

	//render the game object
	virtual void Draw(SDL_Renderer* Rendere) {}

	//add a component into the component stack
	void AddComponent(Components* NewComponent);

	//return the tag of the game object
	const char* GetTag() const { return Tag; }

	//set the gameobject to be destroyed in the handle garbage function
	void DestroyGameObject() { bShouldDestroy = true; }

	//get the should destroy boolean
	bool ShouldDestroy() const { return bShouldDestroy; }

protected:
	//Scale of the object
	float Scale;

	//Rotation of the whole object
	double Rotation;

	//store an array of components
	ComponentStack AllComponents;

	//tag the game object for detection
	const char* Tag;

public:
	//Screen position of the game object
	Vector2 Position;

private:
	//if set game should destroy the object
	bool bShouldDestroy;
};