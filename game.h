#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

class Tile{
 public:
  Tile(std::string); // DONE
  std::string value_string;
  bool picked;
};

class Case{
 public:
  Case(int, int); // DONE
  int value;
  int index;
  bool opened;
  bool user_case;
};

class Game{
 public:
  Game();
  ~Game();
  void print_table();
  int choose_case();
  int take_turn();
  void open_cases(int);
  void print_data();
  void play();
  void print_cases();
  void print_case(int);
  int switch_case(int);
 private:
  std::vector <Tile *> tiles;
  std::vector <Case *> cases;
};

#endif
