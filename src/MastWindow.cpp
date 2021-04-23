
#include <curses.h>
#include "MastWindow.h"

Mast::TK::Window::Window(int height, int width, int startx, int starty, WindowType type, Window* root_win){
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
  switch(type){
      case Mast::TK::WindowType::RegularWindow:
          window_pvt = newwin(border.height, border.width, border.starty, border.startx);
          break;
      case Mast::TK::WindowType::SubWindow:
          window_pvt = derwin(root_win->getWindow(), border.height, border.width, border.starty, border.startx);
          break;
  }
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

void Mast::TK::Window::set_menu_subw(MENU*& menu) {
  set_menu_sub(menu, this->window_pvt);
}

int Mast::TK::Window::get_input(){
    return wgetch(this->window_pvt);
}

WINDOW* Mast::TK::Window::getWindow() const {
    return this->window_pvt;
}

void Mast::TK::Window::refresh() {
    wrefresh(this->window_pvt);
}

void Mast::TK::Window::clearScreen(){
  wclear(this->window_pvt);
}

void Mast::TK::Window::draw(bool use_border) {
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

void Mast::TK::Window::toggleCursor(bool on){
  cursor_active = on;
}

void Mast::TK::Window::processCursorInput(int c){
  if(cursor_active){
    curs_set(1);
  } else {
    curs_set(0);
  }
}
