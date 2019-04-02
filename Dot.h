#ifndef DOT_H
#define DOT_H

#include <SDL2/SDL.h>
#include "Tile.h"
#include "Texture.h"

//The dot that will move around on the screen
class Dot
{
    public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 2;

		//Initializes the variables
		Dot(int _x, int _y);

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot and check collision against tiles
		void move( Tile *tiles[] );

		//Shows the dot on the screen
		void render(LTexture& gDotTexture, SDL_Renderer* gRenderer);

    private:
		//Collision box of the dot
		SDL_Rect mBox;

		//The velocity of the dot
		int mVelX, mVelY;
};

#endif // DOT_H
