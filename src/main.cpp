#include "includes.h"
#include "Object.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({480, 480}), "Window");
    window.setFramerateLimit(5);

    sf::Vector2f pos = sf::Vector2f(5, 5);

    sf::VertexArray square(sf::PrimitiveType::LineStrip, 5);
    square[0].position = sf::Vector2f(190.0f, 190.0f); // Top-left corner
    square[1].position = sf::Vector2f(290.0f, 190.0f); // Top-right corner
    square[2].position = sf::Vector2f(290.0f, 290.0f); // Bottom-right corner
    square[3].position = sf::Vector2f(190.0f, 260.0f); // Bottom-left corner
    square[4].position = sf::Vector2f(190.0f, 190.0f); // Close the square (back to top-left corner)

    Object obj1(square, pos, window);

    while (window.isOpen())
    {
        pos.x -= 5;
        pos.y += 2;
        obj1.move(pos);

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
