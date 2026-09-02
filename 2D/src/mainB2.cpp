#include "../headers/Node.hpp"
#include <iostream>
#include <random>
#include <vector>

int main() {
  const double PI = std::acos(-1.0);
  const double G = 4.0 * PI * PI;
  const double epsilon = 0.1;
  const int N = 200;

  std::vector<Corps> systeme(N);
  std::mt19937 gen(42);
  std::uniform_real_distribution<double> pos_dist(-10.0, 10.0);
  std::uniform_real_distribution<double> mass_dist(0.01, 1.0);

  for (int i = 0; i < N; i++) {
    systeme[i].mass = mass_dist(gen);
    systeme[i].position = {pos_dist(gen), pos_dist(gen)};
    systeme[i].speed = {0.0, 0.0};
    systeme[i].acceleration = {0.0, 0.0};
  }

  std::vector<Vector2D> acc_exacte(N, {0.0, 0.0});
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (i != j) {
        Vector2D distVect = sub2D(systeme[j].position, systeme[i].position);
        double d = norm2D(distVect);
        double gFact =
            (G * systeme[j].mass) / std::pow(d * d + epsilon * epsilon, 1.5);
        acc_exacte[i] = add2D(acc_exacte[i], mult2D(distVect, gFact));
      }
    }
  }

  Node racine({0.0, 0.0}, 20.0);
  for (int i = 0; i < N; i++) {
    racine.inserer(&systeme[i]);
  }
  racine.calculer_masses();

  std::vector<double> valeurs_theta = {0.0, 0.5, 0.80, 1.0, 2.0};

  std::cout << "Theta | Erreur Relative Moyenne (%)\n";
  std::cout << "-----------------------------------\n";

  for (double theta : valeurs_theta) {
    double somme_erreur_relative = 0.0;

    for (int i = 0; i < N; i++) {
      Vector2D acc_bh =
          racine.calculer_acceleration(&systeme[i], theta, G, epsilon);

      Vector2D diff = sub2D(acc_bh, acc_exacte[i]);
      double norme_diff = norm2D(diff);
      double norme_exacte = norm2D(acc_exacte[i]);

      if (norme_exacte > 0.0) {
        somme_erreur_relative += (norme_diff / norme_exacte);
      }
    }

    double erreur_moyenne_pct = (somme_erreur_relative / N) * 100.0;
    std::cout << theta << "   | " << erreur_moyenne_pct << " %\n";
  }

  return 0;
}