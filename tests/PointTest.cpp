#include "Point.hpp"

#include <gtest/gtest.h>


TEST(PointTest, DefaultInitializesToZero)
{
    Point p{};
    EXPECT_EQ(p.x, 0);
    EXPECT_EQ(p.y, 0);
}

TEST(PointTest, InitializesFields)
{
    Point p{1.0, 1.0};
    EXPECT_EQ(p.x, 1.0);
    EXPECT_EQ(p.y, 1.0);
}
