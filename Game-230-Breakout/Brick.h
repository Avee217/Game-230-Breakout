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
    Sprite brickSprite;

    RectangleShape brickShape;

    float brickSpeed = 0.0f;
public:

    Brick();
    void setPosition(float startX, float startY);
    void setHealth(float health);
    float getHealth();

    //void setSpeed(float speed);


    FloatRect getPosition();

    bool getRenderStatus();


    void changeSize(float width, float height);

    RectangleShape getShape();
    Sprite getSprite();

    void hit();
    void setSpeed(float speed);
    

    void reboundSides();
    void update(float timeElapsed);
    void reset(float startX, float startY,float health);

};