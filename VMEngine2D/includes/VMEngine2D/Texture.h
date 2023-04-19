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
		SDL_Renderer* SdlRenderer,	//@param1 - renderer
		Vector2 Position,			//@param2 - the position on the screen
		double Rolation,			//@param3 - the rotation of the texture
		SDL_Rect* SourceRect,		//@param4 - the clip amount of the texture
		float Scale = 1.0f,			//@param5 - how much to scale the image
		bool bFlip = false			//@param6 - if it should flip horizontally
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