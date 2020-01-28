#include <stdio.h>
#include <stdlib.h>
#include <gb/gb.h>
#include "sprites.c"
#include "bgs.c"
#include "GameCharacter.c"

struct GameCharacter frogChar;
struct GameCharacter pickleChar;
struct GameCharacter missileChar;
UBYTE spritesize = 8;
UINT8 lives = 4;

void performantdelay(UINT8 numloops){
    UINT8 i;
    for (i=0; i < numloops; i++){
        wait_vbl_done();
    }
}

UBYTE checkcollisions(struct GameCharacter* one, struct GameCharacter* two){
 return(one->x >= two->x && one->x <= two->x + two->width) && (one->y >= two->y && one->y <= two->y + two->height) || (two->x >= one->x && two->x <= one->x + one->width) && (two->y >= one->y && two->y <= one->y + one->height);
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


void setupMissile(){
    missileChar.x += pickleChar.x;
    missileChar.y += pickleChar.y;
    pickleChar.width = 8;
    pickleChar.height = 8;
    set_sprite_tile(8,8);
    pickleChar.spritids[0] = 8;
    movegamecharacter(&missileChar, missileChar.x, missileChar.y);
}


void setupFrog(){

frogChar.x = pickleChar.x;
frogChar.y = 5;
frogChar.width = 16;
frogChar.height = 16;

set_sprite_tile(4,4);
frogChar.spritids[0] = 4;
set_sprite_tile(5,5);
frogChar.spritids[1] = 5;
set_sprite_tile(6,6);
frogChar.spritids[2] = 6;
set_sprite_tile(7,7);
frogChar.spritids[3] = 7;
movegamecharacter(&frogChar, frogChar.x, frogChar.y);

}

void main(){
    set_sprite_data(0, 8, sprites);
    setupPickle();
    setupFrog();
    setupMissile();
    set_bkg_data(0,4, bgTiles);
    set_bkg_tiles(0,0,20,18, playfield);
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;
    while(lives >= 2){
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
                if(joypad() & J_A){
                    missileChar.y += 3;
                }
                movegamecharacter(&frogChar, frogChar.x, frogChar.y); 

                if(pickleChar.x >= frogChar.x){
                    frogChar.x += 1;
                }
                else if(pickleChar.x <= frogChar.x){
                    frogChar.x -= 1;
                }

                if (pickleChar.y <= 100){
                    pickleChar.y = 101;
                }

               if(checkcollisions(&pickleChar, &frogChar)){
                    frogChar.y = 5;
                    lives -= 1;
                }

                frogChar.y += 3;
                performantdelay(2);
            }   

            printf("\n \n \n \n     GAME OVER!");


    }

