#include "drawutils.h"

void draw_name(char *name) {
  mvprintw(1, 2, "            ");
  mvprintw(1, 2, "%s", name);
}

void draw_money(int money) {
  mvprintw(1, 24, "            ");
  mvprintw(1, 24, "%d", money);
}

void draw_life(int life) {
  mvprintw(1, 45, "            ");
  mvprintw(1, 45, "%d", life);
}

void draw_time(int time) {
  mvprintw(1, 66, "            ");
  mvprintw(1, 66, "%d", time);
}

void draw_waiting_cust_elem(int i, char *elem) {
  mvprintw(4 + i, 2, "            ");
  mvprintw(4 + i, 2, "%s", elem);
}

void draw_order_elem(int i, char *elem) {
  mvprintw(14 + i, 2, "            ");
  mvprintw(14 + i, 2, "%s", elem);
}

void draw_food_stack_elem(int i, char *elem) {
  mvprintw(4 + i, 66, "            ");
  mvprintw(4 + i, 66, "%s", elem);
}

void draw_hand_elem(int i, char *elem) {
  mvprintw(14 + i, 66, "            ");
  mvprintw(14 + i, 66, "%s", elem);
}

void draw_map_tile(int y, int x, char tile) {
  mvaddch(2 + y, 14 + x * 3, tile);
}

void draw_static_elems(int h, int w) {  
  //borders
  mvhline(3 + h, 16, 0, w * 3);
  mvvline(3, 16 + w * 3, 0, h);
  mvaddch(3 + h, 16 + w * 3, ACS_LRCORNER);
  
  //vertical lines
  mvvline(0, 0, 0, 25);
  mvvline(0, 15, 0, 23);
  mvvline(0, 37, 0, 3);
  mvvline(0, 58, 0, 3);
  mvvline(2, 64, 0, 21);
  mvvline(0, 79, 0, 25);
  
  //horizontal lines
  mvhline(0, 0, 0, 10);
  mvhline(0, 0, 0, 80);
  mvhline(2, 0, 0, 80);
  mvhline(12, 0, 0, 16);
  mvhline(12, 64, 0, 16);
  mvhline(22, 0, 0, 80);
  mvhline(24, 0, 0, 80);
  
  //corners
  mvaddch(0, 0, ACS_ULCORNER);
  mvaddch(0, 15, ACS_TTEE);
  mvaddch(0, 37, ACS_TTEE);
  mvaddch(0, 58, ACS_TTEE);
  mvaddch(0, 79, ACS_URCORNER);
  
  mvaddch(2, 0, ACS_LTEE);
  mvaddch(2, 15, ACS_PLUS);
  mvaddch(2, 37, ACS_BTEE);
  mvaddch(2, 58, ACS_BTEE);
  mvaddch(2, 64, ACS_TTEE);
  mvaddch(2, 79, ACS_RTEE);
  
  mvaddch(12, 0, ACS_LTEE);
  mvaddch(12, 15, ACS_RTEE);
  mvaddch(12, 64, ACS_LTEE);
  mvaddch(12, 79, ACS_RTEE);
  
  mvaddch(22, 0, ACS_LTEE);
  mvaddch(22, 15, ACS_BTEE);
  mvaddch(22, 64, ACS_BTEE);
  mvaddch(22, 79, ACS_RTEE);
  
  mvaddch(24, 0, ACS_LLCORNER);
  mvaddch(24, 79, ACS_LRCORNER);
  
  //text
  mvprintw(1, 17, "Money:");
  mvprintw(1, 39, "Life:");
  mvprintw(1, 60, "Time:");
  
  mvprintw(3, 2, "Waiting Cust");
  mvprintw(3, 66, "Food Stack");
  
  mvprintw(13, 2, "Order");
  mvprintw(13, 66, "Hand");
  
  mvprintw(23, 2, "Command:");
}

void clear_command() {
  mvprintw(23, 11, "                                                                   ");
  move(23, 11);
}

