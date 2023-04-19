#include "VMEngine2D/Text.h"
#include "SDL2/SDL_ttf.h"

using namespace std;

Text::Text(SDL_Renderer* Renderer)
{
	TextRenderer = Renderer;
	TextTexture = nullptr;
}

Text::~Text()
{
	if (TextTexture != nullptr) {
		SDL_DestroyTexture(TextTexture);
	}

	//TextTexture = nullptr;
	TextRenderer = nullptr;
}

Text* Text::InitText(const char* FontPath, STTextInfo TextInfo)
{
	//if there is already a texture set then destroy it to make room for a new one
	if (TextTexture != nullptr) {
		SDL_DestroyTexture(TextTexture);
		TextTexture = nullptr;
	}

	//import the font
	TTF_Font* Font = TTF_OpenFont(FontPath, TextInfo.Size);

	//error if the font couldnt be loaded
	if (Font == nullptr) {
		cout << "Couldnt load font at: " << FontPath << " - " << TTF_GetError() << endl;
		return nullptr;
	}

	//create a surface from the font file
	SDL_Surface* TextSurface = TTF_RenderText_Solid(Font, TextInfo.TextStr.c_str(), TextInfo.Colour);

	//error if the surface didnt work
	if (TextSurface == nullptr) {
		cout << "Couldnt create surface for: " << FontPath << " - " << TTF_GetError() << endl;
		return nullptr;
	}

	//convert the surface into a texture
	TextTexture = SDL_CreateTextureFromSurface(TextRenderer, TextSurface);

	//fill in and save the text info
	this->TextInfo = TextInfo;
	this->FontPath = FontPath;

	//now we know everything worked we can get the surface dimensions and save them
	this->TextInfo.Dimensions = Vector2(static_cast<float>(TextSurface->w), static_cast<float>(TextSurface->h));

	//clear the surface from memory
	SDL_FreeSurface(TextSurface);

	return this;
}

void Text::Draw(SDL_Renderer* Renderer)
{
	SDL_FRect Dest;
	
	//create a SDL rectangle for SDL to know how to render the text
	Dest.x = TextInfo.Position.x;
	Dest.y = TextInfo.Position.y;
	Dest.w = TextInfo.Dimensions.x;
	Dest.h = TextInfo.Dimensions.y;

	//render the text to the screen using the above rectangle
	SDL_RenderCopyExF(Renderer, TextTexture, NULL, &Dest, 0.0, NULL, SDL_RendererFlip::SDL_FLIP_NONE);
}

void Text::SetText(string NewText)
{
	//if the text isnt different from the current text then dont run the function
	if (TextInfo.TextStr == NewText) {
		return;
	}

	//update the text in the class
	TextInfo.TextStr = NewText;

	//Initialise text
	InitText(FontPath, TextInfo);

}

void Text::SetTextPosision(Vector2 Posision)
{
	//update the text info posision that is drawn each from with the new position
	TextInfo.Position = Posision;
}
