#include "Ball.h"

// This the constructor and it is called when we create an object
Ball::Ball(float startX, float startY)
{
    position.x = startX;
    position.y = startY;

    ballShape.setSize(sf::Vector2f(10, 10));
    ballShape.setPosition(position);
}
FloatRect Ball::getPosition()
{
    return ballShape.getGlobalBounds();
}

RectangleShape Ball::getShape()
{
    return ballShape;
}

float Ball::getXVelocity()
{
    return xVelocity;
}

void Ball::reboundSides()
{
    xVelocity = -xVelocity;
}
// split  and change pos y reset val

void Ball::reboundPaddle(float paddleX, float paddleWidth) 
{
    float paddleHitPos = (position.x - paddleX) / (paddleWidth / 2);
    yVelocity = abs(yVelocity) + 50;
    if (yVelocity > 400) yVelocity = 400;
    yVelocity = -yVelocity;
    xVelocity = -100 * (1.0f - paddleHitPos);

}

void Ball::reboundTop()
{
    yVelocity = -yVelocity;
}

void Ball::hitBottom()
{
    position.y = 1;
    position.x = 500;
}

void Ball::update(float timeElapsed)
{
    // Update the ball position variables
    position.y += yVelocity * timeElapsed;
    position.x += xVelocity * timeElapsed;

    // Move the ball and the bat
    ballShape.setPosition(position);
}
void Ball::reset(float startX, float startY)
{
    position.x = startX;
    position.y = startY;
    if (xVelocity < 0)
        xVelocity = -100.0f;
    else
        xVelocity = 100.0f;
    yVelocity = 0.0f;
}