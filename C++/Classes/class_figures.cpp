#include <iostream>
#include <cmath>
#include <vector>

struct dot{
    int x_;
    int y_;
};

class point{
    public:
    dot dot_;

    //конструктор
    point (int x = 0, int y = 0){
        dot_.x_ = x;
        dot_.y_ = y;
    }
    //конструктор копирования
    point (const point &point_A){
        dot_.x_ = point_A.dot_.x_;
        dot_.y_ = point_A.dot_.y_;
    }
    //оператор присваивания
    point& operator=(const point &point_B){
        this->dot_.x_ = point_B.dot_.x_;
        this->dot_.y_ = point_B.dot_.y_;
        return *this;
    }
    //setters
    void set_x(const int& x){
        dot_.x_ = x;
    }
    void set_y(const int& y){
        dot_.y_ = y;
    }
    //getters
    int get_x(const point& point_A){
        return point_A.dot_.x_;
    }
    int get_y(const point& point_B){
        return point_B.dot_.y_;
    }
    //деструктор
    ~point()
    {}
};

class polyline{
    public:
    std :: vector <dot> broken_line;

    //конструктор
    polyline (int count, ...){
        va_list vl;
        va_start (vl, count);
        for (int i = 0; i < count; i ++){
            broken_line.push_back(va_arg(vl, dot));
        }
        va_end(vl);
    }
    //конструктор копирования
    polyline(const polyline& polyline_a){
        for (int i = 0; i < polyline_a.broken_line.size(); i++){
            broken_line[i] = polyline_a.broken_line[i];
        }
    }
    //оператор присваивания
    polyline& operator=(const polyline& polyline_b){
        for (int i = 0; i < polyline_b.broken_line.size(); i++){
            this->broken_line[i] = polyline_b.broken_line[i];
        }
        return *this;
    }
    void add_point(const dot& A){
        broken_line.resize(broken_line.size() + 1, A);
    }
    //длина
    double length_polyline(){
        double rez = 0.0;
        for (int i = 0; i < broken_line.size() - 1; i++){
            rez += sqrt(pow(broken_line[i].x_ - broken_line[i + 1].x_, 2) + pow(broken_line[i].y_ - broken_line[i + 1].y_,2)); //pow- возведение в степень
        }
        return rez;
    }
    //деструктор
    ~polyline()
    {}
};

class closed_polyline{
    public:
    std :: vector <dot> broken_line;

    //конструктор
    closed_polyline (int count, ...){
        va_list vl;
        va_start (vl, count);
        for (int i = 0; i < count; i ++){
            broken_line.push_back(va_arg(vl, dot));
        }
        va_end(vl);
        broken_line.resize(broken_line.size() + 1, broken_line.front()); //broken_line.push_back(broken_line.front());
    }
    //конструктор копирования
    closed_polyline(const polyline& polyline_a){
        for (int i = 0; i < polyline_a.broken_line.size(); i++){
            broken_line.push_back(polyline_a.broken_line[i]);
        }
        broken_line.resize(broken_line.size() + 1, broken_line.front());
    }

    closed_polyline(const closed_polyline& polyline_b){
        for (int i = 0; i < polyline_b.broken_line.size(); i++){
            broken_line.push_back(polyline_b.broken_line[i]);
        }
    }
    //оператор присваивания
    closed_polyline& operator=(const closed_polyline& polyline_c){
        for (int i = 0; i < polyline_c.broken_line.size(); i++){
            this->broken_line[i] = polyline_c.broken_line[i];
        }
        return *this;
    }
    void add_point(const dot& A){
        broken_line.resize(broken_line.size() + 1, A);
    }
    // длина
    double length_polyline(){
        double rez = 0.0;
        for (int i = 0; i < broken_line.size() - 1; i++){
            rez += sqrt(pow(broken_line[i].x_ - broken_line[i + 1].x_, 2) + pow(broken_line[i].y_ - broken_line[i + 1].y_,2)); //pow- возведение в степень
        }
        return rez;
    }
    //деструктор
    ~closed_polyline()
    {}
};

class polygon : public closed_polyline{
    public:
    //конструктор
    polygon(const closed_polyline& closed_polyline_a) : closed_polyline(closed_polyline_a) 
    {}
    //оператор присваивания
    polygon& operator= (const polygon& polygon_B){
        for (int i = 0; i < polygon_B.broken_line.size(); i++){
            this->broken_line[i] = polygon_B.broken_line[i];
        }
        return *this;
    }
    //площадь многоугольника
    double polygon_area(){
        double rez = 0.0;
        for (int i = 0; i < broken_line.size() - 1; i++){
            rez += ((broken_line[i].x_ * broken_line[i + 1].y_) - (broken_line[i].y_ * broken_line[i + 1].x_));
        }
        return abs(rez / 2);
    }
    //деструктор
    ~polygon()
    {}
};

