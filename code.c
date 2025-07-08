#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_STATES 100 

typedef struct Transition {
    char etat_depart[10];
    char symbole;
    char etat_arrivee[10];
    struct Transition *suivant;
} Transition;

typedef struct Etat {
    char nom[10];
    struct Etat *suivant;
} Etat;

typedef struct {
    Etat *etats;
    char alphabet[10];
    Transition *transitions;
    Etat *etat_initial;
    Etat *etats_finaux;
} Automate;

Automate* CreerAutomate();
Etat* creerEtat(const char* nom);
Transition* creerTransition(const char* depart, char symbole, const char* arrivee);

bool estAutomateVide(Automate* automate);
bool estDansEnsemble(Etat* ensemble, const char* etat);
void ajouterEtatAEnsemble(Etat** ensemble, const char* etat);
void libererEnsemble(Etat* ensemble);

void LibererAutomate(Automate* automate);

void ajouterEtat(Automate* automate, Etat* etat);
void ajouterTransition(Automate* automate, Transition* transition);
void ajouterEtatFinal(Automate* automate, Etat* etat) ;
void ajouterEtatinitial(Automate* automate, Etat* etat) ;

void afficherEtats(Automate* automate);
void afficherTransitions(Automate* automate);
void afficherAlphabet(Automate* automate);
void afficherEtatInitial(Automate* automate);
void afficherEtatsFinaux(Automate* automate);
void afficherAutomate(Automate* automate);

Automate* lireAutomateDepuisDot(const char* nomFichier) ;
void genererFichierDot(Automate* automate, const char* nomFichier);

void afficherEtatAvecPlusDeTransitionsSortantes(Automate* automate);
void afficherEtatsAvecTransitionSortante(Automate* automate, char etiquette);

bool estEtatFinal(Automate* automate, const char* etat);
int motEstEngendre(Automate* automate, const char* mot);
void lireMotsDepuisFichier(const char* nom_fichier, Automate* automate);

Automate* Concatenation(Automate* a1, Automate* a2);
Automate* UnionThompson(Automate* automate1, Automate* automate2);
Automate* KleeneStar(Automate* automate) ;
Automate* KleenePlus(Automate* automate);
void renommerEtats(Automate* automate, int startNumber) ;
int countStates(Automate* automate);
Automate* concatenateWithRenaming(Automate* a1, Automate* a2);
Automate* UnionWithRenaming(Automate* a1, Automate* a2);

Automate* creerAutomateDepuisExpressionReguliere(const char* expression);

Automate* supprimerEpsilonTransitions(Automate* automate);

Automate* determinisation(Automate* afn);

void transposer(Automate* afn, Automate **transposed);

Automate* minimisationBrzozowski(Automate* afn);

Automate* Intersection(Automate* a1, Automate* a2);

