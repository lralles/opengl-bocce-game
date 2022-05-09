#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "collisions .h"
#include <cstdio>

// Checa se 2 bolas colidiram
bool checkCollision(Ball ball1, Ball ball2){
	float distance = sqrt(
		pow(ball1.position.x - ball2.position.x,2) +
		pow(ball1.position.y - ball2.position.y,2) +
		pow(ball1.position.z - ball2.position.z,2) 
	);
	if( distance <= ball1.radius + ball2.radius ){
		return true;
	}
	return false;
}


// Aplica uma colisao elastica em 2 bolas
void applyCollision(Ball* ball1, Ball* ball2){
	glm::vec3 v1 = ball1->velocity;
	glm::vec3 v2 = ball2->velocity;
	glm::vec3 x1 = ball1->position;
	glm::vec3 x2 = ball2->position;

	glm::vec3 v1_new = v1-(float)(dotproduct_vec3(v1-v2, x1-x2)/pow(norm_vec3(x1-x2),2.0f))*(x1-x2);
	glm::vec3 v2_new = v2-(float)(dotproduct_vec3(v2-v1, x2-x1)/pow(norm_vec3(x2-x1),2.0f))*(x2-x1);
	
	ball1->velocity = v1_new;
	ball2->velocity = v2_new;
		
	if( norm_vec3(ball1->velocity) != 0){
		ball1->stationary = false;
	}else{
		ball1->stationary = true;
	}
									
	if( norm_vec3(ball2->velocity) != 0){
		ball2->stationary = false;
	}else{
		ball2->stationary = true;
	}
}


// implementa dotproduct e norma de vec3
float dotproduct_vec3(glm::vec3 v1, glm::vec3 v2){
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}
float norm_vec3(glm::vec3 v){
	return sqrt(v.x*v.x +v.y*v.y + v.z*v.z);
}