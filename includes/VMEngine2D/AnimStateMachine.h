#pragma once
#include "Animation.h"
#include <iostream>
#include <vector>
using namespace std;

class AnimStateMachine {
public:
	AnimStateMachine();
	~AnimStateMachine();

	//add an animation to the vector array of Animations
	void AddAnimation(SDL_Renderer* Renderer, const char* SpriteSheetPath, STAnimationData AnimationData);

	//draw the animation based on the anim index via the vector array of Animations
	void Draw(SDL_Renderer* Renderer, unsigned int AnimIndex, Vector2 Position,double Rotation, float Scale, bool bFlip);

	vector<Animation*> GetAnimations() const;

private:
	//hold an array of animation objects
	vector<Animation*> Animations;
};