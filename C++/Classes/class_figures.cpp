#include <iostream>
#include <cmath>
#include <vector>

struct dot{
    int x_;
    int y_;
};

class point{
    private:
    dot dot_;

    public:
    //конструктор
    point (int x = 0, int y = 0){
        this->set_x(x);
        this->set_y(y);
    }
    //конструктор копирования
    point (const point &point_A){
        this->set_x(point_A.get_x());
        this->set_y(point_A.get_y());
    }
    //оператор присваивания
    point& operator=(const point &point_B){
        this->set_x(point_B.get_x());
        this->set_y(point_B.get_y());
        return *this;
    }
    //setters
    void set_x(const int& x){
        this->dot_.x_ = x;
    }
    void set_y(const int& y){
        this->dot_.y_ = y;
    }
    //getters
    int get_x() const{
        return this->dot_.x_;
    }
    int get_y() const{
        return this->dot_.y_;
    }
    dot get_dot(){
        return this->dot_;
    }
    //деструктор
    ~point()
    {}
};

class polyline{
    private:
    std :: vector <dot> broken_line;

    public:
    //setters
    void set_point (int i, const dot& point){
        this->broken_line[i] = point;
    }
    //getters
    dot get_point(int i) const {
        return this->broken_line[i];
    }
    unsigned get_size() const{
        return this->broken_line.size();
    }
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
        for (int i = 0; i < polyline_a.get_size(); i++){
            this->set_point(i, polyline_a.get_point(i));
        }
    }
    //оператор присваивания
    polyline& operator=(const polyline& polyline_b){
        for (int i = 0; i < polyline_b.get_size(); i++){
            this->set_point(i, polyline_b.get_point(i));
        }
        return *this;
    }
    void add_point(const dot& A){
        this->broken_line.resize(this->get_size() + 1, A);
    }
    //длина
    double length_polyline(){
        double rez = 0.0;
        for (int i = 0; i < this->get_size() - 1; i++){
            rez += sqrt(pow(this->get_point(i).x_ - this->get_point(i + 1).y_, 2) + pow(this->get_point(i).x_ - this->get_point(i + 1).y_, 2)); //pow- возведение в степень
        }
        return rez;
    }
    //деструктор
    ~polyline()
    {}
};

class closed_polyline{
    private:
    std :: vector <dot> broken_line;

    public:
    //setters
    void set_point (int i, const dot& point){
        this->broken_line[i] = point;
    }
    //getters
    dot get_point(int i) const {
        return this->broken_line[i];
    }
    unsigned get_size() const{
        return this->broken_line.size();
    }
    //конструктор
    closed_polyline (int count, ...){
        va_list vl;
        va_start (vl, count);
        for (int i = 0; i < count; i ++){
            this->broken_line.push_back(va_arg(vl, dot));
        }
        va_end(vl);
        this->broken_line.resize(this->broken_line.size() + 1, this->broken_line.front()); //broken_line.push_back(broken_line.front());
    }
    //конструктор копирования
    closed_polyline(const polyline& polyline_a){
        for (int i = 0; i < polyline_a.get_size(); i++){
            this->broken_line.push_back(polyline_a.get_point(i));
        }
        this->broken_line.resize(this->broken_line.size() + 1, this->broken_line.front());
    }

