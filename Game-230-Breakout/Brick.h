#pragma once
#include<SFML/Graphics.hpp>

using namespace sf;

class Brick
{
private:
    Vector2f position;
    float brickHeight;
    float brickWidth;
    float brickHealth;
    Texture brickTexture;
    Texture brickBrokenTexture;
    Texture brickHeavyTexture;
    Texture brickMovingTexture;
    Texture brickNoBreakTexture;
    RectangleShape brickShape;
    float brickSpeed = 0.0f;

public:

    Brick();
    void setPosition(float startX, float startY);
    void setHealth(float health,int j);
    void setSpeed(float speed);
    float getHealth();
    FloatRect getPosition();
    RectangleShape getShape();
    void hit();  
    void reboundSides();
    void update(float timeElapsed);
    void reset(float startX, float startY,float health);
};