#include "Brick.h"
#include<math.h>

Brick::Brick()
{   
    brickHeight = 20;
    brickWidth = 70;
    brickHealth = 0;
    brickTexture.loadFromFile("Sprites/BrickBasic.png");
    brickBrokenTexture.loadFromFile("Sprites/BrickBroken.png");
    brickHeavyTexture.loadFromFile("Sprites/BrickHeavy.png");
    brickMovingTexture.loadFromFile("Sprites/BrickMoving.png");
    brickNoBreakTexture.loadFromFile("Sprites/BrickNoBreak.png");
    brickShape.setSize(sf::Vector2f(brickWidth, brickHeight));    
    brickShape.setPosition(position);
}

void Brick::setPosition(float startX, float startY)
{
    position.x = startX;
    position.y = startY;
    brickShape.setPosition(position);
}

void Brick::setHealth(float health,int j)
{
    brickHealth = health;
    brickShape.setTexture(&brickTexture);
    if (brickHealth == 2)
        brickShape.setTexture(&brickHeavyTexture);
    if (j == 2 || j == 5) {
        brickShape.setTexture(&brickNoBreakTexture);
    }
}

void Brick::setSpeed(float speed)
{
    brickSpeed = speed;
    brickShape.setTexture(&brickMovingTexture);
}

float Brick::getHealth()
{
    return brickHealth;
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
    if (brickHealth == 1)
        brickShape.setTexture(&brickBrokenTexture);

}

void Brick::reboundSides()
{
    brickSpeed = -brickSpeed;
}

void Brick::update(float timeElapsed)
{
    position.x += brickSpeed * timeElapsed;
    brickShape.setPosition(position);
}

void Brick::reset(float startX, float startY, float health)
{
    position.x = startX;
    position.y = startY;
    brickHealth = health;
}