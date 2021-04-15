
#include <curses.h>
#include "MastWindow.h"

Mast::TK::Window::Window(int height, int width, int startx, int starty){
  border = (Mast::TK::WindowBorder){
    .height = height,
    .width = width,
    .startx = startx,
    .starty = starty,
    .ls = '|',
    .rs = '|',
    .ts = '-',
    .bs = '-',
    .tl = '+',
    .bl = '+',
    .br = '+',
    .tr = '+'
  };

}

void Mast::TK::Window::toggle_keypad(bool on){
  keypad(this->window_pvt, (on) ? TRUE : FALSE);
}

Mast::TK::Window::~Window(){
  
}

void Mast::TK::Window::set_border(Mast::TK::WindowBorder border2){
  border = border2;
}

void Mast::TK::Window::set_menu(MENU*& menu) {
  set_menu_win(menu, this->window_pvt);
}


void Mast::TK::Window::draw(bool use_border) {
  window_pvt = newwin(border.height, border.width, border.starty, border.startx);
  int x, y, w, h;
  x = border.startx;
  y = border.starty; 
  w = border.width;
  h = border.height;
  if(use_border){
    mvaddch(y, x, border.tl);
    mvaddch(y, x + w, border.tr);
    mvaddch(y + h, x, border.bl);
    mvaddch(y + h, x + w, border.br );
    mvvline(y + 1, x, border.ls, h - 1);
    mvvline(y + 1, x + w, border.rs, h - 1);
    mvhline(y , x + 1, border.ts, w - 1);
    mvhline(y + h, x + 1, border.bs, w - 1);
  }
  refresh();
  
}

