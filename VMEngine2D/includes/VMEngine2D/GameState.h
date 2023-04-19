#pragma once
#include <iostream>
#include <vector>

using namespace std;

struct SDL_Renderer;
struct SDL_Window;
class Input;
class GameObject;
class CollisionComponent;

class Text;

typedef vector<CollisionComponent*>::iterator ColIterator;

typedef vector<GameObject*>::iterator GOIterator;

class GameState {
public:
	GameState(SDL_Window* Window, SDL_Renderer* Renderer);
	~GameState();

	//game loop
	virtual void ProcessInput(Input* PlayerInput);

	virtual void Update(float DeltaTime);

	virtual void Draw(SDL_Renderer* Renderer);

	//add objects into the game state
	void Instantiate();

	void HandleGarbage();

	//add a collision component into the game state collisions stack
	void AddCollisionToState(CollisionComponent* Collision);

	//remove collision component from the game state collisions stack
	void RemoveCollisionFromState(CollisionComponent* Collision);

	//return the collisions for the current state
	vector<CollisionComponent*> GetStateCollisions() { return StateCollisions; }

	//run when the state update for the first time
	virtual void BeginState();

	//run when the the game state ended
	virtual void EndState();

	//return the state renderer
	SDL_Renderer* GetRenderer() const { return StateRenderer; }

	//return the state window
	SDL_Window* GetWindow() const { return StateWindow; }

	//add a object into the game stack
	void SpawnGameObject(GameObject* Object);

protected:
	//add gameobjects to the state
	void ActivateGameObject(GameObject* ObjectToAdd);

	//add text object to this state
	void ActivateTextObject(Text* TextToAdd);

protected:
	//store the window for this state
	SDL_Window* StateWindow;
	//the rendere assigned to this state
	SDL_Renderer* StateRenderer;
private:
	//all of the game objects specific to the state
	vector<GameObject*> StateGameObjects;

	//all of the game objects that will pawn on the next frame
	vector<GameObject*> ObjectToSpawn;

	//all of the collision components specific to the state
	vector<CollisionComponent*> StateCollisions;

	//hold all of the text objects in the state
	vector<Text*> StateTextObjects;

	//will determine when the begin play is activated
	bool bHasActivated;

};

//gamestatemachine class within the game state
class GameStateMachine {
public:
	GameStateMachine(GameState* StartingState);
	~GameStateMachine();

	//swith the current state with a new state
	void SwitchState(GameState* NewState);

	//add a state into the state stack
	//will not destroy the current state
	void PushState(GameState* NewState);

	//removw the last state that was added from the stack
	void PopState();

	//return the last added game state
	GameState* GetCurrentState() const {return GameStateStack.back(); }

private:
	vector<GameState*> GameStateStack;
};