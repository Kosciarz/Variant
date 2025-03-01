#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "Point.hpp"

#include <iostream>
#include <variant>

// An example of the visitor pattern
struct Visitor
{
    void operator()(auto&& item) { std::cout << item << '\n'; }
};

inline void CheckParam(const Point& p, int x)
{
    std::cout << "Point p: " << p << ". Int x: " << x << '\n';
}

inline void CheckParam(const Point& p, double x)
{
    std::cout << "Point p: " << p << ". Double x: " << x << '\n';
}

template <typename T>
struct VisitorWithParams
{
    VisitorWithParams(T param)
        : m_val{param}
    {
    }

    void operator()(auto& item) { CheckParam(item, m_val); }

    T m_val{};
};

// An example of the overload pattern
template <typename... Lambdas>
struct Overload : Lambdas...
{
    using Lambdas::operator()...;

    // safety net for types unsupported types e.g. implicit conversions into
    // bool
    consteval void operator()(auto) const { static_assert(false, "Unsupported type"); }
};

#endif // VISITOR_HPP