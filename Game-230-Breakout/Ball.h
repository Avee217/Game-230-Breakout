#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball
{
private:
    Vector2f position;
    RectangleShape ballShape;
    float xVelocity = 0.0f;
    float yVelocity = 0.0f;
    float width = 15.0f;
    float height = 15.0f;
    Texture ballTexture;  

public:
    Ball(float startX, float startY);
    FloatRect getPosition();
    RectangleShape getShape();
    float getXVelocity();
    void setYVelocity(float speed);
    void setXVelocity(float speed);
    void setPosition(float X, float Y);
    void reboundSides();
    void reboundPaddle(float paddleX,float paddleWidth);
    void reboundTop();
    void hitBottom();
    void reboundBrick(float brickTop, float brickBottom, float brickLeft, float brickRight);
    void update(float timeElapsed);
    void reset(float startX,float startY);

};