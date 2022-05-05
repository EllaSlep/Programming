#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include "cube.hpp"

// 1 - white, 2 - yellow, 3 - pink, 4 - green, 5 - orange, 6 - blue

int main(){
    std::string rotations, str;
    std::cout << "\n\n";
    
    int front[3][3] = {{6, 6, 6}, {6, 6, 6}, {6, 6, 6}};
    int back[3][3] = {{4, 4, 4}, {4, 4, 4}, {4, 4, 4}};
    int right[3][3] = {{3, 3, 3}, {3, 3, 3}, {3, 3, 3}};
    int left[3][3] = {{5, 5, 5}, {5, 5, 5}, {5, 5, 5}};
    int up[3][3] = {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}};
    int down[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};

    cube cub(front, back, right, left, up, down);
    std::cout << cub << "\n\n";
    
    cub.read(rotations, "cube.txt");
    std::cout << cub << "\n\n";

    /* cub.cube_disassembling();
    std::cout << cub << "\n\n"; */
    /* cub.cube_assembling();
    std::cout << cub << "\n\n"; */
}