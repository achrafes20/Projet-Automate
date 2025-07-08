# 🚀 Projet Automate - Théorie des Langages et Compilation

![License: MIT](https://img.shields.io/badge/License-MIT-blue)
![Status: Completed](https://img.shields.io/badge/Status-Completed-brightgreen)

Un projet complet implémentant des **automates finis déterministes (AFD)** et **non-déterministes (AFN)** avec diverses **opérations avancées** en **C**.

> ✨ Conçu avec passion pour la théorie des langages et la compilation ✨

---

## 📌 Fonctionnalités

### 🔧 Manipulation d'automates
- Lecture/écriture depuis/vers des fichiers `.dot`
- Affichage des caractéristiques de l'automate
- Opérations de base : union, concaténation, étoile de Kleene ✳️

### 🔍 Analyse
- Vérification d'appartenance d'un mot
- Test de mots depuis un fichier
- Recherche d'états avec transitions spécifiques

### 🔄 Transformations avancées
- Suppression des ε-transitions
- Déterminisation
- Minimisation (algorithme de Brzozowski)
- Intersection d'automates
- Génération à partir d'expressions régulières

---

## 🛠 Installation & Utilisation

### ✅ Prérequis
- Compilateur C (`gcc` recommandé)
- `make` (optionnel)

### 🧱 Compilation
```bash
gcc -o automate main.c
▶️ Exécution
bash
Copier
Modifier
./automate
📈 Génération de fichiers DOT (pour Graphviz)
bash
Copier
Modifier
dot -Tpng fichier.dot -o output.png
📂 Structure du Projet
bash
Copier
Modifier
automate/
├── main.c              # Code source principal
├── automate.h          # Déclarations des fonctions
├── Makefile            # Fichier de compilation (optionnel)
├── exemples/           # Automates exemples
│   ├── exemple1.dot
│   └── exemple2.dot
├── mots/               # Fichiers de mots à tester
│   └── test_mots.txt
└── LICENSE             # Licence du projet
🎯 Exemples d'Utilisation
🔹 Charger un automate
c
Copier
Modifier
Automate* monAutomate = lireAutomateDepuisDot("exemple1.dot");
🔹 Vérifier un mot
c
Copier
Modifier
if (motEstEngendre(monAutomate, "aba")) {
    printf("Le mot est accepté !\n");
}
🔹 Opérations avancées
c
Copier
Modifier
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
Les contributions sont les bienvenues !
N’hésitez pas à :

Signaler des bugs 🐞

Ajouter de nouvelles fonctionnalités 🌟

Améliorer la documentation 📝

🔧 Ouvrez une issue ou soumettez une pull request

📜 Licence
Ce projet est sous licence MIT.
Voir le fichier LICENSE pour plus d’informations.
