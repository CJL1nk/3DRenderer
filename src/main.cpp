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
    Point("8", Vector3(-1.5f,  1.5f,  1.5f))
};

int main() {

    // Movement speed
    float movementSpeed = 0.8f;
    float rotationSpeed = 0.06f;
    int movXMod = 1;
    int movZMod = 1;

    sf::SoundBuffer buffer("./Audio/boing.ogg");
    sf::Sound sound(buffer);

    std::mt19937 gen(time(nullptr));
    std::uniform_real_distribution<> distrib(0.2, .5);

    float pathX = distrib(gen);
    float pathZ = distrib(gen);

    // Create window
    sf::Vector2u windowSize = sf::Vector2u(1920, 1080);
    sf::RenderWindow window(sf::VideoMode(windowSize), "Window");
    window.setFramerateLimit(60);

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
    Object plane = Object(planePoints, planePos, window);
    plane.setColor(sf::Color::Green);

    Hitbox cube1Box = Hitbox(HitboxType::CUBE);
    Hitbox cube2Box = Hitbox(HitboxType::CUBE);
    cube1Box.init(3.f);
    cube2Box.init(3.f);
    // Create object with above defined points
    Object cube1 = Object(points, Position(0, 0, 0, Rotation(0, 0, 0)), window, cube1Box);
    cube1.setColor(sf::Color::Red);
    Object cube2 = Object(points, Position(0, 0, 0, Rotation(0, 0, 0)), window, cube2Box);
    cube2.setColor(sf::Color::Blue);

    Camera camera(Position(0, 0, 5));


    while (window.isOpen()) {

        cube1.move({pathX * movXMod, 0, pathZ * movZMod,
            {0, 4., 2.}});

        cube2.move({0, 0, 0,
            {0.7, 0, -0.3}});

        if (cube1.getX() > 100) {
            movXMod *= -1;
            cube1.setX(100);
            pathX = distrib(gen);
            sound.play();
        } else if (cube1.getX() < -100) {
            movXMod *= -1;
            cube1.setX(-100);
            pathX = distrib(gen);
            sound.play();
        }

        if (cube1.getZ() > 100) {
            movZMod *= -1;
            cube1.setZ(100);
            pathZ = distrib(gen);
            sound.play();
        } else if (cube1.getZ() < -100) {
            movZMod *= -1;
            cube1.setZ(-100);
            pathZ = distrib(gen);
            sound.play();
        }

        if (cube1.collidesWith(cube2)) {
            movXMod *= -1;
            movZMod *= -1;
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
            cube2.move({0, 0, 0.3, {}});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)) {
            cube2.move({0, 0, -0.3, {}});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) {
            cube2.move({0.3, 0, 0, {}});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J)) {
            cube2.move({-0.3, 0, 0, {}});
        }

        // Rendering
        window.clear(sf::Color::Black);
        plane.draw(camera, false);
        cube1.draw(camera);
        cube2.draw(camera);
        window.display();
    }
}
