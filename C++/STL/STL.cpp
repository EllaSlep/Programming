#include <iostream>
#include <cmath>
#define MAX 10000

class buffer{
    private:
    int start_;
    int finish_;
    int array_size_;
    int size_;
    int buf_[MAX];

    public:
    void set_start(const int& s){
        start_ = s;
    }

    void set_finish(const int& f){
        finish_ = f;
    }

    void set_buf(const int& i, const int& value){
        buf_[i] = value;
    }

    void set_size(int size){
        size_ = size;
    }

    void set_array_size(int size){// complite later
        if (size > get_array_size()){
            if (get_size() <= get_array_size() && get_start() < get_finish()){
                array_size_ = size;
            }
            else{
                array_size_ = size;
                if (get_finish() + get_size() < size){
                    for (int i = 0; i < get_finish(); ++i){
                        set_buf(get_size(), get_buf(i));
                        set_size(get_size() + 1);
                    }
                }
            }
        }
        else{
            if (get_start() < get_finish()){
                set_finish(get_finish() - size + 1);
                array_size_ = size;
                set_size(size);
            }
        }
    }

    int get_start() const {
        return start_;
    }

    int get_finish() const {
        return finish_;
    }

    int get_size() const {
        return size_;
    }

    int get_buf(const int& i) const {
        return buf_[i];
    }

    int get_begin() const{
        return buf_[get_start()];
    }

    int get_end() const {
        return buf_[get_finish()];
    }

    int get_array_size() const {
        return array_size_;
    }

    buffer(){
        this->set_start(0);
        this->set_finish(-1);
        this->set_size(0);
        this->set_array_size(5);
    }

    buffer(int buff[], const int& size){
        this->set_array_size(size);
        for (int i = 0; i < size; ++i){
            this->set_buf(i, buff[i]);
        }
        this->set_start(0);
        this->set_finish(size - 1);
        this->set_size(size);
    }

    void insert_end(const int& value){
        if (get_size() + 1 <= get_array_size()){ //without a curcle
            set_finish(get_finish() + 1);
            set_buf(get_finish(), value);
            set_size(get_size() + 1);
        }
        else{ // need to do a curcle
            set_finish(get_start());
            set_buf(get_finish(), value);
            set_start(get_start() + 1);
        }
    }

    void delete_end(){
        set_size(get_size() - 1);
        if (get_finish() - 1 >= 0)
            set_finish(get_finish() - 1);
        else
            set_finish(get_array_size() - 1);
    }

    void insert_begin(const int & value){ 
        if (get_size() + 1 <= get_array_size() && get_start() <= get_finish()){ //without curcle
            for (int i = get_finish() ; i >= get_start(); --i){
                set_buf(i + 1, get_buf(i));
            }
            set_finish(get_finish() + 1);
            set_buf(get_start(), value);
            set_size(get_size() + 1);
        }
        else { //with cucle
            int last = get_buf(get_array_size() - 1);
            for (int i  = get_array_size() - 1; i > 0; --i){
                set_buf(i + 1, get_buf(i));
            }
            set_buf(0, last);
            set_buf(get_start(), value);
        }
    }

    void delete_begin(){
        set_size(get_size() - 1);
        if (get_size() + 1 < get_array_size())
            set_start(get_start() + 1);
        else
            set_start(0);
    }

    const int operator[](int i){
        return get_buf(get_start() + i);
    }

    template <typename pred>
    bool all_of (int begin, int end, pred predicant){
        for (; begin != end; ++begin){
            if (begin == get_array_size())
                begin = 0;
            if (!predicant(get_buf(begin)))
                return false;
        }
        return true;
    }

    template <typename pred>
    bool any_of (int begin, int end, pred predicant){
        for (; begin != end; ++begin){
            if (begin == get_array_size())
                begin = 0;
            if (predicant(get_buf(begin)))
                return true;
        }
        return false;
    }

    template <typename pred>
    bool none_of (int begin, int end, pred predicant){
        for (; begin != end; ++begin){
            if (begin == get_array_size())
                begin = 0;
            if (predicant(get_buf(begin)))
                return false;
        }
        return true;
    }

