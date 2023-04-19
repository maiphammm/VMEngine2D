#include "VMEngine2D/Texture.h"
#include "VMEngine2D/Vector2.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <string>
using namespace std;

Texture::Texture()
{
	//intialise the texture as null
	SdlTexture = nullptr;
	//set the texture dimensions to the default 0 for everything
	TextureDimensions = SDL_Rect();
}

Texture::~Texture()
{
	ResetTexture();

	cout << "Destroyed Texture..." << endl;
}

bool Texture::LoadImageFromFile(const char* Path, SDL_Renderer* SdlRenderer)
{
	if (SdlTexture == nullptr) {
		//load the image into a surface
		SDL_Surface* LoadedSurface = IMG_Load(Path);

		if (LoadedSurface != nullptr) {
			//create the texture from the surface
			SdlTexture = SDL_CreateTextureFromSurface(SdlRenderer, LoadedSurface);

			if (SdlTexture != nullptr) {
				cout << "Texture successfully loaded!" << endl;

				//Assign the dimensions of the texture
				TextureDimensions.w = LoadedSurface->w;
				TextureDimensions.h = LoadedSurface->h;
			}
			else {
				cout << "Could not create texture from surface: " << SDL_GetError() << endl;
			}
		}
		else {
			cout << "Could not load file to surface..." << endl;
		}
	}
	else {
		//if already a texture - remove it then aply new texture
		ResetTexture();
		LoadImageFromFile(Path, SdlRenderer);
	}

	//return false if the texture wasn't set
	return SdlTexture != nullptr;
}

void Texture::Draw(SDL_Renderer* SdlRenderer, Vector2 Position,double Rotation, 
	SDL_Rect* SourceRect, float Scale, bool bFlip)
{
	//set the rendering space and render the dimensions of the texture
	//i.e. clip the texture
	SDL_Rect ClipRect = { 
		static_cast<int>(Position.x), static_cast<int>(Position.y),
		TextureDimensions.w, TextureDimensions.h };

	//clip the rectangle if the source rect is updated
	if (SourceRect != nullptr) {
		//scale the source rect if ine is set
		ClipRect.w = SourceRect->w * Scale;
		ClipRect.h = SourceRect->h * Scale;
	}
	else {
		//this will scale if there is no source rect
		ClipRect.w *= Scale;
		ClipRect.h *= Scale;
	}
	
	//this will define whether or not to flip the image
	SDL_RendererFlip FlipFlag = SDL_FLIP_NONE;

	//flip the image if bFlip is set
	if (bFlip) {
		FlipFlag = SDL_FLIP_HORIZONTAL;
	}

	//render the texture to the screen
	SDL_RenderCopyEx(
		SdlRenderer,	//renderer 
		SdlTexture,		//texture
		SourceRect,		//the source rect
		&ClipRect,		//the clip amount
		Rotation,		//angle - rotation in degrees
		0,				//where the center of the image is
		FlipFlag		//how should it flip
	);
}

void Texture::ResetTexture()
{
	if (SdlTexture != nullptr) {
		//SDL will remove the texture from memory
		SDL_DestroyTexture(SdlTexture);
		//make sure it's set to nullptr to avoid infinite loop
		SdlTexture = nullptr;
		//reset the dimensions
		TextureDimensions = SDL_Rect();
	}
}
