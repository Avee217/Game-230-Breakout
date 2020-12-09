// These "include" code from the C++ library and SFML too
#include "Paddle.h"
#include "Ball.h"
#include"Brick.h"
#include"Menu.h"
//#include"Obstacle.h" Change to bricks
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
    int windowWidth = 800;
    int windowHeight = 600;
   

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

    int score = 0;
    int lives = 3;

    //Load Sound files Add error checks 
    SoundBuffer bumpBuffer;
    if (!bumpBuffer.loadFromFile("Sounds/Bump.wav")) {
        std::cout << "Bump Sound Error" << std::endl;
    }
    Sound bump(bumpBuffer);
    bump.setVolume(50);

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
    Paddle paddle(windowWidth *0.5f, windowHeight - 20.0f);

    // create a ball - place ball on paddle and make it move with paddle. 
    Ball ball(windowWidth * 0.5f, 1);

    // create bricks
    Brick brick[];

    // Create a "Text" object called "message". Weird but we will learn about objects soon
    Text hud;

    // We need to choose a font
    Font font;
    // dafont.com - error check
    font.loadFromFile("Font/DS-DIGIT.ttf");

    // Set the font to our message
    hud.setFont(font);

    // Make it really big
    hud.setCharacterSize(75);

    // Choose a color
    hud.setFillColor(sf::Color::White);
    hud.setPosition((windowWidth / 2.0f) - 40, 20);

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
            //Menu
            if (event.type == Event::Closed)
                // Someone closed the window- bye
                window.close();
        }

        //not in menu

        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            // move left...
            paddle.moveLeft(timeElapsed);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            // move right...
            paddle.moveRight(timeElapsed);
        }
        else if (Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            // quit...
            // Someone closed the window- bye
            window.close();
        }
        // add pause and restart
        /*
            Update the frame
            *********************************************************************
            *********************************************************************
            *********************************************************************
        */
        //Collisions redo,split top and paddle add for bricks.
        // Handle ball hitting the bottom
        if (ball.getPosition().top > windowHeight)
        {
            // reverse the ball direction
            ball.hitBottom();

            // Remove a life
            lives--;

            // Check for zero lives
            if (lives < 1) {
                // reset the score
                score = 0;
                // reset the lives
                lives = 3;
            }

        }

        // Handle ball hitting top
        if (ball.getPosition().top < 0)
        {
            ball.reboundTop();

            // Add a point to the players score
            score++;

        }

        // Handle ball hitting sides
        if (ball.getPosition().left < 0 || ball.getPosition().left + 10 > windowWidth)
        {
            ball.reboundSides();
        }

        // Has the ball hit the paddle?
        if (ball.getPosition().intersects(paddle.getPosition()))
        {
            // Hit detected so reverse the ball and score a point
            ball.reboundPaddle(paddle.getPosition().left,paddle.getPosition().width);
        }

        ball.update(timeElapsed);
        paddle.update(timeElapsed);

        // Update the HUD text
        std::stringstream ss;
        ss << "Score:" << score << "    Lives:" << lives;
        hud.setString(ss.str());
        /*
   Draw the frame
   *********************************************************************
   *********************************************************************
   *********************************************************************
*/

// Clear everything from the last frame
        window.clear(Color(26, 128, 182, 255));

        window.draw(paddle.getShape());

        window.draw(ball.getShape());

        // Draw our score
        window.draw(hud);

        // Show everything we just drew
        window.display();
    }// This is the end of the "while" loop

    return 0;
}