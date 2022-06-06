#include <iostream>
#include <vector>
#include <list>
#include <cstdarg>
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

    my_alloc() = default;

    my_alloc(unsigned int count, ...){
        va_list ap;
        va_start (ap, count);
        for (int i = 0; i < count; ++i){
            block temp_block;
            temp_block.size_ = va_arg(ap, unsigned int);
            temp_block.pointer_ = malloc(sizeof(value_type) * temp_block.size_);
        }
        va_end(ap);
        std::cout << "\nAllocate";
    }

    my_alloc(const my_alloc& other_alloc){
        for (auto& i : other_alloc.mem_blocks){
            block temp_block;
            temp_block.pointer_ = i.pointer_;
            temp_block.size_ = i.size_;
            temp_block.used_ = i.used_;
            this->mem_blocks.push_back(temp_block);
        }
    }

    pointer allocate (size_type size){ // тут нужно что-то придуать с итераторами и блоками...
        block i = mem_blocks.begin();
        while (i != mem_blocks.end() && i.size_ < size){
            ++i;
        }
        if (i == mem_blocks.end() && i.size_ < size){
            throw std::bad_alloc();
        }
        while (i != mem_blocks.end() && i.used_ == true){
            ++i;
        }
        if (i == mem_blocks.end() && i.used_ == true){
            throw std::bad_alloc();
        }
        i.used_ = true;
        return i.pointer_;
    }

    void deallocate(pointer p, size_type n){ // тут нужно что-то придуать с итераторами и блоками...
        block i = mem_blocks.begin();
        while (i != mem_blocks.end() && i.pointer_ != p){
            ++i;
        }
        i.used_ = false;
        std::cout << "\nDeallocate";
    }
};

int main(){
    //my_alloc<int> Allocator(2, 2, 4, 8);
    std::vector<int, my_alloc<int> > vec(2);
}