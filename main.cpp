#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
using namespace sf;

const float movementMultiplier = 0.7;
const float enemySpeed = 0.05;
bool isDone = false;

int main()
{
    //initializing variables
    RenderWindow window(VideoMode(800, 800), "pong.");

    RectangleShape centerNet;
    centerNet.setSize(Vector2f(2, 800));
    centerNet.setPosition(Vector2f(399, 0));

    Vector2f ballVelocity = Vector2f(-0.2, 0);
    RectangleShape ball;
    ball.setFillColor(Color::White);
    ball.setSize(Vector2f(4, 4));
    ball.setPosition(Vector2f(398, 398));

    RectangleShape paddle1;
    paddle1.setSize(Vector2f(10, 100));
    paddle1.setOrigin(Vector2f(5, 50));
    paddle1.setPosition(Vector2f(20, 400));
    RectangleShape paddle2;
    paddle2.setSize(Vector2f(10, 100));
    paddle2.setOrigin(Vector2f(5, 50));
    paddle2.setPosition(Vector2f(780, 400));

    int score1 = 0;
    int score2 = 0;
    Font pixeboy;
    pixeboy.loadFromFile("assets/pixeboy.ttf");
    Text textScore1;
    textScore1.setFillColor(Color::White);
    textScore1.setFont(pixeboy);
    textScore1.setPosition(Vector2f(399 - textScore1.getCharacterSize(), 0));
    Text textScore2;
    textScore2.setFillColor(Color::White);
    textScore2.setFont(pixeboy);
    textScore2.setPosition(Vector2f(401 + textScore2.getCharacterSize() / 2, 0));

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case (Event::Closed):
            {
                window.close();
                break;
            }
            }
        }

        //Game Logic
        if (!isDone)
        {
            float paddle1Velocity = 0;
            float paddle2Velocity = 0;

            if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
            {
                Vector2f curPosition = paddle1.getPosition();
                if (curPosition.y - 50 - (0.2 * movementMultiplier) > 0)
                {
                    paddle1.setPosition(Vector2f(curPosition.x, curPosition.y - (0.2 * movementMultiplier)));
                    paddle1Velocity -= 0.05;
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
            {
                Vector2f curPosition = paddle1.getPosition();
                if (curPosition.y + 50 + (0.2 * movementMultiplier) <= 800)
                {
                    paddle1.setPosition(Vector2f(curPosition.x, curPosition.y + (0.2 * movementMultiplier)));
                    paddle1Velocity += 0.05;
                }
            }

            //Enemy Paddle

            if (paddle2.getPosition().y > ball.getPosition().y)
            {
                Vector2f curPosition = paddle2.getPosition();
                if (curPosition.y - 50 - (enemySpeed * movementMultiplier) > 0)
                {
                    paddle2.setPosition(Vector2f(curPosition.x, curPosition.y - (enemySpeed * movementMultiplier)));
                    paddle2Velocity -= 0.05;
                }
            }
            else if (paddle2.getPosition().y < ball.getPosition().y)
            {
                Vector2f curPosition = paddle2.getPosition();
                if (curPosition.y + 50 + (enemySpeed * movementMultiplier) <= 800)
                {
                    paddle2.setPosition(Vector2f(curPosition.x, curPosition.y + (enemySpeed * movementMultiplier)));
                    paddle2Velocity += 0.05;
                }
            }

            Vector2f curBallPosition = ball.getPosition();
            ball.setPosition(Vector2f(curBallPosition.x + (ballVelocity.x * movementMultiplier), curBallPosition.y + (ballVelocity.y * movementMultiplier)));
            //check ball collision with paddle 1
            if (ball.getPosition().x <= 20 && abs(ball.getPosition().y - paddle1.getPosition().y) < 50)
            {
                ballVelocity = Vector2f(ballVelocity.x * (-1), ballVelocity.y + paddle1Velocity);
            }
            //check ball collision with paddle 2
            if (ball.getPosition().x >= 780 && abs(ball.getPosition().y - paddle2.getPosition().y) < 50)
            {
                ballVelocity = Vector2f(ballVelocity.x * (-1), ballVelocity.y + paddle2Velocity);
            }

            if (ball.getPosition().y < 0 || ball.getPosition().y >= 800)
            {
                ballVelocity = Vector2f(ballVelocity.x, ballVelocity.y * (-1));
            }

            if (ball.getPosition().x <= 0)
            {
                score2++;
                ball.setPosition(Vector2f(398, 398));
                ballVelocity = Vector2f(-0.2, 0);
            }
            if (ball.getPosition().x > 800)
            {
                score1++;
                ball.setPosition(Vector2f(398, 398));
                ballVelocity = Vector2f(+0.2, 0);
            }
            window.clear();
            window.draw(ball);
            window.draw(centerNet);
            textScore1.setString(to_string(score1));
            textScore2.setString(to_string(score2));
            window.draw(textScore1);
            window.draw(textScore2);
            window.draw(paddle1);
            window.draw(paddle2);
            window.display();
        }
        if (score1 == 5)
        {
            Text winningText;
            winningText.setFont(pixeboy);
            winningText.setString("You Won.");
            winningText.setOrigin(Vector2f(winningText.getCharacterSize() * winningText.getString().getSize() / 4, winningText.getCharacterSize() / 2));
            winningText.setPosition(Vector2f(400, 400));
            window.clear();
            window.draw(winningText);
            window.display();
            isDone = true;
        }
        else if (score2 == 5)
        {
            Text losingText;
            losingText.setFont(pixeboy);
            losingText.setString("You Lost.");
            losingText.setOrigin(Vector2f(losingText.getCharacterSize() * losingText.getString().getSize() / 4, losingText.getCharacterSize() / 2));
            losingText.setPosition(Vector2f(400, 400));
            window.clear();
            window.draw(losingText);
            window.display();
            isDone = true;
        }
    }

    return 0;
}