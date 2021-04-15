#pragma once

#include <curses.h>
#include <string>
#include <menu.h>

namespace Mast {
  namespace TK {
    typedef struct {
      int height;
      int width;
      int startx;
      int starty;
      char ls;
      char rs;
      char ts;
      char bs;
      char tl;
      char bl;
      char br;
      char tr;
    } WindowBorder;
    class Window {
    public:
      WindowBorder border;
      void draw(bool use_border = true);
      void toggle_keypad(bool on);
      Window(int height, int width, int startx, int starty);
      ~Window();
      void set_border(WindowBorder border2);
    private:
      WINDOW* window_pvt;
      
    };

 
    
  }
}
