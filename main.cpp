#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>


std::string formatNumber(float value, int precision = 2) {
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(precision) << value;
    return stream.str();
}

int main() {
    
    sf::RenderWindow window(sf::VideoMode({ 800, 700 }), "Spring Oscillation Physics Demo");
    window.setFramerateLimit(60);

    
    sf::Font font;
    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf")) {
        
        std::cout << "Warning: Could not load font. Text will not be displayed.\n";
    }

    sf::Text infoText(font, "", 18);
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition({ 20.f, 20.f });

    
    const float gravity = 980.f;        
    float mass = 1.0f;                  
    float stiffness = 1500.f;           
    float damping = 2.0f;              

    const sf::Vector2f anchorPos(400.f, 100.f); 
    const float restLength = 150.f; 

    
    float posY = anchorPos.y + restLength + 100.f;
    float velocityY = 0.f;

   
    sf::CircleShape massShape(25.f);
    massShape.setFillColor(sf::Color::Cyan);
    massShape.setOrigin({ 25.f, 0.f });

    sf::RectangleShape springLine;
    springLine.setFillColor(sf::Color::Yellow);

    sf::Clock clock;
    bool isPaused = false;

    while (window.isOpen()) {
        // Обробка подій
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (event->is<sf::Event::KeyPressed>()) {
                const auto key = event->getIf<sf::Event::KeyPressed>();
                if (key->code == sf::Keyboard::Key::Up) {
                    mass += 0.2f; // Збільшити масу
                }
                if (key->code == sf::Keyboard::Key::Down) {
                    mass = std::max(0.2f, mass - 0.2f); // Зменшити масу
                }
                if (key->code == sf::Keyboard::Key::Right) {
                    stiffness += 200.f; // Збільшити жорсткість
                }
                if (key->code == sf::Keyboard::Key::Left) {
                    stiffness = std::max(200.f, stiffness - 200.f); // Зменшити жорсткість
                }
                if (key->code == sf::Keyboard::Key::Space) {
                    isPaused = !isPaused; // Пауза / Запуск
                }
                if (key->code == sf::Keyboard::Key::R) {
                    // Скидання у початковий стан
                    posY = anchorPos.y + restLength + 100.f;
                    velocityY = 0.f;
                }
            }
        }

   
        float dt = clock.restart().asSeconds();
        if (dt > 0.1f) dt = 0.1f;

        if (!isPaused) {

            float displacement = (posY - anchorPos.y) - restLength;
            float acceleration = gravity - (stiffness / mass) * displacement - (damping / mass) * velocityY;

            velocityY += acceleration * dt;
            posY += velocityY * dt;
        }

        massShape.setPosition({ anchorPos.x, posY });


        float springLength = posY - anchorPos.y;
        springLine.setSize({ 4.f, springLength });
        springLine.setPosition({ anchorPos.x - 2.f, anchorPos.y });

        if (font.getInfo().family != "") {
            infoText.setString(
                "[UP / DOWN] Masa (m): " + formatNumber(mass, 1) + " kg\n"
                "[LEFT / RIGHT] Zhorstkist (k): " + formatNumber(stiffness, 0) + " N/m\n"
                "[SPACE] Pauza / Zapusk (Paused: " + (isPaused ? "YES" : "NO") + ")\n"
                "[R] Skynuty stan\n"
                "Shvydkist (V): " + formatNumber(velocityY, 1) + " pix/s"
            );
        }

        window.clear(sf::Color(30, 30, 40));

        window.draw(springLine);
        window.draw(massShape);

        sf::CircleShape anchor(6.f);
        anchor.setFillColor(sf::Color::Red);
        anchor.setOrigin({ 6.f, 6.f });
        anchor.setPosition(anchorPos);
        window.draw(anchor);

        if (font.getInfo().family != "") {
            window.draw(infoText);
        }

        window.display();
    }

    return 0;
}