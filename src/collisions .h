#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

#define Z_AXIS 2
#define Y_AXIS 1
#define X_AXIS 0

typedef struct{
	float radius = 0.1f;
	glm::vec3 position;
	glm::vec3 velocity;
	float gravity = 0.6f;
	float drag = 0.05f;
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
			velocity.y -= t_delta * gravity;
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
		if (velocityModule <= drag * t_delta){
			stationary = true;
			velocity.x = velocity.z = 0.0f;
			return;
		}
		float newVelocityModule = velocityModule - drag * t_delta;
		velocity.x = velocity.x/velocityModule * newVelocityModule;
		velocity.z = velocity.z/velocityModule * newVelocityModule;
	}
	void checkWalls(){
		if (position.x > 1.0f - radius || position.x < -1.0f + radius){
			velocity.x *= -1;
		}
		if(position.z > 4.0f - radius || position.z < -4.0f + radius){
			velocity.z *= -1;
		}
	}

}Ball;

int distance(int a, int b);

bool checkCollision(Ball ball1, Ball ball2);
void applyCollision(Ball* ball1, Ball* ball2);

float dotproduct_vec3(glm::vec3 v1, glm::vec3 v2);
float norm_vec3(glm::vec3 v);