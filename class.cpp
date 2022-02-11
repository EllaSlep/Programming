#include <iostream>
#include <cmath>
#include <vector>

class point{
    private:
    int x_;
    int y_;

    public:
    //конструктор
    point (int x, int y){
        x_ = x;
        y_ = y;
    }
    //конструктор копирования
    point (const point &point_A){
        x_ = point_A.x_;
        y_ = point_A.y_;
    }
    //оператор присваивания
    point& operator=(const point &point_B){
        this->x_ = point_B.x_;
        this->y_ = point_B.y_;
        return *this;
    }
};

class polyline{
    private:
    std :: vector <point> broken_line(128);

    public:
    //конструктор
    polyline (const point& point_A){
        vector <point> :: broken_line.push_back(point_A);
    }
    //конструктор копирования
    polyline(const polyline& polyline_a){
        for (int i = 0; i < vector <point> :: polyline_a.broken_line.size(); i++){
            broken_line[i] == polyline_a.broken_line[i];
        }
    }
    //оператор присваивания
    polyline& operator=(const polyline& polyline_b){
        for (int i = 0; i < vector <point> :: polyline_a.broken_line.size(); i++){
            this->broken_line[i] == polyline_a.broken_line[i];
        }
        return *this;
    }
    //длина
    double length_polyline(/* const polyline& polyline_c */){
        double rez = 0.0;
        for (int i = 0; i < vector <point> :: broken_line.size(); i++){
            rez += sqrt(pow(, 2) + pow(,2));
        }
    }
    /* double Length(){
        double result = 0.0;

        for (int i = 0; i < (points.size() - 1); ++i)
        {
            result += sqrt(pow(points[i].first - points[i+1].first, 2) + pow(points[i].second - points[i+1].second, 2));//pow- возведение в степень
        }

        return result;
    } */
};

class closed_polyline : public polyline{
    public:
    //конструктор
    closed_polyline(const polyline& polyline_a){
        vector <point> :: broken_line.push_back(vector <point> :: polyline_a.broken_line.front());
    }
    //конструктор копирования
    //оператор присваивания
};

int main(){

}