    template <typename pred>
    bool one_of (int begin, int end, pred predicant){
        int count = 0;
        for (; begin != end; ++begin){
            if (begin == get_array_size())
                begin = 0;
            if (!predicant(get_buf(begin)))
                ++count;
        }
        if (count == 1)
            return true;
        else
            return false;
    }

    template <typename pred>
    bool is_sorted (int begin, int end, pred predicant){
        for (; begin != end; ++begin){
            if (begin == get_array_size())
                begin = 0;
            if (begin != get_array_size() - 1){
                if (!predicant(get_buf(begin), get_buf(begin + 1)))
                    return false;
            }
            else
                if (!predicant(get_buf(begin), get_buf(0)))
                    return false;
        }
        return true;
    }

    template <typename pred>
    bool is_partitioned (int begin, int end, pred predicant){
        int count = 0;
        int rez = predicant(get_buf(begin));
        for (; begin != end; ++begin){
            if (begin == get_array_size())
                begin = 0;
            if (rez != (predicant(get_buf(begin)))){
                ++count;
                rez = predicant(get_buf(begin));
            }
        }
        if (count == 1)
            return true;
        else
            return false;
    }

    template <typename pred>
    pred find_not (pred predicant){
        if (get_start() < get_finish())
            for (int i = get_start(); i <= get_finish(); ++i){
                if (get_buf(i) != predicant)
                    return i - get_start();
            }
        else{
            for (int i = get_start(); i < get_array_size(); ++i){
                if (get_buf(i) != predicant)
                    return i - get_start();
            }
            for (int i = 0; i <= get_finish(); ++i)
                if (get_buf(i) != predicant)
                    return get_array_size() - get_start() + i;
        }
        return -1;
    }

    template <typename pred>
    pred find_backward(pred predicant){
        if (get_finish() < get_start()){
            for (int i = get_finish(); i >= 0; --i){
                if (get_buf(i) == predicant)    
                    return get_array_size() - get_start() + i;
            }
            for (int i = get_array_size() - 1; i >= get_start(); --i)
                if (get_buf(i) == predicant)    
                    return i - get_start();
            return -1;
        }
        else{
            for (int i = get_finish(); i >= get_start(); --i)
                if (get_buf(i) == predicant)
                    return i - get_start();
            return -1;
        }
    }

    bool is_palindrome(int begin, int end){
        if (begin < end){
            for ( ; begin <= end; ++begin, --end){
                if (get_buf(begin) != get_buf(end))
                    return false;
            }
        }
        else{
            
        }
        return true;
    } 

};

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

std::ostream& operator<< (std::ostream& stream, const buffer& buff){
    if (buff.get_size() == 0){
        return stream;
    }
    else if(buff.get_size() == 1){
        stream << buff.get_buf(buff.get_finish());
    }
    else if (buff.get_size() <= buff.get_array_size() && buff.get_start() < buff.get_finish()){
        for (int i = buff.get_start(); i <= buff.get_finish(); ++ i){
            stream << buff.get_buf(i) << " ";
        }
    }
    else {
        for (int i = buff.get_start(); i < buff.get_array_size(); ++i){
            stream << buff.get_buf(i) << " ";
        }
        for (int i = 0; i <= buff.get_finish(); ++i){
            stream << buff.get_buf(i) << " ";
        }
    }
    return stream;
};

