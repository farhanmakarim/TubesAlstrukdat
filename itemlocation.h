#ifndef ITEMLOCATION_H
#define ITEMLOCATION_H

#include "item.h"
#include "maplocation.h"

typedef struct ItemLocation {
    Item item;
    MapLocation map_location;
}
ItemLocation;

#endif