#ifndef _STRUCTURE_
#define _STRUCTURE_

typedef enum boolean
{
    True = 0,
    False = 1
} boolean;

struct etiquette
{
    void *value;
    int index;
};

struct element
{
    void *value;
    struct element *next;
};

struct Point
{
    int x;
    int y;
    int color;
};

struct Point *new_Point(int x, int y, int color);
boolean equal_point(void *val1, void *val2, ...);

#endif