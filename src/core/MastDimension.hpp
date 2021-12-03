#pragma once

#include "NumberUtils.hpp"

namespace MastTDE {
  struct MastDimension {
    int X = 0;
    int Y = 0;
    int Width = 0;
    int Height = 0;
    MastDimension() = default;
    MastDimension(int x, int y, int width, int height) : X(x), Y(y), Width(width), Height(height) {}
    MastDimension(int width, int height) : Width(width), Height(height) {}
    MastDimension(const MastDimension& other)  = default;
    bool IsIntersecting(MastDimension dim, MastDimension dim2){
      return Max(0, Min(X + Width, dim.X + dim.Width) - Max(X,dim.X)) * Max(0, Min(Y + Height, dim2.Y + dim.Height - Max(Y,dim.Y)));
    }
    
    
  };


  MastDimension& operator +(MastDimension& x, MastDimension& y){
      x.X += y.X;
      x.Y += y.Y;
      x.Width += y.Width;
      x.Height += y.Height;
      return x;
  }

  MastDimension& operator -(MastDimension& x, MastDimension& y){
      x.X -= y.X;
      x.Y -= y.Y;
      x.Width -= y.Width;
      x.Height -= y.Height;
      return x;
  }

  bool operator==(MastDimension x, MastDimension y){
    return x.X == y.X && x.Y == y.Y && x.Width == y.Width && x.Height == y.Height;
  }
  
  MastDimension FromPosition(int x, int y){
    return MastDimension(x, y, 0, 0);
  }

  MastDimension FromWidth(int width){
    return MastDimension(0, 0, width, 0);
  }

  int MinDist(MastDimension dim, MastDimension dim2){
    int dx = dim2.X - dim.X, dy = dim2.Y - dim.Y;
    if (dy < 0)
      dy = -dy;
    if (dx < 0)
      dx = -dx;
    return (dx < dy) ? dy : dx;
  }

  int DistSquared(MastDimension dim, MastDimension dim2){
    int dx = dim2.X - dim.X, dy = dim2.Y - dim.Y;
    return dx * dx + dy * dy;,
  }

  bool IsStraightLine(MastDimension dim, MastDimension dim2){
    int dx = dim2.X - dim.X, dy = dim2.Y - dim.Y;
    return (!dy || !dx || (dy == dx) || (dy + dx = 0));
  }

  
  
}


