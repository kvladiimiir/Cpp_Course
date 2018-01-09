#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>

//Обрабатывает событие MouseMove обновляя позицию мыши
void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse x=" << event.x << " , y=" << event.y << std::endl;
    mousePosition = {float(event.x),
                     float(event.y)};
}

// Опрашивает и обрабатывает доступные события в цикле.
void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition, sf::Sprite &laser)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            laser.setPosition(event.mouseButton.x, event.mouseButton.y);
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
void init(sf::Sprite &cat, sf::Sprite &laser, sf::Texture &texture, sf::Texture &laserTexture)
{
    texture.loadFromFile("cat.png", sf::IntRect(0, 0, 40, 40));
    texture.setSmooth(true);
    cat.setTexture(texture);
    cat.setPosition(400, 300);
    cat.setOrigin(16, 16);

    laserTexture.loadFromFile("laser.png", sf::IntRect(0, 0, 40, 40));
    laserTexture.setSmooth(true);
    laser.setTexture(laserTexture);
    laser.setPosition(400, 300);
    laser.setOrigin(16, 16);
}

// Обновляет фигуру, указывающую на мышь
void update(sf::Sprite &laser, sf::Sprite &cat, float &deltaTime)
{
    const sf::Vector2f delta = laser.getPosition() - cat.getPosition();
    float distance = std::hypot(delta.x, delta.y);
    sf::Vector2f direction = {delta.x / distance, delta.y / distance};
    float speed = 90.f;
    if ((delta.x, delta.y) != 0.f)
    {
        float move = std::min(speed * deltaTime, distance);
        cat.setPosition(cat.getPosition() + direction * move);
    }
    if (laser.getPosition().x < cat.getPosition().x)
    {
        cat.setScale(-1, 1);
    }
    else
    {
        cat.setScale(1, 1);
    }
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, sf::Sprite &cat, sf::Sprite &laser)
{
    window.clear(sf::Color(255, 255, 255));
    window.draw(laser);
    window.draw(cat);
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
        "Kitten follows laser", sf::Style::Default, settings);

    sf::Texture texture;
    sf::Texture laserTexture;
    sf::Sprite cat;
    sf::Sprite laser;

    init(cat, laser, texture, laserTexture);

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        pollEvents(window, mousePosition, laser);
        update(laser, cat, deltaTime);
        redrawFrame(window, cat, laser);
    }
}