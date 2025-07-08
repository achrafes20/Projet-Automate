Projet Automate - Théorie des Langages et Compilation
https://img.shields.io/badge/License-MIT-blue
https://img.shields.io/badge/Status-Completed-brightgreen

Un projet complet implémentant des automates finis déterministes et non-déterministes avec diverses opérations avancées en C.

📌 Fonctionnalités
Manipulation d'automates:

Lecture/écriture depuis/vers des fichiers .dot

Affichage des caractéristiques de l'automate

Opérations de base (union, concaténation, étoile de Kleene)

Analyse:

Vérification d'appartenance d'un mot

Test de mots depuis un fichier

Recherche d'états avec transitions spécifiques

Transformations avancées:

Suppression des ε-transitions

Déterminisation

Minimisation (algorithme de Brzozowski)

Intersection d'automates

Génération depuis expressions régulières

🛠 Installation & Utilisation
Prérequis:

Compilateur C (gcc recommandé)

Make (optionnel)

Compilation:

bash
gcc -o automate main.c
Exécution:

bash
./automate
Génération de fichiers DOT:

Le programme peut générer des fichiers .dot visualisables avec Graphviz:

bash
dot -Tpng fichier.dot -o output.png
📂 Structure du Projet
text
automate/
├── main.c                # Code source principal
├── automate.h            # Déclarations des fonctions
├── Makefile              # Fichier de compilation (optionnel)
├── exemples/             # Dossier contenant des automates exemples
│   ├── exemple1.dot
│   └── exemple2.dot
└── mots/                 # Dossier pour les fichiers de mots à tester
    └── test_mots.txt
🎯 Exemples d'Utilisation
Charger un automate:

c
Automate* monAutomate = lireAutomateDepuisDot("exemple1.dot");
Vérifier un mot:

c
if (motEstEngendre(monAutomate, "aba")) {
    printf("Le mot est accepté !\n");
}
Opérations avancées:

c
Automate* minimal = minimisationBrzozowski(monAutomate);
genererFichierDot(minimal, "automate_minimal.dot");
📚 Théorie Implémentée
Automates finis non-déterministes (AFN)

Automates finis déterministes (AFD)

ε-fermeture

Construction de sous-ensembles

Algorithme de minimisation de Brzozowski

Opérations sur les langages réguliers

🤝 Contribution
Les contributions sont les bienvenues ! Ouvrez une issue ou soumettez une pull request pour :

Corriger des bugs

Ajouter de nouvelles fonctionnalités

Améliorer la documentation

📜 Licence
Ce projet est sous licence MIT - voir le fichier LICENSE pour plus de détails.

✨ Fait avec passion pour la théorie des langages et la compilation ✨
