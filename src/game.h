#include "src/collisions .h"

typedef struct {
	Ball blueBalls[3];
	int blueBallsInGame = 0;
	Ball orangeBalls[3];
	int orangeBallsInGame = 0;
	Ball bolim;
	bool bolimInGame = false;
	bool noMovement;

}Game;

