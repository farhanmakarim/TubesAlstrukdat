#include "game.h"

// Assumes 0 <= max <= RAND_MAX
// Returns in the closed interval [0, max]
long random_max(long max) {
  unsigned long
    // max <= RAND_MAX < ULONG_MAX, so this is okay.
    num_bins = (unsigned long) max + 1,
    num_rand = (unsigned long) RAND_MAX + 1,
    bin_size = num_rand / num_bins,
    defect   = num_rand % num_bins;

  long x;
  do {
   x = random();
  }
  // This is carefully written not to overflow
  while (num_rand - defect <= (unsigned long)x);

  // Truncated division is intentional
  return x/bin_size;
}

void game_queue_customer(Game *game) {
  if (game->time_to_next_customer <= 0 && !QueueIsFull(game->waiting_cust)) {
    Customer customer;
    customer.count = 1 + random_max(3);
    customer.patience = 30;
    QueueAdd(&game->waiting_cust, customer);
    game->time_to_next_customer = 5 + (int) random_max(10);
  }
  else {
    --game->time_to_next_customer;
  }
}

BinTree game_depth_first_read_tree(Game *game, int depth) {
  ADVKATA();
  if (CKata.TabKata[0] == '0') {
    return TreeNil;
  }
  else {
    Item item;
    strncpy(item.name, CKata.TabKata, 10);
    game->food_prices[game->food_count] = 100 * (depth + 1);
    ADVKATA();
    if (CKata.TabKata[0] == '0') {
      game->foods[game->food_count] = item;
      ++game->food_count;
      return Tree(item, TreeNil, TreeNil);
    }
    else {
      BinTree left, right;
      ItemLocation item_location;
      MapLocation map_location;
      POINT point;
      item_location.item = item;
      map_location.map_index = atoi(CKata.TabKata);
      ADVKATA();
      point.Y = atoi(CKata.TabKata);
      ADVKATA();
      point.X = atoi(CKata.TabKata);
      map_location.point = point;
      item_location.map_location = map_location;
      game->item_locations[game->item_count] = item_location;
      ++game->item_count;
      left = game_depth_first_read_tree(game, depth + 1);
      right = game_depth_first_read_tree(game, depth + 1);
      return Tree(item, left, right);
    }
  }
}

void game_new(Game *game, const char *name) {
  game_load_from_file(game, "newgame.template", name);
}

void game_load(Game *game, const char *filename) {
  game_load_from_file(game, filename, NULL);
}

