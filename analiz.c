#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    printf("%ld\tDONE\n\n", time(NULL) - start);
    fclose(in);
    
/*
    struct tm u1;
    struct tm u2;
    int time_limit;

    in = fopen("access_log_Jul95", "r");
    //scanf("%d\n", time_limit);
    printf("%s\n", local_time);
    strptime(local_time, "%d/%b/%Y:%H:%M:%S", &u1);
    printf("day %d, monday %d, year %d, hour %d, minets %d, secods %d\n", u1.tm_mday, u1.tm_mon + 1, u1.tm_year + 1900, u1.tm_hour, u1.tm_min, u1.tm_sec);
    strptime("28/Jul/1995:13:32:30", "%s/%b/%Y:%H:%M:%S", &u2);
    printf("day %d, monday %d, year %d, hour %d, minets %d, secods %d\n", u1.tm_mday, u1.tm_mon + 1, u1.tm_year + 1900, u1.tm_hour, u1.tm_min, u1.tm_sec);
    struct tm rez;
    rez.tm_mday = u2.tm_mday - u1.tm_mday;
    rez.tm_mon = u2.tm_mon - u1.tm_mon;
    rez.tm_year = u2.tm_year - u1.tm_year;
    rez.tm_hour = u2.tm_hour - u1.tm_hour;
    rez.tm_min = u2.tm_min - u1.tm_min;
    rez.tm_sec = u2.tm_sec - u1.tm_sec;
    printf("day %d, monday %d, year %d, hour %d, minets %d, secods %d\n", rez.tm_mday, rez.tm_mon + 1, rez.tm_year + 1900, rez.tm_hour, rez.tm_min, rez.tm_sec);
    */
    fclose(in);
    return 0;
}