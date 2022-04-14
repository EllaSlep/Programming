#include <iostream>
#include "STL.hpp"

bool my_greater(int first, int second){
    return first > second ? first : second;
}

bool my_low(int first, int second){
    return !my_greater(first, second);
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
    buffer<int> buf;
    std::cout <<"\n---------- INSERT ----------\n";
    std::cout << buf << "size: " << buf.size() << std::endl;
    buf.push_back(5);
    std::cout <<"buf.push_back(5)\t" << buf << "\tsize: " << buf.size() << std::endl;
    buf.push_front(3);
    std::cout <<"buf.push_front(3)\t" << buf << "\tsize: " << buf.size() << std::endl;
    buf.push_back(6);
    std::cout << "buf.push_back(6)\t" << buf << "\tsize: " << buf.size() << std::endl;
    buf.push_back(7);
    std::cout << "buf.push_back(7)\t" << buf << "\tsize: " << buf.size() << std::endl;
    buf.push_back(2);
    std::cout << "\nbuf.push_back(2)\t" << buf << "\tsize: " << buf.size() << std::endl;

    std::cout << "In memory:\t\t";
    for (int i  = 0; i < buf.size(); ++i){
        std::cout << buf[i] << " ";
    }
    std::cout << std::endl;

    buf.push_back(1);
    std::cout << "\nbuf.push_back(1)\t" << buf << "\tsize: " << buf.size() << std::endl;

    std::cout << "In memory:\t\t";
    for (int i  = 0; i < buf.size(); ++i){
        std::cout << buf.get_buf(i) << " ";
    }
    std::cout << std::endl;

    buf.push_front(7);
    std::cout << "\nbuf.push_front(7)\t" << buf << "\tsize: " << buf.size() << std::endl;

    std::cout << "In memory:\t\t";
    for (int i  = 0; i < buf.size(); ++i){
        std::cout << buf[i] << " ";
    }
    std::cout << std::endl;

    std::cout <<"\n---------- DELETE ----------\n";
    buf.pop_back();
    std::cout << "buf.pop_back()\t" << buf << "\tsize: " << buf.size() << std::endl;

    std::cout << "In memory:\t";
    for (int i  = 0; i < buf.size(); ++i){
        std::cout << buf[i] << " ";
    }
    std::cout << std::endl;

    buf.pop_front();
    std::cout << "\nbuf.pop_front()\t" << buf << "\tsize: " << buf.size() << std::endl;

    std::cout << "In memory:\t";
    for (int i  = 0; i < buf.size(); ++i){
        std::cout << buf[i] << " ";
    }
    std::cout << std::endl;

    std::cout <<"\n---------- OPERATOR[] ----------\n";
    std::cout << "buf[1]\t" << buf[1] << std::endl;

    std::cout <<"\n---------- ALGO ----------\n";
    std::cout << "buf.all_of(greater(4))\t" << buf.all_of(buf.front_iter(), buf.back_iter(), greater_4) << std::endl;
    std::cout << "buf.all_of(greater(5))\t" << buf.all_of(buf.front_iter(), buf.back_iter(), greater_5) << "\n" << std::endl;
    std::cout << "buf.any_of(less(4))\t" << buf.any_of(buf.front_iter(), buf.back_iter(), less_4) << std::endl;
    std::cout << "buf.any_of(greater(5))\t" << buf.any_of(buf.front_iter(), buf.back_iter(), greater_5) << "\n" << std::endl;
    std::cout << "buf.none_of(greater(5))\t" << buf.none_of(buf.front_iter(), buf.back_iter(), greater_5) << std::endl;
    std::cout << "buf.none_of(less(4))\t" << buf.none_of(buf.front_iter(), buf.back_iter(), less_4) << "\n" << std::endl;
    std::cout << "buf.one_of(greater(5))\t" << buf.one_of(buf.front_iter(), buf.back_iter(), greater_5) << std::endl;
    std::cout << "buf.one_of(less(4))\t" << buf.one_of(buf.front_iter(), buf.back_iter(), less_4) << "\n" << std::endl;
    std::cout << "buf.find_not(4)\t\t" << buf.find_not(4) << std::endl;
    std::cout << "buf.find_not(5)\t\t" << buf.find_not(5) << "\n" << std::endl;
    buf.push_back(5);
    std::cout << "buf.find_backward(5)\t" << buf.find_backward(5) << std::endl;
    std::cout << "buf.find_backward(4)\t" << buf.find_backward(4) << std::endl;
    buf.pop_back();
    std::cout << "buf.find_backward(5)\t" << buf.find_backward(5) << "\n" << std::endl;
    std::cout << "buf.is_sorted(greater)\t" << buf.is_sorted(buf.front_iter(), buf.back_iter(), my_greater) << std::endl;
    std::cout << "buf.is_sorted(low)\t" << buf.is_sorted(buf.front_iter(), buf.back_iter(), my_low) << "\n" << std::endl;
    buf.push_front(4);
    std::cout <<"buf.push_front(4)\t" << buf << "\tsize: " << buf.size() << std::endl;
    std::cout << "buf.is_partitioned(greater_5)\t" << buf.is_partitioned(buf.front_iter(), buf.back_iter(), greater_5) << std::endl;
    std::cout << "buf.is_partitioned(low_4)\t" << buf.is_partitioned(buf.front_iter(), buf.back_iter(), less_4) << "\n" << std::endl;
    buf.pop_front();
    buf.pop_back();
    buf.push_back(5);
    std::cout <<"buf.push_back(5)\t" << buf << "\tsize: " << buf.size() << std::endl;
    std::cout << "buf.is_palindrome()\t" << buf.is_palindrome(buf.front_iter(), buf.back_iter()) << "\n" << std::endl;
    buf.pop_back();
    std::cout <<"buf.pop_back()\t" << buf << "\tsize: " << buf.size() << std::endl;
    std::cout << "buf.is_palindrome()\t" << buf.is_palindrome(buf.front_iter(), buf.back_iter()) << "\n" << std::endl;

    std::cout <<"\n---------- REIZE ----------\n";
    buf.set_array_size(6);
    std::cout << "buf.set_array_size(6)\t" << buf << "\tsize: " << buf.size() << std::endl;

    std::cout << "In memory:\t\t";
    for (int i  = 0; i < buf.size(); ++i){
        std::cout << buf[i] << " ";
    }
    std::cout << std::endl;

    buf.set_array_size(2);
    std::cout << "\nbuf.set_array_size(2)\t" << buf << "\tsize: " << buf.size() << std::endl;

    std::cout << "In memory:\t\t";
    for (int i  = 0; i < buf.size(); ++i){
        std::cout << buf[i] << " ";
    }
    std::cout << std::endl;
}