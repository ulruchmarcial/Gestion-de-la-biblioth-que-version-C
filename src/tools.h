#ifndef TOOLS_H
#define TOOLS_H
#include <stdbool.h>

// structures des livres
typedef struct Livre Livre;
typedef struct CelluleLivre CelluleLivre;
typedef struct ListeLivres ListeLivres;

// structures des Utilisateurs
typedef struct Utilisateur Utilisateur;
typedef struct CelluleUtilisateur CelluleUtilisateur;
typedef struct ListeUtilisateurs ListeUtilisateurs;

// structures des emprunts
typedef struct Emprunt Emprunt;
typedef struct CelluleEmprunt CelluleEmprunt;
typedef struct Listemprunts Listemprunts;

// structures des Dates
typedef struct Date Date;

// structures des Statistiques
typedef struct StatistiquesLivre StatistiquesLivre;

// Déclaration de l'énumération pour les choix du menu principal
typedef enum MenuChoice MenuChoice;

enum MenuChoice
{
    CHOIX_A = 'A',
    CHOIX_B = 'B',
    CHOIX_C = 'C',
    CHOIX_D = 'D',
    CHOIX_E = 'E',
    CHOIX_F = 'F',
    CHOIX_G = 'G',
    CHOIX_H = 'H',
    CHOIX_I = 'I',
    CHOIX_J = 'J',
    CHOIX_K = 'K',
    CHOIX_L = 'L',
    CHOIX_M = 'M',
    CHOIX_N = 'N',
    CHOIX_O = 'O',
    CHOIX_QUITTER = 'Q'
};
typedef struct Date
{
    int jour;
    int mois;
    int annee;
};

struct Livre
{
    int id;
    char titre[100];
    char auteur[100];
    int annee_publication;
    char genre[50];
    int nombre_exemplaires;
};

struct CelluleLivre
{
    Livre livre;
    CelluleLivre *suivant;
};
// Structure de contrôle pour la liste des livres
struct ListeLivres
{
    CelluleLivre *tete;
};

struct Utilisateur
{
    int id;
    char nom[100];
    char prenom[100];
    char adresse[200];
    char email[100];
    int telephone;
};

struct CelluleUtilisateur
{
    Utilisateur utilisateur;
    CelluleUtilisateur *suivant;
};
// Structure de contrôle pour la liste des utilisateurs
struct ListeUtilisateurs
{
    CelluleUtilisateur *tete;
};

struct Emprunt
{
    int id_emprunt;
    int id_utilisateur;
    int id_livre_emprunte;
    Date date_emprunt;
    Date date_retour_prevue;
    bool est_retourne;
};

struct CelluleEmprunt
{
    Emprunt emprunt;
    CelluleEmprunt *suivant;
};

struct Listemprunts
{
    CelluleEmprunt *tete;
};

struct StatistiquesLivre
{
    int id_livre;
    int nombre_emprunts;
    int nombre_retards;
    float taux_emprunts;
    float taux_retards;
};

// Affichage du menu principal

void printMainMenu();

//*********************************************************** GESTION DES LIVRES **********************************************************

void initialiserListeLivres(ListeLivres *liste);
Livre Enregistrementlivre(Livre livre);
void Ajouterlivre(ListeLivres *liste, Livre livre);
void afficherLivre(Livre livre);
void Afficherlistelivre(ListeLivres *listelivre);
bool livreExiste(ListeLivres *listeLivres, int idLivre);
Livre rechercherLivreParID(CelluleLivre *listeLivres, int idLivre);
void rechercherLivre(ListeLivres *listeLivres);
void diminuerExemplairesDisponibles(ListeLivres *listeLivres, int idLivre);
void supprimerLivre(ListeLivres *listeLivres, int idLivre);
void trierEtReecrireLivresParIdentifiant(ListeLivres *listeLivres);
void modifierLivre(ListeLivres *listeLivres, const char *nomFichierLivres);
void afficherLivresEmpruntesParUtilisateur(Listemprunts *listeEmprunts, ListeLivres *listeLivres);
int livreexiste(ListeLivres *ListeLivres, int idLivre);

//*********************************************************** GESTION DES UTILISATEURS **********************************************************
void initialiserListeutilisateurs(ListeUtilisateurs *liste);
Utilisateur Enregistrementutilisateur(Utilisateur utilisateur);
void Ajouterutilisateurs(ListeUtilisateurs *listeUtilisateurs, Utilisateur utilisateur);
void Afficherlisteutilisateurs(ListeUtilisateurs *listeUtilisateurs);
void supprimerUtilisateur(ListeUtilisateurs *listeUtilisateurs, int idUtilisateur);
int utilisateurExiste(ListeUtilisateurs *listeUtilisateurs, int idUtilisateur);
void trierEtReecrireUtilisateursParIdentifiant(ListeUtilisateurs *listeUtilisateurs);
void modifierUtilisateur(ListeUtilisateurs *listeUtilisateurs, const char *utilisateurs);
void utilisateursEmpruntantLivre(Listemprunts *listeEmprunts, ListeUtilisateurs *listeUtilisateurs);

//*********************************************************** GESTION DES EMPRUNTS **********************************************************

void initialiserListemprunts(Listemprunts *liste);
Emprunt Enregistrementemprunt(Emprunt emprunt);
void Ajouteremprunts(Listemprunts *liste, Emprunt emprunt, ListeUtilisateurs *listeUtilisateurs, ListeLivres *listeLivres);
void AfficherlisteEmprunts(Listemprunts *listemprunts);
void retournerLivre(Listemprunts *listemprunts, ListeLivres *listeLivres, const char *nomFichierEmprunts);
void augmenterExemplairesDisponibles(ListeLivres *listeLivres, int idLivre);
void supprimerEmprunt(Listemprunts *listeEmprunts, int idEmprunt);
void modifierEmprunt(Listemprunts *listeEmprunts, const char *emprunts);

//*********************************************************** SAUVEGARDE DES FICHIERS  **********************************************************

void sauvegarderListeLivres(ListeLivres *listeLivres, const char *livres);
void sauvegarderListeUtilisateurs(ListeUtilisateurs *listeUtilisateurs, const char *nomFichier);
void sauvegarderListeEmprunts(Listemprunts *listeEmprunts, const char *nomFichier);
void chargerListeLivres(ListeLivres *listeLivres, const char *nomFichier);
void chargerListeUtilisateurs(ListeUtilisateurs *listeUtilisateurs, const char *nomFichier);
void chargerListeEmprunts(Listemprunts *listeEmprunts, const char *emprunts, ListeLivres *listeLivres, ListeUtilisateurs *listeUtilisateurs);

//*********************************************************** SATISTIQUES BIBLIOTHEQUE  **********************************************************

void modifierElement(ListeLivres *listeLivres, ListeUtilisateurs *listeUtilisateurs, Listemprunts *listeEmprunts, const char *livres, const char *utilisateurs, const char *emprunts);
void statistiques(ListeLivres *listeLivres, ListeUtilisateurs *listeUtilisateurs, Listemprunts *listemprunts);
float calculerMoyenneEmpruntsParUtilisateur(Listemprunts *listeEmprunts, ListeUtilisateurs *listeUtilisateurs);
void afficherNombreExemplairesDisponibles(ListeLivres *listeLivres);
void afficherNombreEmprunts(Listemprunts *listemprunts);
void afficherNombreUtilisateurs(ListeUtilisateurs *listeUtilisateurs);
void afficherNombreLivres(ListeLivres *listeLivres);

#endif