void afficherMenu() {
    int choix;
    char expr [30];
    char fichier[100];
    Automate* automate2 = NULL;
    Automate* result = NULL;

    do {
        printf("\n");
        printf("*                Menu Principal - Projet Automate             *\n");
        printf("**************     Operations sur l'automate     **************\n\n");
        printf("*    1. Afficher les informations de l'automate              *\n");
        printf("*    2. Afficher l'etat avec le plus de transitions sortantes*\n");
        printf("*    3. Afficher les etats avec une transition sortante      *\n");
        printf("*    4. Verifier si un mot est engendre par l'automate       *\n");
        printf("*    5. Verifier les mots d'un fichier avec l'automate       *\n\n");
        printf("**************     Operations avancees sur l'automate *********\n\n");
        printf("*    6. Concatener deux automates                            *\n");
        printf("*    7. Union de deux automates                              *\n");
        printf("*    8. Lire depuis une expression reguliere                 *\n");
        printf("*    9. Produit de deux automates (intersection)             *\n");
        printf("*    10. Suppression des transitions epsilon                 *\n");
        printf("*    11. Determiniser l'automate                             *\n");
        printf("*    12. Minimiser l'automate                                *\n");
        printf("*    13. Generer les fichiers .dot pour automate initial,    *\n");
        printf("*         deterministe et minimal                            *\n");
        printf("*    14. Afficher les mots engendres par l'automate minimal  *\n");
        printf("\n");
        printf("*    0. Quitter                                              *\n");
        printf("\n");
        printf("                   Entrez votre choix :    ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                 printf("Entrez le nom du fichier .dot pour le deuxieme automate : ");
                 scanf("%s", fichier);
                 automate2= lireAutomateDepuisDot(fichier);
                 afficherAutomate(automate2);
                 LibererAutomate(automate2);

                break;
            case 2:
                    printf("Entrez le nom du fichier .dot pour le deuxieme automate : ");
                    scanf("%s", fichier);
                    automate2= lireAutomateDepuisDot(fichier);
                    afficherEtatAvecPlusDeTransitionsSortantes(automate2);
                    LibererAutomate(automate2);

                break;
            case 3:
                    printf("Entrez le nom du fichier .dot pour le deuxieme automate : ");
                    scanf("%s", fichier);
                    automate2= lireAutomateDepuisDot(fichier);
                    char etiquette;
                    printf("Entrez l'etiquette a rechercher : ");
                    scanf(" %c", &etiquette);
                    afficherEtatsAvecTransitionSortante(automate2, etiquette);
                    LibererAutomate(automate2);

                break;
            case 4:
                    printf("Entrez le nom du fichier .dot pour le deuxieme automate : ");
                    scanf("%s", fichier);
                    automate2= lireAutomateDepuisDot(fichier);
                    char mot[100];
                    printf("Entrez un mot a verifier : ");
                    scanf("%s", mot);
                    if (motEstEngendre(automate2, mot)) {
                        printf("Le mot \"%s\" est engendre par l'automate.\n", mot);
                    } else {
                        printf("Le mot \"%s\" n'est pas engendre par l'automate.\n", mot);
                    }
                    LibererAutomate(automate2);
                    break;
            case 5:
                    printf("Entrez le nom du fichier .dot pour l'automate : ");
                    scanf("%s", fichier);
                    automate2= lireAutomateDepuisDot(fichier);
                    printf("Entrez le nom du fichier .txt contenant les mots : ");
                    scanf("%s", fichier);
                    lireMotsDepuisFichier(fichier, automate2);
                    LibererAutomate(automate2);
                break;
            case 6:
                printf("Entrez le nom du fichier .dot pour le premier automate : ");
                scanf("%s", fichier);
                Automate* auto1 = lireAutomateDepuisDot(fichier);

                printf("Entrez le nom du fichier .dot pour le deuxieme automate : ");
                scanf("%s", fichier);
                Automate* auto2 = lireAutomateDepuisDot(fichier);

                result = concatenateWithRenaming(auto1, auto2);
                if (result != NULL) {
                    printf("Entrez le nom du fichier.dot pour stocker l'automate : ");
                    scanf("%s", fichier);
                    genererFichierDot(result, fichier);
                    printf("Concatenation des automates reussie !\n");
                    
                } else {
                    printf("Erreur lors de la concatenation des automates.\n");
                }
                LibererAutomate(result);
                LibererAutomate(auto1);
                LibererAutomate(auto2);
                break;
            case 7:
                printf("Entrez le nom du fichier .dot pour le premier automate : ");
                scanf("%s", fichier);
                Automate* auto3 = lireAutomateDepuisDot(fichier);

                printf("Entrez le nom du fichier .dot pour le deuxieme automate : ");
                scanf("%s", fichier);
                Automate* auto4 = lireAutomateDepuisDot(fichier);

                result = UnionWithRenaming(auto3, auto4);
                if (result != NULL) {
                    printf("Entrez le nom du fichier.dot pour stocker l'automate : ");
                    scanf("%s", fichier);
                    genererFichierDot(result, fichier);
                    printf("Union des automates reussie !\n");
                } else {
                    printf("Erreur lors de l'union des automates.\n");
                }
                LibererAutomate(result);
                LibererAutomate(auto3);
                LibererAutomate(auto4);
                break;
            case 8:
            printf("Entrer l'expression reguliere : ");
            scanf("%s",expr);
            result = creerAutomateDepuisExpressionReguliere(expr);
            printf("Entrez le nom du fichier.dot pour stocker l'automate : ");
            scanf("%s", fichier);
            genererFichierDot(result, fichier);
            break;
            case 9:
                printf("Entrez le nom du fichier .dot pour le premier automate : ");
                scanf("%s", fichier);
                Automate* auto5 = lireAutomateDepuisDot(fichier);

                printf("Entrez le nom du fichier .dot pour le deuxieme automate : ");
                scanf("%s", fichier);
                Automate* auto6 = lireAutomateDepuisDot(fichier);

                result = Intersection(auto5,auto6);

                if (result != NULL) {
                    printf("Entrez le nom du fichier.dot pour stocker l'automate : ");
                    scanf("%s", fichier);
                    genererFichierDot(result, fichier);
                    printf("Produit des automates reussie !\n");
                } else {
                    printf("Erreur lors de la creation du produit des automates.\n");
                }
                LibererAutomate(result);
                LibererAutomate(auto5);
                LibererAutomate(auto6);
                break;
            case 10:
                    printf("Entrez le nom du fichier.dot d'automate : ");
                    scanf("%s", fichier);
                    automate2 = lireAutomateDepuisDot(fichier);
                    result = supprimerEpsilonTransitions(automate2);
                    if (result != NULL) {
                        printf("Entrez le nom du fichier.dot pour stocker l'automate : ");
                        scanf("%s", fichier);
                        genererFichierDot(result, fichier);
                        printf("Suppression des transitions epsilon reussie !\n");
                    } else {
                        printf("Erreur lors de la suppression des transitions epsilon.\n");
                    }
                    LibererAutomate(result);
                    LibererAutomate(automate2);
                break;
                case 11:
                printf("Entrez le nom du fichier.dot d'automate : ");
                scanf("%s", fichier);
                automate2 = lireAutomateDepuisDot(fichier);
                result = determinisation(automate2);
                if (result != NULL ) {
                    printf("Entrez le nom du fichier.dot pour stocker l'automate : ");
                        scanf("%s", fichier);
                        genererFichierDot(result, fichier);
                } else {
                    printf("Erreur lors de la generation des fichiers .dot.\n");
                }
                LibererAutomate(result);
                LibererAutomate(automate2);
            break;
            case 12:
                printf("Entrez le nom du fichier.dot d'automate : ");
                scanf("%s", fichier);
                automate2 = lireAutomateDepuisDot(fichier);
                result = minimisationBrzozowski(automate2);
                if (result != NULL ) {
                    printf("Entrez le nom du fichier.dot pour stocker l'automate : ");
                        scanf("%s", fichier);
                        genererFichierDot(result, fichier);
                } else {
                    printf("Erreur lors de la generation des fichiers .dot.\n");
                }
                LibererAutomate(automate2);
                LibererAutomate(result);
                    break;
            case 13:
                    printf("Entrez le nom du fichier.dot d'automate : ");
                    scanf("%s", fichier);
                    Automate* auto9 = lireAutomateDepuisDot(fichier);
                    Automate* automateDeterministe1 = determinisation(auto9);
                    Automate* automateMinimal1 = minimisationBrzozowski(auto9);

                    if (automateDeterministe1 != NULL && automateMinimal1 != NULL) {
                        genererFichierDot(auto9, "AutomateInitial.dot");
                        genererFichierDot(automateDeterministe1, "AutomateDeterministe.dot");
                        genererFichierDot(automateMinimal1, "AutomateMinimal.dot");
                        printf("Fichiers .dot generes avec succes.\n");
                    } else {
                        printf("Erreur lors de la generation des fichiers .dot.\n");
                    }
                    LibererAutomate(auto9);
                    LibererAutomate(automateDeterministe1);
                    LibererAutomate(automateMinimal1);
                break;
            case 14:
                    printf("Entrez le nom du fichier.dot d'automate : ");
                    scanf("%s", fichier);
                    Automate* auto10 = lireAutomateDepuisDot(fichier);
                    Automate* automateMin = minimisationBrzozowski(auto10);
                    if (automateMin != NULL) {
                        printf("Entrez le nom du fichier.dot pour stocker l'automate Minimale : ");
                        scanf("%s", fichier);
                        genererFichierDot(automateMin, fichier);
                        printf("Entrez le nom du fichier .txt contenant les mots : ");
                        scanf("%s", fichier);
                        lireMotsDepuisFichier(fichier,automateMin);
                    } else {
                        printf("Erreur lors de la minimisation de l'automate.\n");
                    }
                    LibererAutomate(auto10);
                    LibererAutomate(automateMin);
                break;
            case 0:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide !\n");
        }
    } while (choix != 0);

        LibererAutomate(result);
        LibererAutomate(automate2);
}

int main() {
afficherMenu();
return 0;
}


Automate* CreerAutomate() {
    Automate* automate = (Automate*)malloc(sizeof(Automate));
    if (automate == NULL) {  
        printf("Erreur : Impossible d'allouer de la mémoire pour l'automate.\n");
        return NULL;  
    }
    automate->alphabet[0] = '\0';
    automate->etats = NULL;
    automate->transitions = NULL;
    automate->etat_initial = NULL;
    automate->etats_finaux = NULL;
    return automate;
}

Etat* creerEtat(const char* nom) {
    Etat* nouvelEtat = (Etat*)malloc(sizeof(Etat));
    if (!nouvelEtat) {
        printf("Erreur d'allocation memoire.\n");
        exit(1);
    }
    strcpy(nouvelEtat->nom, nom);
    nouvelEtat->suivant = NULL;
    return nouvelEtat;
}

Transition* creerTransition(const char* depart, char symbole, const char* arrivee) {
    Transition* nouvelleTransition = (Transition*)malloc(sizeof(Transition));
    if (!nouvelleTransition) {
        printf("Erreur d'allocation memoire.\n");
        exit(1);
    }
    strcpy(nouvelleTransition->etat_depart, depart);
    nouvelleTransition->symbole = symbole;
    strcpy(nouvelleTransition->etat_arrivee, arrivee);
    nouvelleTransition->suivant = NULL;
    return nouvelleTransition;
}

