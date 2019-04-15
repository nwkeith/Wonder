#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

const int height = 800;
const int width = 800;

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to set */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	//printf("moss %i \n", *p);
	switch (bpp) {
	case 1:
		*p = pixel;
		break;

	case 2:
		*(Uint16 *)p = pixel;
		break;

	case 3:
		p[0] = pixel & 0xff;
		p[1] = (pixel >> 8) & 0xff;
		p[2] = (pixel >> 16) & 0xff;
		break;

	case 4:
		*(Uint32 *)p = pixel;
		break;
	//default:
		//printf("This picture has %i bypes per pixel. That is too many for wonder paint to handle!\n", bpp);
		//break;
	}
}

void MenuChoice(int x, int y, Uint32 & color)
{
	if (x > width + 6 && x < width + 131)
	{
		if (y < 125)
		{
			color = 0xFF0000;
		}
		else if (y < 250)
		{
			color = 0x00FF00;
		}
		else if (y < 375)
		{
			color = 0x0000FF;
		}
		else if (y < 500)
		{
			color = 0xFFFF00;
		}
		else if (y < 625)
		{
			color = 0;
		}
		else if (y < 750)
		{
			color = 0xFFFFFF;
		}
		else if (y >= 759)
		{
			color = 0x00FFFF;
		}

	}
}



int main(int argc, char* args[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	Uint32 color = 0;
	SDL_Window* gWindow = NULL;
	SDL_Surface* picture = NULL;
	SDL_Surface* optimizedSurface = NULL;
	SDL_Surface* colormenu = NULL;
	SDL_Surface* gScreenSurface = NULL;
	gWindow = SDL_CreateWindow("Wonder Paint", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, height, SDL_WINDOW_SHOWN);
	gScreenSurface = SDL_GetWindowSurface(gWindow);
	picture = SDL_LoadBMP("avxsample3.bmp");
	colormenu = SDL_LoadBMP("colormenu.bmp");
	if (picture != NULL)
	{
		printf("BMP File is loaded!\n");
		optimizedSurface = SDL_ConvertSurface(picture, gScreenSurface->format, NULL);
		//SDL_SaveBMP(picture, "avxsample.bmp");
	}
	else
	{
		printf("Cannot load file. Wonder Paint will create a new canvas.\n");
		SDL_FreeSurface(picture);
		picture = SDL_CreateRGBSurface(0, 16, 16, 24, 0xFF0000, 0x00FF00, 0x0000FF, 0); //0xFF0000, 0x00FF00, 0x0000FF, 0xFFFFFF
		//0xFF000000, 0x00FF0000, 0x0000FF00, 0x00000000
		//SDL_SetColorKey(picture, SDL_TRUE, 0);
		SDL_FillRect(picture, 0, 0xFFFFFF);
		optimizedSurface = SDL_ConvertSurface(picture, gScreenSurface->format, NULL);
		/*
		printf("Cannot load BMP File!\n");
		SDL_FreeSurface(picture);
		*/
	}

	bool quit = false;
	SDL_Event e;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_r:
					color = 0xFF0000;
					break;

				case SDLK_g:
					color = 0x00FF00;
					break;

				case SDLK_b:
					color = 0x0000FF;
					break;

				case SDLK_w:
					color = 0xFFFFFF;
					break;

				case SDLK_y:
					color = 0xFFFF00;
					break;

				case SDLK_k:
					color = 0x000000;
					break;
				}
			}
			else if (e.type == SDL_MOUSEMOTION)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				//SDL_MouseMotionEvent(&x, &y);
				if (x < width)
				{
					x = x / (width / 16);
					y = y / (width / 16);
					printf("x position: %i. y position: %i", x, y);
					if (SDL_GetMouseState(NULL, NULL)& SDL_BUTTON(1))
					{
						//printf("Mouse Button 1(left) is pressed.\n");
						putpixel(optimizedSurface, x, y, color);
					}
					else if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(3))
					{
						putpixel(optimizedSurface, x, y, 0xFFFFFF);
					}
				}
				/*else
				{
					MenuChoice(x, y, color);
				}*/
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (x < width)
				{
					x = x / (width / 16);
					y = y / (width / 16);
					if (SDL_GetMouseState(NULL, NULL)& SDL_BUTTON(1))
					{
						putpixel(optimizedSurface, x, y, color);
					}
					else if (SDL_GetMouseState(NULL, NULL)& SDL_BUTTON(3))
					{
						putpixel(optimizedSurface, x, y, 0xFFFFFF);
					}
				}
				else
				{
					MenuChoice(x, y, color);
				}

				
			}
		}
		SDL_Rect stretchRect;
		stretchRect.x = 0;
		stretchRect.y = 0;
		stretchRect.w = width;
		stretchRect.h = height;
		SDL_Rect menuRect;
		menuRect.x = 800;
		menuRect.y = 0;
		menuRect.w = 200;
		menuRect.h = 800;
		//SDL_BlitSurface(picture, NULL, gScreenSurface, NULL);
		SDL_BlitScaled(optimizedSurface, NULL, gScreenSurface, &stretchRect);
		SDL_BlitSurface(colormenu, NULL, gScreenSurface, &menuRect);
		SDL_UpdateWindowSurface(gWindow);
	}
	SDL_SaveBMP(optimizedSurface, "avxsample_new.bmp");
	return 0;
}