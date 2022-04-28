#include <iostream>
#include <vector>

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

    void right_rotation_up(){ 
        int up1[3], up2[3], back1[3], back2[3], down1[3], down2[3], front1[3], front2[3];
        
        for (int i = 0; i < 3; ++i){
            up1[i] = get_up(i, 2);
            back1[i] = get_back(i, 2);
            down1[i] = get_down(i, 2);
            front1[i] = get_front(i, 2);

            up2[i] = get_right(0, i);
            back2[i] = get_right(i, 2);
            down2[i] = get_right(2, i);
            front2[i] = get_right(i, 0);
        }
        for (int i = 0; i < 3; ++i){
            set_up(i, 2, front1[i]);
            set_back(i, 2, up1[i]);
            set_down(i, 2, back1[i]);
            set_front(i , 2, down1[i]);

            set_right(0, i, front2[i]);
            set_right(i, 0, down2[i]);
            set_right(2, i, back2[i]);
            set_right(i, 2, up2[i]);
        }
    }
    void right_rotation_down(){ 
        int up1[3], up2[3], back1[3], back2[3], down1[3], down2[3], front1[3], front2[3];
        
        for (int i = 0; i < 3; ++i){
            up1[i] = get_up(i, 2);
            back1[i] = get_back(i, 2);
            down1[i] = get_down(i, 2);
            front1[i] = get_front(i, 2);

            up2[i] = get_right(0, i);
            back2[i] = get_right(i, 2);
            down2[i] = get_right(2, i);
            front2[i] = get_right(i, 0);
        }
        for (int i = 0; i < 3; ++i){
            set_up(i, 2, back1[i]);
            set_back(i, 2, down1[i]);
            set_down(i, 2, front1[i]);
            set_front(i , 2, up1[i]);

            set_right(0, i, back2[i]);
            set_right(i, 0, up2[i]);
            set_right(2, i, front2[i]);
            set_right(i, 2, down2[i]);
        }
    }

    void left_rotation_up(){
        int up1[3], up2[3], back1[3], back2[3], down1[3], down2[3], front1[3], front2[3];
        
        for (int i = 0; i < 3; ++i){
            up1[i] = get_up(i, 0);
            back1[i] = get_back(i, 0);
            down1[i] = get_down(i, 0);
            front1[i] = get_front(i, 0);

            up2[i] = get_left(0, i);
            back2[i] = get_left(i, 0);
            down2[i] = get_left(2, i);
            front2[i] = get_left(i, 2);
        }
        for (int i = 0; i < 3; ++i){
            set_up(i, 0, front1[i]);
            set_back(i, 0, up1[i]);
            set_down(i, 0, back1[i]);
            set_front(i , 0, down1[i]);

            set_left(0, i, front2[i]);
            set_left(i, 0, up2[i]);
            set_left(2, i, back2[i]);
            set_left(i, 2, down2[i]);
        }
    }
    void left_rotation_down(){
        int up1[3], up2[3], back1[3], back2[3], down1[3], down2[3], front1[3], front2[3];
        
        for (int i = 0; i < 3; ++i){
            up1[i] = get_up(i, 0);
            back1[i] = get_back(i, 0);
            down1[i] = get_down(i, 0);
            front1[i] = get_front(i, 0);

            up2[i] = get_left(0, i);
            back2[i] = get_left(i, 0);
            down2[i] = get_left(2, i);
            front2[i] = get_left(i, 2);
        }
        for (int i = 0; i < 3; ++i){
            set_up(i, 0, back1[i]);
            set_back(i, 0, down1[i]);
            set_down(i, 0, front1[i]);
            set_front(i , 0, up1[i]);

            set_left(0, i, back2[i]);
            set_left(i, 0, down2[i]);
            set_left(2, i, front2[i]);
            set_left(i, 2, up2[i]);
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
            back2[i] = get_up(0, i);
            left2[i] = get_up(i, 0);
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
    void up_rotation_left(){
        int front1[3], front2[3], right1[3], right2[3], back1[3], back2[3], left1[3], left2[3];
        for (int i = 0; i < 3; ++i){
            front1[i] = get_front(0, i);
            right1[i] = get_right(0, i);
            back1[i] = get_back(0, i);
            left1[i] = get_left(0, i);

            front2[i] = get_up(2, i);
            right2[i] = get_up(i, 2);
            back2[i] = get_up(0, i);
            left2[i] = get_up(i, 0);
        }
        for (int i = 0; i < 3; ++i){
            set_right(0, i, back1[i]);
            set_back(0, i, left1[i]);
            set_left(0, i, front1[i]);
            set_front(0, i, right1[i]);

            set_up(i, 2, back2[i]);
            set_up(0, i,left2[i]);
            set_up(i, 0, front2[i]);
            set_up(2, i, right2[i]);
        }
    }

    void down_rotation_right(){
        int front1[3], front2[3], right1[3], right2[3], back1[3], back2[3], left1[3], left2[3];

        for (int i = 0; i < 3; ++i){
            front1[i] = get_front(2, i);
            right1[i] = get_right(2, i);
            back1[i] = get_back(2, i);
            left1[i] = get_left(2, i);

            front2[i] = get_down(0, i);
            right2[i] = get_down(i, 2);
            back2[i] = get_down(2, i);
            left2[i] = get_down(i, 0);
        }

        for (int i = 0; i < 3; ++i){
            set_right(2, i, front1[i]);
            set_back(2, i, right1[i]);
            set_left(2, i, back1[i]);
            set_front(2, i, left1[i]);

            set_down(0, i, left2[i]);
            set_down(i, 2, front2[i]);
            set_down(2, i, right2[i]);
            set_down(i, 0, back2[i]);
        }
    }
    void down_rotation_left(){
        int front1[3], front2[3], right1[3], right2[3], back1[3], back2[3], left1[3], left2[3];

        for (int i = 0; i < 3; ++i){
            front1[i] = get_front(2, i);
            right1[i] = get_right(2, i);
            back1[i] = get_back(2, i);
            left1[i] = get_left(2, i);

            front2[i] = get_down(0, i);
            right2[i] = get_down(i, 2);
            back2[i] = get_down(2, i);
            left2[i] = get_down(i, 0);
        }

        for (int i = 0; i < 3; ++i){
            set_right(2, i, back1[i]);
            set_back(2, i, left1[i]);
            set_left(2, i, front1[i]);
            set_front(2, i, right1[i]);

            set_down(0, i, right2[i]);
            set_down(i, 2, back2[i]);
            set_down(2, i, left2[i]);
            set_down(i, 0, front2[i]);
        }
    }

    void front_rotation_right(){
        int up1[3], up2[3], right1[3], right2[3], down1[3], down2[3], left1[3], left2[3];

        for (int i = 0; i < 3; ++i){
            up1[i] = get_up(2, i);
            right1[i] = get_right(i, 0);
            down1[i] = get_down(0, i);
            left1[i] = get_left(i, 2);

            up2[i] = get_front(0, i);
            right2[i] = get_front(i, 2);
            down2[i] = get_front(2, i);
            left2[i] = get_front(i, 0);
        }

        for (int i = 0; i < 3; ++i){
            set_up(2, i, left1[i]);
            set_right(i, 0, up1[i]);
            set_down(0, i, right1[i]);
            set_left(i, 2, down1[i]);

            set_front(0, i, left2[i]);
            set_front(i, 2, up2[i]);
            set_front(2, i, right2[i]);
            set_front(i, 0, down2[i]);
        }
    }
    void front_rotation_left(){
        int up1[3], up2[3], right1[3], right2[3], down1[3], down2[3], left1[3], left2[3];

        for (int i = 0; i < 3; ++i){
            up1[i] = get_up(2, i);
            right1[i] = get_right(i, 0);
            down1[i] = get_down(0, i);
            left1[i] = get_left(i, 2);

            up2[i] = get_front(0, i);
            right2[i] = get_front(i, 2);
            down2[i] = get_front(2, i);
            left2[i] = get_front(i, 0);
        }

        for (int i = 0; i < 3; ++i){
            set_up(2, i, right1[i]);
            set_right(i, 0, down1[i]);
            set_down(0, i, left1[i]);
            set_left(i, 2, up1[i]);

            set_front(0, i, right2[i]);
            set_front(i, 2, down2[i]);
            set_front(2, i, left2[i]);
            set_front(i, 0, up2[i]);
        }
    }

    void back_rotation_right(){
        int up1[3], up2[3], right1[3], right2[3], down1[3], down2[3], left1[3], left2[3];

        for (int i = 0; i < 3; ++i){
            up1[i] = get_up(0, i);
            right1[i] = get_right(i, 2);
            down1[i] = get_down(2, i);
            left1[i] = get_left(i, 0);

            up2[i] = get_back(0, i);
            right2[i] = get_back(i, 0);
            down2[i] = get_back(2, i);
            left2[i] = get_back(i, 2);
        }

        for (int i = 0; i < 3; ++i){
            set_up(0, i, left1[i]);
            set_right(i, 2, up1[i]);
            set_down(2, i, right1[i]);
            set_left(i, 0, down1[i]);

            set_back(0, i, left2[i]);
            set_back(i, 0, up2[i]);
            set_back(2, i, right2[i]);
            set_back(i, 2, down2[i]);
        }
    }
    void back_rotation_left(){
        int up1[3], up2[3], right1[3], right2[3], down1[3], down2[3], left1[3], left2[3];

        for (int i = 0; i < 3; ++i){
            up1[i] = get_up(0, i);
            right1[i] = get_right(i, 2);
            down1[i] = get_down(2, i);
            left1[i] = get_left(i, 0);

            up2[i] = get_back(0, i);
            right2[i] = get_back(i, 0);
            down2[i] = get_back(2, i);
            left2[i] = get_back(i, 2);
        }

        for (int i = 0; i < 3; ++i){
            set_up(0, i, right1[i]);
            set_right(i, 2, down1[i]);
            set_down(2, i, left1[i]);
            set_left(i, 0, up1[i]);

            set_back(0, i, right2[i]);
            set_back(i, 0, down2[i]);
            set_back(2, i, left2[i]);
            set_back(i, 2, up2[i]);
        }
    }

    void pif_paf_right(){
        right_rotation_up();
        up_rotation_left();
        right_rotation_down();
        up_rotation_right();
    }
    void pif_paf_left(){
        left_rotation_up();
        up_rotation_right();
        left_rotation_down();
        up_rotation_left();
    }
    void pif_paf_left_down(){
        left_rotation_down();
        down_rotation_right();
        left_rotation_up();
        down_rotation_left();
    }
    void pif_paf_back_right(){
        right_rotation_down();
        up_rotation_right();
        right_rotation_up();
        up_rotation_left();
    }
    void pif_paf_back_left(){
        left_rotation_down();
        up_rotation_left();
        left_rotation_up();
        up_rotation_right();
    }
    void pif_paf_front_left(){
        front_rotation_right();
        up_rotation_left();
        front_rotation_left();
        up_rotation_right();
    }
    void pif_paf_front_right(){
        front_rotation_left();
        up_rotation_right();
        front_rotation_right();
        up_rotation_left();
    }

    bool side_is_completed(int side[3][3]){
        for(int i = 0; i < 3; ++i){
            for (int j = 0; j < 3; ++j){
                if (side[i][j] != side[1][1])
                    return false;
            }
        }
        return true;
    }
    bool cube_is_completed(){
        bool rez = side_is_completed(front_);
        if (rez == false)
            return false;
        rez = side_is_completed(back_);
        if (rez == false)
            return false;
        rez = side_is_completed(right_);
        if (rez == false)
            return false;
        rez = side_is_completed(left_);
        if (rez == false)
            return false;
        rez = side_is_completed(up_);
        if (rez == false)
            return false;
        rez = side_is_completed(down_);
        if (rez == false)
            return false;
        return true;
    }

    bool down_cross_completed(){
        if (get_down(0, 1) == get_down(1, 0) == get_down(1, 1) == get_down(1, 2) == get_down(2, 1) && get_front(1, 1) == get_front(2, 1) && get_right(1, 1) == get_right(2, 1) && get_left(1, 1) == get_left(2, 1) && get_back(1, 1) == get_back(2, 1))
            return true;
        return false;
    }
    void down_cross(){ // all else
        if (down_cross_completed())
            break;
        
        int color = get_down(1, 1);

        for (int i = 1; i < 9; i += 2){
            //down
            if (get_down(i / 3, i % 3) == color){
                if (i / 3 == 0){
                    if (get_front(2, 1) == get_right(1, 1))
                        down_rotation_right();
                    else if (get_front(2, 1) == get_left(1, 1))
                        down_rotation_left();
                    else{
                        down_rotation_left();
                        down_rotation_left();
                    }

                    if (down_cross_completed())
                        break;
                }
                else if (i / 3 == 1 && i % 3 == 0){
                    if (get_left(2, 1) == get_front(1, 1))
                        down_rotation_right();
                    else if (get_left(2, 1) == get_back(1, 1))
                        down_rotation_left();
                    else{
                        down_rotation_left();
                        down_rotation_left();
                    }

                    if (down_cross_completed())
                        break;
                }
                else if (i / 3 == 1 && i % 3 == 2){
                    if (get_right(2, 1) == get_front(1, 1))
                        down_rotation_left();
                    else if (get_right(2, 1) == get_back(1, 1))
                        down_rotation_right();
                    else{
                        down_rotation_left();
                        down_rotation_left();
                    }

                    if (down_cross_completed())
                        break;
                }
                else{
                    if (get_back(2, 1) == get_right(1, 1))
                        down_rotation_left();
                    else if (get_back(2, 1) == get_left(1, 1))
                        down_rotation_right();
                    else{
                        down_rotation_left();
                        down_rotation_left();
                    }

                    if (down_cross_completed()){
                        break;
                    }
                }
            }

            // front
            if (get_front(i / 3, i % 3) == color){
                if (i / 3 == 0){
                    if (get_up(2, 1) == get_front(1, 1)){
                        up_rotation_right();
                        right_rotation_down();
                        front_rotation_left();
                    }
                    else if (get_up(2, 1) == get_right(1, 1)){
                        front_rotation_left();
                        right_rotation_down();
                    }
                    else if (get_up(2, 1) == get_left(1, 1)){
                        front_rotation_right();
                        left_rotation_down();
                    }
                    else{
                        up_rotation_right();
                        right_rotation_up();
                        back_rotation_right();
                    }

                    if (down_cross_completed()){
                        break;
                    }
                }
                else if (i / 3 == 1 && i % 3 == 0){
                    if (get_left(1, 2) == get_front(1, 1)){
                        left_rotation_up();
                        up_rotation_right();
                        front_rotation_left();
                        front_rotation_left();
                    }
                    else if (get_left(1, 2) == get_left(1, 1))
                        left_rotation_down();
                    else if (get_left(1, 2) == get_right(1, 1)){
                        front_rotation_left();
                        front_rotation_left();
                        right_rotation_down();
                    }
                    else{
                        left_rotation_up();
                        up_rotation_left();
                        back_rotation_left();
                        back_rotation_left();
                    }

                    if (down_cross_completed()){
                        break;
                    }
                }
                else if (i / 3 == 1 && i % 3 == 2){
                    if (get_right(1, 0) == get_front(1, 1)){
                        right_rotation_up();
                        up_rotation_left();
                        front_rotation_left();
                        front_rotation_left();
                    }
                    else if (get_right(1, 0) == get_right(1, 1))
                        right_rotation_down();
                    else if (get_right(1, 0) == get_left(1, 1)){
                        front_rotation_left();
                        front_rotation_left();
                        left_rotation_down();
                    }
                    else{
                        right_rotation_up();
                        up_rotation_right();
                        back_rotation_left();
                        back_rotation_left();
                    }

                    if (down_cross_completed()){
                        break;
                    }
                }
                else {
                    if (get_down(0, 1) == get_front(1, 1)){
                        front_rotation_left();
                        front_rotation_left();
                        up_rotation_left();
                        left_rotation_down();
                        front_rotation_right();
                    }
                    else if (get_down(0, 1) == get_left(1, 1)){
                        front_rotation_left();
                        left_rotation_down();
                    }
                    else if (get_down(0, 1) == get_right(1, 1)){
                        front_rotation_right();
                        right_rotation_down();
                    }
                    else{
                        front_rotation_right();
                        right_rotation_up();
                        up_rotation_left();
                        back_rotation_left();
                        back_rotation_left();
                    }

                    if (down_cross_completed()){
                        break;
                    }
                }
            }

            //back
            if (get_back(i / 3, i % 3) == color){
                if (i / 3 == 0){
                    if (get_up(0, 1) == get_right(1, 1)){
                        back_rotation_right();
                        right_rotation_up();
                    }
                    else if (get_up(0, 1) == get_front(1, 1)){
                        up_rotation_left();
                        right_rotation_down();
                        front_rotation_left();
                    }
                    else if (get_up(0, 1) == get_left(1, 1)){
                        back_rotation_left();
                        left_rotation_up();
                    }
                    else{
                        up_rotation_right();
                        left_rotation_up();
                        back_rotation_left();
                    }

                    if (down_cross_completed())
                        break;
                }
                else if (i / 3 == 1 && i % 3 == 0){
                    if (get_right(1, 2) == get_front(1, 1)){
                        back_rotation_left();
                        up_rotation_left();
                        right_rotation_down();
                        front_rotation_left();
                    }
                    else if (get_right(1, 2) == get_left(1, 1)){
                        back_rotation_left();
                        back_rotation_left();
                        left_rotation_up();
                    }
                    else if (get_right(1, 2) == get_right(1, 1))
                        right_rotation_up();
                    else{
                        right_rotation_down();
                        up_rotation_right();
                        back_rotation_left()
                        back_rotation_left();
                    }

                    if (down_cross_completed()){
                        break;
                    }
                }
                else if (i / 3 == 1 && i % 3 == 2){
                    if (get_left(1, 0) == get_left(1, 1))
                        left_rotation_up();
                    else if (get_left(1, 0) == get_right(1, 1)){
                        back_rotation_left();
                        back_rotation_left();
                        right_rotation_up();
                    }
                    else if (get_left(1, 0) == get_front(1, 1)){
                        left_rotation_down();
                        up_rotation_right();
                        front_rotation_left();
                        front_rotation_left();
                    }
                    else{
                        left_rotation_down();
                        up_rotation_left();
                        back_rotation_left();
                        back_rotation_left();
                    }

                    if (down_cross_completed())
                        break;
                }
                else{
                    if (get_down(2, 1) == get_left(1, 1)){
                        back_rotation_right();
                        left_rotation_up();
                    }
                    else if (get_down(2, 1) == get_right(1, 1)){
                        back_rotation_left();
                        right_rotation_up();
                    }
                    else if(get_down(2, 1) == get_front(1, 1)){
                        down_rotation_left();
                        right_rotation_up();
                        down_rotation_right();
                        front_rotation_right();
                    }
                    else{
                        down_rotation_right();
                        left_rotation_down();
                        down_rotation_left();
                        back_rotation_left();
                    }

                    if (down_cross_completed())
                        break;
                }
            }

            // right
            if (get_right(i / 3, i % 3) == color){
                if (i / 3 == 0){
                    if (get_up(1, 2) == get_front(1, 1)){
                        right_rotation_down();
                        front_rotation_right();
                    }
                    else if (get_up(1, 2) == get_back(1, 1)){
                        right_rotation_up();
                        back_rotation_right();
                    }
                    else if (get_up(1, 2) == get_left(1, 1)){
                        up_rotation_left();
                        front_rotation_left();
                        left_rotation_down();
                    }
                    else{
                        up_rotation_left();
                        front_rotation_right();
                        right_rotation_down();
                        front_rotation_left();
                    }

                    if (down_cross_completed())
                        break;
                }
                else if (i / 3 == 1 && i % 3 == 0){
                    if (get_front(1, 2) == get_left(1, 1)){
                        front_rotation_left();
                        up_rotation_left();
                        left_rotation_down();
                        left_rotation_down();
                    }
                    else if (get_front(1, 2) == get_back(1, 1)){
                        right_rotation_up();
                        right_rotation_up();
                        back_rotation_right();
                    }
                    else if (get_front(1, 2) == get_front(1, 1))
                        front_rotation_right();
                    else{
                        front_rotation_left();
                        up_rotation_right();
                        right_rotation_up();
                        right_rotation_up();
                    }

                    if (down_cross_completed())
                        break;
                }
                else if (i / 3 == 1 && i % 3 == 2){
                    if (get_back(1, 0) == get_front(1, 1)){
                        right_rotation_down();
                        right_rotation_down();
                        front_rotation_right();
                    }
                    else if (get_back(1, 0) == get_back(1, 1))
                        back_rotation_right();
                    else if (get_back(1, 0) == get_left(1, 1)){
                        back_rotation_left();
                        up_rotation_right();
                        left_rotation_down();
                        left_rotation_down();
                    }
                    else{
                        back_rotation_left();
                        up_rotation_left();
                        right_rotation_down();
                        right_rotation_down();
                    }

                    if (down_cross_completed())
                        break;
                }
                else{
                    if (get_down(1, 2) == get_back(1, 1)){
                        right_rotation_down();
                        back_rotation_right();
                    }
                    else if (get_down(1, 2) == get_front(1, 1)){
                        right_rotation_up();
                        front_rotation_right();
                    }
                    else if (get_down(1, 2) == get_left(1, 1)){
                        right_rotation_up();
                        front_rotation_left();
                        up_rotation_left();
                        left_rotation_down();
                        left_rotation_down();
                    }
                    else{
                        right_rotation_up();
                        front_rotation_left();
                        up_rotation_right();
                        right_rotation_down();
                        right_rotation_down();
                    }

                    if (down_cross_completed())
                        break;
                }
            }

            // left
            if (get_left(i / 3, i % 3) == color){
                if (i / 3 == 0){
                    if (get_up(1, 0) == get_right(1, 1)){
                        up_rotation_left();
                        back_rotation_right();
                        right_rotation_up();
                    }
                    else if (get_up(1, 0) == get_back(1, 1)){
                        left_rotation_up();
                        back_rotation_left();
                    }
                    else if (get_up(1, 0) == get_front(1, 1)){
                        left_rotation_down();
                        front_rotation_left();
                    }
                    else{
                        up_rotation_left();
                        back_rotation_left();
                        left_rotation_up();
                    }

                    if (down_cross_completed())
                        break;
                }
                else if (i / 3 == 1 && i % 3 == 0){
                    if (get_back(1, 2) == get_back(1, 1))
                        back_rotation_left();
                    else if (get_back(1, 2) == get_right(1, 1)){
                        back_rotation_right();
                        up_rotation_left();
                        right_rotation_down()
                        right_rotation_down();
                    }
                    else if (get_back(1, 2) == get_front(1, 1)){
                        left_rotation_down();
                        left_rotation_down();
                        front_rotation_left();
                    }
                    else{
                        back_rotation_right();
                        up_rotation_right();
                        left_rotation_down();
                        left_rotation_down();
                    }

                    if (down_cross_completed())
                        break;
                }
                else if (i / 3 == 1 && i % 3 == 2){
                    if (get_front(1, 0) == get_front(1, 1))
                        front_rotation_left();
                    else if (get_front(1, 0) == get_back(1, 1)){
                        left_rotation_down();
                        left_rotation_down();
                        back_rotation_left();
                    }
                    else if (get_front(1, 0) == get_right(1, 1)){
                        front_rotation_right();
                        up_rotation_right();
                        right_rotation_down();
                        right_rotation_down();
                    }
                    else{
                        front_rotation_right();
                        up_rotation_left();
                        left_rotation_down();
                        left_rotation_down();
                    }

                    if (down_cross_completed())
                        break;
                }
                else {
                    if (get_down(1, 0) == get_back(1, 1)){
                        left_rotation_down();
                        back_rotation_left();
                    }
                    else if (get_down(1, 0) == get_front(1, 1)){
                        left_rotation_up();
                        front_rotation_left();
                    }
                    else if (get_down(1, 0) == get_right(1, 1)){
                        left_rotation_up();
                        front_rotation_right();
                        up_rotation_right();
                        right_rotation_down();
                        right_rotation_down();
                    }
                    else{
                        down_rotation_right();
                        front_rotation_right();
                        left_rotation_down();
                    }

                    if (down_cross_completed())
                        break;
                }
            }

            // up
            if (get_up(i / 3, i % 3) == color){
                if (i / 3 == 0){
                    if (get_back(0, 1) == get_back(1, 1)){
                        back_rotation_left();
                        back_rotation_left();
                    }
                    else if (get_back(0, 1) == get_right()){
                        up_rotation_left();
                        right_rotation_down();
                        right_rotation_down();
                    }
                    else if (get_back(0, 1) == get_left()){
                        up_rotation_right();
                        left_rotation_down();
                        left_rotation_down();
                    }
                    else{
                        up_rotation_left();
                        up_rotation_left();
                        front_rotation_left();
                        front_rotation_left();
                    }

                    if (down_cross_completed())
                        break;
                }
                else if (i / 3 == 1 && i % 3 == 0){
                    if (get_left(0, 1) == get_left(1, 1)){
                        left_rotation_down();
                        left_rotation_down();
                    }
                    else if (get_left(0, 1) == get_front(1, 1)){
                        up_rotation_right();
                        front_rotation_left();
                        front_rotation_left();
                    }
                    else if (get_left(0, 1) == get_back(1, 1)){
                        up_rotation_left();
                        back_rotation_left();
                        back_rotation_left();
                    }
                    else{
                        up_rotation_left();
                        up_rotation_left();
                        right_rotation_down();
                        right_rotation_down();
                    }

                    if (down_cross_completed())
                        break;
                }
                else if (i / 3 == 1 && i % 3 == 2){
                    if (get_right(0, 1) == get_right(1, 1)){
                        right_rotation_down();
                        right_rotation_down();
                    }
                    else if (get_right(0, 1) == get_front(1, 1)){
                        up_rotation_left();
                        front_rotation_left();
                        front_rotation_left();
                    }
                    else if (get_right(0, 1) == get_back(1, 1)){
                        up_rotation_right();
                        back_rotation_left();
                        back_rotation_left();
                    }
                    else{
                        up_rotation_left();
                        up_rotation_left();
                        left_rotation_down();
                        left_rotation_down();
                    }

                    if (down_cross_completed())
                        break;
                }
                else{
                    if (get_front(0, 1) == get_front(1, 1)){
                        front_rotation_left();
                        front_rotation_left();
                    }
                    else if (get_front(0, 1) == get_right(1, 1)){
                        up_rotation_right();
                        right_rotation_down();
                        right_rotation_down();
                    }
                    else if (get_front(0, 1) == get_left(1, 1)){
                        up_rotation_left();
                        left_rotation_down();
                        left_rotation_down();
                    }
                    else{
                        up_rotation_left();
                        up_rotation_left();
                        back_rotation_left();
                        back_rotation_left();
                    }

                    if (down_cross_completed())
                        break;
                }
            }
        }

        if (!down_cross_completed()){
            down_cross();
        }
    }

    bool down_side_completed(){
        int color = get_down(1, 1);
        for (int i = 0; i < 9; ++i){
            if (get_down(i / 3, i % 3) != color)
                return false;
        }
        return true;
    }
    void down_side(){
        if (down_side_completed)
            return;

        int color = get_down(1, 1);
        
        for (int i = 0; i < 9; i += 2){
            // down
            if (get_down(i / 3, i % 3) == color){
                if (i / 3 == 0 && i % 3 == 0){
                    if(get_left(2, 2) == get_back(1, 1) && get_front(2, 0) == get_left(1, 1)){
                        pif_paf_front_left();
                        up_rotation_left();
                        while (get_back(2, 2) != get_back(1, 1) || get_left(2, 0) != get_left(1, 1))
                            pif_paf_back_left();
                    }
                    else if (get_left(2, 2) == get_front(1, 1) && get_front(2, 0) == get_right(1, 1)){
                        pif_paf_front_left();
                        up_rotation_right();
                        while (get_front(2, 2) != get_front(1, 1) || get_right(2, 0) != get_right(1, 1))
                            pif_paf_front_right();
                    }
                    else if (get_left(2, 2) == get_right(1, 1) && get_front(2, 0) == get_back(1, 1)){
                        pif_paf_front_left();
                        up_rotation_left();
                        up_rotation_left();
                        while (get_right(2, 2) != get_right(1, 1) || get_back(2, 0) != get_back(1, 1))
                            pif_paf_back_right();
                    }

                    if (down_side_completed())
                        break;
                }
                else if (i / 3 == 0 && i % 3 == 2){
                    if (get_front(2, 2) == get_left(1, 1) && get_right(2, 0) == get_front(1, 1)){
                    pif_paf_right();
                    up_rotation_left();
                    while (get_left(2, 2) != get_left(1, 1) || get_front(2, 0) != get_front(1, 1))
                        pif_paf_left();
                }
                    else if (get_front(2, 2) == get_right(1, 1) && get_right(2, 0) == get_back(1, 1)){
                    pif_paf_right();
                    up_rotation_right();
                    while (get_right(2, 2) != get_right(1, 1) || get_back(2, 0) != get_back(1, 1))
                        pif_paf_back_right();
                }
                    else if (get_front(2, 2) == get_back(1, 1) && get_right(2, 0) == get_left(1, 1)){
                        pif_paf_right();
                        up_rotation_left();
                        up_rotation_left();
                        while (get_back(2, 2) != get_back(1, 1) || get_left(2, 0) != get_left(1, 1))
                            pif_paf_back_left();
                    }

                    if (down_side_completed())
                        break;
                }
                else if (i / 3 == 2 && i % 3 == 0){
                    if (get_back(2, 2) == get_left(1, 1) && get_left(2, 0) == get_front(1, 1)){
                        pif_paf_back_left();
                        up_rotation_right();
                        while (get_left(2, 2) != get_left(1, 1) || get_front(2, 0) != get_front(1, 1))
                            pif_paf_left();
                    }
                    else if (get_back(2, 2) == get_front(1, 1) && get_left(2, 0) == get_right(1, 1)){
                        pif_paf_back_left();
                        up_rotation_left();
                        up_rotation_left();
                        while (get_front(2, 2) != get_front(1, 1) || get_right(2, 0) != get_right(1, 1))
                            pif_paf_right();
                    }
                    else if (get_back(2, 2) == get_right(1, 1) && get_left(2, 0) == get_back(1, 1)){
                        pif_paf_back_left();
                        up_rotation_left();
                        while (get_right(2, 2) != get_right(1, 1) || get_back(2, 0) != get_back(1, 1))
                            pif_paf_back_right();
                    }

                    if (down_side_completed())
                        break;
                }
                else{
                    if (get_right(2, 2) == get_front(1, 1) && get_back(2, 0) == get_right(1, 1)){
                        pif_paf_back_right();
                        up_rotation_left();
                        while (get_front(2, 2) != get_front(1, 1) || get_right(2, 0) != get_right(1, 1))
                            pif_paf_right();
                    }
                    else if (get_right(2, 2) == get_back(1, 1) && get_back(2, 0) == get_left(1, 1)){
                        pif_paf_back_right();
                        up_rotation_right();
                        while (get_back(2, 2) != get_back(1, 1) || get_left(2, 0) != get_left(1, 1))
                            pif_paf_back_left();
                    }
                    else if (get_right(2, 2) == get_left(1, 1) && get_back(2, 0) == get_front(1, 1)){
                        pif_paf_back_right();
                        up_rotation_left();
                        up_rotation_left();
                        while (get_left(2, 2) != get_left(1, 1) || get_front(2, 0) != get_front(1, 1))
                            pif_paf_left();
                    }

                    if (down_side_completed())
                        break;
                }
            }

            // front
            
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
    std::cout << "\n\n";
    
    int front[3][3] = {{6, 6, 6}, {6, 6, 6}, {6, 6, 6}};
    int back[3][3] = {{4, 4, 4}, {4, 4, 4}, {4, 4, 4}};
    int right[3][3] = {{3, 3, 3}, {3, 3, 3}, {3, 3, 3}};
    int left[3][3] = {{5, 5, 5}, {5, 5, 5}, {5, 5, 5}};
    int up[3][3] = {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}};
    int down[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};

    cube cub(front, back, right, left, up, down);
    std::cout << cub << "\n\n";
    std::cout << cub.down_cross_completed() << "\n\n";

    /* cub.right_rotation_up();
    std::cout << cub << "\n\n";
    
    cub.right_rotation_down();
    std::cout << cub << "\n\n";

    cub.left_rotation_down();
    std::cout << cub << "\n\n";

    cub.left_rotation_up();
    std::cout << cub << "\n\n";

    cub.up_rotation_right();
    std::cout << cub << "\n\n";

    cub.up_rotation_left();
    std::cout << cub << "\n\n";

    cub.down_rotation_right();
    std::cout << cub << "\n\n";

    cub.down_rotation_left();
    std::cout << cub << "\n\n";

    cub.back_rotation_right();
    std::cout << cub << "\n\n";

    cub.back_rotation_left();
    std::cout << cub << "\n\n"; */
}