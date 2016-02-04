#include <structures.h>
#include <player.h>
#include <level.h>
#include <f3d_lcd_sd.h>

void drawPlayer(player p){
	int i,j;
	for(i=0; i<16; ++i){
		for(j=0; j<16; ++j){
			if(p.sprite[i][j] != 7){
				f3d_lcd_drawPixel(p.posX+j, p.posY+i, p.sprite[i][j]);			
			}
		}
	}
}

void drawPenises(){
	if(rand()%100<15){
		unsigned int colors[8] = {		
		0x0000,
		0x001F,
		0x07E0,
		0x07FF,
		0xF800,
		0xF81F,
		0xFFE0,
		0xFFFF};

		unsigned int color = colors[rand()%8];

		int tmps[14][9] = {
		  0,0,0,1,1,1,0,0,0,
		  0,0,1,0,1,0,1,0,0,
		  0,0,1,0,0,0,1,0,0,
		  0,0,1,1,1,1,1,0,0,
		  0,0,1,0,0,0,1,0,0,
		  0,0,1,0,0,0,1,0,0,
		  0,0,1,0,0,0,1,0,0,
		  0,0,1,0,0,0,1,0,0,
		  0,0,1,0,0,0,1,0,0,
		  0,1,0,0,0,0,0,1,0,
		  1,0,0,0,0,0,0,0,1,
		  1,0,0,0,0,0,0,0,1,
		  1,0,0,0,1,0,0,0,1,
		  0,1,1,1,0,1,1,1,0};	
		int posx = rand()%200 - 10;
		int posy = rand()%200 - 10;
		int r;
		int c;
		int val = rand()%4;
		if (val==0){
			for(r = 0; r<14;r++){
				for(c=0;c<9;c++){
					if(tmps[r][c]==1){
					f3d_lcd_drawPixel(posx+r,posy+c,color);
					}
				}
			}
		}
		else if(val==1){
			for(r = 0; r<14;r++){
				for(c=0;c<9;c++){
					if(tmps[r][c]==1){
					f3d_lcd_drawPixel(posy+c,posx+r,color);
					}
				}
			}
		}
		else if (val==2){
			for(r = 0; r<14;r++){
				for(c=0;c<9;c++){
					if(tmps[r][c]==1){
					f3d_lcd_drawPixel(posx+14-r,posy+9-c,color);
					}
				}
			}
		}
		else if(val==3){
			for(r = 0; r<14;r++){
				for(c=0;c<9;c++){
					if(tmps[r][c]==1){
					f3d_lcd_drawPixel(posy+9-c,posx+14-r,color);
					}
				}
			}
		}
}
}

player initP1(){
	player p1;
	int i,j;
	uint16_t tsprite[16][16] = {
	    {7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7},
	    {7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7},
	    {7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7},

	    {7, 7, 7, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 7, 7, 7},
	    {7, 7, 7, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 7, 7, 7},
	    {7, 7, 7, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 7, 7, 7},

	    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

	    {0x001F, 0x001F, 0x001F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x001F, 0x001F, 0x001F},
	    {0x001F, 0x001F, 0x001F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x001F, 0x001F, 0x001F},
	    {0x001F, 0x001F, 0x001F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x001F, 0x001F, 0x001F},
	    {0x001F, 0x001F, 0x001F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x001F, 0x001F, 0x001F},

	    {7, 7, 7, 0, 0, 0, 7, 7, 7, 7, 0, 0, 0, 7, 7, 7},
	    {7, 7, 7, 0, 0, 0, 7, 7, 7, 7, 0, 0, 0, 7, 7, 7},
	    {7, 7, 7, 0, 0, 0, 7, 7, 7, 7, 0, 0, 0, 7, 7, 7}
    };

    for(i=0; i<16; ++i){
		for(j=0; j<16; ++j){
			p1.sprite[i][j] = tsprite[i][j];
		}
	}
	p1.posX = 64;
	p1.posY = 64;
	p1.curlvlmoves = 0;
	return p1;
}

