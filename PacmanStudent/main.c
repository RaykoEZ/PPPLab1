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

//Function for drawing map tiles and Pacman~
void DrawMap(SDL_Renderer *ren){
    SDL_Rect block;
    for(int row=0;row<ROWS;++row){
        for(int col=0;col<COLS;++col){
    //dynamically assign block position on the map for drawing
            block.x=col*BLOCKSIZE;
            block.y=row*BLOCKSIZE;
            block.w=BLOCKSIZE;
            block.h=BLOCKSIZE;
            if (map[row][col]==2){
    //draw floor block and colour according to the map's index
                SDL_SetRenderDrawColor(ren,0,0,0,0);
                SDL_RenderFillRect(ren,&block);
    //Reassign coin block for drawing coins(them collectables and stuff~)
                block.w=(BLOCKSIZE)/2;
                block.h=(BLOCKSIZE)/2;
                block.x=(col*BLOCKSIZE)+(BLOCKSIZE/4);
                block.y=(row*BLOCKSIZE)+(BLOCKSIZE/4);
                SDL_SetRenderDrawColor(ren,255,255,255,255);
                SDL_RenderFillRect(ren,&block);

            }
            else if(map[row][col]==1){
    //draw wall block and colour according to the map's index
                SDL_SetRenderDrawColor(ren,50,205,50,255);
                SDL_RenderFillRect(ren,&block);
            }
            else if(map[row][col]==0){
    //draw space block and colour according to the map's index
                SDL_SetRenderDrawColor(ren,115, 91, 60,255);
                SDL_RenderFillRect(ren,&block);
            }
            else{
                printf("Failing to draw blocks, please help me with map indexing! OTZ");

            }


        }
    }
}
void DrawPMan(SDL_Renderer *ren, SDL_Texture *tex, SDL_Rect *block){
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
    // takes the texture and copies the portion from the pacman rect to block rect
    SDL_RenderCopy(ren, tex,&pacman, block);


}

void MovePMan(int Direction, SDL_Rect *block){
    int MoveInterval=1;
    int Velocity=6;
    if(Direction==UP){
        ColliCheck();
        block->y+= -MoveInterval*Velocity;
        printf("\n PAC POSITION:\n x:%d y:%d",block->x,block->y);

    }
    else if(Direction==DOWN){
        ColliCheck();
        block->y+= MoveInterval*Velocity;
        printf("\n PAC POSITION:\n x:%d y:%d",block->x,block->y);
    }

    else if(Direction==LEFT){
        ColliCheck();
        block->x-= MoveInterval*Velocity;
        printf("\n PAC POSITION:\n x:%d y:%d",block->x,block->y);
    }

    else if(Direction==RIGHT){
        ColliCheck();
        block->x+=MoveInterval*Velocity;
        printf("\n PAC POSITION:\n x:%d y:%d",block->x,block->y);
    }
    else return;


}
int ColliCheck(){

}
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
  SDL_Surface *image;
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
  SDL_Rect block;
  //The movement Interval for the pacman per direction input
  block.w=BLOCKSIZE;
  block.h=BLOCKSIZE;
  // first re-position the block position
  block.x=1*BLOCKSIZE;
  block.y=1*BLOCKSIZE;

  //Game Loop
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
        case SDLK_w : MovePMan(UP,&block);break;
        case SDLK_a : MovePMan(LEFT,&block);break;
        case SDLK_s : MovePMan(DOWN,&block);break;
        case SDLK_d : MovePMan(RIGHT,&block);break;

        // add other key control here (all begin with SDLK_)
       }
    }
  }
      // now we clear the screen (will use the clear colour set previously)
      SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
      SDL_RenderClear(ren);
      //calling DrawMap function to draw map tiles
      DrawMap(ren);
      //calling drawPackman function to draw pacman
      DrawPMan(ren,tex,&block);
      //Up until now everything was drawn behind the scenes.
      //This will show the new, red contents of the window.
      SDL_RenderPresent(ren);
  }


  SDL_Quit();
  return EXIT_SUCCESS;
}


