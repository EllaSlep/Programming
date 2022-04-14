#include <iostream>
#include <vector>
#include "Algo.hpp"

bool my_greater(int first, int second){
    return first > second ? first : second;
}

bool my_low(int first, int second){
    return !my_greater(first, second);
}

bool greater_1(int value){
    return value > 1 ? true : false;
}

bool less_1 (int value){
    return !greater_1(value);
}

bool greater_4(int value){
    return value > 4 ? true : false;
}

bool greater_5(int value){
    return value > 5 ? true : false;
}

bool less_4(int value){
    return value < 4 ? true : false;
}

bool less_5(int value){
    return value < 5 ? true : false;
}

int main(){
    std::vector<int> algo;
    algo.push_back(2);
    algo.push_back(3);
    algo.push_back(6);

    for (int i = 0; i < algo.size(); ++i){
        std::cout << algo[i] << " ";
    }

    std::cout << "\n\nall_of:\t\t" << my_all_of(algo.begin(), algo.end(), greater_1) << std::endl;
    std::cout << "all_of:\t\t" << my_all_of(algo.begin(), algo.end(), less_1) << std::endl;
    std::cout << "\n";

    std::cout << "any_of:\t\t" << my_any_of(algo.begin(), algo.end(), greater_4) << std::endl;
    std::cout << "any_of:\t\t" << my_any_of(algo.begin(), algo.end(), less_1) << std::endl;
    std::cout << "\n";

    std::cout << "none_of:\t" << my_none_of(algo.begin(), algo.end(), less_1) << std::endl;
    std::cout << "none_of:\t" << my_none_of(algo.begin(), algo.end(), greater_4) << std::endl;
    std::cout << "\n";

    std::cout << "one_of:\t\t" << my_one_of(algo.begin(), algo.end(), less_1) << std::endl;
    std::cout << "one_of:\t\t" << my_one_of(algo.begin(), algo.end(), greater_5) << std::endl;
    std::cout << "\n";

    std::cout << "is_sorted:\t" << my_is_sorted(algo.begin(), algo.end(), my_greater) << std::endl;
    std::cout << "is_sorted:\t" << my_is_sorted(algo.begin(), algo.end(), my_low) << std::endl;
    std::cout << "\n";

    std::cout << "is_partitioned:\t" << my_is_partitioned(algo.begin(), algo.end(), less_4) << std::endl;
    std::cout << "is_partitioned:\t" << my_is_partitioned(algo.begin(), algo.end(), greater_1) << std::endl;
    std::cout << "\n";

    std::cout << "find_not:\t" << *my_find_not(algo.begin(), algo.end(), 4) << std::endl;
    std::cout << "find_not:\t" << *my_find_not(algo.begin(), algo.end(), 2) << std::endl;
    std::cout << "\n";

    std::cout << "find_backward:\t" << *my_find_backward(algo.begin(), algo.end(), 2) << std::endl;
    std::cout << "find_backward:\t" << *my_find_backward(algo.begin(), algo.end(), 5) << std::endl;
    std::cout << "\n";

    std::cout << "is_palindrome:\t" << my_is_palindrome(algo.begin(), algo.end()) << std::endl;
    algo.push_back(3);
    algo.push_back(2);
    std::cout << "is_palindrome:\t" << my_is_palindrome(algo.begin(), algo.end()) << std::endl;
    std::cout << "\n";
}