bool estAutomateVide(Automate* automate) {
    if (automate == NULL) {
        return true;
    }
    return (automate->etats == NULL &&
            automate->transitions == NULL &&
            automate->etat_initial == NULL &&
            automate->etats_finaux == NULL &&
            automate->alphabet[0] == '\0');
}

bool estDansEnsemble(Etat* ensemble, const char* etat) {
    Etat* courant = ensemble;
    while (courant) {
        if (strcmp(courant->nom, etat) == 0) {
            return true;
        }
        courant = courant->suivant;
    }
    return false;
}

void ajouterEtatAEnsemble(Etat** ensemble, const char* etat) {
    if (!estDansEnsemble(*ensemble, etat)) {
        Etat* nouvelEtat = creerEtat(etat);
        nouvelEtat->suivant = *ensemble;
        *ensemble = nouvelEtat;
    }
}


void libererEnsemble(Etat* ensemble) {
    while (ensemble) {
        Etat* temp = ensemble;
        ensemble = ensemble->suivant;
        free(temp);
    }
}

void LibererAutomate(Automate* automate) {
    if (automate == NULL) return;

    Etat* etatCourant = automate->etats;
    while (etatCourant) {
        Etat* temp = etatCourant;
        etatCourant = etatCourant->suivant;
        free(temp);
    }

    Transition* transitionCourante = automate->transitions;
    while (transitionCourante) {
        Transition* temp = transitionCourante;
        transitionCourante = transitionCourante->suivant;
        free(temp);
    }
    Etat* etatInitialCourant = automate->etat_initial;
    while (etatInitialCourant) {
        Etat* temp = etatInitialCourant;
        etatInitialCourant = etatInitialCourant->suivant;
        free(temp);
    }
    Etat* etatFinalCourant = automate->etats_finaux;
    while (etatFinalCourant) {
        Etat* temp = etatFinalCourant;
        etatFinalCourant = etatFinalCourant->suivant;
        free(temp);
    }

    free(automate);
}

void ajouterEtat(Automate* automate, Etat* etat) {
    if (!automate->etats) {
        automate->etats = etat;
    } else {
        Etat* courant = automate->etats;
        while (courant->suivant) {
            if (strcmp(courant->nom, etat->nom) == 0 ) {
                free(etat);
                return;
            }
            courant = courant->suivant;
        }
        if (strcmp(courant->nom, etat->nom) == 0 ) {
            free(etat);
            return;
        }
        courant->suivant = etat;
    }
}
void ajouterTransition(Automate* automate, Transition* transition) {
    Transition* courant = automate->transitions;
    while (courant) {
        if (strcmp(courant->etat_depart, transition->etat_depart) == 0 &&
            strcmp(courant->etat_arrivee, transition->etat_arrivee) == 0 &&
            courant->symbole == transition->symbole ) 
            {
            free(transition); 
            return;
        }
        courant = courant->suivant;
    }

    if (!automate->transitions) {
        automate->transitions = transition;
    } else {
        courant = automate->transitions;
        while (courant->suivant) {
            courant = courant->suivant;
        }
        courant->suivant = transition;
    }
    if (!strchr(automate->alphabet, transition->symbole)) {
        int len = strlen(automate->alphabet);
        automate->alphabet[len] = transition->symbole;
        automate->alphabet[len + 1] = '\0';
    }
}

void ajouterEtatFinal(Automate* automate, Etat* etat) {
    Etat* nouvelEtatFinal = creerEtat(etat->nom);
    if (!automate->etats_finaux) {
        automate->etats_finaux = nouvelEtatFinal;
    } else {
        Etat* courant = automate->etats_finaux;
        while (courant->suivant) {
            if (strcmp(courant->nom, etat->nom) == 0) {
                free(etat);
                return;
            }
            courant = courant->suivant;
        }
        if (strcmp(courant->nom, etat->nom) == 0 ) {
            free(etat);
            return;
        }
        courant->suivant = nouvelEtatFinal;
    }
}
void ajouterEtatinitial(Automate* automate, Etat* etat) {
    Etat* nouvelEtatinitial = creerEtat(etat->nom);
    if (!automate->etat_initial) {
        automate->etat_initial = nouvelEtatinitial;
    } else {
        Etat* courant = automate->etat_initial;
        while (courant->suivant) {
            if (strcmp(courant->nom, etat->nom) == 0) {
                    free(etat);
                return;
            }
            courant = courant->suivant;
        }
        courant->suivant = nouvelEtatinitial;
    }
}

void afficherEtats(Automate* automate) {
    printf("Etats de l'automate :\n");
    if(!automate->etats){
        printf("Aucun Etats n'est enregistre\n");
    }else{
        Etat* courant = automate->etats;
        while (courant) {
        printf("- %s\n", courant->nom);
        courant = courant->suivant;
        }
    }
}
void afficherTransitions(Automate* automate) {
    printf("Transitions de l'automate :\n");
    if(!automate->transitions){
        printf("Aucune Transistion n'est enregistre\n");
    }else{
        Transition* courant = automate->transitions;
        while (courant) {
        printf("- %s --(%c)--> %s\n", courant->etat_depart, courant->symbole, courant->etat_arrivee);
        courant = courant->suivant;
            }
    }
}
void afficherAlphabet(Automate* automate) {
    printf("Alphabet de l'automate : ");
    if (strlen(automate->alphabet) == 0) {
        printf("Aucun alphabet defini.\n");
    } else {
        printf("{");
        for (int i = 0; i < strlen(automate->alphabet); i++) {
            printf("%c", automate->alphabet[i]);
            if (i < strlen(automate->alphabet) - 1) {
                printf(","); 
            }
        }
        printf("}\n");
    }
}
void afficherEtatInitial(Automate* automate) {
     Etat* courant = automate->etat_initial;
     printf("Etats initiaux de l'automate :\n");
    if (!courant) {
        printf("- Aucun etat initiale defini.\n");
    } else {
        while (courant) {
            printf("-%s\n", courant->nom);
            courant = courant->suivant;
        }
    }
}
void afficherEtatsFinaux(Automate* automate) {
    Etat* courant = automate->etats_finaux;
    printf("Etats finaux de l'automate :\n");
    if (!courant) {
        printf("- Aucun etat final defini.\n");
    } else {
        while (courant) {
            printf("-%s\n", courant->nom);
            courant = courant->suivant;
        }
    }
}

void afficherAutomate(Automate* automate) {
    printf("===== Informations de l'automate =====\n");
    afficherEtats(automate);
    afficherAlphabet(automate);
    afficherEtatInitial(automate);
    afficherEtatsFinaux(automate);
    afficherTransitions(automate);
    printf("=====================================\n");
}

