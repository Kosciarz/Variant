#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

struct Point
{
    double x;
    double y;

    explicit Point(double x, double y);

    friend std::ostream& operator<<(std::ostream& os, const Point& obj);
};

inline std::ostream& operator<<(std::ostream& os, const Point& obj)
{
    return os << obj.x << ", " << obj.y;
}

#endif // POINT_HPP