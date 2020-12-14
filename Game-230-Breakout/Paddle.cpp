#include "Paddle.h"

// This the constructor and it is called when we create an object
Paddle::Paddle(float startX, float startY)
{   
    paddleHeight = 15;
    paddleWidth = 100;
    position.x = startX-paddleWidth/2.0f;
    position.y = startY;
    paddle3Texture.loadFromFile("Sprites/Paddle3b.png");
    paddle2Texture.loadFromFile("Sprites/Paddle2b.png");
    paddle1Texture.loadFromFile("Sprites/Paddle1b.png");
    paddleSprite.setTexture(paddle3Texture);
    // change speeds
    paddleShape.setSize(sf::Vector2f(paddleWidth, paddleHeight));
    paddleSprite.setScale(sf::Vector2f(paddleWidth, paddleHeight));
    paddleShape.setTexture(&paddle3Texture);
    paddleShape.setPosition(position);
    paddleSprite.setPosition(position);
}
FloatRect Paddle::getPosition()
{
    return paddleShape.getGlobalBounds();
}

Sprite Paddle::getSprite() {
    return paddleSprite;
}

void Paddle::changeTexture(int lives) {
    if (lives == 3)
        paddleShape.setTexture(&paddle3Texture);

    if (lives == 2)
        paddleShape.setTexture(&paddle2Texture);

    if (lives == 1)
        paddleShape.setTexture(&paddle1Texture);

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
    paddleSprite.setPosition(position);
}
void Paddle::reset(float startX, float startY)
{
    position.x = startX;
    position.y = startY;
}