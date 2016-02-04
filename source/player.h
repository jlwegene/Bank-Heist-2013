#define STAND 0
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

void draw_player(player p);

void movePlayer(player* p, player* p2, int dir, level* lvl, options* op);

player initP1(void);
player initP2(void);