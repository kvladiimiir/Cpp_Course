#include "main.hpp"

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};

    sf::Vector2f dt = sf::Vector2f({WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2}) - mousePosition;
    float length = sqrt(pow(dt.x, 2) + pow(dt.y, 2));

    std::cout << "length = " << length << std::endl;
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

void update(const sf::Vector2f &mousePosition, sf::VertexArray &lines)
{
    lines[0].position = sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    lines[1].position = mousePosition;

    lines[0].color = sf::Color::Black;
    lines[1].color = sf::Color::Black;
}

void redrawFrame(sf::RenderWindow &window, sf::VertexArray &lines)
{
    window.clear(sf::Color::White);
    window.draw(lines);
    window.display();
}

int main()
{

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Lines", sf::Style::Default, settings);

    sf::VertexArray lines(sf::Lines, 2);
    sf::Vector2f mousePosition;

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, lines);
        redrawFrame(window, lines);
    }
}