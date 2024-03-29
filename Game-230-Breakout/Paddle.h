#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Paddle
{
private:
    Vector2f position;
    float paddleHeight;
    float paddleWidth;
    Texture paddle1Texture;
    Texture paddle2Texture;
    Texture paddle3Texture;
    RectangleShape paddleShape;
    float paddleSpeed = 200.0f;

public:
    Paddle(float startX, float startY);
    FloatRect getPosition();
    void changeTexture(int lives);
    RectangleShape getShape();
    void moveLeft(float timerElapsed);
    void moveRight(float timeElapsed);
    void update(float timeElapsed);
    void reset(float startX, float startY);

};