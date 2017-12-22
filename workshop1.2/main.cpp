#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>

//переводит полярные координаты в декартовы.
float toDegrees(float radians)
{
    return float(double(radians) * 180 / M_PI);
}

//Обрабатывает событие MouseMove обновляя позицию мыши
void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse x=" << event.x << " , y=" << event.y << std::endl;
    mousePosition = {float(event.x),
                     float(event.y)};
}

// Опрашивает и обрабатывает доступные события в цикле.
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

//Инициализирует фигуру
void init(sf::ConvexShape &arrow)
{
    arrow.setFillColor(sf::Color(255, 255, 0));
    arrow.setPosition({450, 300});
    arrow.setPointCount(7);

    arrow.setPoint(0, {0, 0});
    arrow.setPoint(1, {-50, -50});
    arrow.setPoint(2, {-50, -25});
    arrow.setPoint(3, {-100, -25});
    arrow.setPoint(4, {-100, 25});
    arrow.setPoint(5, {-50, 25});
    arrow.setPoint(6, {-50, 50});

    arrow.setOutlineColor(sf::Color(0, 0, 0));
    arrow.setOutlineThickness(3);
}

// Обновляет фигуру, указывающую на мышь
void update(const sf::Vector2f &mousePosition, sf::ConvexShape &arrow, float &deltaTime)
{
    const sf::Vector2f delta = mousePosition - arrow.getPosition();
    float angle = atan2(delta.y, delta.x);
    sf::Vector2f direction = (delta / hypotf(delta.x, delta.y));
    float speed = 20.f;
    if ((delta.x, delta.y) != 0.f)
    {
        arrow.setPosition(arrow.getPosition() + direction * deltaTime * speed);
    }
    if (angle < 0)
    {
        angle = angle + 2 * M_PI;
    }
    angle = toDegrees(angle);
    const float maxRotation = 90 * deltaTime;
    const float rotation = std::min(std::abs(angle - arrow.getRotation()), maxRotation);
    if (angle != arrow.getRotation())
    {
        if (angle > arrow.getRotation())
        {
            if ((angle - 180) > arrow.getRotation())
            {
                arrow.setRotation(arrow.getRotation() - std::min(maxRotation, rotation));
            }
            else
            {
                arrow.setRotation(arrow.getRotation() + std::min(maxRotation, rotation));
            }
        }

        else
        {
            if ((angle + 180) < arrow.getRotation())
            {
                arrow.setRotation(arrow.getRotation() + std::min(maxRotation, rotation));
            }
            else
            {
                arrow.setRotation(arrow.getRotation() - std::min(maxRotation, rotation));
            }
        }
    }
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &arrow)
{
    window.clear(sf::Color(255, 255, 255));
    window.draw(arrow);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::Clock clock;
    sf::Vector2f mousePosition;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Strelka", sf::Style::Default, settings);

    sf::ConvexShape arrow;
    init(arrow);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        float deltaTime = clock.restart().asSeconds();
        update(mousePosition, arrow, deltaTime);
        redrawFrame(window, arrow);
    }
}