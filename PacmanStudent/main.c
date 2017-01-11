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
enum direction{UP,DOWN,LEFT,RIGHT,NONE};
//an enumeraton for whether there is a collision or not during collision check
enum COLLISION{NO_COLLISION,YES_COLLISION,DEFAULT};
//an enumeration for whether animation delay has finished
enum DELAY{NO_DELAY,DELAY_DONE};

//---------------------------Functions---------------------------------------

///\brief For removing pills from the map after the Pacman sprite eats them
/// @Param[in] _mapRow - row number of pacman's current position on the map in map.h (INCLUDING BLOCKSIZE MULTIPLIER)
/// @Param[in] _mapCol - column number of pacman's current position on the map in map.h (INCLUDING BLOCKSIZE MULTIPLIER)

void EatPill(int _mapRow , int _mapCol)
{
    //To prevent the pacman from eating the walls
    //we only want pacman to eat on map with index "2" (which is where the pills are at)
    if (map[_mapRow/BLOCKSIZE][_mapCol/BLOCKSIZE]==2)
    {
        //We turn the index "2" to index "3" for DrawMap function to know not to draw more pills on this tile
        //since pill has been eaten already
        map[_mapRow/BLOCKSIZE][_mapCol/BLOCKSIZE]=3;
    }

}

///\brief For delaying sprite animation delay
/// @Param[in/out] io_delayCt - a frame counter needed to be compared with delay criteria
///  to repeat animation frames to slow down pacman sprite's animation
///  counter resets in thsi function after a criteria is met and continues the cycle.
char Delay(int *io_delayCt)
{
    //Setting how many frames we want to delay
    int _delayFrames=3;
    //DelayCt is a value incremented every frame
    //DelayCt is compared with the criteria to determine return value
    if(*io_delayCt>=_delayFrames)
    {
        //reset Counter and tells DrawPMan to increment on sprite sheet
        *io_delayCt=0;
        return DELAY_DONE;
    }
    //delay criteria not met so we continue the delay check next frame
    return NO_DELAY;

}

///\brief Function for drawing map tiles~
/// @Param[in] *_ren - SDL_Renderer is needed to call SDLRender functions
void DrawMap(SDL_Renderer *_ren)
{
    //declaring the rect we are using for the map tiles
    SDL_Rect block;
    //Looping through the map array
    for(int row=0;row<ROWS;++row)
    {
        for(int col=0;col<COLS;++col)
        {
            //assign block position on the map for drawing each map tile
            block.x=col*BLOCKSIZE;
            block.y=row*BLOCKSIZE;
            block.w=BLOCKSIZE;
            block.h=BLOCKSIZE;
            if (map[row][col]==2||map[row][col]==3)
            {
                //draw floor block and colour according to the map's index, 2 and 3 in map are traversable paths
                SDL_SetRenderDrawColor(_ren,0,0,0,0);
                SDL_RenderFillRect(_ren,&block);
                //Reassign coin block for drawing coins~
                if(map[row][col]==2)
                {
                    //if index is 2 on the map index, that means the pill hasn't been eaten
                    //therefore, we draw a pill on the tile
                    block.w=(BLOCKSIZE)/4;
                    block.h=(BLOCKSIZE)/4;
                    block.x=(col*BLOCKSIZE)+(BLOCKSIZE/4);
                    block.y=(row*BLOCKSIZE)+(BLOCKSIZE/4);
                    //pill colour set to white
                    SDL_SetRenderDrawColor(_ren,255,255,255,255);
                    SDL_RenderFillRect(_ren,&block);
                }
            }
            else if(map[row][col]==1)
            {
                //draw wall block and colour according to the map's index, 1 and 0 are not traversable
                SDL_SetRenderDrawColor(_ren,50,205,50,255);
                SDL_RenderFillRect(_ren,&block);
            }
            else if(map[row][col]==0)
            {
                //draw space block and colour according to the map's index
                SDL_SetRenderDrawColor(_ren,115, 91, 60,255);
                SDL_RenderFillRect(_ren,&block);
            }
            else
            {
                printf("Failing to draw blocks, please help me with map indexing! OTZ");

            }


        }
    }
}