    closed_polyline(const closed_polyline& polyline_b){
        for (int i = 0; i < polyline_b.get_size(); i++){
            this->broken_line.push_back(polyline_b.get_point(i));
        }
    }
    //оператор присваивания
    closed_polyline& operator=(const closed_polyline& polyline_c){
        for (int i = 0; i < polyline_c.get_size(); i++){
            this->set_point(i, polyline_c.get_point(i));
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
            rez += sqrt(pow(this->get_point(i).x_ - this->get_point(i + 1).y_, 2) + pow(this->get_point(i).x_ - this->get_point(i + 1).y_, 2)); //pow- возведение в степень
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
        for (int i = 0; i < polygon_B.get_size(); i++){
            this->set_point(i, polygon_B.get_point(i));
        }
        return *this;
    }
    //площадь многоугольника
    double polygon_area(){
        double rez = 0.0;
        for (int i = 0; i < this->get_size() - 1; i++){
            rez += ((this->get_point(i).x_ * this->get_point(i + 1).y_) - (this->get_point(i).y_ * this->get_point(i + 1).x_));
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
    {
        if (closed_polyline_a.get_size() != 4){
            std :: cout << "It's not a triangle!\n";
            exit(-2);
        }
    }
    //оператор присваивания
    triangle& operator= (const triangle& ABC){
        for (int i = 0; i < 3; i++){
            this->set_point(i, ABC.get_point(i));
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
    {
        if (closed_polyline_a.get_size() != 5){
            std :: cout << "It's not a trapezoid!\n";
            exit(-2);
        }
        
        float k1 = (closed_polyline_a.get_point(1).y_ - closed_polyline_a.get_point(0).y_)/(closed_polyline_a.get_point(1).x_ - closed_polyline_a.get_point(0).x_);
        float k2 = (closed_polyline_a.get_point(2).y_ - closed_polyline_a.get_point(1).y_)/(closed_polyline_a.get_point(2).x_ - closed_polyline_a.get_point(1).x_);
        float k3 = (closed_polyline_a.get_point(3).y_ - closed_polyline_a.get_point(2).y_)/(closed_polyline_a.get_point(3).x_ - closed_polyline_a.get_point(2).x_);
        float k4 = (closed_polyline_a.get_point(4).y_ - closed_polyline_a.get_point(3).y_)/(closed_polyline_a.get_point(4).x_ - closed_polyline_a.get_point(3).x_);
        
        if (k1 != k2 && k1 != k3 && k1 != k4 && k2 != k3 && k2 != k4 && k3 != k4){
            std :: cout << "It's not a trapezoid!\n";
            exit(-2);
        }
        
    }
    //оператор присваивания
    trapezoid& operator= (const trapezoid& ABCD){
        for (int i = 0; i < 4; i++){
            this->set_point(i, ABCD.get_point(i));
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
    {
        if (closed_polyline_a.get_size() != 5){
            std :: cout << "It's not a regular polygon!\n";
            exit(-2);
        }
    }
    //оператор присваивания
    regular_polygon& operator= (const regular_polygon& ABCD){
        for (int i = 0; i < 4; i++){
            this->set_point(i, ABCD.get_point(i));
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
    std :: cout << "\nPOINTS:\nA (" << A.get_x() << ";" << A.get_y() << ")\nB (" << B.get_x() << ";" << B.get_y() << ")\nC (" << C.get_x() << ";" << C.get_y() <<  ")\nD (" << D.get_x() << ";" << D.get_y() << ")" << std :: endl;
    
    polyline line(4, A.get_dot(), B.get_dot(), C.get_dot(), D.get_dot());
    std :: cout << "\nLINES\nline length: " << line.length_polyline() << std :: endl;

    closed_polyline closed_line(line);
    std :: cout << "closed line lenght: "<< closed_line.length_polyline() << std :: endl;

    polygon ABCD(line);
    std :: cout << "\nPOLYGON\nABCD perimeter: " << ABCD.length_polyline() << std :: endl;
    std :: cout << "ABCD area: " << ABCD.polygon_area() << std :: endl;

    std :: cout << "\nTRIANGLE\npoints:\nA (" << A.get_x() << ";" << A.get_y() << ")\nC (" << C.get_x() << ";" << C.get_y() <<  ")\nD (" << D.get_x() << ";" << D.get_y() << ")" << std :: endl;
    closed_polyline line2(3, A.get_dot(), C.get_dot(), D.get_dot());
    triangle ACD(line2);
    std :: cout << "ABC perimeter: " << ACD.length_polyline() << std :: endl;
    std :: cout << "ABC area: " << ACD.polygon_area() << std :: endl;

    point K(1, 2);
    point L(3, 6);
    point M(4, 5);
    point N(2, 1);
    std :: cout << "\nTRAPEZIOD\npoints:\nK (" << K.get_x() << ";" << K.get_y() << ")\nL (" << L.get_x() << ";" << L.get_y() << ")\nM (" << M.get_x() << ";" << M.get_y() <<  ")\nN (" << N.get_x() << ";" << N.get_y() << ")" << std :: endl;
    closed_polyline line3(4, K.get_dot(), L.get_dot(), M.get_dot(), N.get_dot());
    trapezoid KLMN(line3);
    std :: cout << "KLMN perimeter: " << KLMN.length_polyline() << std :: endl;
    std :: cout << "KLMN area: " << KLMN.polygon_area() << std :: endl;

    point F(0, 0);
    point E(0, 2);
    point G(2, 2);
    point H(2, 0);
    std :: cout << "\nSQUARE\npoints:\nF (" << F.get_x() << ";" << F.get_y() << ")\nE (" << E.get_x() << ";" << E.get_y() << ")\nG (" << G.get_x() << ";" << G.get_y() <<  ")\nH (" << H.get_x() << ";" << H.get_y() << ")" << std :: endl;
    closed_polyline line4(4, F.get_dot(), E.get_dot(), G.get_dot(), H.get_dot());
    regular_polygon FEGH(line4);
    std :: cout << "FEGH perimeter: " << FEGH.length_polyline() << std :: endl;
    std :: cout << "FEGH area: " << FEGH.polygon_area() << "\n" << std :: endl;
}