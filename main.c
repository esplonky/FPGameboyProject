#include <stdio.h>
#include <gb/gb.h>
#include "sprites.c"
#include "bgs.c"
#include "GameCharacter.c"

struct GameCharacter frog;
struct GameCharacter pickle;


void setupPickle(){
    pickle.x = 80;
    pickle.y = 130;
    pickle.width = 16;
    pickle.height = 16;

    set_sprite_tile(0,0);
    pickle.spritids[0] = 0;
    set_sprite_tile(1,1);
    pickle.spritids[1] = 1;
    set_sprite_tile(2,2);
    pickle.spritids[2] = 2;
    set_sprite_tile(3,3);
    pickle.spritids[3] = 3;


}


void setupFrog(){
frog.x = 30;
frog.y = 30;
frog.width = 16;
frog.height = 16;

set_sprite_tile(0,0);
frog.spritids[0] = 0;
set_sprite_tile(1,1);
frog.spritids[1] = 1;
set_sprite_tile(2,2);
frog.spritids[2] = 2;
set_sprite_tile(3,3);
frog.spritids[3] = 3;


}

void main(){

    setupFrog();
    setupPickle();
    set_bkg_data(0,4, bgTiles);
    set_bkg_tiles(0,0,20,18, playfield);
    move_sprite(0, 88, 78);
    move_sprite(1,78,88);
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;
    while(1){
        switch(joypad()){
            case J_LEFT:
                scroll_sprite(0,-1,0);
                break;
            case J_RIGHT:
                scroll_sprite(0,1,0);
                break;
            case J_UP:
                scroll_sprite(0,0,-1);
                break;
            case J_DOWN:
                scroll_sprite(0,0,1);
                break;
     
                }   

            /*if (joypad(J_DOWN && J_LEFT)){
                scroll_sprite(0,-1,1);}
            if (joypad(J_DOWN && J_RIGHT)){
                scroll_sprite(0,1,1);}
            if (joypad(J_UP && J_RIGHT)){
                scroll_sprite(0,1,-1);}
            if (joypad(J_UP && J_LEFT)){
                scroll_sprite(0,-1,-1);}*/
               

        delay(20);

    }

}