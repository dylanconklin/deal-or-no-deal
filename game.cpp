#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "game.h"
#include "menu.h"

Tile::Tile(std::string value_string){
  this->picked = false;
  this->value_string = value_string;
}

Case::Case(int index, int value){
  this->index = index;
  this->value = value;
  this->opened = false;
  this->user_case = false;
}

Game::Game(){
  tiles.push_back(new Tile("$      0.01"));
  tiles.push_back(new Tile("$         1"));
  tiles.push_back(new Tile("$         5"));
  tiles.push_back(new Tile("$        10"));
  tiles.push_back(new Tile("$        25"));
  tiles.push_back(new Tile("$        50"));
  tiles.push_back(new Tile("$        75"));
  tiles.push_back(new Tile("$       100"));
  tiles.push_back(new Tile("$       200"));
  tiles.push_back(new Tile("$       300"));
  tiles.push_back(new Tile("$       400"));
  tiles.push_back(new Tile("$       500"));
  tiles.push_back(new Tile("$       750"));
  tiles.push_back(new Tile("$     1,000"));
  tiles.push_back(new Tile("$     5,000"));
  tiles.push_back(new Tile("$    10,000"));
  tiles.push_back(new Tile("$    25,000"));
  tiles.push_back(new Tile("$    50,000"));
  tiles.push_back(new Tile("$    75,000"));
  tiles.push_back(new Tile("$   100,000"));
  tiles.push_back(new Tile("$   200,000"));
  tiles.push_back(new Tile("$   300,000"));
  tiles.push_back(new Tile("$   400,000"));
  tiles.push_back(new Tile("$   500,000"));
  tiles.push_back(new Tile("$   750,000"));
  tiles.push_back(new Tile("$ 1,000,000"));
  
  cases.push_back(new Case( 0,       0));
  cases.push_back(new Case( 1,       1));
  cases.push_back(new Case( 2,       5));
  cases.push_back(new Case( 3,      10));
  cases.push_back(new Case( 4,      25));
  cases.push_back(new Case( 5,      50));
  cases.push_back(new Case( 6,      75));
  cases.push_back(new Case( 7,     100));
  cases.push_back(new Case( 8,     200));
  cases.push_back(new Case( 9,     300));
  cases.push_back(new Case(10,     400));
  cases.push_back(new Case(11,     500));
  cases.push_back(new Case(12,     750));
  cases.push_back(new Case(13,    1000));
  cases.push_back(new Case(14,    5000));
  cases.push_back(new Case(15,   10000));
  cases.push_back(new Case(16,   25000));
  cases.push_back(new Case(17,   50000));
  cases.push_back(new Case(18,   75000));
  cases.push_back(new Case(19,  100000));
  cases.push_back(new Case(20,  200000));
  cases.push_back(new Case(21,  300000));
  cases.push_back(new Case(22,  400000));
  cases.push_back(new Case(23,  500000));
  cases.push_back(new Case(24,  750000));
  cases.push_back(new Case(25, 1000000));

  unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
  shuffle(cases.begin(), cases.end(), std::default_random_engine(seed));
}

Game::~Game(){
  for(unsigned int i = 0; i < cases.size(); i++)
    delete(cases[i]);
  for(unsigned int i = 0; i < tiles.size(); i++)
    delete(tiles[i]);
}

void Game::play(){
  int user_case = take_turn();
  bool accepted_bank_offer = false;
  int amount_won = 0;
  std::cout << std::endl << "You chose case number " << user_case << std::endl << std::endl << "Press any key to continue...";
  cases[user_case-1]->user_case = true;
  getchar();
  std::vector <int> numbers;
  numbers.push_back(6);
  numbers.push_back(5);
  numbers.push_back(4);
  numbers.push_back(3);
  numbers.push_back(2);
  numbers.push_back(1);
  numbers.push_back(1);
  numbers.push_back(1);
  numbers.push_back(1);
  for(unsigned int i = 0; i < numbers.size(); i++){
    open_cases(numbers[i]);
    accepted_bank_offer = make_offer(cases, amount_won);
    if(accepted_bank_offer)
      break;
  }
  if(!(accepted_bank_offer))
    user_case = switch_case(user_case);
  win_message(amount_won);
}

int Game::switch_case(int user_case){
  clear_screen();
  print_logo();
  print_data();
  int last_case = 0;
  std::string response;
  for(unsigned int i = 0; i < cases.size(); i++){
    if(cases[i]->opened == false && cases[i]->user_case == false){
      last_case = i+1;
      break;
    }
  }
  std::cout << "There's one case left... case number " << last_case << std::endl << std::endl;
  std::cout << "Would you like to switch your case?" << std::endl << std::endl;

  getline(std::cin, response);
  if(!(response == "yes" || response == "no"))
    return switch_case(user_case);

  return (response == "yes") ? last_case : user_case;
}

void Game::open_cases(int number_of_turns){
  for(int i = 0; i < number_of_turns; i++){
    int chosen_case = take_turn();
    std::cout << std::endl << "You chose case number " << chosen_case << std::endl << std::endl;
    std::cout << "Case " << chosen_case << " is worth $ ";
    if(cases[chosen_case-1]->value != 0)
      std::cout << cases[chosen_case-1]->value;
    else
      std::cout << "0.01";
    tiles[cases[chosen_case-1]->index]->picked = true;
    tiles[cases[chosen_case-1]->index]->value_string = "           ";
    cases[chosen_case-1]->opened = true;
    std::cout << std::endl << std::endl << "Press any key to continue...";
    getchar();
  }
}

int Game::choose_case(){
  std::cout << std::endl << "Please choose a case: ";
  std::string chosen_case;
  getline(std::cin, chosen_case);
  int casenum = stoi(chosen_case);
  if(casenum > 26 || casenum < 1 || cases[casenum-1]->opened){
    std::cout << "Invalid option" << std::endl;
    getchar();
    return take_turn();
  }
  cases[casenum-1]->opened = true;
  return casenum;
}

int Game::take_turn(){
  clear_screen();
  print_logo();
  print_data();
  return choose_case();
}

void Game::print_table(){
  std::cout << "     " << "\033[3;43;30m             \033[0m" << "    " << "\033[3;43;30m             \033[0m";
  std::cout << std::endl;
  for(int i = 0; i < 13; i++){
    std::cout << "     ";
    std::cout << "\033[3;43;30m " << this->tiles[i]->value_string << " \033[0m";
    std::cout << "    ";
    std::cout << "\033[3;43;30m " << this->tiles[i+13]->value_string << " \033[0m";
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void Game::print_case(int i){
  if(cases[i-1]->opened)
    std::cout << "      ";
  else{
    if(i < 10){
      std::cout << "\033[3;47;30m " << " " << i << " \033[0m" << "  ";
    }else{
      std::cout << "\033[3;47;30m " << i << " \033[0m" << "  ";
    }
  }
}

void Game::print_cases(){
  std::cout << std::endl << "   ";
  for(int i = 21; i <= 26; i++){
    print_case(i);
  }
  std::cout << std::endl << std::endl;
  for(int i = 14; i <= 20; i++){
    print_case(i);
  }
  std::cout << std::endl << std::endl;
  for(int i = 7; i <= 13; i++){
    print_case(i);
  }
  std::cout << std::endl << std::endl << "   ";
  for(int i = 1; i <= 6; i++){
    print_case(i);
  }
  std::cout << std::endl;
}

void Game::print_data(){
  print_table();
  print_cases();
}
