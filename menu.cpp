#include <iostream>
#include <cmath>
#include <string>
#include <vector>

#include "menu.h"

void clear_screen(){
  if(getenv("windir"))
    system("cls");
  else
    system("clear");
}

void print_logo(){
  std::cout << "     ";
  printf("\033[3;43;30m     Deal    \033[0m");
  printf("\033[3;33;40m or \033[0m");
  printf("\033[3;43;30m   No Deal   \033[0m");
  std::cout << std::endl;
}

void print_menu(){
  clear_screen();
  print_logo();
  std::cout << std::endl;
  std::vector <std::string> menu_items;
  menu_items.push_back("Play Game");
  menu_items.push_back("Settings");
  menu_items.push_back("Credits");
  menu_items.push_back("Exit");
  for(unsigned int i = 0; i < menu_items.size(); i++)
    std::cout << i+1 << ". " << menu_items[i] << std::endl;
  std::cout << std::endl;
}

int read_menu_option(){
  print_menu();
  std::cout << "Please enter an option: ";
  std::string selected_item;
  getline(std::cin, selected_item);
  return stoi(selected_item);
}

bool make_offer(std::vector <Case *> cases, int &offer){
  clear_screen();
  int sum = 0;
  int closed_cases = 0;
  std::string answer;
  for(unsigned int i = 0; i < cases.size(); i++){
    sum += (cases[i]->opened) ? 0 : cases[i]->value;
    closed_cases += (cases[i]->opened) ? 0 : 1;
  }
  offer = round((sum / closed_cases) * 0.85);
  std::cout << "The bank is offering you " << offer << std::endl << std::endl;
  std::cout << "DEAL or NO DEAL?" << std::endl << std::endl;
  std::cout << ">>> ";
  getline(std::cin, answer);
  if(!(answer == "deal") && !(answer == "no deal"))
    return make_offer(cases, offer);
  return (answer == "deal") ? true : false;
}

void win_message(int amount_won){
  clear_screen();
  if(amount_won == 1000000)
    std::cout << "Congratulations! You're a millionaire!" << std::endl;
  else if(amount_won == 0)
    std::cout << "Sorry, you only won $ 0.01" << std::endl;
  else
    std::cout << "You won $ " << amount_won << std::endl;
  std::cout << std::endl << "Press any key to continue..." << std::endl;
  getchar();
}
