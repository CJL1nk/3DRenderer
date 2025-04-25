#include "includes.h"
#include "Point.h"
#include "types.h"
#include "Object.h"

/* std::vector<Point> points = {
    Point("1", Vector3(-0.5f, -0.5f, -0.5f), std::vector<std::string>{"2", "4", "5"}),
    Point("2", Vector3( 0.5f, -0.5f, -0.5f), std::vector<std::string>{"3", "6"}),
    Point("3", Vector3( 0.5f,  0.5f, -0.5f), std::vector<std::string>{"4", "7"}),
    Point("4", Vector3(-0.5f,  0.5f, -0.5f), std::vector<std::string>{"1", "8"}),
    Point("5", Vector3(-0.5f, -0.5f,  0.5f), std::vector<std::string>{"6", "8"}),
    Point("6", Vector3( 0.5f, -0.5f,  0.5f), std::vector<std::string>{"7"}),
    Point("7", Vector3( 0.5f,  0.5f,  0.5f), std::vector<std::string>{"8"}),
    Point("8", Vector3(-0.5f,  0.5f,  0.5f)),
}; */

int main()
{
    // Create window
    sf::Vector2u windowSize = sf::Vector2u(800, 600);
    sf::RenderWindow window(sf::VideoMode(windowSize), "Window");
    window.setFramerateLimit(30);

    Point p1 = Point("1", Vector3(-0.5f, -0.5f, -0.5f));
    Point p2 = Point("2", Vector3( 0.5f, -0.5f, -0.5f));
    Point p3 = Point("3", Vector3( 0.5f,   0.5f, -0.5f));
    Point p4 = Point("4", Vector3(-0.5f,    0.5f, -0.5f));
    Point p5 = Point("5", Vector3(-0.5f, -0.5f,   0.5f));
    Point p6 = Point("6", Vector3( 0.5f, -0.5f,    0.5f));
    Point p7 = Point("7", Vector3( 0.5f,    0.5f,     0.5f));
    Point p8 = Point("8", Vector3(-0.5f,     0.5f,      0.5f));
    p1.addConnection({p2, p4, p5});
    p2.addConnection({p3, p6});
    p3.addConnection({p4, p7});
    p4.addConnection({p1, p8});
    p5.addConnection({p6, p8});
    p6.addConnection({p7});
    p7.addConnection({p8});

    std::vector<Point> points {p1, p2, p3, p4, p5, p6, p7, p8};

    Object cube = Object(points, Vector3(0, 0, 0), window);

    while (window.isOpen())
    {
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

        cube.draw();

        window.display();
    }
}
