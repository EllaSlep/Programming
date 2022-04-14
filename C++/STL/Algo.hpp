#include <iostream>

template <typename iterator, typename pred>
bool my_all_of(iterator begin, iterator end, pred predicant){
    for (; begin != end; ++begin){
            if (!predicant(*begin))
                return false;
        }
        return true;
}

template <typename iterator, typename pred>
    bool my_any_of (iterator begin, iterator end, pred predicant){
        for (; begin != end; ++begin){
            if (predicant(*begin))
                return true;
        }
        return false;
    }

    template <typename iterator, typename pred>
    bool my_none_of (iterator begin, iterator end, pred predicant){
        for (; begin != end; ++begin){
            if (predicant(*begin))
                return false;
        }
        return true;
    }

    template <typename iterator, typename pred>
    bool my_one_of (iterator begin, iterator end, pred predicant){
        int count = 0;
        for (; begin != end; ++begin){
            if (predicant(*begin))
                ++count;
        }
        if (count == 1)
            return true;
        else
            return false;
    }

    template <typename iterator, typename pred>
    bool my_is_sorted (iterator begin, iterator end, pred predicant){
        for (; begin != end; ++begin){
            if (!predicant(*begin, *(begin + 1)))
                    return false;
        }
        return true;
    }

    template <typename iterator, typename pred>
    bool my_is_partitioned (iterator begin, iterator end, pred predicant){
        int count = 0;
        int rez = predicant(*(begin));
        for (; begin != end; ++begin){
            if (rez != (predicant(*(begin)))){
                ++count;
                rez = predicant(*(begin));
            }
        }
        if (count == 1)
            return true;
        else
            return false;
    }

    template <typename iterator, typename pred>
    iterator my_find_not (iterator begin, iterator end, pred predicant){
        for ( ; begin != end; ++begin){
            if (*(begin) != predicant)
                return begin;
        }
        return end + 1;
    }

    template <typename iterator, typename pred>
    iterator my_find_backward(iterator begin, iterator end, pred predicant){
        for ( ; end != begin; --end)
            if (*(end) == predicant)
                return end;
        return begin - 1;
    }

    template <typename iterator>
    bool my_is_palindrome(iterator begin, iterator end){
        for ( ; begin != end; ++begin, --end){
            if (*(begin) != *(end))
                return false;
        }
        return true;
    } 