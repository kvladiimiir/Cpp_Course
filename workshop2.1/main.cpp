#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

struct Ball
{
    sf::Vector2f speed;
    sf::CircleShape shape;
};

void init(Ball (&balls)[5], const float BALL_SIZE)
{
    sf::CircleShape shape(BALL_SIZE);
    shape.setPosition({200, 120});
    shape.setFillColor(sf::Color(0, 255, 255));
    sf::Vector2f speed = {50.f, 15.f};

    balls[0].speed = speed;
    balls[0].shape = shape;

    shape.setPosition({100, 120});
    shape.setFillColor(sf::Color(255, 0, 255));
    speed = {50.f, 45.f};

    balls[1].speed = speed;
    balls[1].shape = shape;

    shape.setPosition({200, 220});
    shape.setFillColor(sf::Color(255, 255, 0));
    speed = {50.f, 25.f};

    balls[2].speed = speed;
    balls[2].shape = shape;

    shape.setPosition({300, 120});
    shape.setFillColor(sf::Color(0, 0, 255));
    speed = {-50.f, 75.f};

    balls[3].speed = speed;
    balls[3].shape = shape;

    shape.setPosition({300, 220});
    shape.setFillColor(sf::Color(0, 255, 0));
    speed = {-50.f, -75.f};

    balls[4].speed = speed;
    balls[4].shape = shape;
}

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void redrawFrame(sf::RenderWindow &window, Ball (&balls)[5])
{
    window.clear();
    for (int i = 0; i < std::size(balls); ++i)
    {
        window.draw(balls[i].shape);
    }
    window.display();
}

void update(const unsigned WINDOW_WIDTH, const unsigned WINDOW_HEIGHT, const float dt, const float BALL_SIZE, Ball (&balls)[5])
{
    for (size_t i = 0; i < std::size(balls); ++i)
    {
        sf::Vector2f position = balls[i].shape.getPosition();

        if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (balls[i].speed.x > 0))
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if ((position.x < 0) && (balls[i].speed.x < 0))
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if ((position.y + 2 * BALL_SIZE >= WINDOW_HEIGHT) && (balls[i].speed.y > 0))
        {
            balls[i].speed.y = -balls[i].speed.y;
        }
        if ((position.y < 0) && (balls[i].speed.y < 0))
        {
            balls[i].speed.y = -balls[i].speed.y;
        }

        const float x = balls[i].speed.x * dt;
        const float y = balls[i].speed.y * dt;
        sf::Vector2f offset = {x, y};

        balls[i].shape.setPosition(position + offset);
    }
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    constexpr float BALL_SIZE = 50;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Moving Ball");
    sf::Clock clock;

    Ball balls[5];

    init(balls, BALL_SIZE);

    while (window.isOpen())
    {
        pollEvents(window);
        const float dt = clock.restart().asSeconds();
        update(WINDOW_WIDTH, WINDOW_HEIGHT, dt, BALL_SIZE, balls);
        redrawFrame(window, balls);
    }
}