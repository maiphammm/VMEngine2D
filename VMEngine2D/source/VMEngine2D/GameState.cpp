#include "VMEngine2D/GameState.h"
#include "VMEngine2D/GameObject.h"
#include "SDL2/SDL.h"
#include "VMEngine2D/Text.h"


GameState::GameState(SDL_Window* Window, SDL_Renderer* Renderer)
{
	StateWindow = Window;
	StateRenderer = Renderer;
	bHasActivated = false;
}

GameState::~GameState()
{
	EndState();

	//remove any of the text objects in the state
	for (Text* SingleText : StateTextObjects) {
		delete SingleText;
	}

	StateTextObjects.clear();

	for (GameObject* SingleObject : ObjectToSpawn) {
		delete SingleObject;
	}

	ObjectToSpawn.clear();
}

void GameState::ProcessInput(Input* PlayerInput)
{
	//stop function if not activated the state
	if (!bHasActivated) {
		return;
	}
	//process the input of each GameObject
	for (GameObject* SingleGameObject : StateGameObjects) {
		SingleGameObject->ProcessInput(PlayerInput);
	}
}

void GameState::Update(float DeltaTime)
{
	//run on the first update
	if (!bHasActivated) {
		bHasActivated = true;
		BeginState();
	}

	//run the game object logic
	for (GameObject* SingleGameObject : StateGameObjects) {
		SingleGameObject->Update();
	}

}

void GameState::Draw(SDL_Renderer* Renderer)
{
	//dont draw if not activated the state
	if (!bHasActivated) {
		return;
	}
	
	//cycle through all of the game objects in the AllGameObjects
	//each loop reassign the SingleGameObject pointer with the next item in the array
	for (GameObject* SingleGameObject : StateGameObjects) {
		//each loop run the draw function for the assigned gameobject
		SingleGameObject->Draw(Renderer);
	}

	//draw all text objects in the state and make sure to draw them last
	//so that they draw on top of the game object
	for (Text* SingleText : StateTextObjects) {
		SingleText->Draw(Renderer);
	}

}

void GameState::Instantiate()
{
	//insert is inserting the whole objects to spawn list into the state game objects at the beginning of the array
	StateGameObjects.insert(StateGameObjects.begin(), ObjectToSpawn.begin(), ObjectToSpawn.end());

	//remove the objects from the objects to spawn list
	ObjectToSpawn.clear();
}

void GameState::HandleGarbage()
{
	//stop function if not activated
	if (!bHasActivated) {
		return;
	}

	//loop through all of he gameobject and assign the iterator each loop
	for (GOIterator Object = StateGameObjects.begin(); Object != StateGameObjects.end();) {
		//if the object is not marked for delete then incement and skip to the next one
		if (!(*Object)->ShouldDestroy()) {
			Object++;
			continue;
		}

		//delete the game object
		delete* Object;

		//remove the object from the array and resize the array
		Object = StateGameObjects.erase(Object);

		cout << "Deleted game object." << endl;
	}
}

void GameState::AddCollisionToState(CollisionComponent* Collision)
{
	//add a collision into the StateCollisions stack
	StateCollisions.push_back(Collision);
}

void GameState::RemoveCollisionFromState(CollisionComponent* Collision)
{
	//find function finds and object the data using the object in a vector stack 
	//param1: look from the start of the array
	//param2: to the end of the array
	//param3: the object that we are searching for
	ColIterator ColToRemove = find(StateCollisions.begin(), StateCollisions.end(), Collision);

	//the find function will set the iterator to AllColliders.end() is it didnt find anything
	if (ColToRemove == StateCollisions.end()) {
		return;//kill the rest of the function
	}
	//remove the collider if the find function found the collider
	StateCollisions.erase(ColToRemove);
}

void GameState::BeginState()
{
	//when the state start
}

void GameState::EndState()
{
	//mark all gameobjects for deletioc
	for (GameObject* SingleGameObject : StateGameObjects) {
		SingleGameObject->DestroyGameObject();
	}

	//run the handle garbage to delete them
	HandleGarbage();
}

void GameState::SpawnGameObject(GameObject* Object)
{
	ObjectToSpawn.push_back(Object);
}

void GameState::ActivateGameObject(GameObject* ObjectToAdd)
{
	StateGameObjects.push_back(ObjectToAdd);
}

void GameState::ActivateTextObject(Text* TextToAdd)
{
	StateTextObjects.push_back(TextToAdd);
}

//GAME STATE MACHINE

GameStateMachine::GameStateMachine(GameState* StartingState)
{
	SwitchState(StartingState);
}

GameStateMachine::~GameStateMachine()
{
	//run through all the states, end them then delete them
	for (GameState* SingleGameState : GameStateStack) {
		delete SingleGameState;
	}
	//clear the stack
	GameStateStack.clear();
}

void GameStateMachine::SwitchState(GameState* NewState)
{
	//take out the current top state
	PopState();
	//add in a new state
	PushState(NewState);
}

void GameStateMachine::PushState(GameState* NewState)
{
	//add the state to the top of the stack
	GameStateStack.push_back(NewState);
}

void GameStateMachine::PopState()
{
	if (GameStateStack.size() > 0) {
		//cache the old state so we can delete it after it's removed
		GameState* OldState = GetCurrentState();
		//remove it from the stack
		GameStateStack.pop_back();
		// aend the old state then delete it
		OldState->EndState();
		delete OldState;
	}
}
