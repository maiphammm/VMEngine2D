#include "VMEngine2D/AnimStateMachine.h"
#include "VMEngine2D/Vector2.h"

AnimStateMachine::AnimStateMachine()
{
	Animations = vector<Animation*>();
}

AnimStateMachine::~AnimStateMachine()
{
	cout << "Destroyed Animation State Machine..." << endl;
	//run through each item in the vector array
	for (Animation* Anim : Animations) {
		delete Anim;
	}

	//clear vector
	Animations.clear();
}

void AnimStateMachine::AddAnimation(SDL_Renderer* Renderer, const char* SpriteSheetPath, STAnimationData AnimationData)
{
	Animation* NewAnim = new Animation(Renderer, SpriteSheetPath, AnimationData);

	//add it into the Animations array
	Animations.push_back(NewAnim);
}

void AnimStateMachine::Draw(SDL_Renderer* Renderer, unsigned int AnimIndex, Vector2 Position, double Rotation, float Scale, bool bFlip)
{
	//make sure there is an item in the array at that index
	if (Animations.size() > AnimIndex && Animations[AnimIndex] != nullptr) {
		//draw the correct animation based on the Index
		Animations[AnimIndex]->Draw(Renderer, Position, Rotation, Scale, bFlip);
	}	
}

vector<Animation*> AnimStateMachine::GetAnimations() const
{
	return Animations;
}
