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
            coef.push_back(coefficents[i]);
        }
    }
    //get-set data
    void set_coef(int i, float coefficent){
        this->coef[i] = coefficent;
    }
    unsigned get_max_degree() const{
        return coef.size();
    }
    float get_coef(int i) const{
        return coef[i];
    }
    //operators
    polynomal& operator=(const polynomal& poly){
        if (&poly == this)
            return *this;
        this->coef.clear();
        for (int i = 0; i < poly.get_max_degree(); ++i){
            this->coef.push_back(poly.get_coef(i));
        }
        return *this;
    }
    polynomal& operator+=(const polynomal& poly){ //некорректо присваивает при 0
        if (poly.get_max_degree() != 0){
            if (this->get_max_degree() < poly.get_max_degree()){
                this->coef.resize(poly.get_max_degree());
            }
            for (int i = 0; i < poly.get_max_degree(); ++i){
                float coef = this->get_coef(i);
                float new_coef = coef + poly.get_coef(i);
                this->set_coef(i, new_coef);
            }
        }
        return *this;
    }
    polynomal& operator-=(const polynomal& poly){ //некорректо присваивает при 0
        if (poly.get_max_degree() != 0){
            if (this->get_max_degree() < poly.get_max_degree()){
                this->coef.resize(poly.get_max_degree());
            }
            for (int i = 0; i < poly.get_max_degree(); ++i){
                float new_coef = this->get_coef(i) - poly.get_coef(i);
                this->set_coef(i, new_coef);
            }
        }
        return *this;
    }
    const polynomal operator+(const polynomal& poly){ //некорректо присваивает
        polynomal rez;
        rez.coef.resize(fmax(this->get_max_degree(), poly.get_max_degree()));
        for (int i = 0; i < rez.get_max_degree(); ++i){
            float new_coef = this->get_coef(i) + poly.get_coef(i);
            this->set_coef(i, new_coef);
        }
        return rez;
    }
    const polynomal operator-(const polynomal& poly){ //некорректо присваивает
        polynomal rez;
        rez.coef.resize(fmax(this->get_max_degree(), poly.get_max_degree()));
        for (int i = 0; i < rez.get_max_degree(); ++i){
            float new_coef = this->get_coef(i) - poly.get_coef(i);
            this->set_coef(i, new_coef);
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
        if (poly.get_coef(j) != 0){
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
    std :: cout << std :: endl;

    std :: vector <float> coefficents;
    coefficents.push_back(0);
    coefficents.push_back(1);
    coefficents.push_back(-2);
    coefficents.push_back(3);

    polynomal poly(coefficents);
    polynomal poly2;

    std :: cout << "poly: \t\t" << poly << std :: endl;
    std :: cout << "poly2: \t\t"<< poly2 << std :: endl;
    poly2 = poly;
    std :: cout << "new poly2: \t" << poly2 << std :: endl;
    std :: cout << "poly ? poly2\t" << (poly == poly2) << std :: endl;
    std :: cout << "poly ? poly2\t" << (poly != poly2) << std :: endl;

    poly2 += poly;
    std :: cout << "poly2: \t\t" << poly2 << "\tpoly:\t\t" << poly << std :: endl;
    std :: cout << "poly ? poly2\t" << (poly == poly2) << std :: endl;
    std :: cout << "poly ? poly2\t" << (poly != poly2) << std :: endl;
    std :: cout << "poly2[2]: \t\t" << poly2[2] << std :: endl;

    polynomal poly3;
    poly3 += poly;
    poly3 -= poly;
    std :: cout << "poly3: \t\t" << poly3 << std :: endl;

    polynomal poly4;
    poly4 = poly2 + poly;
    std :: cout << "poly4: \t\t" << poly4 << "\tpoly2: \t\t" << poly2 << "\tpoly:\t\t" << poly << std :: endl;

    std :: cout << "poly2:\t\t" << poly2 << std :: endl;
    poly2 = - poly2;
    std :: cout <<"- poly2:\t" << poly2 << std :: endl;

    std :: vector <float> coefficents2;
    coefficents2.push_back(1);
    coefficents2.push_back(0);
    coefficents2.push_back(-2);
    coefficents2.push_back(3);
    polynomal poly5(coefficents2);
    std :: cout << "poly: \t\t" << poly << "\tpoly5: \t\t" << poly5 << std :: endl;
    poly5 *= poly;
    std :: cout << "poly: \t\t" << poly << "\tpoly5: \t\t" << poly5 << std :: endl;
    std :: cout << "\nDONE" << std :: endl;
}
/* class polynomial{
    public:
    std :: string poly[100][2]; //1 - коэфициент, 2 - число, i - степень

    //constructer
    polynomial(std :: string str = "\0"){
        str.append("+");
        int pos1 = 0;
        while (pos1 < str.size()){
            if ((str.compare(pos1, 1, "-") == 0)){
                str.insert(pos1, "+", 0, 1); //вставляем  в строку + перед минусом
                ++pos1;
            }
            ++pos1;
        }
        std :: cout << str << std :: endl;
        
        while (!str.empty())
        {
            int degree_start = str.find("^", str.size());
            int plus_pos = str.find("+", str.size());
            if (degree_start == std :: string :: npos){
                degree_start = str.size() + 1;
            }
            if (plus_pos == std :: string :: npos){
                plus_pos = str.size() + 1;
            }

            if (plus_pos < degree_start && degree_start != str.size() + 1){ // the number doesn't have the degree
                char number_string[10];
                str.copy(number_string, plus_pos, 0);
                str.erase(0, plus_pos);

                poly[1][0].append(number_string);
            }
            else if (plus_pos > degree_start && plus_pos != str.size() + 1){
                char number_string[10];
                str.copy(number_string, degree_start, 0);
                str.erase(0, degree_start + 1);

                char degree_string[10];
                str.copy(degree_string, plus_pos, 0);
                str.erase(0, plus_pos);

                int degree_int = atoi(degree_string);
                poly[degree_int][0].append(number_string);
            }
            int degree_start = str.rfind("^", str.length() - 1), degree_finish = str.length() - 1;
            char degree[10];
            str.copy(degree, degree_finish - degree_start, degree_start);
            int degree_int = atoi(degree);
            str.erase(degree_start - 1, degree_finish - degree_start + 1);

            int number_start = str.rfind("+", str.length()), number_finish = str.length() - 1;
            char number[100];
            str.copy(number, number_finish - number_start, number_start);
            poly[degree_int][1] = number;
            str.erase(number_start, number_finish - number_start);
        }
        //make poly coef and letter brackement
    }
}; */

/* std :: ostream& operator<< (std :: ostream& stream, const polynomial& poly){
    stream << poly.poly[0][0] << poly.poly[0][1];
    for (int i = 1; i < 100; ++i){
        if (poly.poly[i][1] != 0){
            if (poly.poly[i][1] > 0)
                stream << " + " << poly.poly[i][0] << poly.poly[i][1] << "^" << i;
            else
                stream << " " <<  poly.poly[i][0] << poly.poly[i][2] << "^" << i;
        }
    }
} */

/* int main (){
    std :: string str;
    std :: cin >> str;
    polynomial poly(str);
    for (int i = 0; i < 100; ++i){
        if (poly.poly[i][0] != "\0")
            std :: cout << " + " << poly.poly[i][0] << "^" << i;
    }
} */
/* class polynomial{
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
    void with_letters(){
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
    }
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
    std :: string str3 = "2a-3b+c";
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
    std :: cout << "\n" << std :: endl;
} */