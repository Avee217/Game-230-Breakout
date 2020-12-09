#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Paddle
{
private:
    Vector2f position;
    float paddleHeight;
    float paddleWidth;

    // A RectangleShape object
    RectangleShape paddleShape;

    float paddleSpeed = 100.0f;

public:
    Paddle(float startX, float startY);

    //void setSpeed(float speed);

    FloatRect getPosition();

    RectangleShape getShape();

    void moveLeft(float timerElapsed);

    void moveRight(float timeElapsed);

    void update(float timeElapsed);
    void reset(float startX, float startY);

};