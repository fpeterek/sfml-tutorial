//
// Created by fpeterek on 28.07.20.
//

#include "custom_rect.hpp"

#include <iostream>
#include <algorithm>
#include <iomanip>


CustomRect::CustomRect(const uint64_t width, const uint64_t height, const float radius) {

    std::vector<sf::Vector2f> top;
    const float horMod = (width * width) / (radius * 4);

    for (uint64_t i = 0; i < width; ++i) {

        if (i and i != width and i%3) {
            continue;
        }

        const float x = i;

        const uint64_t distanceFromCorner = x > width / 2 ? width - x : x;
        const uint64_t distanceFromCenter = (width / 2) - distanceFromCorner;
        const float y = distanceFromCenter*distanceFromCenter / horMod * -1 + radius;
        top.emplace_back(x, y);
    }

    std::vector<sf::Vector2f> right;
    const float vertMod = (height * height) / (radius * 4);

    for (uint64_t i = 1; i < height; ++i) {

        if (i != 1 and i != height-1 and i%3) {
            continue;
        }

        const float y = i;

        const uint64_t distanceFromCorner = y > height/2 ? height-y : y;
        const uint64_t distanceFromCenter = (height / 2) - distanceFromCorner;
        const float x = width - (distanceFromCenter*distanceFromCenter / vertMod * -1 + radius);

        right.emplace_back(x, y);
    }

    std::vector<sf::Vector2f> bottom;
    bottom.reserve(top.size());

    auto transformTop = [&](sf::Vector2f point) -> sf::Vector2f {
        point.y = height - point.y;
        return point;
    };

    std::transform(top.rbegin(), top.rend(), std::back_inserter(bottom), transformTop);

    std::vector<sf::Vector2f> left;
    left.reserve(right.size());

    auto transformRight = [&](sf::Vector2f point) -> sf::Vector2f {
        point.x = std::abs(width - point.x);
        return point;
    };

    std::transform(right.rbegin(), right.rend(), std::back_inserter(left), transformRight);

    std::vector<sf::Vector2f> points;

    std::copy(top.begin(), top.end(), std::back_inserter(points));
    std::copy(right.begin(), right.end(), std::back_inserter(points));
    std::copy(bottom.begin(), bottom.end(), std::back_inserter(points));
    std::copy(left.begin(), left.end(), std::back_inserter(points));

    setPointCount(points.size());
    for (uint64_t i = 0; i < points.size(); ++i) {
        setPoint(i, points[i]);
    }

    /*std::for_each(points.begin(), points.end(), [](sf::Vector2f point) -> void {
        std::cout << std::setprecision(4) << "[" << std::setw(5) << point.x << std::setw(0) << ", "
                  << std::setw(5) << point.y << std::setw(0) << "]" << std::endl;
    });*/
}

/*size_t CustomRect::getPointCount() const {
    return points.size();
}

sf::Vector2f CustomRect::getPoint(const size_t i) const {
    return points[i];
}*/
