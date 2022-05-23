#include "src/lib/polynimal.hpp"
#include <iostream>
#include <vector>
#include "gtest/gtest.h"

TEST(Polynomal_Should, Return_Polynimal){
    std::vector<int> coef (3, 2);
    polynomal<int> poly(coef);
    std::string actual = poly.print();
    std::string expected = "2 + 2x^1 + 2x^2";
    EXPECT_EQ(expected, actual);
}

TEST(Polynomal2_Should, Return_Polynimal2){
    std::vector<int> coef (2, -2);
    polynomal<int> poly(coef);
    std::string actual = poly.print();
    std::string expected = "-2 -2x^1";
    EXPECT_EQ(expected, actual);
}

TEST(Polynomal3_Should, Return_Polynimal3){
    polynomal<int> poly;
    std::string actual = poly.print();
    std::string expected = "0";
    EXPECT_EQ(expected, actual);
}