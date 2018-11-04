#include "game.h"

void game_init(Game *game, const char *name) {
  int i;
  indeks y, x;
  
  strcpy(game->name, name);
  game->money = 500;
  game->life = 3;
  game->time = 0;
  game->player_pos = MakePOINT(1, 1);
  game->current_map = 0;
  //CreateEmpty(&game->waiting_cust, 8);
  //CreateEmpty(&game->food_stack);
  //CreateEmpty(&game->hand);
  for (i = 0; i < MAX_MAPS; ++i) {
    MakeMATRIKS(8, 8, &game->map_tiles[i]);
    for (y = GetFirstIdxBrs(game->map_tiles[i]); y <= GetLastIdxBrs(game->map_tiles[i]); ++y) {
      for (x = GetFirstIdxKol(game->map_tiles[i]); x <= GetLastIdxKol(game->map_tiles[i]); ++x) {
        Elmt(game->map_tiles[i], y, x) = ' ';
      }
    }
    Elmt(game->map_tiles[i], 3, 4) = 'X';
    Elmt(game->map_tiles[i], 4, 3) = 'X';
    Elmt(game->map_tiles[i], 4, 4) = '1';
    Elmt(game->map_tiles[i], 5, 4) = 'X';
    Elmt(game->map_tiles[i], 4, 5) = 'X';
  }
}

void game_init_draw(Game *game) {
  indeks y, x;
  
  draw_static_elems(NBrsEff(game->map_tiles[game->current_map]), NKolEff(game->map_tiles[game->current_map]));
  draw_name(game->name);
  draw_money(game->money);
  draw_life(game->life);
  draw_time(game->time);
  for (y = GetFirstIdxBrs(game->map_tiles[game->current_map]); y <= GetLastIdxBrs(game->map_tiles[game->current_map]); ++y) {
    for (x = GetFirstIdxKol(game->map_tiles[game->current_map]); x <= GetLastIdxKol(game->map_tiles[game->current_map]); ++x) {
      draw_map_tile(y, x, Elmt(game->map_tiles[game->current_map], y, x));
    }
  }
  draw_map_tile(Ordinat(game->player_pos), Absis(game->player_pos), PLAYER_SYMBOL);
}

boolean game_move_player(Game *game, int delta_x, int delta_y) {
  POINT next_point;
  
  next_point = PlusDelta(game->player_pos, delta_x, delta_y);
  if (IsIdxEff(game->map_tiles[game->current_map], Ordinat(next_point), Absis(next_point))
      && Elmt(game->map_tiles[game->current_map], Ordinat(next_point), Absis(next_point)) == ' ') {
    draw_map_tile(Ordinat(game->player_pos), Absis(game->player_pos), ' ');
    game->player_pos = next_point;
    draw_map_tile(Ordinat(game->player_pos), Absis(game->player_pos), PLAYER_SYMBOL);
    return true;
  }
  else {
    return false;
  }
}

void game_advance_time(Game *game) {
  ++game->time;
  draw_time(game->time);
}
