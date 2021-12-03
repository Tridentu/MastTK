#include <X11/Xlib.h>
#include <X11/Xft/Xft.h>
#include <sstream>
#include "UnicodeUtils.hpp"
#include "../core/MastDimension.hpp"
#include "Easel.hpp"
#include "../core/GenericUtils.hpp"
#include "../core/NumberUtils.hpp"
#include <string.h>
#include <stdlib.h>
#include <vector>

namespace MastTDE {
  MastEasel::MastEasel(Display *dpy, int screen, Window win, MastDimension dim){
    display = dpy;
    currentScreen = screen;
    root = win;
    dimensions = dim;
    drawable = XCreatePixmap(display,drawable,dimensions.Width,dimensions.Height,DefaultDepth(display,screen));
    gc = XCreateGC(display,root,0,NULL);
    XSetLineAttributes(display,gc,1,LineSolid,CapButt,JoinMiter);
  }

  void MastEasel::Resize(MastDimension dim){
    dimensions = dim;
    if(drawable)
      XFreePixmap(display,drawable);
    drawable = XCreatePixmap(display,root,dimensions.Width,dimensions.Height,DefaultDepth(display,currentScreen));
    
  }

  MastEasel::~MastEasel(){
    XFreePixmap(display, drawable);
    XFreeGC(display, gc);
  }

  void MastFont::Setup(std::string fontName){
    xFont = XftFontOpenName(display,screen,fontName.c_str());
    if (!xFont){
      std::stringstream msg;
      msg << "error, can't load font from name." << fontName;
      Exit(msg.str());
      return;
    }
    pattern = FcNameParse((FcChar8*)fontName.c_str());
    if (!pattern){
      std::stringstream msg;
      msg << "error, can't parse font name to pattern ." << fontName;
      XftFontClose(display,xFont);
      Exit(msg.str());
    }
    FcBool isCol;
    if (FcPatternGetBool(xFont->pattern,FC_COLOR,0,&isCol) == FcResultMatch && isCol){
      XftFontClose(display, xFont);
      return;
    }
    HDim.Height = xFont->ascent + xFont->descent;
    
  }

  void MastFont::Setup(FcPattern* pattern){
    xFont = XftFontOpenPattern(display,pattern);
    if (!xFont){
      std::stringstream msg;
      msg << "error, can't load font from namepattern.";
      Exit(msg.str());
      return;
    }
    FcBool isCol;
    if (FcPatternGetBool(xFont->pattern,FC_COLOR,0,&isCol) == FcResultMatch && isCol){
      XftFontClose(display, xFont);
      return;
    }
    HDim.Height = xFont->ascent + xFont->descent;
    
  }


  void MastFont::Free(){
    if(pattern)
      FcPatternDestroy(pattern);
    XftFontClose(display,xFont);
    free(this);
  }

  void MastEasel::AddFonts(std::vector<std::string> fontNames){
    MastFont* font;
    size_t i;
    for (int i = 0; i < fontNames.size(); ++i){
      font = new MastFont(fontNames.at(i), display);
      if (font){
	fonts.push_back(font);
      }
    }
  }

  MastFont* MastEasel::GetFont(int index){
    return fonts.at(index);
  }


  void MastEasel::RemoveFont(MastFont* font){
    if(!font)
      return; 
    int it;
    for (size_t i = 0; i < fonts.size(); ++i){
      if(fonts.at(i) == font){
	it = i;
	break;
      }
    }
    if (fonts.begin()  + it == fonts.end())
      return;
    font->Free();
    fonts.erase(fonts.begin()+  it);
    
  }

  void MastEasel::CreateColor(XftColor *dest, std::string colorName){
    if(!dest || colorName.empty())
      return;
    auto res = XftColorAllocName(display,DefaultVisual(display, currentScreen),DefaultColormap(display,currentScreen),colorName.c_str() , dest);
    if(!res){
      std::stringstream msg;
      msg << "Error, cannot allocate color " << colorName;
      Exit(msg.str());
    }
  }

  XftColor* MastEasel::CreateColorScheme(std::string name, std::vector<std::string> colorNames){
    size_t i;
    XftColor *ret;

    if (colorNames.empty() || !(ret = (XftColor*)ECalloc(colorNames.size(),sizeof(XftColor))))
      return NULL;

    for (int i = 0; i < colorNames.size(); i++)
      CreateColor(&ret[i],colorNames.at(i));
    colorSchemes[name] = ret;
    return ret;
  }

  void MastEasel::SetCurrentColorScheme(std::string colorScheme){
    colorScheme_current = colorScheme;
    
  }

  XftColor* MastEasel::GetCurrentColors(){
    return colorSchemes[colorScheme_current];
  }

  void MastEasel::DrawRect(MastDimension dim, bool filled, bool invert){
    if(!GetCurrentColors())
      return;
    XSetForeground(display,gc,invert ? GetCurrentColors()[1].pixel : GetCurrentColors()[0].pixel);
    if (filled)
      XFillRectangle(display,drawable,gc,dim.X,dim.Y,dim.Width,dim.Height);
    else
      XDrawRectangle(display,drawable,gc,dim.X,dim.Y,dim.Width - 1,dim.Height - 1);
  }

