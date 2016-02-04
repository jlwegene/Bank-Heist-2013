#include <structures.h>
#include <player.h>
#include <level.h>
#include <f3d_lcd_sd.h>
#include <f3d_uart.h>
#include <block.h>
#include <audioPlayer.h>
#include <movingBlock.h>

//Level State code
// 0 == Empty space
// 1 == Wall
// 2 == Hole
// 3 == 
void resetLevel1(player* p1, player* p2, level* l1){
	int i,j;
	int tmps[10][8] = {
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,4,0,0,0},
		{0,0,1,0,1,0,1,0},
		{0,0,1,3,1,5,1,0},
		{0,0,1,0,1,0,1,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,1,0,1,0,1,0,1},
		{0,2,0,0,2,0,0,2},
		{0,0,0,0,0,0,0,0}
	};
	for(i=0; i<8; ++i){
		for(j=0; j<10; ++j){
			(*l1).state[j][i] = tmps[j][i];
			if(tmps[j][i] >= 3){
				(*l1).blocks[tmps[j][i]-3].posX = i*16; 
				(*l1).blocks[tmps[j][i]-3].posY = j*16; 
			}
		}
	}
	(*p1).posX = 0;
	(*p1).posY = 0;

	(*p2).posX = 16;
	(*p2).posY = 0;
	(*l1).blocksLeft = 3;
	(*p1).curlvlmoves = 0;
	(*p2).curlvlmoves = 0;
}

void initLevel1(player* p1, player* p2, level* l1){
	int i,j;
//level 1
	int tmps[10][8] = {
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,4,0,0,0},
		{0,0,1,0,1,0,1,0},
		{0,0,1,3,1,5,1,0},
		{0,0,1,0,1,0,1,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,1,0,1,0,1,0,1},
		{0,2,0,0,2,0,0,2},
		{0,0,0,0,0,0,0,0}
	};
	for(i=0; i<8; ++i){
		for(j=0; j<10; ++j){
			(*l1).state[j][i] = tmps[j][i];
			if(tmps[j][i] >= 3){
				block tmpb;
				initBlock(&tmpb, i*16, j*16);
				(*l1).blocks[tmps[j][i] - 3] = tmpb;
			}
		}
	}
	//2,2
	(*p1).posX = 0;
	(*p1).posY = 0;

	(*p2).posX = 16;
	(*p2).posY = 0;
	(*l1).blocksLeft = 3;
}

void initLevel2(player* p1, player* p2, level* l1){
	int i,j;
//level 2
	int tmps[10][8] = {
		{0,0,1,0,1,0,0,2},
		{0,0,1,0,0,1,0,1},
		{1,0,0,0,0,0,0,0},
		{1,0,3,1,4,1,5,0},
		{1,0,0,0,0,0,0,0},
		{0,6,0,1,0,0,0,0},
		{0,0,1,0,1,0,0,1},
		{0,0,0,0,1,0,0,1},
		{1,0,1,2,1,1,0,1},
		{0,0,2,1,2,0,0,0}
	};
	for(i=0; i<8; ++i){
		for(j=0; j<10; ++j){
			(*l1).state[j][i] = tmps[j][i];
			if(tmps[j][i] >= 3){
				block tmpb;
				initBlock(&tmpb, i*16,j*16);
				(*l1).blocks[tmps[j][i] - 3] = tmpb;
			}
		}
	}
	//2,2
	(*p1).posX = 0;
	(*p1).posY = 0;

	(*p2).posX = 16;
	(*p2).posY = 0;
	(*l1).blocksLeft = 4;
	(*p1).curlvlmoves = 0;
	(*p2).curlvlmoves = 0;
}
void resetLevel2(player* p1, player* p2, level* l1){
	int i,j;

//actual level 1 //
	int tmps[10][8] = {
		{0,0,1,0,1,0,0,2},
		{0,0,1,0,0,1,0,1},
		{1,0,0,0,0,0,0,0},
		{1,0,3,1,4,1,5,0},
		{1,0,0,0,0,0,0,0},
		{0,6,0,1,0,0,0,0},
		{0,0,1,0,1,0,0,1},
		{0,0,0,0,1,0,0,1},
		{1,0,1,2,1,1,0,1},
		{0,0,2,1,2,0,0,0}
	};
	for(i=0; i<8; ++i){
		for(j=0; j<10; ++j){
			(*l1).state[j][i] = tmps[j][i];
			if(tmps[j][i] >= 3){
				(*l1).blocks[tmps[j][i]-3].posX = i*16; 
				(*l1).blocks[tmps[j][i]-3].posY = j*16; 
			}
		}
	}
	//2,2
	(*p1).posX = 0;
	(*p1).posY = 0;

	(*p2).posX = 16;
	(*p2).posY = 0;
	(*l1).blocksLeft = 4;
	(*p1).curlvlmoves = 0;
	(*p2).curlvlmoves = 0;
}
void initLevel3(player* p1, player* p2, level* l1){
	int i,j;
//level 2
	int tmps[10][8] = {
		{0,1, 0,  1,1,0,0,0},
		{0,0, 0,  0,0,0,0,0},
		{0,1, 0,  1,0,1,1,0},
		{1,0, 0,  1,3,0,0,1},
		{2,1,13, 14,0,1,1,0},
		{0,0, 0,  1,0,0,0,0},
		{0,1, 0,  0,1,0,0,0},
		{1,0, 0,  1,0,1,0,0},
		{0,0, 0,  0,0,4,0,0},
		{0,0, 0,  1,2,1,0,0}
	};
	// int tmps[10][8] = {
	// 	{0,1, 0,  1,1,0,0,0},
	// 	{0,0, 0,  0,0,0,0,0},
	// 	{0,1, 0,  1,0,1,1,0},
	// 	{1,0, 0,  1,3,0,0,1},
	// 	{1,0,13, 14,0,1,0,0},
	// 	{0,0, 0,  1,0,0,0,0},
	// 	{0,1, 0,  0,0,0,0,0},
	// 	{1,0, 0,  0,0,0,0,0},
	// 	{0,0, 0,  0,0,0,0,0},
	// 	{0,0, 0,  0,0,0,0,0}
	// };
	for(i=0; i<8; ++i){
		for(j=0; j<10; ++j){
			(*l1).state[j][i] = tmps[j][i];
			if(tmps[j][i]==13){
				mblock tmpmb;
				initMovingBlock(&tmpmb, i*16,j*16);
				(*l1).mb = tmpmb;
			}
			if(tmps[j][i] >= 3 && tmps[j][i]!=13&& tmps[j][i]!=14){
				block tmpb;
				initBlock(&tmpb, i*16,j*16);
				(*l1).blocks[tmps[j][i] - 3] = tmpb;
			}
		}
	}
	//2,2
	(*p1).posX = 112;
	(*p1).posY = 144;

	(*p2).posX = 96;
	(*p2).posY = 144;
	(*l1).blocksLeft = 4;
	(*p1).curlvlmoves = 0;
	(*p2).curlvlmoves = 0;
}

