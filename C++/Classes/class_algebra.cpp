#include <iostream>
#include <math.h>
#include <string>
#include <vector>

class polynomial{
    public:
    std :: vector <std :: string> data;
    // constructor
    polynomial(std :: string str = "\0"){
        str.append("+");
        while (!str.empty()){
            int pos1 = str.find("+", 0), pos2 = str.find("-", 0);
            if (pos1 == -1){
                pos1 = pos2 + 1;
            }
            if (pos2 == -1){
                pos2 = pos1 + 1;
            } 
            if (pos1 < pos2){
                data.push_back(str.substr(0, pos1));
                str.erase(0, pos1 + 1);
                data.push_back("+");
            }
            else if (pos1 > pos2){
                data.push_back(str.substr(0, pos2));
                str.erase(0, pos2 + 1);
                data.push_back("-");
            }
            else if (pos1 == pos2){
                data.push_back(str.substr(0, str.length()));
                str.erase(0, str.length());
            }
            pos1 = pos2 = -1;
        }
        data.pop_back();
    }
    //copy constructor
    polynomial(const polynomial& poly){
        for(int i = 0; i < poly.data.size(); i++){
            data.push_back(poly.data[i]);
        }
    }
    //operator =
    polynomial& operator=(const polynomial& poly){
        if (&poly == this)
            return *this;
        if (this != nullptr)
            this->data.clear();
        for (int i = 0; i < poly.data.size(); i++){
            this->data.push_back(poly.data[i]);
        }
        return *this;
    }
    //operators +=, -=
    polynomial& operator+=(const polynomial& poly){
        this->data.push_back("+");
        for (int i = 0; i < poly.data.size(); i++){
            this->data.push_back(poly.data[i]);
        }
        return *this;
    }
    polynomial& operator-=(const polynomial& poly){
        this->data.push_back("-");
        for (int i = 0; i < poly.data.size(); i++){
            if (poly.data[i] == "+"){
                this->data.push_back("-");
            }
            else if (poly.data[i] == "-"){
                this->data.push_back("+");
            }
            else{
                this->data.push_back(poly.data[i]);
            }
        }
        return *this;
    }
    polynomial& operator+(const polynomial& poly_a){
        this->data.push_back("+");
        for (int i = 0; i < poly_a.data.size(); i++){
            this->data.push_back(poly_a.data[i]);
        }
        return *this;
    }
    polynomial& operator-(const polynomial& poly_b){
        this->data.push_back("-");
        for (int i = 0; i < poly_b.data.size(); i++){
            if (poly_b.data[i] == "+"){
                this->data.push_back("-");
            }
            else if (poly_b.data[i] == "-"){
                this->data.push_back("+");
            }
            else{
                this->data.push_back(poly_b.data[i]);
            }
        }
        return *this;
    }
    //bool
    //
    /* void with_letters(){
        for (int i = 0; i < data.size(); i++){
            for (int j = 0; j < data[i].length(); j++){
                if (data[i][j] >= 'a' && data[i][j] <= 'z'){
                    std :: string str1;
                    str1.assign(data[i], j, data[i].length() - j);
                    data.insert(i + 1, str1.length(), str1);
                    data[i].erase(j, data[i].length());
                }
            }
        }
    } */
    //
    ~polynomial()
    {}
};

int main (){
    std :: string str = "2+3-1";
    std :: cout << str << std :: endl;
    polynomial poly(str);
    for (int i = 0; i < poly.data.size(); i++){
        std :: cout << poly.data[i] << " ";
    }
    std :: cout << "\n" << std :: endl;

    std :: string str2 = "2-3+1";
    std :: cout << str2 <<std :: endl;
    polynomial poly2(str2);
    for (int i = 0; i < poly2.data.size(); i++){
        std :: cout << poly2.data[i] << " ";
    }
    std :: cout << "\n" << std :: endl;
    std :: cout << "operator+" << std :: endl;
    polynomial poly4;
    poly4 = poly2 + poly;
    for (int i = 0; i < poly4.data.size(); i++){
        std :: cout << poly4.data[i] << " ";
    }
    std :: cout << "\n" << std :: endl;
    std :: cout << "operator-" << std :: endl;
    poly4 = poly2 - poly;
    for (int i = 0; i < poly4.data.size(); i++){
        std :: cout << poly4.data[i] << " ";
    }
    std :: cout << "\n" << std :: endl;
    /* std :: string str3 = "2a-3b+c";
    std :: cout << str3 << std :: endl;
    polynomial poly3(str3);
    for (int i = 0; i < poly3.data.size(); i++){
        std :: cout << poly3.data[i] << " ";
    }
    std :: cout << "\n" << std :: endl;
    poly3 += poly;
    for (int i = 0; i < poly3.data.size(); i++){
        std :: cout << poly3.data[i] << " ";
    }
    std :: cout << "\n" << std :: endl;
    poly3 -= poly2;
    for (int i = 0; i < poly3.data.size(); i++){
        std :: cout << poly3.data[i] << " ";
    }
    std :: cout << "\n" << std :: endl; */
}