class triangle : public polygon{
    public:
    //конструктор
    triangle(const closed_polyline& closed_polyline_a) : polygon(closed_polyline_a)
    {}
    //оператор присваивания
    triangle& operator= (const triangle& ABC){
        for (int i = 0; i < 3; i++){
            this->broken_line[i] = ABC.broken_line[i];
        }
        return *this;
    }
    //деструктор
    ~triangle()
    {}
};

class trapezoid : public polygon{
    public:
    //конструктор
    trapezoid(const closed_polyline& closed_polyline_a) : polygon(closed_polyline_a)
    {}
    //оператор присваивания
    trapezoid& operator= (const trapezoid& ABCD){
        for (int i = 0; i < 4; i++){
            this->broken_line[i] = ABCD.broken_line[i];
        }
        return *this;
    }
    //деструктор
    ~trapezoid()
    {}
};

class regular_polygon : public polygon{
    public:
    //конструктор
    regular_polygon(const closed_polyline& closed_polyline_a) : polygon(closed_polyline_a)
    {}
    //оператор присваивания
    regular_polygon& operator= (const regular_polygon& ABCD){
        for (int i = 0; i < 4; i++){
            this->broken_line[i] = ABCD.broken_line[i];
        }
        return *this;
    }
    //деструктор
    ~regular_polygon()
    {}
};

int main(){
    point A(2, 1);
    point B(3, 2);
    point C(4, 3);
    point D(4, 1);
    std :: cout << "\nPOINTS:\nA (" << A.dot_.x_ << ";" << A.dot_.y_ << ")\nB (" << B.dot_.x_ << ";" << B.dot_.y_ << ")\nC (" << C.dot_.x_ << ";" << C.dot_.y_ <<  ")\nD (" << D.dot_.x_ << ";" << D.dot_.y_ << ")" << std :: endl;
    
    polyline line(4, A.dot_, B.dot_, C.dot_, D.dot_);
    std :: cout << "\nLINES\nline length: " << line.length_polyline() << std :: endl;

    closed_polyline closed_line(line);
    std :: cout << "closed line lenght: "<< closed_line.length_polyline() << std :: endl;

    polygon ABCD(line);
    std :: cout << "\nPOLYGON\nABCD perimeter: " << ABCD.length_polyline() << std :: endl;
    std :: cout << "ABCD area: " << ABCD.polygon_area() << std :: endl;

    std :: cout << "\nTRIANGLE\npoints:\nA (" << A.dot_.x_ << ";" << A.dot_.y_ << ")\nC (" << C.dot_.x_ << ";" << C.dot_.y_ <<  ")\nD (" << D.dot_.x_ << ";" << D.dot_.y_ << ")" << std :: endl;
    closed_polyline line2(3, A.dot_, C.dot_, D.dot_);
    triangle ACD(line2);
    std :: cout << "ABC perimeter: " << ACD.length_polyline() << std :: endl;
    std :: cout << "ABC area: " << ACD.polygon_area() << std :: endl;

    point K(0, 0);
    point L(0, 2);
    point M(2, 2);
    point N(3, 0);
    std :: cout << "\nTRAPEZIOD\npoints:\nK (" << K.dot_.x_ << ";" << K.dot_.y_ << ")\nL (" << L.dot_.x_ << ";" << L.dot_.y_ << ")\nM (" << M.dot_.x_ << ";" << M.dot_.y_ <<  ")\nN (" << N.dot_.x_ << ";" << N.dot_.y_ << ")" << std :: endl;
    closed_polyline line3(4, K.dot_, L.dot_, M.dot_, N.dot_);
    trapezoid KLMN(line3);
    std :: cout << "KLMN perimeter: " << KLMN.length_polyline() << std :: endl;
    std :: cout << "KLMN area: " << KLMN.polygon_area() << std :: endl;

    point F(0, 0);
    point E(0, 2);
    point G(2, 2);
    point H(2, 0);
    std :: cout << "\nSQUARE\npoints:\nF (" << F.dot_.x_ << ";" << F.dot_.y_ << ")\nE (" << E.dot_.x_ << ";" << E.dot_.y_ << ")\nG (" << G.dot_.x_ << ";" << G.dot_.y_ <<  ")\nH (" << H.dot_.x_ << ";" << H.dot_.y_ << ")" << std :: endl;
    closed_polyline line4(4, F.dot_, E.dot_, G.dot_, H.dot_);
    regular_polygon FEGH(line4);
    std :: cout << "FEGH perimeter: " << FEGH.length_polyline() << std :: endl;
    std :: cout << "FEGH area: " << FEGH.polygon_area() << "\n" << std :: endl;
}