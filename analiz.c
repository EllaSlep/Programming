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
    struct tm u;
    char remote_addr[1000], request[1000], local_time[100];
    int status, bytes_send, number_of_500requests, number_of_requests;

    time_t start = time(NULL);
    in = fopen("access_log_Jul95", "r");
    
    number_of_500requests = 0;
    number_of_requests = 0;
    while(!feof(in))
    {
        fscanf(in, "%s - - [%s -0400] \"GET %s HTTP/1.0\" %d %d\n", remote_addr, local_time, request, &status, &bytes_send);
        number_of_requests++;
        if (status / 100 == 5)
        {
            printf("\n%s - - [%s -0400] \"GET %s HTTP/1.0\" %d %d\n", remote_addr, local_time, request, status, bytes_send);
            number_of_500requests++;
        }
    }
    printf("\nnumber of 500 requests: %d\nnumber of all requests: %d\n", number_of_500requests, number_of_requests);
    printf("%ld\tDONE\n\n", time(NULL) - start);
    fclose(in);
    return 0;
}