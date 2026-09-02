// A1 //

#include "../headers/Corps.hpp"
#include "../headers/Vector2D.hpp"

#include <cmath>
#include <fstream>
#include <iostream>

/// seed= 2250969900  e_perso= 0.2  theta_perso= 0.8

int main() {
  const double PI = std::acos(-1.0);

  const double G = 4.0 * PI * PI;
  const double epsilon = 0.1;
  const double dt = 0.001;

  double temps_simule = 0.0;
  int tour = 1;

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
  terre.speed.y = std::sqrt(G);
  terre.mass = 0.000003;

  std::cout << "Vitesse initiale calculee : " << terre.speed.y << " UA/an"
            << std::endl;

  std::ofstream fichier_sortie("csv/trajectoire_A1.csv");

  if (!fichier_sortie.is_open()) {
    std::cout << "Erreur : Impossible de creer le fichier CSV !" << std::endl;
    return 1;
  }

  fichier_sortie << "x,y\n";

  for (int i = 0; i < 2000; i++) {

    double y_precedent = terre.position.y;
    fichier_sortie << terre.position.x << "," << terre.position.y << "\n";

    Vector2D distVect = sub2D(soleil.position, terre.position);
    double d = norm2D(distVect);
    double gFact = (G * soleil.mass) / std::pow(d * d + epsilon * epsilon, 1.5);
    Vector2D accel = mult2D(distVect, gFact);

    terre.speed = add2D(terre.speed, mult2D(accel, dt));
    terre.position = add2D(terre.position, mult2D(terre.speed, dt));

    temps_simule = temps_simule + dt;

    if (y_precedent < 0.0 && terre.position.y >= 0.0 &&
        terre.position.x > 0.0) {
      std::cout << "Orbite " << tour << " terminee !" << std::endl;
      std::cout << "Periode mesuree : " << temps_simule << " annees."
                << std::endl;

      temps_simule = 0.0;
      tour++;
    }
  }

  fichier_sortie.close();
  std::cout
      << "Simulation terminee. Les donnees sont dans csv/trajectoire_A1.csv\n";

  return 0;
}