Automate* lireAutomateDepuisDot(const char* nomFichier) {
    Automate*automate = CreerAutomate();
    FILE* fichier = fopen(nomFichier, "r");
    if (!fichier) {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", nomFichier);
        LibererAutomate(automate);
        return NULL;
    }
    char ligne[256];
    while (fgets(ligne, sizeof(ligne), fichier) ){
        ligne[strcspn(ligne, "\n")] = '\0';
        if (strstr(ligne, "[shape=circle]")) {
            char *start = strstr(ligne, "]") + 1;
            char *name = strtok(start, " ;");
            while (name != NULL) {
                ajouterEtat(automate, creerEtat(name));
                name = strtok(NULL, " ;");
            }
        }
        else if (strstr(ligne, "S") && strstr(ligne, "->")) {
            char etat[10];
            if (sscanf(ligne," S%*d -> %[^;]", etat) == 1) {
                ajouterEtatinitial(automate, creerEtat(etat));
            }
        }
        else if (strstr(ligne, "-> F")) {
            char etat[10];
            if (sscanf(ligne," %s -> F", etat) == 1) {
                ajouterEtatFinal(automate, creerEtat(etat));
            }
        }
        else if (strstr(ligne, "->") ) {
            char etat1[10], etat2[10], symbole;
            if (sscanf(ligne, " %s -> %s [label=\"%c\"]", etat1, etat2, &symbole) == 3) {
                ajouterTransition(automate, creerTransition(etat1, symbole, etat2));
            }
        }
    }
    fclose(fichier);
    printf("Automate charge avec succes depuis %s !\n\n", nomFichier);
    return automate;
}

void genererFichierDot(Automate* automate, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "w");
    if (!fichier) {
        printf("Erreur : Impossible de creer le fichier %s\n", nomFichier);
        return;
    }
    fprintf(fichier, "digraph Automate {\n");
    fprintf(fichier, "    rankdir=LR;\n");
    fprintf(fichier, "    node[shape=circle];");
    Etat* etatCourant = automate->etats;
    while (etatCourant) {
        fprintf(fichier, " %s;", etatCourant->nom);
        etatCourant = etatCourant->suivant;
    }
    fprintf(fichier, "\n");

    
    fprintf(fichier, "    node[shape=none, label=\"\"];");
    etatCourant = automate->etat_initial;
    int compteurS = 1; 
    while (etatCourant) {
        fprintf(fichier, "S%d;", compteurS);
        compteurS++;
        etatCourant = etatCourant->suivant;
    }
    fprintf(fichier, "\n");

    
    fprintf(fichier, "    node[shape=none, label=\"\"];");
    etatCourant = automate->etats_finaux;
    int compteurF = 1; 
    while (etatCourant) {
        fprintf(fichier, "F%d;", compteurF);
        compteurF++;
        etatCourant = etatCourant->suivant;
    }
    fprintf(fichier, "\n");

    
    etatCourant = automate->etat_initial;
    compteurS = 1;
    while (etatCourant) {
        fprintf(fichier, "    S%d -> %s;\n", compteurS, etatCourant->nom);
        compteurS++;
        etatCourant = etatCourant->suivant;
    }

    
    etatCourant = automate->etats_finaux;
    compteurF = 1;
    while (etatCourant) {
        fprintf(fichier, "    %s -> F%d;\n", etatCourant->nom, compteurF);
        compteurF++;
        etatCourant = etatCourant->suivant;
    }

    
    Transition* transitionCourante = automate->transitions;
    while (transitionCourante) {
        fprintf(fichier, "    %s -> %s [label=\"%c\"];\n",
                transitionCourante->etat_depart,
                transitionCourante->etat_arrivee,
                transitionCourante->symbole);
        transitionCourante = transitionCourante->suivant;
    }

    
    fprintf(fichier, "}\n");
    fclose(fichier);

    printf("Fichier %s genere avec succes !\n", nomFichier);
}

void afficherEtatAvecPlusDeTransitionsSortantes(Automate* automate) {
    int maxTransitions = 0;
    char etatMaxTransitions[10] = "";
    Etat* courantEtat = automate->etats;
    while (courantEtat) {
        int count = 0;
        Transition* courantTransition = automate->transitions;
        while (courantTransition) {
            if (strcmp(courantTransition->etat_depart, courantEtat->nom) == 0) {
                count++;
            }
            courantTransition = courantTransition->suivant;
        }

        // Mettre à jour l'état avec le plus de transitions sortantes
        if (count > maxTransitions) {
            maxTransitions = count;
            strcpy(etatMaxTransitions, courantEtat->nom);
        }

        courantEtat = courantEtat->suivant;
    }

    if (maxTransitions > 0) {
        printf("L'etat avec le plus de transitions sortantes est : %s (%d transitions)\n", etatMaxTransitions, maxTransitions);
    } else {
        printf("Aucun etat avec des transitions sortantes trouve.\n");
    }
}
void afficherEtatsAvecTransitionSortante(Automate* automate, char etiquette) {
    printf("Etats avec au moins une transition sortante etiquetee par '%c' :\n", etiquette);
     
    int count = 0;
    Transition* courantTransition = automate->transitions;
    while (courantTransition) {
        if (courantTransition->symbole == etiquette) {
            int dejaAffiche = 0;
            for (int i = 0; i < count; i++) {
                if (strcmp(courantTransition->etat_depart, automate->etats[i].nom) == 0) {
                    dejaAffiche = 1;
                    break;
                }
            }

            if (!dejaAffiche) {
                printf("- %s\n", courantTransition->etat_depart);
                strcpy(automate->etats[count].nom, courantTransition->etat_depart);
                count++;
            }
        }
        courantTransition = courantTransition->suivant;
    }

    if (count == 0) {
        printf("Aucun etat trouve avec une transition sortante etiquetee par '%c'.\n", etiquette);
    }
}

bool estEtatFinal(Automate* automate, const char* etat) {
    Etat* courant = automate->etats_finaux;
    while (courant) {
        if (strcmp(courant->nom, etat) == 0) {
            return true;
        }
        courant = courant->suivant;
    }
    return false;
}

int motEstEngendre(Automate* automate, const char* mot) {
    Etat* courant = automate->etat_initial;
    char etatsCourants[100][10]; 
    int nbEtatsCourants = 0;
    //passer toutes les etats initiaux 
    while (courant) {
        strcpy(etatsCourants[nbEtatsCourants], courant->nom);
        nbEtatsCourants++;
        courant = courant->suivant;
    }
    //passer par chaque symbole de transitions 
    for (int i = 0; mot[i] != '\0'; i++) {
        char symbole = mot[i];
        char nouveauxEtats[100][10]; 
        int nbNouveauxEtats = 0;
        //pour chaque etat chercher les transitions possibles avec le symbole actuel
        for (int j = 0; j < nbEtatsCourants; j++) {
            Transition* transition = automate->transitions;
            while (transition) {
                if (strcmp(transition->etat_depart, etatsCourants[j]) == 0 && transition->symbole == symbole) {
                
                    strcpy(nouveauxEtats[nbNouveauxEtats], transition->etat_arrivee);
                    nbNouveauxEtats++;
                }
                transition = transition->suivant;
            }
        }
        //si un nouvel etat n'est pas trouvee sortir
        if (nbNouveauxEtats == 0) {
            return 0;
        }
        //sortir les etats de la boucle 
        nbEtatsCourants = nbNouveauxEtats;
        for (int j = 0; j < nbEtatsCourants; j++) {
            strcpy(etatsCourants[j], nouveauxEtats[j]);
        }
    }
    //verifier si l'etat courant est finale 
    for (int i = 0; i < nbEtatsCourants; i++) {
        if (estEtatFinal(automate, etatsCourants[i])) {
            return 1; 
        }
    }
    return 0; 
}

