#include <iostream>
#include <vector>
#include <math.h>
#include "polynimal.hpp"

int main(){
    std::vector<int> coef;
    coef.push_back(3);
    coef.push_back(2);
    coef.push_back(1);

    polynomal <int> poly(coef);
    std::cout << poly << std::endl;
}