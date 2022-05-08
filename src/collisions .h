#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "constants.h"

#define RADIUS 0.1f
// Objeto Bola
typedef struct{
	float radius = RADIUS; 

	glm::vec3 position;
	glm::vec3 velocity;

	bool onFloor = false;
	bool stationary = false;

	void applyAmbientForces(float t_delta){
		if(!onFloor){
			applyGravity(t_delta);
		}else if (!stationary){
			applyDrag(t_delta);
		}
		checkWalls();
	}

	void applyGravity(float t_delta){
		if(onFloor){
			return;
		}
		if(position.y > -1.0f + radius ){
			velocity.y -= t_delta * GRAVITY;
		}
		else{
			if(fabs(velocity.y) > 0.2f){
				velocity.y *= -0.3f;
				return;
			}
			onFloor = true;
			velocity.y = 0.0f;
			position.y = -1.0f + radius;
		}
	}

	void applyDrag(float t_delta){
		if(stationary){
			return;
		}
		float velocityModule = sqrt(velocity.x*velocity.x + velocity.z*velocity.z);
		if (velocityModule <= DRAG * t_delta){
			stationary = true;
			velocity.x = velocity.z = 0.0f;
			return;
		}
		float newVelocityModule = velocityModule - DRAG * t_delta;
		velocity.x = velocity.x/velocityModule * newVelocityModule;
		velocity.z = velocity.z/velocityModule * newVelocityModule;
	}
	void checkWalls(){
		if (fabs(position.x) > WIDTH - radius){
			velocity.x *= -1;
		}
		if(fabs(position.z) > DEPTH - radius ){
			velocity.z *= -1;
		}
	}

}Ball;


bool checkCollision(Ball ball1, Ball ball2);
void applyCollision(Ball* ball1, Ball* ball2);

float dotproduct_vec3(glm::vec3 v1, glm::vec3 v2);
float norm_vec3(glm::vec3 v);