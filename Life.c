#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <iso646.h>
#include <string.h>


#define LIVE_CELL  1
#define NOT_LIVE_CELL 0
#define MAX_DIRECTORY_LEN 1000


int MAX_ITER; // (inf)
int DUMP_FREQ; // save frequency
char* INPUT_FILE_NAME;
char* DIRECTORY_NAME;

#pragma pack(push, 1)
typedef struct stBitMapFile {

    uint16_t bheader_type;            //Метка BM
    uint32_t bheader_size;            //Длина в байтах
    uint16_t bheader_rez1;            //Резерв1
    uint16_t bheader_rez2;           //Резерв2
    uint32_t bheader_off;            //Смещение области данных

    //Начало BITMAP_INFO:
    uint32_t binfo_size;            //Длина BITMAP_INFO
    int32_t binfo_wigth;                //Ширина картинки
    int32_t binfo_height;              //высота картинки
    uint16_t binfo_planes;            //Число плоскостей
    uint16_t binfo_bit_per_pikcel;            //Бит на пиксел
    uint32_t binfo_compress;            //Тип сжатия
    uint32_t binfo_image_size;            //Размер изображения в байтах
    int32_t binfo_x_pix;                //Разрешение по горизонтали
    int32_t binfo_y_pix;                //Разрешение по вертикали
    uint32_t binfo_colours_used;            //Количество используемых цветов
    uint32_t binfo_colours_main;            //Количество основных цветов
} BMP_file;
#pragma pack(pop)

void printUsage(char* err){
    printf("Error: %s\n", err);
    printf("%s", USAGE_MESSAGE);
}

void openCorrect(FILE* file){
    if (file == NULL){
        printUsage("Can't open a file");
        exit(-1);
    }
}

void freePixelArray(int height, int** arr){
    for (int i = 0; i < height; i++){
        free(arr[i]);
    }
    free(arr);
}

int** mallocPixelArray(int height, int width){
    int** resArr = (int**) calloc(height, sizeof (int));
    for (int i = 0; i < height; i++){
        resArr[i] = (int*)calloc(width, sizeof(int));
    }
    return resArr;
}

int** bmpToPixelsArray(int height, int width, FILE* in, BMP_file bmp){
    int **resArr = mallocPixelArray(height, width);
    fseek(in, (int)bmp.bheader_off, SEEK_SET);  // перемещаем указатель на начало считываения пикселей

    int realWidth = (width / 8) + ((width % 8 > 0) ? 1 : 0);    // действительная ширина где находятся значащие биты
    int scanLineSize = realWidth;
    if (realWidth % 4 != 0){
        scanLineSize = realWidth + (4 - (realWidth % 4));
    }
    char* scanLine = calloc(scanLineSize, sizeof(char));

    for (int y = height - 1; y >= 0; y--){  // записываем снизу вверх, т.к. пиксели считываются с левого нижнего угла
        fread(scanLine, 1, scanLineSize, in);  // cчитываем строку с учётом паддинга
        for (int x = 0; x < width; x++){
            int curBytePos = x / 8;
            int curBit = 1 << (7 - x % 8);
            int pixel = scanLine[curBytePos] & curBit;
            if (pixel == 0){        // если бит равен 1(белый цвет), то будем помечать его как 1, если равен нулю - нулём
                resArr[y][x] = LIVE_CELL;
            }
            else{
                resArr[y][x] = NOT_LIVE_CELL;
            }
        }
    }
    free(scanLine);
    return resArr;
}

void pixelArrayToBmp(int** pixelArr, int height, int width, char* offset, int generationNumber, int offsetLen, char* directoryName){

    char *strGenNumber = calloc(10, sizeof(char));
    sprintf(strGenNumber, "%d", generationNumber);
    char *fullFilePath = calloc(MAX_DIRECTORY_LEN, sizeof(char));
    strcat(fullFilePath, directoryName);
    strcat(fullFilePath, "/");
    strcat(fullFilePath, strGenNumber);
    strcat(fullFilePath, ".bmp");

    FILE *out = fopen(fullFilePath, "wb");
    openCorrect(out);

    fwrite(offset, 1, offsetLen, out); // записываем все байты до самой битмапы

    int realWidth = (width / 8) + ((width % 8 > 0) ? 1 : 0);    // действительная ширина где находятся значащие биты
    int scanLineSize = realWidth;
    if (realWidth % 4 != 0){
        scanLineSize = realWidth + (4 - (realWidth % 4));
    }

    for (int y = height - 1; y >= 0; y--){
        char* scanLine = calloc(scanLineSize, sizeof(char));
        for (int x = 0; x < width; x++){
            int curBytePosition = x / 8;
            if (pixelArr[y][x] == 0){
                scanLine[curBytePosition] = (char)(1 << (7 - x % 8)) bitor scanLine[curBytePosition];
            }
        }
        fwrite(scanLine, 1, scanLineSize, out);
        free(scanLine);
    }

    fclose(out);
    free(fullFilePath);
    free(strGenNumber);
}

int neighbourCheck(int **pixelArr, int row, int col, int height, int width) {
    if (row < 0 || row >= height || col < 0 || col >= width) {
        return 0;
    } else if (pixelArr[row][col] != LIVE_CELL){
        return 0;
    }
    else {
        return 1;
    }
}

int getNeighborCount(int **table, int row, int col, int height, int width) {
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
    int **tempArr = mallocPixelArray(height, width);
    int neighbourCnt;

    for (int y = 0; y < height; y++) {                  // проверка всех правил игры
        for (int x = 0; x < width; x++) {
            neighbourCnt = getNeighborCount(pixelArr, y, x, height, width);
            if ((neighbourCnt == 3) || (neighbourCnt == 2 && pixelArr[y][x] == LIVE_CELL)) {
                tempArr[y][x] = LIVE_CELL;
            }
            else {
                tempArr[y][x] = NOT_LIVE_CELL;
            }
        }
    }

    freePixelArray(height, pixelArr);

    return tempArr;
}

void argParse(int argc, char** argv){
    if (argc < 3){                              // число аргументов точно не может быть < 3
        printUsage("Invalid number of arguments");
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
        printUsage("The input file name is not specified");
        exit(-1);
    }
    if (DIRECTORY_NAME == NULL){
        printUsage("The output directory is not specified");
        exit(-1);
    }
}

int main(int argc, char** argv) {

    MAX_ITER = 5;
    DUMP_FREQ = 1;

    argParse(argc, argv);
    FILE *in = fopen(INPUT_FILE_NAME, "rb");
    openCorrect(in);     //проверяем, а открылась ли корректно

    BMP_file bmp;

    fread(&bmp, 1, sizeof(BMP_file), in);
    char *offset = calloc(bmp.bheader_off, sizeof(char));
    fseek(in, 0, SEEK_SET);
    fread(offset, 1, bmp.bheader_off, in);

    int **pixelArr = bmpToPixelsArray(bmp.binfo_height, bmp.binfo_wigth, in, bmp);

    for (int i = 0; i < MAX_ITER; i++){
        pixelArr = gameLife(pixelArr, bmp.binfo_height, bmp.binfo_wigth);
        if (i % DUMP_FREQ == 0){
            pixelArrayToBmp(pixelArr, bmp.binfo_height, bmp.binfo_wigth, offset, i + 1, (int)bmp.bheader_off, DIRECTORY_NAME);
        }
    }

    freePixelArray(bmp.binfo_height, pixelArr);
    fclose(in);
    free(offset);
    free(INPUT_FILE_NAME);
    free(DIRECTORY_NAME);

}