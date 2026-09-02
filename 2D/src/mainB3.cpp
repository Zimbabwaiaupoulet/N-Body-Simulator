#include "../headers/Node.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

int main() {
  const double G = 4.0 * std::acos(-1.0) * std::acos(-1.0);
  const double epsilon = 0.1;
  const double theta = 0.5;

  std::vector<int> valeurs_N = {100,  500,   1000,  3000,
                                5000, 10000, 15000, 30000};
  const int repetitions = 5;

  std::ofstream fichier_sortie("csv/benchmark.csv");
  if (!fichier_sortie.is_open()) {
    std::cerr << "Erreur : Impossible de creer csv/benchmark.csv\n";
    return 1;
  }

  fichier_sortie << "N,BruteForce_ms,BarnesHut_ms\n";

  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist_pos(-10.0, 10.0);
  std::uniform_real_distribution<double> dist_masse(0.001, 1.0);

  for (int N : valeurs_N) {
    std::vector<Corps> systeme(N);
    for (int i = 0; i < N; i++) {
      systeme[i].mass = dist_masse(gen);
      systeme[i].position = {dist_pos(gen), dist_pos(gen)};
      systeme[i].speed = {0.0, 0.0};
      systeme[i].acceleration = {0.0, 0.0};
    }

    std::vector<double> temps_bf;
    std::vector<double> temps_bh;

    for (int r = 0; r < repetitions; r++) {

      if (N <= 15000) {
        auto debut_bf = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < N; i++) {
          for (int j = 0; j < N; j++) {
            if (i != j) {
              Vector2D distVect =
                  sub2D(systeme[j].position, systeme[i].position);
              double d = norm2D(distVect);
              double gFact = (G * systeme[j].mass) /
                             std::pow(d * d + epsilon * epsilon, 1.5);
              Vector2D acc = mult2D(distVect, gFact);
            }
          }
        }
        auto fin_bf = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duree_bf = fin_bf - debut_bf;
        temps_bf.push_back(duree_bf.count());
      }

      auto debut_bh = std::chrono::high_resolution_clock::now();
      Node racine({0.0, 0.0}, 20.0);
      for (int i = 0; i < N; i++) {
        racine.inserer(&systeme[i]);
      }
      racine.calculer_masses();
      for (int i = 0; i < N; i++) {
        Vector2D acc =
            racine.calculer_acceleration(&systeme[i], theta, G, epsilon);
      }
      auto fin_bh = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double, std::milli> duree_bh = fin_bh - debut_bh;
      temps_bh.push_back(duree_bh.count());
    }

    double mediane_bf = 0.0;
    if (N <= 15000) {
      std::sort(temps_bf.begin(), temps_bf.end());
      mediane_bf = temps_bf[repetitions / 2];
    }

    std::sort(temps_bh.begin(), temps_bh.end());
    double mediane_bh = temps_bh[repetitions / 2];

    fichier_sortie << N << "," << mediane_bf << "," << mediane_bh << "\n";
  }

  fichier_sortie.close();
  std::cout << "Benchmark termine. Les donnees sont dans csv/benchmark.csv\n";

  return 0;
}