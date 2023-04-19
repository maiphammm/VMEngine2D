#include "VMEngine2D/Animation.h"
#include "VMEngine2D/Vector2.h"
#include "VMEngine2D/Game.h"
#include <iostream>
#include <algorithm>
using namespace std;


Animation::Animation(SDL_Renderer* Renderer, const char* SpriteSheetPath, STAnimationData AnimationData)
{
	SpriteSheet = nullptr;
	this->AnimationData = AnimationData;
	CurrentFrame = AnimationData.StartFrame;
	AnimationTimer = 0.0;

	//create the texture
	SpriteSheet = new Texture();
	//load image spritesheet based on the file path
	SpriteSheet->LoadImageFromFile(SpriteSheetPath, Renderer);

	//set the width of the frame position
	FramePos.w = SpriteSheet->GetDimensions().w / max(1u, AnimationData.MaxFrames);

	//set the height at the height of the texture
	FramePos.h = SpriteSheet->GetDimensions().h;

	//set the possition of the x on the clip rectangle to the correct frame location
	FramePos.x = FramePos.w * CurrentFrame;
}

Animation::~Animation()
{
	delete SpriteSheet;
}

void Animation::UpdateAnimationTimer()
{
	//add time to the animation timer each frame
	AnimationTimer += Game::GetGameInstance().GetDeltaTime();

	//if FPS is 0 then there is no need to change the frame
	if (AnimationData.FPS == 0.0) {
		return;
	}

	//calculate how long we should wait before ticking to the next frame based on FPS (Frame Per Sencond)
	double TimePerFrame = 1.0 / static_cast<double>(AnimationData.FPS);

	//if the timer has reach the amount of time to switch frames
	//run the frame update function
	if (AnimationTimer >= TimePerFrame) {
		AnimationTimer = 0.0;
		OnFrameUpdate();
	}
}

void Animation::OnFrameUpdate()
{
	//if the current frame is not the last frame then tick to the next frame
	if (CurrentFrame < AnimationData.EndFrame) {
		CurrentFrame++;
	}
	else {
		//reset the frame to the first frame if we are at the end of the animation frames
		CurrentFrame = AnimationData.StartFrame;
	}

	//update the frame pos x
	FramePos.x = FramePos.w * CurrentFrame;
}

void Animation::Draw(SDL_Renderer* Renderer, Vector2 Position,double Rotation, float Scale, bool bFlip)
{
	UpdateAnimationTimer();

	//draw the texture with the clip rext and updated frame pos
	SpriteSheet->Draw(Renderer, Position, Rotation, &FramePos, Scale, bFlip);
}
