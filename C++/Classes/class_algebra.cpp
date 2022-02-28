#include <iostream>
#include <math.h>
#include <string>
#include <vector>

class polynomal{
    private:
    std :: vector <float> coef;
    
    public:
    //constructor
    polynomal(){
    }
    //copy constructor
    polynomal(std :: vector <float> coefficents){
        for (int i = 0; i < coefficents.size(); ++i){
            this->coef.push_back(coefficents[i]);
        }
    }
    //get-set data
    void set_coef(int i, float coefficent){
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
    float operator[] (int i){
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

std :: istream& operator>> (std :: istream& stream, polynomal& poly){
    std :: vector <float> coefficents;
    char number_string[10];
    stream >> number_string;
    while (!strcmp(number_string, "\n")){
        coefficents.push_back(atof(number_string));
        stream >> number_string;
    }
    poly = polynomal(coefficents);
    return stream;
}
std :: ostream& operator<< (std :: ostream& stream, const polynomal& poly){
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
                stream << "+" << poly.get_coef(i) << "x^" << i;
            }
            else if (poly.get_coef(i) < 0){
                stream << poly.get_coef(i) << "x^" << i;
            }
        }
    }
    else
        stream << "0";
    return stream;
}

int main(){
    std :: vector <float> coefficents;
    coefficents.push_back(0);
    coefficents.push_back(1);
    coefficents.push_back(-2);
    coefficents.push_back(3);

    polynomal poly(coefficents);
    polynomal poly2;

    std :: cout << "\nприсваивание\t\t\t" << "poly:\t\t" << poly << "\tpoly2: \t\t"<< poly2 << std :: endl;
    poly2 = poly;
    std :: cout << "\nоператор =\t\t\t" << "new poly2: \t" << poly2 << std :: endl;
    std :: cout << "\nравенство 1 и 2\t\t\t" << "poly ? poly2\t" << (poly == poly2) << std :: endl;
    std :: cout << "\nнеравенство 1 и 2\t\t" << "poly ? poly2\t" << (poly != poly2) << std :: endl;

    poly2 += poly;
    std :: cout << "\nоператор +=\t\t\t" << "poly2: \t\t" << poly2 << "\tpoly:\t\t" << poly << std :: endl;
    std :: cout << "\nравенство 1 и 2\t\t\t" << "poly ? poly2\t" << (poly == poly2) << std :: endl;
    std :: cout << "\nнеравенство 1 и 2\t\t" << "poly ? poly2\t" << (poly != poly2) << std :: endl;
    std :: cout << "\nоператор []\t\t\t" << "poly2[2]: \t\t" << poly2[2] << std :: endl;

    polynomal poly3;
    poly3 += poly;
    std :: cout << "\nоператор +=\t\t\t" << "poly3: \t\t" << poly3 << std :: endl;
    poly3 -= poly;
    std :: cout << "\nоператор -=\t\t\t" << "poly3: \t\t" << poly3 << std :: endl;

    polynomal poly4;
    poly4 = poly2 + poly;
    std :: cout << "\nоператор +\t\t\t" << "poly4: \t\t" << poly4 << "\tpoly2: \t\t" << poly2 << "\tpoly:\t\t" << poly << std :: endl;

    std :: cout << "\nоператор -\t\t\t" << "poly2:\t\t" << poly2;
    poly2 = - poly2;
    std :: cout <<"\t- poly2:\t" << poly2 << std :: endl;

    std :: vector <float> coefficents2;
    coefficents2.push_back(0);
    polynomal poly5(coefficents2);
    std :: cout << "\nопертор *=\t\t\t" << "poly: \t\t" << poly << "\tpoly5: \t\t" << poly5;
    poly5 *= poly;
    std :: cout << "\t\t\t new poly5: \t\t" << poly5 << std :: endl;

    polynomal poly6;
    poly6 = poly5 * poly;
    std :: cout << "\nоператор *\t\t\t" << "poly6:\t\t" << poly6 << "\tpoly5:\t\t" << poly5 << "\tpoly\t\t" << poly << std :: endl;

    poly5 = poly5 / 4.0;
    std :: cout << "\nоператор /\t\t\t" << "poly5:\t\t" << poly5 << std :: endl;
    
    poly6 /= 4.0;
    std :: cout << "\nоператор /=\t\t\t" << "poly6:\t\t" << poly6 << std :: endl;
    std :: cout << "\nDONE" << std :: endl;
}