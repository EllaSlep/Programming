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

void set(mp3* music, FILE* in, char* command, char* set_value)
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
            strcpy(music->song_name, set_value);
            printf("Song name:\t\t%s\n", music->song_name);
        }
        else if (!strcmp(command, "TPE1"))
        {
            strcpy(music->artist_name, set_value);
            printf("Artist name:\t\t%s\n", music->artist_name);
        }
        else if (!strcmp(command, "COMM"))
        {
            strcpy(music->descrition, set_value);
            printf("Description:\t\t%s\n", music->descrition);
        }
        else if (!strcmp(command, "TALB"))
        {    
            strcpy(music->albom_name, set_value);
            printf("Albom name:\t\t%s\n", music->albom_name);
        }
        else if (!strcmp(command, "TYER"))
        {
            strcpy(music->year, set_value);
            printf("Year:\t\t%s\n", music->year);
        }
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
    
    if (!strcmp(buf, "--set"))
    {
        char *prop_name;
        buf = strtok(NULL, "=");
        prop_name = buf;

        char *set_value;
        buf = strtok(argv[3], "=");
        buf = strtok(NULL, "=");
        set_value = buf;
        set(music, in, prop_name, set_value);
    }

    printf("\nDONE\n");
    return 0;
}