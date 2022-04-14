#include <iostream>
#include <cmath>

#ifndef MAX
#define MAX 10000
#endif

template <typename T>
class buffer{
    private:
    int start_;
    int finish_;
    int array_size_;
    int size_;
    T buf_[MAX];

    public:
    void set_front_iter(const int& s){
        start_ = s;
    }

    void set_back_iter(const int& f){
        finish_ = f;
    }

    //template <typename T>
    void set_buf(const int& i, const T& value){
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

    //template <typename T>
    T get_buf(const int& i) const {
        return buf_[i];
    }

    //template <typename T>
    T front() const{
        return buf_[front_iter()];
    }

    //template <typename T>
    T back() const {
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

    //template <typename T>
    buffer(T buff[], const int& size){
        this->set_array_size(size);
        for (int i = 0; i < size; ++i){
            this->set_buf(i, buff[i]);
        }
        this->set_front_iter(0);
        this->set_back_iter(size - 1);
        this->set_size(size);
    }

    //template <typename T>
    void push_back(const T& value){
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

    //template <typename T>
    void push_front(const T & value){ 
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

    //template <typename T>
    const T operator[](int i){
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

template <typename T>
std::ostream& operator<< (std::ostream& stream, const buffer<T>& buff){
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