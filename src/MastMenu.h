#pragma once

#include <string>
#include <cstring>
#include <vector>
#include <curses.h>
#include <menu.h>
#include <mast_tk/MastWindow.h>
#include <algorithm>
#include <functional>
#include <any>
#include <sigc++-3.0/sigc++/signal.h>
#include <map>

using namespace std;

namespace Mast {
 namespace TK {
   typedef std::vector<string> StringEntryVector;
   typedef std::function<void(int)> ItemCallback;
   typedef sigc::signal<void(int)> ItemSelectedEvent;
   typedef std::map<int,bool> BoolChoiceMap;
   typedef std::map<int, int> ColorMap;
   typedef int ColorPair;
   class Menu {
   public:
       Menu();
     explicit Menu(Window* wind, ColorMap colorMap, ColorPair new_pair);
       ~Menu();
       void generateMenu(bool show_desc);
       virtual void addEntry(string name, std::string value) {
            options_vec.push_back(name);
            values_vec.push_back(value);
       };
       virtual void removeEntry(int index) {
            options_vec.erase(options_vec.begin()+index);   
       };
       void draw();
       int currentIndex;
       void toggleInput(bool use_input);
       void setExitKey(int exitFKey2);
       int getExitKey() const;
       void setColorPair(ColorPair pair2);
       ColorPair getColorPair() const;
       void processInput(int c);
       ItemSelectedEvent onSelect;
       void displayExitMsg();
   protected:
       MENU* menu_pvt;
       ITEM** menu_items;
       StringEntryVector options_vec;
       StringEntryVector values_vec;
       char** options;
       char** values;
       Window* win;
       WINDOW* sub_win;
       ColorPair pair;
       int exitFKey;
       void resetIndex();
       virtual void trigger(int index) {
          this->onSelect(index);  
       };
   };
   
   class MultiChoiceMenu : public Menu {
   public:
       BoolChoiceMap switches;
   protected:
       virtual void trigger(int index) {
            Menu::trigger(index);
            this->switches[index] = !this->switches[index];
       };
       
   };
 }
}