///\brief Function for drawing and updating pacman sprite every frame
/// @Param[in] *_ren - SDL_Renderer is needed to call SDLRender functions
/// @Param[in] *_tex - SDL_Texture is needed in SDL_RenderCopy
/// @Param[in] *_block - SDL_Rect is initialised in main(), we need to bring its values to this function for SDL_RenderCopy
/// @Param[in] *_pacman - This is used as a source of our sprite image for the *block when calling SDL_RenderCopy
/// @Param[in] *_direction - Direction of sprite changes the animation sequences which changes what this may draw
/// @Param[in] *_delayCt - A frame counter to be passed into Delay(int, *delayCt) for animation delay
void DrawPMan(SDL_Renderer *_ren, SDL_Texture *_tex, SDL_Rect *_block,SDL_Rect *_pacman, int *_direction,int *_delayCt)
{
    //If the player decides to go up
    if(*_direction==UP)
    {
        //if one cycle of sprtie animation is finished, recycle the sprite animation on the sprite sheet
        if (_pacman->y>=6*20)
        {
            _pacman->y=0*20;
        }
        //if Delay() function says the delay is finished, we proceed to incrent to the next sprite animation frame
        if(Delay(_delayCt)==DELAY_DONE)
        {
            _pacman->y+=20;
            SDL_RenderCopy(_ren, _tex,_pacman, _block);
        }
        //if the return value says NO_Delay, we repeat the same sprite frame to delay the animation
        else
        {
            SDL_RenderCopy(_ren, _tex,_pacman, _block);

        }

    }
    //If the player decides to go left
    else if(*_direction==LEFT)
    {
        //Recycling animation
        if (_pacman->y>=6*20)
        {
            _pacman->y=0*20;
        }
        //Increment animation frame when delay is finished
        if(Delay(_delayCt)==DELAY_DONE)
        {
            _pacman->y+=20;
            SDL_RenderCopy(_ren, _tex,_pacman, _block);

        }
        //Continue the delay if delay is not finished yet
        else
        {
            SDL_RenderCopy(_ren, _tex,_pacman, _block);

        }
    }
    //If the player decides to go down
    else if (*_direction==DOWN)
    {
        //Recycling animation
        if (_pacman->y>=6*20)
        {
            _pacman->y=0*20;
        }
        //Increment animation frame when delay is finished
        if(Delay(_delayCt)==DELAY_DONE)
        {
            _pacman->y+=20;
            SDL_RenderCopy(_ren, _tex,_pacman, _block);
        }
        //Continue the delay if delay is not finished yet
        else
        {
            SDL_RenderCopy(_ren, _tex,_pacman, _block);
        }
    }
    //If the player decides to go right
    else if (*_direction==RIGHT)
    {
        //Recycling animation
        if (_pacman->y>=6*20)
        {
            _pacman->y=0*60;
        }
        //Increment animation frame when delay is finished
        if(Delay(_delayCt)==DELAY_DONE)
        {
            _pacman->y+=20;
            SDL_RenderCopy(_ren, _tex,_pacman, _block);
        }
        //Continue the delay if delay is not finished yet
        else
        {
    /*For testing:
             * printf("\nTesting if statement path\n");
             */
            SDL_RenderCopy(_ren, _tex,_pacman, _block);
        }
    }
    //If the player is initially stationary
    else if(*_direction==NONE)
    {
        //Don't animate when sprite is stationary at the beginning
    /*For testing:
         * printf("\nStationary Position\n");
         */
        SDL_RenderCopy(_ren, _tex,_pacman, _block);

    }
}

