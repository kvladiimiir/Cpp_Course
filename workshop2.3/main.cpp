#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>
#include <cmath>

struct PRNG
{
    std::mt19937 engine;
};

void initGenerator(PRNG &generator)
{
    const unsigned seed = unsigned(std::time(nullptr));
    generator.engine.seed(seed);
}

unsigned randomSpeed(PRNG &generator, unsigned min, unsigned max)
{
    std::uniform_int_distribution<unsigned> distribution(min, max);
    return distribution(generator.engine);
}

struct Ball
{
    sf::Vector2f speed;
    sf::Vector2f position;
    sf::CircleShape shape;
};

void init(Ball (&balls)[5], const float BALL_SIZE)
{

    PRNG generator;
    initGenerator(generator);

    sf::CircleShape shape(BALL_SIZE);
    shape.setPosition({200, 120});
    shape.setFillColor(sf::Color(0, 255, 255));
    float speedX = randomSpeed(generator, 300, 500);
    float speedY = randomSpeed(generator, 300, 500);

    balls[0].speed = {speedX, speedY};
    balls[0].shape = shape;

    shape.setPosition({550, 120});
    shape.setFillColor(sf::Color(255, 0, 255));
    speedX = randomSpeed(generator, 300, 500);
    speedY = randomSpeed(generator, 300, 500);

    balls[1].speed = {speedX, speedY};
    balls[1].shape = shape;

    shape.setPosition({200, 220});
    shape.setFillColor(sf::Color(255, 255, 0));
    speedX = randomSpeed(generator, 300, 500);
    speedY = randomSpeed(generator, 300, 500);

    balls[2].speed = {speedX, speedY};
    balls[2].shape = shape;

    shape.setPosition({300, 120});
    shape.setFillColor(sf::Color(0, 0, 255));
    speedX = randomSpeed(generator, 300, 500);
    speedY = randomSpeed(generator, 300, 500);

    balls[3].speed = {speedX, speedY};
    balls[3].shape = shape;

    shape.setPosition({300, 220});
    shape.setFillColor(sf::Color(0, 255, 0));
    speedX = randomSpeed(generator, 300, 500);
    speedY = randomSpeed(generator, 300, 500);

    balls[4].speed = {speedX, speedY};
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
        balls[i].position = balls[i].shape.getPosition();
        balls[i].position += balls[i].speed * dt;

        if (balls[i].position.x + 2 * BALL_SIZE >= WINDOW_WIDTH)
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if (balls[i].position.x < 0)
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if (balls[i].position.y + 2 * BALL_SIZE >= WINDOW_HEIGHT)
        {
            balls[i].speed.y = -balls[i].speed.y;
        }
        if (balls[i].position.y < 0)
        {
            balls[i].speed.y = -balls[i].speed.y;
        }

        balls[i].shape.setPosition(balls[i].position);
    }

    for (int m = 0; m < std::size(balls); ++m)
    {
        for (int n = m + 1; n < std::size(balls); ++n)
        {
            sf::Vector2f dtPosition = balls[n].position - balls[m].position;
            sf::Vector2f dtSpeed = balls[n].speed - balls[m].speed;

            float length = std::sqrt(pow(dtPosition.x, 2) + std::pow(dtPosition.y, 2));
            float changeSpeed = ((dtPosition.x * dtSpeed.x) + (dtPosition.y * dtSpeed.y)) / std::pow(length, 2);

            if (length <= (2 * BALL_SIZE))
            {
                balls[m].speed = balls[m].speed + changeSpeed * dtPosition;
                balls[n].speed = balls[n].speed - changeSpeed * dtPosition;
            }
        }
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