void lireMotsDepuisFichier(const char* nom_fichier, Automate* automate) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nom_fichier);
        return;
    }
    char mot[100];
    printf("Liste des mots generes par l'automate :\n");
    while (fscanf(fichier, "%s", mot) != EOF) {
        if (motEstEngendre(automate, mot)) {
            printf("Le mot \"%s\" est engendre par l'automate.\n", mot);
        } else {
            printf("Le mot \"%s\" n'est pas engendre par l'automate.\n", mot);
        }
    }
    
    fclose(fichier);
}

Automate* Concatenation(Automate* a1, Automate* a2) {
    if (a1 == NULL || a2 == NULL) {
        printf("Erreur : Un des automates est NULL.\n");
        return NULL;
    }

    Automate* automateConca = CreerAutomate();

    Etat* etatCourant = a1->etats;
    while (etatCourant) {
        ajouterEtat(automateConca, creerEtat(etatCourant->nom));
        etatCourant = etatCourant->suivant;
    }

    etatCourant = a2->etats;
    while (etatCourant) {
        ajouterEtat(automateConca, creerEtat(etatCourant->nom));
        etatCourant = etatCourant->suivant;
    }

    Transition* transitionCourante = a1->transitions;
    while (transitionCourante) {
        ajouterTransition(automateConca, creerTransition(transitionCourante->etat_depart, transitionCourante->symbole, transitionCourante->etat_arrivee));
        transitionCourante = transitionCourante->suivant;
    }

    transitionCourante = a2->transitions;
    while (transitionCourante) {
        ajouterTransition(automateConca, creerTransition(transitionCourante->etat_depart, transitionCourante->symbole, transitionCourante->etat_arrivee));
        transitionCourante = transitionCourante->suivant;
    }

    etatCourant = a1->etat_initial;
    while (etatCourant != NULL) { 
        ajouterEtatinitial(automateConca, creerEtat(etatCourant->nom));
        etatCourant = etatCourant->suivant;
    }

    etatCourant = a2->etats_finaux;
    while (etatCourant != NULL) { 
        ajouterEtatFinal(automateConca, creerEtat(etatCourant->nom));
        etatCourant = etatCourant->suivant;
    }

    int hasMultipleFinals = 0;
    Etat* final1 = a1->etats_finaux;
    if (final1 && final1->suivant) {
        hasMultipleFinals = 1;
    }

    int hasMultipleInitials = 0;
    Etat* initial2 = a2->etat_initial;
    if (initial2 && initial2->suivant) {
        hasMultipleInitials = 1;
    }


    if (hasMultipleFinals) {
                ajouterEtat(automateConca, creerEtat("S"));
                Etat* etatfinAuto1 = a1->etats_finaux;
                while (etatfinAuto1) {
                ajouterTransition(automateConca, creerTransition(etatfinAuto1->nom, 'e', "S")); 
                etatfinAuto1 = etatfinAuto1->suivant;
                }
            if (hasMultipleInitials) {
                ajouterEtat(automateConca, creerEtat("E"));
                Etat* etatiniauto2 = a2->etat_initial;
                while (etatiniauto2) {
                ajouterTransition(automateConca, creerTransition("E", 'e', etatiniauto2->nom));
                etatiniauto2 = etatiniauto2->suivant;
             }
             ajouterTransition(automateConca, creerTransition("S", 'e', "E"));
            }else{
                ajouterTransition(automateConca, creerTransition("S", 'e', a2->etat_initial->nom));
            }
    }else{
        if (hasMultipleInitials) {
            ajouterEtat(automateConca, creerEtat("E"));
            Etat* etatiniauto2 = a2->etat_initial;
            while (etatiniauto2) {
            ajouterTransition(automateConca, creerTransition("E", 'e', etatiniauto2->nom));
            etatiniauto2 = etatiniauto2->suivant;
         }
         ajouterTransition(automateConca, creerTransition(a1->etats_finaux->nom, 'e', "E"));
        }else{
            ajouterTransition(automateConca, creerTransition(a1->etats_finaux->nom, 'e', a2->etat_initial->nom));
        }

    }
    return automateConca;
}

Automate* UnionThompson(Automate* automate1, Automate* automate2) {
    if (automate1 == NULL || automate2 == NULL) {
        printf("Erreur : Un des automates est NULL.\n");
        return NULL;
    }
    Automate* automateUnion = CreerAutomate();

    Etat* etatCourant = automate1->etats;
    while (etatCourant) {
        ajouterEtat(automateUnion, creerEtat(etatCourant->nom));
        etatCourant = etatCourant->suivant;
    }

    etatCourant = automate2->etats;
    while (etatCourant) {
        ajouterEtat(automateUnion, creerEtat(etatCourant->nom));
        etatCourant = etatCourant->suivant;
    }

    Transition* transitionCourante = automate1->transitions;
    while (transitionCourante) {
        ajouterTransition(automateUnion, creerTransition(transitionCourante->etat_depart, transitionCourante->symbole, transitionCourante->etat_arrivee));
        transitionCourante = transitionCourante->suivant;
    }

    transitionCourante = automate2->transitions;
    while (transitionCourante) {
        ajouterTransition(automateUnion, creerTransition(transitionCourante->etat_depart, transitionCourante->symbole, transitionCourante->etat_arrivee));
        transitionCourante = transitionCourante->suivant;
    }

    ajouterEtat(automateUnion, creerEtat("S")); 
    ajouterEtatinitial(automateUnion, creerEtat("S"));

    ajouterEtat(automateUnion, creerEtat("F")); 
    ajouterEtatFinal(automateUnion, creerEtat("F"));

    Etat* initial1 = automate1->etat_initial;
    while (initial1 != NULL) {
        ajouterTransition(automateUnion, creerTransition("S", 'e', initial1->nom));
        initial1 = initial1->suivant;
    }

    Etat* initial2 = automate2->etat_initial;
    while (initial2 != NULL) {
        ajouterTransition(automateUnion, creerTransition("S", 'e', initial2->nom));
        initial2 = initial2->suivant;
    }

    Etat* final1 = automate1->etats_finaux;
    while (final1 != NULL) {
        ajouterTransition(automateUnion, creerTransition(final1->nom, 'e', "F"));
        final1 = final1->suivant;
    }

    Etat* final2 = automate2->etats_finaux;
    while (final2 != NULL) {
        ajouterTransition(automateUnion, creerTransition(final2->nom, 'e', "F"));
        final2 = final2->suivant;
    }

    LibererAutomate(automate1);
    LibererAutomate(automate2);

    return automateUnion;
}

