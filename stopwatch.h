#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <stdbool.h>
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    double elapsed_milliseconds;
    bool is_running;
    LARGE_INTEGER freq, start;
} Stopwatch;

Stopwatch sw_create(void);
Stopwatch sw_create_and_start(void);
void sw_init(Stopwatch *sw);
void sw_start(Stopwatch *sw);
void sw_stop(Stopwatch *sw);
void sw_reset(Stopwatch *sw);
void sw_restart(Stopwatch *sw);
double sw_get_elapsed_milliseconds(Stopwatch *sw);

#ifdef __cplusplus
}
#endif
#endif // STOPWATCH_H


#ifdef STOPWATCH_IMPLEMENTATION

Stopwatch sw_create(void)
{
    Stopwatch sw;
    sw_init(&sw);
    return sw;
}

Stopwatch sw_create_and_start(void)
{
    Stopwatch sw;
    sw_init(&sw);
    sw_start(&sw);
    return sw;
}

void sw_init(Stopwatch *sw)
{
    QueryPerformanceFrequency(&sw->freq);
    sw_reset(sw);
}

void sw_start(Stopwatch *sw)
{
    if (!sw->is_running) {
        sw->is_running = true;
        QueryPerformanceCounter(&sw->start);
    }
}

void sw_stop(Stopwatch *sw)
{
    if (sw->is_running) {
        sw->elapsed_milliseconds = sw_get_elapsed_milliseconds(sw);
        sw->is_running = false;
    }
}

void sw_reset(Stopwatch *sw)
{
    sw->elapsed_milliseconds = 0.0;
    sw->is_running = false;
}

void sw_restart(Stopwatch *sw)
{
    sw_reset(sw);
    sw_start(sw);
}

double sw_get_elapsed_milliseconds(Stopwatch *sw)
{
    double result = sw->elapsed_milliseconds;
    if (sw->is_running) {
        LARGE_INTEGER end;
        QueryPerformanceCounter(&end);

        LARGE_INTEGER elapsed_microseconds;
        elapsed_microseconds.QuadPart = end.QuadPart - sw->start.QuadPart;
        elapsed_microseconds.QuadPart *= 1000000;
        elapsed_microseconds.QuadPart /= sw->freq.QuadPart;

        result += elapsed_microseconds.QuadPart / 1000.0;
    }
    return result;
}

#endif // STOPWATCH_IMPLEMENTATION
