#include "Ball.h"
Ball::Ball(float startX, float startY)
{
    position.x = startX-width/2.0f;
    position.y = startY;
    ballTexture.loadFromFile("Sprites/Ball.png");
    ballShape.setTexture(&ballTexture);
    ballShape.setSize(sf::Vector2f(height, width));
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

void Ball::setYVelocity(float speed)
{
    yVelocity = speed;
}

void Ball::setXVelocity(float speed)
{
    xVelocity = speed;
}


void Ball::setPosition(float X, float Y)
{
    position.x = X;
    position.y = Y;
}
void Ball::reboundSides()
{
    xVelocity = -xVelocity;
}

void Ball::reboundPaddle(float paddleX, float paddleWidth) 
{
    float paddleHitPos = (position.x - paddleX) / (paddleWidth / 2);
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
    xVelocity = 0;
    yVelocity = 0;
}

void Ball::reboundBrick(float brickTop, float brickBottom, float brickLeft, float brickRight)
{
    float ballTop, ballBottom, ballLeft, ballRight;
    ballTop = getPosition().top;
    ballBottom = getPosition().top+ getPosition().height;
    ballLeft = getPosition().left;
    ballRight = getPosition().left+getPosition().width;

    float distanceX1 = abs(ballRight - brickLeft);
    float distanceX2 = abs(ballLeft - brickRight);
    float distanceY1 = abs(ballTop - brickBottom);
    float distanceY2 = abs(ballBottom - brickTop);

    // From bottom
    if (yVelocity < 0 && distanceY1 < distanceY2 && distanceY1 < distanceX1 && distanceY1 < distanceX2)
    {
        yVelocity = abs(yVelocity);
    }
    // From top
    if (yVelocity > 0 && distanceY2 < distanceY1 && distanceY2 < distanceX1 && distanceY2 < distanceX2)
    {
        yVelocity = -abs(yVelocity);
    }
    // From left
    if (xVelocity > 0 && distanceX1 < distanceX2 && distanceX1 < distanceY1 && distanceX1 < distanceY2)
    {
        xVelocity = -abs(xVelocity);
    }
    // From right
    if (xVelocity < 0 && distanceX2 < distanceX1 && distanceX2 < distanceY1 && distanceX2 < distanceY2)
    {
        xVelocity = abs(xVelocity);
    }
}

void Ball::update(float timeElapsed)
{
    position.y += yVelocity * timeElapsed;
    position.x += xVelocity * timeElapsed;
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