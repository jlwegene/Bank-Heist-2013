#include <structures.h>
#include <movingBlock.h>
#include <level.h>
#include <f3d_lcd_sd.h>
#include <stdio.h>
void drawMovingBlock(mblock mb, uint16_t c1){
	int i,j;
	drawTile(mb.posX/16, mb.posY/16);
	for(i=0; i<16; ++i){
		for(j=0; j<32; ++j){
			if(mb.sprite[i][j] == 0){
				f3d_lcd_drawPixel(mb.posX+j, mb.posY+i, c1);			
			}
		}
	}
}

void initMovingBlock(mblock* mb, int x, int y){
	int i,j;

	uint16_t tsprite[16][32] = {
	    {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
	    {7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7},
	    {7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7},
	    {7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7},
	    {7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7},
	    {7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7},
	    {7, 7, 7, 0, 0, 0, 0, 8, 8, 8, 0, 0, 0, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 8, 8, 8, 0, 0, 0, 7, 7, 7},
	    {7, 7, 0, 0, 0, 0, 8, 8, 0, 8, 8, 0, 0, 0, 7, 7, 7, 7, 0, 0, 0, 0, 8, 8, 0, 8, 8, 0, 0, 0, 7, 7},
	    {7, 7, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0, 7, 7},
	    {7, 0, 0, 0, 0, 0, 8, 8, 8, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 8, 8, 8, 0, 0, 0, 0, 0, 0, 7},
	    {7, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 7},
	    {7, 0, 0, 0, 0, 8, 8, 0, 0, 8, 8, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 8, 8, 0, 0, 8, 8, 0, 0, 0, 0, 7},
	    {7, 7, 0, 0, 0, 0, 8, 8, 8, 8, 0, 0, 0, 0, 7, 7, 7, 7, 0, 0, 0, 0, 8, 8, 8, 8, 0, 0, 0, 0, 7, 7},
	    {7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7},
	    {7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7},
	    {7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7}
    };
    for(i=0; i<16; ++i){
		for(j=0; j<32; ++j){
			(*mb).sprite[i][j] = tsprite[i][j];
		}
	}
	(*mb).posX = x;
	(*mb).posY = y;
}

int moveMovingBlock(int dir, level* lv,player* p1, player* p2){
	int i,j;
	int moved = 0;
	int oldX = (*lv).mb.posX;
	int oldY = (*lv).mb.posY;
	int nextx,nexty;
	if(dir==LEFT){
		nextx = oldX-16;
		nexty = oldY;
		if(nextx>=0&&(*lv).state[nexty/16][nextx/16]==0&&((*p2).posX!=nextx||(*p2).posY!=nexty)&&((*p1).posX!=nextx||(*p1).posY!=nexty)){
			moved = 1;
			(*lv).state[nexty/16][nextx/16] = (*lv).state[oldY/16][oldX/16];
			(*lv).state[oldY/16][oldX/16] = 14;
			(*lv).state[oldY/16][oldX/16 +1] = 0;
			(*lv).mb.posX = nextx;
			drawTile(oldX/16 +1, oldY/16);
			drawMovingBlock((*lv).mb, 0xA140);
			return 1;
		}
	}
	if(dir == RIGHT){
		nextx = oldX+16;
		nexty = oldY;
		if(nextx<=96&&(*lv).state[nexty/16][nextx/16 +1]==0&&((*p2).posX!=nextx+16||(*p2).posY!=nexty)&&((*p1).posX!=nextx+16||(*p1).posY!=nexty)){
			moved = 1;
			(*lv).state[nexty/16][nextx/16+1] = (*lv).state[oldY/16][oldX/16];
			(*lv).state[nexty/16][nextx/16] = 13;
			(*lv).state[oldY/16][oldX/16] = 0;
			(*lv).mb.posX = nextx;
			drawTile(oldX/16, oldY/16);
			drawMovingBlock((*lv).mb, 0xA140);
			return 1;
		}
	}
	return 0;
}