#include "game.h"

void game_init(Game *game, const char *name) {
  int i;
  indeks y, x;
  
  strcpy(game->name, name);
  game->money = 500;
  game->life = 3;
  game->time = 0;
  game->player_pos = MakePOINT(1, 1);
  game->current_map = 1;
  //CreateEmpty(&game->waiting_cust, 5);
  //CreateEmpty(&game->food_stack);
  //CreateEmpty(&game->hand);
  for (i = 0; i < MAX_MAPS; ++i) {
    MakeMATRIKS(8, 8, &game->map_tiles[i]);
    for (y = GetFirstIdxBrs(game->map_tiles[i]); y <= GetLastIdxBrs(game->map_tiles[i]); ++y) {
      for (x = GetFirstIdxKol(game->map_tiles[i]); x <= GetLastIdxKol(game->map_tiles[i]); ++x) {
        MatrixElmt(game->map_tiles[i], y, x) = ' ';
      }
    }
    MatrixElmt(game->map_tiles[i], 3, 4) = 'X';
    MatrixElmt(game->map_tiles[i], 4, 3) = 'X';
    MatrixElmt(game->map_tiles[i], 4, 4) = '1';
    MatrixElmt(game->map_tiles[i], 5, 4) = 'X';
    MatrixElmt(game->map_tiles[i], 4, 5) = 'X';
  }
}

void game_load_from_file(Game *game, const char *filename) {
  int i, x, y, w, h, n;
  
  //name
  STARTKATA(filename);
  strncpy(game->name, CKata.TabKata, 12);

  //money
  ADVKATA();
  game->money = atoi(CKata.TabKata);

  //life
  ADVKATA();
  game->life = atoi(CKata.TabKata);

  //time
  ADVKATA();
  game->time = atoi(CKata.TabKata);

  //player_pos
  ADVKATA();
  x = atoi(CKata.TabKata);
  ADVKATA();
  y = atoi(CKata.TabKata);
  game->player_pos = MakePOINT(x, y);

  //current_map
  ADVKATA();
  game->current_map = atoi(CKata.TabKata);
  
  //waiting_cust
  QueueCreateEmpty(&game->waiting_cust, 8);
  ADVKATA();
  n = atoi(CKata.TabKata);
  for (i = 1; i <= n; ++i) {
    Customer customer;
    ADVKATA();
    customer.count = atoi(CKata.TabKata);
    ADVKATA();
    customer.patience = atoi(CKata.TabKata);
    QueueAdd(&game->waiting_cust, customer);
  }

  //order
  MakeEmpty(&game->order);
  ADVKATA();
  n = atoi(CKata.TabKata);
  for (i = 1; i <= n; ++i) {
    Order ord;
    Item food;
    Customer customer;
    ADVKATA();
    strncpy(food.name, CKata.TabKata, 10);
    ord.food = food;
    ADVKATA();
    ord.table = atoi(CKata.TabKata);
    ADVKATA();
    customer.count = atoi(CKata.TabKata);
    ADVKATA();
    customer.patience = atoi(CKata.TabKata);
    ord.customer = customer;
    AddAsLastEl(&game->order, ord); 
  }

  //food_stack
  StackCreateEmpty(&game->food_stack);
  ADVKATA();
  n = atoi(CKata.TabKata);
  for (i = 1; i <= n; ++i) {
    Item item;
    ADVKATA();
    strncpy(item.name, CKata.TabKata, 10);
    StackPush(&game->food_stack, item);
  }

  //hand
  StackCreateEmpty(&game->hand);
  ADVKATA();
  n = atoi(CKata.TabKata);
  for (i = 1; i <= n; ++i) {
    Item item;
    ADVKATA();
    strncpy(item.name, CKata.TabKata, 10);
    StackPush(&game->hand, item);
  }

  //table_locations
  for (i = 1; i <= MAX_TABLES; ++i) {
    game->table_locations[i-1].map_index = 0;
  }

  //map_tiles
  ADVKATA();
  n = atoi(CKata.TabKata);
  for (i = 1; i <= n; ++i) {
    ADVKATA();
    w = atoi(CKata.TabKata);
    ADVKATA();
    h = atoi(CKata.TabKata);

    MakeMATRIKS(h, w, &game->map_tiles[i-1]);
    for (y = GetFirstIdxBrs(game->map_tiles[i-1]); y <= GetLastIdxBrs(game->map_tiles[i-1]); ++y) {
      char map_line[MAX_MAP_WIDTH + 1];
      ADVKATA();
      strncpy(map_line, CKata.TabKata, MAX_MAP_WIDTH);
      for (x = GetFirstIdxKol(game->map_tiles[i-1]); x <= GetLastIdxKol(game->map_tiles[i-1]); ++x) {
        char c = map_line[x-1];
        MatrixElmt(game->map_tiles[i-1], y, x) = c;
        if (c >= '1' && c <= '9') {
          MapLocation table_location;
          POINT point;
          table_location.map_index = i;
          point.X = x;
          point.Y = y;
          table_location.point = point;
          game->table_locations[c - '1'] = table_location;
        }
      }
    }
  }

  //map_graph
  GraphCreateEmpty(&game->map_graph);
  ADVKATA();
  n = atoi(CKata.TabKata);
  for (i = 0; i < n; ++i) {
    GraphEdge edge;
    GraphVertex start, end;
    POINT p_start, p_end;

    ADVKATA();
    start.map_index = atoi(CKata.TabKata);
    ADVKATA();
    p_start.Y = atoi(CKata.TabKata);
    ADVKATA();
    p_start.X = atoi(CKata.TabKata);
    start.point = p_start;
    edge.start = start;

    ADVKATA();
    edge.direction = CKata.TabKata[0];

    ADVKATA();
    end.map_index = atoi(CKata.TabKata);
    ADVKATA();
    p_end.Y = atoi(CKata.TabKata);
    ADVKATA();
    p_end.X = atoi(CKata.TabKata);
    end.point = p_end;
    edge.end = end;

    GraphAddEdge(&game->map_graph, edge);
  }

  //item_locations
  ADVKATA();
  n = atoi(CKata.TabKata);
  for (i = 0; i < n; ++i) {
    ItemLocation item_location;
    Item item;
    MapLocation map_location;
    POINT point;

    ADVKATA();
    strncpy(item.name, CKata.TabKata, 10);
    item_location.item = item;
    ADVKATA();
    map_location.map_index = atoi(CKata.TabKata);
    ADVKATA();
    point.X = atoi(CKata.TabKata);
    ADVKATA();
    point.Y = atoi(CKata.TabKata);
    map_location.point = point;
    item_location.map_location = map_location;

    game->item_locations[i] = item_location;
  }
}

