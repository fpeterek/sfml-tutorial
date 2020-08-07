#include <vector>
#include <cmath>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "line.hpp"

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

bool isMouseDown(const sf::Event & e) {
    return e.type == sf::Event::MouseButtonPressed and e.mouseButton.button == sf::Mouse::Left;
}

bool isMouseUp(const sf::Event & e) {
    return e.type == sf::Event::MouseButtonReleased and e.mouseButton.button == sf::Mouse::Left;
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

float calcDistance(const sf::Vector2f p1, const sf::Vector2f p2) {

    const auto sx = p1.x - p2.x;
    const auto sy = p1.y - p2.y;

    return std::sqrt(sx*sx + sy*sy);
}

float calcRadius(const sf::Vector2f center, sf::Window & win) {
    return calcDistance(center, mousePosition(win));
}

void resizeCircle(sf::CircleShape & circle, sf::Window & win) {

    const auto center = circle.getPosition();
    const auto radius = calcRadius(center, win);

    circle.setRadius(radius);
    circle.setOrigin(radius, radius);
    circle.setPosition(center);
    circle.setPointCount(std::max(10.f, radius / 2.f));

}

void createLine(const sf::Vector2f begin, const sf::Vector2f end, std::vector<Line> & lines) {

    const auto len = calcDistance(begin, end);
    const auto sx = end.x - begin.x;

    const auto cos = sx / len;
    const auto tmpAngle = std::acos(cos) * (180/M_PI);
    const auto angle = (end.y < begin.y) ? 360 - tmpAngle : tmpAngle;

    constexpr float lineWidth = 5;
    constexpr float origX = 0;
    constexpr float origY = 3;

    const sf::Color color(252, 186, 3);

    sf::RectangleShape line(sf::Vector2f(len, lineWidth));
    line.setOrigin(origX, origY);
    line.setPosition(begin);
    line.setRotation(angle);

    sf::CircleShape beginCircle(lineWidth/2);
    beginCircle.setOrigin(lineWidth/2, lineWidth/2);
    beginCircle.setPosition(begin);

    sf::CircleShape endCircle(lineWidth/2);
    endCircle.setOrigin(lineWidth/2, lineWidth/2);
    endCircle.setPosition(end);

    line.setFillColor(color);
    beginCircle.setFillColor(color);
    endCircle.setFillColor(color);

    lines.emplace_back(beginCircle, line, endCircle);

}

int main(int argc, const char * argv[]) {

    auto win = window();

    std::vector<sf::CircleShape> circles;
    std::vector<Line> lines;
    bool circle = false;
    bool line = false;
    sf::Vector2f lineBegin;

    while (win.isOpen()) {

        sf::Event ev{};

        while (win.pollEvent(ev)) {
            if (isClosed(ev) or isEscape(ev)) {
                win.close();
                break;
            }
            if (isSpaceDown(ev) and not circle) {
                line = false;
                circle = true;
                circles.emplace_back(createCircle(win));
            }
            else if (isSpaceUp(ev)) {
                circle = false;
            }
            else if (isMouseDown(ev) and not line) {
                circle = false;
                line = true;
                lineBegin = mousePosition(win);
            }
            else if (isMouseUp(ev)) {
                line = false;
            }
        }

        if (circle) {
            resizeCircle(circles.back(), win);
        }
        else if (line) {
            const auto lineEnd = mousePosition(win);
            createLine(lineBegin, lineEnd, lines);
            lineBegin = lineEnd;
        }


        win.clear(sf::Color::White);
        for (const auto & c : circles) {
            win.draw(c);
        }
        for (const auto & l : lines) {
            win.draw(l);
        }
        win.display();

    }

}
