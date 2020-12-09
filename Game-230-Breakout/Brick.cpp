#include "Brick.h"
#include<math.h>

Brick::Brick(float startX, float startY,float health)
{

    brickHeight = 75;
    brickWidth = 5;
    position.x = startX;
    position.y = startY;
    brickHealth = health;


    brickShape.setSize(sf::Vector2f(brickWidth, brickHeight));
    brickShape.setPosition(position);
}

//void Brick::setSpeed(float speed)
//{
//    brickSpeed = speed;
//}
void Brick::changeSize(float width, float height)
{
    brickWidth = width;
    brickHeight = height;
   
    brickShape.setSize(sf::Vector2f(brickWidth, brickHeight));
}

FloatRect Brick::getPosition()
{
    return brickShape.getGlobalBounds();
}

RectangleShape Brick::getShape()
{
    return brickShape;
}

void Brick::hit()
{
    brickHealth--;

}

bool Brick::getRenderStatus()
{
    if (brickHealth == 0)
    {
        return false;
    }
    return true;
}

//
//void Brick::update(float timeElapsed)
//{
//    position.y += brickSpeed * timeElapsed;
//    brickShape.setPosition(position);
//}

void Brick::reset(float startX, float startY, float health)
{
    position.x = startX;
    position.y = startY;
    brickHealth = health;
}