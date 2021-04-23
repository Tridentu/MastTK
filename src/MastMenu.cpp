
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <curses.h>
#include <menu.h>
#include <mast_tk/MastWindow.h>
#include <algorithm>
#include <any>
#include <functional>
#include <sigc++-3.0/sigc++/signal.h>
#include <map>
#include "MastMenu.h"

using namespace std;

Mast::TK::Menu::Menu() {
  currentIndex = 0;
  init_pair(1, COLOR_CYAN, COLOR_BLACK);
  pair = 1;
}

Mast::TK::Menu::Menu(Mast::TK::Window* wind, Mast::TK::ColorMap colorMap, Mast::TK::ColorPair new_pair){
  currentIndex = 0;
  int i = 0;
  for(auto it = colorMap.begin(); it != colorMap.end(); ++it){
    i++;
    init_pair(i, it->first, it->second);
  }
  pair = new_pair;
  win = wind;
}

void Mast::TK::Menu::toggleInput(bool use_input){
  win->toggle_keypad(use_input);
}

void Mast::TK::Menu::setExitKey(int exitFKey2){
  exitFKey = exitFKey2;
}

int Mast::TK::Menu::getExitKey() const {
  return exitFKey;
}

void Mast::TK::Menu::setColorPair(Mast::TK::ColorPair pair2) {
 pair = pair2;
}

Mast::TK::ColorPair Mast::TK::Menu::getColorPair() const {
  return pair;
}

void Mast::TK::Menu::processInput(int c) {
    switch(c){
        case KEY_DOWN:
            menu_driver(menu_pvt, REQ_DOWN_ITEM);
            if(currentIndex < (options_vec.size() - 1))
                currentIndex++;
            break;
        case KEY_UP:
            menu_driver(menu_pvt, REQ_UP_ITEM);
            if(currentIndex  > (0))
                currentIndex--;
            break;
        case KEY_NPAGE:
            menu_driver(menu_pvt, REQ_SCR_DPAGE);
            break;
        case KEY_PPAGE:
            menu_driver(menu_pvt, REQ_SCR_UPAGE);
            break;
        case 10:
            onSelect(currentIndex);
            break;
    }
}


void Mast::TK::Menu::addPointer(int index, std::any pointer){
  pointers[index] = pointer;
}

void Mast::TK::Menu::generateMenu(bool show_desc){
    int n_choices = this->options_vec.size();
    options = (char**)calloc(n_choices, 258*sizeof(char));
    values = (char**)calloc(n_choices, 258*sizeof(char));
    for(int i = 0; i < n_choices; ++i){
      options[i] = (char*)malloc(1+(options_vec[i].size()*sizeof(char)));
      values[i] = (char*)malloc(1+(values_vec[i].size()*sizeof(char)));
        strcpy(options[i], options_vec[i].c_str());
        strcpy(values[i], values_vec[i].c_str());
    }
   menu_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
   for(int i = 0; i < n_choices; ++i){
        menu_items[i] = new_item(options[i], values[i]);
   }
    menu_items[n_choices] = (ITEM *)NULL;
    menu_pvt = new_menu((ITEM **)menu_items);
    set_menu_format(menu_pvt, 40, 1);
}

void Mast::TK::Menu::draw(){
    attron(COLOR_PAIR(1));
    win->set_menu(menu_pvt);
    sub_win = derwin(win->getWindow(), win->border.height - 4, win->border.width - 2, 4, 2);
    set_menu_sub(menu_pvt, sub_win);
    displayExitMsg();
	refresh();
    post_menu(menu_pvt);
    win->draw(true);
    attroff(COLOR_PAIR(1));
}


void Mast::TK::Menu::displayExitMsg(){
    std::string exit_str = "F";
    exit_str += std::to_string(exitFKey);
    exit_str +=  " to Exit";
    mvprintw(LINES - 2, 1, exit_str.c_str());
}


Mast::TK::Menu::~Menu(){
  for(int i = 1; i < options_vec.size() + 1; ++i)
    free_item(menu_items[i]);
  free_menu(menu_pvt);
  
  
  
}

void Mast::TK::Menu::clearScreen(){
  if(this->win){
    this->win->clearScreen();
    wclear(this->sub_win);
  }
}
