#include "../headers/Vector2D.hpp"
#include <cmath>

Vector2D add2D(Vector2D v1, Vector2D v2) {
  Vector2D nv;
  nv.x = v1.x + v2.x;
  nv.y = v1.y + v2.y;
  return nv;
};

Vector2D sub2D(Vector2D v1, Vector2D v2) {
  Vector2D nv;
  nv.x = v1.x - v2.x;
  nv.y = v1.y - v2.y;
  return nv;
};

Vector2D mult2D(Vector2D v, double factor) {
  Vector2D nv;
  nv.x = v.x * factor;
  nv.y = v.y * factor;
  return nv;
}

double norm2D(Vector2D v) { return (std::sqrt((v.x * v.x) + (v.y * v.y))); };

double scalar2D(Vector2D v1, Vector2D v2) {
  return ((v1.x * v2.y) + (v1.y * v2.x));
};