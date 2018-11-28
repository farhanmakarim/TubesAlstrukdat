#ifndef DRAWUTILS_H
#define DRAWUTILS_H

#include <ncurses.h>
#include "bintree.h"

void draw_name(const char *name);
void draw_money(int money);
void draw_life(int life);
void draw_time(int time);
void draw_waiting_cust_elem(int i, const char *elem);
void draw_order_elem(int i, const char *elem);
void draw_food_stack_elem(int i, const char *elem);
void draw_hand_elem(int i, const char *elem);
void draw_map_tile(int x, int y, char tile);
void clear_command();
void draw_game_ui(int h, int w);
void draw_main_menu();
void draw_main_menu_cursor(int i);
void draw_credits(int money, int time);
void draw_recipe_tree(BinTree recipe_tree);

#endif
