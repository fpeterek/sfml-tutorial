#include <iostream>
#include <cmath>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "custom_rect.hpp"

sf::VideoMode fullscreen() {
    return sf::VideoMode(1920, 1080);
}

sf::RenderWindow createWindow() {
   return sf::RenderWindow(fullscreen(), "Example 1", sf::Style::Fullscreen);
}

float sign(const float arg) {
    return arg ? (arg < 0.f ? -1.f : 1.f) : 0.f;
}

float calcDec(const float cv, const float dt) {
    return std::max(cv*cv / 400, 5.f) * dt * sign(cv);
}

void boundV(float & vx, float & vy, const float maxVelocity) {
    const float currentV = std::sqrt(vx*vx + vy*vy);
    const float maxV = maxVelocity*maxVelocity;
    if (currentV < maxV) {
        return;
    }

    const float ratio = currentV / maxV;
    const float div = std::sqrt(ratio);

    vx /= div;
    vy /= div;
}

int main(int argc, const char * argv[]) {

    auto window = createWindow();

    /*auto rect = sf::RectangleShape(sf::Vector2f(70.f, 35.f));
    rect.setFillColor(sf::Color(247, 104, 94));
    rect.setOrigin(35, 17.5);
    rect.setPosition(window.getSize().x / 2, window.getSize().y / 2);*/

    auto rect = CustomRect(200, 100, 25);
    rect.setFillColor(sf::Color(247, 104, 94));
    rect.setOrigin(100, 50);
    rect.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    constexpr float acc = 1000.f;
    constexpr float rv = M_PI/2;
    constexpr float maxV = 400;
    float vx = 0.f;
    float vy = 0.f;
    float rotation = -(M_PI/2);

    sf::RectangleShape line(sf::Vector2f(5000, 2));
    line.setOrigin(2500, 1);
    line.setFillColor(sf::Color(0, 255, 47));

    rect.setRotation(rotation);
    line.setRotation(rotation);

    bool locked = false;

    sf::Clock clock;

    while (window.isOpen()) {

        const auto dt = clock.getElapsedTime().asSeconds();
        clock.restart();

        sf::Event e{};
        while (window.pollEvent(e)) {

            if (e.type == sf::Event::Closed) {
                window.close();
                break;
            }

            if (e.type == sf::Event::KeyPressed and e.key.code == sf::Keyboard::Escape) {
                window.close();
                break;
            }

            if (e.type == sf::Event::KeyPressed and e.key.code == sf::Keyboard::Space) {
                locked = !locked;
            }

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            rotation += rv * dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            rotation -= rv * dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            vx += acc * std::cos(rotation) * dt;
            vy += acc * std::sin(rotation) * dt;
        }

        const auto v = std::sqrt(vx*vx + vy*vy);
        if (v) {
            const auto dec = calcDec(v, dt);
            const auto ratio = (vx * vx) / (v * v);
            const auto dx = dec * ratio * sign(vx);
            const auto dy = dec * (1 - ratio) * sign(vy);

            vx = (std::abs(dx) > std::abs(vx)) ? 0 : (vx - dx);
            vy = (std::abs(dy) > std::abs(vy)) ? 0 : (vy - dy);
        }

        rect.setRotation(rotation * (180.f/M_PI));
        rect.setPosition(rect.getPosition().x + vx * dt, rect.getPosition().y + vy*dt);

        const auto bounds = rect.getGlobalBounds();

        if (bounds.left < 0) {
            rect.setPosition(rect.getPosition().x - bounds.left, rect.getPosition().y);
            vx *= -1;
        } else if (bounds.left + bounds.width > window.getSize().x) {
            rect.setPosition(rect.getPosition().x - (bounds.left + bounds.width - window.getSize().x), rect.getPosition().y);
            vx *= -1;
        }

        if (bounds.top < 0) {
            rect.setPosition(rect.getPosition().x, rect.getPosition().y - bounds.top);
            vy *= -1;
        } else if (bounds.top + bounds.height > window.getSize().y) {
            rect.setPosition(rect.getPosition().x, rect.getPosition().y - (bounds.top + bounds.height - window.getSize().y));
            vy *= -1;
        }

        if (!locked) {
            line.setPosition(rect.getPosition());
            line.setRotation(rotation * (180.f / M_PI));
        }

        window.clear(sf::Color(143, 175, 227));
        window.draw(line);
        window.draw(rect);
        //window.draw(shape);
        window.display();
    }

}












