#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct uint256_t
{
    uint64_t n1;
    uint64_t n2;
    uint64_t n3;
    uint64_t n4;
} uint256_t;

typedef union uint1024_t
{
    char number[308];
    struct
    {
        uint256_t n1;
        uint256_t n2;
        uint256_t n3;
        uint256_t n4;
    };
} uint1024_t;

uint1024_t from_uint(unsigned int x)
{
    uint1024_t number;
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
    return number;
}

uint1024_t add_op(uint1024_t x, uint1024_t y)
{
    uint1024_t number;
    char sum[307];
    int i;

    for (i=307; i>-1; i--)
    {
        int x2 = x.number[i] + 0;
        int y2 =  y.number[i] + 0;
        printf ("x = %d\ty = %d\t", x2,y2);
        sum[i] = (x2 + y2);
        printf ("sum[%d] = %c\n", i, sum[i]);
    }
    printf ("sum = %s", sum);
    for (i = 307; i > -1; i--)
    {
        int x1 = sum[i] + 0;
        if (x1 / 10 > 0)
        {
            int more = x1 / 10;
            int y1 = sum[i-1] + 0;
            y1 += more;
            sum[i] = y1 +'0';
        }
    }
    strcpy(number.number, sum);
    return number;
    /*uint1024_t rez;
    char sum[308];
    int x2,y2,ost,more,i;
    i=307;
    while (i > 0)
    {
        x2 = x.number[i-1] + 0;
        y2 = y.number[i-1] + 0;
        ost = ost + (x2 + y2) % 10;
        more = (x2 + y2) / 10;
        sum[i] = ost+'0';
        printf("\n (%c + %c) %d + %d = %d\t%d   %d", x.number[i-1], y.number[i-1], x2, y2, x2+y2,more, ost);
        printf (" %d %s\n",i ,sum);
        i--;
        if (i == 0)
        {
            continue;
        }
        else
        {
            ost = more;
            more = 0;
        }
    }
    if (i < 0)
    {
        sum[i] = more + '0';
    }
    strcpy(rez.number, sum);
    return rez;*/
}

/*uint1024_t subtr_op(uint1024_t x, uint1024_t y)
{
    
}

uint1024_t mult_op(uint1024_t x, uint1024_t y)
{
    
}*/

void scanf_value(uint1024_t *x)
{
    scanf("%s",x->number);
}

void printf_value(uint1024_t x)
{
    printf("%s\n", x.number);
}

int main(int argc, char *argv[])
{
    uint1024_t x,y;
    x = from_uint(1000);
    y = from_uint(1000);
    printf_value(add_op(x,y));
    printf("\nDONE");
    return 0;
}