#include "Vector2D.hpp"
#include <iostream>

using namespace std;

int main() {
  Vector2D va;
  va.x = 3;
  va.y = 4;

  Vector2D vb;
  vb.x = 8;
  vb.y = 1;

  Vector2D vc = add2D(va, vb);
  Vector2D vd = sub2D(va, vb);
  double rnorm = norm2D(va);
  double rprod = scalar2D(va, vb);

  cout << "Somme : \n x : " << vc.x << " | y : " << vc.y << "\n";
  cout << "Soustraction : \n x : " << vd.x << " | y : " << vd.y << "\n";
  cout << "Norme : " << rnorm << "\n";
  cout << "Produit scalaire : " << rprod << "\n";
  return 0;
}