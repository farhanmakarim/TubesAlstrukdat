#ifndef DRAWUTILS_H
#define DRAWUTILS_H

#include <ncurses.h>

void draw_name(char *name);
void draw_money(int money);
void draw_life(int life);
void draw_waiting_cust_elem(int i, char *elem);
void draw_order_elem(int i, char *elem);
void draw_food_stack_elem(int i, char *elem);
void draw_hand_elem(int i, char *elem);
void draw_map_tile(int x, int y, char tile);
void draw_static_elems(int h, int w);
void clear_command();

#endif
