#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define MAX_FILE_NAME 255

//queue
typedef struct node{
    char* value;
    struct node* next;
}node;

void push(node** head, char* data){
    node* tmp = malloc(sizeof(node));
    tmp->value = calloc(strlen(data) + 1, sizeof(char));
    strcpy(tmp->value, data);
    tmp->next = *head;
    (*head) = tmp;
}

node* get_second_last(node*head){
    if (head == NULL)
        exit(-2);

    if (head->next == NULL)
        return NULL;

    while (head->next->next)
        head = head->next;
    return head;
}

char* pop_back(node** head) {
    char* rez;
    node *second_last = NULL;
    if (!head || !(*head))
        exit(-1);
    second_last = get_second_last(*head);

    if (second_last == NULL){
        rez = (*head)->value;
        free(*head);
        *head = NULL;
    }else{
        rez = second_last->next->value;
        free(second_last->next);
        second_last->next = NULL;
    }
    return rez;
}
//end of queue

int digits(uint64_t x){
    int rez = 1;
    while (x > 10){
        rez++;
        x /= 10;
    }
    return rez;
}

void get_info(char **files, int file_number) {

    remove("info.txt");
    FILE *info = fopen("info.txt", "wb");
    FILE *current_file;
    if (info == NULL){
        printf("CAN'T OPEN THE FILE: %s\n", "info.txt");
        exit(-1);
    }

    uint32_t header_size = 2;
    for (int i = 0; i < file_number; i++){
        uint64_t file_size;
        FILE *temp = fopen(files[i], "rb");
        fseek(temp, 0, SEEK_END);
        file_size = ftell(temp);
        fclose(temp);
        header_size += (int) strlen(files[i]) + digits(file_size) + 4;
    }
    fwrite(&header_size, 4, 1, info);
    fwrite("||", 1, 2, info);

    for (int i = 0; i < file_number; i++) {
        current_file = fopen(files[i], "rb");
        if (current_file == NULL){
            printf("CAN'T OPEN THE FILE: %s\n", files[i]);
            exit(-1);
        } 

        fseek(current_file, 0, SEEK_END);    // записываем размер архивируемого файла(доходя до конца)
        uint64_t file_size = ftell(current_file);
        int d = digits(file_size);
        char *str_file_size = calloc(d, sizeof(char));
        sprintf(str_file_size, "%lld", file_size);
        fwrite(str_file_size, 1, d, info);
        fwrite("||", 1, 2, info);

        fclose(current_file);
        
        char *current_file_name; // записываем путь до архивируемого файла
        if (strrchr(files[i], '\\') == NULL) {
            current_file_name = calloc(strlen(files[i]), sizeof(char));
            strcpy(current_file_name, files[i]);
        } else {
            char *current_file_name = calloc(strlen(files[i]), sizeof(char));
            strcpy(current_file_name, strrchr(files[i], '\\'));
        }

        fputs(current_file_name, info);
        fwrite("||", 1, 2, info);
    }
    fclose(info);
}

void create(char **files, int file_number, char *arc_name) {
    FILE *arc = fopen(arc_name, "wb");
    FILE *current_file;
    if (arc == NULL){
        printf("CAN'T OPEN THE FILE: %s\n", arc_name);
        exit(-1);
    } 

    get_info(files, file_number);
    FILE *info = fopen("info.txt", "rb");
    if (info == NULL){
        printf("CAN'T OPEN THE FILE: %s\n", "info.txt");
        exit(-1);
    }

    char byte;

    while (!feof(info)) {
        if (fread(&byte, 1, 1, info) == 1) {
            fwrite(&byte, 1, 1, arc);
        }
    }

    fclose(info);
    remove("info.txt");

    for (int i = 0; i < file_number; i++) {
        current_file = fopen(files[i], "rb");
        if (current_file == NULL){
            printf("CAN'T OPEN THE FILE: %s\n", files[i]);
            exit(-1);
        }
        while (!feof(current_file)) {
            if (fread(&byte, 1, 1, current_file) == 1) {
                fwrite(&byte, 1, 1, arc);
            }
        }
        fclose(current_file);
        remove(files[i]);
    }

    fclose(arc);
}

