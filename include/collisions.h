#ifndef COLLISIONS_H
#define COLLISIONS_H
#endif
#include <cmath>
#include <iostream>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef struct{
	float radius;
	glm::vec3 position;
	glm::vec3 velocity;
}Ball;

int distance(int,int);
bool checkCollision(Ball,Ball);
bool checkCollisionPlane(Ball,glm::mat4);


