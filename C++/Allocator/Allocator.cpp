#include <iostream>
#include <vector>
#include <list>
#include <cstdarg>
#include <iterator>
#include <ctime>
#include <ratio>
#include <chrono>
#include <exception>

template <typename T>
class my_alloc{
private:
    struct block{
        bool used_ = false;
        T* pointer_;
        unsigned int size_;
    };
    std::list<block> mem_blocks;

public:
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T value_type;

    my_alloc(){
        block temp_block;
        temp_block.size_ = 8;
        temp_block.pointer_ = (pointer)malloc(sizeof(value_type) * temp_block.size_);
        if (temp_block.pointer_ == nullptr){
            throw std::bad_alloc();
        }
        mem_blocks.push_back(temp_block);
        
        temp_block.size_ = 4;
        temp_block.pointer_ = (pointer)malloc(sizeof(value_type) * temp_block.size_);
        if (temp_block.pointer_ == nullptr){
            throw std::bad_alloc();
        }
        mem_blocks.push_back(temp_block);

        temp_block.size_ = 8;
        temp_block.pointer_ = (pointer)malloc(sizeof(value_type) * temp_block.size_);
        if (temp_block.pointer_ == nullptr){
            throw std::bad_alloc();
        }
        mem_blocks.push_back(temp_block);
        std::cout << "\nCreate";
    }

    my_alloc(unsigned int count, ...){
        va_list ap;
        va_start (ap, count);
        for (int i = 0; i < count; ++i){
            block temp_block;
            temp_block.size_ = va_arg(ap, unsigned int);
            temp_block.pointer_ = (pointer)malloc(sizeof(value_type) * temp_block.size_);
            if (temp_block.pointer_ == nullptr){
                throw std::bad_alloc();
            }
            mem_blocks.push_back(temp_block);
        }
        va_end(ap);
        std::cout << "\nCreate";
    }

    my_alloc(const my_alloc& other_alloc){
        for (auto& i : other_alloc.mem_blocks){
            block temp_block;
            temp_block.pointer_ = i.pointer_;
            temp_block.size_ = i.size_;
            temp_block.used_ = i.used_;
            this->mem_blocks.push_back(temp_block);
        }
        std::cout << "\nCreate";
    }

    pointer allocate (size_type size){ 
        typename std::list<block>::iterator i = mem_blocks.begin();
        while (i != mem_blocks.end() && (*i).size_ < size){
            ++i;
        }
        if (i == mem_blocks.end()){
            throw std::bad_alloc();
        }
        while (i != mem_blocks.end() && (*i).used_ == true){
            ++i;
        }
        if (i == mem_blocks.end() && (*i).used_ == true){
            throw std::bad_alloc();
        }
        (*i).used_ = true;
        std::cout << "\nAllocate";
        return (*i).pointer_;
    }

    void deallocate(pointer p, size_type n){ 
        typename std::list<block>::iterator i = mem_blocks.begin();
        while (i != mem_blocks.end() && (*i).pointer_ != p){
            ++i;
        }
        (*i).used_ = false;
        std::cout << "\nDeallocate";
    }
};

int main(){
    //auto start = std::chrono::high_resolution_clock::now();
    //my_alloc<int> Allocator(2, 2, 4, 8);
    std::vector<int, my_alloc<int> > vec(2, 4);
    std::cout << "\n";
    std::cout << "\n" << vec[0];
    std::cout << "\n" << vec[1];
    std::cout << "\n";

    vec.resize(5);
    std::cout << "\n";
    std::cout << "\n" << vec[0];
    std::cout << "\n" << vec[1];
    std::cout << "\n";

    //auto end = std::chrono::high_resolution_clock::now();
    //std::chrono::duration<float> duration = end - start;
    //std::cout << "\n" << duration.count() << "s\n";
}