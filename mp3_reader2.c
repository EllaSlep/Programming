#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

const int header_bytes = 10;
const int frame_bytes = 11;

typedef struct ID3v2_header
{
    char ID3[3];
    char version[2];
    char flag;
    char size[4];
} ID3v2_header;

typedef struct ID3v2_frame
{
    char name[4];
    char size[4];
    char flag;
    char unicode;
} ID3v2_frame;

ID3v2_header header;
ID3v2_frame frame;

int btoi(char bytes[4], int header_or_not)
{
    if (header.version[0] == 4 || header_or_not)
    {
        return bytes[0] << 21 | bytes[1] << 14 | bytes[2] << 7 | bytes[3];
    }
    return bytes[0] << 24 | bytes[1] << 16 | bytes[2] << 8 | bytes[3];
}

void itob(int value, char *bytes, int header_or_not)
{
    int bits = 127;
    if (header.version[0] == 4 || header_or_not)
    {
        bytes[3] = (char)(value & bits);
        bytes[2] = (char)((value >> 7) & bits);
        bytes[1] = (char)((value >> 14) & bits);
        bytes[0] = (char)((value >> 21) & bits);
    }
    bytes[3] = (char)(value & bits);
    bytes[2] = (char)((value >> 8) & bits);
    bytes[1] = (char)((value >> 16) & bits);
    bytes[0] = (char)((value >> 24) & bits);
}

void show(char *file_path)
{
    FILE *in;
    int header_size;

    in = fopen(file_path, "rb");

    fread(&header, sizeof(char), header_bytes, in);
    header_size = btoi(header.size, 1);
    printf("struct size: %d\n", header_size);

    fread(&frame, 1, frame_bytes, in);
    while (frame.name[0] != 0 && ftell(in) < header_size)
    {
        int frame_size;
        char *frame_consict;

        frame_size = btoi(frame.size, 0);
        frame_consict = (char *)malloc(frame_size);
        fgets(frame_consict, frame_size, in);

        printf("pos: %5ld | id: %5s | size: %5d | value: ", ftell(in), frame.name, frame_size);
        if (frame.unicode)
        {
            printf("%s\n", frame_consict + 2);
        }
        else
        {
            printf("%s\n", frame_consict);
        }

        fread(&frame, 1, frame_bytes, in);
        free(frame_consict);
    }
    fclose(in);
}

int get(char *file_path, char *command)
{
    FILE *in;
    int header_size;
    int pos = -1;

    in = fopen(file_path, "rb");

    fread(&header, sizeof(char), header_bytes, in);
    header_size = btoi(header.size, 1);

    fread(&frame, 1, frame_bytes, in);
    while (frame.name[0] != 0 && ftell(in) < header_size)
    {
        int frame_size;
        char *frame_const;

        frame_size = btoi(frame.size, 0);
        frame_const = (char *)malloc(frame_size * sizeof(char));
        fgets(frame_const, frame_size, in);

        if (!strcmp(frame.name, command))
        {
            printf("pos: %5ld | id: %5s | size: %5d | value: ", ftell(in), frame.name, frame_size);
            if (frame.unicode)
            {
                printf("%s\n", frame_const + 2);
                pos = ftell(in) - frame_size - 10;
                return pos;
            }
            else
            {
                printf("%s\n", frame_const);
                pos = ftell(in) - frame_size - 10;
                return pos;
            }
        }
        fread(&frame, 1, frame_bytes, in);
        free(frame_const);
    }

    fclose(in);
    return pos;
}

void set(char *file_path, char *command, char *value)
{
    FILE *in, *out;
    ID3v2_frame frame_now;
    char *buf, *frame_content;
    int frame_size, last_pos, new_header, pos_now;

    in = fopen(file_path, "rb");
    out = fopen("/Users/macbook/Desktop/temp.txt", "wb");

    int pos = get(file_path, command);
    fread(&header, 1, header_bytes, in);
    buf = calloc(pos - 10, 1);
    fread(buf, 1, pos - 10, in);
    fread(&frame_now, 1, frame_bytes, in);
    frame_size = btoi(frame_now.size, 0);

    fseek(in, 0, SEEK_END);
    last_pos = ftell(in);
    fseek(in, 0, SEEK_SET);
    fread(&header, 1, header_bytes, in);

    new_header = btoi(header.size, 1) + strlen(value) - frame_size + 1;
    itob(new_header, header.size, 1);

    fwrite(&header, 1, header_bytes, out);

    fread(buf, 1, pos - 10, in);
    fwrite(buf, 1, pos - 10, out);

    fread(&frame_now, 1, frame_bytes, in);
    frame_content = (char *)malloc(frame_size * sizeof(char));
    fgets(frame_content, frame_size, in);

    itob(strlen(value) + 1, frame_now.size, 0);
    fwrite(&frame_now, 1, frame_bytes, out);
    fwrite(value, 1, strlen(value), out);

    pos_now = ftell(in);

    unsigned int *end_of_file = malloc(last_pos - pos_now);
    fread(end_of_file, 1, last_pos - pos_now, in);
    fwrite(end_of_file, 1, last_pos - pos_now, out);
    get("/Users/macbook/Desktop/temp.txt", command);

    fclose(in);
    fclose(out);
}

