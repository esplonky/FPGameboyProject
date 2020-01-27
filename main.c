#include <stdio.h>
// @ts-ignore
#include <stdlib.h>
#include <gb/gb.h>
#include "sprites.c"
#include "bgs.c"
#include "GameCharacter.c"

struct GameCharacter frogChar;
struct GameCharacter pickleChar;
UBYTE spritesize = 8;

void performantdelay(UINT8 numloops){
    UINT8 i;
    for (i=0; i < numloops; i++){
        wait_vbl_done();
    }
}



void movegamecharacter(struct GameCharacter* character, UINT8 x, UINT8 y){
    move_sprite(character->spritids[0], x, y);
    move_sprite(character->spritids[1], x + spritesize, y);
    move_sprite(character->spritids[2], x, spritesize + y);
    move_sprite(character->spritids[3], x + spritesize, y + spritesize);
}

void setupPickle(){
    pickleChar.x = 80;
    pickleChar.y = 130;
    pickleChar.width = 16;
    pickleChar.height = 16;

    set_sprite_tile(0,0);
    pickleChar.spritids[0] = 0;
    set_sprite_tile(1,1);
    pickleChar.spritids[1] = 1;
    set_sprite_tile(2,2);
    pickleChar.spritids[2] = 2;
    set_sprite_tile(3,3);
    pickleChar.spritids[3] = 3;

    movegamecharacter(&pickleChar, pickleChar.x, pickleChar.y);
}


void setupFrog(){


frogChar.x = rand();
frogChar.y = 30;
frogChar.width = 16;
frogChar.height = 16;

set_sprite_tile(0,0);
frogChar.spritids[0] = 0;
set_sprite_tile(1,1);
frogChar.spritids[1] = 1;
set_sprite_tile(2,2);
frogChar.spritids[2] = 2;
set_sprite_tile(3,3);
frogChar.spritids[3] = 3;
movegamecharacter(&frogChar, frogChar.x, frogChar.y);

}

void main(){

    //setupFrog();
    setupPickle();
    set_sprite_data(0, 8, pickle);
    set_bkg_data(0,4, bgTiles);
    set_bkg_tiles(0,0,20,18, playfield);
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;
    while(1){
                if(joypad() & J_LEFT){
                    pickleChar.x -= 2;
                    movegamecharacter(&pickleChar, pickleChar.x, pickleChar.y);
                }
                if(joypad() & J_RIGHT){
                    pickleChar.x += 2;
                    movegamecharacter(&pickleChar, pickleChar.x, pickleChar.y);
                }
                if(joypad() & J_UP){
                    pickleChar.y -= 2;
                    movegamecharacter(&pickleChar, pickleChar.x, pickleChar.y);
                }
                if(joypad() & J_DOWN){
                    pickleChar.y += 2;
                    movegamecharacter(&pickleChar, pickleChar.x, pickleChar.y);
                }
                movegamecharacter(&frogChar, frogChar.x, frogChar.y); 

                if(pickleChar.x >= frogChar.x){
                    frogChar.x += 5;
                }
                if(pickleChar.x >= frogChar.x){
                    frogChar.x -= 5;
                }
                frogChar.y += 3;
                performantdelay(2);
            }   

               

    
    }

