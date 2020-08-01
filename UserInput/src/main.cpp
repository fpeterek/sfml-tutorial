#include <vector>
#include <cmath>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

sf::VideoMode fullscreen() {
    return sf::VideoMode::getDesktopMode();
}

sf::RenderWindow window() {
    return sf::RenderWindow(fullscreen(), "User Input", sf::Style::Fullscreen);
}

bool isClosed(const sf::Event & e) {
    return e.type == sf::Event::Closed;
}

bool isEscape(const sf::Event & e) {
    return e.type == sf::Event::KeyPressed and e.key.code == sf::Keyboard::Escape;
}

bool isSpaceDown(const sf::Event & e) {
    return e.type == sf::Event::KeyPressed and e.key.code == sf::Keyboard::Space;
}

bool isSpaceUp(const sf::Event & e) {
    return e.type == sf::Event::KeyReleased and e.key.code == sf::Keyboard::Space;
}

sf::Vector2f mousePosition(sf::Window & win) {
    const auto center = sf::Mouse::getPosition(win);
    return sf::Vector2f(center.x, center.y);
}

sf::CircleShape createCircle(sf::Window & win) {
    const auto center = mousePosition(win);
    sf::CircleShape circle;
    circle.setPosition(center.x, center.y);
    circle.setFillColor(sf::Color(52, 132, 168));
    return circle;
}

float calcRadius(const sf::Vector2f center, sf::Window & win) {

    const auto mouse = mousePosition(win);

    const auto sx = mouse.x - center.x;
    const auto sy = mouse.y - center.y;

    const auto s = std::sqrt(sx*sx + sy*sy);

    return s;

}

void resizeCircle(sf::CircleShape & circle, sf::Window & win) {

    const auto center = circle.getPosition();
    const auto radius = calcRadius(center, win);

    circle.setRadius(radius);
    circle.setOrigin(radius, radius);
    circle.setPosition(center);
    circle.setPointCount(radius/2);

}

int main(int argc, const char * argv[]) {

    auto win = window();

    std::vector<sf::CircleShape> circles;
    bool circle = false;

    while (win.isOpen()) {

        sf::Event ev{};

        while (win.pollEvent(ev)) {
            if (isClosed(ev) or isEscape(ev)) {
                win.close();
                break;
            }
            if (isSpaceDown(ev) and !circle) {
                circle = true;
                circles.emplace_back(createCircle(win));
            }
            else if (isSpaceUp(ev)) {
                circle = false;
            }
        }

        if (circle) {
            resizeCircle(circles.back(), win);
        }

        win.clear(sf::Color::White);
        for (const auto c : circles) {
            win.draw(c);
        }
        win.display();

    }

}
