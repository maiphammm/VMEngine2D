#pragma once
#include "SDL2/SDL.h"
#include "VMEngine2D/Vector2.h"
#include <iostream>
#include <string>

using namespace std;

//structure to simply the functions paremeters and outputs
struct STTextInfo {
	Vector2 Position;
	Vector2 Dimensions;
	SDL_Color Colour = {255, 255, 255, 255};
	int Size = 24;
	string TextStr = "";
};

class Text {
public:
	Text(SDL_Renderer* Renderer);
	~Text();

	//initialise and create the font using the font supplied in the font path
	//use the text info to position, colour, sizr and set the text
	//Dimension will be set based on the text input
	//will return nullptr if it false
	Text* InitText(const char* FontPath, STTextInfo TextInfo);

	void Draw(SDL_Renderer* Renderer);

	//change the text in realtime
	void SetText(string NewText);

	//move the posision of the text on the screen
	void SetTextPosision(Vector2 Posision);

	//get the important tet infor
	STTextInfo GetTextInfo() const { return TextInfo; }

private:
	//store all the important text information
	STTextInfo TextInfo;

	//store the renderer
	SDL_Renderer* TextRenderer;

	//store the texture
	SDL_Texture* TextTexture;

	//store the font path from reseting the text
	const char* FontPath;
};