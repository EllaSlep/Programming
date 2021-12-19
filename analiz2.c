#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

int get_month(char *mon)
{
    int rez;
    for (rez = 0; rez < 12 && strcmp(mon, months[rez]); rez++);
    return rez + 1;
}

int get_time(char *reqTime)
{
    int rez;
    struct tm localTime = {};

    localTime.tm_mday = atoi(strtok(reqTime, "/"));
    localTime.tm_mon = get_month(strtok(NULL, "/"));
    localTime.tm_year = atoi(strtok(NULL, ":")) - 1900;
    localTime.tm_hour = atoi(strtok(NULL, ":"));
    localTime.tm_min = atoi(strtok(NULL, ":"));
    localTime.tm_sec = atoi(strtok(NULL, ":"));

    rez = mktime(&localTime);

    return rez;
}

void time_limit_search(long long **time_interval, long long number_of_requests, int time_limit, int *times)
{
    long long max = 0, j = 1;

    for (long long i = 0; i < number_of_requests; i++)
    {
        while (j < number_of_requests && times[j] - times[i] <= time_limit)
        {
            j++;
        }
        if (times[j] - times[i] > time_limit)
        {
            if (j - i > max)
            {
                max = j - i;
                (*time_interval)[0] = times[i];
                (*time_interval)[1] = times[j - 1];
                (*time_interval)[2] = max;
            }
        }
        else
        {
            if (j - i > max)
            {
                max = j - i;
                (*time_interval)[0] = times[i];
                (*time_interval)[1] = times[j - 1];
                (*time_interval)[2] = max;
            }
            break;
        }
    }
}

typedef struct data
{
    char *remote_addr;
    char *local_time;
    char *time_zone;
    char *request;
    char *status;
    char *bytes_send;
} data;

int correct_data(data data)
{
    return !(data.local_time == NULL || data.request == NULL || data.status == NULL ||
             data.time_zone == NULL || data.remote_addr == NULL || data.bytes_send == NULL);
}

int main(int argc, char *argv[])
{
    FILE *in = fopen("/Users/macbook/Desktop/ИТМО/Programming/Programming/access_log_Jul95", "r");
    data request;
    int time_limit = 2;
    long long number_of_requests = 0;
    long long number_500_requests = 0;
    char *line = malloc(2000 * sizeof(char));
    int *times = malloc(2000000 * sizeof(long long));

    printf("\ntime limit %d\n", time_limit);

    while (!feof(in))
    {
        fgets(line, 2000, in);

        request.remote_addr = strtok(line, "-");
        strtok(NULL, "[");
        request.local_time = strtok(NULL, " ");
        request.time_zone = strtok(NULL, "]");
        strtok(NULL, "\"");
        request.request = strtok(NULL, "\"");
        request.status = strtok(NULL, " ");
        request.bytes_send = strtok(NULL, "\n");

        if (correct_data(request))
        {
            times[number_of_requests] = get_time(request.local_time);

            if (request.status[0] == '5')
            {
                printf("%s\n", request.request);
                number_500_requests++;
            }
            number_of_requests++;
        }
    }
    printf("5xx:  %lld\n", number_500_requests);

    long long *tmWindowInterval = malloc(3 * sizeof(long long));
    time_limit_search(&tmWindowInterval, number_of_requests, time_limit, times);

    printf("\nmax = %lld\nstarted at: %lld\nended at:%lld\n\n", tmWindowInterval[2], tmWindowInterval[0], tmWindowInterval[1]);

    return 0;
}