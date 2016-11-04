#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
// include the map for the maze.
#include "map.h"
// the size of the block to draw
const int BLOCKSIZE=25;
// the width of the screen taking into account the maze and block
#define WIDTH COLS*BLOCKSIZE
// the height of the screen taking into account the maze and block
#define HEIGHT ROWS*BLOCKSIZE
// an enumeration for direction to move USE more enums!
enum DIRECTION{UP,DOWN,LEFT,RIGHT,NONE};



int main()
{
  // initialise SDL and check that it worked otherwise exit
  // see here for details http://wiki.libsdl.org/CategoryAPI
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
  {
    printf("%s\n",SDL_GetError());
    return EXIT_FAILURE;
  }
  // we are now going to create an SDL window

  SDL_Window *win = 0;
  win = SDL_CreateWindow("Pacman", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  if (win == 0)
  {
    printf("%s\n",SDL_GetError());
    return EXIT_FAILURE;
  }
  // the renderer is the core element we need to draw, each call to SDL for drawing will need the
  // renderer pointer
  SDL_Renderer *ren = 0;
  ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  // check to see if this worked
  if (ren == 0)
  {
    printf("%s\n",SDL_GetError() );
    return EXIT_FAILURE;
  }
  // this will set the background colour to white.
  // however we will overdraw all of this so only for reference
  SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);

  // SDL image is an abstraction for all images
  SDL_Surface *image;
  // we are going to use the extension SDL_image library to load a png, documentation can be found here
  // http://www.libsdl.org/projects/SDL_image/
  image=IMG_Load("pacsprite.png");
  if(!image)
  {
    printf("IMG_Load: %s\n", IMG_GetError());
    return EXIT_FAILURE;
  }
  // SDL texture converts the image to a texture suitable for SDL rendering  / blitting
  // once we have the texture it will be store in hardware and we don't need the image data anymore

  SDL_Texture *tex = 0;
  tex = SDL_CreateTextureFromSurface(ren, image);
  // free the image
  SDL_FreeSurface(image);



  int quit=0;
  // now we are going to loop forever, process the keys then draw

  while (quit !=1)
  {
    SDL_Event event;
    // grab the SDL even (this will be keys etc)
    while (SDL_PollEvent(&event))
    {
      // look for the x of the window being clicked and exit
      if (event.type == SDL_QUIT)
        quit = 1;
      // check for a key down
      if (event.type == SDL_KEYDOWN)
      {
        switch (event.key.keysym.sym)
        {
        // if we have an escape quit
        case SDLK_ESCAPE : quit=1; break;
        // add other key control here (all begin with SDLK_)
       }
    }
  }

  // now we clear the screen (will use the clear colour set previously)
  SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
  SDL_RenderClear(ren);
  // we will create an SDL_Rect structure and draw a block
  SDL_Rect block;
  // set the block position
  block.x=100;
  block.y=50;
  block.w=BLOCKSIZE;
  block.h=BLOCKSIZE;
  SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
  SDL_RenderFillRect(ren,&block);
  // now to draw an element of the sprite sheet
  // first re-position the block position
  block.x=200;
  block.y=150;
  // now we need to create a rect for the texture.
  SDL_Rect pacman;
  // each sprite is 22 x 20 so set the width and height
  pacman.w=22;
  pacman.h=20;
  // now we calculate the offset into the sprite sheet for one of the
  // sprites 2nd across 3rd down should really define something for the
  // sprite size ;-)
  pacman.x=2*22;
  pacman.y=3*20;
  // finally draw using the SDL_RenderCopy function
  // this takes the texture and copies the portion from the rect
  SDL_RenderCopy(ren, tex,&pacman, &block);
  // your job is now to use functions, good coding practice data structures
  // and read the SDL documentation to complete the project!
  // good luck

  // Up until now everything was drawn behind the scenes.
  // This will show the new, red contents of the window.
  SDL_RenderPresent(ren);

  }


  SDL_Quit();
  return EXIT_SUCCESS;
}
