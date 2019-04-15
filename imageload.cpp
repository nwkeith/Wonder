#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

const int height = 800;
const int width = 800;
TTF_Font *gFont = TTF_OpenFont("TCCM____.TTF", 14);

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

void splashScreen()
{
	int sHeight = 800;
	int sWidth = 1600;
	SDL_Window* sWindow = NULL;
	SDL_Surface* splash = NULL;
	SDL_Surface* optimizedSplash = NULL;
	SDL_Surface* sScreenSurface = NULL;
	sWindow = SDL_CreateWindow("Welcome", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, sWidth, sHeight, SDL_WINDOW_SHOWN);
	sScreenSurface = SDL_GetWindowSurface(sWindow);
	splash = SDL_LoadBMP("Wonder_Splash.bmp");
	if (splash != NULL)
	{
		//printf("BMP File is loaded!\n");
		optimizedSplash = SDL_ConvertSurface(splash, sScreenSurface->format, NULL);
		SDL_FreeSurface(splash);
		SDL_Rect splashRect;
		splashRect.x = 0;
		splashRect.y = 0;
		splashRect.w = sWidth;
		splashRect.h = sHeight;
		SDL_BlitScaled(optimizedSplash, NULL, sScreenSurface, &splashRect);
		SDL_UpdateWindowSurface(sWindow);
		SDL_Delay(1000);
		SDL_FreeSurface(optimizedSplash);
		optimizedSplash = NULL;
		SDL_DestroyWindow(sWindow);
		sWindow = NULL;
	}
	//SDL_BlitScaled(optimizedSurface, NULL, gScreenSurface, &stretchRect)
	else
	{
		printf("Error 125: Splash was not found. Try reinstalling the program.");
	}

}

void Square(SDL_Surface *& screen)
{
	SDL_Surface* square = NULL;
	//SDL_Surface* opSquare = NULL;
	square = SDL_LoadBMP("Paintboxes.bmp");
	if (square != NULL)
	{
		//opSquare = SDL_ConvertSurface();
		SDL_Rect squareRect;
		squareRect.x = width+6;//width + 6;
		squareRect.y = 0;
		squareRect.w = 125;
		squareRect.h = 125;
		SDL_BlitSurface(square, NULL, screen, &squareRect);

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
			splashScreen();
		}

	}
}



int main(int argc, char* args[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	splashScreen();
	/*string path;
	char option;
	printf("Would you like to create a new canvas?(y/n)\n");
	cin >> option;
	if (char == 'y')*/
	Uint32 color = 0;
	SDL_Window* gWindow = NULL;
	SDL_Surface* picture = NULL;
	SDL_Surface* optimizedSurface = NULL;
	SDL_Surface* colormenu = NULL;
	SDL_Surface* gScreenSurface = NULL;
	SDL_Surface * icon = NULL;
	icon = SDL_LoadBMP("Wonder_Icon.bmp");
	gWindow = SDL_CreateWindow("Wonder Paint", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, height, SDL_WINDOW_SHOWN);
	SDL_SetWindowIcon(gWindow, icon);
	gScreenSurface = SDL_GetWindowSurface(gWindow);
	picture = SDL_LoadBMP("pattern5.bmp");
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
				case SDLK_d:
					Square(gScreenSurface);
					break;
				case SDLK_UP:
					color = color + 0x010101;
					break;
				case SDLK_DOWN:
					color = color - 0x010101;
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
		//Square(gScreenSurface);
		SDL_Color textColor = { 0,0,0 };
		SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, "num", textColor);


		SDL_UpdateWindowSurface(gWindow);
	}
	SDL_SaveBMP(optimizedSurface, "avxsample_new.bmp");
	return 0;
}