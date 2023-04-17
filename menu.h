#ifndef MENU_H
#define MENU_H

#include "game.h"

void clear_screen();
void print_logo();
void print_menu();
int read_menu_option();
bool make_offer(std::vector <Case *>, int &);
void win_message(int);

#endif
