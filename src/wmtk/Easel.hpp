

#pragma once

#include <X11/Xft/Xft.h>
#include <X11/Xlib.h>
#include <fontconfig/fontconfig.h>
#include <X11/Xutil.h>
#include <string>
#include <map>
#include <vector>
#include "../core/MastDimension.hpp"


namespace MastTDE {
 class MastEasel;
 struct MastFont {
   Display *display;
   MastDimension HDim;
   XftFont *xFont;
   FcPattern *pattern;
   int screen;
   MastFont(std::string fontName, Display *display2){
     display = display2;
     Setup(fontName); 
   }
    MastFont(FcPattern* pattern, Display *display2){
     display = display2;
     Setup(pattern); 
   }
   void Setup(std::string fontName);
   void Setup(FcPattern* pattern);
   void Free();
   uint32_t GetWidth(std::string text, MastEasel* easel);
   void GetText(std::string text, uint32_t len, MastDimension dim);
   MastFont(const MastFont& other) = default;
    };


  


  struct MastCursor {
    Cursor cursor;
    Display* displayVar;
    MastCursor(int shape, Display* display);
    MastCursor(const MastCursor& other) = default;
    void Free();
  };

  typedef std::vector<MastFont*> FontSet;
  typedef std::map<std::string, XftColor*> ColorSchemeSet;
  typedef int ScreenID;
  
  class MastEasel {
  protected:
    Display *display;
    FontSet fonts;
    ColorSchemeSet colorSchemes;
    std::string colorScheme_current;
    ScreenID currentScreen;
    MastDimension dimensions;
    Window root;
    Drawable drawable;
    GC gc;
  public:
    MastEasel(Display *dpy, ScreenID screen, Window win, MastDimension dim);
    ~MastEasel();
  public:
    virtual void Resize(MastDimension dim);
    virtual void AddFonts(std::vector<std::string> fontNames);
    virtual XftColor* CreateColorScheme(std::string name, std::vector<std::string> colorNames);
    virtual void CreateColor(XftColor *dest, std::string colorName);
    virtual void SetCurrentColorScheme(std::string colorScheme);
    virtual MastFont* GetFont(int index);
    virtual XftColor* GetCurrentColors();
    virtual void DrawRect(MastDimension dim, bool filled, bool invert);
    virtual int  DrawText(MastDimension dim, uint32_t lpad, std::string text, bool invert);
    virtual void DrawMap(Window win, MastDimension dim);
    virtual void RemoveFont(MastFont * font);
  };

}
