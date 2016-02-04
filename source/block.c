#include <structures.h>
#include <block.h>
#include <level.h>
#include <f3d_lcd_sd.h>
#include <stdio.h>
#include <audioPlayer.h>


void drawBlock(block b, uint16_t c1, uint16_t c2){
	int i,j;
	drawTile(b.posX/16, b.posY/16);
	for(i=0; i<16; ++i){
		for(j=0; j<16; ++j){
			if(b.sprite[i][j] == 0){
				f3d_lcd_drawPixel(b.posX+j, b.posY+i, c1);			
			}else if(b.sprite[i][j] == 8){
				f3d_lcd_drawPixel(b.posX+j, b.posY+i, c2);			
			}
		}
	}
}

void initBlock(block* b, int x, int y){
	int i,j;

	uint16_t tsprite[16][16] = {
	    {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
	    {7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7},
	    {7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7},
	    {7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7},
	    {7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7},
	    {7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7},
	    {7, 7, 7, 0, 0, 0, 0, 8, 8, 8, 0, 0, 0, 7, 7, 7},
	    {7, 7, 0, 0, 0, 0, 8, 8, 0, 8, 8, 0, 0, 0, 7, 7},
	    {7, 7, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0, 7, 7},
	    {7, 0, 0, 0, 0, 0, 8, 8, 8, 0, 0, 0, 0, 0, 0, 7},
	    {7, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 7},
	    {7, 0, 0, 0, 0, 8, 8, 0, 0, 8, 8, 0, 0, 0, 0, 7},
	    {7, 7, 0, 0, 0, 0, 8, 8, 8, 8, 0, 0, 0, 0, 7, 7},
	    {7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7},
	    {7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7},
	    {7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7}
    };
    for(i=0; i<16; ++i){
		for(j=0; j<16; ++j){
			(*b).sprite[i][j] = tsprite[i][j];
		}
	}
	(*b).posX = x;
	(*b).posY = y;
}

int moveBlock(int bn, int dir, level* lv, player* p2, options* op)
{
	int i,j;
	int moved = 0, dropped = 0;
	int oldX = (*lv).blocks[bn].posX;
	int oldY = (*lv).blocks[bn].posY;
	int nextx,nexty;
	if(dir==LEFT){
		nextx = oldX-16;
		nexty = oldY;
		if(nextx>=0&&(*lv).state[nexty/16][nextx/16]==0&&((*p2).posX!=nextx||(*p2).posY!=nexty)){
			moved = 1;
			(*lv).state[nexty/16][nextx/16] = (*lv).state[oldY/16][oldX/16];
			(*lv).state[oldY/16][oldX/16] = 0;
			(*lv).blocks[bn].posX = nextx;
		}
		else if(nextx>=0&&(*lv).state[nexty/16][nextx/16]==2){
			(*lv).state[oldY/16][oldX/16] = 0;
			(*lv).blocks[bn].posX = nextx;
			moved = 1;
			dropped = 1;
			drawBlock((*lv).blocks[bn],0x3C0,YELLOW);
			
		}
	}
	if(dir == RIGHT){
		nextx = oldX+16;
		nexty = oldY;
		if(nextx<=112&&(*lv).state[nexty/16][nextx/16]==0&&((*p2).posX!=nextx||(*p2).posY!=nexty)){
			moved = 1;
			(*lv).state[nexty/16][nextx/16] = (*lv).state[oldY/16][oldX/16];
			(*lv).state[oldY/16][oldX/16] = 0;
			(*lv).blocks[bn].posX = nextx;
		}
		else if(nextx<=112&&(*lv).state[nexty/16][nextx/16]==2){
			(*lv).state[oldY/16][oldX/16] = 0;
			(*lv).blocks[bn].posX = nextx;
			moved = 1;
			dropped = 1;
			drawBlock((*lv).blocks[bn],0x3C0,YELLOW);
		}
	}
	if(dir == UP){
		nextx = oldX;
		nexty = oldY-16;
		if(nexty>=0&&(*lv).state[nexty/16][nextx/16]==0&&((*p2).posY!=nexty||(*p2).posX!=nextx)){
			moved = 1;
			(*lv).state[nexty/16][nextx/16] = (*lv).state[oldY/16][oldX/16];
			(*lv).state[oldY/16][oldX/16] = 0;
			(*lv).blocks[bn].posY = nexty;
		}
		else if(nexty>=0&&(*lv).state[nexty/16][nextx/16]==2){
			(*lv).state[oldY/16][oldX/16] = 0;
			(*lv).blocks[bn].posY = nexty;
			moved = 1;
			dropped = 1;
			drawBlock((*lv).blocks[bn],0x3C0,YELLOW);
		}

	}
	if(dir == DOWN){
		nextx = oldX;
		nexty = oldY+16;
		if(nexty<=144&&(*lv).state[nexty/16][nextx/16]==0&&((*p2).posY!=nexty||(*p2).posX!=nextx)){
			moved = 1;
			(*lv).state[nexty/16][nextx/16] = (*lv).state[oldY/16][oldX/16];
			(*lv).state[oldY/16][oldX/16] = 0;
			(*lv).blocks[bn].posY = nexty;
		}
		else if(nexty<=144&&(*lv).state[nexty/16][nextx/16]==2){
			(*lv).state[oldY/16][oldX/16] = 0;
			(*lv).blocks[bn].posY = nexty;
			moved = 1;
			dropped = 1;
			drawBlock((*lv).blocks[bn],0x3C0,YELLOW);
		}
	}
	if(moved){
		// for(i=0;i<16;++i){
		// 	for(j=0;j<16;++j){
		// 		f3d_lcd_drawPixel(oldX+i,oldY + j, YELLOW);
		// 	}
		// }
		drawTile(oldX/16, oldY/16);

		// int l,m;
		// for(l=0;l<8;++l){
		// 	for(m=0;m<10;++m){
		// 		printf("%d \n",(*lv).state[m][l]);
		// 	}
		// 	// printf("\n");
		// }
		if(!dropped){
			drawBlock((*lv).blocks[bn], 0xA140,YELLOW);
		}
		else{
			//playFile("chaching.wav");
			(*lv).blocksLeft--;
			// if((*op).music)
				
		}
		return 1;
	}
	return 0;
}