#include "includes.h"
#include "Object.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({480, 480}), "Window");
    window.setFramerateLimit(30);

    sf::Vector2f centerPos = sf::Vector2f(0, 0);
    int xmod = 1;
    int ymod = 1;

    // Point construction is relative to the objects "center" position
    sf::VertexArray shape(sf::PrimitiveType::LineStrip, 7);
    shape[0].position = sf::Vector2f(-50.0f, -50.0f);
    shape[1].position = sf::Vector2f(-50.0f, 50.0f);
    shape[2].position = sf::Vector2f(70.0f, 50.0f);
    shape[3].position = sf::Vector2f(50.0f, -50.0f);
    shape[4].position = sf::Vector2f(-50.0f, -40.0f);
    shape[5].position = sf::Vector2f(60.0f, -40.0f);
    shape[5].position = sf::Vector2f(70.0f, -20.0f);

    Object obj1(shape, centerPos, window);

    while (window.isOpen())
    {
        centerPos.x += 10 * xmod;
        centerPos.y += 10 * ymod;

        if (centerPos.x > 480 || centerPos.x < 0) xmod *= -1;
        if (centerPos.y > 480 || centerPos.y < 0) ymod *= -1;

        obj1.move(centerPos);

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
