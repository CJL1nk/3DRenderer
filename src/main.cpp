#include "includes.h"
#include "types.h"
#include "Object.h"
#include "objects.h"

/**
 * Calculates distance between 2 objects, used for camera here
 * @param p1 First position
 * @param p2 Second position
 * @return Distance between the two objects
 */
float calculateDistance(const Position& p1, const Position& p2) {
    return std::sqrt(
        std::pow(p2.x - p1.x, 2) +
        std::pow(p2.y - p1.y, 2) +
        std::pow(p2.z - p1.z, 2)
    );
}

/**
 * Sorts objects based on distance to camera and renders them, ensures correct draw order BUT is not very optimized
 * @param window Window to render in
 */
void drawObjects(sf::RenderWindow& window) {
    std::sort(Object::_allObjects.begin(), Object::_allObjects.end(), [](const Object* a, const Object* b) {
        const float distA = calculateDistance(camera.pos, a->getPos());
        const float distB = calculateDistance(camera.pos, b->getPos());
        return distA > distB;  // Sort farthest first
    });

    for (const auto& obj : Object::_allObjects) {
        obj->draw(window);
    }
}

/**
 * Main logic of the program
 * @return 0 if successful
 */
int main() {

    // Movement speed
    float movementSpeed = 0.8f;
    float rotationSpeed = 0.06f;
    int movXMod = 1;
    int movZMod = 1;

    sf::SoundBuffer buffer("./Audio/boing.ogg");
    sf::Sound sound(buffer);

    std::mt19937 gen(time(nullptr));
    std::uniform_real_distribution<> distrib(0.2f, 0.8f);

    float pathX = distrib(gen);
    float pathZ = distrib(gen);

    // Create window
    sf::Vector2u windowSize = sf::Vector2u(1920, 1080);
    sf::RenderWindow window(sf::VideoMode(windowSize), "Window");
    window.setFramerateLimit(60);

    while (window.isOpen()) {

        cube1.move({pathX * movXMod, 0, pathZ * movZMod,
            {0, 4., 2.}});

        cube2.move({0, 0, 0,
            {0.7, 0, -0.3}});

        tetrahedron.move({0, 0, 0, {0, 0, 1}});

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
        drawObjects(window);
        window.display();
    }
}
