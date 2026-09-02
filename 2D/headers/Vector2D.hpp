#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include <cmath>

// Structure de vecteur 2D (x,y)
struct Vector2D {
  double x;
  double y;
};

// Addition de Vecteurs : x = x1 + x2 ; y = y1 + y2
Vector2D add2D(Vector2D v1, Vector2D v2);

// soustraction de Vecteurs : x = x1 - x2 ; y = y1 + y2
Vector2D sub2D(Vector2D v1, Vector2D v2);

// Multiplication d'un vecteur par un facteur.
Vector2D mult2D(Vector2D v, double factor);

// Norme d'un vecteur : Racince(x²+y²)
double norm2D(Vector2D v);
// Produit scalaire de deux vecteurs (x1*y2 + x2*y1)
double scalar2D(Vector2D v1, Vector2D v2);

#endif