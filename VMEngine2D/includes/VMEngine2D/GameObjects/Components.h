#pragma once

class GameObject;

class Components {
public:
	Components(GameObject* OwnerToAttach);
	virtual ~Components();
	
	//contain all logic for the components
	virtual void Update();

	//other classes to test the owner
	GameObject* GetOwner() const { return OwnerObject; }

protected:
	//run before the first update
	virtual void OnActivated() {}

protected:
	//store the owner
	GameObject* OwnerObject;
private:
	//decide if the component update should run
	bool bHasAvtivated;

};