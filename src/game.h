#include "collisions .h"
#define BALLS 7
#define SIDE_BALLS (BALLS-1)/2
#define THROW_BOLIM 0
#define RED_PLAY 1
#define BLUE_PLAY 2
#define RELEASED 3


typedef struct {
	int blueBallsInGame = 0;
	int redBallsInGame = 0;
	bool bolimInGame = false;
	int gameState =  THROW_BOLIM;	
	bool hasMovement(Ball* balls){
		for (int i = 0; i<BALLS ;i++){
			if(norm_vec3(balls[i].velocity) != 0.0f)
				return false;
		}
		return true;
	}
	int getWinner(Ball* balls){
		float smallestDistance = norm_vec3(balls[1].position - balls[0].position);
		int smallest = 1;
		for (int i = 2 ; i< BALLS ; i++){
			if(norm_vec3(balls[i].position - balls[0].position)<smallestDistance){
				smallestDistance = norm_vec3(balls[i].position - balls[0].position);
				smallest = i;
			}
		}
		return smallest;
	}
}Game;