void game_draw_table_customers(Game *game, int table, int customer_count) {
  POINT point;
  if (game->table_locations[table-1].map_index == game->current_map) {
    point = PlusDelta(game->table_locations[table-1].point, -1, 0);
    if (MatrixElmt(game->map_tiles[game->current_map-1], point.Y, point.X) == 'X') {
      --customer_count;
      draw_map_tile(point.Y, point.X, customer_count >= 0 ? 'C' : 'X');
    }
    point = PlusDelta(game->table_locations[table-1].point, 1, 0);
    if (MatrixElmt(game->map_tiles[game->current_map-1], point.Y, point.X) == 'X') {
      --customer_count;
      draw_map_tile(point.Y, point.X, customer_count >= 0 ? 'C' : 'X');
    }
    point = PlusDelta(game->table_locations[table-1].point, 0, -1);
    if (MatrixElmt(game->map_tiles[game->current_map-1], point.Y, point.X) == 'X') {
      --customer_count;
      draw_map_tile(point.Y, point.X, customer_count >= 0 ? 'C' : 'X');
    }
    point = PlusDelta(game->table_locations[table-1].point, 0, 1);
    if (MatrixElmt(game->map_tiles[game->current_map-1], point.Y, point.X) == 'X') {
      --customer_count;
      draw_map_tile(point.Y, point.X, customer_count >= 0 ? 'C' : 'X');
    }
  }
}

void game_draw_map_tiles(Game *game) {
  int i;
  indeks y, x;
  for (y = GetFirstIdxBrs(game->map_tiles[game->current_map-1]); y <= GetLastIdxBrs(game->map_tiles[game->current_map-1]); ++y) {
    for (x = GetFirstIdxKol(game->map_tiles[game->current_map-1]); x <= GetLastIdxKol(game->map_tiles[game->current_map-1]); ++x) {
      draw_map_tile(y, x, MatrixElmt(game->map_tiles[game->current_map-1], y, x));
    }
  }
  for (i = 1; i <= MAX_TABLES; ++i) {
    //mvprintw(26 + i, 0, "%d %d %d", game->table_locations[i-1].map_index, game->table_locations[i-1].point.X, game->table_locations[i-1].point.Y);
  }

  for (i = 1; i <= NbElmt(game->order); ++i) {
    //mvprintw(26 + i, 0, "%d %d", , Elmt(game->order, i).customer.count);
    game_draw_table_customers(game, Elmt(game->order, i).table, Elmt(game->order, i).customer.count);
  }

  draw_map_tile(Ordinat(game->player_pos), Absis(game->player_pos), PLAYER_SYMBOL);
}

