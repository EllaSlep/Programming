#include <iostream>
#include <math.h>
#include <string>
#include <vector>

template <typename T>
class polynomal /*<T>*/{
    private:
    std :: vector <T> coef;
    
    public:
    //constructor
    polynomal(){
    }
    //copy constructor
    //template <typename T>
    polynomal(std :: vector <T> coefficents){
        for (int i = 0; i < coefficents.size(); ++i){
            this->coef.push_back(coefficents[i]);
        }
    }
    //get-set data
    //template <typename T>
    void set_coef(int i, T coefficent){
        this->coef[i] = coefficent;
    }
    unsigned get_max_degree() const{
        return this->coef.size();
    }
    float get_coef(int i) const{
        return this->coef[i];
    }
    //operators
    polynomal& operator=(const polynomal& poly){
        if (&poly == this)
            return *this;
        this->coef.clear();
        this->coef.resize(poly.get_max_degree());
        for (int i = 0; i < poly.get_max_degree(); ++i){
            this->set_coef(i, poly.get_coef(i));
        }
        return *this;
    }
    polynomal& operator+=(const polynomal& poly){ //некорректо присваивает при 0
        if (poly.get_max_degree() != 0){
            if (this->get_max_degree() < poly.get_max_degree()){
                this->coef.resize(poly.get_max_degree());
            }
            for (int i = 0; i < poly.get_max_degree(); ++i){
                float new_coef = this->get_coef(i) + poly.get_coef(i);
                this->set_coef(i, new_coef);
            }
            int flag = 0;
            for (int i = 0; i < this->get_max_degree(); ++i){
                if (this->get_coef(i) != 0){
                    flag = 1;
                }
            }
            if(!flag){
                this->coef.clear();
            }
        }
        return *this;
    }
    polynomal& operator-=(const polynomal& poly){ //некорректо присваивает при 0
        if (poly.get_max_degree() != 0){
            if (this->get_max_degree() < poly.get_max_degree()){
                this->coef.resize(poly.get_max_degree());
            }
            for (int i = 0; i < fmax(poly.get_max_degree(), this->get_max_degree()); ++i){
                float new_coef = this->get_coef(i) - poly.get_coef(i);
                this->set_coef(i, new_coef);
            }
            int flag = 0;
            for (int i = 0; i < this->get_max_degree(); ++i){
                if (this->get_coef(i) != 0){
                    flag = 1;
                }
            }
            if(!flag){
                this->coef.clear();
            }
        }
        return *this;
    }
    polynomal operator+(const polynomal& poly){
        polynomal rez;
        rez.coef.resize(fmax(this->get_max_degree(), poly.get_max_degree()));
        for (int i = 0; i < rez.get_max_degree(); ++i){
            float new_coef = this->get_coef(i) + poly.get_coef(i);
            rez.set_coef(i, new_coef);
        }
        return rez;
    }
    polynomal operator-(const polynomal& poly){
        polynomal rez;
        rez.coef.resize(fmax(this->get_max_degree(), poly.get_max_degree()));
        for (int i = 0; i < rez.get_max_degree(); ++i){
            float new_coef = this->get_coef(i) - poly.get_coef(i);
            rez.set_coef(i, new_coef);
        }
        return rez;
    }
    polynomal& operator-(){
        for (int i = 0; i < this->get_max_degree(); ++i){
            this->set_coef(i, - this->get_coef(i));
        }
        return *this;
    }
    //template <typename T>
    T operator[] (int i){
        return this->get_coef(i);
    }
    bool operator==(const polynomal& poly){
        return this->coef == poly.coef;
    }
    bool operator!=(const polynomal& poly){
        return !(this->coef == poly.coef);
    }
    polynomal& operator*=(const polynomal& poly){
        polynomal rez;
        if ((this->get_max_degree() != 0) && (poly.get_max_degree()) != 0){
            rez.coef.resize(poly.get_max_degree() + this->get_max_degree());
            for (int i = 0; i < this->get_max_degree(); ++i){
                if (this->get_coef(i) != 0){
                    for (int j = 0; j < poly.get_max_degree(); ++j){
                        if (poly.get_coef(j) != 0){
                            rez.set_coef(i + j, rez.get_coef(i + j) + (this->get_coef(i) * poly.get_coef(j)));
                        }
                    }
                }
            }
            int flag = 0;
            for (int i = 0; i < rez.get_max_degree(); ++i){
                if (rez.get_coef(i) != 0){
                    flag = 1;
                }
            }
            if(!flag){
                this->coef.clear();
                return *this;
            }
        }
        this->coef.clear();
        this->coef.resize(rez.get_max_degree());
        for(int i = 0; i < rez.get_max_degree(); ++i){
            this->set_coef(i, rez.get_coef(i));
        }
        return *this;
    }
    polynomal operator*(const polynomal& poly){
        polynomal rez;
        if ((this->get_max_degree() != 0) && (poly.get_max_degree()) != 0){
            rez.coef.resize(poly.get_max_degree() + this->get_max_degree());
            for (int i = 0; i < this->get_max_degree(); ++i){
                if (this->get_coef(i) != 0){
                    for (int j = 0; j < poly.get_max_degree(); ++j){
                        if (poly.get_coef(j) != 0){
                            rez.set_coef(i + j, rez.get_coef(i + j) + (this->get_coef(i) * poly.get_coef(j)));
                        }
                    }
                }
            }
        }
        return rez;
    }
    polynomal operator/(const float& del){
        polynomal rez;
        if (del != 0){
            rez.coef.resize(this->get_max_degree());
            for (int i = 0; i < this->get_max_degree(); ++i){
                rez.set_coef(i, this->get_coef(i) / del);
            }
        }
        return rez;
    }
    polynomal& operator/=(const float& del){
        polynomal rez;
        if (del != 0){
            rez.coef.resize(this->get_max_degree());
            for (int i = 0; i < this->get_max_degree(); ++i){
                rez.set_coef(i, this->get_coef(i) / del);
            }
            int flag = 0;
            for (int i = 0; i < rez.get_max_degree(); ++i){
                if (rez.get_coef(i) != 0){
                    flag = 1;
                }
            }
            if(!flag){
                this->coef.clear();
                return *this;
            }
        }
        this->coef.clear();
        this->coef.resize(rez.get_max_degree());
        for(int i = 0; i < rez.get_max_degree(); ++i){
            this->set_coef(i, rez.get_coef(i));
        }
        return *this;
    }
    //destructor
    ~polynomal(){
        coef.clear();
    }
};

template <typename T>
std :: istream& operator>> (std :: istream& stream, polynomal<T>& poly){
    std :: vector <T> coefficents;
    char number_string;
    stream >> number_string;
    while ((number_string != '\n')){
        coefficents.push_back(number_string - 'a' + 1);
        stream >> number_string;
    }
    poly = polynomal<float>(coefficents);
    return stream;
}

template <typename T>
std :: ostream& operator<< (std :: ostream& stream, const polynomal<T>& poly){
    if (poly.get_max_degree() != 0){
        int j = 0;
        while (poly.get_coef(j) == 0 && j < poly.get_max_degree()){
            ++j;
        }
        if (j == 0){
            stream << poly.get_coef(j);
            
        }else if(j == 1){
            stream << poly.get_coef(j) << "x";
        }
        else{
            stream << poly.get_coef(j) << "x^" << j;
        }
        for (int i = j + 1; i < poly.get_max_degree(); ++i){
            if (poly.get_coef(i) > 0){
                stream << " + " << poly.get_coef(i) << "x^" << i;
            }
            else if (poly.get_coef(i) < 0){
                stream << " " << poly.get_coef(i) << "x^" << i;
            }
        }
    }
    else
        stream << "0";
    return stream;
}