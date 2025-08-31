#include "header/Ponto.h"
#include <iostream>

Ponto::Ponto() : x(0), y(0) {
}

Ponto::Ponto(int x, int y) {
  this->x = x;
  this->y = y;
}

void Ponto::setX(int x) {
  this->x = x;
}

void Ponto::setY(int y) {
  this->y = y;
}

int Ponto::getX() {
  return x;
}

int Ponto::getY() {
  return y;
}
