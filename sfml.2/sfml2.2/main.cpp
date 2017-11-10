#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

int main()
{
    constexpr int pointCount = 250;
    float trackradius = 100;
    sf::Vector2f position = {400.f, 300.f};
    float period = 3.f;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({800, 600}), "ROSE",
        sf::Style::Default, settings);
    sf::ConvexShape rose;
    rose.setPosition({400, 320});
    rose.setFillColor(sf::Color(0x01, 0xE9, 0x19));

    sf::Clock clock;
    float time = 0;

    rose.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        float Radius = 200 * sin(6 * angle);
        sf::Vector2f point = {
            Radius * std::sin(angle),
            Radius * std::cos(angle)};
        rose.setPoint(pointNo, point);
    }

    while (window.isOpen())

    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        const float dt = clock.restart().asSeconds();
        time = dt + time;

        float phasa = time * float(2 * M_PI);
        float x = trackradius * std::sin(phasa / period);
        float y = trackradius * std::cos(phasa / period);
        sf::Vector2f offset = {x, y};

        rose.setPosition(position + offset);

        window.clear();
        window.draw(rose);
        window.display();
    }
}
