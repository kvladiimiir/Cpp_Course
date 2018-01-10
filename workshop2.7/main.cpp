#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <random>
#include <cmath>
#include <vector>

struct PRNG
{
    std::mt19937 engine;
};

void initGenerator(PRNG &generator)
{
    const unsigned seed = unsigned(std::time(nullptr));
    generator.engine.seed(seed);
}

unsigned randomIndex(PRNG &generator, unsigned minValue, unsigned maxValue)
{
    std::uniform_int_distribution<unsigned> distribution(minValue, maxValue);
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
    float time;
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

void destructionBall(std::vector<Ball> &balls)
{
    auto removeBalls = [&](Ball balls) -> bool {
        return balls.time < 0;
    };
    auto iterator = std::remove_if(balls.begin(), balls.end(), removeBalls);
    balls.erase(iterator, balls.end());
}

void update(const unsigned WINDOW_WIDTH, const unsigned WINDOW_HEIGHT, const float dt, const float BALL_SIZE, std::vector<Ball> &balls)
{
    for (size_t i = 0; i < std::size(balls); ++i)
    {
        balls[i].position = balls[i].shape.getPosition();
        balls[i].position += balls[i].speed * dt;
        balls[i].time = balls[i].time - dt;

        if ((balls[i].position.x + BALL_SIZE >= WINDOW_WIDTH) && (balls[i].speed.x > 0))
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if ((balls[i].position.x - BALL_SIZE < 0) && (balls[i].speed.x < 0))
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if ((balls[i].position.y + BALL_SIZE >= WINDOW_HEIGHT) && (balls[i].speed.y > 0))
        {
            balls[i].speed.y = -balls[i].speed.y;
        }
        if ((balls[i].position.y - BALL_SIZE < 0) && (balls[i].speed.y < 0))
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
    destructionBall(balls);
}

void init(sf::Event::MouseButtonEvent &event, std::vector<Ball> &balls, const float BALL_SIZE, sf::Color (&color)[8])
{
    bool initBall = true;
    sf::Vector2f mousePosition = {float(event.x), float(event.y)};
    for (int i = 0; i < size(balls); ++i)
    {
        sf::Vector2f dtPos = balls[i].shape.getPosition() - mousePosition;
        float distance = sqrt(pow(dtPos.x, 2) + pow(dtPos.y, 2));
        if (distance <= (2 * BALL_SIZE))
        {
            initBall = false;
        }
    }
    if (initBall == true)
    {
        Ball newBall;

        PRNG generator;
        initGenerator(generator);

        sf::CircleShape shape(BALL_SIZE);
        newBall.time = 10;
        shape.setPosition(mousePosition);
        shape.setOrigin(BALL_SIZE, BALL_SIZE);

        int m = randomIndexColor(generator);
        int n = randomIndexColor(generator);
        shape.setFillColor(sf::Color((color[m].r + color[n].r) / 2, (color[m].g + color[n].g) / 2, (color[m].b + color[n].b) / 2));

        float speedX = randomIndex(generator, 0, 100);
        float speedY = randomIndex(generator, 0, 100);

        newBall.speed = {speedX, speedY};
        newBall.shape = shape;
        balls.push_back(newBall); // иначе будет пустая
    }
}

void pollEvents(sf::RenderWindow &window, std::vector<Ball> &balls, const float BALL_SIZE, sf::Color (&color)[8])
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
            init(event.mouseButton, balls, BALL_SIZE, color);
        default:
            break;
        }
    }
}

void redrawFrame(sf::RenderWindow &window, std::vector<Ball> &balls)
{
    window.clear();

    for (int i = 0; i < std::size(balls); ++i)
    {
        window.draw(balls[i].shape);
    }

    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    constexpr float BALL_SIZE = 50;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Moving Ball");
    sf::Clock clock;

    std::vector<Ball> balls;
    sf::Color(color[8]);
    resolutionColor(color);

    while (window.isOpen())
    {
        pollEvents(window, balls, BALL_SIZE, color);
        const float dt = clock.restart().asSeconds();
        const float physics = dt / 10;
        destructionBall(balls);
        for (int i = 0; i < 10; ++i)
        {
            update(WINDOW_WIDTH, WINDOW_HEIGHT, physics, BALL_SIZE, balls);
        }
        redrawFrame(window, balls);
    }
}