#include "Paddle.h"

// This the constructor and it is called when we create an object
Paddle::Paddle(float startX, float startY)
{   
    paddleHeight = 5;
    paddleWidth = 100;
    position.x = startX-paddleWidth/2.0f;
    position.y = startY;
    // change speeds
    paddleShape.setSize(sf::Vector2f(100, 5));
    paddleShape.setPosition(position);
}
FloatRect Paddle::getPosition()
{
    return paddleShape.getGlobalBounds();
}

RectangleShape Paddle::getShape()
{
    return paddleShape;
}

void Paddle::moveLeft(float timerElapsed)
{
    if(position.x>=0)
        position.x -= paddleSpeed*timerElapsed;
}

void Paddle::moveRight(float timeElapased)
{
    if(position.x<= 800-paddleWidth)
        position.x += paddleSpeed*timeElapased;
}

void Paddle::update(float timerElapsed)
{
    paddleShape.setPosition(position);
}
void Paddle::reset(float startX, float startY)
{
    position.x = startX;
    position.y = startY;
}