#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/*
$remote_addr - - [$local_time] “$request” $status $bytes_send

$remote_addr - источник запроса
$local_time - время запроса
$request - запрос
$status - статус ответ
$bytes_send - количество переданных в ответе байт
*/

int main (int argc, char * argv[])
{
    FILE *in;
    char remote_addr[1000], request[1000], command[10], local_time[100], bytes_send[10];
    int status, number_of_500requests, number_of_requests;

    time_t start = time(NULL);
    in = fopen("access_log_Jul95", "r");
    
    number_of_500requests = 0;
    number_of_requests = 0;
    while(!feof(in))
    {
        fscanf(in, "%s - - [%s -0400] \"%s %s HTTP/1.0\" %d %s\n", remote_addr, local_time, command, request, &status, bytes_send);
        number_of_requests++;
        if (status / 100 == 5)
        {
            printf("%s - - [%s -0400] \"%s %s HTTP/1.0\" %d %s\n", remote_addr, local_time, command, request, status, bytes_send);
            number_of_500requests++;
        }
    }
    printf("\nNumber of 500 requests: %d\nNumber of all requests: %d\n", number_of_500requests, number_of_requests);
    fclose(in);

    time_t time1, time2;
    struct tm u1;
    struct tm u2;
    char local_time2[100];
    char strtime1[80], strtime2[80];
    int time_limit, rez;
    int *a;
    int i = 0, j, size, k, max = 0;

    in = fopen("access_log_Jul95", "r");
    fscanf(in, "%s - - [%s -0400] \"%s %s HTTP/1.0\" %d %s\n", remote_addr, local_time, command, request, &status, bytes_send);
    a = (int*)malloc(8000000);
    while (!feof(in))
    {
        strptime(local_time, "%d/%b/%Y:%H:%M:%S", &u1);
        time1 = mktime(&u1);
        fscanf(in, "%s - - [%s -0400] \"%s %s HTTP/1.0\" %d %s\n", remote_addr, local_time2, command, request, &status, bytes_send);
        strptime(local_time2, "%d/%b/%Y:%H:%M:%S", &u2);
        time2 = mktime(&u2);
        strftime(strtime1, 80, "%d/%b/%Y %H:%M:%S", localtime(&time1));
        strftime(strtime2, 80, "%d/%b/%Y %H:%M:%S", localtime(&time2));
        a[i] = difftime(time2, time1);
        i++;
        strcpy(local_time, local_time2);
    }
    printf("\n time_limit = ");
    scanf("%d", &time_limit);
    size = i;
    for (i = 0; i < size; i++)
    {
        k = 2; //потому что в  a[i] содержтся разница между двумя строчками
        rez = a[i];
        j = i + 1;
        if ((rez == time_limit) && (k > max))
        {
            max = k;
        }
        while ((time_limit >= rez) && ( j != size))
        {
            rez += a[j];
            j++;
            k++;
            if ((rez == time_limit) && (k > max))
            {
                max = k;
            }
        }
    }
    fclose(in);
    
    printf("\nmax number of request in %d is %d\n", time_limit, max);
    printf("\nDONE in %ld\n", time(NULL) - start);
    free(a);
    return 0;
}