player initP2(){
	player p2;
	int i,j;
	uint16_t tsprite[16][16] = {
	    {7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7},
	    {7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7},
	    {7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7},

	    {7, 7, 7, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 7, 7, 7},
	    {7, 7, 7, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 7, 7, 7},
	    {7, 7, 7, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 7, 7, 7},

	    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

	    {0xF800, 0xF800, 0xF800, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xF800, 0xF800, 0xF800},
	    {0xF800, 0xF800, 0xF800, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xF800, 0xF800, 0xF800},
	    {0xF800, 0xF800, 0xF800, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xF800, 0xF800, 0xF800},
	    {0xF800, 0xF800, 0xF800, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xF800, 0xF800, 0xF800},

	    {7, 7, 7, 0, 0, 0, 7, 7, 7, 7, 0, 0, 0, 7, 7, 7},
	    {7, 7, 7, 0, 0, 0, 7, 7, 7, 7, 0, 0, 0, 7, 7, 7},
	    {7, 7, 7, 0, 0, 0, 7, 7, 7, 7, 0, 0, 0, 7, 7, 7}
    };

    for(i=0; i<16; ++i){
		for(j=0; j<16; ++j){
			p2.sprite[i][j] = tsprite[i][j];
		}
	}

	p2.posX = 16;
	p2.posY = 16;
	p2.curlvlmoves = 0;
	return p2;	
}

void movePlayer(player* p, player* p2, int dir, level* lv, options* op){
	if(dir==STAND) return;
	if((*op).dicks) drawPenises();
	int i,j;
	int moved = 0;
	int oldX = (*p).posX;
	int oldY = (*p).posY;
	int nextx,nexty;
	if(dir==LEFT){
		nextx = oldX-16;
		nexty = oldY;
		if(nextx>=0&&(*lv).state[nexty/16][nextx/16]==0 && (nextx != (*p2).posX || nexty != (*p2).posY)){
			moved = 1;
			(*p).posX = nextx;
		}else if(nextx>=0&&(*lv).state[nexty/16][nextx/16] >=3){
			if(moveBlock((*lv).state[nexty/16][nextx/16]-3, dir, lv,p2,op)){
				moved = 1;
				(*p).posX = nextx;
			}
		}
	}
	if(dir == RIGHT){
		nextx = oldX+16;
		nexty = oldY;
		if(nextx<=112&&(*lv).state[nexty/16][nextx/16]==0 && (nextx != (*p2).posX || nexty != (*p2).posY)){
			moved = 1;
			(*p).posX = nextx;
		}else if(nextx<=112&&(*lv).state[nexty/16][nextx/16] >=3){
			if(moveBlock((*lv).state[nexty/16][nextx/16]-3, dir, lv,p2,op)){
				moved = 1;
				(*p).posX = nextx;
			}
		}
	}
	if(dir == UP){
		nextx = oldX;
		nexty = oldY-16;
		if(nexty>=0&&(*lv).state[nexty/16][nextx/16]==0 && (nextx != (*p2).posX || nexty != (*p2).posY)){
			moved = 1;
			(*p).posY = nexty;
		}else if(nexty>=0 && (*lv).state[nexty/16][nextx/16] >=3){
			if(moveBlock((*lv).state[nexty/16][nextx/16]-3, dir, lv,p2,op)){
				moved = 1;
				(*p).posY = nexty;
			}
		}
	}
	if(dir == DOWN){
		nextx = oldX;
		nexty = oldY+16;
		if(nexty<=144&&(*lv).state[nexty/16][nextx/16]==0 && (nextx != (*p2).posX || nexty != (*p2).posY)){
			moved = 1;
			(*p).posY = nexty;
		}else if(nexty<=144&&(*lv).state[nexty/16][nextx/16] >=3){
			if(moveBlock((*lv).state[nexty/16][nextx/16]-3, dir, lv,p2,op)){
				moved = 1;
				(*p).posY = nexty;
			}
		}
	}
	if(moved){
		// for(i=0;i<16;++i){
		// 	for(j=0;j<16;++j){
		// 		f3d_lcd_drawPixel(oldX+i,oldY + j, YELLOW);
		// 	}
		// }
		(*p).curlvlmoves++;
		drawTile(oldX/16, oldY/16);
		// drawLevel(*lv);
		drawPlayer(*p);

	}
	return;
}
