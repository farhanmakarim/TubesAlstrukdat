#include "game.h"

int main() {
  srand(time(NULL));

  char name[64];
  strcpy(name, "?");

  Game game;

  boolean loaded = false;
  boolean loop = true;
  while (loop) {
    int input;
    printf("ENGI'S KITCHEN EXPANSION\n\n\n1. New Game\n2. Start Game\n3. Load Game\n4. Quit Game\n\nInput: ");
    scanf("%d", &input);
    switch (input) {
      case 1: 
        printf("Name: ");
        scanf("%10s", name);
        game_new(&game, name);
        loaded = true;
      break;
      case 2: 
        if (loaded) {
          loop = false; 
        }
        else {
          printf("Please create a new game or load an existing game first\n");
        }
      break;
      case 3:
        printf("Filename: ");
        scanf("%s", name);
        game_load(&game, name);
        loaded = true;
      break;
      case 4: return 0;
    }
    printf("\n\n");
  }
  
  initscr();
  game_init_draw(&game);
  
  char input[68];
  boolean is_running = true;
  boolean advance_time = true;
  
  while (is_running) {
    clear_command();
    advance_time = true;
    getnstr(input, 67);
    
    if (strcmp(input, "GU") == 0) {
      advance_time = game_move_player(&game, 0, -1);
    }
    else if (strcmp(input, "GD") == 0) {
      advance_time = game_move_player(&game, 0, 1);
    }
    else if (strcmp(input, "GL") == 0) {
      advance_time = game_move_player(&game, -1, 0);
    }
    else if (strcmp(input, "GR") == 0) {
      advance_time = game_move_player(&game, 1, 0);
    }
    else if (strcmp(input, "ORDER") == 0) {
      advance_time = game_take_order(&game);
    }
    else if (strcmp(input, "PUT") == 0) {
      advance_time = game_put_food(&game);
    }
    else if (strcmp(input, "TAKE") == 0) {
      advance_time = game_take_item(&game);
    }
    else if (strcmp(input, "CH") == 0) {
      advance_time = game_clear_hand(&game);
    }
    else if (strcmp(input, "CT") == 0) {
      advance_time = game_clear_tray(&game);
    }
    else if (strcmp(input, "PLACE") == 0) {
      advance_time = game_place_customer(&game);
    }
    else if (strcmp(input, "GIVE") == 0) {
      advance_time = game_give_food(&game);
    }
    else if (strcmp(input, "RECIPE") == 0) {
      game_show_recipe_tree(&game);
      advance_time = false;
      getch();
      game_init_draw(&game);
    }
    else if (strcmp(input, "SAVE") == 0) {
    }
    else if (strcmp(input, "LOAD") == 0) {
    }
    else if (strcmp(input, "EXIT") == 0) {
      is_running = false;
    }
    else {
      advance_time = false;
    }
    if (advance_time) {
      if (!game_advance_time(&game)) {
        getch();
        is_running = false;
      }
    }
    refresh();
  }

  
  endwin();
  
  return 0;
}
