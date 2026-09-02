import pandas as pd
import matplotlib.pyplot as plt
import os

print("Recherche de données à tracer...")

DOSSIER_DONNEES = os.path.join(os.path.dirname(__file__), "2D", "csv")

# --- Recherche des fichiers CSV ---
fichiers_csv = []
if os.path.isdir(DOSSIER_DONNEES):
    fichiers_csv = [
        os.path.join(DOSSIER_DONNEES, nom)
        for nom in os.listdir(DOSSIER_DONNEES)
        if nom.endswith(".csv")
    ]
fichiers_trajectoire = [
    fichier for fichier in fichiers_csv
    if os.path.basename(fichier) not in ("benchmark.csv", "derive_energie.csv")
]
fichier_energie = os.path.join(DOSSIER_DONNEES, "derive_energie.csv")
fichier_benchmark = os.path.join(DOSSIER_DONNEES, "benchmark.csv")

nombre_graphiques = len(fichiers_trajectoire)
if os.path.exists(fichier_energie):
    nombre_graphiques += 1
if os.path.exists(fichier_benchmark):
    nombre_graphiques += 1

if nombre_graphiques > 0:
    nombre_colonnes = 2
    nombre_lignes = (nombre_graphiques + nombre_colonnes - 1) // nombre_colonnes
    figure, axes = plt.subplots(
        nombre_lignes,
        nombre_colonnes,
        figsize=(12, 5 * nombre_lignes),
        squeeze=False,
    )
    axes = axes.ravel()
    index_graphique = 0

    for fichier in sorted(fichiers_trajectoire):
        print(f"-> Traçage de {os.path.basename(fichier)}...")
        df_traj = pd.read_csv(fichier)
        nom_fichier = os.path.splitext(os.path.basename(fichier))[0]
        axe = axes[index_graphique]
        for i in range(0, len(df_traj.columns) - 1, 2):
            morceaux = str(df_traj.columns[i]).split('_')
            nom_astre = morceaux[1] if len(morceaux) > 1 else "corps"
            axe.plot(
                df_traj.iloc[:, i],
                df_traj.iloc[:, i + 1],
                label=nom_astre.capitalize(),
            )
        axe.set_xlim(-2.0, 2.0)
        axe.set_ylim(-2.0, 2.0)
        axe.set_title(nom_fichier)
        axe.legend()
        axe.grid(True, linestyle='--')
        index_graphique += 1

    if os.path.exists(fichier_energie):
        print("-> Traçage de derive_energie.csv...")
        axe = axes[index_graphique]
        df_ener = pd.read_csv(fichier_energie)
        axe.plot(df_ener['Temps'], df_ener['Derive_Relative'], color='orange')
        axe.set_xlabel("Temps (années)")
        axe.set_ylabel("Dérive Relative (%)")
        axe.set_title("Dérive d'énergie")
        axe.grid(True)
        index_graphique += 1

    if os.path.exists(fichier_benchmark):
        print("-> Traçage de benchmark.csv...")
        axe = axes[index_graphique]
        df_bench = pd.read_csv(fichier_benchmark)
        if 'BruteForce_ms' in df_bench.columns:
            axe.loglog(df_bench['N'], df_bench['BruteForce_ms'],
                       'r-o', label='Brute Force O(N²)')
        if 'BarnesHut_ms' in df_bench.columns:
            axe.loglog(df_bench['N'], df_bench['BarnesHut_ms'],
                       'b-s', label='Barnes-Hut O(N log N)')
        axe.set_xlabel("Nombre de corps (N)")
        axe.set_ylabel("Temps (ms)")
        axe.set_title("Performances")
        axe.legend()
        axe.grid(True, which="both", linestyle='--')

    for axe in axes[nombre_graphiques:]:
        axe.set_visible(False)

    figure.suptitle("Résultats des simulations", fontsize=16)
    figure.tight_layout()
    figure.savefig(os.path.join(DOSSIER_DONNEES, "figure_subplots.png"))
    plt.show()

print("Terminé !")