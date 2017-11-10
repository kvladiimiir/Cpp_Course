#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

struct Eye1
{
    sf::ConvexShape ellipse1;
    sf::ConvexShape zr1;
    sf::Vector2f position;
    float rotation = 0;
};

//переводит полярные координаты в декартовы.
sf::Vector2f toEuclidean(float radiusX, float radiusY, float angle)
{
    return {
        radiusX * std::cos(angle),
        radiusY * std::sin(angle)};
}

//Обновляет позиции и повороты частей стрелки согласно текущему
//состоянию стрелки.
void updateEye1Elements(Eye1 &Eye1)
{
    eye1.ellipse1.setPosition(ellipse1.position + head0ffset);
    const sf::Vector2f zr10ffset = toEuclidean(20, 40, eye1.rotation);
    eye1.zr1.setPosition(eye1.position);
}

//Рисует 1 глаз
void initEye1(Eye1 &eye1)
{
    constexpr int pointCount = 200;
    eye1.position = {400, 300};

    const sf::Vector2f ellipse1Radius = {40.f, 80.f};
    eye1.ellipse1.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    eye1.ellipse1.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            ellipse1Radius.x * std::sin(angle),
            ellipse1Radius.y * std::cos(angle)};
        eye1.ellipse1.setPoint(pointNo, point);
    }

    const sf::Vector2f zr1Radius = {10.f, 20.f};
    eye1.zr1.setFillColor(sf::Color(0x0, 0x0, 0x0));
    eye1.zr1.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            zr1Radius.x * std::sin(angle),
            zr1Radius.y * std::cos(angle)};
        eye1.zr1.setPoint(pointNo, point);
    }

    updateEye1Elements(eye1);
}

//Обрабатывает событие MouseMove обновляя позицию мыши
void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;
    mousePosition = {float(event.x), float(event.y)};
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

// Обновляет фигуру, указывающую на мышь
void update(const sf::Vector2f &mousePosition, Eye1 &eye1)
{
    const sf::Vector2f delta = mousePosition - eye1.position;
    eye1.rotation = atan2(delta.y, delta.x);
    updateEye1Elements(eye1);
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, Eye1 &eye1)
{
    window.clear();
    window.draw(eye1.ellipse1);
    window.draw(eye1.zr1);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Yey1 follows mouse", sf::Style::Default, settings);

    sf::Vector2f mousePosition;

    initEye1(eye1);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, eye1);
        redrawFrame(window, eye1);
    }
}