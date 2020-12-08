// These "include" code from the C++ library and SFML too
#include "Paddle.h"
#include "Ball.h"
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

    //Flags for game states 

    int score = 0;
    int lives = 3;

    //Load Sound files Add error checks 

    //Load Music


    //Load background images


    //Load Sprites

    

    // create a paddle
    Paddle paddle(windowWidth *0.5f, windowHeight - 20.0f);

    // create a ball - place ball on paddle and make it move with paddle. 
    Ball ball(windowWidth * 0.5f, 1);

    //create bricks

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
            paddle.moveLeft();
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            // move right...
            paddle.moveRight();
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
            ball.reboundPaddleOrTop();

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
            ball.reboundPaddleOrTop();
        }

        ball.update();
        paddle.update();

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