int main(int argc, char *argv[])
{
    char filename[200];
    /*
    char *buf = strtok(argv[1], "=");
    buf = strtok(NULL, "=");
    strcpy(filename, buf);
    buf = NULL;

    if (!strcmp(argv[2], "--show"))
    {
        show(filename);
    }

    buf = strtok(argv[2], "=");

    if (!strcmp(buf, "--get"))
    {
        char *prop_name;
        buf = strtok(NULL, "=");
        prop_name = buf;

        get(filename, prop_name);
    }

    if (!strcmp(buf, "--set"))
    {
        char *prop_name;
        buf = strtok(NULL, "=");
        prop_name = buf;

        char *set_value;
        buf = strtok(argv[3], "=");
        buf = strtok(NULL, "=");
        set_value = buf;

        set(filename, prop_name, set_value);
    }*/

    printf("\nFIRST mp3\n");
    strcpy(filename, "/Users/macbook/Desktop/C418 - Sweden (Minecraft OST).mp3");
    printf("\nFunction show\n");
    show(filename);
    printf("\nFunction get\n");
    get(filename, "TIT2");
    printf("\nFunction set\n");
    set(filename, "TPE1", "Test");

    printf("\nSECOND mp3\n");
    strcpy(filename, "/Users/macbook/Music/iTunes/iTunes Media/Music/Ou noy O no/Unknown Album/2-08 o no no no (not clip).mp3");
    printf("\nFunction show\n");
    show(filename);
    printf("\nFunction get\n");
    get(filename, "TIT2");
    printf("\nFunction set\n");
    set(filename, "TSSE", "Test");

    printf("\nDONE\n");
    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ID3_MAX_SIZE 128

typedef struct mp3
{
    char structure[3];
    char song_name[30];
    char artist_name[30];
    char albom_name[30];
    char year[4];
    char descrition[100];
    unsigned int ganer;
}mp3;

long read_mp3(FILE *in)
{
    fseek(in, 0, SEEK_END); //в версии ID3v2.4 запись о файле содержиться в конце файла (последние 128 байт) => ищем в конце
    return ftell(in) - ID3_MAX_SIZE;
}

void show(mp3* music, FILE* in)
{
    char* tmp = (char*)malloc(ID3_MAX_SIZE * sizeof(char));
    if (tmp == NULL)
    {
        printf("Can't find memory\n");
        exit(-1);
    }
    fseek(in, read_mp3(in), SEEK_SET);
    fread(tmp, 1, ID3_MAX_SIZE, in);
    music = (mp3*)tmp;
    if (music != NULL)
    {
        printf("Song name:\t\t%s\n", music->song_name);
        printf("Artist name:\t\t%s\n", music->artist_name);
        printf("Albom name:\t\t%s\n", music->albom_name);
        printf("Year:\t\t%s\n", music->year);
        printf("Description:\t\t%s\n", music->descrition);
        printf("Ganer:\t\t%d\n", music->ganer);
    }
    free(tmp);
}

void get(mp3* music, FILE*in, char *command)
{

    char* tmp = (char*)malloc(ID3_MAX_SIZE * sizeof(char));
    if (tmp == NULL)
    {
        printf("Can't find memory\n");
        exit(-1);
    }
    fseek(in, read_mp3(in), SEEK_SET);
    fread(tmp, 1, ID3_MAX_SIZE, in);
    music = (mp3*)tmp;

    if (music != NULL)
    {
        if (!strcmp(command, "TIT2"))
        {
            printf("Song name:\t\t%s\n", music->song_name);
        }
        else if (!strcmp(command, "TPE1"))
        {
            printf("Artist name:\t\t%s\n", music->artist_name);
        }
        else if (!strcmp(command, "COMM"))
        {
            printf("Description:\t\t%s\n", music->descrition);
        }
        else if (!strcmp(command, "TALB"))
        {
            printf("Albom name:\t\t%s\n", music->albom_name);
        }
        else if (!strcmp(command, "TYER"))
        {
            printf("Year:\t\t%s\n", music->year);
        }
    }
    free(tmp);
}

void set(mp3* music, FILE* in, FILE* out, char* command, char* set_value)
{
    while (!feof(in))
    {
        char c = fgetc(in);
        fputc(c, out);
    }
    fputs(set_value, out);

    char* tmp = (char*)malloc(ID3_MAX_SIZE * sizeof(char));
    if (tmp == NULL)
    {
        printf("Can't find memory\n");
        exit(-1);
    }
    fseek(out, read_mp3(out) - strlen(set_value), SEEK_SET);
    fread(tmp, 1, ID3_MAX_SIZE + strlen(set_value), out);
    music = (mp3*)tmp;
    if (music != NULL)
    {
        printf("Song name:\t\t%s\n", music->song_name);
        printf("Artist name:\t\t%s\n", music->artist_name);
        printf("Albom name:\t\t%s\n", music->albom_name);
        printf("Year:\t\t%s\n", music->year);
        printf("Description:\t\t%s\n", music->descrition);
        printf("Ganer:\t\t%d\n", music->ganer);
    }
    free(tmp);
}

int main (int argc, char * argv[])
{
    mp3 *music = NULL;
    FILE *in;
    char filename[100];

    char *buf = strtok(argv[1], "=");
    buf = strtok(NULL, "=");
    strcpy(filename, buf);
    buf = NULL;
    in = fopen(filename, "r");

    if (!strcmp(argv[2], "--show"))
    {
        show(music, in);
    }

    buf = strtok(argv[2], "=");

    if (!strcmp(buf, "--get"))
    {
        char *prop_name;
        buf = strtok(NULL, "=");
        prop_name = buf;
        get(music, in, prop_name);
    }

    FILE*out = fopen("/Users/macbook/Desktop/temp.txt", "w");
    if (!strcmp(buf, "--set"))
    {
        char *prop_name;
        buf = strtok(NULL, "=");
        prop_name = buf;

        char *set_value;
        buf = strtok(argv[3], "=");
        buf = strtok(NULL, "=");
        set_value = buf;
        set(music, in, out, prop_name, set_value);
    }

    printf("\nDONE\n");
    return 0;
}
*/