#include "VMEngine2D/GameObjects/Components/CollisionComponent.h"
#include "VMEngine2D/GameObject.h"
#include "VMEngine2D/Game.h"
#include "VMEngine2D/GameState.h"

using namespace std;

CollisionComponent::CollisionComponent(GameObject* OwnerObject) : Components(OwnerObject)
{
	//assign the current game state to the collision component
	AttachedGameState = Game::GetGameInstance().GetGameState()->GetCurrentState();

}

CollisionComponent::~CollisionComponent()
{
	cout << "Delete Collision." << endl;

	//remove self from game when deleted
	AttachedGameState->RemoveCollisionFromState(this);
	
	//loop through all the collision when overlapping
	for (CollisionComponent* OtherCol : OverlappedCollisions) {
		//remove self from the overlapped collisions ~ overlapped collisions vector
		OtherCol->RemoveCollisionFromOverlapped(this);
	}
}

void CollisionComponent::Update()
{
	Components::Update();

	//folow the position of the parent game object
	Dimensions.Position = OwnerObject->Position;

	//loop all of the game colliders and detect intersecting colliders
	for (CollisionComponent* OtherCol : AttachedGameState->GetStateCollisions()) {
		//skip this collsion
		if (OtherCol == this) {
			continue; //will skip to the next item in the array
		}

		//convert
		SDL_FRect OtherRect;
		OtherRect.x = OtherCol->Dimensions.Position.x;
		OtherRect.y = OtherCol->Dimensions.Position.y;
		OtherRect.w = OtherCol->Dimensions.Width;
		OtherRect.h = OtherCol->Dimensions.Height;

		SDL_FRect ColRect;
		ColRect.x = Dimensions.Position.x;
		ColRect.y = Dimensions.Position.y;
		ColRect.w = Dimensions.Width;
		ColRect.h = Dimensions.Height;

		//check if this collider is in the overlapped collisions
		vector<CollisionComponent*>::iterator It = find(
			OverlappedCollisions.begin(), OverlappedCollisions.end(), OtherCol);

		//check if tis collision is interacting with the other collision
		if (SDL_HasIntersectionF(&ColRect, &OtherRect)) {
			//if not in overlappedcollosion
			if (It == OverlappedCollisions.end()) {
				//add object into overlapping collision
				OverlappedCollisions.push_back(OtherCol);
			}	
		}
		else {
			//if in overlappedcollosion
			if (It != OverlappedCollisions.end()) {
				OverlappedCollisions.erase(It); //remove It
			}
		}
	}
}

bool CollisionComponent::IsOverlappingAny()
{
	//return true if the size of the arrray larger 0
	return OverlappedCollisions.size() > 0;
}

bool CollisionComponent::IsOverlappingTag(const char* Tag)
{
	//loop through all the overlapped collisions
	for (CollisionComponent* OverCol : OverlappedCollisions) {
		//if any of the collisions have this tag then exit the function with true
		if (OverCol->GetOwner()->GetTag() == Tag) {
			return true;
		}
	}
	//if none of the collisions have the tag then exit the function with false
	return false;
}

vector<CollisionComponent*> CollisionComponent::GetOverlappedByTag(const char* Tag)
{
	vector<CollisionComponent*> TaggedCollisions;

	//loop through all the overlapped collsions
	for (CollisionComponent* OverCol : OverlappedCollisions) {
		//if it has the tag
		if (OverCol->GetOwner()->GetTag() == Tag) {
			//add collider into the local vector
			TaggedCollisions.push_back(OverCol);
		}
	}
	//return the array with only the tagged colliders
	return TaggedCollisions;
}

void CollisionComponent::RemoveCollisionFromOverlapped(CollisionComponent* Collision)
{
	if (OverlappedCollisions.size() <= 0) {
		return;
	}

	//eraze the component from the overlapped collisions and resizes the array
	OverlappedCollisions.erase(
		//this is like a find iterator function
		remove(OverlappedCollisions.begin(), OverlappedCollisions.end(), Collision),
		//this sets the new size of the array
		OverlappedCollisions.end()
	);
}

void CollisionComponent::OnActivated()
{
	//add itself into the game collision array
	AttachedGameState->AddCollisionToState(this);

	cout << "Collision Activated." << endl;

}
