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
    void set_front_iter(const int& s){
        start_ = s;
    }

    void set_back_iter(const int& f){
        finish_ = f;
    }

    void set_buf(const int& i, const int& value){
        buf_[i] = value;
    }

    void set_size(int size){
        size_ = size;
    }

    void set_array_size(int n){
        if (n > get_array_size()){
            if (size() <= get_array_size() && front_iter() < back_iter()){
                array_size_ = n;
            }
            else{
                array_size_ = n;
                if (back_iter() + size() < n){
                    for (int i = 0; i < back_iter(); ++i){
                        set_buf(size(), get_buf(i));
                        set_size(size() + 1);
                    }
                }
            }
        }
        else{
            if (front_iter() + n < get_array_size()){
                set_back_iter(front_iter() + n - 1);
                array_size_ = n;
                set_size(n);
            }
            else{
                if (back_iter() - (get_array_size() - n) >= 0)
                    set_back_iter(back_iter() - get_array_size() - 1 + n);
                else
                    set_back_iter(get_array_size() - 1 - (back_iter() - n));
                array_size_ = n;
                set_size(n);
            }
        }
    }

    int front_iter() const {
        return start_;
    }

    int back_iter() const {
        return finish_;
    }

    int size() const {
        return size_;
    }

    int get_buf(const int& i) const {
        return buf_[i];
    }

    int front() const{
        return buf_[front_iter()];
    }

    int back() const {
        return buf_[back_iter()];
    }

    int get_array_size() const {
        return array_size_;
    }

    buffer(){
        this->set_front_iter(0);
        this->set_back_iter(-1);
        this->set_size(0);
        this->set_array_size(5);
    }

    buffer(int buff[], const int& size){
        this->set_array_size(size);
        for (int i = 0; i < size; ++i){
            this->set_buf(i, buff[i]);
        }
        this->set_front_iter(0);
        this->set_back_iter(size - 1);
        this->set_size(size);
    }

    void push_back(const int& value){
        if (size() + 1 <= get_array_size()){ //without a curcle
            set_back_iter(back_iter() + 1);
            set_buf(back_iter(), value);
            set_size(size() + 1);
        }
        else{ // need to do a curcle
            set_back_iter(front_iter());
            set_buf(back_iter(), value);
            set_front_iter(front_iter() + 1);
        }
    }

    void pop_back(){
        set_size(size() - 1);
        if (back_iter() - 1 >= 0)
            set_back_iter(back_iter() - 1);
        else
            set_back_iter(get_array_size() - 1);
    }

    void push_front(const int & value){ 
        if (size() + 1 <= get_array_size() && front_iter() <= back_iter()){ //without curcle
            for (int i = back_iter() ; i >= front_iter(); --i){
                set_buf(i + 1, get_buf(i));
            }
            set_back_iter(back_iter() + 1);
            set_buf(front_iter(), value);
            set_size(size() + 1);
        }
        else { //with cucle
            int last = get_buf(get_array_size() - 1);
            for (int i  = get_array_size() - 1; i > 0; --i){
                set_buf(i + 1, get_buf(i));
            }
            set_buf(0, last);
            set_buf(front_iter(), value);
        }
    }

    void pop_front(){
        set_size(size() - 1);
        if (size() + 1 < get_array_size())
            set_front_iter(front_iter() + 1);
        else
            set_front_iter(0);
    }

    const int operator[](int i){
        return get_buf(front_iter() + i);
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
        if (front_iter() < back_iter())
            for (int i = front_iter(); i <= back_iter(); ++i){
                if (get_buf(i) != predicant)
                    return i - front_iter();
            }
        else{
            for (int i = front_iter(); i < get_array_size(); ++i){
                if (get_buf(i) != predicant)
                    return i - front_iter();
            }
            for (int i = 0; i <= back_iter(); ++i)
                if (get_buf(i) != predicant)
                    return get_array_size() - front_iter() + i;
        }
        return -1;
    }

    template <typename pred>
    pred find_backward(pred predicant){
        if (back_iter() < front_iter()){
            for (int i = back_iter(); i >= 0; --i){
                if (get_buf(i) == predicant)    
                    return get_array_size() - front_iter() + i;
            }
            for (int i = get_array_size() - 1; i >= front_iter(); --i)
                if (get_buf(i) == predicant)    
                    return i - front_iter();
            return -1;
        }
        else{
            for (int i = back_iter(); i >= front_iter(); --i)
                if (get_buf(i) == predicant)
                    return i - front_iter();
            return -1;
        }
    }

    bool is_palindrome(int begin, int end){
        for ( ; begin != end; ++begin, --end){
            if (begin == get_array_size())
                begin = 0;
            if (end == -1)
                end = get_array_size() - 1;
            if (get_buf(begin) != get_buf(end))
                return false;
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
    if (buff.size() == 0){
        return stream;
    }
    else if(buff.size() == 1){
        stream << buff.get_buf(buff.back_iter());
    }
    else if (buff.size() <= buff.get_array_size() && buff.front_iter() < buff.back_iter()){
        for (int i = buff.front_iter(); i <= buff.back_iter(); ++ i){
            stream << buff.get_buf(i) << " ";
        }
    }
    else {
        for (int i = buff.front_iter(); i < buff.get_array_size(); ++i){
            stream << buff.get_buf(i) << " ";
        }
        for (int i = 0; i <= buff.back_iter(); ++i){
            stream << buff.get_buf(i) << " ";
        }
    }
    return stream;
};

int main(){
    buffer buf;
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