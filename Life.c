#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <iso646.h>
#include <string.h>

#define DEBUG

#ifdef DEBUG
    #define print_debug(format, ...) printf("%d\t" format, __LINE__, ##__VA_ARGS__)
#else
    #define print_debug(format, ...)
#endif

#define ALIVE  1
#define NOT_ALIVE 0
#define MAX_DIRECTORY_LEN 1000

int MAX_ITER; // (inf)
int DUMP_FREQ; // save frequency
char* INPUT_FILE_NAME;
char* DIRECTORY_NAME;

#pragma pack(push, 1)
typedef struct stBitMapFile {

    uint16_t bmp_header_Type;            //Метка BM
    uint32_t bmp_header_Size;            //Длина в байтах
    uint16_t bmp_header_res1;            //Резерв1
    uint16_t bmp_header_res2;           //Резерв2
    uint32_t bmp_header_end;            //Смещение области данных(положение пиксельных данных)

    //Начало BITMAP_INFO:(версия 3(не CORE))
    uint32_t bmp_information_Size;            //Длина BITMAP_INFO
    int32_t bmp_information_width;                //Ширина картинки
    int32_t bmp_information_height;              //высота картинки
    uint16_t bmp_information_planes;            //Число плоскостей
    uint16_t bmp_information_bit_per_pixel;            //Бит на пиксел
    uint32_t bmp_information_compression;            //Тип сжатия
    uint32_t bmp_information_image_size;            //Размер изображения в байтах
    int32_t bmp_information_X_pixels;                //Разрешение по горизонтали
    int32_t bmp_information_Y_pixels;                //Разрешение по вертикали
    uint32_t bmp_information_colours_used;            //Количество используемых цветов
    uint32_t bmp_information_colours_major;            //Количество основных цветов
} bitMapFile;
#pragma pack(pop)

void freePixelArray(int height, int** arr){
    print_debug("calling freePixelArray\n");

    int i = 0;
    while (i < height && arr[i] != NULL){
        free(arr[i]);
        ++i;
    }
    /*for (int i = 0; i < height; i++){
        free(arr[i]);
    }*/
    free(arr);

    print_debug("freePixelArray correct\n");
}

int** mallocPixelArray(int height, int width){
    print_debug("calling mallocPixelArray\n");

    int** resArr = (int**) calloc(height, sizeof (int));
    for (int i = 0; i < height; i++){
        resArr[i] = (int*)calloc(width, sizeof(int));
    }

    print_debug("mallocPixelArray correct\n");
    return resArr;
}

//мы читаем наш файл и переводим
int** bmpToPixelsArray(int height, int width, FILE* in, bitMapFile bmp){
    print_debug("calling bmpToPixelsArray\n");

    int **resArr = mallocPixelArray(height, width);
    fseek(in, (int)bmp.bmp_header_end, SEEK_SET);

    //мы находим ширину в байтах деля на 8 и если у нас не делится без остатка,то добавляем 1 байт(что б не было обрезания)
    //теперь scanLineSize это ширина картинки
    int realWidth = (width / 8) + ((width % 8 > 0) ? 1 : 0);    // действительная ширина(в байтах) где находятся значащие биты
    int scanLineSize = realWidth;
    if (realWidth % 4 != 0){//байт в строке должно быть кратно 4
        scanLineSize = realWidth + (4 - (realWidth % 4));
    }
    int scanLine[scanLineSize]; //char* scanLine = calloc(scanLineSize, sizeof(char));

    for (int y = height - 1; y >= 0; y--){  // записываем снизу вверх, т.к. пиксели считываются с левого нижнего угла
        fread(scanLine, 1, scanLineSize, in);  // cчитываем строку с учётом отступов
        for (int x = 0; x < width; x++){
            int curBytePos = x / 8;//идём по байтам
            int curBit = 1 << (7 - x % 8);
            int pixel = scanLine[curBytePos] & curBit;
            if (pixel == 0){        // если бит равен 1(белый цвет), то будем помечать его как живую клетку, если равен нулю - нулём(мёртв)
                resArr[y][x] = ALIVE;
            }
            else{
                resArr[y][x] = NOT_ALIVE;
            }
        }
    }
    print_debug("bmpToPixelsArray correct\n");
    //free(scanLine);
    return resArr;
}