///\brief Function for moving pacman sprite
/// @Param[in] _direction - Different direction affect which direction the command specifies the block to move towards
/// @Param[in] *_block - To move and steer the block (the pacman we are controlling), we need to change x and y values of its struct
void MovePMan(int _direction, SDL_Rect *_block)
{
    //Store the coordinate to move to for collision checks
    int coordToMove;
    //The movement after movement modifier
    int totalMove=3;

    if(_direction==UP)
    {
        //The coordinate to check for collision a is the top section of the y direction of the block
        //when going up
        coordToMove=_block->y;
        /*Explanations:
        "block->x+ totalMove" and "coordToMove-(totalMove-1)" and such
        ensures pacman is detecting the correct coordinate when moving in intervals of totalMove.

        This is because SDL_Rect.x and .y are initialised to the block's top left corner
        This means that if block->x (or ->y) is not modified in some situations, the collision check may return true
        for traversable spaces and block/allow pacman's movement when it should be allowed to do so*/
        if(ColliCheck((_block->x+totalMove),(coordToMove-(totalMove-1)),UP)==NO_COLLISION
        && ColliCheck((_block->x+(BLOCKSIZE-totalMove)),(coordToMove-(totalMove-1)),UP)==NO_COLLISION)
        {
            //Move pacman if collsion check says NO_COLLISION
            _block->y-= totalMove;
            //Eat the pill on the tile when pacman reaches it
            //printf("\n PAC POSITION:\n x:%d y:%d",block->x,block->y);
            EatPill(_block->y+BLOCKSIZE/2,_block->x+BLOCKSIZE/2);
        }
    }
    /*Explanations:
    "block->x+ totalMove" and "coordToMove-(totalMove-1)" and such
    ensures pacman is detecting the correct coordinate when moving in intervals of totalMove.

    This is because SDL_Rect.x and .y are initialised to the block's top left corner
    This means that if block->x (or ->y) is not modified in some situations, the collision check may return true
    for traversable spaces and block/allow pacman's movement when it should be allowed to do so*/
    else if(_direction==DOWN)
    {
        coordToMove=((_block->y)+(BLOCKSIZE));
        if(ColliCheck((_block->x+(BLOCKSIZE-totalMove)),(coordToMove+(totalMove-1)),DOWN)==NO_COLLISION
        && ColliCheck((_block->x+totalMove),(coordToMove+(totalMove-1)),DOWN)==NO_COLLISION)
        {
            //Move pacman if collsion check says NO_COLLISION
            _block->y+= totalMove;
            //Eat the pill on the tile when pacman reaches it
            //printf("\n PAC POSITION:\n x:%d y:%d",block->x,block->y);
            EatPill(_block->y+BLOCKSIZE/2,_block->x+BLOCKSIZE/2);
        }

    }
    /*Explanations:
    "block->x+ totalMove" and "coordToMove-(totalMove-1)" and such
    ensures pacman is detecting the correct coordinate when moving in intervals of totalMove.

    This is because SDL_Rect.x and .y are initialised to the block's top left corner
    This means that if block->x (or ->y) is not modified in some situations, the collision check may return true
    for traversable spaces and block/allow pacman's movement when it should be allowed to do so*/
    else if(_direction==LEFT)
    {
        coordToMove=_block->x;
        //When pacman reaches the end of one route, it teleport to the other side
        if((_block->x*BLOCKSIZE)<0)
        {
            printf("\n PAC POSITION:\n x:%d\n",_block->x);
            _block->x+=(28*BLOCKSIZE);
        }
        if(ColliCheck((coordToMove-(totalMove-1)),(_block->y+(BLOCKSIZE-totalMove)),LEFT)==NO_COLLISION
        && ColliCheck((coordToMove-(totalMove-1)),(_block->y+totalMove),LEFT)==NO_COLLISION)
        {
            //Move pacman if collsion check says NO_COLLISION
            _block->x-= totalMove;
            //Eat the pill on the tile when pacman reaches it
            //printf("\n PAC POSITION:\n x:%d y:%d",_block->x,_block->y);
            EatPill(_block->y+BLOCKSIZE/2,_block->x+BLOCKSIZE/2);
        }

    }
    /*Explanations:
    "block->x+ totalMove" and "coordToMove-(totalMove-1)" and such
    ensures pacman is detecting the correct coordinate when moving in intervals of totalMove.

    This is because SDL_Rect.x and .y are initialised to the block's top left corner
    This means that if block->x (or ->y) is not modified in some situations, the collision check may return true
    for traversable spaces and block/allow pacman's movement when it should be allowed to do so*/
    else if(_direction==RIGHT)
    {
        coordToMove=((_block->x)+(BLOCKSIZE));
        //When pacman reaches the end of one route, it teleport to the other side
        if((_block->x)>=28*BLOCKSIZE)
        {
            _block->x=0;
        }
        if(ColliCheck((coordToMove+(totalMove-1)),(_block->y+(BLOCKSIZE-totalMove)),RIGHT)==NO_COLLISION
        && ColliCheck((coordToMove+(totalMove-1)),(_block->y+totalMove),RIGHT)==NO_COLLISION)
        {
            //Move pacman if collsion check says NO_COLLISION
            _block->x+=totalMove;
            //Eat the pill on the tile when pacman reaches it
            //printf("\n PAC POSITION:\n x:%d y:%d",_block->x,_block->y);
            EatPill(_block->y+BLOCKSIZE/2,_block->x+BLOCKSIZE/2);
        }

    }
    return;
}

