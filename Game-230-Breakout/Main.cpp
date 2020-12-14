#include "Paddle.h"
#include "Ball.h"
#include"Brick.h"
#include"Menu.h"
#include <sstream>
#include<iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include<chrono>

using namespace sf;

int main()
{
    float windowWidth = 800;
    float windowHeight = 600;

    int i, j;
   

    std::chrono::steady_clock::time_point clockStart = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point clockEnd = std::chrono::steady_clock::now();
    float timeElapsed;

    // Make a window that is 800*600 pixels
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Breakout!");
    window.setFramerateLimit(30); // set FPS Limit

    Menu menu(windowWidth, windowHeight);

    //Flags for game states 
    bool gameRunning = false;
    bool pause = false;
    bool resetGame = false;
    bool ballStart = false;
    bool vm = false;
    bool gom = false;

    int score = 0;
    int lives = 3;
    int brickCount = 38;    // Number of bricks you can break
    float yVelocity = -100.0f;

    //Load Sound files Add error checks 
    SoundBuffer bumpBuffer;
    if (!bumpBuffer.loadFromFile("Sounds/Bump.wav")) {
        std::cout << "Bump Sound Error" << std::endl;
    }
    Sound bump(bumpBuffer);
    bump.setVolume(50);

    SoundBuffer breakBuffer;
    if (!breakBuffer.loadFromFile("Sounds/Break.wav")) {
        std::cout << "Bump Sound Error" << std::endl;
    }
    Sound breakSound(breakBuffer);
    breakSound.setVolume(75);
    
    SoundBuffer lifeLostBuffer;
    if (!lifeLostBuffer.loadFromFile("Sounds/LifeLost.wav")) {
        std::cout << "Bump Sound Error" << std::endl;
    }
    Sound lifeLost(lifeLostBuffer);
    lifeLost.setVolume(50);

    SoundBuffer scoreBuffer;
    if (!scoreBuffer.loadFromFile("Sounds/Score.wav")) {
        std::cout << "Score Sound Error" << std::endl;
    }
    Sound scoreSound(scoreBuffer);
    scoreSound.setVolume(50);

    // Music
    Music backgroundMusic;
    if (!backgroundMusic.openFromFile("Music/BackgroundMusic.wav")) {
        std::cout << "Background Music Error" << std::endl;
    }
    backgroundMusic.setVolume(25);

    Music menuMusic;
    if (!menuMusic.openFromFile("Music/MenuMusic.wav")) {
        std::cout << "Menu Music Error" << std::endl;
    }
    menuMusic.setVolume(25);

    Music victoryMusic;
    if (!victoryMusic.openFromFile("Music/VictoryMusic.wav")) {
        std::cout << "Menu Music Error" << std::endl;
    }
    victoryMusic.setVolume(25);

    Music gameOverMusic;
    if (!gameOverMusic.openFromFile("Music/GameOverMusic.wav")) {
        std::cout << "Menu Music Error" << std::endl;
    }
    gameOverMusic.setVolume(25);

    // Load backgound
    Texture texture1;
    if (!texture1.loadFromFile("Images/Background.png")) {
        std::cout << "background Image Error" << std::endl;
    }
    Sprite	 background, menuBackGround;
    background.setTexture(texture1);

    Texture texture2;
    if (!texture2.loadFromFile("Images/menu.png")) {
        std::cout << "background 2 Image Error" << std::endl;
    }
    menuBackGround.setTexture(texture2);

    // create a paddle
    Paddle paddle(windowWidth *0.5f, windowHeight - 15.0f);

    // create a ball
    Ball ball(windowWidth * 0.5f, windowHeight-30.0f);
    ball.setYVelocity(0);
    ball.setXVelocity(0);
    
    // create bricks
    Brick brick[5][8];
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 8; j++)
        {
            brick[i][j].setPosition(80.0f * (j + 1.0f), 25.0f * (i + 1.0f));
            brick[i][j].setHealth(1,0);
            if (i == 3)
                brick[i][j].setHealth(2,j);
            if (i == 1)
                brick[i][j].setSpeed(100.0f);
        }
    }
    
    // create HUD
    Text hud;

    Font font;
    // dafont.com 
    font.loadFromFile("Font/DS-DIGIT.ttf");
    hud.setFont(font);
    hud.setCharacterSize(25);
    hud.setFillColor(sf::Color::White);
    hud.setPosition((windowWidth / 2.5f) - 40, 0);

    menuMusic.play();
    menuMusic.setLoop(true);

    //Start
    while (window.isOpen())
    {
        //Time
        clockEnd = std::chrono::steady_clock::now();
        timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(clockEnd - clockStart).count() / 1000000.0f;
        clockStart = clockEnd;

        //Event
        Event event;
        while (window.pollEvent(event))
        {
            if (!gameRunning)//Check if in menu
            {
                switch (event.type)
                {
                case Event::KeyReleased:
                    switch (event.key.code)
                    {
                    case Keyboard::Up:
                        menu.MoveUp();
                        break;

                    case Keyboard::Down:
                        menu.MoveDown();
                        break;

                    case Keyboard::Return:
                        switch (menu.GetPressedItem())
                        {
                        case 1:
                            std::cout << "Play has been pressed" << std::endl;
                            gameRunning = true;
                            menuMusic.stop();
                            backgroundMusic.play();
                            backgroundMusic.setLoop(true);
                            backgroundMusic.setVolume(50);
                            break;

                        case 2:
                            window.close();
                            break;
                        }
                        break;
                    }
                    break;

                case Event::Closed:
                    window.close();
                    break;
                }
            }
        }
        
        // Not in menu
        if (gameRunning)
        {
            if (event.type == Event::Closed) window.close();
            
            //Keyboard Inputs
            if (Keyboard::isKeyPressed(Keyboard::Left))
            {
                // move left...
                paddle.moveLeft(timeElapsed);
            }
            if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                // move right...
                paddle.moveRight(timeElapsed);
            }

            //Mouse Inputs
            if (Event::MouseEntered)
            {
                if (event.type == Event::MouseMoved)
                {
                    if (event.mouseMove.x > paddle.getPosition().left + paddle.getPosition().width)
                    {
                        paddle.moveRight(timeElapsed);
                    }
                    else if (event.mouseMove.x < paddle.getPosition().left)
                    {
                        paddle.moveLeft(timeElapsed);
                    }
                    
                }
            }

            //Ball is not moving and not waiting to reset game -> move the ball
            if (!ballStart && !resetGame)
            {
                if (Keyboard::isKeyPressed(Keyboard::Space) || (Mouse::isButtonPressed(Mouse::Left) && Event::MouseEntered))
                {
                    // ball moves
                    if (ball.getPosition().left > 400)
                    {

                        ball.setXVelocity(+50.0f);
                    }
                    if (ball.getPosition().left < 400)
                    {
                        ball.setXVelocity(-50.0f);
                    }
                    ball.setYVelocity(yVelocity);
                    ballStart = true;
                }
            }

            if (Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                // quit...
                // Someone closed the window- bye
                window.close();
            }

            //Pause
            if (Keyboard::isKeyPressed(Keyboard::P))
            {
                pause = !pause;
            }

            // If resetting the game
            if (resetGame)
            {
                if (Keyboard::isKeyPressed(sf::Keyboard::R))
                {
                    
                    lives = 3;
                    resetGame = false;
                    vm = false;
                    victoryMusic.stop();
                    gom = false;
                    gameOverMusic.stop();

                    //Cleared 
                    if (brickCount <= 0)
                    {
                        yVelocity = -abs(yVelocity) - 25.0f;
                        if (yVelocity > 400)
                            yVelocity = 400;
                    }
                    // Gave over
                    else
                    {
                        score = 0;
                    }
                    brickCount = 38;
                    ball.setYVelocity(0);
                    ball.setPosition(paddle.getPosition().left + ((paddle.getPosition().width) / 2.0f) - 5.0f, windowHeight - 30.0f);
                    paddle.changeTexture(lives);
                    backgroundMusic.play();
                    backgroundMusic.setLoop(true);
                    backgroundMusic.setVolume(50);
                    background.setColor(Color(255, 255, 255, 255));
                    hud.setCharacterSize(20);
                    hud.setPosition((windowWidth / 2.5f) - 40, 0);
                    for (i = 0; i < 5; i++)
                    {
                        for (j = 0; j < 8; j++)
                        {
                            brick[i][j].setPosition(80.0f * (j + 1.0f), 25.0f * (i + 1.0f));
                            brick[i][j].setHealth(1,0);
                            if (i == 3)
                                brick[i][j].setHealth(2,j);
                            if (i == 1)
                                brick[i][j].setSpeed(100.0f);
                        }
                    }
                   
                }

                //Quit
                if (Keyboard::isKeyPressed(Keyboard::Q))
                {
                    score = 0;
                    vm = false;
                    victoryMusic.stop();
                    gameRunning = false;
                    resetGame = false;
                    gom = false;
                    gameOverMusic.stop();
                    hud.setPosition((windowWidth / 2.0f) - 40, 20);
                    background.setColor(sf::Color(255, 255, 255, 255));
                    menuMusic.play();
                }

            }

            //Brick movement
            for (j = 0; j < 8; j++)
            {
                if (brick[1][j].getPosition().left <= 0 || (brick[1][j].getPosition().left + 70 >= windowWidth))
                {
                    brick[1][j].reboundSides();
                }
            }

            //Ball Collisions
            if (ballStart)
            {
                if (ball.getPosition().top > windowHeight) //Bottom
                {
                    if (ballStart)
                    {
                        lives = lives - 1;
                    }
                    ballStart = false;
                    ball.hitBottom();
                    lifeLost.play();
                    paddle.changeTexture(lives);
                    if (lives < 1) {
                        resetGame = true;
                    }

                }
            
                if (ball.getPosition().top < 0) //top
                {
                    ball.reboundTop();
                    bump.play();

                }

                if (ball.getPosition().left <= 0 || ball.getPosition().left + 10 >= windowWidth) //sides
                {
                    ball.reboundSides();
                    bump.play();
                }

                if (ball.getPosition().intersects(paddle.getPosition())) //Paddle
                {
                    ball.reboundPaddle(paddle.getPosition().left, paddle.getPosition().width);
                    bump.play();
                }

                // Collision with bricks
                for (i = 0; i < 5; i++)
                {
                    for (j = 0; j < 8; j++)
                    {
                        if (ball.getPosition().intersects(brick[i][j].getPosition()))
                        {
                            if (brick[i][j].getHealth() > 0)
                            {
                                ball.reboundBrick(brick[i][j].getPosition().top, brick[i][j].getPosition().top + brick[i][j].getPosition().height, brick[i][j].getPosition().left, brick[i][j].getPosition().left + brick[i][j].getPosition().width);
                                if (brick[i][j].getHealth() == 1)
                                {
                                    score = score + 10;
                                    scoreSound.play();
                                    brickCount--;
                                }
                                if (!(i == 3 && (j == 2 || j == 5)))
                                {
                                    brick[i][j].hit();
                                }
                                breakSound.play();
                            }
                        }
                    }
                }
            }
            //Update ball, brick and paddle
            if (!pause && !resetGame)
            {
                ball.update(timeElapsed);
                paddle.update(timeElapsed);
                for (j = 0; j < 8; j++)
                {
                    if (brick[1][j].getHealth() > 0)
                    {
                        brick[1][j].update(timeElapsed);
                    }
                }
            
            }
            //Draw
            // Clear everything from the last frame
            window.clear(Color(26, 128, 182, 255));
            window.draw(background);
            if (brickCount <= 0 || lives < 1)
            {

                resetGame = true;
                ballStart = false;
                backgroundMusic.stop();
            }
            // Update the HUD text
            std::stringstream ss;
            if (brickCount <= 0)
            {
                ss << "Level Cleared.\n Score: " << score << "\n Press R to restart";
                background.setColor(Color(182, 128, 230, 255));
                window.draw(background);
                hud.setPosition(windowWidth / 2 - 300, windowHeight / 8);
                hud.setCharacterSize(65);
                if (!vm)
                {
                    victoryMusic.play();
                    victoryMusic.setVolume(50);
                }
                vm = true;
            }
            else if (lives < 1)
            {
                ss << "Game Over.\n Score : " << score<< "\n Press R to restart";
                background.setColor(Color(230, 128, 182, 255));
                window.draw(background);
                hud.setCharacterSize(75);
                hud.setPosition(windowWidth / 2 - 275, windowHeight / 6); 
                if (!gom)
                {
                    gameOverMusic.play();
                    gameOverMusic.setVolume(50);
                }
                gom = true;
            }
            else
            {
                ss << "Score:" << score << "    Lives:" << lives;
                hud.setCharacterSize(20);
                hud.setPosition((windowWidth / 2.5f) - 40, 0);
            }

            if (!resetGame)
            {
                window.draw(paddle.getShape());

                if (!ballStart)
                {
                    ball.setYVelocity(0);
                    ball.setPosition(paddle.getPosition().left + ((paddle.getPosition().width) / 2.0f) - 5.0f, windowHeight - 30.0f);
                }

                window.draw(ball.getShape());

                for (i = 0; i < 5; i++)
                {
                    for (j = 0; j < 8; j++)
                    {
                        if (brick[i][j].getHealth() > 0)
                        {

                            window.draw(brick[i][j].getShape());
                        }
                    }
                }
            }
            hud.setString(ss.str());
            window.draw(hud);
            window.display();
        }
        if (!gameRunning)
        {
            window.clear();
            window.draw(menuBackGround);
            menu.draw(window);
            window.display();
        }

    }// This is the end of the "while" loop

    return 0;
}