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

    cube(){
        for (int i = 0; i < 9; ++ i){
            set_front(i / 3, i % 3, 6);
            set_back(i / 3, i % 3, 4);
            set_right(i / 3, i % 3, 3);
            set_left(i / 3, i % 3, 5);
            set_up(i / 3, i % 3, 2);
            set_down(i / 3, i % 3, 1);
        }
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
        int front1[3], front2[3], up1[3], up2[3], back1[3], back2[3], down1[3], down2[3];
        for (int i = 0; i < 3; ++i){
            front1[i] = get_front(i, 2);
            up1[i] = get_up(i, 2);
            back1[i] = get_back(i, 0);
            down1[i] = get_down(i, 2);

            front2[i] = get_right(i, 0);
            up2[i] = get_right(0, i);
            back2[i] = get_right(i, 2);
            down2[i] = get_right(2, i);
        }
        std::swap(front2[0], front2[2]);
        std::swap(back2[0], back2[2]);
        std::swap(back1[0], back1[2]);
        std::swap(up1[0], up1[2]);
        for (int i = 0; i < 3; ++ i){
            set_up(i, 2, front1[i]);
            set_back(i, 0, up1[i]);
            set_down(i, 2, back1[i]);
            set_front(i, 2, down1[i]);

            set_right(0, i, front2[i]);
            set_right(i, 2, up2[i]);
            set_right(2, i, back2[i]);
            set_right(i, 0, down2[i]);
        }
    }
    void right_rotation_down(){ 
        right_rotation_up();
        right_rotation_up();
        right_rotation_up();
    }

    void left_rotation_up(){
        int front1[3], front2[3], up1[3], up2[3], back1[3], back2[3], down1[3], down2[3];
        for (int i = 0; i < 3; ++i){
            front1[i] = get_front(i, 0);
            up1[i] = get_up(i, 0);
            back1[i] = get_back(i, 2);
            down1[i] = get_down(i, 0);

            front2[i] = get_left(i, 2);
            up2[i] = get_left(0, i);
            back2[i] = get_left(i, 0);
            down2[i] = get_left(2, i);
        }
        std::swap(up1[0], up1[2]);
        std::swap(back1[0], back1[2]);
        std::swap(down2[0], down2[2]);
        std::swap(up2[0], up2[2]);
        for (int i = 0; i < 3; ++i){
            set_front(i, 0, down1[i]);
            set_up(i, 0, front1[i]);
            set_back(i, 2, up1[i]);
            set_down(i, 0, back1[i]);

            set_left(i, 2, down2[i]);
            set_left(0, i, front2[i]);
            set_left(i, 0, up2[i]);
            set_left(2, i, back2[i]);
        }
    }
    void left_rotation_down(){
        left_rotation_up();
        left_rotation_up();
        left_rotation_up();
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
        std::swap(front2[0], front2[2]);
        std::swap(back2[0], back2[2]);
        for (int i = 0; i < 3; ++i){
            set_front(0, i, left1[i]);
            set_right(0, i, front1[i]);
            set_back(0, i, right1[i]);
            set_left(0, i, back1[i]);

            set_up(2, i, left2[i]);
            set_up(i, 2, front2[i]);
            set_up(0, i, right2[i]);
            set_up(i, 0, back2[i]);
        }
    }
    void up_rotation_left(){
        up_rotation_right();
        up_rotation_right();
        up_rotation_right();
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
        std::swap(left2[0], left2[2]);
        std::swap(right2[0], right2[2]);
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
        down_rotation_right();
        down_rotation_right();
        down_rotation_right();
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
        std::swap(left1[0], left1[2]);
        std::swap(right1[0], right1[2]);
        std::swap(left2[0], left2[2]);
        std::swap(right2[0], right2[2]);
        for (int i = 0; i < 3; ++i){
            set_up(2, i, left1[i]);
            set_right(i, 0, up1[i]);
            set_down(0, i,right1[i]);
            set_left(i, 2, down1[i]);

            set_front(0, i, left2[i]);
            set_front(i, 2, up2[i]);
            set_front(2, i, right2[i]);
            set_front(i, 0, down2[i]);
        }
    }
    void front_rotation_left(){
        front_rotation_right();
        front_rotation_right();
        front_rotation_right();
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
        std::swap(left1[0], left1[2]);
        std::swap(right1[0], right1[2]);
        std::swap(up2[0], up2[2]);
        std::swap(down2[0], down2[2]);
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
        back_rotation_right();
        back_rotation_right();
        back_rotation_right();
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
        back_rotation_left();
        up_rotation_left();
        back_rotation_right();
        up_rotation_right();
    }
    void pif_paf_back_left(){
        back_rotation_right();
        up_rotation_right();
        back_rotation_left();
        up_rotation_left();
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
    void pif_paf_left_back(){
        left_rotation_down();
        up_rotation_left();
        left_rotation_up();
        up_rotation_right();
    }
    void pif_paf_right_back(){
        right_rotation_down();
        up_rotation_right();
        right_rotation_up();
        up_rotation_left();
    }
    void pif_paf_back_down(){
        back_rotation_left();
        down_rotation_right();
        back_rotation_right();
        down_rotation_left();
    }
    void pif_paf_right_down(){
        right_rotation_up();
        down_rotation_right();
        right_rotation_down();
        down_rotation_left();
    }
    void pif_paf_front_down(){
        front_rotation_right();
        down_rotation_right();
        front_rotation_left();
        down_rotation_left();
    }

    void wrong_cube(){
        std::cout << "\n\n----------wrong complantation-----------\n\n";
        exit(-1);
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
        if (side_is_completed(front_) && side_is_completed(back_) && side_is_completed(up_) && side_is_completed(down_) && side_is_completed(right_) && side_is_completed(left_))
            return true;
        return false;
    }

    bool down_cross_completed(){
        if (get_down(0, 1) == get_down(1, 0) == get_down(1, 1) == get_down(1, 2) == get_down(2, 1) && get_front(1, 1) == get_front(2, 1) && get_right(1, 1) == get_right(2, 1) && get_left(1, 1) == get_left(2, 1) && get_back(1, 1) == get_back(2, 1))
            return true;
        return false;
    }
    void down_cross(){
        if (down_cross_completed())
            return;
        
        int color = get_down(1, 1);

        for (int i = 1; i < 9; i += 2){
            //down
            if (get_down(i / 3, i % 3) == color){
                if (i / 3 == 0){
                    if (get_front(2, 1) == get_right(1, 1))
                        down_rotation_right();
                    else if (get_front(2, 1) == get_left(1, 1))
                        down_rotation_left();
                    else if (get_front(2, 1) == get_back(1, 1)){
                        down_rotation_left();
                        down_rotation_left();
                    }
                    /* else if (get_front(2, 1) != get_front(1, 1))
                        wrong_cube(); */

                    if (down_cross_completed())
                        return;
                }
                else if (i / 3 == 1 && i % 3 == 0){
                    if (get_left(2, 1) == get_front(1, 1))
                        down_rotation_right();
                    else if (get_left(2, 1) == get_back(1, 1))
                        down_rotation_left();
                    else if (get_left(2, 1) == get_right(1, 1)){
                        down_rotation_left();
                        down_rotation_left();
                    }
                    /* else if (get_left(2, 1) != get_left(1, 1))
                        wrong_cube(); */

                    if (down_cross_completed())
                        return;
                }
                else if (i / 3 == 1 && i % 3 == 2){
                    if (get_right(2, 1) == get_front(1, 1))
                        down_rotation_left();
                    else if (get_right(2, 1) == get_back(1, 1))
                        down_rotation_right();
                    else if (get_right(2, 1) == get_left(1, 1)){
                        down_rotation_left();
                        down_rotation_left();
                    }
                    /* else if (get_right(2, 1) != get_right(1, 1))
                        wrong_cube(); */

                    if (down_cross_completed())
                        return;
                }
                else{
                    if (get_back(2, 1) == get_right(1, 1))
                        down_rotation_left();
                    else if (get_back(2, 1) == get_left(1, 1))
                        down_rotation_right();
                    else if (get_back(2, 1) == get_front(1, 1)){
                        down_rotation_left();
                        down_rotation_left();
                    }
                    /* else if (get_back(2, 1) != get_back(1, 1))
                        wrong_cube(); */

                    if (down_cross_completed()){
                        return;
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
                    else if (get_up(2, 1) == get_back(1, 1)){
                        up_rotation_right();
                        right_rotation_up();
                        back_rotation_right();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_cross_completed()){
                        return;
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
                    else if (get_left(1, 2) == get_back(1, 1)){
                        left_rotation_up();
                        up_rotation_left();
                        back_rotation_left();
                        back_rotation_left();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_cross_completed()){
                        return;
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
                    else if (get_right(1, 0) == get_back(1, 1)){
                        right_rotation_up();
                        up_rotation_right();
                        back_rotation_left();
                        back_rotation_left();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_cross_completed()){
                        return;
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
                    else if (get_down(0, 1) == get_back(1, 1)){
                        front_rotation_right();
                        right_rotation_up();
                        up_rotation_left();
                        back_rotation_left();
                        back_rotation_left();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_cross_completed()){
                        return;
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
                    else if (get_up(0, 1) == get_back(1, 1)){
                        up_rotation_right();
                        left_rotation_up();
                        back_rotation_left();
                    }
                    /* else{
                        wrong_cube();
                    } */

                    if (down_cross_completed())
                        return;
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
                    else if (get_right(1, 2) == get_back(1, 1)){
                        right_rotation_down();
                        up_rotation_right();
                        back_rotation_left();
                        back_rotation_left();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_cross_completed()){
                        return;
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
                    else if (get_left(1, 0) == get_back(1, 1)){
                        left_rotation_down();
                        up_rotation_left();
                        back_rotation_left();
                        back_rotation_left();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_cross_completed())
                        return;
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
                    else if (get_down(2, 1) == get_back(1, 1)){
                        down_rotation_right();
                        left_rotation_down();
                        down_rotation_left();
                        back_rotation_left();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_cross_completed())
                        return;
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
                    else if (get_up(1, 2) == get_right(1, 1)){
                        up_rotation_left();
                        front_rotation_right();
                        right_rotation_down();
                        front_rotation_left();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_cross_completed())
                        return;
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
                    else if (get_front(1, 2) == get_right(1, 1)){
                        front_rotation_left();
                        up_rotation_right();
                        right_rotation_up();
                        right_rotation_up();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_cross_completed())
                        return;
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
                    else if (get_back(1, 0) == get_right(1, 1)){
                        back_rotation_left();
                        up_rotation_left();
                        right_rotation_down();
                        right_rotation_down();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_cross_completed())
                        return;
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
                    else if (get_down(1, 2) == get_right(1, 1)){
                        right_rotation_up();
                        front_rotation_left();
                        up_rotation_right();
                        right_rotation_down();
                        right_rotation_down();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_cross_completed())
                        return;
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
                    else if (get_up(1, 0) == get_left(1, 1)){
                        up_rotation_left();
                        back_rotation_left();
                        left_rotation_up();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_cross_completed())
                        return;
                }
                else if (i / 3 == 1 && i % 3 == 0){
                    if (get_back(1, 2) == get_back(1, 1))
                        back_rotation_left();
                    else if (get_back(1, 2) == get_right(1, 1)){
                        back_rotation_right();
                        up_rotation_left();
                        right_rotation_down();
                        right_rotation_down();
                    }
                    else if (get_back(1, 2) == get_front(1, 1)){
                        left_rotation_down();
                        left_rotation_down();
                        front_rotation_left();
                    }
                    else if (get_back(1, 2) == get_left(1, 1)){
                        back_rotation_right();
                        up_rotation_right();
                        left_rotation_down();
                        left_rotation_down();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_cross_completed())
                        return;
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
                    else if (get_front(1, 0) == get_left(1, 1)){
                        front_rotation_right();
                        up_rotation_left();
                        left_rotation_down();
                        left_rotation_down();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_cross_completed())
                        return;
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
                    else if (get_down(1, 0) == get_left(1, 1)){
                        down_rotation_right();
                        front_rotation_right();
                        left_rotation_down();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_cross_completed())
                        return;
                }
            }

            // up
            if (get_up(i / 3, i % 3) == color){
                if (i / 3 == 0){
                    if (get_back(0, 1) == get_back(1, 1)){
                        back_rotation_left();
                        back_rotation_left();
                    }
                    else if (get_back(0, 1) == get_right(1, 1)){
                        up_rotation_left();
                        right_rotation_down();
                        right_rotation_down();
                    }
                    else if (get_back(0, 1) == get_left(1, 1)){
                        up_rotation_right();
                        left_rotation_down();
                        left_rotation_down();
                    }
                    else if (get_back(0, 1) == get_front(1, 1)){
                        up_rotation_left();
                        up_rotation_left();
                        front_rotation_left();
                        front_rotation_left();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_cross_completed())
                        return;
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
                    else if (get_left(0, 1) == get_right(1, 1)){
                        up_rotation_left();
                        up_rotation_left();
                        right_rotation_down();
                        right_rotation_down();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_cross_completed())
                        return;
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
                    else if (get_right(0, 1) == get_left(1, 1)){
                        up_rotation_left();
                        up_rotation_left();
                        left_rotation_down();
                        left_rotation_down();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_cross_completed())
                        return;
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
                    else if (get_front(0, 1) == get_back(1, 1)){
                        up_rotation_left();
                        up_rotation_left();
                        back_rotation_left();
                        back_rotation_left();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_cross_completed())
                        return;
                }
            }
        }

        if (!down_cross_completed())
            down_cross();
    }

    bool down_side_completed(){
        int color = get_down(1, 1);
        for (int i = 0; i < 9; ++i){
            if (get_down(i / 3, i % 3) != color)
                return false;
        }
        int back = get_back(1, 1), front = get_front(1, 1), right = get_right(1, 1), left = get_left(1, 1);
        for (int i = 0; i < 3; ++i){
            if (get_front(2, i) != front)
                return false;
            if (get_back(2, i) != back)
                return false;
            if (get_right(2, i) != right)
                return false;
            if (get_left(2, i) != left)
                return false;
        }
        return true;
    }
    void down_side(){
        int count = 0;
        if (down_side_completed())
            return;

        int color = get_down(1, 1);
        
        for (int i = 0; i < 9; i += 2){
            // down
            if (get_down(i / 3, i % 3) == color && i != 4){
                if (i == 0){
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
                            pif_paf_right();
                    }
                    else if (get_left(2, 2) == get_right(1, 1) && get_front(2, 0) == get_back(1, 1)){
                        pif_paf_front_left();
                        up_rotation_left();
                        up_rotation_left();
                        while (get_right(2, 2) != get_right(1, 1) || get_back(2, 0) != get_back(1, 1))
                            pif_paf_back_right();
                    }
                    /* else if (get_front(2, 0) != get_front(1, 1) || get_left(2, 2) != get_left(1, 1))
                        wrong_cube(); */

                    if (down_side_completed())
                        return;
                }
                else if (i == 2){
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
                    /* else if (get_front(2, 2) != get_front(1, 1) || get_right(2, 0) != get_right(1, 1))
                        wrong_cube(); */

                    if (down_side_completed())
                        return;
                }
                else if (i == 6){
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
                    /* else if (get_back(2, 2) != get_back(1, 1) || get_left(2, 0) != get_left(1, 1))
                        wrong_cube(); */

                    if (down_side_completed())
                        return;
                }
                else if (i == 8){
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
                    /* else if (get_right(2, 2) != get_right(1, 1) || get_back(2, 0) != get_back(1, 1))
                        wrong_cube(); */

                    if (down_side_completed())
                        return;
                }
            }

            // front
            if (get_front(i / 3, i % 3) == color && i != 4){
                if (i == 0){
                    if (get_up(2, 0) == get_back(1, 1) && get_left(0, 2) == get_right(1, 1)){
                        up_rotation_left();
                        up_rotation_left();
                        while (get_right(2, 2) != get_right(1, 1) || get_back(2, 0) != get_back(1, 1))
                            pif_paf_back_right();
                    }
                    else if (get_up(2, 0) == get_right(1, 1) && get_left(0, 2) == get_front(1, 1)){
                        up_rotation_right();
                        while (get_front(2, 2) != get_front(1, 1) || get_right(2, 0) != get_right(1, 1))
                            pif_paf_right();
                    }
                    else if (get_up(2, 0) == get_left(1, 1) && get_left(0, 2) == get_back(1, 1)){
                        up_rotation_left();
                        while (get_back(2, 2) != get_back(1, 1) || get_left(2, 0) != get_left(1, 1))
                            pif_paf_back_left();
                    }
                    else if (get_up(2, 0) == get_front(1, 1) && get_left(0, 2) == get_left(1, 1)){
                        while (get_left(2, 2) != get_left(1, 1) || get_front(2, 0) != get_front(1, 1))
                            pif_paf_left();
                    }
                    /* else 
                        wrong_cube(); */

                    if (down_side_completed())
                        return;
                }
                else if (i == 2){
                    if (get_up(2, 2) == get_right(1, 1) && get_right(0, 0) == get_back(1, 1)){
                        up_rotation_right();
                        while (get_back(2, 0) != get_back(1, 1) || get_right(2, 2) != get_right(1, 1))
                            pif_paf_back_right();
                    }
                    else if (get_up(2, 2) == get_left(1, 1) && get_right(0, 0) == get_front(1, 1)){
                        up_rotation_left();
                        while (get_left(2, 2) != get_left(1, 1) || get_front(2, 0) != get_front(1, 1))
                            pif_paf_left();
                    }
                    else if (get_up(2, 2) == get_back(1, 1) && get_right(0, 0) == get_left(1, 1)){
                        up_rotation_left();
                        up_rotation_left();
                        while(get_back(2, 2) != get_back(1, 1) || get_left(2, 0) != get_left(1, 1))
                            pif_paf_back_left();
                    }
                    else if (get_up(2, 2) == get_front(1, 1) && get_right(0, 0) == get_right(1, 1)){
                        while(get_front(2, 2) != get_front(1, 1) || get_right(2, 0) != get_right(1, 1))
                            pif_paf_right();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_side_completed())
                        return;
                }
                else if (i == 6){
                    if (get_left(2, 2) == get_right(1, 1) && get_down(0, 0) == get_front(1, 1)){
                        pif_paf_left();
                        up_rotation_right();
                        while (get_right(2, 0) != get_right(1, 1) || get_front(2, 2) != get_front(1, 1))
                            pif_paf_right();
                    }
                    else if (get_left(2, 2) == get_front(1, 1) && get_down(0, 0) == get_left(1, 1)){
                        while (get_left(2, 2) != get_left(1, 1) || get_front(2, 0) != get_front(1, 1))
                            pif_paf_left();
                    }
                    else if (get_left(2, 2) == get_left(1, 1) && get_down(0, 0) == get_back(1, 1)){
                        pif_paf_left();
                        up_rotation_left();
                        while (get_back(2, 2) != get_back(1, 1) || get_left(2, 0) != get_left(1, 1))
                            pif_paf_back_left();
                    }
                    else if (get_left(2, 2) == get_back(1, 1) && get_down(0, 0) == get_right(1, 1)){
                        pif_paf_left();
                        up_rotation_right();
                        up_rotation_right();
                        while (get_back(2, 0) != get_back(1, 1) || get_right(2, 2) != get_right(1, 1))
                            pif_paf_back_right();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_side_completed())
                        return;
                }
                else if (i == 8){
                    if (get_right(2, 0) == get_front(1, 1) && get_down(0, 2) == get_right(1, 1)){
                        while (get_front(2, 2) != get_front(1, 1) || get_right(2, 0) != get_right(1, 1))
                            pif_paf_right();
                    }
                    else if (get_right(2, 0) == get_left(1, 1) && get_down(0, 2) == get_front(1, 1)){
                        pif_paf_right();
                        up_rotation_left();
                        while(get_left(2, 2) != get_left(1, 1) || get_front(2, 0) != get_front(1, 1))
                            pif_paf_left();
                    }
                    else if (get_right(2, 0) == get_back(1, 1) && get_down(0, 2) == get_left(1, 1)){
                        pif_paf_right();
                        up_rotation_left();
                        up_rotation_left();
                        while (get_back(2, 2) != get_back(1, 0) || get_left(2, 0) != get_left(1, 1))
                            pif_paf_back_left();
                    }
                    else if (get_right(2, 0) == get_right(1, 1) && get_down(0, 2) == get_back(1, 1)){
                        pif_paf_right();
                        up_rotation_right();
                        while (get_right(2, 2) != get_right(1, 1) || get_back(2, 0) != get_back(1, 1))
                            pif_paf_back_right();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_side_completed())
                        return;
                }
            }
            
            // back
            if (get_back(i / 3, i % 3) == color && i != 4){
                if (i == 0){
                    if (get_up(0, 2) == get_left(1, 1) && get_right(2, 0) == get_back(1, 1)){
                        up_rotation_right();
                        while (get_back(2, 2) != get_back(1, 1) || get_left(2, 0) != get_left(1, 1))
                            pif_paf_back_left();
                    }
                    else if (get_up(0, 2) == get_front(1, 1) && get_right(2, 0) == get_left(1, 1)){
                        up_rotation_left();
                        up_rotation_left();
                        while(get_front(2, 0) != get_front(1, 1) || get_left(2, 2) != get_left(1, 1))
                            pif_paf_left();
                    }
                    else if (get_up(0, 2) == get_right(1, 1) && get_right(2, 0) == get_front(1, 1)){
                        up_rotation_left();
                        while(get_front(2, 2) != get_front(1, 1) || get_right(2, 0) != get_right(1, 1))
                            pif_paf_right();
                    }
                    else if(get_up(0, 2) == get_back(1, 1) && get_right(2, 0) == get_right(1, 1)){
                        while (get_back(2, 0) != get_back(1, 1) || get_right(2, 2) != get_right(1, 1))
                            pif_paf_back_right();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_side_completed())
                        return;
                }
                else if (i == 2){
                    if (get_up(0, 0) == get_back(1, 1) && get_left(0, 0) == get_left(1, 1)){
                        while (get_back(2, 2) != get_back(1, 1) || get_left(2, 0) != get_left(1, 1))
                            pif_paf_back_left();
                    }
                    else if (get_up(0, 0) == get_right(1, 1) && get_left(0, 0) == get_back(1, 1)){
                        up_rotation_left();
                        while (get_right(2, 2) != get_right(1, 1) || get_back(2, 0) != get_back(1, 1))
                            pif_paf_back_right();
                    }
                    else if (get_up(0, 0) == get_front(1, 1) && get_left(0, 0) == get_right(1, 1)){
                        up_rotation_left();
                        up_rotation_left();
                        while (get_front(2, 2) != get_front(1, 1) || get_right(2, 0) != get_right(1, 1))
                            pif_paf_right();
                    }
                    else if (get_up(0, 0) == get_left(1, 1) && get_left(0, 0) == get_front(1, 1)){
                        up_rotation_right();
                        while (get_left(2, 2) != get_left(1, 1) || get_front(2, 0) != get_front(1, 1))
                            pif_paf_left();
                    }
                    /* else
                        wrong_cube(); */
                    
                    if (down_side_completed())
                        return;
                }
                else if (i == 6){
                    if (get_right(2, 2) == get_back(1, 1) && get_down(2, 2) == get_right(1, 1)){
                        while (get_right(2, 2) != get_right(1, 1) || get_back(2, 0) != get_back(1, 1))
                            pif_paf_back_right();
                    }
                    else if (get_right(2, 2) == get_right(1, 1) && get_down(2, 2) == get_front(1, 1)){
                        pif_paf_back_right();
                        up_rotation_left();
                        while (get_front(2, 2) != get_front(1, 1) || get_right(2, 0) != get_right(1, 1))
                            pif_paf_right();
                    }
                    else if (get_right(2, 2) == get_front(1, 1) && get_down(2, 2) == get_left(1, 1)){
                        pif_paf_back_right();
                        up_rotation_left();
                        up_rotation_left();
                        while (get_left(2, 2) != get_left(1, 1) || get_front(2, 0) != get_front(1, 1))
                            pif_paf_left();
                    }
                    else if (get_right(2, 2) == get_left(1, 1) && get_down(2, 2) == get_back(1, 1)){
                        pif_paf_back_right();
                        up_rotation_right();
                        while (get_back(2, 2) != get_back(1, 1) || get_left(2, 0) != get_left(1, 1))
                            pif_paf_back_left();
                    }
                    /* else 
                        wrong_cube(); */
                    
                    if (down_side_completed())
                        return;
                }
                else if (i == 8){
                    if (get_left(2, 0) == get_back(1, 1) && get_down(2, 0) == get_left(1, 1)){
                        while (get_back(2, 2) != get_back(1, 1) || get_down(2, 0) != get_left(1, 1))
                            pif_paf_back_left();
                    }
                    else if(get_left(2, 0) == get_right(1, 1) && get_down(2, 0) == get_back(1, 1)){
                        pif_paf_back_left();
                        up_rotation_left();
                        while (get_right(2, 2) != get_right(1, 1) || get_back(2, 0) != get_back(1, 1))
                            pif_paf_back_right();
                    }
                    else if (get_left(2, 0) == get_front(1, 1) && get_down(2, 0) == get_right(1, 1)){
                        pif_paf_back_left();
                        up_rotation_left();
                        up_rotation_left();
                        while (get_right(2, 0) != get_right(1, 1) || get_front(2, 2) != get_front(1, 1))
                            pif_paf_right();
                    }
                    else if (get_left(2, 0) == get_left(1, 1) && get_down(2, 0) == get_front(1, 1)){
                        pif_paf_back_left();
                        up_rotation_right();
                        while (get_left(2, 2) != get_left(1, 1) || get_front(2, 0) != get_front(1, 1))
                            pif_paf_left();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_side_completed())
                        return;
                }
            }

            // right
            if (get_right(i / 3, i % 3) == color && i != 4){
                if (i == 0){
                    if (get_up(2, 2) == get_right(1, 1) && get_front(0, 2) == get_front(1, 1)){
                        while (get_front(2, 2) != get_front(1, 1) || get_right(2, 0) != get_right(1, 1))
                            pif_paf_right();
                    }
                    else if (get_up(2, 2) == get_front(1, 1) && get_front(0, 2) == get_left(1, 1)){
                        up_rotation_left();
                        while (get_front(2, 0) != get_front(1, 1) || get_left(2, 2) != get_left(1, 1))
                            pif_paf_left();
                    }
                    else if (get_up(2, 2) == get_left(1, 1) && get_front(0, 2) == get_back(1, 1)){
                        up_rotation_left();
                        up_rotation_left();
                        while (get_back(2, 2) != get_back(1, 1) || get_left(2, 0) == get_left(1, 1))
                            pif_paf_back_left();
                    }
                    else if (get_up(2, 2) == get_back(1, 1) && get_front(2, 0) == get_right(1, 1)){
                        up_rotation_right();
                        while (get_back(2, 0) != get_back(1, 1) || get_right(2, 2) != get_right(1, 1))
                            pif_paf_back_right();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_side_completed())
                        return;
                }
                else if (i == 2){
                    if (get_up(0, 2) == get_right(1, 1) && get_back(0, 0) == get_back(1, 1)){
                        while (get_right(2, 2) != get_right(1, 1) || get_back(2, 0) != get_back(1, 1))
                            pif_paf_back_right();
                    }
                    else if (get_up(0, 2) == get_front(1, 1) && get_back(0, 0) == get_right(1, 1)){
                        up_rotation_left();
                        while (get_front(2, 2) != get_front(1, 1) || get_right(2, 0) != get_right(1, 1))
                            pif_paf_right();
                    }
                    else if (get_up(0, 2) == get_left(1, 1) && get_back(0, 0) == get_front(1, 1)){
                        up_rotation_left();
                        up_rotation_left();
                        while (get_front(2, 0) != get_front(1, 1) || get_left(2, 2) != get_left(1, 1))
                            pif_paf_left();
                    }
                    else if (get_up(0, 2) == get_back(1, 1) && get_back(0, 0) == get_left(1, 1)){
                        up_rotation_right();
                        while (get_back(2, 2) != get_back(1, 1) || get_left(2, 0) != get_left(1, 1))
                            pif_paf_back_left();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_side_completed())
                        return;
                }
                else if (i == 6){
                    if (get_front(2, 2) == get_right(1, 1) && get_down(0, 2) == get_front(1, 1)){
                        while (get_front(2, 2) != get_front(1, 1) || get_right(2, 0) != get_right(1, 1))
                            pif_paf_right();
                    }
                    else if (get_front(2, 2) == get_front(1, 1) && get_down(0, 2) == get_left(1, 1)){
                        pif_paf_right();
                        up_rotation_left();
                        while (get_front(2, 0) != get_front(1, 1) || get_left(2, 2) != get_left(1, 1))
                            pif_paf_left();
                    }
                    else if (get_front(2, 2) == get_left(1, 1) && get_down(0, 2) == get_back(1, 1)){
                        pif_paf_right();
                        up_rotation_left();
                        up_rotation_left();
                        while (get_back(2, 2) != get_back(1, 1) || get_left(2, 0) != get_left(1, 1))
                            pif_paf_back_left();
                    }
                    else if (get_front(2, 2) == get_back(1, 1) && get_down(0, 2) == get_right(1, 1)){
                        pif_paf_right();
                        up_rotation_right();
                        while (get_back(2, 0) != get_back(1, 1) || get_right(2, 2) != get_right(1, 1))
                            pif_paf_back_right();
                    }
                    /* else
                        wrong_cube(); */
                    
                    if (down_side_completed())
                        return;
                }
                else if (i == 8){
                    if (get_back(2, 0) == get_right(1, 1) && get_down(2, 2) == get_back(1, 1)){
                        while (get_back(2, 0) != get_back(1, 1) || get_right(2, 2) != get_right(1, 1))
                            pif_paf_back_right();
                    }
                    else if (get_back(2, 0) == get_front(1, 1) && get_down(2, 2) == get_right(1, 1)){
                        pif_paf_back_right();
                        up_rotation_left();
                        while (get_front(2, 2) != get_front(1, 1) || get_right(2, 0) != get_right(1, 1))
                            pif_paf_right();
                    }
                    else if (get_back(2, 0) == get_left(1, 1) && get_down(2, 2) == get_front(1, 1)){
                        pif_paf_back_right();
                        up_rotation_left();
                        up_rotation_left();
                        while (get_left(2, 2) != get_left(1, 1) || get_front(2, 0) != get_front(1, 1))
                            pif_paf_left();
                    }
                    else if (get_back(2, 0) == get_back(1, 1) && get_down(2, 2) == get_left(1, 1)){
                        pif_paf_back_right();
                        up_rotation_right();
                        while (get_back(2, 2) != get_back(1, 1) || get_left(2, 0) != get_left(1, 1))
                            pif_paf_left_back();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_side_completed())
                        return;
                }
            }

            // left
            if (get_left(i / 3, i % 3) == color && i != 4){
                if (i == 0){
                    if (get_up(0, 0) == get_left(1, 1) && get_back(0, 2) == get_back(1, 1)){
                        while (get_back(2, 2) != get_back(1, 1) || get_left(2, 0) != get_left(1, 1))
                            pif_paf_back_left();
                    }
                    else if (get_up(0, 0) == get_back(1, 1) && get_back(0, 2) == get_right(1, 1)){
                        up_rotation_left();
                        while (get_back(2, 0) != get_back(1, 1) || get_right(2, 2) != get_right(1, 1))
                            pif_paf_back_right();
                    }
                    else if (get_up(0, 0) == get_right(1, 1) && get_back(0, 2) == get_front(1, 1)){
                        up_rotation_left();
                        up_rotation_left();
                        while (get_front(2, 2) != get_front(1, 1) || get_right(2, 0) != get_right(1, 1))
                            pif_paf_right();
                    }
                    else if (get_up(0, 0) == get_front(1, 1) && get_back(0, 2) == get_left(1, 1)){
                        up_rotation_right();
                        while (get_front(2, 0) != get_front(1, 1) || get_left(2, 2) != get_left(1, 1))
                            pif_paf_left();
                    }
                    /* else
                        wrong_cube(); */
                    
                    if (down_side_completed())
                        return;
                }
                else if (i == 2){
                    if (get_up(2, 0) == get_left(0, 0) && get_front(0, 0) == get_front(1, 1)){
                        while (get_front(2, 0) != get_front(1, 1) || get_left(2, 2) != get_left(1, 1))
                            pif_paf_left();
                    }
                    else if (get_up(2, 0) == get_back(1, 1) && get_front(0, 0) == get_left(1, 1)){
                        up_rotation_left();
                        while (get_left(2, 0) != get_left(1, 1) || get_back(2, 2) != get_back(1, 1))
                            pif_paf_back_left();
                    }
                    else if (get_up(2, 0) == get_right(1, 1) && get_front(0, 0) == get_back(1, 1)){
                        up_rotation_left();
                        up_rotation_left();
                        while (get_back(2, 0) != get_back(1, 1) || get_right(2, 2) != get_right(1, 1))
                            pif_paf_back_right();
                    }
                    else if (get_up(2, 0) == get_front(1, 1) && get_front(0, 0) == get_right(1, 1)){
                        up_rotation_right();
                        while (get_front(2, 2) != get_front(1, 1) || get_right(2, 0) != get_right(1, 1))
                            pif_paf_right();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_side_completed())
                        return;
                }
                else if (i == 6){
                    if (get_back(2, 2) == get_left(1, 1) && get_down(2, 0) == get_back(1, 1)){
                        while (get_back(2, 2) != get_back(1, 1) || get_left(2, 0) != get_left(1, 1))
                            pif_paf_back_left();
                    }
                    else if (get_back(2, 2) == get_back(1, 1) && get_down(2, 0) == get_right(1, 1)){
                        pif_paf_back_left();
                        up_rotation_left();
                        while (get_back(2, 0) != get_back(1, 1) || get_right(2, 2) != get_right(1, 1))
                            pif_paf_back_right();
                    }
                    else if (get_back(2, 2) == get_right(1, 1) && get_down(2, 0) == get_front(1, 1)){
                        pif_paf_back_left();
                        up_rotation_left();
                        up_rotation_left();
                        while (get_front(2, 2) != get_front(1, 1) || get_right(2, 0) != get_right(1, 1))
                            pif_paf_right();
                    }
                    else if (get_back(2, 2) == get_front(1, 1) && get_down(2, 0) == get_left(1, 1)){
                        pif_paf_back_left();
                        up_rotation_right();
                        while (get_left(2, 2) != get_left(1, 1) || get_front(2, 0) != get_front(1, 1))
                            pif_paf_left();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_side_completed())
                        return;
                }
                else if (i == 8){
                    if (get_front(2, 0) == get_left(1, 1) && get_down(0, 0) == get_front(1, 1)){
                        while (get_front(2, 0) != get_front(1, 1) || get_left(2, 2) != get_left(1, 1))
                            pif_paf_left();
                    }
                    else if (get_front(2, 0) == get_back(1, 1) && get_down(0, 0) == get_left(1, 1)){
                        pif_paf_left();
                        up_rotation_left();
                        while (get_back(2, 2) != get_back(1, 1) || get_left(2, 0) != get_left(1, 1))
                            pif_paf_back_left();
                    }
                    else if (get_front(2, 0) == get_right(1, 1) && get_down(0, 0) == get_back(1, 1)){
                        pif_paf_left();
                        up_rotation_left();
                        up_rotation_left();
                        while (get_back(2, 0) != get_back(1, 1) || get_right(2,2) != get_right(1, 1))
                            pif_paf_back_right();
                    }
                    else if (get_front(2, 0) == get_front(1, 1) && get_down(0, 0) == get_right(1, 1)){
                        pif_paf_left();
                        up_rotation_right();
                        while (get_front(2, 2) != get_front(1, 1) || get_right(2, 0) != get_right(1, 1))
                            pif_paf_right();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_side_completed())
                        return;
                }
            }

            // up
            if (get_up(i / 3, i % 3) == color && i != 4){
                if (i == 0){
                    if (get_back(0, 2) == get_front(1, 1) && get_left(0, 0) == get_left(1, 1)){
                        up_rotation_right();
                        while (get_front(2, 0) != get_front(1, 1) || get_left(2, 2) != get_left(1, 1))
                            pif_paf_left();
                    }
                    else if (get_back(0, 2) == get_right(1, 1) && get_left(0, 0) == get_front(1, 1)){
                        up_rotation_left();
                        up_rotation_left();
                        while (get_right(2, 1) != get_right(1, 1) || get_front(2, 2) != get_front(1, 1))
                            pif_paf_right();
                    }
                    else if (get_back(0, 2) == get_back(1, 1) && get_left(0, 0) == get_right(1, 1)){
                        up_rotation_left();
                        while (get_back(2, 0) != get_back(1, 1) || get_right(2, 2) != get_right(1, 1))
                            pif_paf_back_right();

                    }
                    else if (get_back(0, 2) == get_left(1, 1) && get_left(0, 0) == get_back(1, 1)){
                        while (get_back(2, 2) != get_back(1, 1) || get_left(2, 0) != get_left(1, 1))
                            pif_paf_back_left();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_side_completed())
                        return;
                }
                else if (i == 2){
                    if (get_back(0, 0) == get_right(1, 1) && get_right(0, 2) == get_back(1, 1)){
                        while (get_back(2, 0) != get_back(1, 1) || get_right(2, 2) != get_right(1, 1))
                            pif_paf_back_right();
                    }
                    else if (get_back(0, 0) == get_front(1, 1) && get_right(0, 2) == get_right(1, 1)){
                        up_rotation_left();
                        while (get_front(2, 2) != get_front(1, 1) || get_right(2, 0) != get_right(1, 1))
                            pif_paf_right();
                    }
                    else if (get_back(0, 0) == get_left(1, 1) && get_right(0, 2) == get_front(1, 1)){
                        up_rotation_left();
                        up_rotation_left();
                        while (get_left(2, 2) != get_left(1, 1) || get_front(2, 0) != get_front(1, 1))
                            pif_paf_left();
                    }
                    else if (get_back(0, 0) == get_back(1, 1) && get_right(0, 2) == get_left(1, 1)){
                        up_rotation_right();
                        while (get_back(2, 2) != get_back(1, 1) || get_left(2, 0) != get_left(1, 1))
                            pif_paf_back_left();
                    }
                    /* else 
                        wrong_cube(); */
                    
                    if (down_side_completed())
                        return;
                }
                else if (i == 6){
                    if (get_front(0, 0) == get_left(1, 1) && get_left(0, 2) == get_front(1, 1)){
                        while (get_left(2, 2) != get_left(1, 1) || get_front(2, 0) != get_front(1, 1))
                            pif_paf_left();
                    }
                    else if (get_front(0, 0) == get_front(1, 1) && get_left(0, 2) == get_right(1, 1)){
                        up_rotation_right();
                        while (get_front(2, 2) != get_front(1, 1) || get_right(2, 0) != get_right(1, 1))
                            pif_paf_right();
                    }
                    else if (get_front(0, 0) == get_right(1, 1) && get_left(0, 2) == get_back(1, 1)){
                        up_rotation_left();
                        up_rotation_left();
                        while (get_right(2, 2) != get_right(1, 1) || get_back(2, 0) != get_back(1, 1))
                            pif_paf_back_right();
                    }
                    else if (get_front(0, 0) == get_back(1, 1) && get_left(0, 2) == get_left(1, 1)){
                        up_rotation_left();
                        while ( get_back(2, 2) != get_back(1, 1) || get_left(2, 0) != get_left(1, 1))
                            pif_paf_back_left();
                    }
                    /* else
                        wrong_cube(); */
                    
                    if (down_side_completed())
                        return;
                }
                else if (i == 8){
                    if (get_front(0, 2) == get_right(1, 1) && get_right(0, 0) == get_front(1, 1)){
                        while ( get_front(2, 2) != get_front(1, 1) || get_right(2, 0) != get_right(1, 1))
                            pif_paf_right();
                    }
                    else if (get_front(0, 2) == get_back(1, 1) && get_right(0, 0) == get_right(1, 1)){
                        up_rotation_right();
                        while (get_back(2, 0) != get_back(1, 1) || get_right(2, 2) != get_right(1, 1))
                            pif_paf_back_right();
                    }
                    else if (get_front(0, 2) == get_left(1, 1) && get_right(0, 0) == get_back(1, 1)){
                        up_rotation_left();
                        up_rotation_left();
                        while (get_back(2, 2) != get_back(1, 1) || get_left(2, 0) != get_left(1, 1))
                            pif_paf_back_left();
                    }
                    else if (get_front(0, 2) == get_front(1, 1) && get_right(0, 0) == get_left(1, 1)){
                        up_rotation_left();
                        while (get_front(2, 0) != get_front(1, 1) || get_left(2, 2) != get_left(1, 1))
                            pif_paf_left();
                    }
                    /* else
                        wrong_cube(); */

                    if (down_side_completed())
                        return;
                }
            }
        }

        if (!down_side_completed())
            down_side();
    }

    bool two_levels_completed(){
        int front = get_front(1, 1), back = get_back(1, 1), right = get_right(1, 1), left = get_left(1, 1);
        if (get_front(1, 0) != front || get_front(1, 2) != front || get_front(2, 0) != front || get_front(2, 1) != front || get_front(2, 2) != front)
            return false;
        if (get_back(1, 0) != back || get_back(1, 2) != back || get_back(2, 0) != back || get_back(2, 1) != back || get_back(2, 2) != back)
            return false;
        if (get_right(1, 0) != right || get_right(1, 2) != right || get_right(2, 0) != right || get_right(2, 1) != right || get_right(2, 2) != right)
            return false;
        if (get_left(1, 0) != left || get_left(1, 2) != left || get_left(2, 0) != left || get_left(2, 1) != left || get_left(2, 2) != left)
            return false;
        return true; 
    }
    void two_levels(){
        // up
        if (get_up(0, 1) == get_front(1, 1) && get_back(0, 1) == get_left(1, 1)){
            pif_paf_front_left();
            pif_paf_left();
        }
        if (get_up(0, 1) == get_left(1, 1) && get_back(0, 1) == get_front(1, 1)){
            up_rotation_left();
            pif_paf_left();
            pif_paf_front_left();
        }
        if (get_up(0, 1) == get_front(1, 1) && get_back(0, 1) == get_right(1, 1)){
            pif_paf_front_right();
            pif_paf_right();
        }
        if (get_up(0, 1) == get_right(1, 1) && get_back(0, 1) == get_front(1, 1)){
            up_rotation_right();
            pif_paf_right();
            pif_paf_front_right();
        }
        if (get_up(0, 1) == get_back(1, 1) && get_back(0, 1) == get_right(1, 1)){
            up_rotation_left();
            up_rotation_left();
            pif_paf_back_right();
            pif_paf_right_back();
        }
        if (get_up(0, 1) == get_right(1, 1) && get_back(0, 1) == get_back(1, 1)){
            up_rotation_right();
            pif_paf_right_back();
            pif_paf_back_right();
        }
        if (get_up(0, 1) == get_left(1, 1) && get_back(0, 1) == get_back(1, 1)){
            up_rotation_left();
            pif_paf_left_back();
            pif_paf_back_left();
        }
        if (get_up(0, 1) == get_back(1, 1) && get_back(0, 1) == get_left(1, 1)){
            up_rotation_left();
            up_rotation_left();
            pif_paf_back_left();
            pif_paf_left_back();
        }
        
        if (get_up(1, 0) == get_back(1, 1) && get_left(0, 1) == get_left(1, 1)){
            up_rotation_right();
            pif_paf_back_left();
            pif_paf_left_back();
        }
        if (get_up(1, 0) == get_left(1, 1) && get_left(0, 1) == get_back(1, 1)){
            up_rotation_left();
            up_rotation_left();
            pif_paf_left_back();
            pif_paf_back_left();

        }
        if (get_up(1, 0) == get_left(1, 1) && get_left(0, 1) == get_front(1, 1)){
            up_rotation_left();
            up_rotation_left();
            pif_paf_left();
            pif_paf_front_left();
        }
        if (get_up(1, 0) == get_front(1, 1) && get_left(0, 1) == get_left(1, 1)){
            up_rotation_left();
            pif_paf_front_left();
            pif_paf_left();
        }
        if (get_up(1, 0) == get_right(1, 1) && get_left(0, 1) == get_back(1, 1)){
            pif_paf_right_back();
            pif_paf_back_right();
        }
        if (get_up(1, 0) == get_back(1, 1) && get_left(0, 1) == get_right(1, 1)){
            up_rotation_right();
            pif_paf_back_right();
            pif_paf_right_back();
        }
        if (get_up(1, 0) == get_right(1, 1) && get_left(0, 1) == get_front(1, 1)){
            pif_paf_right();
            pif_paf_front_right();
        }
        if (get_up(1, 0) == get_front(1, 1) && get_left(0, 1) == get_right(1, 1)){
            up_rotation_left();
            pif_paf_front_right();
            pif_paf_right();
        }
        
        if (get_up(1, 2) == get_front(1, 1) && get_right(0, 1) == get_right(1, 1)){
            up_rotation_right();
            pif_paf_front_right();
            pif_paf_right();
        }
        if (get_up(1, 2) == get_right(1, 1) && get_right(0, 1) == get_front(1, 1)){
            up_rotation_left();
            up_rotation_left();
            pif_paf_right();
            pif_paf_front_right();
        }
        if (get_up(1, 2) == get_right(1, 1) && get_right(0, 1) == get_back(1, 1)){
            up_rotation_left();
            up_rotation_left();
            pif_paf_right_back();
            pif_paf_back_right();
        }
        if (get_up(1, 2) == get_back(1, 1) && get_right(0, 1) == get_right(1, 1)){
            up_rotation_left();
            pif_paf_back_right();
            pif_paf_right_back();
        }
        if (get_up(1, 2) == get_back(1, 1) && get_right(0, 1) == get_left(1, 1)){
            up_rotation_left();
            pif_paf_back_left();
            pif_paf_left_back();
        }
        if (get_up(1, 2) == get_left(1, 1) && get_right(0, 1) == get_back(1, 1)){
            pif_paf_left_back();
            pif_paf_back_left();
        }
        if (get_up(1, 2) == get_left(1, 1) && get_right(0, 1) == get_front(1, 1)){
            pif_paf_left();
            pif_paf_front_left();
        }
        if (get_up(1, 2) == get_front(1, 1) && get_right(0, 1) == get_left(1, 1)){
            up_rotation_right();
            pif_paf_front_left();
            pif_paf_left();
        }
        
        if (get_up(2, 1) == get_left(1, 1) && get_front(0, 1) == get_front(1, 1)){
            up_rotation_right();
            pif_paf_left();
            pif_paf_front_left();
        }
        if (get_up(2, 1) == get_front(1, 1) && get_front(0, 1) == get_left(1, 1)){
            up_rotation_left();
            up_rotation_left();
            pif_paf_front_left();
            pif_paf_left();
        }
        if (get_up(2, 1) == get_front(1, 1) && get_front(0, 1) == get_right(1, 1)){
            up_rotation_left();
            up_rotation_left();
            pif_paf_front_right();
            pif_paf_right();
        }
        if (get_up(2, 1) == get_right(1, 1) && get_front(0, 1) == get_front(1, 1)){
            up_rotation_left();
            pif_paf_right();
            pif_paf_front_right();
        }
        if (get_up(2, 1) == get_back(1, 1) && get_front(0, 1) == get_left(1, 1)){
            pif_paf_back_left();
            pif_paf_left_back();
        }
        if (get_up(2, 1) == get_left(1, 1) && get_front(0, 1) == get_back(1, 1)){
            up_rotation_right();
            pif_paf_left_back();
            pif_paf_back_left();
        }
        if (get_up(2, 1) == get_right(1, 1) && get_front(0, 1) == get_back(1, 1)){
            up_rotation_left();
            pif_paf_right_back();
            pif_paf_back_right();
        }
        if (get_up(2, 1) == get_back(1, 1) && get_front(0, 1) == get_right(1, 1)){
            pif_paf_back_right();
            pif_paf_left_back();
        }
        
        // front
        if (get_front(1, 2) == get_right(1, 1) && get_right(1, 0) == get_front(1, 1)){
            pif_paf_right();
            pif_paf_front_right();
            up_rotation_right();
            pif_paf_right();
            pif_paf_front_right();
        }
        if (get_front(1, 2) == get_back(1, 1) && get_right(1, 0) == get_right(1, 1)){
            pif_paf_right();
            pif_paf_front_right();
            up_rotation_left();
            pif_paf_back_right();
            pif_paf_right_back();
        }
        if (get_front(1, 2) == get_right(1, 1) && get_right(1, 0) == get_back(1, 1)){
            pif_paf_right();
            pif_paf_front_right();
            up_rotation_left();
            up_rotation_left();
            pif_paf_right_back();
            pif_paf_back_right();
        }
        if (get_front(1, 2) == get_left(1, 1) && get_right(1, 0) == get_back(1, 1)){
            pif_paf_right();
            pif_paf_front_right();
            pif_paf_left_back();
            pif_paf_back_left();
        }
        if (get_front(1, 2) == get_back(1, 1) && get_right(1, 0) == get_left(1, 1)){
            pif_paf_right();
            pif_paf_front_right();
            up_rotation_left();
            pif_paf_back_left();
            pif_paf_left_back();
        }
        if (get_front(1, 2) == get_front(1, 1) && get_right(1, 0) == get_left(1, 1)){
            pif_paf_right();
            pif_paf_front_right();
            up_rotation_right();
            pif_paf_front_left();
            pif_paf_right();
        }
        if (get_front(1, 2) == get_left(1, 1) && get_right(1, 0) == get_front(1, 1)){
            pif_paf_right();
            pif_paf_front_right();
            pif_paf_left();
            pif_paf_front_left();
        }
        
        if(get_front(1, 0) == get_left(1, 1) && get_left(1, 2) == get_front(1, 1)){
            pif_paf_left();
            pif_paf_front_left();
            up_rotation_left();
            up_rotation_left();
            pif_paf_left();
            pif_paf_front_left();
        }
        if (get_front(1, 0) == get_back(1, 1) && get_left(1, 2) == get_left(1, 1)){
            pif_paf_left();
            pif_paf_front_left();
            up_rotation_right();
            pif_paf_back_left();
            pif_paf_left_back();
        }
        if (get_front(1, 0) == get_left(1, 1) && get_left(1, 2) == get_back(1, 1)){
            pif_paf_left();
            pif_paf_front_left();
            up_rotation_left();
            up_rotation_left();
            pif_paf_left_back();
            pif_paf_back_left();
        }
        if (get_front(1, 0) == get_back(1, 1) && get_left(1, 2) == get_right(1, 1)){
            pif_paf_left();
            pif_paf_front_left();
            up_rotation_right();
            pif_paf_back_right();
            pif_paf_right_back();
        }
        if (get_front(1, 0) == get_right(1, 1) && get_left(1, 2) == get_back(1, 1)){
            pif_paf_left();
            pif_paf_front_left();
            pif_paf_right_back();
            pif_paf_back_right();
        }
        if (get_front(1, 0) == get_right(1, 1) && get_left(1, 2) == get_front(1, 1)){
            pif_paf_left();
            pif_paf_front_left();
            pif_paf_right();
            pif_paf_front_right();
        }
        if (get_front(1, 0) == get_front(1, 1) && get_left(1, 2) == get_right(1, 1)){
            pif_paf_left();
            pif_paf_front_left();
            up_rotation_left();
            pif_paf_front_right();
            pif_paf_right();
        }
        
        // back
        if (get_back(1, 0) == get_right(1, 1) && get_right(1, 2) == get_back(1, 1)){
            pif_paf_back_right();
            pif_paf_right_back();
            up_rotation_left();
            up_rotation_left();
            pif_paf_back_right();
            pif_paf_right_back();
        }
        if (get_back(1, 0) == get_back(1, 1) && get_right(1, 2) == get_left(1, 1)){
            pif_paf_back_right();
            pif_paf_right_back();
            up_rotation_left();
            pif_paf_left_back();
            pif_paf_back_left();
        }
        if (get_back(1, 0) == get_left(1, 1) && get_right(1, 2) == get_back(1, 1)){
            pif_paf_back_right();
            pif_paf_right_back();
            up_rotation_left();
            up_rotation_left();
            pif_paf_back_left();
            pif_paf_left_back();
        }
        if (get_back(1, 0) == get_front(1, 1) && get_right(1, 2) == get_left(1, 1)){
            pif_paf_back_right();
            pif_paf_right_back();
            up_rotation_left();
            pif_paf_left();
            pif_paf_front_left();
        }
        if (get_back(1, 0) == get_left(1, 1) && get_right(1, 2) == get_front(1, 1)){
            pif_paf_back_right();
            pif_paf_right_back();
            pif_paf_front_left();
            pif_paf_left();
        }
        if (get_back(1, 0) == get_front(1, 1) && get_right(1, 2) == get_right(1, 1)){
            pif_paf_back_right();
            pif_paf_right_back();
            up_rotation_right();
            pif_paf_right();
            pif_paf_front_right();
        }
        if (get_back(1, 0) == get_right(1, 1) && get_right(1, 2) == get_front(1, 1)){
            pif_paf_back_right();
            pif_paf_right_back();
            pif_paf_front_right();
            pif_paf_right();
        }
        
        if (get_back(1, 2) == get_left(1, 1) && get_left(1, 0) == get_back(1, 1)){
            pif_paf_left_back();
            pif_paf_back_left();
            up_rotation_left();
            up_rotation_left();
            pif_paf_left_back();
            pif_paf_back_left();
        }
        if(get_back(1, 2) == get_back(1, 1) && get_left(1, 0) == get_right(1, 1)){
            pif_paf_left_back();
            pif_paf_back_left();
            up_rotation_right();
            pif_paf_back_right();
            pif_paf_right_back();
        }
        if (get_back(1, 2) == get_right(1, 1) && get_left(1, 0) == get_back(1, 1)){
            pif_paf_left_back();
            pif_paf_back_left();
            pif_paf_right_back();
            pif_paf_back_right();
        }
        if (get_back(1, 2) == get_right(1, 1) && get_left(1, 0) == get_front(1, 1)){
            pif_paf_left_back();
            pif_paf_back_left();
            pif_paf_right();
            pif_paf_front_right();
        }
        if (get_back(1, 2) == get_front(1, 1) && get_left(1, 0) == get_right(1, 1)){
            pif_paf_left_back();
            pif_paf_back_left();
            up_rotation_left();
            up_rotation_left();
            pif_paf_front_right();
            pif_paf_right();
        }
        if (get_back(1, 2) == get_front(1, 1) && get_left(1, 0) == get_left(1, 1)){
            pif_paf_left_back();
            pif_paf_back_left();
            up_rotation_left();
            pif_paf_front_left();
            pif_paf_left();
        }
        if (get_back(1, 2) == get_left(1, 1) && get_left(1, 0) == get_front(1, 1)){
            pif_paf_left_back();
            pif_paf_back_left();
            up_rotation_left();
            up_rotation_left();
            pif_paf_left();
            pif_paf_front_left();
        }
        
        //std::cout << two_levels_completed() << "\n";
        if (!two_levels_completed()){
            two_levels();
        }
    }

    bool up_cross_completed(){
        if (down_side_completed() && two_levels_completed()){
            int color = get_up(1, 1);
            if (get_up(0, 1) != color)
                return false;
            if (get_up(1, 0) != color)
                return false;
            if (get_up(1, 2) != color)
                return false;
            if (get_up(2, 1) != color)
                return false;
            return true;
        }
        return false;
    }
    void up_cross(){
        if (up_cross_completed())
            return;
        if (get_up(0, 1) != get_up(1, 1) && get_up(1, 2) != get_up(1, 1) && get_up(1, 0) != get_up(1, 1) && get_up(2, 1) != get_up(1, 1)){
            front_rotation_right();
            pif_paf_right();
            front_rotation_left();
            up_cross();
        }
        else if (get_up(1, 0) == get_up(1, 1) && get_up(1, 1) == get_up(1, 2)){
            front_rotation_right();
            pif_paf_right();
            front_rotation_left();
        }
        else if (get_up(0, 1) == get_up(1, 1) && get_up(1, 1) == get_up(2, 1)){
            left_rotation_down();
            pif_paf_front_left();
            left_rotation_up();
        }
        else if (get_up(1, 1) == get_up(1, 2) && get_up(1, 1) == get_up(2, 1)){
            back_rotation_left();
            pif_paf_left_back();
            pif_paf_left_back();
            back_rotation_right();
        }
        else if (get_up(1, 1) == get_up(1, 2) && get_up(1, 1) == get_up(0, 1)){
            left_rotation_down();
            pif_paf_front_left();
            pif_paf_front_left();
            left_rotation_up();
        }
        else if (get_up(1, 1) == get_up(0, 1) && get_up(1, 1) == get_up(1, 0)){
            front_rotation_right();
            pif_paf_right();
            pif_paf_right();
            front_rotation_left();
        }
        else if (get_up(1, 1) == get_up(1, 0) && get_up(1, 1) == get_up(2, 1)){
            right_rotation_up();
            pif_paf_back_right();
            pif_paf_back_right();
            right_rotation_down();
        }
        /* else{
            wrong_cube();
        } */

        if (!up_cross_completed()){
            up_cross();
        }
    }

    bool up_cross_rotation_completed(){
        if(up_cross_completed()){
            if(get_front(0, 1) == get_front(1, 1) && get_back(0, 1) == get_back(1, 1) && get_left(0, 1) == get_left(1, 1) && get_right(0, 1) == get_right(1, 1))
                return true;
            return false;
        }
        return false;
    }
    void up_cross_rotation(){
        if (up_cross_rotation_completed())
            return;
        else{
            if (get_front(0, 1) == get_front(1, 1) && get_right(0, 1) != get_right(1, 1) && get_left(0, 1) != get_left(1, 1)){
                right_rotation_up();
                up_rotation_left();
                right_rotation_down();
                up_rotation_left();
                right_rotation_up();
                up_rotation_left();
                up_rotation_left();
                right_rotation_down();
            }
            else if (get_left(0, 1) == get_left(1, 1) && get_front(0, 1) != get_front(1, 1) && get_back(0, 1) == get_back(1, 1)){
                front_rotation_right();
                up_rotation_left();
                front_rotation_left();
                up_rotation_left();
                front_rotation_right();
                up_rotation_left();
                up_rotation_left();
                front_rotation_left();
            }
            else if (get_back(0, 1) == get_back(1, 1) && get_left(0, 1) != get_left(1, 1) && get_right(0, 1) != get_right(1, 1)){
                left_rotation_down();
                up_rotation_left();
                left_rotation_up();
                up_rotation_left();
                left_rotation_down();
                up_rotation_left();
                up_rotation_left();
                left_rotation_up();
            }
            else if (get_right(0, 1) == get_right(1, 1) && get_back(0, 1) != get_back(1, 1) && get_front(0, 1) != get_front(1, 1)){
                back_rotation_left();
                up_rotation_left();
                back_rotation_right();
                up_rotation_left();
                back_rotation_left();
                up_rotation_left();
                up_rotation_left();
                back_rotation_right();
            }
            else if (get_front(0, 1) == get_front(1, 1) && get_right(0, 1) == get_right(1, 1) && get_left(0, 1) != get_left(1, 1) && get_back(0, 1) != get_back(1, 1)){
                front_rotation_right();
                up_rotation_left();
                front_rotation_left();
                up_rotation_left();
                front_rotation_right();
                up_rotation_left();
                up_rotation_left();
                front_rotation_left();
                up_rotation_left();
            }
            else if (get_front(0, 1) == get_front(1, 1) && get_right(0, 1) != get_right(1, 1) && get_left(0, 1) == get_left(1, 1) && get_back(0, 1) != get_back(1, 1)){
                left_rotation_down();
                up_rotation_left();
                left_rotation_up();
                up_rotation_left();
                left_rotation_down();
                up_rotation_left();
                up_rotation_left();
                left_rotation_up();
                up_rotation_left();
            }
            else if (get_front(0, 1) != get_front(1, 1) && get_right(0, 1) == get_right(1, 1) && get_left(0, 1) != get_left(1, 1) && get_back(0, 1) == get_back(1, 1)){
                right_rotation_up();
                up_rotation_left();
                right_rotation_down();
                up_rotation_left();
                right_rotation_up();
                up_rotation_left();
                up_rotation_left();
                right_rotation_down();
                up_rotation_left();
            }
            else if (get_front(0, 1) != get_front(1, 1) && get_right(0, 1) != get_right(1, 1) && get_left(0, 1) == get_left(1, 1) && get_back(0, 1) == get_back(1, 1)){
                back_rotation_left();
                up_rotation_left();
                back_rotation_right();
                up_rotation_left();
                back_rotation_left();
                up_rotation_left();
                up_rotation_left();
                back_rotation_right();
                up_rotation_left();
            }
            else{
                up_rotation_left();
            }

            if(!up_cross_rotation_completed()){
                up_cross_rotation();
                return;
            }
        }
    }

    bool angles_position_completed(){
        if (up_cross_rotation_completed()){
            if((get_up(2, 0) == get_up(1, 1) || get_up(2, 0) == get_front(1, 1) || get_up(2, 0) == get_left(1, 1)) && (get_left(0, 2) == get_left(1, 1) || get_left(0, 2) == get_up(1, 1) || get_left(0, 2) == get_front(1, 1))
            && (get_front(0, 0) == get_front(1, 1) || get_front(0, 0) == get_left(1, 1) || get_front(0, 0) == get_up(1, 1)) && (get_up(0, 0) == get_up(1, 1) || get_up(0, 0) == get_left(1, 1) || get_up(0, 0) == get_back(1, 1))
            && (get_left(0, 0) == get_left(1, 1) || get_left(0, 0) == get_up(1, 1) || get_left(0, 0) == get_back(1, 1)) && (get_back(0, 2) == get_back(1, 1) || get_back(0, 2) == get_up(1, 1) || get_back(0, 2) == get_left(1, 1))
            && (get_up(0, 2) == get_up(1, 1) || get_up(0, 2) == get_back(1, 1) || get_up(0, 2) == get_right(1, 1)) && (get_back(0, 0) == get_back(1, 1) || get_back(0, 0) ==get_right(1, 1) || get_back(0, 0) == get_up(1, 1))
            && (get_right(0, 2) == get_up(1, 1) || get_right(0, 2) == get_back(1, 1) || get_right(0, 2) == get_right(1, 1)) && (get_up(2, 2) == get_up(1, 1) || get_up(2, 2) == get_front(1, 1) || get_up(2, 2) == get_right(1, 1))
            && (get_right(0, 0) == get_up(1, 1) || get_right(0, 0) == get_front(1, 1) || get_right(0, 0) == get_right(1, 1)) && (get_front(0, 2) == get_up(1, 1) || get_front(0, 2) == get_front(1, 1) || get_front(0, 2) == get_right(1, 1)))
                return true;
            else
                return false;
        }
        else
            return false;
    }
    void angels_position(){
        if (angles_position_completed())
            return;
        
        if ((get_up(2, 2) == get_up(1, 1) || get_up(2, 2) == get_front(1, 1) || get_up(2, 2) == get_right(1, 1)) && (get_front(0, 2) == get_up(1, 1) || get_front(0, 2) == get_front(1, 1) || get_front(0, 2) == get_right(1, 1))
        && (get_right(0, 0) == get_up(1, 1) || get_right(0, 0) == get_front(1, 1) || get_right(0, 0) == get_right(1, 1))){
            up_rotation_left();
            right_rotation_up();
            up_rotation_right();
            left_rotation_up();
            up_rotation_left();
            right_rotation_down();
            up_rotation_right();
            left_rotation_down();
        }
        else if ((get_up(2, 0) == get_up(1, 1) || get_up(2, 0) == get_front(1, 1) || get_up(2, 0) == get_left(1, 1)) && (get_left(0, 2) == get_left(1, 1) || get_left(0, 2) == get_up(1, 1) || get_left(0, 2) == get_front(1, 1))
        && (get_front(0, 0) == get_front(1, 1) || get_front(0, 0) == get_left(1, 1) || get_front(0, 0) == get_up(1, 1))){
            up_rotation_left();
            front_rotation_right();
            up_rotation_right();
            back_rotation_right();
            up_rotation_left();
            front_rotation_left();
            up_rotation_right();
            back_rotation_left();
        }
        else if ((get_up(0, 0) == get_up(1, 1) || get_up(0, 0) == get_left(1, 1) || get_up(0, 0) == get_back(1, 1)) && (get_left(0, 0) == get_left(1, 1) || get_left(0, 0) == get_up(1, 1) || get_left(0, 0) == get_back(1, 1))
        && (get_back(0, 2) == get_back(1, 1) || get_back(0, 2) == get_up(1, 1) || get_back(0, 2) == get_left(1, 1))){
            up_rotation_left();
            left_rotation_down();
            up_rotation_right();
            right_rotation_down();
            up_rotation_left();
            left_rotation_up();
            up_rotation_right();
            right_rotation_up();
        }
        else if ((get_up(0, 2) == get_up(1, 1) || get_up(0, 2) == get_back(1, 1) || get_up(0, 2) == get_right(1, 1)) && (get_back(0, 0) == get_back(1, 1) || get_back(0, 0) ==get_right(1, 1) || get_back(0, 0) == get_up(1, 1))
        && (get_right(0, 2) == get_up(1, 1) || get_right(0, 2) == get_back(1, 1) || get_right(0, 2) == get_right(1, 1))){
            up_rotation_left();
            back_rotation_left();
            up_rotation_right();
            front_rotation_left();
            up_rotation_left();
            back_rotation_right();
            up_rotation_right();
            front_rotation_right();
        }
        else {
            up_rotation_left();
            right_rotation_up();
            up_rotation_right();
            left_rotation_up();
            up_rotation_left();
            right_rotation_down();
            up_rotation_right();
            left_rotation_down();
        }

        if (!angles_position_completed()){
            angels_position();
        }
    }

    void last_action(){
        if (cube_is_completed())
            return;
        
        if (get_up(2, 0) != get_up(1, 1)){
            while (!side_is_completed(up_)){
                while (get_up(2, 0) != get_up(1, 1))
                    pif_paf_left_down();
                if (!side_is_completed(up_)){
                    do{
                        up_rotation_right();
                    } while (get_up(2, 0) == get_up(1, 1));
                }
            }
        }
        else if (get_up(0, 0) != get_up(1, 1)){
            while (!side_is_completed(up_)){
                while (get_up(0, 0) != get_up(1, 1))
                    pif_paf_back_down();
                if (!side_is_completed(up_)){
                    do{
                        up_rotation_right();
                    } while (get_up(0, 0) == get_up(1, 1));
                }
            }
        }
        else if (get_up(0, 2) != get_up(1, 1)){
            while(!side_is_completed(up_)){
                while (get_up(0, 2) != get_up(1, 1))
                    pif_paf_right_down();
                if (!side_is_completed(up_)){
                    do{
                        up_rotation_right();
                    } while (get_up(0, 2) == get_up(1, 1));
                }
            }
        }
        else if (get_up(2, 2) != get_up(1, 1)){
            while (!side_is_completed(up_)){
                while (get_up(2, 2) != get_up(1, 1))
                    pif_paf_front_down();
                if (!side_is_completed(up_)){
                    do{
                        up_rotation_right();
                    } while (get_up(2, 2) == get_up(1, 1));
                }
            }
        }
        else{
            while (!cube_is_completed())
                up_rotation_right();
        }

        if (!side_is_completed(up_))
            last_action();
        if (side_is_completed(up_) && !cube_is_completed()){
            while (!cube_is_completed())
                up_rotation_right();
        }
    }

    void cube_assembling(){
        std::cout << "down_cross\n\n";
        down_cross();
        if (cube_is_completed()){
            std::cout << "----------cube completed----------\n\n";
            return;
        }
        std::cout << "down_side\n\n";
        down_side();
        if (cube_is_completed()){
            std::cout << "----------cube completed----------\n\n";
            return;
        }
        std::cout << "two_level\n\n";
        two_levels();
        if (cube_is_completed()){
            std::cout << "----------cube completed----------\n\n";
            return;
        }
        std::cout << "up_cross\n\n";
        up_cross();
        if (cube_is_completed()){
            std::cout << "----------cube completed----------\n\n";
            return;
        }
        std::cout << "up_rotation\n\n";
        up_cross_rotation();
        if (cube_is_completed()){
            std::cout << "----------cube completed----------\n\n";
            return;
        }
        std::cout << "angels_position\n\n";
        angels_position();
        if (cube_is_completed()){
            std::cout << "----------cube completed----------\n\n";
            return;
        }
        std::cout << "last_action\n\n";
        last_action();
        if (cube_is_completed()){
            std::cout << "----------cube completed----------\n\n";
            return;
        }
    }

    void cube_disassembling(){
        right_rotation_up();
        left_rotation_down();
        up_rotation_right();
        down_rotation_left();
        
        right_rotation_up();
        left_rotation_down();
        up_rotation_right();
        down_rotation_left();
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