///\brief Function for checking collision with walls before moving
/// @Param[in] _xCoord - x coordinate of pacman on the SDL grid, needed for comparisons to map.h
/// @Param[in] _yCoord - y coordinate of pacman on the SDL grid, needed for comparisons to map.h
/// @Param[in] _direction - Different direction affect which side the function is trying to detect collision from
int ColliCheck(int _xCoord,int _yCoord,int _direction)
{
    /*if future x or y coordinate is not equal to current x or y coordinate,
    then block is moving in x direction.*/
    /* Explanation:
    xCoord = COL gain on map [ROW][COL]
    yCoord = ROW gain on map [ROW][COL]
    */
    //Declare variables to store map.h coordinates for comparison in collision check
    int mapXCoord;
    mapXCoord = (_xCoord/BLOCKSIZE);
    int mapYCoord;
    mapYCoord=(_yCoord/BLOCKSIZE);

    /* For testing:
     * printf("\n Map Coord :%d %d",mapXCoord,mapYCoord);
     */
    if(_direction==RIGHT)
    {   //Moving right
        //if the parameter from the MovePman function matched the map index for traversable path, then
        //there is no collision, return NO_COLLISION to MovePMan to allow movement onto the block
        //Adding special case where pac goes through on the right side
        if(map[mapYCoord][mapXCoord]==2 || map[mapYCoord][mapXCoord]==3 || mapXCoord>=28)
        {
            //printf("\n Collision: No collision");
            return NO_COLLISION;
        }
        //If map index not met, return YES_COLLISION for the MovePMan to block the pacman
        else
        {
            /*
            printf("\n Checked Coord :%d %d",mapXCoord,mapYCoord);
            printf("\n Collision: Collision triggered while going right");
            */
            return YES_COLLISION;
        }
    }
    //if the parameter from the MovePman function matched the map index for traversable path, then
    //there is no collision, return NO_COLLISION to MovePMan to allow movement onto the block
    else if(_direction==LEFT)
    {   //Moving Left
        if(map[mapYCoord][mapXCoord]==2 || map[mapYCoord][mapXCoord]==3)
        {
            //printf("\n Collision: No collision");
            return NO_COLLISION;
        }
        //If map index not met, return YES_COLLISION for the MovePMan to block the pacman
        else
        {
            /*
            printf("\n Checked Coord :%d %d",mapXCoord,mapYCoord);
            printf("\n Collision: Collision triggered while going left");
            */
            return YES_COLLISION;
        }
    }
    //if the parameter from the MovePman function matched the map index for traversable path, then
    //there is no collision, return NO_COLLISION to MovePMan to allow movement onto the block
    else if(_direction==DOWN)
    {//Moving Down
        if(map[mapYCoord][mapXCoord]==2 || map[mapYCoord][mapXCoord]==3)
        {
            //printf("\n Collision: No collision");
            return NO_COLLISION;
        }
        //If map index not met, return YES_COLLISION for the MovePMan to block the pacman
        else
        {
            /*
            printf("\n Checked Coord :%d %d",mapXCoord,mapYCoord);
            printf("\n Collision: Collision triggered while going down");
            */
            return YES_COLLISION;
        }
    }
    //if the parameter from the MovePman function matched the map index for traversable path, then
    //there is no collision, return NO_COLLISION to MovePMan to allow movement onto the block
    else if(_direction==UP)
    {//Moving Up
        if(map[mapYCoord][mapXCoord]==2 || map[mapYCoord][mapXCoord]==3)
        {
            //printf("\n Collision: No collision");
            return NO_COLLISION;
        }
        //If map index not met, return YES_COLLISION for the MovePMan to block the pacman
        else
        {
            /*
            printf("\n Checked Coord :%d %d",mapXCoord,mapYCoord);
            printf("\n Collision: Collision triggered while going up.");
            */
            return YES_COLLISION;
        }
    }
    return DEFAULT;

}

