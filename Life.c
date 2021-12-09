#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

//#define DEBUG

#define HEADER_SIZE 62// Заголовок BMP составляет 54 байта + 8 байтов палитры(BITMAPFILEHEADER(14б)+BITMAPINFO(40б))
#define MAX_PATH_LEN 200
#define MAX_NAME_LEN 120

#ifdef DEBUG
    #define print_debug(format, ...) printf("%d\t" format, __LINE__, ##__VA_ARGS__)
#else
    #define print_debug(format, ...)
#endif

typedef struct image{
    uint8_t *header;
    uint8_t *image;//массив для картинки
    uint8_t *data;//само изображение
    int file_size;
    int header_size;
}image;

image bmp_to_image(FILE *f, int* _width, int* _height){
    image rez;//будем заносить информацию в структуру rez
    uint8_t *header = malloc(HEADER_SIZE * sizeof(uint8_t));
    rez.header_size = HEADER_SIZE; // Заголовок BMP составляет 54 байта + 8 байтов палитры
    fread(header, 1, HEADER_SIZE, f);

    uint32_t offset = header[10] + (((uint8_t)header[11]) << 8) + (((uint8_t)header[12]) << 16) + (((uint8_t)header[13]) << 24);//offset-смещение байт

    int width = header[18] + (((uint8_t)header[19]) << 8) + (((uint8_t)header[20]) << 16) + (((uint8_t)header[21]) << 24);
    int height = header[22] + (((uint8_t)header[23]) << 8) + (((uint8_t)header[24]) << 16) + (((uint8_t)header[25]) << 24);
    if (offset > HEADER_SIZE){
        free(header);
        header = malloc(offset * sizeof(uint8_t));
        fseek(f, 0, SEEK_SET);
        fread(header, 1, offset, f);
        rez.header_size = (int) offset;
    }
    print_debug("offset = %d\n", offset);

    // наше колличество байт должно быть кратно 4
    int lineSize = (width / 32) * 4 + (width % 32 != 0 ? 4 : 0);//наша ширина в байтах с округлением
    int file_size = lineSize * height;//ширина*высоту=file_size

    uint8_t *img = malloc(width * height);
    uint8_t *data = malloc(file_size); // готовим место для картинки

    fseek(f, (long) offset, SEEK_SET);
    fread(data, 1, file_size, f);

    print_debug("width = %d; height = %d; bytes in line: %d; total size: %d \n", width, height, lineSize , file_size);//выведем высоту и ширину

    // декодируем биты
    int current_byte;
    for(int i = 0, reversed_i = height - 1; i < height ; i++, reversed_i--) {//идём с левого нижнего угла
        for(int j = 0; j < width; j++) {
            current_byte = j / 8;

            uint8_t data_byte = data[i * lineSize + current_byte];//скинируемая линия

            uint8_t mask = 0x80 >> j % 8; // 2^7
            int pos = reversed_i * width + j;
            img[pos] = (data_byte & mask) ? 1 : 0;
        }
    }

    *_width = width; 
    *_height = height;
    rez.header = header;
    rez.image = img;
    rez.data = data;
    rez.file_size = file_size;
    return rez;
}

void matrix_to_data(int n, int m, uint8_t **matrix, uint8_t *data){
    int current_position = 0;
    uint8_t current_byte = 0;

    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= m; j++) {

            uint8_t mask = 0x80 >> (j - 1) % 8;
            if (matrix[i][j] == '0') {
                current_byte = current_byte | mask;
            }

            if ((j % 8) == 0 || j == m) { // кладём 8 бит в текущий байт
                data[current_position] = current_byte;
                current_position++;
                current_byte = 0;
                mask = 0x80;
            }
        }
        while ((current_position) % 4 != 0) {
            current_position++;
        }
    }
}

int count_neigbours(int count, uint8_t **current, int x, int y){
    for (int k = -1; k <= 1; k++){
        for (int p = -1; p <= 1; p++){
            if (current[x + k][y + p] == '1'){
                count++;
            }
        }
    }
    return count;
}

uint8_t **life_generation(int n, int m, uint8_t **current, uint8_t **target){
    for (int i = 1; i < n + 1; i++){
        for (int j = 1; j < m + 1; j++){
            if (current[i][j] == '0'){//если эта клетка не живая
                int count = count_neigbours(0, current, i, j);
                if (count == 3){//если у нас 3 живых соседа -> новая жизнь
                    //print_debug("live %d %d %d\n", i, j, target[i][j]);
                    target[i][j] = '1';
                }
                else{//иначе клетка умирает
                    target[i][j] = '0';
                }
            }
            else if (current[i][j] == '1'){//если клетка уже была живая
                int count  = count_neigbours(-1, current, i, j);
                if (count != 2 && count != 3){//если 2-3 живых соседа, клетка продолжает жить
                    //print_debug("die %d %d %d\n", i, j, target[i][j]);
                    target[i][j] = '0';
                }
                else{//иначе умирает
                    target[i][j] = '1';
                }
            }
        }
    }
    print_debug("\n");
    return target;
}

