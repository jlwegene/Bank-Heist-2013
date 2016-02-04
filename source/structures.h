#include <f3d_nunchuk.h>
typedef struct players {
	int posX;
	int posY;
	int curlvlmoves;

	uint16_t sprite[16][16];

} player;

typedef struct block {
	int posX;
	int posY;

	uint16_t sprite[16][16];

} block;

typedef struct mblock {
	int posX;
	int posY;

	uint16_t sprite[16][32];

} mblock;

typedef struct level {
	int state[10][8];
	block blocks[10];
	mblock mb;
	int blocksLeft;
} level;

typedef struct scores {
	char names[10][25];
	int moves[10];
	char strmoves[10][5];
} scores;

typedef struct options {
	uint8_t music;
	uint8_t dicks;
	uint8_t instructions;
	uint8_t leds;
} options;