int main(){
    buffer buf;
    std::cout << buf << "size: " << buf.get_size() << std::endl;
    std::cout <<"\n---------- INSERT ----------\n";
    buf.insert_end(5);
    std::cout <<"buf.insert_end(5)\t" << buf << "\tsize: " << buf.get_size() << std::endl;
    buf.insert_begin(3);
    std::cout <<"buf.insert_begin(3)\t" << buf << "\tsize: " << buf.get_size() << std::endl;
    buf.insert_end(6);
    std::cout << "buf.insert_end(6)\t" << buf << "\tsize: " << buf.get_size() << std::endl;
    buf.insert_end(7);
    std::cout << "buf.insert_end(7)\t" << buf << "\tsize: " << buf.get_size() << std::endl;
    buf.insert_end(2);
    std::cout << "buf.insert_end(2)\t" << buf << "\tsize: " << buf.get_size() << std::endl;
    buf.insert_end(1);
    std::cout << "buf.insert_end(1)\t" << buf << "\tsize: " << buf.get_size() << std::endl;
    buf.insert_begin(7);
    std::cout << "buf.insert_begin(7)\t" << buf << "\tsize: " << buf.get_size() << std::endl;
    std::cout <<"\n---------- DELETE ----------\n";
    buf.delete_end();
    std::cout << "buf.delete_end()\t" << buf << "\tsize: " << buf.get_size() << std::endl;
    buf.delete_begin();
    std::cout << "buf.delete_begin()\t" << buf << "\tsize: " << buf.get_size() << std::endl;
    /* std::cout <<"\n---------- REIZE ----------\n";
    buf.set_array_size(6);
    std::cout << "buf.set_array_size(6)\t" << buf << "\tsize: " << buf.get_size() << std::endl;
    buf.set_array_size(2);
    std::cout << "buf.set_array_size(2)\t" << buf << "\tsize: " << buf.get_size() << std::endl; */
    std::cout <<"\n---------- OPERATOR[] ----------\n";
    std::cout << "buf[1]\t" << buf[1] << std::endl;
    std::cout <<"\n---------- ALGO ----------\n";
    std::cout << "buf.all_of(greater(4))\t" << buf.all_of(buf.get_start(), buf.get_finish(), greater_4) << std::endl;
    std::cout << "buf.all_of(greater(5))\t" << buf.all_of(buf.get_start(), buf.get_finish(), greater_5) << "\n" << std::endl;
    std::cout << "buf.any_of(less(4))\t" << buf.any_of(buf.get_start(), buf.get_finish(), less_4) << std::endl;
    std::cout << "buf.any_of(greater(5))\t" << buf.any_of(buf.get_start(), buf.get_finish(), greater_5) << "\n" << std::endl;
    std::cout << "buf.none_of(greater(5))\t" << buf.none_of(buf.get_start(), buf.get_finish(), greater_5) << std::endl;
    std::cout << "buf.none_of(less(4))\t" << buf.none_of(buf.get_start(), buf.get_finish(), less_4) << "\n" << std::endl;
    std::cout << "buf.one_of(greater(5))\t" << buf.one_of(buf.get_start(), buf.get_finish(), greater_5) << std::endl;
    std::cout << "buf.one_of(less(4))\t" << buf.one_of(buf.get_start(), buf.get_finish(), less_4) << "\n" << std::endl;
    std::cout << "buf.find_not(4)\t\t" << buf.find_not(4) << std::endl;
    std::cout << "buf.find_not(5)\t\t" << buf.find_not(5) << "\n" << std::endl;
    buf.insert_end(5);
    std::cout << "buf.find_backward(5)\t" << buf.find_backward(5) << std::endl;
    std::cout << "buf.find_backward(4)\t" << buf.find_backward(4) << std::endl;
    buf.delete_end();
    std::cout << "buf.find_backward(5)\t" << buf.find_backward(5) << "\n" << std::endl;
    std::cout << "buf.is_sorted(greater)\t" << buf.is_sorted(buf.get_start(), buf.get_finish(), my_greater) << std::endl;
    std::cout << "buf.is_sorted(low)\t" << buf.is_sorted(buf.get_start(), buf.get_finish(), my_low) << "\n" << std::endl;
    buf.insert_begin(4);
    std::cout <<"buf.insert_begin(4)\t" << buf << "\tsize: " << buf.get_size() << std::endl;
    std::cout << "buf.is_partitioned(greater_5)\t" << buf.is_partitioned(buf.get_start(), buf.get_finish(), greater_5) << std::endl;
    std::cout << "buf.is_partitioned(low_4)\t" << buf.is_partitioned(buf.get_start(), buf.get_finish(), less_4) << "\n" << std::endl;
    buf.delete_begin();
    buf.delete_end();
    buf.insert_end(5);
    std::cout <<"buf.insert_end(4)\t" << buf << "\tsize: " << buf.get_size() << std::endl;
    std::cout << "buf.is_palindrome()\t" << buf.is_palindrome(buf.get_start(), buf.get_finish()) << "\n" << std::endl;
    buf.delete_end();
    std::cout <<"buf.delete_end()\t" << buf << "\tsize: " << buf.get_size() << std::endl;
    std::cout << "buf.is_palindrome()\t" << buf.is_palindrome(buf.get_start(), buf.get_finish()) << "\n" << std::endl;
}