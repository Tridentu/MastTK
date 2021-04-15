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
    
    enum class WindowType {
      SubWindow,
      RegularWindow
    };
    
    class Window {
    public:
      WindowBorder border;
      void draw(bool use_border = true);
      void toggle_keypad(bool on);
      Window(int height, int width, int startx, int starty, WindowType type, Window* root_win = nullptr);
      ~Window();
      void set_border(WindowBorder border2);
      void set_menu(MENU*& menu);
      void set_menu_subw(MENU*& menu);
      int get_input();
      WINDOW* getWindow() const;
      void refresh();
    private:
      WINDOW* window_pvt;
      
    };

 
    
  }
}
