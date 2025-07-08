🚀 Automate - Théorie des Langages et Compilation



Un projet complet en C pour manipuler des automates finis déterministes (AFD) et non-déterministes (AFN), avec des fonctionnalités avancées de transformation, d’analyse et de visualisation.

✨ Conçu avec passion pour la théorie des langages et la compilation ✨

📌 Fonctionnalités principales
🔧 Manipulation d'automates
📥 Lecture / écriture d'automates depuis/vers des fichiers .dot

👀 Affichage des caractéristiques : états, transitions, alphabet, etc.

➕ Opérations sur les automates :

Union

Concaténation

Étoile de Kleene ✳️

🔍 Analyse de mots
✅ Vérification d'appartenance d'un mot

📂 Test de mots depuis un fichier

🔎 Recherche d’états avec certaines transitions

🔄 Transformations avancées
❌ Suppression des ε-transitions

🔁 Déterminisation (AFN → AFD)

🧹 Minimisation (algorithme de Brzozowski)

⚔️ Intersection entre automates

🧪 Génération d’automates à partir d'expressions régulières

⚙️ Installation & Utilisation
🧱 Prérequis
Compilateur C (gcc recommandé)

make (optionnel)

🏗️ Compilation
bash
Copier
Modifier
gcc -o automate main.c
▶️ Exécution
bash
Copier
Modifier
./automate
📈 Visualisation avec Graphviz
Générez une image à partir d’un fichier .dot :

bash
Copier
Modifier
dot -Tpng fichier.dot -o output.png
📂 Arborescence du projet
bash
Copier
Modifier
automate/
├── main.c              # Code source principal
├── automate.h          # Déclarations des fonctions
├── Makefile            # Compilation simplifiée (optionnel)
├── exemples/           # Automates d'exemples (.dot)
│   ├── exemple1.dot
│   └── exemple2.dot
├── mots/               # Mots à tester
│   └── test_mots.txt
└── LICENSE             # Licence du projet
🎯 Exemples d'utilisation
📥 Charger un automate
c
Copier
Modifier
Automate* monAutomate = lireAutomateDepuisDot("exemple1.dot");
✅ Vérifier un mot
c
Copier
Modifier
if (motEstEngendre(monAutomate, "aba")) {
    printf("Le mot est accepté !\n");
}
🧹 Minimisation & export
c
Copier
Modifier
Automate* minimal = minimisationBrzozowski(monAutomate);
genererFichierDot(minimal, "automate_minimal.dot");
📚 Concepts théoriques couverts
Automates Finis Non-Déterministes (AFN)

Automates Finis Déterministes (AFD)

ε-fermeture & construction de sous-ensembles

Algorithme de Brzozowski (minimisation)

Opérations sur les langages réguliers

🤝 Contributions bienvenues !
Tu veux améliorer ce projet ? Tu es le·la bienvenu·e !
N’hésite pas à :

🐛 Signaler des bugs

🌟 Proposer de nouvelles fonctionnalités

📖 Améliorer la documentation

📬 Ouvre une issue ou envoie une pull request !

📜 Licence
Ce projet est sous licence MIT — consulte LICENSE pour les détails.

❤️ Remerciements
Ce projet a été réalisé dans le cadre du module Théorie des Langages et Compilation

Merci aux enseignants et camarades pour leur soutien et retours constructifs.
