#include <stdlib.h>
#include "../header/structure.h"


struct Point *new_Point(int x, int y, int color)
{
    typedef struct Point Point;
    Point *point = calloc(1, sizeof(Point));
    point->x = x;
    point->y = y;
    point->color = color;
    return point ;
}

boolean equal_point(void *val1, void *val2, ...)
{
    typedef struct Point Point;
    Point *p1 = val1;
    Point *p2 = val2;
    if (p1->x == p2->x && p1->y == p2->y)
        return True;

    return False;
}
