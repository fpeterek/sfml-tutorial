//
// Created by fpeterek on 28.07.20.
//

#ifndef UKAZKA1_CUSTOM_RECT_HPP
#define UKAZKA1_CUSTOM_RECT_HPP

#include <vector>

#include <SFML/Graphics.hpp>

class CustomRect : public sf::ConvexShape {

    // std::vector<sf::Vector2f> points;

public:

    CustomRect(uint64_t width, uint64_t height, float radius);

    // size_t getPointCount() const override;
    // sf::Vector2f getPoint(std::size_t index) const override;

};

#endif //UKAZKA1_CUSTOM_RECT_HPP