void check_argv(int argc, char *argv[], char *file_name, char *directory_name, uint64_t max_generation, uint32_t step){
    if (argc < 5 || argc > 9 || (argc % 2 == 0)){
        if (argc < 5){
            printf("lack of arguments\n");
            exit(-1);
        }
        if (argc > 9){
            printf("too many arguments\n");
            exit(-1);
        }
        if (argc % 2 == 0){
            printf("one of parameters doesn't have indentification\n");
            exit(-1);
        }
    } 
    for (int i = 1; i < argc; i += 2){
        print_debug("%s ", argv[i]);
        if (strcmp(argv[i], "--input") == 0){
            file_name = argv[i + 1];
            print_debug("%s\n", file_name);
        }
        else if (strcmp(argv[i], "--output") == 0){
            directory_name = argv[i + 1];
            print_debug("%s\n", directory_name);
        }
        else if (strcmp(argv[i], "--max_iter") == 0){
            max_generation = atoi(argv[i + 1]);
            print_debug("%lld\n", max_generation);
        }
        else if (strcmp(argv[i], "--dump_freq") == 0){
            step = atoi(argv[i + 1]);
            print_debug("%u\n", step);
        }
        else {
            print_debug("wrong parameter: %s\n", argv[i]);
            exit(-1);
        }
    } 
}

uint8_t **new_arr(int n, int m){
    uint8_t **matrix = (uint8_t**) malloc((n + 2) * sizeof (uint8_t*));
    for (int i = 0; i < n + 2; i++){
        matrix[i] = (uint8_t*) malloc((m + 2) * sizeof (uint8_t));
    }
    return matrix;
}

int main(int argc, char *argv[]) {

    char *file_name;
    char *directory_name;
    uint64_t max_generation = (uint64_t) INFINITY;
    uint32_t step = 1;

    //check_argv(argc, argv, file_name, directory_name, max_generation, step);

    file_name="/Users/macbook/Desktop/ИТМО/программирование/Pulsar.bmp";
    directory_name="/Users/macbook/Desktop/ИТМО/программирование";
    max_generation=2;
    step=1;

    FILE *in;
    in = fopen(file_name, "rb");

    if (in == NULL){
        printf("can't open file %s\n", file_name);
        return 1;
    }

    int width, height;
    //читаем файл и разбиваем его на структуру
    image bmp_struct = bmp_to_image(in, &width, &height);
    uint8_t *img = bmp_struct.image;
    uint8_t *bmp_header = bmp_struct.header;
    uint8_t *data = bmp_struct.data;

    int n = height;
    int m = width;
    
//объявляем 2 двумерных массива- они в начале одинаковы(это наша картинка). берём 1 массив и проводим 1 итерацию игры(образуем 2е поколение)->
//  ->записываем во второй массив. Теперь берём второй массив и делаем итерацию с ним в игре -> pзаписываем в первый массив
//  В итоге получается некий шаг(т.е один массив хранит текущее значение картинки, а другой предыдущее
// В тот в котором хранится предыдущее мы записываем новый шаг(новое значение картинки) и он становится текущим
    uint8_t **matrix = new_arr(n, m);
    uint8_t **arr = new_arr(n, m);

    for(int i = 0 ; i < height ; i++){
        for(int j = 0 ; j < width ; j++){
            if (img[i * width + j]){//если клетка не закрашена ->0

                matrix[i + 1][j + 1] = '0';
                arr[i + 1][j + 1] = '0';
            }
            else{
                //print_debug("%c ", '1');
                matrix[i + 1][j + 1] = '1';
                arr[i + 1][j + 1] = '1';
            }

        }
    }

    uint64_t iter = 0;
    uint32_t step_counter = 0;
    int file_counter = 0;
    uint8_t **current_matrix;//тот массив который мы будем записывать в файл после игры
    //начинаем выводить поколения игры
    while (iter < max_generation){//проверяем сколько поколений
        if (iter % 2 == 0){
            life_generation(n, m, arr, matrix);//игру на 1 поколение и записываем его в файл если это поколение нужной частоты
            current_matrix = matrix;//новый массив который запишем в новый файл
        }
        else {
            life_generation(n, m, matrix, arr);
            current_matrix = arr;//новый массив который запишем в новый файл
        }
        step_counter++;//частота
        if (step_counter == step){//если это нужное нам повторение которое мы должны вывести
            FILE *out;
            step_counter = 0;//как только увидели что поколение сошлось мы сбрасываем счётчик
            file_counter++;

            //создам новый файл в который запишем новую картинку
            char file_path[MAX_PATH_LEN] = "";
            char current_slice[MAX_NAME_LEN] = "";
            //strcpy(current_slice, slice_name);
            int length = snprintf(NULL, 0, "%d", file_counter);
            char str[length + 1];
            snprintf(str, length + 1, "%d", file_counter);//поколение начинается с 1 -> +1
            print_debug("%s\n", str);
            strcat(current_slice, str);
            print_debug("current_slice = %s\n", current_slice);
            strcat(file_path, directory_name);
            strcat(file_path, "/");
            strcat(file_path, current_slice);
            strcat(file_path, ".bmp\0");
            print_debug("%s\n", file_path);

            out = fopen(file_path, "wb");
            if (out == NULL){
                printf("can't open file %s\n", file_path);
                return 1;
            }
            print_debug("fine\n");
            matrix_to_data(n, m, current_matrix, data);//записываем в виде картинки(data) полученый массив(current_matrix)
            fwrite(bmp_header, sizeof(uint8_t), bmp_struct.header_size, out);//перезаписываем header в новый файл
            fwrite(data, sizeof(uint8_t), bmp_struct.file_size, out);
            print_debug("make image slice\n");
        }
        iter++;
    }


    
    fclose(in);
    free(matrix);
    free(arr);
    free(data);
    free(img);
    print_debug("\nDONE\n");
    return 0;
}