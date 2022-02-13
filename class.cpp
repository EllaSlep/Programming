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

    point(){
        dot_.x_ = 0;
        dot_.y_ = 0;
    }
    //конструктор
    point (int x, int y){
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
        broken_line.push_back(broken_line.front());
    }

    //конструктор копирования
    closed_polyline(const polyline& polyline_a){
        broken_line.push_back(polyline_a.broken_line.front());
    }
    
    closed_polyline(const closed_polyline& polyline_b){
        for (int i = 0; i < polyline_b.broken_line.size(); i++){
            broken_line[i] = polyline_b.broken_line[i];
        }
    }
    //оператор присваивания
    closed_polyline& operator=(const closed_polyline& polyline_c){
        for (int i = 0; i < polyline_c.broken_line.size(); i++){
            this->broken_line[i] = polyline_c.broken_line[i];
        }
        return *this;
    }
    double length_polyline(){
        double rez = 0.0;
        for (int i = 0; i < broken_line.size() - 1; i++){
            rez += sqrt(pow(broken_line[i].x_ - broken_line[i + 1].x_, 2) + pow(broken_line[i].y_ - broken_line[i + 1].y_,2)); //pow- возведение в степень
        }
        return rez;
    }
};

int main(){
    int x, y;
    std :: cin >> x >> y;
    point A(x, y);
    std :: cin >> x >> y;
    point B(x, y);
    std :: cin >> x >> y;
    point C(x, y);
    std :: cout << "A (" << A.dot_.x_ << ";" << A.dot_.y_ << ")\n" << "B (" << B.dot_.x_ << ";" << B.dot_.y_ << ")\n" << "C (" << C.dot_.x_ << ";" << C.dot_.y_ << ")" << std :: endl;
    polyline line(3, A.dot_, B.dot_, C.dot_);

    //std :: cout << line.length_polyline() << std :: endl;

    /* point D(A);
    std :: cout << "\nA (" << A.dot_.x_ << ";" << A.dot_.y_ << ")\n" << "D (" << D.dot_.x_ << ";" << D.dot_.y_ << ")\n" << std :: endl;

    point F;
    F.operator=(A);
    std :: cout << "\nA (" << A.dot_.x_ << ";" << A.dot_.y_ << ")\n" << "F (" << F.dot_.x_ << ";" << F.dot_.y_ << ")\n" << std :: endl; */
    
    closed_polyline closed_line(line);
    dot D = closed_line.broken_line.back();
    std :: cout << "D (" << D.x_ << ";" << D.y_ << ")\n" << std :: endl;
    std :: cout << closed_line.length_polyline() << std :: endl;
}