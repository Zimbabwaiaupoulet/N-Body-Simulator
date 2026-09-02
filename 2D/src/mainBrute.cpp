#include "../headers/Corps.hpp"
#include "../headers/Vector2D.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

int main() {
  const double G = 4.0 * 3.1415926535 * 3.1415926535;
  const double epsilon = 0.1;

  std::vector<int> valeurs_N = {100, 300, 1000, 3000, 10000};
  const int repetitions = 5;

  std::cout << "N,Temps_Median_ms\n";

  std::mt19937 generateur(42);
  std::uniform_real_distribution<double> dist_pos(-10.0, 10.0);
  std::uniform_real_distribution<double> dist_masse(0.001, 1.0);

  for (int N : valeurs_N) {
    std::vector<Corps> systeme(N);
    for (int i = 0; i < N; i++) {
      systeme[i].mass = dist_masse(generateur);
      systeme[i].position = {dist_pos(generateur), dist_pos(generateur)};
      systeme[i].speed = {0.0, 0.0};
      systeme[i].acceleration = {0.0, 0.0};
    }

    std::vector<double> temps_mesures;

    for (int r = 0; r < repetitions; r++) {

      auto debut = std::chrono::high_resolution_clock::now();

      for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
          if (i != j) {
            Vector2D distVect = sub2D(systeme[j].position, systeme[i].position);
            double d = norm2D(distVect);
            double gFact = (G * systeme[j].mass) /
                           std::pow(d * d + epsilon * epsilon, 1.5);
            systeme[i].acceleration =
                add2D(systeme[i].acceleration, mult2D(distVect, gFact));
          }
        }
      }

      auto fin = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double, std::milli> duree = fin - debut;

      temps_mesures.push_back(duree.count());
    }

    std::sort(temps_mesures.begin(), temps_mesures.end());
    double mediane = temps_mesures[repetitions / 2];

    std::cout << N << "," << mediane << "\n";
  }

  return 0;
}