  int MastEasel::DrawText(MastDimension dim, uint32_t lpad, std::string text, bool invert){
    char buf[1024];
    int ty;
    uint32_t ew;
    const char* newText = text.c_str();
    XftDraw* d = NULL;
    MastFont *usedfont, *curfont, *nextfont;
    size_t i, len;
    int i2;
    int utf8strlen, utf8charlen, render = dim.X || dim.Y || dim.Width || dim.Height;
    long utf8codepoint = 0;
    const char *utf8str;
    FcCharSet *fccharset;
    FcPattern *fcpattern;
    FcPattern *match;
    XftResult result;
    bool charExists = false;
    if ((render && !GetCurrentColors()) || text.empty() || fonts.empty())
      return 0;

    if (!render){
      dim.Width = ~dim.Width;
      
    } else {
      XSetForeground(display,gc,GetCurrentColors()[invert ? 0 : 1].pixel);
      XFillRectangle(display,drawable,gc,dim.X,dim.Y,dim.Width,dim.Height);
      d = XftDrawCreate(display,drawable,DefaultVisual(display, currentScreen),DefaultColormap(display,currentScreen));
      dim.X += lpad;
      dim.Width += lpad;
    }

    usedfont = *fonts.data();
    while(1){
      utf8strlen = 0;
      utf8str = text.c_str();
      nextfont = NULL;
	while(*newText){
	  utf8charlen = UTF8Decode(newText,&utf8codepoint,UTF_SIZ);
	  for (i2 = 0; i2 < fonts.size(); ++i){
	    curfont = &usedfont[i];
	    charExists = charExists || XftCharExists(display,curfont->xFont,utf8codepoint);
	    if(charExists){
	      if(curfont == usedfont){
		utf8strlen += utf8charlen;
		text += utf8charlen;
	      } else {
		nextfont = curfont;
	      }
	      break;
	
	    }
	  }
	  if (!charExists || nextfont)
	    break;
	  else
	    charExists = false;
	  
	}
      if (utf8strlen){
	usedfont->GetText(std::string(utf8str), utf8strlen, MastDimension(ew, 0));
	for (len = Min<int>(utf8strlen,sizeof(buf) - 1); len && ew > dim.Width; len--)
	  usedfont->GetText(std::string(utf8str), len, MastDimension(ew, 0));

	if(len){
	  memcpy(buf, utf8str, len);
	  buf[len] = '\0';
	  if(len < utf8strlen)
	    for(i = len; i && i > len - 3; buf[--i] = '.')
	      ;
	  if (render){
	    ty = dim.Y - (dim.Height - usedfont->HDim.Height) / 2 + (usedfont->xFont->ascent);
	    XftDrawStringUtf8(d,&GetCurrentColors()[invert ? 1 : 0],usedfont->xFont,dim.X,ty, (XftChar8*)buf,len);
	    
	  }
	  dim.X += ew;
	  dim.Width += ew;
	}
	
      }

      if(!*newText){
	break;
	
      } else if (nextfont){
	charExists = false;
	usedfont = nextfont;
	
      } else {
	charExists = true;
	fccharset = FcCharSetCreate();
	FcCharSetAddChar(fccharset,utf8codepoint);
	if(!fonts.at(0)->pattern){
	  Exit("First font must be loaded from the cache and from a font string.");
	}
	fcpattern = FcPatternDuplicate(fonts.at(0)->pattern);
	FcPatternAddCharSet(fcpattern,FC_CHARSET,fccharset);
	FcPatternAddBool(fcpattern,FC_SCALABLE,FcTrue);
	FcPatternAddBool(fcpattern,FC_COLOR,FcFalse);

	FcConfigSubstitute(NULL,fcpattern,FcMatchPattern);
	FcDefaultSubstitute(fcpattern);
	match = XftFontMatch(display,currentScreen,fcpattern,&result);
	FcCharSetDestroy(fccharset);
	FcPatternDestroy(fcpattern);
	if (match){
	  usedfont = new MastFont(match, display);
	  if (usedfont && XftCharExists(display,usedfont->xFont,utf8codepoint)){
	    for (i2 = 1; i2 < fonts.size(); ++i2){
	      if(!fonts.at(i))
		break;
	      curfont = fonts.at(i); 
	    }
	    
	  } else {
	    usedfont->Free();
	    usedfont = *fonts.data();
	  }
	}
      }
    }
    if(d)
      XftDrawDestroy(d);

    return dim.X + (render ? dim.Width : 0);
  }

  void MastEasel::DrawMap(Window win, MastDimension dim){

    XCopyArea(display,drawable,win,gc,dim.X,dim.X,dim.Width,dim.Height,dim.X,dim.Y);
    XSync(display,False);
  }


  uint32_t MastFont::GetWidth(std::string text, MastEasel* easel){
    if ( text.empty())
      return 0;
    return easel->DrawText(MastDimension(0,0,0,0),0,text,false);
  }

  void MastFont::GetText(std::string text, uint32_t length, MastDimension dim){
    XGlyphInfo ext;

    if(text.empty())
      return;

    XftTextExtentsUtf8(display,xFont,(XftChar8*)text.c_str(),length,&ext);
    if (&dim.Width)
      dim.Width = ext.xOff;
    if(&dim.Height)
      dim.Height = HDim.Height;
  }


  MastCursor::MastCursor(int shape, Display* display){
    cursor = XCreateFontCursor(display,shape);
    displayVar = display;
  };

  void MastCursor::Free(){
    XFreeCursor(displayVar,cursor);
    free(this);
  }
}
