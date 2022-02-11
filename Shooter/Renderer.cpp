#include "Renderer.h"
#include "Log.h"
#include "Texture.h"
#include "Maths.h"
#include "SpriteComponent.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Score.h"

Renderer::Renderer() : SDLRenderer(nullptr)
{
}

bool Renderer::Initialize(Window& window)
{
	SDLRenderer = SDL_CreateRenderer(window.getSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!SDLRenderer){
		Log::error(LogCategory::Video, "Failed to create renderer");
		return false;
	}
	if(IMG_Init(IMG_INIT_PNG) == 0){
		Log::error(LogCategory::Video, "Unable to initialize SDL_image");
		return false;

	}
	return true;
}

void Renderer::BeginDraw()
{
	SDL_SetRenderDrawColor(SDLRenderer, 120, 120, 255, 255);
	SDL_RenderClear(SDLRenderer);
}

void Renderer::EndDraw()
{
	SDL_RenderPresent(SDLRenderer);
}



void Renderer::DrawRect(Rectangle& rect)
{
	SDL_SetRenderDrawColor(SDLRenderer, 255, 255, 255, 255);
	SDL_Rect SDLRect = rect.toSDLRect();
	SDL_RenderFillRect(SDLRenderer, &SDLRect);
}

void Renderer::Close()
{
	SDL_DestroyRenderer(SDLRenderer);
}

void Renderer::Draw() {
	DrawSprites();
}

void Renderer::DrawSprites() {
	for (auto sprite : sprites) {
		sprite->Draw(*this);
	}
}

void Renderer::DrawSprite(const Actor& actor, const Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip) const {
	SDL_Rect dstRect;
	Vector2 position = actor.GetPosition();
	float rotation = actor.GetRotation();
	float scale = actor.GetScale();
	//Scale the width/height by owner's
	dstRect.w = static_cast<int>(tex.GetWidth() * scale);
	dstRect.h = static_cast<int>(tex.GetHeight() * scale);
	//Center the rectangle around the position of the owner
	dstRect.x = static_cast<int>(position.x - origin.x);
	dstRect.y = static_cast<int>(position.y - origin.y);

	SDL_Rect* srcSDL = nullptr;
	if (srcRect != Rectangle::nullRect) {
		srcSDL = new SDL_Rect{
			Maths::round(srcRect.x),
			Maths::round(srcRect.y),
			Maths::round(srcRect.width),
			Maths::round(srcRect.height)
		};
	}

	SDL_RenderCopyEx(
		SDLRenderer,
		tex.toSDLTexture(),
		srcSDL,
		&dstRect,
		-Maths::ToDegrees(rotation),
		nullptr, //rotation point, center by default
		SDL_FLIP_NONE);
	delete srcSDL;
}

void Renderer::AddSprite(SpriteComponent* sprite) {
	int spriteDrawOrder = sprite->GetDrawOrder();
	auto iter = begin(sprites);
	for (; iter != end(sprites); ++iter) {
		if (spriteDrawOrder < (*iter)->GetDrawOrder()) break;
	}
	sprites.insert(iter, sprite);
}

void Renderer::RemoveSprite(SpriteComponent* sprite) {
	auto iter = std::find(begin(sprites), end(sprites), sprite);
	sprites.erase(iter);
}
//
//void Renderer::DrawScore() {
//
//	//this opens a font style and sets a size
//	TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);
//
//	//color white
//	SDL_Color White = { 255, 255, 255 };
//
//	// as TTF_RenderText_Solid could only be used on
//	// SDL_Surface then you have to create the surface first
//	SDL_Surface* surfaceMessage =
//		TTF_RenderText_Solid(Sans, "put your text here", White);
//
//	// now you can convert it into a texture
//	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
//
//	SDL_Rect Message_rect; //create a rect
//	Message_rect.x = 0;  //controls the rect's x coordinate 
//	Message_rect.y = 0; // controls the rect's y coordinte
//	Message_rect.w = 100; // controls the width of the rect
//	Message_rect.h = 100; // controls the height of the rect
//
//	// (0,0) is on the top left of the window/screen,
//	// think a rect as the text's box,
//	// that way it would be very simple to understand
//
//	// Now since it's a texture, you have to put RenderCopy
//	// in your game loop area, the area where the whole code executes
//
//	// you put the renderer's name first, the Message,
//	// the crop size (you can ignore this if you don't want
//	// to dabble with cropping), and the rect which is the size
//	// and coordinate of your texture
//	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
//
//	// Don't forget to free your surface and texture
//	SDL_FreeSurface(surfaceMessage);
//	SDL_DestroyTexture(Message);
//}