#ifndef GAME_H
#define GAME_H

//#include "queue.h"
//#include "stackt.h"
#include "matriks.h"
#include "point.h"
//#include "bintree.h"
#include "drawutils.h"

#include <string.h>

#define MAX_STR_LEN 12
#define MAX_MAPS 4
#define MAX_MAP_WIDTH 16
#define MAX_MAP_HEIGHT 19
#define PLAYER_SYMBOL 'P'

typedef struct {
  char name[MAX_STR_LEN + 1];
  int money;
  int life;
  int time;
  POINT player_pos;
  int current_map;
  //Queue waiting_cust;
  //Array order;
  //Stack food_stack;
  //Stack hand;
  MATRIKS map_tiles[MAX_MAPS];
  //Graph map_conns;
  //BinTree menu_tree;
} 
Game;

void game_init(Game *game, const char *name);

void game_load_from_file(Game *game, FILE *file);
void game_init_draw(Game *game);
void game_save_to_file(Game *game, FILE *file);
boolean game_move_player(Game *game, int delta_x, int delta_y);
void game_advance_time(Game *game);

#endif