void extract(char* arc_name){
    FILE *arc = fopen(arc_name, "rb");
    if (arc == NULL){
        printf("CAN'T OPEN THE FILE: %s\n", arc_name);
        exit(-1);
    }
    int info_block_size;
    fread(&info_block_size, 4, 1, arc);

    char *info_block = calloc(info_block_size + 1, sizeof(char));
    fread(info_block, 1, info_block_size, arc);

    info_block[info_block_size] = '\0';

    int token_count = 0;
    node *tokens; 
    char *tok = strtok(info_block, "||");
    while(tok){
        if(strlen(tok) == 0)
            break;
        push(&tokens, tok);
        tok = strtok(NULL, "||");
        ++token_count;
    }
    free(info_block);
    int file_number = token_count / 2;

    char byte;

    for (int i = 0; i < file_number; i++){
        char* file_size = pop_back(&tokens);
        char* file_name = pop_back(&tokens);
        FILE *current_file = fopen(file_name, "wb");
        if (current_file == NULL){
            printf("\t\tCAN'T OPEN THE FILE: %s\n", file_name);
            exit (-1);
        }

        uint64_t intSize = atoll(file_size);

        for (uint64_t j = 0; j < intSize; j++){
            if (fread(&byte, 1, 1, arc) == 1){
                fwrite(&byte, 1, 1, current_file);
            }
        }
        fclose(current_file);
        free(file_size);
        free(file_name);
    }

    fclose(arc);
    remove(arc_name);
}

void list(char* arc_name){
    FILE *arc = fopen(arc_name, "rb");
    if (arc == NULL){
        printf("\t\tCAN'T OPEN THE FILE: %s\n", arc_name);
        exit(-1);
    }
    int info_block_size;
    fread(&info_block_size, 4, 1, arc);

    char *info_block = calloc(info_block_size + 1, sizeof(char));
    fread(info_block, 1, info_block_size, arc);

    info_block[info_block_size] = '\0';

    int token_count = 0;
    node *tokens;
    char *tok = strtok(info_block, "||");
    while(tok){
        if(strlen(tok) == 0)
            break;
        push(&tokens, tok);
        tok = strtok(NULL, "||");
        ++token_count;
    }
    free(info_block);

    int file_number = token_count / 2;

    printf("\n\t\tThere are %d files in %s:\n", file_number, arc_name);

    for (int i = 0; i < file_number; i++){
        char* file_size = pop_back(&tokens);
        char* file_name = pop_back(&tokens);

        printf("\t\t•\t%s\n", file_name);

        free(file_size);
        free(file_name);
    }

}

int main(int argc, char **argv) {
    if (argc < 4){
        printf("\nERROR:\tInvalid number of arguments\n\n");
        exit(-1);
    } else {
        char* arc_name = calloc(MAX_FILE_NAME, sizeof(char));
        char** files = calloc(argc, sizeof(char*));
        int file_number = 0;

        printf("\n\t############# ARCHIVE MAKER #############\n\n");
        for (int i = 1; i < argc; i++){
            if (!strcmp("--file", argv[i])){
                arc_name = argv[i+1];
            }
        }

        if (strlen(arc_name) == 0){
            printf("\nERROR:\tArchive file_name not found\n");
            exit(-1);
        }

        for (int i = 1; i < argc; i++){
            if (!strcmp("--create", argv[i])){
                for (int j = i + 1; j < argc; j++){
                    files[file_number] = argv[j];
                    file_number++;
                }
                create(files, file_number, arc_name);
                printf("\n\t\tARCHIVE CREATED\n");
            }
            else if (!strcmp("--extract", argv[i])){
                extract(arc_name);
                printf("\n\t\tARCHIVE EXTRACTED\n");
            }
            else if (!strcmp("--list", argv[i])){
                list(arc_name);
            }
        }
    }

    printf("\n\t########################################\n");
    return 0;
}