Automate* KleeneStar(Automate* automate) {
    if (automate == NULL) {
        printf("Erreur : L'automate est NULL.\n");
        return NULL;
    }

    // Create a new automaton for the Kleene star
    Automate* starAutomate = CreerAutomate();
    if (!starAutomate) {
        printf("Erreur : Impossible de creer l'automate pour l'étoile de Kleene.\n");
        return NULL;
    }

    // Add all states from the input automaton to the new automaton
    Etat* etatCourant = automate->etats;
    while (etatCourant) {
        ajouterEtat(starAutomate, creerEtat(etatCourant->nom));
        etatCourant = etatCourant->suivant;
    }

    // Add all transitions from the input automaton to the new automaton
    Transition* transitionCourante = automate->transitions;
    while (transitionCourante) {
        ajouterTransition(starAutomate, creerTransition(transitionCourante->etat_depart, transitionCourante->symbole, transitionCourante->etat_arrivee));
        transitionCourante = transitionCourante->suivant;
    }

    // Add a new start state and a new end state
    Etat* newStart = creerEtat("S");
    Etat* newEnd = creerEtat("E");
    ajouterEtat(starAutomate, newStart);
    ajouterEtat(starAutomate, newEnd);
    ajouterEtatinitial(starAutomate, newStart);
    ajouterEtatFinal(starAutomate, newEnd);

    // Add epsilon transitions for the Kleene star
    // Transition from new start to the start(s) of the input automaton
    Etat* initialCourant = automate->etat_initial;
    while (initialCourant) {
        ajouterTransition(starAutomate, creerTransition("S", 'e', initialCourant->nom));
        initialCourant = initialCourant->suivant;
    }

    // Transition from the end(s) of the input automaton to the new end
    Etat* finalCourant = automate->etats_finaux;
    while (finalCourant) {
        ajouterTransition(starAutomate, creerTransition(finalCourant->nom, 'e', "E"));
        finalCourant = finalCourant->suivant;
    }

    // Transition from new start to new end (to allow zero repetitions)
    ajouterTransition(starAutomate, creerTransition("S", 'e', "E"));

    // Transition from the end(s) of the input automaton back to the start(s) (to allow repetitions)
    finalCourant = automate->etats_finaux;
    while (finalCourant) {
        initialCourant = automate->etat_initial;
        while (initialCourant) {
            ajouterTransition(starAutomate, creerTransition(finalCourant->nom, 'e', initialCourant->nom));
            initialCourant = initialCourant->suivant;
        }
        finalCourant = finalCourant->suivant;
    }

    // Free the input automaton
    LibererAutomate(automate);

    // Rename states in the star automaton to ensure unique names
    renommerEtats(starAutomate, 0);

    return starAutomate;
}

Automate* KleenePlus(Automate* automate) {
    if (automate == NULL) {
        printf("Erreur : L'automate est NULL.\n");
        return NULL;
    }

    Automate* plusAutomate = CreerAutomate();
    if (!plusAutomate) {
        printf("Erreur : Impossible de creer l'automate pour l'operateur +.\n");
        return NULL;
    }

    Etat* etatCourant = automate->etats;
    while (etatCourant) {
        ajouterEtat(plusAutomate, creerEtat(etatCourant->nom));
        etatCourant = etatCourant->suivant;
    }

    Transition* transitionCourante = automate->transitions;
    while (transitionCourante) {
        ajouterTransition(plusAutomate, creerTransition(transitionCourante->etat_depart, transitionCourante->symbole, transitionCourante->etat_arrivee));
        transitionCourante = transitionCourante->suivant;
    }

    // Ajouter les états initiaux et finaux de l'automate original au nouvel automate
    Etat* initialCourant = automate->etat_initial;
    while (initialCourant) {
        ajouterEtatinitial(plusAutomate, creerEtat(initialCourant->nom));
        initialCourant = initialCourant->suivant;
    }

    Etat* finalCourant = automate->etats_finaux;
    while (finalCourant) {
        ajouterEtatFinal(plusAutomate, creerEtat(finalCourant->nom));
        finalCourant = finalCourant->suivant;
    }

    finalCourant = automate->etats_finaux;
    while (finalCourant) {
        initialCourant = automate->etat_initial;
        while (initialCourant) {
            ajouterTransition(plusAutomate, creerTransition(finalCourant->nom, 'e', initialCourant->nom));
            initialCourant = initialCourant->suivant;
        }
        finalCourant = finalCourant->suivant;
    }

    LibererAutomate(automate);

    renommerEtats(plusAutomate, 0);

    return plusAutomate;
}

void renommerEtats(Automate* automate, int startNumber) {
    if (automate == NULL) return;

    char oldToNew[100][20]; 
    int counter = startNumber;

    Etat* etatCourant = automate->etats;
    while (etatCourant) {
        char newName[20];
        sprintf(newName, "q%d", counter); // New name format: q0, q1, q2, etc.
        strcpy(oldToNew[counter - startNumber], etatCourant->nom); // Store old name
        strcpy(etatCourant->nom, newName); // Update state name
        counter++;
        etatCourant = etatCourant->suivant;
    }

    // Update transitions to reflect the new state names
    Transition* transitionCourante = automate->transitions;
    while (transitionCourante) {
        // Update etat_depart
        for (int i = 0; i < counter; i++) {
            if (strcmp(transitionCourante->etat_depart, oldToNew[i]) == 0) {
                sprintf(transitionCourante->etat_depart, "q%d", i + startNumber);
                break;
            }
        }

        // Update etat_arrivee
        for (int i = 0; i < counter; i++) {
            if (strcmp(transitionCourante->etat_arrivee, oldToNew[i]) == 0) {
                sprintf(transitionCourante->etat_arrivee, "q%d", i + startNumber);
                break;
            }
        }

        transitionCourante = transitionCourante->suivant;
    }

    // Update etat_initial and etats_finaux
    
    Etat* Etatini = automate->etat_initial;
    while (Etatini) {
        for (int i = 0; i < counter; i++) {
            if (strcmp(Etatini->nom, oldToNew[i]) == 0) {
                sprintf(Etatini->nom, "q%d", i + startNumber);
                break;
            }
        }
        Etatini = Etatini->suivant;
    }

    Etat* finalCourant = automate->etats_finaux;
    while (finalCourant) {
        for (int i = 0; i < counter; i++) {
            if (strcmp(finalCourant->nom, oldToNew[i]) == 0) {
                sprintf(finalCourant->nom, "q%d", i + startNumber);
                break;
            }
        }
        finalCourant = finalCourant->suivant;
    }
}

int countStates(Automate* automate) {
    if (automate == NULL) return 0;

    int count = 0;
    Etat* etatCourant = automate->etats;

    while (etatCourant) {
        count++;
        etatCourant = etatCourant->suivant;
    }

    return count;
}

Automate* concatenateWithRenaming(Automate* a1, Automate* a2) {
    renommerEtats(a1, 0);
    int startNumber = countStates(a1); 
    renommerEtats(a2, startNumber);

    Automate* result = Concatenation(a1, a2);
    return result;
}

