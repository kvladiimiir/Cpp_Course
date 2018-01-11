#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

void initBall(sf::CircleShape &ball)
{
    ball.setPosition({350, 250});
    ball.setRadius(50);
    ball.setFillColor(sf::Color(255, 165, 0));

    ball.setOutlineColor(sf::Color(105, 89, 205));
    ball.setOutlineThickness(6);
}

void redrawFrame(sf::RenderWindow &window, sf::Text &text, sf::CircleShape &ball)
{
    window.clear(sf::Color(255, 255, 255));
    window.draw(ball);
    window.draw(text);
    window.display();
}

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        default:
            break;
        }
    }
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Ball");

    sf::CircleShape ball;
    initBall(ball);

    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text text;
    text.setFont(font);
    text.setString("KVA");
    text.setPosition(382, 290);
    text.setFillColor(sf::Color(0, 139, 0));
    text.setCharacterSize(20);

    while (window.isOpen())
    {
        pollEvents(window);
        redrawFrame(window, text, ball);
    }
}