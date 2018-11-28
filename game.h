#ifndef GAME_H
#define GAME_H

#include "mesinkata.h"
#include "queue.h"
#include "array.h"
#include "stackt.h"
#include "matriks.h"
#include "point.h"
#include "graph.h"
#include "bintree.h"
#include "drawutils.h"
#include "customer.h"
#include "order.h"
#include "item.h"
#include "itemlocation.h"
#include "table.h"

#include <string.h>
#include <time.h>
#include <stdlib.h> // For random(), RAND_MAX

#define MAX_STR_LEN 12
#define MAX_MAPS 4
#define MAX_ITEMS 32
#define MAX_FOODS 32
#define MAX_TABLES 9
#define MAX_MAP_WIDTH 16
#define MAX_MAP_HEIGHT 19
#define PLAYER_SYMBOL 'P'

char CC;
boolean EOP;
boolean EndKata;
Kata CKata;

typedef struct {
  char name[MAX_STR_LEN+1];
  int money;
  int life;
  int time;
  POINT player_pos;
  int current_map;
  Queue waiting_cust;
  Array order;
  Stack food_stack;
  Stack hand;
  MATRIKS map_tiles[MAX_MAPS];
  Graph map_graph;
  BinTree recipe_tree;

  MapLocation tray_location;
  int item_count;
  ItemLocation item_locations[MAX_ITEMS];
  int food_count;
  Item foods[MAX_FOODS];
  int food_prices[MAX_FOODS];
  Table tables[MAX_TABLES];
  int time_to_next_customer;
} 
Game;

void game_new(Game *game, const char *name);
void game_load(Game *game, const char *filename);
void game_load_from_file(Game *game, const char *filename, const char *name);
void game_init_draw(Game *game);
boolean game_advance_time(Game *game);
void game_save_to_file(Game *game, const char *filename);
boolean game_move_player(Game *game, int delta_x, int delta_y);
boolean game_take_order(Game *game);
boolean game_put_food(Game *game);
boolean game_take_item(Game *game);
boolean game_clear_hand(Game *game);
boolean game_clear_tray(Game *game);
boolean game_place_customer(Game *game);
boolean game_give_food(Game *game);
void game_show_recipe_tree(Game *game);

#endif


