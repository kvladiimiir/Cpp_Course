#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

//инициализирует фигуру-указатель
void init(sf::ConvexShape &pointer)
{
    pointer.setPointCount(3);
    pointer.setPoint(0, {40, 0});
    pointer.setPoint(1, {-20, -20});
    pointer.setPoint(2, {-20, 20});
    pointer.setPosition({400, 300});
    pointer.setFillColor(sf::Color(0xFF, 0x80, 0x00));
}

//Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
    window.clear();
    window.draw(pointer);
    window.display();
}

//переводит радианы в градусы
float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

//Обрабатывает событие MouseMove, обновляя позицию мыши
void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse x=" << event.x << ", y= " << event.y << std::endl;

    mousePosition = {float(event.x), float(event.y)};
}

//Опрашивает и обрабатывает доступные события в цикле.
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

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &pointer, float &deltaTime)
{
    const sf::Vector2f delta = mousePosition - pointer.getPosition();
    float angle = atan2(delta.y, delta.x);
    sf::Vector2f direction = (delta / hypotf(delta.x, delta.y));
    if (angle < 0)
    {
        angle += 2 * M_PI;
    }
    angle = toDegrees(angle);
    const float maxRotation = 15 * deltaTime; //Если умножаем на deltatime то стрелка не дергается
    const float rotation = std::min(std::abs(angle - pointer.getRotation()), maxRotation);
    if (angle != pointer.getRotation())
    {
        if (angle > pointer.getRotation())
        {
            if ((angle - 180) > pointer.getRotation())
            {
                pointer.setRotation(pointer.getRotation() - std::min(maxRotation, rotation));
            }
            else
            {
                pointer.setRotation(pointer.getRotation() + std::min(maxRotation, rotation));
            }
        }

        else
        {
            if ((angle + 180) < pointer.getRotation())
            {
                pointer.setRotation(pointer.getRotation() + std::min(maxRotation, rotation));
            }
            else
            {
                pointer.setRotation(pointer.getRotation() - std::min(maxRotation, rotation));
            }
        }
    }
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Pointer follows mouse", sf::Style::Default, settings);

    sf::ConvexShape pointer;
    sf::Vector2f mousePosition;

    sf::Clock clock;
    init(pointer);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        float deltaTime = clock.restart().asSeconds();
        update(mousePosition, pointer, deltaTime);
        redrawFrame(window, pointer);
    }
}