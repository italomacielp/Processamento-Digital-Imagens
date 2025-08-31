#ifndef PONTO_H
#define PONTO_H

#include <string>

class Ponto {
private:
  int x;
  int y;

public:
  Ponto();
  Ponto(int x, int y);
  void setX(int x);
  void setY(int y);
  int getX();
  int getY(); 

};

#endif
