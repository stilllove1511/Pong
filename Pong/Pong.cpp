#include <SFML/Graphics.hpp>
#include <cmath>

void movePaddles(sf::RectangleShape& leftPaddle, sf::RectangleShape& rightPaddle, sf::RenderWindow& window)
{
    // Move the left paddle up if the W key is pressed and it's not at the top of the screen
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && leftPaddle.getPosition().y > 0)
    {
        leftPaddle.move(0, -0.15f);
    }

    // Move the left paddle down if the S key is pressed and it's not at the bottom of the screen
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && leftPaddle.getPosition().y + leftPaddle.getSize().y < window.getSize().y)
    {
        leftPaddle.move(0, 0.15f);
    }

    // Move the right paddle up if the up arrow key is pressed and it's not at the top of the screen
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rightPaddle.getPosition().y > 0)
    {
        rightPaddle.move(0, -0.15f);
    }

    // Move the right paddle down if the down arrow key is pressed and it's not at the bottom of the screen
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rightPaddle.getPosition().y + rightPaddle.getSize().y < window.getSize().y)
    {
        rightPaddle.move(0, 0.15f);
    }
}

bool checkCollision(sf::CircleShape& ball, sf::RectangleShape& paddle)
{
    sf::FloatRect ballBounds = ball.getGlobalBounds();
    sf::FloatRect paddleBounds = paddle.getGlobalBounds();
    if (ballBounds.intersects(paddleBounds))
    {
        return true;
    }
    return false;
}


float angleBall = 90.f;
const float ballDisplacement = 0.15f;
const float pi = 3.14f;

void moveBall(sf::CircleShape& ball, sf::RectangleShape& leftPaddle, sf::RectangleShape& rightPaddle
  //  , int& scoreLeft, int& scoreRight
)
{
    // Move the ball
    ball.move(ballDisplacement *sin(angleBall*pi/180), ballDisplacement *cos(angleBall * pi/180));

    // Check if the ball hit the top or bottom of the window
    if (ball.getPosition().y < 0 || ball.getPosition().y + ball.getRadius() * 2 > 600)
    {
        angleBall = 180.f - angleBall;
    }

    // Check if the ball hit the left paddle
    if (checkCollision(ball,leftPaddle)
        )
    {
        if(ball.getPosition().y> leftPaddle.getPosition().y)
            angleBall = 360.f - angleBall-rand()%10;
        else 
           angleBall = 360.f - angleBall + rand() % 10;
    }

    // Check if the ball hit the right paddle
    if (checkCollision(ball, rightPaddle)
        )
    {
        if (ball.getPosition().y > rightPaddle.getPosition().y)
            angleBall = 360.f - angleBall - rand() % 10;
        else
            angleBall = 360.f - angleBall + rand() % 10;
    }
}

int main()
{
    srand(time(NULL));
    // Create a window to draw in
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong Game");

    // Set up the left paddle
    sf::RectangleShape leftPaddle(sf::Vector2f(20, 80));
    leftPaddle.setFillColor(sf::Color::White);
    leftPaddle.setPosition(0, 260);

    // Set up the right paddle
    sf::RectangleShape rightPaddle(sf::Vector2f(20, 80));
    rightPaddle.setFillColor(sf::Color::White);
    rightPaddle.setPosition(780, 260);

    // Set up the ball
    sf::CircleShape ball(10);
    ball.setFillColor(sf::Color::White);
    ball.setPosition(395, 295);

    // Draw the paddles and ball to the window
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        movePaddles(leftPaddle, rightPaddle, window);
        moveBall(ball, leftPaddle, rightPaddle);

        window.clear(sf::Color::Black);
        window.draw(leftPaddle);
        window.draw(rightPaddle);
        window.draw(ball);
        window.display();
    }

    return 0;
}