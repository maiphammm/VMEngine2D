#pragma once
#include "Vector2.h"

class Input;
struct SDL_Renderer;

class GameObject {
public:
	GameObject();
	//Destructor needs to be virtual or the inherited class destructor wont run
	virtual ~GameObject();

	//handle the input detection for this game object
	virtual void ProcessInput(Input* PlayerInput){}

	//run the logic of the game object
	virtual void Update() {}

	//render the game object
	virtual void Draw(SDL_Renderer* Rendere) {}
protected:
	//Screen position of the game object
	Vector2 Position;

	//Scale of the object
	float Scale;

	//Rotation of the whole object
	double Rotation;
};