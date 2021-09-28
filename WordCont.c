#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[])
{
    FILE *in = fopen(argv[2],"r");

    //проверка на корректность открытия
    if (in==NULL)
    {
        printf("%s","Ошибка открытия файла");
    }

    // simbols - количество символов
    // strings -  количество строк
    // words - количество слов
    // simbol - какой сейчас символ
    // lastsimbol - последний считаный символ
    int simbols, strings, words=0;
    int simbol,lastsimbol=EOF; 

    // если файл не пустой, то выполняем действия:
    while ((simbol=getc(in)) != EOF)
    {
        //считаем слова
        if ((simbol==' ')||(simbol=='\n'))
        {
            ++words;
            if ((lastsimbol=='\n')&&(simbol=='\n')||(lastsimbol==' ')&&(simbol==' '))
            {
                --words;
            }
        } 
        
        // считанный символ передаём в последний
        lastsimbol=simbol;
        ++simbols;
        
        // если есть символ переноса строки - добавляем строчку
        if (simbol=='\n')
        {
            ++strings;
        }

    }
    
    // если в файле что-то было, то нужно добавить 1 к строчкам 
    // (последнюю строчку чаще всего не отделяют новой строчкой)
    if ((lastsimbol !=EOF) && (lastsimbol !='\n'))
    {
        ++ strings;
    }

    fclose(in);

   

    // если файл пуст - сообщаем об этом
    if (lastsimbol == EOF)
    {
        printf("%s\n", "Файл пустой");
    }
    else 
    {
         //-l, --lines -c, --bytes -w, --words
        if ((strcmp(argv[1],"--bytes") == 0)||(strcmp(argv[1],"-c") == 0))
        {
            printf("%s\t%d\n", "Количество символов:",simbols);
        }
        if ((strcmp(argv[1],"-w")==0)||(strcmp(argv[1],"--words")==0))
        {
            printf("%s\t%d\n", "Количество слов:",words);
        }
        if ((strcmp(argv[1],"-l")==0)||(strcmp(argv[1],"--lines")==0))
        {
            printf( "%s\t%d\n", "Количество строк:",strings);
        }
    }
    printf("DONE");
    return 0;
}