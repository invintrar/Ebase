/* clock_times.c
Licensed under GNU General Public License v2 or later.
*/
#define _XOPEN_SOURCE 700
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define SECS_IN_DAY (24 * 60 * 60)

struct timespec ts;

static void changeClock(clockid_t clock, char *name, bool showRes)
{
    
    if (clock_gettime(clock, &ts) == -1) 
    {
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }
    printf("%-15s: %10ld.%03ld (", name,
    (long) ts.tv_sec, ts.tv_nsec / 1000000);
    long days = ts.tv_sec / SECS_IN_DAY;
    if (days > 0)
        printf("%ld days + ", days);
    printf("%2ldh %2ldm %2lds", (ts.tv_sec % SECS_IN_DAY) / 3600,
    (ts.tv_sec % 3600) / 60, ts.tv_sec % 60);
    printf(")\n");
    if (clock_getres(clock, &ts) == -1) 
    {
        perror("clock_getres");
        exit(EXIT_FAILURE);
    }
    if (showRes)
        printf("     resolution: %10ld.%09ld\n",
        (long) ts.tv_sec, ts.tv_nsec);
}

static void setClock(clockid_t clock, time_t tsec, long tnsec){
    struct timespec tp = {tp.tv_sec = 31415930, tp.tv_nsec = 0};
    if(clock_settime(clock, &tp) == -1 )
    {
        perror("clock_settime");
        exit(EXIT_FAILURE);
    }

}

int main(int argc, char *argv[])
{
    bool showRes = argc > 1;

    displayClock(CLOCK_REALTIME, "CLOCK_REALTIME", showRes);

    //setClock(CLOCK_REALTIME);

    #ifdef CLOCK_TAI
        displayClock(CLOCK_TAI, "CLOCK_TAI", showRes);
    #endif
        displayClock(CLOCK_MONOTONIC, "CLOCK_MONOTONIC", showRes);
    #ifdef CLOCK_BOOTTIME
        displayClock(CLOCK_BOOTTIME, "CLOCK_BOOTTIME", showRes);
    #endif
    exit(EXIT_SUCCESS);
}