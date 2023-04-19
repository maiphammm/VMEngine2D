#pragma once
#include"VMEngine2D/GameObjects/Components.h"
#include"VMEngine2D/Vector2.h"
#include <iostream>
#include <vector>

class GameState;

using namespace std;

struct STColDimensions {
	float Width = 25.0f;
	float Height = 25.0f;
	Vector2 Position;
};

class CollisionComponent :
	public Components {
public:
	CollisionComponent(GameObject* OwnerObject);
	~CollisionComponent();

	void Update() override;

	//return true if any collision is overlapped
	bool IsOverlappingAny();

	//return true if collision is overlapping gameobject with tag
	bool IsOverlappingTag(const char* Tag);
	//return the gambeobject wthis collision is overlapping with this tag
	vector<CollisionComponent*> GetOverlappedByTag(const char* Tag);

	//remove a collider from the overlapped collisions
	void RemoveCollisionFromOverlapped(CollisionComponent* Collision);

protected:
	void OnActivated() override;

public:
	//Dimensions and position for the Collision
	STColDimensions Dimensions;

	//Store the colliders that are being overlapped
	vector<CollisionComponent*> OverlappedCollisions;

private:
	//this is the game state that the collision spawned into
	GameState* AttachedGameState;

};