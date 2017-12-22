#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

void init(sf::Sprite &cat, sf::Texture &texture)
{
    texture.loadFromFile("cat.png", sf::IntRect(0, 0, 40, 40));
    texture.setSmooth(true);
    cat.setTexture(texture);
    cat.setPosition(400, 300);
}
void drawFrame(sf::RenderWindow &window, sf::Sprite &cat)
{
    window.clear(sf::Color(255, 255, 255));
    window.draw(cat);
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

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Kitten", sf::Style::Default, settings);

    sf::Texture texture;
    sf::Sprite cat;

    init(cat, texture);
    while (window.isOpen())
    {
        pollEvents(window);
        drawFrame(window, cat);
    }
}