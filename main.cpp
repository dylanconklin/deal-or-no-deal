#include <iostream>
#include <string>
#include <vector>

#include "game.h"
#include "menu.h"

int main(){
  while(true){
    int selected_option = read_menu_option();
    if(selected_option == 1){
      clear_screen();
      Game * game = new Game();
      game->play();
      delete(game);
    }else if(selected_option == 2){
      std::cout << "Settings" << std::endl;
      getchar();
    }else if(selected_option == 3){
      std::cout << "Credits" << std::endl;
      getchar();
    }else if(selected_option == 4){
      exit(EXIT_SUCCESS);
    }else{
      std::cout << "Error" << std::endl;
      getchar();
      std::cout << std::endl;
    }
  }
}
