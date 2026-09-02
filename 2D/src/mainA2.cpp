#include "../headers/Corps.hpp"
#include "../headers/Vector2D.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

/// seed= 2250969900  e_perso= 0.2  theta_perso= 0.8

int main() {
  const double PI = std::acos(-1.0);
  const double G = 4.0 * PI * PI;
  const double epsilon = 0.1;
  const double dt = 0.01;

  const double e_perso = 0.2;
  const double a = 1.0;

  double temps_simule = 0.0;
  int tour = 1;

  std::vector<Corps> systeme;

  Corps soleil;
  soleil.mass = 1.0;
  soleil.position.x = 0.0;
  soleil.position.y = 0.0;
  soleil.speed.x = 0.0;
  soleil.speed.y = 0.0;
  soleil.acceleration.x = 0.0;
  soleil.acceleration.y = 0.0;
  systeme.push_back(soleil);

  Corps terre;
  terre.mass = 0.000003;
  terre.position.x = a * (1.0 - e_perso);
  terre.position.y = 0.0;
  terre.speed.x = 0.0;
  terre.speed.y =
      std::sqrt(G * soleil.mass * (1.0 + e_perso) / (a * (1.0 - e_perso)));
  terre.acceleration.x = 0.0;
  terre.acceleration.y = 0.0;
  systeme.push_back(terre);

  std::cout << "Lancement de la simulation A2 (Leapfrog, e=" << e_perso
            << ")..." << std::endl;

  std::ofstream fichier_sortie("csv/trajectoire_A2.csv");
  if (!fichier_sortie.is_open()) {
    std::cout << "Erreur : Impossible de creer le fichier CSV !" << std::endl;
    return 1;
  }
  fichier_sortie << "x_soleil,y_soleil,x_terre,y_terre\n";

  for (size_t i = 0; i < systeme.size(); i++) {
    for (size_t j = 0; j < systeme.size(); j++) {
      if (i != j) {
        Vector2D distVect = sub2D(systeme[j].position, systeme[i].position);
        double d = norm2D(distVect);
        double gFact =
            (G * systeme[j].mass) / std::pow(d * d + epsilon * epsilon, 1.5);
        systeme[i].acceleration =
            add2D(systeme[i].acceleration, mult2D(distVect, gFact));
      }
    }
  }

  for (int etape = 0; etape < 5000; etape++) {

    double y_terre_precedent = systeme[1].position.y;

    fichier_sortie << systeme[0].position.x << "," << systeme[0].position.y
                   << "," << systeme[1].position.x << ","
                   << systeme[1].position.y << "\n";

    for (size_t i = 0; i < systeme.size(); i++) {
      systeme[i].speed =
          add2D(systeme[i].speed, mult2D(systeme[i].acceleration, dt / 2.0));
    }

    for (size_t i = 0; i < systeme.size(); i++) {
      systeme[i].position =
          add2D(systeme[i].position, mult2D(systeme[i].speed, dt));
    }

    for (size_t i = 0; i < systeme.size(); i++) {
      systeme[i].acceleration = {0.0, 0.0};
    }
    for (size_t i = 0; i < systeme.size(); i++) {
      for (size_t j = 0; j < systeme.size(); j++) {
        if (i != j) {
          Vector2D distVect = sub2D(systeme[j].position, systeme[i].position);
          double d = norm2D(distVect);
          double gFact =
              (G * systeme[j].mass) / std::pow(d * d + epsilon * epsilon, 1.5);
          systeme[i].acceleration =
              add2D(systeme[i].acceleration, mult2D(distVect, gFact));
        }
      }
    }

    for (size_t i = 0; i < systeme.size(); i++) {
      systeme[i].speed =
          add2D(systeme[i].speed, mult2D(systeme[i].acceleration, dt / 2.0));
    }

    temps_simule = temps_simule + dt;

    if (y_terre_precedent < 0.0 && systeme[1].position.y >= 0.0 &&
        systeme[1].position.x > 0.0) {
      std::cout << "Orbite " << tour
                << " terminee ! Periode mesuree : " << temps_simule
                << " annees." << std::endl;
      temps_simule = 0.0;
      tour++;
    }
  }

  fichier_sortie.close();
  std::cout << "Simulation terminee. Trace le fichier CSV pour voir l'orbite "
               "elliptique !\n";

  return 0;
}