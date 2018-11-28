#include "drawutils.h"

void draw_name(const char *name) {
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

void draw_waiting_cust_elem(int i, const char *elem) {
  mvprintw(3 + i, 2, "            ");
  mvprintw(3 + i, 2, "%s", elem);
}

void draw_order_elem(int i, const char *elem) {
  mvprintw(13 + i, 2, "            ");
  mvprintw(13 + i, 2, "%s", elem);
}

void draw_food_stack_elem(int i, const char *elem) {
  mvprintw(3 + i, 66, "            ");
  mvprintw(3 + i, 66, "%s", elem);
}

void draw_hand_elem(int i, const char *elem) {
  mvprintw(13 + i, 66, "            ");
  mvprintw(13 + i, 66, "%s", elem);
}

void draw_map_tile(int y, int x, char tile) {
  mvaddch(2 + y, 14 + x * 3, tile);
}

void clear_command() {
  mvprintw(23, 11, "                                                                   ");
  move(23, 11);
}

void draw_game_ui(int h, int w) {  
  clear();
  curs_set(1);
  
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

void draw_main_menu() {
  clear();
}

void draw_main_menu_cursor(int i) {
  
}

void draw_credits(int money, int time) {
  clear();
  mvprintw(0, 0, "\
  GAME OVER\n\
  \n\
  Final results\n\
  Money: %d\n\
  Time: %d\n\
  \n\
  \n\
  CREDITS\n\
  \n\
  Developers\n\
  Farhan Makarim        - 13515003\n\
  Hafiz Maulana         - 13516138\n\
  Dimas Aditia Pratikto - 13516153\n\
  Willsen Sentosa       - 13517036\n\
  Hamzah Chairil Salim  - 13517051\n\
  \n\
  \n\
  Press any key to exit...", money, time);
}

int draw_recipe_tree_node(BinTree recipe_tree, int row, int col) {
  if (recipe_tree != TreeNil) {
    mvprintw(row + 2, col * 2, "%s", Akar(recipe_tree).name);
    ++row;
    row = draw_recipe_tree_node(Left(recipe_tree), row, col + 1);
    row = draw_recipe_tree_node(Right(recipe_tree), row, col + 1);
  }
  return row; 
}

void draw_recipe_tree(BinTree recipe_tree) {
  int row;
  clear();
  mvprintw(0, 0, "RECIPE");
  row = draw_recipe_tree_node(recipe_tree, 0, 0);
  mvprintw(row + 3, 0, "Press any key to return...");
}