Automate* UnionWithRenaming(Automate* a1, Automate* a2) {
    renommerEtats(a1, 0);
    int startNumber = countStates(a1); 
    renommerEtats(a2, startNumber);

    Automate* result = UnionThompson(a1, a2);
    return result;
}

Automate* creerAutomateDepuisExpressionReguliere(const char* expression) {
    Automate* automate = CreerAutomate();
    if (!automate) {
        printf("Erreur : Impossible de creer l'automate.\n");
        return NULL;
    }

    Automate* leftAutomate = NULL;
    Automate* rightAutomate = NULL;

    for (int i = 0; expression[i] != '\0'; i++) {
        char c = expression[i];

        if (c != '+' && c != '|' && c != '*' && c != '(' && c != ')' && c != '.') {
            leftAutomate = CreerAutomate();
            Etat* start = creerEtat("S0");
            Etat* end = creerEtat("S1");
            ajouterEtat(leftAutomate, start);
            ajouterEtat(leftAutomate, end);
            ajouterEtatinitial(leftAutomate, start);
            ajouterEtatFinal(leftAutomate, end);
            ajouterTransition(leftAutomate, creerTransition("S0", c, "S1"));

            renommerEtats(leftAutomate, 0);
        }

        else if ( c == '|') {
            rightAutomate = creerAutomateDepuisExpressionReguliere(expression + i + 1);
            int leftStateCount = countStates(leftAutomate);
            renommerEtats(rightAutomate, leftStateCount);

            leftAutomate = UnionThompson(leftAutomate,rightAutomate);
            i += strlen(expression + i + 1);
        }

        else if (c == '*') {
            leftAutomate = KleeneStar(leftAutomate);

        }
        else if (c == '+') {
            leftAutomate = KleenePlus(leftAutomate);

        }

        else if (c == '.') {
            rightAutomate = creerAutomateDepuisExpressionReguliere(expression + i + 1);
            int leftStateCount = countStates(leftAutomate);
            renommerEtats(rightAutomate, leftStateCount);

            leftAutomate = Concatenation(leftAutomate, rightAutomate);
            i += strlen(expression + i + 1);

        }
        
        else if (c == '(') {
            int j = i + 1;
            int parenCount = 1;
            while (expression[j] != '\0' && parenCount > 0) {
                if (expression[j] == '(') parenCount++;
                if (expression[j] == ')') parenCount--;
                j++;
            }

            char subExpr[MAX_STATES];
            strncpy(subExpr, expression + i + 1, j - i - 2);
            subExpr[j - i - 2] = '\0';
            leftAutomate = creerAutomateDepuisExpressionReguliere(subExpr);

            i = j - 1;

            renommerEtats(leftAutomate, 0);
        }
    }
    return leftAutomate;
}

Automate* supprimerEpsilonTransitions(Automate* automate) {
    if (estAutomateVide(automate)) {
        printf("Erreur : L'automate est vide.\n");
        return NULL;
    }

    Automate* automateSansEpsilon = CreerAutomate();

    Etat* etatCourant = automate->etats;
    while (etatCourant) {
        ajouterEtat(automateSansEpsilon, creerEtat(etatCourant->nom));
        etatCourant = etatCourant->suivant;
    }

    Etat* etat = automate->etats;
    while (etat) {
        Etat* fermetureEpsilon[100];
        int nbEtatsFermeture = 0;
        fermetureEpsilon[nbEtatsFermeture++] = etat;

        for (int i = 0; i < nbEtatsFermeture; i++) {
            Transition* transition = automate->transitions;
            while (transition) {
                if (strcmp(transition->etat_depart, fermetureEpsilon[i]->nom) == 0 && transition->symbole == 'e') {
                    Etat* etatArrivee = NULL;
                    Etat* courant = automate->etats;
                    while (courant) {
                        if (strcmp(courant->nom, transition->etat_arrivee) == 0) {
                            etatArrivee = courant;
                            break;
                        }
                        courant = courant->suivant;
                    }
                    if (etatArrivee) {
                        int dejaPresent = 0;
                        for (int j = 0; j < nbEtatsFermeture; j++) {
                            if (fermetureEpsilon[j] == etatArrivee) {
                                dejaPresent = 1;
                                break;
                            }
                        }
                        if (!dejaPresent) {
                            fermetureEpsilon[nbEtatsFermeture++] = etatArrivee;
                        }
                    }
                }
                transition = transition->suivant;
            }
        }

        for (int i = 0; i < nbEtatsFermeture; i++) {
            Transition* transition = automate->transitions;
            while (transition) {
                if (strcmp(transition->etat_depart, fermetureEpsilon[i]->nom) == 0 && transition->symbole != 'e') {
                    ajouterTransition(automateSansEpsilon, creerTransition(etat->nom, transition->symbole, transition->etat_arrivee));
                }
                transition = transition->suivant;
            }
        }

        for (int i = 0; i < nbEtatsFermeture; i++) {
            if (estEtatFinal(automate, fermetureEpsilon[i]->nom)) {
                ajouterEtatFinal(automateSansEpsilon, creerEtat(etat->nom));
                break;
            }
        }

        etat = etat->suivant;
    }

    Etat* etatInitial = automate->etat_initial;
    while (etatInitial) {
        ajouterEtatinitial(automateSansEpsilon, creerEtat(etatInitial->nom));
        etatInitial = etatInitial->suivant;
    }

    return automateSansEpsilon;
}

Automate* determinisation(Automate* afn) {
    if (estAutomateVide(afn)) {
        printf("Erreur : L'automate est vide.\n");
        return NULL;
    }

    Automate* afd = CreerAutomate();

    Etat* ensembles[MAX_STATES] = {0};
    int num_ensembles = 0;

    Etat* ensemble_initial = NULL;
    Etat* etat_initial = afn->etat_initial;
    while (etat_initial) {
        ajouterEtatAEnsemble(&ensemble_initial, etat_initial->nom);
        etat_initial = etat_initial->suivant;
    }
    ensembles[num_ensembles++] = ensemble_initial;

    ajouterEtatinitial(afd, creerEtat("I0"));

    for (int i = 0; i < num_ensembles; i++) {
        Etat* ensemble_courant = ensembles[i];
        char nom_etat_afd[10];
        sprintf(nom_etat_afd, "I%d", i);
        ajouterEtat(afd, creerEtat(nom_etat_afd));

        for (int a = 0; a < strlen(afn->alphabet); a++) {
            char symbole = afn->alphabet[a];
            Etat* nouvel_ensemble = NULL;

            Etat* etat_courant = ensemble_courant;
            while (etat_courant) {
                Transition* transition = afn->transitions;
                while (transition) {
                    if (strcmp(transition->etat_depart, etat_courant->nom) == 0 && transition->symbole == symbole) {
                        ajouterEtatAEnsemble(&nouvel_ensemble, transition->etat_arrivee);
                    }
                    transition = transition->suivant;
                }
                etat_courant = etat_courant->suivant;
            }

            if (!nouvel_ensemble) {
                continue;
            }

            int index_ensemble = -1;
            for (int j = 0; j < num_ensembles; j++) {
                bool match = true;
                Etat* e1 = nouvel_ensemble;
                Etat* e2 = ensembles[j];
                while (e1 && e2) {
                    if (strcmp(e1->nom, e2->nom) != 0) {
                        match = false;
                        break;
                    }
                    e1 = e1->suivant;
                    e2 = e2->suivant;
                }
                if (match && !e1 && !e2) {
                    index_ensemble = j;
                    break;
                }
            }

            if (index_ensemble == -1) {
                index_ensemble = num_ensembles;
                ensembles[num_ensembles++] = nouvel_ensemble;
                char nom_nouvel_etat[10];
                sprintf(nom_nouvel_etat, "I%d", index_ensemble);
                ajouterEtat(afd, creerEtat(nom_nouvel_etat));
            }

            char nom_etat_arrivee[10];
            sprintf(nom_etat_arrivee, "I%d", index_ensemble);
            ajouterTransition(afd, creerTransition(nom_etat_afd, symbole, nom_etat_arrivee));
        }
    }

    for (int i = 0; i < num_ensembles; i++) {
        Etat* etat_courant = ensembles[i];
        while (etat_courant) {
            if (estEtatFinal(afn, etat_courant->nom)) {
                char nom_etat_afd[10];
                sprintf(nom_etat_afd, "I%d", i);
                ajouterEtatFinal(afd, creerEtat(nom_etat_afd));
                break;
            }
            etat_courant = etat_courant->suivant;
        }
    }

    for (int i = 0; i < num_ensembles; i++) {
        libererEnsemble(ensembles[i]);
    }
    renommerEtats(afd,0);
    return afd;
}

