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
typedef struct data {
    char *remote_Addr;
    char *local_Time;
    char *time_Zone;
    char *request;
    char *status;
    char *bytes_Send;
} data;

data getData(char *request) {//эта функция разделяет нашу строку на части
    data res;

    res.remote_Addr = strtok(request, "-");

    strtok(NULL, "[");
    res.local_Time = strtok(NULL, " ");

    res.time_Zone = strtok(NULL, "]");

    strtok(NULL, "\"");
    res.request = strtok(NULL, "\"");

    res.status = strtok(NULL, " ");
    res.bytes_Send = strtok(NULL, "\n");

    return res;
}

const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun","Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

int getMonthNumber(char *mon) {
    int res;
    for (res = 0; (res < 12) && (strcmp(mon, months[res])); res++);
    return res;
}

int getTime(char *reqTime) {
    int res;
    struct tm localTime = {};

    localTime.tm_mday = atoi(strtok(reqTime, "/"));//считываем пока не дойдём до "/"
    localTime.tm_mon = getMonthNumber(strtok(NULL, "/"));//мы продолжаем поиск в оригинальной строке->ставим NULL
    localTime.tm_year = atoi(strtok(NULL, ":")) - 1900; // years since 1900
    localTime.tm_hour = atoi(strtok(NULL, ":"));
    localTime.tm_min = atoi(strtok(NULL, ":"));
    localTime.tm_sec = atoi(strtok(NULL, ":"));

    res = mktime(&localTime);//конвертирует время в календарное время(1 число на выход)

    return res;
}

int main (int argc, char * argv[])
{
    FILE *in;
    //char remote_addr[1000], request[1000], command[10], local_time[100], bytes_send[10];
    char line[2048];
    data request_line;
    int status, number_of_500requests, number_of_requests;
    
    time_t start = time(NULL);
    in = fopen("access_log_Jul95", "r");
    
    number_of_500requests = 0;
    number_of_requests = 0;
    while(!feof(in))
    {
        fgets(line, 4096, in);
        //fscanf(in, "%s - - [%s -0400] \"%s %s HTTP/1.0\" %d %s\n", remote_addr, local_time, command, request, &status, bytes_send);
        request_line = getData(line);
        number_of_requests++;
        printf("%d\n", number_of_requests);
        status = atoi(request_line.status);
        if (status / 100 == 5)
        {
            //printf("%s\n", request_line.request);
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
    char strtimestart[80], strtimeend[80];
    int time_limit, rez;
    int *a;
    int i = 0, j, size, k, max = 0;
    FILE *out;
    out = fopen("/Users/macbook/Desktop/out.txt", "w");

    in = fopen("access_log_Jul95", "r");

    printf("\ntime_limit = ");
    scanf("%d", &time_limit);

    //fscanf(in, "%s - - [%s -0400] \"%s %s HTTP/1.0\" %d %s\n", remote_addr, local_time, command, request, &status, bytes_send);
    a = malloc(sizeof(int) * number_of_requests);
    while (i < number_of_requests)
    {
        fgets(line, 2048, in);
        //fscanf(in, "%s - - [%s -0400] \"%s %s HTTP/1.0\" %d %s\n", remote_addr, local_time, command, request, &status, bytes_send);
        request_line = getData(line);
        
        a[i] = getTime(request_line.local_Time);
        fprintf(out, "i = %d, day = %d month = %d year = %d hour = %d min = %d sec = %d = %d = %s\n", i, u1.tm_mday, u1.tm_mon + 1, u1.tm_year + 1900, u1.tm_hour, u1.tm_min, u1.tm_sec, a[i], strtime1);
        i++;
        /*fscanf(in, "%s - - [%s -0400] \"%s %s HTTP/1.0\" %d %s\n", remote_addr, local_time, command, request, &status, bytes_send);
        printf("local time = %s ", local_time);
        a[i] = getTime(local_time);
        printf("i = %d, a[i] = %d\n", i,  a[i]);
        i++;*/
        /*fscanf(in, "%s - - [%s -0400] \"%s %s HTTP/1.0\" %d %s\n", remote_addr, local_time2, command, request, &status, bytes_send);
        strptime(local_time2, "%d/%b/%Y:%H:%M:%S", &u2);
        time2 = mktime(&u2);
        strftime(strtime1, 80, "%d/%b/%Y %H:%M:%S", localtime(&time1));
        strftime(strtime2, 80, "%d/%b/%Y %H:%M:%S", localtime(&time2));
        a[i] = difftime(time2, time1);
        i++;
        strcpy(local_time, local_time2);*/
    }

    for (i = 0; i < number_of_requests - 1; i++)
    {
        j = i + 1;
        while ((j < number_of_requests) && (time_limit >= a[j] - a[i]))
        {
            j++;
        }
        if (time_limit < a[j] - a[i])
        {
            if (j - i > max)
            {
                //printf("amount = %d, a[%d] - a[%d] = %d - %d = %d\n", j - i, j - 1, i, a[j - 1], a[i], a[j - 1] - a[i]);
                max = j - i;
                time1 = a[i];
                time2 = a[j - 1];
                strftime(strtimestart, 80, "%d/%b/%Y %H:%M:%S", localtime(&time1));
                strftime(strtimeend, 80, "%d/%b/%Y %H:%M:%S", localtime(&time2));
            }
        }
        else if ((j >= number_of_requests) && (time_limit >= difftime(a[j], a[i])))
        {
            if (j - i > max)
            {
                //printf("amount = %d, a[%d] - a[%d] = %d - %d = %d\n", j - i, j - 1, i, a[j - 1], a[i], a[j - 1] - a[i]);
                max = j - i;
                time1 = a[i];
                time2 = a[j - 1];
                strftime(strtimestart, 80, "%d/%b/%Y %H:%M:%S", localtime(&time1));
                strftime(strtimeend, 80, "%d/%b/%Y %H:%M:%S", localtime(&time2));
            }
            //printf("\"BREAK\"\n");
            break;
        }
    }
    /*for (i = 0; i < number_of_requests; i++)
    {
        k = 2; //потому что в  a[i] содержтся разница между двумя строчками
        rez = a[i];
        j = i + 1;
        if ((rez == time_limit) && (k > max))
        {
            max = k;
        }
        while ((time_limit >= rez) && ( j < size))
        {
            rez += a[j];
            j++;
            k++;
            if ((rez == time_limit) && (k > max))
            {
                max = k;
            }
        }
    }*/
    fclose(in);
    
    printf("\nmax number of request in %d seconds is %d\n", time_limit, max);
    printf("started at: %s\nended at: %s\n", strtimestart, strtimeend);
    printf("\nDONE in %ld\n", time(NULL) - start);
    time1 = 805631578;
    strftime(strtime1, 80, "%d/%b/%Y %H:%M:%S", localtime(&time1));
    printf("%s\n", strtime1);
    free(a);
    return 0;
}