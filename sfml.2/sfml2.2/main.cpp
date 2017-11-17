#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

struct Eye
{
    sf::ConvexShape ellipse;
    sf::ConvexShape pupil;
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
void updateEyeElements(Eye &eyeLeft, Eye &eyeRight)
{
    eyeLeft.ellipse.setPosition(eyeLeft.position);
    sf::Vector2f pupil0ffset = toEuclidean(20, 40, eyeLeft.rotation);
    eyeLeft.pupil.setPosition(eyeLeft.position + pupil0ffset);

    eyeRight.ellipse.setPosition(eyeRight.position);
    pupil0ffset = toEuclidean(20, 40, eyeRight.rotation);
    eyeRight.pupil.setPosition(eyeRight.position + pupil0ffset);
}

//Рисует глаза
void initEye(Eye &eyeLeft, Eye &eyeRight)
{
    constexpr int pointCount = 200;
    eyeLeft.position = {400, 300};

    sf::Vector2f ellipseRadius = {40.f, 80.f};
    eyeLeft.ellipse.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    eyeLeft.ellipse.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            ellipseRadius.x * std::sin(angle),
            ellipseRadius.y * std::cos(angle)};
        eyeLeft.ellipse.setPoint(pointNo, point);
    }

    sf::Vector2f pupilRadius = {10.f, 20.f};
    eyeLeft.pupil.setFillColor(sf::Color(0x0, 0x0, 0x0));
    eyeLeft.pupil.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            pupilRadius.x * std::sin(angle),
            pupilRadius.y * std::cos(angle)};
        eyeLeft.pupil.setPoint(pointNo, point);
    }

    eyeRight.position = {300, 300};

    ellipseRadius = {40.f, 80.f};
    eyeRight.ellipse.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    eyeRight.ellipse.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            ellipseRadius.x * std::sin(angle),
            ellipseRadius.y * std::cos(angle)};
        eyeRight.ellipse.setPoint(pointNo, point);
    }

    pupilRadius = {10.f, 20.f};
    eyeRight.pupil.setFillColor(sf::Color(0x0, 0x0, 0x0));
    eyeRight.pupil.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            pupilRadius.x * std::sin(angle),
            pupilRadius.y * std::cos(angle)};
        eyeRight.pupil.setPoint(pointNo, point);
    }

    updateEyeElements(eyeLeft, eyeRight);
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
void update(const sf::Vector2f &mousePosition, Eye &eyeLeft, Eye &eyeRight)
{
    const sf::Vector2f delta1 = mousePosition - eyeLeft.position;
    eyeLeft.rotation = atan2(delta1.y, delta1.x);

    const sf::Vector2f delta2 = mousePosition - eyeRight.position;
    eyeRight.rotation = atan2(delta2.y, delta2.x);
    updateEyeElements(eyeLeft, eyeRight);
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, Eye &eyeLeft, Eye &eyeRight)
{
    window.clear();
    window.draw(eyeLeft.ellipse);
    window.draw(eyeLeft.pupil);
    window.draw(eyeRight.ellipse);
    window.draw(eyeRight.pupil);
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

    Eye eyeLeft;
    Eye eyeRight;
    initEye(eyeLeft, eyeRight);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, eyeLeft, eyeRight);
        redrawFrame(window, eyeLeft, eyeRight);
    }
}
