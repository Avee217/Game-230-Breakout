#include "Brick.h"
#include<math.h>

Brick::Brick()
{

    brickHeight = 20;
    brickWidth = 70;
    brickHealth = 0;
    //brickTexture.loadFromFile("Sprites/Brick.png");
    //brickSprite.setTexture(brickTexture);
  

    brickShape.setSize(sf::Vector2f(brickWidth, brickHeight));
    brickShape.setFillColor(sf::Color::Color(255, 0, 0, 255));
    //brickShape.setTexture(&brickTexture);
    brickShape.setPosition(position);
}
void Brick::setPosition(float startX, float startY)
{
    position.x = startX;
    position.y = startY;
    brickShape.setPosition(position);

}
void Brick::setHealth(float health)
{
    brickHealth = health;
}
float Brick::getHealth()
{
    return brickHealth;
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