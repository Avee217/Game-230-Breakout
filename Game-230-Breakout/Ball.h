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

    float xVelocity = 5.0f;
    float yVelocity = 5.0f;

public:
    Ball(float startX, float startY);

    FloatRect getPosition();

    RectangleShape getShape();

    float getXVelocity();

    void reboundSides();

    void reboundPaddleOrTop();

    void hitBottom();

    void update();

};