void pixelArrayToBmp(int** pixelArr, int height, int width, char* offset, int generationNumber, int offsetLen, char* directoryName){
    print_debug("calling pixelArrayToBmp\n");

    char strGenNumber[10]; // = calloc(10, sizeof(char));
    sprintf(strGenNumber,"%d",generationNumber);
    char fullFilePath[MAX_DIRECTORY_LEN]; // = calloc(MAX_DIRECTORY_LEN, sizeof(char));
    strcpy(fullFilePath, directoryName);
    strcat(fullFilePath, "/");
    strcat(fullFilePath, strGenNumber);
    strcat(fullFilePath, ".bmp");

    print_debug("%s + / + %s + .bmp = %s\n", directoryName, strGenNumber, fullFilePath);
    FILE *out = fopen(fullFilePath, "wb");
    if (out == NULL){
        printf("Can't open a file\n");
        exit(-1);
    }

    fwrite(offset, 1, offsetLen, out); // записываем все байты до самой битмапы

    int realWidth = (width / 8) + ((width % 8 > 0) ? 1 : 0);    // действительная ширина где находятся значащие биты
    int scanLineSize = realWidth;
    if (realWidth % 4 != 0){
        scanLineSize = realWidth + (4 - (realWidth % 4));
    }

    int scanLine[scanLineSize];

    print_debug("before writing information it's okey!\n");

//ERROR//

    /* int y = height - 1, x = 0;
    print_debug("y = %d\n", y);
    while (pixelArr[y][x] == NULL){
        --y;
    }
    print_debug("y = %d\n", y); */
    int y = height - 1, x;
    print_debug("y = %d\n", y);
    while (pixelArr[y] == NULL){
        --y;
    }
    print_debug("y = %d\n", y);

    while (y >=0){
        x = 0;
        while (x < width && pixelArr[y][x] != NULL){
            int curBytePosition = x / 8;
            if (pixelArr[y][x] == 0){
                scanLine[curBytePosition] = (char)(1 << (7 - x % 8)) bitor scanLine[curBytePosition]; //bitor = или
            }
            ++x;
        }
        fwrite(scanLine, 1, scanLineSize, out);
        --y;
    }
    /*
    for (int y = height - 1; y >= 0; y--){
        int scanLine[scanLineSize]; //char* scanLine = calloc(scanLineSize, sizeof(char));
        for (int x = 0; x < width; x++){
            int curBytePosition = x / 8;
            if (pixelArr[y][x] == 0){
                scanLine[curBytePosition] = (char)(1 << (7 - x % 8)) bitor scanLine[curBytePosition];//bitor = или
            }
        }
        fwrite(scanLine, 1, scanLineSize, out);
        //free(scanLine);
    }
    */
    
    fclose(out);
    //free(fullFilePath);
    //free(strGenNumber);

    print_debug("pixelArrayToBmp correct\n");
}

//если клетка жива -> return 1
int neighbourCheck(int **pixelArr, int row, int col, int height, int width) {//  row-строка    col-столбец

    if (row < 0 || row >= height || col < 0 || col >= width) {
        return 0;
    } else if (pixelArr[row][col] != ALIVE){
        return 0;
    }
    else {
        return 1;
    }
}

int getNeighborCount(int **table, int row, int col, int height, int width) {//смотрим сколько у нас живых соседних клеток
    
    int neighborCounter = 0;
    neighborCounter += neighbourCheck(table, row - 1, col - 1, height, width);
    neighborCounter += neighbourCheck(table, row - 1, col, height, width);
    neighborCounter += neighbourCheck(table, row - 1, col + 1, height, width);
    neighborCounter += neighbourCheck(table, row, col - 1, height, width);
    neighborCounter += neighbourCheck(table, row, col + 1, height, width);
    neighborCounter += neighbourCheck(table, row + 1, col - 1, height, width);
    neighborCounter += neighbourCheck(table, row + 1, col, height, width);
    neighborCounter += neighbourCheck(table, row + 1, col + 1, height, width);
    return neighborCounter;
}

