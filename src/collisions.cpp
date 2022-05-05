#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef struct{
	float radius;
	glm::vec3 position;
	glm::vec3 velocity;
}Ball;

int distance(int a, int b);
bool checkCollision(Ball ball, Ball ball2);