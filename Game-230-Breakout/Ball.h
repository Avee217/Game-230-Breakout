#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball
{
private:
    Vector2f position;

    // A RectangleShape object called ref
    //change speeds
    RectangleShape ballShape;

    float xVelocity = 50.0f;
    float yVelocity = 50.0f;
    float width = 10.0f;
    float height = 10.0f;
    

public:
    Ball(float startX, float startY);

    FloatRect getPosition();

    RectangleShape getShape();

    float getXVelocity();

    void reboundSides();

    void reboundPaddle(float paddleX,float paddleWidth);
    void reboundTop();
    void hitBottom();

    void update(float timeElapsed);
    void reset(float startX,float startY);

};