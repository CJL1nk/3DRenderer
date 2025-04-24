#include "includes.h"
#include "Object.h"

int main()
{
    // Create window
    sf::Vector2u windowSize = sf::Vector2u(480, 480);
    sf::RenderWindow window(sf::VideoMode(windowSize), "Window");
    window.setFramerateLimit(30);

    // Random Number stuff
    std::mt19937 generator(2);
    std::uniform_int_distribution<int> distribution(3, 20);

    // Stuff for bouncing around window
    int xmod = 1;
    int ymod = 1;

    int velX = 10;
    int velY = 10;

    // Object construction
    sf::Vector2f centerPos = sf::Vector2f(240, 0);

    // Point construction is relative to the objects "center" position
    sf::VertexArray shape(sf::PrimitiveType::LineStrip, 11);

    shape[0].position = sf::Vector2f(0.f, -50.f);
    shape[1].position = sf::Vector2f(15.f, -15.f);
    shape[2].position = sf::Vector2f(50.f, -15.f);
    shape[3].position = sf::Vector2f(25.f, 10.f);
    shape[4].position = sf::Vector2f(35.f, 50.f);
    shape[5].position = sf::Vector2f(0.f, 25.f);
    shape[6].position = sf::Vector2f(-35.f, 50.f);
    shape[7].position = sf::Vector2f(-25.f, 10.f);
    shape[8].position = sf::Vector2f(-50.f, -15.f);
    shape[9].position = sf::Vector2f(-15.f, -15.f);
    shape[10].position = shape[0].position;


    Object obj1(shape, centerPos, window);

    while (window.isOpen())
    {
        // Update positions
        centerPos.x += velX * xmod;
        centerPos.y += velY * ymod;

        if (centerPos.x > windowSize.x || centerPos.x < 0) {
            centerPos.x = centerPos.x > windowSize.x ? windowSize.x : 0; // Snap to edge if it goes beyond
            xmod *= -1; // Reverses x direction
            velX = distribution(generator);
        }
        if (centerPos.y > windowSize.y || centerPos.y < 0) {
            centerPos.y = centerPos.y > windowSize.y ? windowSize.y : 0; // Snap to edge if it goes beyond
            ymod *= -1; // Reverses y direction
            velY = distribution(generator);
        }

        obj1.move(centerPos); // Move the actual object itself

        // Event processing
        while (const std::optional event = window.pollEvent())
        {
            // Request for closing the window
            if (event->is<sf::Event::Closed>()) window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) window.close();
        }

        // Activate the window for OpenGL rendering
        window.setActive();
        window.clear(sf::Color::Black);

        obj1.draw();

        window.display();
    }
}
