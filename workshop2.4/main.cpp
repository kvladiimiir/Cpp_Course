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

unsigned randomIndex(PRNG &generator, unsigned min, unsigned max)
{
    std::uniform_int_distribution<unsigned> distribution(min, max);
    return distribution(generator.engine);
}

unsigned randomIndexColor(PRNG &generator)
{
    std::uniform_int_distribution<unsigned> distribution(0, 7);
    return distribution(generator.engine);
}

struct Ball
{
    sf::Vector2f speed;
    sf::Vector2f position;
    sf::CircleShape shape;
};

void resolutionColor(sf::Color (&color)[8])
{
    color[0].r = 255;
    color[0].g = 255;
    color[0].b = 0;

    color[1].r = 0;
    color[1].g = 255;
    color[1].b = 255;

    color[2].r = 0;
    color[2].g = 0;
    color[2].b = 255;

    color[3].r = 255;
    color[3].g = 0;
    color[3].b = 255;

    color[4].r = 255;
    color[4].g = 0;
    color[4].b = 0;

    color[5].r = 0;
    color[5].g = 255;
    color[5].b = 0;

    color[6].r = 150;
    color[6].g = 150;
    color[6].b = 155;

    color[7].r = 200;
    color[7].g = 255;
    color[7].b = 132;
}

void init(Ball (&balls)[5], sf::Color (&color)[8], const float BALL_SIZE)
{

    PRNG generator;
    initGenerator(generator);

    sf::CircleShape shape(BALL_SIZE);
    shape.setPosition({200, 120});
    int m = randomIndexColor(generator);
    int n = randomIndexColor(generator);
    shape.setFillColor(sf::Color((color[m].r + color[n].r) / 2, (color[m].g + color[n].g) / 2, (color[m].b + color[n].b) / 2));
    float speedX = randomIndex(generator, 300, 500);
    float speedY = randomIndex(generator, 300, 500);

    balls[0].speed = {speedX, speedY};
    balls[0].shape = shape;

    shape.setPosition({550, 120});
    m = randomIndexColor(generator);
    n = randomIndexColor(generator);
    shape.setFillColor(sf::Color((color[m].r + color[n].r) / 2, (color[m].g + color[n].g) / 2, (color[m].b + color[n].b) / 2));
    speedX = randomIndex(generator, 300, 500);
    speedY = randomIndex(generator, 300, 500);

    balls[1].speed = {speedX, speedY};
    balls[1].shape = shape;

    shape.setPosition({200, 220});
    m = randomIndexColor(generator);
    n = randomIndexColor(generator);
    shape.setFillColor(sf::Color((color[m].r + color[n].r) / 2, (color[m].g + color[n].g) / 2, (color[m].b + color[n].b) / 2));
    speedX = randomIndex(generator, 300, 500);
    speedY = randomIndex(generator, 300, 500);

    balls[2].speed = {speedX, speedY};
    balls[2].shape = shape;

    shape.setPosition({300, 120});
    m = randomIndexColor(generator);
    n = randomIndexColor(generator);
    shape.setFillColor(sf::Color((color[m].r + color[n].r) / 2, (color[m].g + color[n].g) / 2, (color[m].b + color[n].b) / 2));
    speedX = randomIndex(generator, 300, 500);
    speedY = randomIndex(generator, 300, 500);

    balls[3].speed = {speedX, speedY};
    balls[3].shape = shape;

    shape.setPosition({300, 220});
    m = randomIndexColor(generator);
    n = randomIndexColor(generator);
    shape.setFillColor(sf::Color((color[m].r + color[n].r) / 2, (color[m].g + color[n].g) / 2, (color[m].b + color[n].b) / 2));
    speedX = randomIndex(generator, 300, 500);
    speedY = randomIndex(generator, 300, 500);

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

            float distance = std::sqrt(pow(dtPosition.x, 2) + std::pow(dtPosition.y, 2));
            float changeSpeed = ((dtPosition.x * dtSpeed.x) + (dtPosition.y * dtSpeed.y)) / std::pow(distance, 2);

            if (distance <= (2 * BALL_SIZE))
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
    sf::Color(color[8]);
    resolutionColor(color);

    init(balls, color, BALL_SIZE);

    while (window.isOpen())
    {
        pollEvents(window);
        const float dt = clock.restart().asSeconds();
        update(WINDOW_WIDTH, WINDOW_HEIGHT, dt, BALL_SIZE, balls);
        redrawFrame(window, balls);
    }
}
