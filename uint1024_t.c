#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/*
1. uint1024_t from_uint(unsigned int x) - генерация из числа
2. uint1024_t add_op(uint1024_t x, uint1024_t y) - сложение
3. uint1024_t subtr_op(uint1024_t x, uint1024_t y) - вычетание
4. uint1024_t mult_op(uint1024_t x, uint1024_t y) - умножение
5. void printf_value(uint1024_t x) - вывод в стандартный поток
вывода
6. void scanf_value(uint1024_t* x) - чтение из стандартного потока
ввода
*/
 
void reverse(char s[])
{
    int i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char s[])
{
    int i = 0;
    do 
    {       
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    s[i] = '\0';
    reverse(s);
}

typedef struct uint1024_t
{
    char number[310];
    unsigned int size;
} uint1024_t;

uint1024_t from_uint(unsigned int x)
{
    uint1024_t number;

    number.size = sizeof(x) / sizeof(unsigned int);
    char* c;
    c = (char *)malloc((sizeof(x)/sizeof(unsigned int)) * sizeof(char)); 
    int v = 0; 
    while (x > 9)
    {
        c[v++] = (x % 10) + '0';
        x = x / 10;
    }
    c[v++] = x + '0';
    c[v] = '\0';
    char t;
    for (int i = 0; i < v / 2; i++)
    {
        t = c[i];
        c[i] = c[v - 1 - i];
        c[v - 1 - i] = t;
    }
    strcpy(number.number, c);
    number.size = v;
    return number;
}

uint1024_t add_op(uint1024_t x, uint1024_t y)
{
    uint1024_t number;
    char sum[310];
    int i;

    for (i=309; i>-1; i--)
    {
        int x2 = atoi(&x.number[i]);
        int y2 =  atoi(&y.number[i]);
        itoa(x2 + y2, &sum[i]);
    }
    strcpy(number.number, sum);
    return number;
}

uint1024_t subtr_op(uint1024_t x, uint1024_t y)
{
    uint1024_t number;
    char sum[310];
    int i, more;
    for (i = 309; i > -1; i++)
    {
        int x2 = atoi(&x.number[i]);
        int y2 = atoi(&y.number[i]);
        if (x2 < y2 + more)
        {
            itoa(10 + x2 - y2 - more, &sum[i]);
            more = 1;
        }
        else
        {
            itoa(x2 - y2 - more, &sum[i]);
            more = 0;
        }
        if (atoi(&sum[i]) < 0)
        {
            printf("Unexpected behaviour");
            exit(-1);
        }
    }
    strcpy(number.number, sum);
    return number;
}

void printf_value(uint1024_t x);

uint1024_t mult_op(uint1024_t x, uint1024_t y)
{
    uint1024_t rez, sum;
    long long summery;
    char mult[620];
    int i, j, more;
    
    for (i = 309; i > -1; i--)
    {
        for (j = 309; j > -1; j--)
        {
            int x2 = atoi(&x.number[i]);
            int y2 = atoi(&y.number[j]);
            summery = atoi(&mult[i+j]) + x2 * y2;
        }
        
    }
    rez = from_uint(summery);
    return rez;
}

void scanf_value(uint1024_t *x)
{
    scanf("%s",x->number);
    x->size = sizeof(x->number) / (sizeof(char));
}

void printf_value(uint1024_t x)
{
    printf("%s\n", x.number);
}

int main(int argc, char *argv[])
{
    uint1024_t number1, number2;
    unsigned int x;
    printf("Scanf\n");
    scanf_value(&number1);
    scanf_value(&number2);
    scanf("%u", &x);
    printf("\n");

    printf("From uint\n");
    printf_value(from_uint(x));
    printf("\n");

    printf("Add\n");
    printf_value(add_op(number1, number2));
    printf("\n");

    printf("Subtr\n");
    printf_value(subtr_op(number1, number2));
    printf("\n");

    printf("Mult\n");
    printf_value(mult_op(number1, number2));
    printf("\nDONE");
    return 0;
}
