#include "includes.h"
#include "Point.h"
#include "types.h"
#include "Object.h"

std::vector<Point> points = {
    Point("1", Vector3(-1.5f, -1.5f, -1.5f), std::vector<std::string>{"2", "4", "5"}),
    Point("2", Vector3( 1.5f, -1.5f, -1.5f), std::vector<std::string>{"3", "6"}),
    Point("3", Vector3( 1.5f,  1.5f, -1.5f), std::vector<std::string>{"4", "7"}),
    Point("4", Vector3(-1.5f,  1.5f, -1.5f), std::vector<std::string>{"1", "8"}),
    Point("5", Vector3(-1.5f, -1.5f,  1.5f), std::vector<std::string>{"6", "8"}),
    Point("6", Vector3( 1.5f, -1.5f,  1.5f), std::vector<std::string>{"7"}),
    Point("7", Vector3( 1.5f,  1.5f,  1.5f), std::vector<std::string>{"8"}),
    Point("8", Vector3(-1.5f,  1.5f,  1.5f)),
};

int main() {

    // Movement speed
    float movementSpeed = 0.8f;
    float rotationSpeed = 0.12f;
    int movXMod = 1;
    int movZMod = 1;

    sf::SoundBuffer buffer("./Audio/boing.ogg");
    sf::Sound sound(buffer);

    std::mt19937 gen(6);
    std::uniform_real_distribution<> distrib(0.8, 10.);

    float pathX = distrib(gen);
    float pathZ = distrib(gen);

    // Create window
    sf::Vector2u windowSize = sf::Vector2u(980, 720);
    sf::RenderWindow window(sf::VideoMode(windowSize), "Window");
    window.setFramerateLimit(30);

    std::vector<Point> planePoints;
    for (int x = -100; x <= 100; x += 10) {
        for (int z = -100; z <= 100; z += 10) {
            std::string label = "point_" + std::to_string(x) + "_" + std::to_string(z);
            std::vector<std::string> connections;

            // Connect point to its neighboring points
            if (x + 10 <= 100) connections.push_back("point_" + std::to_string(x + 10) + "_" + std::to_string(z)); // Right
            if (z + 10 <= 100) connections.push_back("point_" + std::to_string(x) + "_" + std::to_string(z + 10)); // Down

            // Create the point
            planePoints.emplace_back(Point(label, Vector3(x, 0, z), connections));
        }
    }

    Position planePos = Position(0, 0, 0, Rotation(0, 0, 0));
    Object plane = Object(planePoints, &planePos, window);
    plane.setColor(sf::Color::Green);

    Position pos = Position(0, 0, 0, Rotation(0, 0, 0));
    Position pos2 = Position(5, -5, 5, Rotation(0, 0, 0));

    // Create object with above defined points
    Object cube1 = Object(points, &pos, window);
    cube1.setColor(sf::Color::Red);
    Object cube2 = Object(points, &pos2, window);
    cube2.setColor(sf::Color::Blue);

    Camera camera(Position(0, 0, 5));


    while (window.isOpen()) {

        pos.rotation.yaw += 4.;
        pos.rotation.pitch += 2.;

        pos.x += pathX * movXMod;
        pos.z += pathZ * movZMod;

        pos2.rotation.yaw += -0.3;
        pos2.rotation.pitch += 0.7;

        if (pos.x > 100) {
            movXMod *= -1;
            pos.x = 100;
            pathX = distrib(gen);
            sound.play();
        } else if (pos.x < -100) {
            movXMod *= -1;
            pos.x = -100;
            pathX = distrib(gen);
            sound.play();
        }

        if (pos.z > 100) {
            movZMod *= -1;
            pos.z = 100;
            pathZ = distrib(gen);
            sound.play();
        } else if (pos.z < -100) {
            movZMod *= -1;
            pos.z = -100;
            pathZ = distrib(gen);
            sound.play();
        }


        // Event processing
        while (const std::optional event = window.pollEvent())
            {
            // Request for closing the window
            if (event->is<sf::Event::Closed>()) window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) window.close();
        }

        // Keyboard controls
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            camera.pos.z -= movementSpeed * cos(camera.pos.rotation.yaw); // Forward
            camera.pos.x -= movementSpeed * sin(camera.pos.rotation.yaw);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            camera.pos.z += movementSpeed * cos(camera.pos.rotation.yaw); // Backward
            camera.pos.x += movementSpeed * sin(camera.pos.rotation.yaw);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            camera.pos.x -= movementSpeed * cos(camera.pos.rotation.yaw); // Strafe left
            camera.pos.z += movementSpeed * sin(camera.pos.rotation.yaw);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            camera.pos.x += movementSpeed * cos(camera.pos.rotation.yaw); // Strafe right
            camera.pos.z -= movementSpeed * sin(camera.pos.rotation.yaw);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) {
            camera.pos.y += movementSpeed; // Move up
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            camera.pos.y -= movementSpeed; // Move down
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            camera.pos.rotation.yaw -= rotationSpeed; // Turn left
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            camera.pos.rotation.yaw += rotationSpeed; // Turn right
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            camera.pos.rotation.pitch -= rotationSpeed; // Look up
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            camera.pos.rotation.pitch += rotationSpeed; // Look down
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I)) {
            pos2.z += 0.3;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)) {
            pos2.z -= 0.3;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) {
            pos2.x += 0.3;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J)) {
            pos2.x -= 0.3;
        }

        // Rendering
        window.clear(sf::Color::Black);
        plane.draw(camera);
        cube1.draw(camera);
        cube2.draw(camera);
        window.display();
    }
}