void game_load_from_file(Game *game, const char *filename, const char *name) {
  int i, x, y, w, h, n;
  
  //name
  STARTKATA(filename);
  if (name == NULL) {
    strncpy(game->name, CKata.TabKata, 13);
  }
  else {
    strncpy(game->name, name, 13);
  }

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

  //table_locations
  for (i = 1; i <= MAX_TABLES; ++i) {
    game->tables[i-1].chair_count = -1;
    game->tables[i-1].order = 0;
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
    game->tables[ord.table-1].order = i;
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
          MapLocation map_location;
          map_location.map_index = i;
          map_location.point = MakePOINT(x, y);
          game->tables[c - '1'].map_location = map_location;
          game->tables[c - '1'].chair_count = 0;
        }
        else if (c == 'T') {
          game->tray_location.map_index = i;
          game->tray_location.point = MakePOINT(x, y);
        }
      }
    }
  }

  //chairs
  for (i = 1; i <= MAX_TABLES; ++i) {
    if (game->tables[i-1].chair_count == 0) {
      MapLocation map_location;
      int map_index = game->tables[i-1].map_location.map_index;
      map_location.map_index = map_index;
      x = game->tables[i-1].map_location.point.X;
      y = game->tables[i-1].map_location.point.Y;

      if (MatrixElmt(game->map_tiles[map_index-1], y, x-1) == 'X') {
        map_location.point = MakePOINT(x-1, y);
        game->tables[i-1].chairs[game->tables[i-1].chair_count] = map_location;
        ++game->tables[i-1].chair_count;
      }
      if (MatrixElmt(game->map_tiles[map_index-1], y, x+1) == 'X') {
        map_location.point = MakePOINT(x+1, y);
        game->tables[i-1].chairs[game->tables[i-1].chair_count] = map_location;
        ++game->tables[i-1].chair_count;
      }
      if (MatrixElmt(game->map_tiles[map_index-1], y-1, x) == 'X') {
        map_location.point = MakePOINT(x, y-1);
        game->tables[i-1].chairs[game->tables[i-1].chair_count] = map_location;
        ++game->tables[i-1].chair_count;
      }
      if (MatrixElmt(game->map_tiles[map_index-1], y+1, x) == 'X') {
        map_location.point = MakePOINT(x, y+1);
        game->tables[i-1].chairs[game->tables[i-1].chair_count] = map_location;
        ++game->tables[i-1].chair_count;
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

  //recipe_tree
  game->item_count = 0;
  game->food_count = 0;
  game->recipe_tree = game_depth_first_read_tree(game, 0);

  //time_to_next_customer
  game->time_to_next_customer = 0;
  game_queue_customer(game);
}

void game_draw_table_customers(Game *game, int table) {
  int i;
  if (game->tables[table-1].map_location.map_index == game->current_map) {
    for (i = 0; i < game->tables[table-1].chair_count; ++i) {
      POINT point = game->tables[table-1].chairs[i].point;
      draw_map_tile(point.Y, point.X, i < Elmt(game->order, game->tables[table-1].order).customer.count ? 'C' : 'X');
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

  for (i = 1; i <= NbElmt(game->order); ++i) {
    game_draw_table_customers(game, Elmt(game->order, i).table);
  }

  draw_map_tile(Ordinat(game->player_pos), Absis(game->player_pos), PLAYER_SYMBOL);
}

void game_draw_waiting_cust(Game *game) {
  int i;
  char elem[13];
  for (i = 1; i <= 8; ++i) {
    if (i <= QueueNBElmt(game->waiting_cust)) {
      Customer customer;
      QueueDel(&game->waiting_cust, &customer);
      snprintf(elem, 13, "%d", customer.count);
      QueueAdd(&game->waiting_cust, customer);
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
      snprintf(elem, 13, "%s,%d", game->order.TI[i].food.name, game->order.TI[i].table);
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

boolean game_advance_time(Game *game) {
  int i, n;
  ++game->time;
  draw_time(game->time);

  game_queue_customer(game);

  n = QueueNBElmt(game->waiting_cust);
  for (i = 0; i < n; ++i) {
    Customer customer;
    QueueDel(&game->waiting_cust, &customer);
    --customer.patience;
    if (customer.patience <= 0) {
      --game->life;
      draw_life(game->life);
      if (n == 1) {
        Head(game->waiting_cust) = 0;
        Tail(game->waiting_cust) = 0;
      }
    }
    else {
      QueueAdd(&game->waiting_cust, customer);
    }
  }
  game_draw_waiting_cust(game);
  for (i = NbElmt(game->order); i >= 1; --i) {
    --Elmt(game->order, i).customer.patience;
    if (Elmt(game->order, i).customer.patience <= 0) {
      Order order;
      --game->life;
      draw_life(game->life);
      DelEli(&game->order, i, &order);
      game->tables[order.table-1].order = 0;
      game_draw_table_customers(game, order.table);
    }
  }
  game_draw_order(game);
  if (game->life <= 0) {
    draw_credits(game->money, game->time);
    return false;
  }
  else {
    return true;
  }
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

boolean game_is_interactable(Game *game, MapLocation map_location) {
  return game->current_map == map_location.map_index
      && (EQ(PlusDelta(game->player_pos, -1, 0), map_location.point)
      || EQ(PlusDelta(game->player_pos, 1, 0), map_location.point)
      || EQ(PlusDelta(game->player_pos, 0, -1), map_location.point)
      || EQ(PlusDelta(game->player_pos, 0, 1), map_location.point));
}



boolean game_put_food(Game *game) {
  Item item;
  BinTree left = game->recipe_tree;
  BinTree right = game->recipe_tree;
  if (game_is_interactable(game, game->tray_location) && !StackIsEmpty(game->hand)) {
    while (!StackIsEmpty(game->hand)) {
      StackPop(&game->hand, &item);
      if (left != TreeNil && strcmp(Akar(left).name, item.name) == 0) {
        right = Right(left);
        left = Left(left);
      }
      else if (right != TreeNil && strcmp(Akar(right).name, item.name) == 0) {
        left = Left(right);
        right = Right(right);
      }
      else {
        break;
      }
      if (right == TreeNil && left != TreeNil && Left(left) == TreeNil && Right(left) == TreeNil) {
        StackPush(&game->food_stack, Akar(left));
        game_draw_food_stack(game);
      }
    }
    game_draw_hand(game);
    return true;
  }
  else {
    return false;
  }
}

boolean game_take_item(Game *game) {
  int i;
  for (i = 0; i < game->item_count; ++i) {
    if (game_is_interactable(game, game->item_locations[i].map_location)) {
      StackPush(&game->hand, game->item_locations[i].item);
      game_draw_hand(game);
      return true;
    }
  }
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
  Item temp;

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

int game_get_interactable_table(Game *game) {
  int i, j;
  for (i = 1; i <= MAX_TABLES; ++i) {
    if (game->tables[i-1].chair_count > 0) {
      if (game_is_interactable(game, game->tables[i-1].map_location)) {
        return i;
      }
      for (j = 0; j < game->tables[i-1].chair_count; ++j) {
        if (game_is_interactable(game, game->tables[i-1].chairs[j])) {
          return i;
        }
      }
    }
  }
  return 0;
}

boolean game_place_customer(Game *game) {
  int table, i, n;
  boolean found;
  Customer customer;
  Order order;
  Item food;

  found = false;
  if (!QueueIsEmpty(game->waiting_cust)) {
    table = game_get_interactable_table(game);
    if (table > 0 && !game->tables[table-1].order > 0) {
      n = QueueNBElmt(game->waiting_cust);
      for (i = 0; i < n; ++i) {
        QueueDel(&game->waiting_cust, &customer);
        if (customer.count > game->tables[table-1].chair_count || found) {
          QueueAdd(&game->waiting_cust, customer);
        }
        else {
          order.food.name[0] = '?';
          order.customer = customer;
          order.customer.patience += 30 + random_max(3) * 10;
          order.table = table;
          AddAsLastEl(&game->order, order);
          game->tables[table-1].order = NbElmt(game->order);
          game_draw_table_customers(game, table);
          found = true;
          if (n == 1) {
            Head(game->waiting_cust) = 0;
            Tail(game->waiting_cust) = 0;
          }
        }
      }
    }
  }
  return found;
}

boolean game_take_order(Game *game) {
  int table = game_get_interactable_table(game);
  if (table > 0 && Elmt(game->order, game->tables[table-1].order).food.name[0] == '?') {
    Elmt(game->order, game->tables[table-1].order).food = game->foods[(int) random_max(game->food_count - 1)];
    return true;
  }
  else {
    return false;
  }
}

int game_find_food_price(Game *game, Item item) {
  int i;
  for (i = 0; i < game->food_count; ++i) {
    if (strcmp(game->foods[i].name, item.name) == 0) {
      return game->food_prices[i];
    }
  }
  return 0;
}

boolean game_give_food(Game *game) {
  int table = game_get_interactable_table(game);
  
  if (table > 0) {
    int order_index = game->tables[table-1].order;
    if (strcmp(InfoTop(game->food_stack).name, Elmt(game->order, order_index).food.name) == 0) {
      Order order;
      Item item;
      DelEli(&game->order, order_index, &order);
      StackPop(&game->food_stack, &item);
      game_draw_food_stack(game);
      game->money += game_find_food_price(game, Elmt(game->order, order_index).food);
      draw_money(game->money);
      game->tables[table-1].order = 0;
      game_draw_table_customers(game, table);
      return true;
    }
    else {
      return false;
    }
  }
  else {
    return false;
  }
}

void game_show_recipe_tree(Game *game) {
  draw_recipe_tree(game->recipe_tree);
}