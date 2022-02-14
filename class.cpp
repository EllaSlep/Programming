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

int main(){
    int x, y;
    std :: cin >> x >> y;
    point A(x, y);
    std :: cin >> x >> y;
    point B(x, y);
    std :: cin >> x >> y;
    point C(x, y);
    std :: cin >> x >> y;
    point D(x, y);
    std :: cout << "\npoints:\nA (" << A.dot_.x_ << ";" << A.dot_.y_ << ")\nB (" << B.dot_.x_ << ";" << B.dot_.y_ << ")\nC (" << C.dot_.x_ << ";" << C.dot_.y_ <<  ")\nD (" << D.dot_.x_ << ";" << D.dot_.y_ << ")" << std :: endl;
    
    polyline line(4, A.dot_, B.dot_, C.dot_, D.dot_);
    std :: cout << "\nline length: " << line.length_polyline() << std :: endl;

    /* point D(A);
    std :: cout << "\nA (" << A.dot_.x_ << ";" << A.dot_.y_ << ")\n" << "D (" << D.dot_.x_ << ";" << D.dot_.y_ << ")\n" << std :: endl; */

    /* point F;
    F = A;
    std :: cout << "\nA (" << A.dot_.x_ << ";" << A.dot_.y_ << ")\nF (" << F.dot_.x_ << ";" << F.dot_.y_ << ")\n" << std :: endl; */
    
    /* closed_polyline closed_line(line);
    std :: cout << "\nclosed line lenght: "<< closed_line.length_polyline() << std :: endl; */

    /* closed_polyline closed_line2(3, A.dot_, B.dot_, C.dot_);
    std :: cout << closed_line2.length_polyline() << std :: endl; */

    polygon ABCD(line);
    std :: cout << "\nperimeter: " << ABCD.length_polyline() << std :: endl;
    std :: cout << "\narea: " << ABCD.polygon_area() << std :: endl;
}