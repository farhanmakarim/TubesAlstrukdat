#include "game.h"

int main() {
  initscr();
  
  Game game;
  game_init(&game, "<NAME>");
  game_init_draw(&game);
  
  char input[68];
  boolean is_running = true;
  boolean is_valid = true;
  
  while (is_running) {
    clear_command();
    is_valid = true;
    getnstr(input, 67);
    
    if (strcmp(input, "GU") == 0) {
      is_valid = game_move_player(&game, 0, -1);
    }
    else if (strcmp(input, "GD") == 0) {
      is_valid = game_move_player(&game, 0, 1);
    }
    else if (strcmp(input, "GL") == 0) {
      is_valid = game_move_player(&game, -1, 0);
    }
    else if (strcmp(input, "GR") == 0) {
      is_valid = game_move_player(&game, 1, 0);
    }
    else if (strcmp(input, "ORDER") == 0) {
    }
    else if (strcmp(input, "PUT") == 0) {
    }
    else if (strcmp(input, "TAKE") == 0) {
    }
    else if (strcmp(input, "CH") == 0) {
    }
    else if (strcmp(input, "CT") == 0) {
    }
    else if (strcmp(input, "PLACE") == 0) {
    }
    else if (strcmp(input, "GIVE") == 0) {
    }
    else if (strcmp(input, "RECIPE") == 0) {
    }
    else if (strcmp(input, "SAVE") == 0) {
    }
    else if (strcmp(input, "LOAD") == 0) {
    }
    else if (strcmp(input, "EXIT") == 0) {
      is_running = false;
    }
    else {
      is_valid = false;
    }
    if (is_valid) {
      game_advance_time(&game);
    }
    refresh();
  }

  
  endwin();
  
  return 0;
}
