// A3 //

#include "../headers/Corps.hpp"
#include "../headers/Vector2D.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

double calculer_moment_cinetique(const std::vector<Corps> &systeme) {
  double Lz = 0.0;
  for (const auto &corps : systeme) {
    Lz = Lz + corps.mass * (corps.position.x * corps.speed.y -
                            corps.position.y * corps.speed.x);
  }
  return Lz;
}

int main() {
  const double PI = std::acos(-1.0);
  const double G = 4.0 * PI * PI;
  const double epsilon = 0.0;
  const double dt = 0.001;

  std::vector<Corps> systeme;

  Corps soleil;
  soleil.mass = 1.0;
  soleil.position = {0.0, 0.0};
  soleil.speed = {0.0, 0.0};
  systeme.push_back(soleil);

  Corps mercure;
  mercure.mass = 1.660e-7;
  mercure.position = {0.387, 0.0};
  mercure.speed = {0.0, std::sqrt(G * soleil.mass / 0.387)};
  systeme.push_back(mercure);

  Corps venus;
  venus.mass = 2.447e-6;
  venus.position = {0.723, 0.0};
  venus.speed = {0.0, std::sqrt(G * soleil.mass / 0.723)};
  systeme.push_back(venus);

  Corps terre;
  terre.mass = 3.003e-6;
  terre.position = {1.0, 0.0};
  terre.speed = {0.0, std::sqrt(G * soleil.mass / 1.0)};
  systeme.push_back(terre);

  Corps mars;
  mars.mass = 3.213e-7;
  mars.position = {1.524, 0.0};
  mars.speed = {0.0, std::sqrt(G * soleil.mass / 1.524)};
  systeme.push_back(mars);

  std::cout << "Lancement de la simulation A3 (Systeme Solaire)..."
            << std::endl;

  std::ofstream fichier_sortie("csv/trajectoire_A3.csv");
  if (!fichier_sortie.is_open()) {
    std::cout << "Erreur : Impossible de creer le fichier CSV !" << std::endl;
    return 1;
  }
  fichier_sortie
      << "x_sol,y_sol,x_mer,y_mer,x_ven,y_ven,x_ter,y_ter,x_mar,y_mar\n";

  for (size_t i = 0; i < systeme.size(); i++) {
    for (size_t j = 0; j < systeme.size(); j++) {
      if (i != j) {
        Vector2D distVect = sub2D(systeme[j].position, systeme[i].position);
        double d = norm2D(distVect);
        double gFact =
            (G * systeme[j].mass) / pow(d * d + epsilon * epsilon, 1.5);
        systeme[i].acceleration =
            add2D(systeme[i].acceleration, mult2D(distVect, gFact));
      }
    }
  }

  double Lz_initial = calculer_moment_cinetique(systeme);
  std::cout << "Lz initial : " << Lz_initial << "\n";

  std::vector<double> temps_ecoule(systeme.size(), 0.0);
  std::vector<int> tours(systeme.size(), 1);
  std::vector<double> y_precedent(systeme.size(), 0.0);

  for (int etape = 0; etape < 5000; etape++) {

    for (size_t k = 1; k < systeme.size(); k++) {
      y_precedent[k] = systeme[k].position.y;
    }

    for (size_t i = 0; i < systeme.size(); i++) {
      fichier_sortie << systeme[i].position.x << "," << systeme[i].position.y;
      if (i < systeme.size() - 1)
        fichier_sortie << ",";
    }
    fichier_sortie << "\n";

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

    for (size_t k = 1; k < systeme.size(); k++) {
      temps_ecoule[k] += dt;
      if (y_precedent[k] < 0.0 && systeme[k].position.y >= 0.0 &&
          systeme[k].position.x > 0.0) {
        std::cout << "Planete " << k << " - Orbite " << tours[k]
                  << " terminee ! Periode : " << temps_ecoule[k] << " ans.\n";
        temps_ecoule[k] = 0.0;
        tours[k]++;
      }
    }
  }

  double Lz_final = calculer_moment_cinetique(systeme);
  double variation_Lz =
      std::abs(Lz_final - Lz_initial) / std::abs(Lz_initial) * 100.0;

  std::cout << "\nLz final : " << Lz_final << "\n";
  std::cout << "Variation du Lz : " << variation_Lz << " %\n";

  fichier_sortie.close();
  std::cout
      << "Simulation terminee. Trace le fichier CSV pour voir les orbites !\n";

  return 0;
}