void transposer(Automate* afn, Automate** transposed) {
    *transposed = CreerAutomate();

    Etat* etat_courant = afn->etats;
    while (etat_courant) {
        ajouterEtat(*transposed, creerEtat(etat_courant->nom));
        etat_courant = etat_courant->suivant;
    }

    Transition* transition_courante = afn->transitions;
    while (transition_courante) {
        ajouterTransition(*transposed, creerTransition(transition_courante->etat_arrivee, transition_courante->symbole, transition_courante->etat_depart));
        transition_courante = transition_courante->suivant;
    }

    Etat* etat_initial = afn->etat_initial;
    while (etat_initial) {
        ajouterEtatFinal(*transposed, creerEtat(etat_initial->nom));
        etat_initial = etat_initial->suivant;
    }

    Etat* etat_final = afn->etats_finaux;
    while (etat_final) {
        ajouterEtatinitial(*transposed, creerEtat(etat_final->nom));
        etat_final = etat_final->suivant;
    }
}

Automate* minimisationBrzozowski(Automate* afn) {
    Automate* transposed = NULL;
    transposer(afn, &transposed);


    Automate* afd_transposed = determinisation(transposed);

    Automate* transposed_again = NULL;
    transposer(afd_transposed,& transposed_again);

    Automate* afd_minimal = determinisation(transposed_again);

    LibererAutomate(transposed);
    LibererAutomate(afd_transposed);
    LibererAutomate(transposed_again);

    return afd_minimal;
}



Automate* Intersection(Automate* a1, Automate* a2) {
    if (!a1 || !a2) return NULL;

    renommerEtats(a1, 0);
    renommerEtats(a2, countStates(a1));

    Automate* result = CreerAutomate();
    if (!result) return NULL;

    char queue[MAX_STATES][20]; 
    int front = 0, rear = 0;

    Etat* init1 = a1->etat_initial;
    while (init1) {
        Etat* init2 = a2->etat_initial;
        while (init2) {
            char newState[20];
            sprintf(newState, "%s_%s", init1->nom, init2->nom);
            
            ajouterEtat(result, creerEtat(newState));
            ajouterEtatinitial(result, creerEtat(newState));
            
            strcpy(queue[rear++], newState); 
            init2 = init2->suivant;
        }
        init1 = init1->suivant;
    }

    while (front < rear) {
        char current[20];
        strcpy(current, queue[front++]);

        char q1[10], q2[10];
        sscanf(current, "%[^_]_%s", q1, q2);

        for (int i = 0; i < strlen(a1->alphabet); i++) {
            char symbol = a1->alphabet[i];
            if (!strchr(a2->alphabet, symbol)) continue;

            Transition* t1 = a1->transitions;
            while (t1) {
                if (strcmp(t1->etat_depart, q1) == 0 && t1->symbole == symbol) {
                    Transition* t2 = a2->transitions;
                    while (t2) {
                        if (strcmp(t2->etat_depart, q2) == 0 && t2->symbole == symbol) {
                            char newState[20];
                            sprintf(newState, "%s_%s", t1->etat_arrivee, t2->etat_arrivee);

                            if (!estDansEnsemble(result->etats, newState)) {
                                ajouterEtat(result, creerEtat(newState));
                                strcpy(queue[rear++], newState); 
                            }
                            
                            ajouterTransition(result, creerTransition(current, symbol, newState));

                            if (estEtatFinal(a1, t1->etat_arrivee) && estEtatFinal(a2, t2->etat_arrivee)) {
                                ajouterEtatFinal(result, creerEtat(newState));
                            }
                        }
                        t2 = t2->suivant;
                    }
                }
                t1 = t1->suivant;
            }
        }
    }
    
    Etat* init_courant = result->etat_initial;
    Etat* prev_init = NULL;
    
    while (init_courant) {
        int has_outgoing = 0;
        Transition* t = result->transitions;
        
        while (t) {
            if (strcmp(t->etat_depart, init_courant->nom) == 0) {
                has_outgoing = 1;
                break;
            }
            t = t->suivant;
        }

        Etat* next_init = init_courant->suivant;
        
        if (!has_outgoing) {
            if (prev_init) {
                prev_init->suivant = next_init;
            } else {
                result->etat_initial = next_init;
            }
            
            int is_used = 0;
            
            Transition* t_check = result->transitions;
            while (t_check) {
                if (strcmp(t_check->etat_arrivee, init_courant->nom) == 0) {
                    is_used = 1;
                    break;
                }
                t_check = t_check->suivant;
            }
            
            if (!is_used) {
                Etat* final_check = result->etats_finaux;
                while (final_check) {
                    if (strcmp(final_check->nom, init_courant->nom) == 0) {
                        is_used = 1;
                        break;
                    }
                    final_check = final_check->suivant;
                }
            }
            
            if (!is_used) {
                Etat* etat_prev = NULL;
                Etat* etat_curr = result->etats;
                while (etat_curr) {
                    if (strcmp(etat_curr->nom, init_courant->nom) == 0) {
                        if (etat_prev) {
                            etat_prev->suivant = etat_curr->suivant;
                        } else {
                            result->etats = etat_curr->suivant;
                        }
                        free(etat_curr);
                        break;
                    }
                    etat_prev = etat_curr;
                    etat_curr = etat_curr->suivant;
                }
            }
            
            free(init_courant);
        } else {
            prev_init = init_courant;
        }
        
        init_courant = next_init;
    }
   
    renommerEtats(result, 0); 
    return result;
}
