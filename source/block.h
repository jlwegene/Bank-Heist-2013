#define STAND 0
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

void drawBlock(block b, uint16_t c1, uint16_t c2);

int moveBlock(int bn, int dir, level* lv, player* p2, options* op);

void initBlock(block* b, int x, int y);