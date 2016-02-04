#define STAND 0
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

void drawMovingBlock(mblock b, uint16_t c);

int moveMovingBlock(int dir, level* lv,player* p1, player* p2);

void initMovingBlock(mblock* mb, int x, int y);