int **gameLife(int **pixelArr, int height, int width) {
    print_debug("calling gameLife\n");
    
    print_debug("doing tempArr\n");

    int **tempArr = mallocPixelArray(height, width);
    print_debug("tempArr completed\n");

    int neighbourCnt;

    int y = 0, x = 0;
    while (y < height && tempArr[y][x] != NULL){
        x = 0;
        while (x < width && tempArr[y][x] != NULL){
            neighbourCnt = getNeighborCount(pixelArr, y, x, height, width);
            if ((neighbourCnt == 3) or
                (neighbourCnt == 2 and pixelArr[y][x] == ALIVE)) {
                tempArr[y][x] = ALIVE;
            }
            else {
                tempArr[y][x] = NOT_ALIVE;
            }
            ++x;
        }
        ++y;
    }
    /*for (int y = 0; y < height; y++) {                  // проверка всех правил игры
        for (int x = 0; x < width; x++) {
            neighbourCnt = getNeighborCount(pixelArr, y, x, height, width);
            if ((neighbourCnt == 3) or
                (neighbourCnt == 2 and pixelArr[y][x] == ALIVE)) {
                tempArr[y][x] = ALIVE;
            }
            else {
                tempArr[y][x] = NOT_ALIVE;
            }
        }
    }*/

    freePixelArray(height, pixelArr);
    print_debug("gameLife correct\n");
    return tempArr;
}

int main(int argc, char** argv) {

    MAX_ITER = 1;
    DUMP_FREQ = 1;
/*
    if (argc < 5){ 
        printf("Invalid number of arguments\n");
        exit(-2);
    }
    for (int i = 1; i < argc; i += 2){
        if (!strcmp("--input", argv[i])){
            INPUT_FILE_NAME = argv[i + 1];
        }
        else if (!strcmp("--output", argv[i])){
            DIRECTORY_NAME = argv[i + 1];
        }
        else if (!strcmp("--max_iter", argv[i])){
            MAX_ITER = atoi(argv[i + 1]);
        }
        else if (!strcmp("--dump_freq", argv[i])){
            DUMP_FREQ = atoi(argv[i + 1]);
        }

    }

    if (INPUT_FILE_NAME == NULL){
        printf("The input file name is not specified\n");
        exit(-1);
    }
    if (DIRECTORY_NAME == NULL){
        printf("The output directory is not specified\n");
        exit(-1);
    }


*/
    DIRECTORY_NAME="/Users/macbook/Desktop/ИТМО/программирование";

    //FILE *in = fopen(INPUT_FILE_NAME, "rb");
    FILE *in = fopen("/Users/macbook/Downloads/Pulsar.bmp", "rb");
    if (in == NULL){
        printf("Can't open a file\n");
        exit(-1);
    }

    bitMapFile bmp;

    fread(&bmp, 1, sizeof(bitMapFile), in);//читаем Header
    char offset[bmp.bmp_header_end];  //= calloc(bmp.bmp_header_end, sizeof(char));//bmp_header_end-положение пиксельных данных
    fseek(in, 0, SEEK_SET);//перемещаемся на пиксельные данные
    fread(offset, 1, bmp.bmp_header_end, in);//offset-где находятся пиксельные данные

    int **pixelArr = bmpToPixelsArray(bmp.bmp_information_height, bmp.bmp_information_width, in, bmp);//pixelArr - картинка в виде массива


    for (int i = 0; i < MAX_ITER; i++){
        pixelArr = gameLife(pixelArr, bmp.bmp_information_height, bmp.bmp_information_width);//запускаем игру 1 раз(т.е продвинемся на 1 поколение вперёд)
        //pixelArr-наша новая картинка после завершения 1 расстановки
        if (i % DUMP_FREQ == 0){//DUMP_FREQ частота сохранения поколения в виде картинки(т.е каждый DUMP_FREQй раз мы сохраняем картинку)
            //конвертируем массив обратно в картинку. Поколения начинаются с 1 -> i+1
            pixelArrayToBmp(pixelArr, bmp.bmp_information_height, bmp.bmp_information_width, offset, i + 1, (int)bmp.bmp_header_end, DIRECTORY_NAME);
        }
    }


    freePixelArray(bmp.bmp_information_height, pixelArr);
    fclose(in);
    //free(offset);
    //free(INPUT_FILE_NAME);
    //free(DIRECTORY_NAME);
}