void game_draw_waiting_cust(Game *game) {
  int i;
  char elem[13];
  for (i = 1; i <= 8; ++i) {
    if (i <= QueueNBElmt(game->waiting_cust)) {
      snprintf(elem, 12, "%d", game->waiting_cust.T[i].count);
      draw_waiting_cust_elem(i, elem);
    }
    else {
      draw_waiting_cust_elem(i, "");
    }
  }
}

void game_draw_order(Game *game) {
  int i;
  char elem[13];
  for (i = 1; i <= 8; ++i) {
    if (i <= NbElmt(game->order)) {
      snprintf(elem, 12, "%s,%d", game->order.TI[i].food.name, game->order.TI[i].table);
      draw_order_elem(i, elem);
    }
    else {
      draw_order_elem(i, "");
    }
  }
}

void game_draw_food_stack(Game *game) {
  int i;
  for (i = 1; i <= 8; ++i) {
    if (i <= Top(game->food_stack)) {
      draw_food_stack_elem(i, game->food_stack.T[i].name);
    }
    else {
      draw_food_stack_elem(i, "");
    }
  }
}

void game_draw_hand(Game *game) {
  int i;
  for (i = 1; i <= 8; ++i) {
    if (i <= Top(game->hand)) {
      draw_hand_elem(i, game->hand.T[i].name);
    }
    else {
      draw_hand_elem(i, "");
    }
  }
}

void game_init_draw(Game *game) {
  draw_game_ui(NBrsEff(game->map_tiles[game->current_map-1]), NKolEff(game->map_tiles[game->current_map-1]));
  draw_name(game->name);
  draw_money(game->money);
  draw_life(game->life);
  draw_time(game->time);

  game_draw_waiting_cust(game);
  game_draw_order(game);
  game_draw_food_stack(game);
  game_draw_hand(game);
  game_draw_map_tiles(game);
}

void game_advance_time(Game *game) {
  ++game->time;
  draw_time(game->time);
}

void game_save_to_file(Game *game, const char *filename) {

}

boolean game_move_player(Game *game, int delta_x, int delta_y) {
  POINT next_point;
  int i;
  
  next_point = PlusDelta(game->player_pos, delta_x, delta_y);
  if (MatrixIsIdxEff(game->map_tiles[game->current_map-1], Ordinat(next_point), Absis(next_point))
      && MatrixElmt(game->map_tiles[game->current_map-1], Ordinat(next_point), Absis(next_point)) == ' ') {
    draw_map_tile(Ordinat(game->player_pos), Absis(game->player_pos), ' ');
    game->player_pos = next_point;
    draw_map_tile(Ordinat(game->player_pos), Absis(game->player_pos), PLAYER_SYMBOL);
    return true;
  }
  else {
    for (i = 0; i < game->map_graph.edge_count; ++i) {
      if (game->current_map == game->map_graph.edges[i].start.map_index
          && EQ(game->player_pos, game->map_graph.edges[i].start.point)
          && (delta_x < 0 && game->map_graph.edges[i].direction == 'W'
           || delta_x > 0 && game->map_graph.edges[i].direction == 'E'
           || delta_y < 0 && game->map_graph.edges[i].direction == 'N'
           || delta_y > 0 && game->map_graph.edges[i].direction == 'S'
          )) {
        game->current_map = game->map_graph.edges[i].end.map_index;
        game->player_pos = game->map_graph.edges[i].end.point;
        game_draw_map_tiles(game);
        return true;
      }
    }
    return false;
  }
}

boolean game_take_order(Game *game) {
  return false;
}

boolean game_put_food(Game *game) {
  return false;
}

boolean game_take_item(Game *game) {
  return false;
}

boolean game_clear_hand(Game *game) {
  stackinfotype temp;

  if (game->hand.TOP > 0) {
    while (game->hand.TOP > 0) {
      StackPop(&game->hand, &temp);
    }
    game_draw_hand(game);
    return true;
  }
  else {
    return false;
  }
}

boolean game_clear_tray(Game *game) {
  stackinfotype temp;

  if (game->food_stack.TOP > 0) {
    while (game->food_stack.TOP > 0) {
      StackPop(&game->food_stack, &temp);
    }
    game_draw_food_stack(game);
    return true;
  }
  else {
    return false;
  }
}

boolean game_place_customer(Game *game) {
  return false;
}

boolean game_give_food(Game *game) {
  return false;
}