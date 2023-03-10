#include "VMEngine2D/GameObject.h"
#include <iostream>
using namespace std;

GameObject::GameObject()
{
	Scale = 1.0f;
	Rotation = 0.0;

	cout << "GameProject created" << endl;
}

GameObject::~GameObject()
{
	cout << "GameObject Deestroyed" << endl;
}
