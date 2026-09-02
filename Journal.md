# Journal de développement

## Projet N-Body Simulator

Ce journal retrace les principales étapes de réalisation du simulateur de dynamique
gravitationnelle à plusieurs corps en 2D.

## Juillet 2026

### 02/07/2026 — Découverte du projet

Réception du sujet par mail, téléchargement des fichiers et première lecture de la
documentation. Cette première étape m’a permis de commencer à comprendre le problème
des N corps, les objectifs du projet et les différentes parties à réaliser.

J’ai ensuite approfondi mes recherches afin de déterminer comment organiser le projet
et comment mettre en place les calculs nécessaires à la simulation, notamment pour les
positions, les vitesses et les forces gravitationnelles.

### Fin juillet — Une pause avant le développement

Le développement n’a pas encore commencé à cette période. J’étais en période
d’examens à l’étranger et je préparais également mon départ vers un autre pays. Le
temps disponible pour travailler sur le projet était donc très limité.

## Août 2026

### 01/08/2026 — Premières lignes de code

Début concret de l’implémentation avec la partie **A1**. J’ai commencé par créer et
tester les vecteurs 2D, qui servent de base à l’ensemble des calculs du simulateur.
Les premières opérations développées sont l’addition, la soustraction, la
multiplication par un scalaire et le calcul de la norme.

Une fois ces calculs vérifiés, j’ai pu commencer à représenter les corps et à utiliser
leurs positions, vitesses et accélérations dans une simulation simple à deux corps.
Cette première version repose sur une intégration d’Euler et permet d’observer une
première trajectoire orbitale.

### À partir du 01/08/2026 — Travail en horaires réduits

À partir de cette date, j’ai travaillé principalement le soir, en raison de journées
déjà très chargées. Malgré ce temps de travail limité, le développement a progressé
par étapes : d’abord les outils mathématiques, puis la simulation, les tests et enfin
les méthodes d’optimisation.

### 03/08/2026 — Avancement des parties A2, A3 et B

Le travail s’est poursuivi sur les parties **A2** et **A3**. L’intégration Leapfrog a
été ajoutée pour améliorer la stabilité numérique de la simulation et mieux conserver
l’énergie du système. La simulation a ensuite été étendue à un système de plusieurs
corps afin de représenter plusieurs trajectoires planétaires.

Les parties **B1**, **B2** et **B3** ont également été abordées :

- mise en place de la méthode de calcul directe, dont le coût augmente en $O(N^2)$ ;
- ajout de la structure d’arbre nécessaire à l’algorithme de Barnes-Hut ;
- étude de l’influence du paramètre $\theta$ sur la précision des résultats ;
- comparaison des temps d’exécution entre la méthode brute et Barnes-Hut.

La partie **B3** a été réalisée avec davantage d’aide d’outils d’intelligence
artificielle, car la date limite approchait. Le code a néanmoins été intégré au projet
et les résultats ont été comparés à l’aide de fichiers CSV et de graphiques.

### 23/08/2026 — Bilan de l’avancement

À cette date, les principales fonctionnalités du simulateur sont en place : calculs
vectoriels 2D, simulation à deux corps, intégration Euler et Leapfrog, système à
plusieurs corps, méthode brute et algorithme de Barnes-Hut.

Les tests et les benchmarks permettent de vérifier le comportement du programme et de
comparer la précision ainsi que les performances des différentes approches. Les
résultats sont exportés au format CSV afin de pouvoir être visualisés et analysés.

### 25/08/2026 | 26/08/2026 — Dates des soutenances
