#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <iso646.h>

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

typedef struct uint1024_t
{
    uint32_t *number;
    int32_t size;
} uint1024_t;

uint1024_t from_uint(unsigned int x)
{
    uint1024_t rez;
    if (x < 1000 * 1000 * 1000)
    {
        rez.size = 1;
        rez.number = malloc(rez.size * sizeof(uint32_t));
        rez.number[0] = x;
    }
    else
    {
        rez.size = 2;
        rez.number = malloc(rez.size * sizeof(uint32_t));
        rez.number[0] = x % (1000 * 1000 * 1000);
        rez.number[1] = x / (1000 * 1000 * 1000);
    }
    return rez;
}

uint1024_t add_op(uint1024_t x, uint1024_t y)
{
    int more = 0;
    int i;
    int rezSize;

    if (x.size > y.size)
    {
        rezSize = x.size;
    }
    else
    {
        rezSize = y.size;
    }
    uint1024_t rez;
    rez.size = rezSize;
    rez.number = calloc(rez.size, sizeof(uint32_t));

    for (i = 0; i < rezSize or more; i++)
    {
        if (i == rezSize)
        {
            rez.number = realloc(rez.number, (rezSize + 1) * sizeof(int32_t));
            rez.number[rezSize] = 0;
            rez.size++;
        }
        rez.number[i] = more + (i < y.size ? y.number[i] : 0) + (i < x.size ? x.number[i] : 0);
        more = rez.number[i] >= (1000 * 1000 * 1000);
        if (more)
        {
            rez.number[i] -= (1000 * 1000 * 1000);
        }
    }
    return rez;
}

uint1024_t subtr_op(uint1024_t x, uint1024_t y)
{
    int more = 0;
    int i;
    int rezSize;
    if (x.size > y.size)
    {
        rezSize = x.size;
    }
    else
    {
        rezSize = y.size;
    }
    uint1024_t rez;
    rez.size = rezSize;
    rez.number = calloc(rez.size, sizeof(uint32_t));
    for (i = 0; i < rezSize or more; ++i)
    {
        if (x.number[i] < (i < y.size ? y.number[i] : 0) + more)
        {
            rez.number[i] = (1000 * 1000 * 1000) + ((i < x.size ? x.number[i] : 0) - (i < y.size ? y.number[i] : 0) - more);
            more = 1;
        }
        else
        {
            rez.number[i] = (i < x.size ? x.number[i] : 0) - (i < y.size ? y.number[i] : 0) - more;
            more = 0;
        }
    }
    while (rez.number[rez.size - 1] == 0 and rez.size > 1)
    {
        rez.size--;
    }
    rez.number = realloc(rez.number, rez.size * sizeof(uint32_t));
    return rez;
}

uint1024_t mult_op(uint1024_t x, uint1024_t y)
{
    int rezSize = x.size + y.size;
    int i, j, more;
    uint1024_t rez;
    rez.size = rezSize;
    rez.number = calloc(rez.size, sizeof(uint32_t));

    for (i = 0; i < x.size; ++i)
        for (j = 0, more = 0; j < y.size or more; ++j)
        {
            long long cur = rez.number[i + j] + x.number[i] * (long long)(j < y.size ? y.number[j] : 0) + more;
            rez.number[i + j] = (uint32_t)(cur % (1000 * 1000 * 1000));
            more = (int)(cur / (1000 * 1000 * 1000));
        }
    while (rez.number[rez.size - 1] == 0 and rez.size > 1)
    {
        rez.size--;
    }
    rez.number = realloc(rez.number, rez.size * sizeof(uint32_t));
    return rez;
}

void scanf_value(uint1024_t *x)
{
    char s[310];
    scanf("%309s", s);
    int sSize = strlen(s);
    int xSize;
    uint1024_t rez;
    if (sSize % 9 == 0)
    {
        xSize = sSize / 9;
    }
    else
    {
        xSize = (sSize / 9) + 1;
    }
    rez.size = xSize;
    rez.number = malloc(xSize * sizeof(uint32_t));
    for (int i = sSize, j = -1; i > 0; i -= 9)
    {
        j++;
        s[i] = '\0';
        if (i >= 9)
        {
            rez.number[j] = atoi(s + i - 9);
        }
        else
        {
            rez.number[j] = atoi(s);
        }
    }
    *x = rez;
}

void printf_value(uint1024_t x)
{
    if (x.number[x.size - 1] == 0 and x.size == 1)
    {
        printf("0\n");
    }
    else
    {
        printf("%d", x.number[x.size - 1]);
    }
    for (int i = x.size - 2; i >= 0; --i)
    {
        printf("%09d", x.number[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    uint1024_t x1, x2, x3, x4, x5, x6;
    int i;
    scanf_value(&x1);
    scanf_value(&x2);
    scanf_value(&x3);
    scanf_value(&x4);
    scanf_value(&x5);
    scanf_value(&x6);
    scanf("%d", &i);

    printf("Test1\n");
    printf_value(add_op(x1, x2));
    printf("\n");
    printf("Test2\n");
    printf_value(subtr_op(x2, x3));
    printf("\n");
    printf("Test3\n");
    printf_value(mult_op(x4, x5));
    printf("\n");
    printf("Test4\n");
    printf_value(add_op(x6, from_uint(i)));
    printf("\n");
}

/*void reverse(char s[])
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
        itoa(x2 + y2, &sum);
        printf("%s = %d\n", sum, x2 + y2);
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
    if (x->size > 310)
    {
        printf("Unexpected behaviour");
        exit(-1);
    }
}

void printf_value(uint1024_t x)
{
    printf("%s\n", x.number);
}

int main(int argc, char *argv[])
{
    uint1024_t x1,x2,x3,x4,x5,x6;
    unsigned int x;
    scanf_value(&x1);
    scanf_value(&x2);
    scanf_value(&x3);
    scanf_value(&x4);
    scanf_value(&x5);
    scanf_value(&x6);
    x = 1;

    printf("\n");
    printf_value(x1);
    printf_value(x2);
    printf_value(x3);
    printf_value(x4);
    printf_value(x5);
    printf_value(x6);

    printf("test1\n");
    printf_value(add_op(x1,x2));
    printf("\n");

    printf("test2\n");
    //printf_value(subtr_op(number1, number2));
    printf("\n");

    printf("test3\n");
    printf_value(mult_op(x4, x5));
    printf("\n");

    printf("test4\n");
    printf_value(mult_op(x6, from_uint(x)));

    printf("\nDONE");
    return 0;
}*/
