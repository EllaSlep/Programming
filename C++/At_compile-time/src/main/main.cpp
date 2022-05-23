#include <iostream>
#include <vector>
#include "src/lib/polynimal.hpp"

int main(){
    std::vector<int> coef (2, -2);
    polynomal<int> poly (coef);
    std::cout << poly << std::endl;

    return EXIT_SUCCESS;
}