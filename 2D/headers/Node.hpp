#pragma once
#include "Corps.hpp"
#include "Vector2D.hpp"
#include <cmath>
#include <memory>
#include <vector>

class Node {
public:
  Vector2D centre;
  double taille;
  double masse_totale;
  Vector2D centre_de_masse;
  bool est_feuille;
  const Corps *corps_unique;
  std::unique_ptr<Node> enfants[4];

  Node(Vector2D c, double t)
      : centre(c), taille(t), masse_totale(0.0), centre_de_masse({0.0, 0.0}),
        est_feuille(true), corps_unique(nullptr) {}

  int obtenir_quadrant(Vector2D pos) {
    if (pos.x <= centre.x && pos.y >= centre.y)
      return 0;
    if (pos.x > centre.x && pos.y >= centre.y)
      return 1;
    if (pos.x <= centre.x && pos.y < centre.y)
      return 2;
    return 3;
  }

  void subdiviser() {
    double quart = taille / 4.0;
    enfants[0] = std::make_unique<Node>(
        Vector2D{centre.x - quart, centre.y + quart}, taille / 2.0);
    enfants[1] = std::make_unique<Node>(
        Vector2D{centre.x + quart, centre.y + quart}, taille / 2.0);
    enfants[2] = std::make_unique<Node>(
        Vector2D{centre.x - quart, centre.y - quart}, taille / 2.0);
    enfants[3] = std::make_unique<Node>(
        Vector2D{centre.x + quart, centre.y - quart}, taille / 2.0);
  }

  void inserer(const Corps *corps, int profondeur = 0) {
    if (profondeur > 50)
      return;

    if (est_feuille && corps_unique == nullptr) {
      corps_unique = corps;
      return;
    }

    if (est_feuille && corps_unique != nullptr) {
      subdiviser();
      est_feuille = false;
      int quadrant_ancien = obtenir_quadrant(corps_unique->position);
      enfants[quadrant_ancien]->inserer(corps_unique, profondeur + 1);
      corps_unique = nullptr;
    }

    int quadrant_nouveau = obtenir_quadrant(corps->position);
    enfants[quadrant_nouveau]->inserer(corps, profondeur + 1);
  }

  void calculer_masses() {
    if (est_feuille) {
      if (corps_unique != nullptr) {
        masse_totale = corps_unique->mass;
        centre_de_masse = corps_unique->position;
      } else {
        masse_totale = 0.0;
        centre_de_masse = {0.0, 0.0};
      }
    } else {
      masse_totale = 0.0;
      Vector2D somme_cm = {0.0, 0.0};

      for (int i = 0; i < 4; i++) {
        enfants[i]->calculer_masses();
        if (enfants[i]->masse_totale > 0) {
          masse_totale += enfants[i]->masse_totale;
          somme_cm.x +=
              enfants[i]->masse_totale * enfants[i]->centre_de_masse.x;
          somme_cm.y +=
              enfants[i]->masse_totale * enfants[i]->centre_de_masse.y;
        }
      }

      if (masse_totale > 0) {
        centre_de_masse.x = somme_cm.x / masse_totale;
        centre_de_masse.y = somme_cm.y / masse_totale;
      }
    }
  }

  Vector2D calculer_acceleration(const Corps *cible, double theta, double G,
                                 double epsilon) {
    Vector2D acc = {0.0, 0.0};
    if (masse_totale == 0.0)
      return acc;

    Vector2D distVect = sub2D(centre_de_masse, cible->position);
    double d = norm2D(distVect);

    if (d == 0.0)
      return acc;

    if (est_feuille || (taille / d < theta)) {
      double gFact =
          (G * masse_totale) / std::pow(d * d + epsilon * epsilon, 1.5);
      acc = mult2D(distVect, gFact);
    } else {
      for (int i = 0; i < 4; i++) {
        if (enfants[i]) {
          acc = add2D(
              acc, enfants[i]->calculer_acceleration(cible, theta, G, epsilon));
        }
      }
    }
    return acc;
  }
};