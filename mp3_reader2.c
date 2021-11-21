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
    fseek(in, 0, SEEK_END);
    return ftell(in) - ID3_MAX_SIZE;
}

int main (int argc, char * argv[])
{
    mp3 *music = NULL;
    FILE *in;
    char *filename = strtok(argv[1], '=');
    filename = strtok(NULL, '=');
    
    in = fopen(filename, "r");
    if (in == NULL)
    {
        printf("Can't open file %s\n", filename);
        exit(-1);
    }

    char* tmp = calloc(ID3_MAX_SIZE, sizeof(char));
    fseek(in, read_mp3, SEEK_SET);
    fread(tmp, 1, ID3_MAX_SIZE, in);
    music = (mp3*)tmp;
    if (music != NULL)
    {
        if (strcmp(argv[2], "--show"))
        {
            printf("Song name:\t\t%s\n", music->song_name);
            printf("Artist name:\t\t%s\n", music->artist_name);
            printf("Albom name:\t\t%s\n", music->albom_name);
            printf("Year:\t\t%s\n", music->year);
            printf("Description:\t\t%s\n", music->descrition);
            printf("Ganer:\t\t%d\n", music->ganer);
        }
        else if (strcmp(argv[2], "--get"))
        {
            char *command_name = strtok(argv[2], '=');
            command_name = strtok(NULL, '=');
            if (strcmp(command_name, "TIT2"))
            {
                printf("Song name:\t\t%s\n", music->song_name);
            }
            if (strcmp(command_name, "TPE1"))
            {
                printf("Artist name:\t\t%s\n", music->artist_name);
            }
            if (strcmp(command_name, "TIT3"))
            {
                printf("Description:\t\t%s\n", music->descrition);
            }
            if (strcmp(command_name, "TALB"))
            {
                printf("Albom name:\t\t%s\n", music->albom_name);
            }
            if (strcmp(command_name, "TYER"))
            {
                printf("Year:\t\t%s\n", music->year);
            }
        }
        else if (strcmp(argv[2], "--set"))
        {
            
        }
    }

    printf("\nDONE\n");
    return 0;
}