#include <iostream>

// 1 - white, 2 - yellow, 3 - pink, 4 - green, 5 - orange, 6 - blue

class cube{
    private:
    int front_[3][3];
    int back_[3][3];
    int right_[3][3];
    int left_[3][3];
    int up_[3][3];
    int down_[3][3];

    public:
    int get_front(int i, int j){
        return front_[i][j];
    }
    int get_back(int i, int j){
        return back_[i][j];
    }
    int get_right(int i, int j){
        return right_[i][j];
    }
    int get_left(int i, int j){
        return left_[i][j];
    }
    int get_up(int i, int j){
        return up_[i][j];
    }
    int get_down(int i, int j){
        return down_[i][j];
    }
    
    void set_front(int i, int j, int value){
        front_[i][j] = value;
    }
    void set_back(int i, int j, int value){
        back_[i][j] = value;
    }
    void set_right(int i, int j, int value){
        right_[i][j] = value;
    }
    void set_left(int i, int j, int value){
        left_[i][j] = value;
    }
    void set_up(int i, int j, int value){
        up_[i][j] = value;
    }
    void set_down(int i, int j, int value){
        down_[i][j] = value;
    }

    cube(int front[3][3], int back[3][3], int right[3][3], int left[3][3], int up[3][3], int down[3][3]){
        for (int i = 0; i < 3; ++i){
            for (int j = 0; j < 3; ++j){
                set_front(i, j, front[i][j]);
                set_back(i, j, back[i][j]);
                set_right(i, j, right[i][j]);
                set_left(i, j, left[i][j]);
                set_up(i, j, up[i][j]);
                set_down(i, j, down[i][j]);
            }
        }
    }

    void right_rotation_up(){ // доделать
        int up[3], back[3], down[3], front[3];
        
        for (int i = 0; i < 3; ++i){
            up[i] = get_up(i, 2);
            back[i] = get_back(i, 2);
            down[i] = get_down(i, 2);
            front[i] = get_front(i, 2);
        }
        for (int i = 0; i < 3; ++i){
            set_up(i, 2, front[i]);
            set_back(i, 2, up[i]);
            set_down(i, 2, back[i]);
            set_front(i , 2, down[i]);
        }
    }

    void right_rotation_down(){ // доделать
        int up[3], back[3], down[3], front[3];
        
        for (int i = 0; i < 3; ++i){
            up[i] = get_up(i, 2);
            back[i] = get_back(i, 2);
            down[i] = get_down(i, 2);
            front[i] = get_front(i, 2);
        }
        for (int i = 0; i < 3; ++i){
            set_up(i, 2, back[i]);
            set_back(i, 2, down[i]);
            set_down(i, 2, front[i]);
            set_front(i , 2, up[i]);
        }
    }

    void left_rotation_up(){ // доделать
        int up[3], back[3], down[3], front[3];
        
        for (int i = 0; i < 3; ++i){
            up[i] = get_up(i, 0);
            back[i] = get_back(i, 0);
            down[i] = get_down(i, 0);
            front[i] = get_front(i, 0);
        }
        for (int i = 0; i < 3; ++i){
            set_up(i, 0, front[i]);
            set_back(i, 0, up[i]);
            set_down(i, 0, back[i]);
            set_front(i , 0, down[i]);
        }
    }

    void left_rotation_down(){ // доделать
        int up[3], back[3], down[3], front[3];
        
        for (int i = 0; i < 3; ++i){
            up[i] = get_up(i, 0);
            back[i] = get_back(i, 0);
            down[i] = get_down(i, 0);
            front[i] = get_front(i, 0);
        }
        for (int i = 0; i < 3; ++i){
            set_up(i, 0, back[i]);
            set_back(i, 0, down[i]);
            set_down(i, 0, front[i]);
            set_front(i , 0, up[i]);
        }
    }

    void up_rotation_right(){
        int front1[3], front2[3], right1[3], right2[3], back1[3], back2[3], left1[3], left2[3];
        for (int i = 0; i < 3; ++i){
            front1[i] = get_front(0, i);
            right1[i] = get_right(0, i);
            back1[i] = get_back(0, i);
            left1[i] = get_left(0, i);

            front2[i] = get_up(2, i);
            right2[i] = get_up(i, 2);
            back2[i] = get_up(2, i);
            left2[i] = get_up(i, 2);
        }
        for (int i = 0; i < 3; ++i){
            set_right(0, i, front1[i]);
            set_back(0, i, right1[i]);
            set_left(0, i, back1[i]);
            set_front(0, i, left1[i]);

            set_up(i, 2, front2[i]);
            set_up(0, i,right2[i]);
            set_up(i, 0, back2[i]);
            set_up(2, i, left2[i]);
        }
    }

};

std::ostream& operator<< (std::ostream& stream, cube cub){
    for (int i = 0; i < 3; ++i){
        stream << "\t    ";
        for (int j = 0; j < 3; ++j)
            stream << cub.get_up(i, j) << " ";
        stream << "\n";
    }
    for (int j = 0; j < 3; ++j){
        for (int i = 0; i < 3; ++i){
            stream << cub.get_back(j, i) << " ";
        }
        for (int i = 0; i < 3; ++i){
            stream << cub.get_left(j, i) << " ";
        }
        for (int i = 0; i < 3; ++i){
            stream << cub.get_front(j, i) << " ";
        }
        for (int i = 0; i < 3; ++i){
            stream << cub.get_right(j, i) << " ";
        }
        stream << "\n";
    }
    for (int i = 0; i < 3; ++i){
        stream << "\t    ";
        for (int j = 0; j < 3; ++j)
            stream << cub.get_down(i, j) << " ";
        stream << "\n";
    }
    return stream;
}

int main(){
    int front[3][3] = {{6, 6, 6}, {6, 6, 6}, {6, 6, 6}};
    int back[3][3] = {{4, 4, 4}, {4, 4, 4}, {4, 4, 4}};
    int right[3][3] = {{3, 3, 3}, {3, 3, 3}, {3, 3, 3}};
    int left[3][3] = {{5, 5, 5}, {5, 5, 5}, {5, 5, 5}};
    int up[3][3] = {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}};
    int down[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};

    cube cub(front, back, right, left, up, down);
    std::cout << cub << "\n\n";

    cub.right_rotation_up();
    std::cout << cub << "\n\n";

    cub.right_rotation_down();
    std::cout << cub << "\n\n";

    cub.left_rotation_down();
    std::cout << cub << "\n\n";

    cub.left_rotation_up();
    std::cout << cub << "\n\n";

    cub.up_rotation_right();
    std::cout << cub << "\n\n";
}