#ifndef ORDER_H
#define ORDER_H

#include "item.h"
#include "customer.h"

typedef struct Order {
    Item food;
    int table;
    Customer customer;
}
Order;

#endif