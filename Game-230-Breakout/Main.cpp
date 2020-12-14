// These "include" code from the C++ library and SFML too
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


// Avoid having to put sf in front of all the SFML classes and functions
using namespace sf;

// This is where our game starts from
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

    int score = 0;
    int lives = 3;
    int brickCount = 40;
    float yVelocity = -100.0f;

    //Load Sound files Add error checks 
    SoundBuffer bumpBuffer;
    if (!bumpBuffer.loadFromFile("Sounds/Bump.wav")) {
        std::cout << "Bump Sound Error" << std::endl;
    }
    Sound bump(bumpBuffer);
    bump.setVolume(50);
    
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

    // Load backgound
    Texture texture1;
    if (!texture1.loadFromFile("Images/pong1.png")) {
        std::cout << "background Image Error" << std::endl;
    }
    Sprite	 background, menuBackGround;
    background.setTexture(texture1);

    Texture texture2;
    if (!texture2.loadFromFile("Images/pong.png")) {
        std::cout << "background 2 Image Error" << std::endl;
    }
    menuBackGround.setTexture(texture2);

    //Load Music


    //Load background images


    //Load Sprites

    

    // create a paddle
    Paddle paddle(windowWidth *0.5f, windowHeight - 15.0f);



    //Texture ballTexture;
    //if (!ballTexture.loadFromFile("Sprites/Ball.png")) {
    //    std::cout << " Error" << std::endl;
    //    //return 0;
    //}

    Ball ball(windowWidth * 0.5f, windowHeight-30.0f);
    ball.setYVelocity(0);
    ball.setXVelocity(0);


    
    // create bricks
    Brick brick[5][8];

    //Texture brickTexture;
    //if (!brickTexture.loadFromFile("Images/brick.png")) {
    //    std::cout << "Sprite Image Error" << std::endl;
    //    }
    //Sprite	 brickSprite;
    //brickSprite.setTexture(brickTexture);





    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 8; j++)
        {
            brick[i][j].setPosition(80.0f * (j + 1.0f), 25.0f * (i + 1.0f));
            brick[i][j].setHealth(1);
        }
    }

    // Create a "Text" object called "message". Weird but we will learn about objects soon
    Text hud;

    // We need to choose a font
    Font font;
    // dafont.com - error check
    font.loadFromFile("Font/DS-DIGIT.ttf");

    // Set the font to our message
    hud.setFont(font);

    // Make it really big
    hud.setCharacterSize(25);

    // Choose a color
    hud.setFillColor(sf::Color::White);
    hud.setPosition((windowWidth / 2.5f) - 40, 0);

    menuMusic.play();
    menuMusic.setLoop(true);

    
    // This "while" loop goes round and round- perhaps forever
    while (window.isOpen())
    {   //Check if menu screen
        /*
            Handle the player input
            *********************************************************************
            *********************************************************************
            *********************************************************************
        */

        // Handle Player Input
        clockEnd = std::chrono::steady_clock::now();
        timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(clockEnd - clockStart).count() / 1000000.0f;
        clockStart = clockEnd;

        Event event;
        while (window.pollEvent(event))
        {
            if (!gameRunning)
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
                            std::cout << "Single player has been pressed" << std::endl;
                            gameRunning = true;
                            menuMusic.stop();
                            backgroundMusic.play();
                            backgroundMusic.setLoop(true);
                            backgroundMusic.setVolume(50);
                            break;

                        case 2:
                            std::cout << "Two-Player button has been pressed" << std::endl;
                            gameRunning = true;
                            menuMusic.stop();
                            backgroundMusic.play();
                            backgroundMusic.setLoop(true);
                            backgroundMusic.setVolume(50);
                            break;

                        case 3:
                            std::cout << "Four-Player button has been pressed" << std::endl;
                            gameRunning = true;
                            menuMusic.stop();
                            backgroundMusic.play();
                            backgroundMusic.setLoop(true);
                            backgroundMusic.setVolume(50);
                            break;

                        case 4:
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
        if (gameRunning)
        {

            //not in menu
            if (event.type == Event::Closed) window.close();
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
            if (!ballStart)
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
            //Pausing
            if (Keyboard::isKeyPressed(Keyboard::P))
            {
                pause = !pause;
            }

            if (resetGame)
            {
                if ((Mouse::isButtonPressed(Mouse::Right) && Event::MouseEntered))
                {
                    score = 0;
                    lives = 3;
                    resetGame = false;
                    vm = false;
                    victoryMusic.stop();
                    if (brickCount <= 0) {
                        yVelocity = -abs(yVelocity) - 25.0f;
                        if (yVelocity > 400)
                            yVelocity = 400;
                    }
                    brickCount = 40;
                    ball.setPosition(paddle.getPosition().left + ((paddle.getPosition().width) / 2.0f) - 5.0f, windowHeight - 30.0f);
                  
                    backgroundMusic.play();
                    backgroundMusic.setLoop(true);
                    backgroundMusic.setVolume(50);
                    hud.setCharacterSize(20);
                    hud.setPosition((windowWidth / 2.5f) - 40, 0);
                    for (i = 0; i < 5; i++)
                    {
                        for (j = 0; j < 8; j++)
                        {
                            brick[i][j].setPosition(80.0f * (j + 1.0f), 25.0f * (i + 1.0f));
                            brick[i][j].setHealth(1);
                        }
                    }
                   
                }
                if (Keyboard::isKeyPressed(Keyboard::Q))
                {
                    score = 0;
                    vm = false;
                    victoryMusic.stop();
                    gameRunning = false;
                    resetGame = false;
                    //vm = false;
                    hud.setPosition((windowWidth / 2.0f) - 40, 20);
                    background.setColor(sf::Color(255, 255, 255, 255));
                    menuMusic.play();
                }

            }
            /*
                Update the frame
                *********************************************************************
                *********************************************************************
                *********************************************************************
            */
            // Handle ball hitting the bottom
            if (ball.getPosition().top > windowHeight)
            {
                // reverse the ball direction
                if (ballStart)
                {
                    lives = lives - 1;
                }

                ballStart = false;
                ball.hitBottom();
                lifeLost.play();

                // Remove a life


                // Check for zero lives
                if (lives < 1) {
                    resetGame = true;
                }

            }

            // Handle ball hitting top
            if (ball.getPosition().top < 0)
            {
                ball.reboundTop();
                bump.play();

            }

            // Handle ball hitting sides
            if (ball.getPosition().left < 0 || ball.getPosition().left + 10 > windowWidth)
            {
                ball.reboundSides();
                bump.play();
            }

            // Has the ball hit the paddle?
            if (ball.getPosition().intersects(paddle.getPosition()))
            {
                // Hit detected so reverse the ball and score a point
                ball.reboundPaddle(paddle.getPosition().left, paddle.getPosition().width);
                bump.play();
            }

            // hits bricks
            for (i = 0; i < 5; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    if (ball.getPosition().intersects(brick[i][j].getPosition()))
                    {
                        if (brick[i][j].getHealth() > 0)
                        {
                            ball.reboundBrick(brick[i][j].getPosition().top, brick[i][j].getPosition().top + brick[i][j].getPosition().height, brick[i][j].getPosition().left, brick[i][j].getPosition().left + brick[i][j].getPosition().width);
                            score = score + 10;
                            brick[i][j].hit();
                            brickCount--;
                            scoreSound.play();
                        }


                    }
                }
            }

            if (!pause && !resetGame)
            {
                ball.update(timeElapsed);
                paddle.update(timeElapsed);
            }




            /*
       Draw the frame
       *********************************************************************
       *********************************************************************
       *********************************************************************
    */

    // Clear everything from the last frame
            window.clear(Color(26, 128, 182, 255));
            window.draw(background);
            if (!resetGame)
            {
                //window.draw(paddle.getSprite());
                window.draw(paddle.getShape());

                if (!ballStart)
                {
                    ball.setPosition(paddle.getPosition().left + ((paddle.getPosition().width) / 2.0f) - 5.0f, windowHeight - 30.0f);
                }
                //window.draw(ball.getSprite());
                window.draw(ball.getShape());
                //ball.Draw(window);

                for (i = 0; i < 5; i++)
                {
                    for (j = 0; j < 8; j++)
                    {
                        if (brick[i][j].getHealth() > 0)
                        {
                            window.draw(brick[i][j].getShape());
                           /* brickSprite.setPosition(80.0f * (j + 1.0f), 25.0f * (i + 1.0f));
                            window.draw(brickSprite);*/
                        }
                    }
                }
            }

            if (brickCount <= 0 || lives < 1)
            {
                window.clear(Color(230, 128, 182, 255));
                resetGame = true;
                ballStart = false;
                backgroundMusic.stop();
            }
            // Update the HUD text
            std::stringstream ss;
            if (brickCount <= 0)
            {
                ss << "Level Cleared.\n Score: " << score << "\n Right to restart with faster speed";
                hud.setPosition(windowWidth / 2 - 300, windowHeight / 4);
                hud.setCharacterSize(75);
                if (!vm)
                {
                    victoryMusic.play();
                    victoryMusic.setVolume(50);
                }
                vm = true;
            }
            else if (lives < 1)
            {
                ss << "Game Over.\n Score : " << score;
                hud.setCharacterSize(75);
                hud.setPosition(windowWidth / 2 - 250, windowHeight / 2);
            }
            else
            {
                ss << "Score:" << score << "    Lives:" << lives;
                hud.setCharacterSize(20);
                hud.setPosition((windowWidth / 2.5f) - 40, 0);
            }

            hud.setString(ss.str());
            // Draw our score
            window.draw(hud);

            // Show everything we just drew
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