//Main game loop, rendering and function calls happen here
int main()
{
    // initialise SDL and check that it worked otherwise exit

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
    SDL_Rect block;
    block.w=BLOCKSIZE;
    block.h=BLOCKSIZE;
    // first re-position the block position
    block.x=(BLOCKSIZE)/2*BLOCKSIZE;
    block.y=29*(BLOCKSIZE);
    // now we need to create a rect for the texture.
    SDL_Rect pacman;
    // each sprite is 22 x 20 so set the width and height
    pacman.w=22;
    pacman.h=20;
    // now we calculate the offset into the sprite sheet for one of the
    // sprites 2nd across 3rd down should really define something for the
    // sprite size ;-)
    pacman.x=1*22;
    pacman.y=1*20;
    int direction=NONE;
    int delay=0;
    // now we are going to loop forever, process the keys then draw
    while (quit !=1)
    {
        ++delay;
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
                    // if we have an escape quit and w,a,s,d for direction inputs
                    case SDLK_ESCAPE : quit=1; break;
                    //each direction control call MovePMan function to try moving in the corresponding direction
                    case SDLK_w :
                    {
                        pacman.x=2*22;
                        direction=UP;
                        MovePMan(direction,&block);
                        break;
                    }
                    case SDLK_a :
                    {
                        pacman.x=0;
                        direction=LEFT;
                        MovePMan(direction,&block);
                        break;
                    }
                    case SDLK_s :
                    {
                        pacman.x=3*22;  
                        direction=DOWN;
                        MovePMan(direction,&block);
                        break;
                    }
                    case SDLK_d :
                    {
                        pacman.x=1*22;                   
                        direction=RIGHT;
                        MovePMan(direction,&block);
                        break;
                    }
                }
            }
        }
        // now we clear the screen (will use the clear colour set previously)
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderClear(ren);
        //calling DrawMap function to draw map tiles
        DrawMap(ren);
        //calling drawPackman function to draw/update pacman sprite every frame
        DrawPMan(ren,tex,&block,&pacman,&direction,&delay);
        //Up until now everything was drawn behind the scenes.
        //This will show the new, red contents of the window.
        SDL_RenderPresent(ren);
    }
    SDL_Quit();
    return EXIT_SUCCESS;
}


