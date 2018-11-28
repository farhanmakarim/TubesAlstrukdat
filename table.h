#ifndef TABLE_H
#define TABLE_H

#include "point.h"
#include "maplocation.h"

#define MAX_CHAIRS 4

typedef struct Table {
    int chair_count;
    MapLocation map_location;
    MapLocation chairs[MAX_CHAIRS];
    int order;
}
Table;

#endif