//
// Created by Filip Peterek on 01/08/2020.
//

#ifndef USERINPUT_LINE_HPP
#define USERINPUT_LINE_HPP

#include <SFML/Graphics.hpp>

class Line : public sf::Drawable {

    const sf::CircleShape beginCircle;
    const sf::RectangleShape rect;
    const sf::CircleShape endCircle;

public:

    Line(sf::CircleShape begin, sf::RectangleShape rect, sf::CircleShape end);

    void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

};

#endif //USERINPUT_LINE_HPP
