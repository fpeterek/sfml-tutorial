#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

sf::VideoMode fullscreen() {
    return sf::VideoMode::getDesktopMode();
}

sf::RenderWindow createWindow() {
    return sf::RenderWindow(fullscreen(), "SFML Tutorial", sf::Style::Fullscreen);
}

template<uint64_t width, uint64_t height>
sf::RectangleShape createRect(const sf::Vector2u windowSize) {
    sf::RectangleShape rect(sf::Vector2f(width, height));
    rect.setOrigin(width / 2.f, height / 2.f);
    rect.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
    rect.setFillColor(sf::Color(255, 115, 102));
    rect.setOutlineColor(sf::Color(171, 43, 31));
    rect.setOutlineThickness(10);
    return rect;
}

bool isClosed(const sf::Event & e) {
    return e.type == sf::Event::Closed;
}

bool isEscape(const sf::Event & e) {
    return e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape;
}

int main(int argc, const char * argv[]) {

    auto win = createWindow();

    auto rect = createRect<500, 200>(win.getSize());

    while (win.isOpen()) {

        sf::Event ev{};
        while (win.pollEvent(ev)) {
            if (isClosed(ev) or isEscape(ev)) {
                win.close();
                break;
            }
        }

        win.clear(sf::Color(141, 215, 242));
        win.draw(rect);
        win.display();

    }
}
