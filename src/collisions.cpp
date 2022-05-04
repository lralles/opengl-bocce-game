#include "collisions.h"

int distance(int a, int b){
    return abs(a-b);
}

bool checkCollision(Ball ball, Ball ball2)
{
    int distx = distance(ball.position.x,ball2.position.x);
    int disty = distance(ball.position.y,ball2.position.y);
    int distz = distance(ball.position.z,ball2.position.z);

    if(distx > ball.radius + ball2.radius || disty > ball.radius + ball2.radius || distz > ball.radius + ball2.radius)
        return true;
    else
        return false;
}
/*
bool checkCollisionPlane(Ball ball, glm::mat4 mod)
{
    // colisão das paredes com a bola, terminar!
}*/

