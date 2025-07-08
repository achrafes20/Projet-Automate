# 🚀 Projet Automate - Théorie des Langages et Compilation

![License: MIT](https://img.shields.io/badge/License-MIT-blue)
![Status: Completed](https://img.shields.io/badge/Status-Completed-brightgreen)

Un projet complet implémentant des **automates finis déterministes (AFD)** et **non-déterministes (AFN)** avec diverses **opérations avancées** en **C**.

> ✨ Conçu avec passion pour la théorie des langages et la compilation ✨

---

## 📌 Fonctionnalités

### 🔧 Manipulation d'automates
- 📥 Lecture/écriture depuis/vers des fichiers `.dot`
- 👀 Affichage des caractéristiques de l'automate
- ➕ Opérations de base :
  - Union  
  - Concaténation  
  - Étoile de Kleene ✳️

### 🔍 Analyse
- ✅ Vérification d'appartenance d'un mot
- 📂 Test de mots depuis un fichier
- 🔎 Recherche d'états avec transitions spécifiques

### 🔄 Transformations avancées
- ❌ Suppression des ε-transitions
- 🔁 Déterminisation (AFN → AFD)
- 🧹 Minimisation (algorithme de Brzozowski)
- ⚔️ Intersection entre automates
- 🧪 Génération depuis des expressions régulières

---

## 🛠 Installation & Utilisation

### ✅ Prérequis
- Compilateur C (`gcc` recommandé)
- `make` (optionnel)

### 🧱 Compilation
```bash
gcc -o automate main.c
````
### ▶️ Exécution
```bash
./automate
````