void resetLevel3(player* p1, player* p2, level* l1){
	int i,j;

//actual level 1 //
	int tmps[10][8] = {
		{0,1, 0,  1,1,0,0,0},
		{0,0, 0,  0,0,0,0,0},
		{0,1, 0,  1,0,1,1,0},
		{1,0, 0,  1,3,0,0,1},
		{2,1,13, 14,0,1,1,0},
		{0,1, 0,  1,0,0,0,0},
		{0,1, 0,  0,1,0,0,0},
		{0,0, 0,  1,0,1,0,0},
		{0,0, 0,  0,0,4,0,0},
		{0,0, 0,  1,2,1,0,0}
	};
	// int tmps[10][8] = {
	// 	{0,1, 0,  1,1,0,0,0},
	// 	{0,0, 0,  0,0,0,0,0},
	// 	{0,1, 0,  1,0,1,1,0},
	// 	{1,0, 0,  1,3,0,0,1},
	// 	{1,0,13, 14,0,1,0,0},
	// 	{0,0, 0,  1,0,0,0,0},
	// 	{0,1, 0,  0,0,0,0,0},
	// 	{1,0, 0,  0,0,0,0,0},
	// 	{0,0, 0,  0,0,0,0,0},
	// 	{0,0, 0,  0,0,0,0,0}
	// };
	for(i=0; i<8; ++i){
		for(j=0; j<10; ++j){
			(*l1).state[j][i] = tmps[j][i];
			if(tmps[j][i]==13){
				(*l1).mb.posX = i*16;
				(*l1).mb.posY = j*16;
			}
			if(tmps[j][i] >= 3&& tmps[j][i]!=13 && tmps[j][i]!=14){
				(*l1).blocks[tmps[j][i]-3].posX = i*16; 
				(*l1).blocks[tmps[j][i]-3].posY = j*16; 
			}
		}
	}
	//2,2
	(*p1).posX = 112;
	(*p1).posY = 144;

	(*p2).posX = 96;
	(*p2).posY = 144;
	(*l1).blocksLeft = 4;
	(*p1).curlvlmoves = 0;
	(*p2).curlvlmoves = 0;
}

void drawTile(int x, int y){
	int l,m;
	for(l=0;l<8;++l){
		for(m=0;m<8;++m){
			f3d_lcd_drawPixel((x*16)+l, (y*16)+m, 0x9CDF);
		}
	}

	for(l=0;l<8;++l){
		for(m=0;m<8;++m){
			f3d_lcd_drawPixel((x*16)+l+8, (y*16)+m, 0xFFF3);
		}
	}
	for(l=0;l<8;++l){
		for(m=0;m<8;++m){
			f3d_lcd_drawPixel((x*16)+l, (y*16)+m+8, 0xFFF3);
		}
	}

	for(l=0;l<8;++l){
		for(m=0;m<8;++m){
			f3d_lcd_drawPixel((x*16)+l+8, (y*16)+m+8, 0x9CDF);
		}
	}
}

void drawLevel(level lvl){
	// printf("HI THIJS\n");
	int i,j,l,m;
	block tmpb;
	for(i=0;i<8;++i){
		for(j=0;j<10;++j){
			switch(lvl.state[j][i]){
				case 0:
						drawTile(i,j);
					break;
				case 1:
					for(l=0;l<16;++l){
						for(m=0;m<16;++m){
							f3d_lcd_drawPixel((i*16)+l, (j*16)+m, BLACK);
						}
					}

					for(l=0;l<16;++l){
						for(m=0;m<16;++m){
							if(!l || !m ||l==15||m==15||l ==m || l+m==15)
								f3d_lcd_drawPixel((i*16)+l, (j*16)+m, 0x514A);
						}
					}

					break;
				case 2:
					initBlock(&tmpb, i*16, j*16);
					drawTile(i,j);
					drawBlock(tmpb, 0x8410, BLACK);
					break;
				default:
					if(lvl.state[j][i] >= 3 && lvl.state[j][i]!=13&& lvl.state[j][i]!=14){
						drawBlock(lvl.blocks[lvl.state[j][i]-3], 0xA140, YELLOW);
					}
					else if(lvl.state[j][i]==13){
						drawMovingBlock(lvl.mb, 0xA140);
					}
					break;
			}
		}
	}
}