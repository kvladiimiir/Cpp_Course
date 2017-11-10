#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

struct EyeLeft
{
    sf::ConvexShape ellipseLeft;
    sf::ConvexShape pupilLeft;
    sf::Vector2f position;
    float rotation = 0;
};

struct EyeRight
{
    sf::ConvexShape ellipseRight;
    sf::ConvexShape pupilRight;
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
void updateEyeLeftElements(EyeLeft &EyeLeft)
{
    EyeLeft.ellipseLeft.setPosition(EyeLeft.position);
    const sf::Vector2f pupilLeft0ffset = toEuclidean(20, 40, EyeLeft.rotation);
    EyeLeft.pupilLeft.setPosition(EyeLeft.position + pupilLeft0ffset);
}

//Рисует 1 глаз
void initEyeLeft(EyeLeft &eyeLeft)
{
    constexpr int pointCount = 200;
    eyeLeft.position = {400, 300};

    const sf::Vector2f ellipseLeftRadius = {40.f, 80.f};
    eyeLeft.ellipseLeft.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    eyeLeft.ellipseLeft.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            ellipseLeftRadius.x * std::sin(angle),
            ellipseLeftRadius.y * std::cos(angle)};
        eyeLeft.ellipseLeft.setPoint(pointNo, point);
    }

    const sf::Vector2f pupilLeftRadius = {10.f, 20.f};
    eyeLeft.pupilLeft.setFillColor(sf::Color(0x0, 0x0, 0x0));
    eyeLeft.pupilLeft.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            pupilLeftRadius.x * std::sin(angle),
            pupilLeftRadius.y * std::cos(angle)};
        eyeLeft.pupilLeft.setPoint(pointNo, point);
    }

    updateEyeLeftElements(eyeLeft);
}

//Обновляет позиции и повороты частей стрелки согласно текущему
//состоянию стрелки.
void updateEyeRightElements(EyeRight &eyeRight)
{
    eyeRight.ellipseRight.setPosition(eyeRight.position);
    const sf::Vector2f pupilRight0ffset = toEuclidean(20, 40, eyeRight.rotation);
    eyeRight.pupilRight.setPosition(eyeRight.position + pupilRight0ffset);
}

//Рисует 2 глаз
void initEyeRight(EyeRight &eyeRight)
{
    constexpr int pointCount = 200;
    eyeRight.position = {300, 300};

    const sf::Vector2f ellipseRightRadius = {40.f, 80.f};
    eyeRight.ellipseRight.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    eyeRight.ellipseRight.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            ellipseRightRadius.x * std::sin(angle),
            ellipseRightRadius.y * std::cos(angle)};
        eyeRight.ellipseRight.setPoint(pointNo, point);
    }

    const sf::Vector2f pupilRightRadius = {10.f, 20.f};
    eyeRight.pupilRight.setFillColor(sf::Color(0x0, 0x0, 0x0));
    eyeRight.pupilRight.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            pupilRightRadius.x * std::sin(angle),
            pupilRightRadius.y * std::cos(angle)};
        eyeRight.pupilRight.setPoint(pointNo, point);
    }

    updateEyeRightElements(eyeRight);
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
void update(const sf::Vector2f &mousePosition, EyeLeft &eyeLeft, EyeRight &eyeRight)
{
    const sf::Vector2f delta1 = mousePosition - eyeLeft.position;
    eyeLeft.rotation = atan2(delta1.y, delta1.x);
    updateEyeLeftElements(eyeLeft);

    const sf::Vector2f delta2 = mousePosition - eyeRight.position;
    eyeRight.rotation = atan2(delta2.y, delta2.x);
    updateEyeRightElements(eyeRight);
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, EyeLeft &eyeLeft, EyeRight &eyeRight)
{
    window.clear();
    window.draw(eyeLeft.ellipseLeft);
    window.draw(eyeLeft.pupilLeft);
    window.draw(eyeRight.ellipseRight);
    window.draw(eyeRight.pupilRight);
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

    EyeLeft eyeLeft;
    EyeRight eyeRight;
    initEyeLeft(eyeLeft);
    initEyeRight(eyeRight);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, eyeLeft, eyeRight);
        redrawFrame(window, eyeLeft, eyeRight);
    }
}