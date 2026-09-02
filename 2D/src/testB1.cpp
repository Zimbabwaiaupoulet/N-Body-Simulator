#include "Node.hpp"
#include <iostream>
#include <vector>

int main() {
  std::vector<Corps> carre_corps(4);
  carre_corps[0].mass = 2.0;
  carre_corps[0].position = {-1.0, 1.0};
  carre_corps[1].mass = 2.0;
  carre_corps[1].position = {1.0, 1.0};
  carre_corps[2].mass = 2.0;
  carre_corps[2].position = {-1.0, -1.0};
  carre_corps[3].mass = 2.0;
  carre_corps[3].position = {1.0, -1.0};

  Node racine({0.0, 0.0}, 4.0);

  for (int i = 0; i < 4; i++) {
    racine.inserer(&carre_corps[i]);
  }

  racine.calculer_masses();

  std::cout << "Masse : " << racine.masse_totale << "\n";
  std::cout << "CM : " << racine.centre_de_masse.x << ", "
            << racine.centre_de_masse.y << "\n";

  return 0;
}