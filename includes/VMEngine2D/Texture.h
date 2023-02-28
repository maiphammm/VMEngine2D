#pragma once
#include "SDL2/SDL.h"

class Vector2;

class Texture {
public:
	Texture();
	~Texture();

	//load an image from a file path
	bool LoadImageFromFile(const char* Path, SDL_Renderer* SdlRenderer);

	//render the image to the app window
	void Draw(
		SDL_Renderer* SdlRenderer, //renderer
		Vector2 Position,		//the position on the screen
		SDL_Rect* SourceRect,	//the clip amount of the texture
		float Scale = 1.0f,			//how much to scale the image
		bool bFlip = false				//if it should flip horizontally
	);

	//get the width and height of the texture
		SDL_Rect GetDimensions() const { return TextureDimensions; }

	//Reset the texture and remove the image attached to it
	void ResetTexture();

private:
	//stores the dimensions of the texture
	SDL_Rect TextureDimensions;

	//stores the texture
	SDL_Texture* SdlTexture;
};