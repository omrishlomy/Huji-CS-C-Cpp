#ifndef EX2_REPO_SORTBUSLINES_H
#define EX2_REPO_SORTBUSLINES_H
// write only between #define EX2_REPO_SORTBUSLINES_H and #endif
// EX2_REPO_SORTBUSLINES_H
#include <string.h>
#define NAME_LEN  21

typedef struct BusLine
{
    char name[NAME_LEN];
    int distance, duration;
} BusLine;

typedef enum SortType
{
    DISTANCE,
    DURATION
} SortType;

void bubble(BusLine *start,BusLine *end);

void bubble_sort (BusLine *start, BusLine *end);


void quick_sort (BusLine *start, BusLine *end, SortType sort_type);

int convert_sortype(BusLine *ptr,SortType sort_type);

void swap(BusLine *low,BusLine *high);

BusLine *partition (BusLine *start, BusLine *end, SortType sort_type);

// write only between #define EX2_REPO_SORTBUSLINES_H and #endif //EX2_REPO_SORTBUSLINES_H
#endif //EX2_REPO_SORTBUSLINES_H
