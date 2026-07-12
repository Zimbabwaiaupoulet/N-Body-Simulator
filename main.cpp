#include "Corps.hpp"
#include "Vector2D.hpp"

#include <cmath>
#include <fstream>
#include <iostream>

int main() {
  const double PI = acos(-1.0);

  const double G = 4.0 * PI * PI;
  const double epsilon = 0.1;
  const double dt = 0.001;

  Corps soleil;
  Corps terre;

  soleil.position.x = 0;
  soleil.position.y = 0;
  soleil.speed.x = 0;
  soleil.speed.y = 0;
  soleil.mass = 1;
  terre.position.x = 1;
  terre.position.y = 0;
  terre.speed.x = 0;
  terre.speed.y = sqrt(G);
  terre.mass = 0.000003;

  std::ofstream fichier_sortie("trajectoire.csv");

  if (!fichier_sortie.is_open()) {
    std::cout << "Erreur : Impossible de creer le fichier CSV !" << std::endl;
    return 1;
  }

  fichier_sortie << "x,y\n";

  for (int i = 0; i < 1000; i++) {
    fichier_sortie << terre.position.x << "," << terre.position.y << "\n";

    Vector2D distVect = sub2D(soleil.position, terre.position);
    double d = norm2D(distVect);
    double gFact = (G * soleil.mass) / pow(d * d + epsilon * epsilon, 1.5);
    Vector2D accel = mult2D(distVect, gFact);

    terre.speed = add2D(terre.speed, mult2D(accel, dt));
    terre.position = add2D(terre.position, mult2D(terre.speed, dt));
  }

  fichier_sortie.close();

  std::cout << "Simulation terminee. Les donnees sont dans trajectoire.csv\n";
}