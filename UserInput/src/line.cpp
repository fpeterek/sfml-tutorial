//
// Created by Filip Peterek on 01/08/2020.
//

#include "line.hpp"

#include <utility>

void Line::draw(sf::RenderTarget & target, sf::RenderStates states) const {
    target.draw(beginCircle, states);
    target.draw(rect, states);
    target.draw(endCircle, states);
}

Line::Line(sf::CircleShape begin,
           sf::RectangleShape rect,
           sf::CircleShape end) :
               beginCircle(std::move(begin)),
               rect(std::move(rect)),
               endCircle(std::move(end)) { }
