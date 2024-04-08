#ifndef TOOLS_H
#define TOOLS_H
#include <stdbool.h>


// structures des livres 
typedef struct Livre Livre ;
typedef struct CelluleLivre CelluleLivre ;
typedef struct ListeLivres ListeLivres ;


// structures des Utilisateurs
typedef struct Utilisateur Utilisateur;
typedef struct CelluleUtilisateur CelluleUtilisateur ;
typedef struct ListeUtilisateurs ListeUtilisateurs ;

// structures des emprunts
typedef struct Emprunt Emprunt;
typedef struct CelluleEmprunt CelluleEmprunt;
typedef struct Listemprunts Listemprunts ;

// structures des Dates 
typedef struct Date Date;

// structures des Statistiques 

typedef struct StatistiquesLivre StatistiquesLivre;

//Affichage du menu principal

void printMainMenu() ;
// fonctions des livres 
void initialiserListeLivres(ListeLivres* liste);
Livre  Enregistrementlivre( Livre livre);
void Ajouterlivre(ListeLivres *liste, Livre livre);
void Afficherlistelivre(ListeLivres  *listelivre);
int affichernombretotallivrebibliotheque (ListeLivres *  liste);

// Fonction pour rechercher un livre par titre, auteur ou genre
void rechercherLivre(ListeLivres *listeLivres);
// Mettre à jour le nombre d'exemplaires disponibles dans la liste des livres
void diminuerExemplairesDisponibles(ListeLivres* listeLivres, int idLivre);
void supprimerLivre(ListeLivres *listeLivres, int idLivre);

// fonctions des utilisateurs 
void initialiserListeutilisateurs(ListeUtilisateurs *liste);
Utilisateur Enregistrementutilisateur( Utilisateur utilisateur);
void Ajouterutilisateurs(ListeUtilisateurs *listeUtilisateurs , Utilisateur utilisateur);
void Afficherlisteutilisateurs(ListeUtilisateurs *listeUtilisateurs);
 // Fonction pour supprimer un utilisateur de la liste des utilisateurs
void supprimerUtilisateur(ListeUtilisateurs *listeUtilisateurs, int idUtilisateur);
// fonctions des emprunts
void initialiserListemprunts(Listemprunts *liste );
Emprunt Enregistrementemprunt(Emprunt emprunt);
void Ajouteremprunts(Listemprunts *liste, Emprunt emprunt, ListeLivres *listeLivres);
void AfficherlisteEmprunts(Listemprunts *listemprunts);
void retournerLivre(Listemprunts* listeEmprunts, ListeLivres* listeLivres) ;
void augmenterExemplairesDisponibles(ListeLivres* listeLivres, int idLivre);
 // Fonction pour supprimer un emprunt de la liste des emprunts

void supprimerEmprunt(Listemprunts *listeEmprunts, int idEmprunt);

void sauvegarderListeLivres(ListeLivres *listeLivres, const char *livres);
void sauvegarderListeUtilisateurs(ListeUtilisateurs *listeUtilisateurs, const char *nomFichier);
void sauvegarderListeEmprunts(Listemprunts *listeEmprunts, const char *nomFichier);

void chargerListeLivres(ListeLivres *listeLivres, const char *nomFichier) ;
void chargerListeUtilisateurs(ListeUtilisateurs *listeUtilisateurs, const char *nomFichier);
void chargerListeEmprunts(Listemprunts *listeEmprunts, const char *emprunts, ListeLivres *listeLivres);



typedef struct Date {
    int jour;
    int mois;
    int annee;
} ;

typedef struct Livre {
    int id;
    char titre[100];
    char auteur[100];
    int annee_publication;
    char genre[50];
    int nombre_exemplaires;
    } ;

typedef struct CelluleLivre {
    Livre livre;
    CelluleLivre* suivant;
} ;
// Structure de contrôle pour la liste des livres
typedef struct ListeLivres {
    CelluleLivre * tete;
} ;

typedef struct Utilisateur {
    int id;
    char nom[100];
    char prenom[100];
    char adresse[200];
    char email[100];
    int telephone;
    
} ;

typedef struct CelluleUtilisateur {
    Utilisateur utilisateur ;
    CelluleUtilisateur * suivant;
} ;
// Structure de contrôle pour la liste des utilisateurs
typedef struct ListeUtilisateurs {
    CelluleUtilisateur * tete;
} ;

typedef struct Emprunt {
    int id_emprunt;
    int id_utilisateur;
    int id_livre_emprunte;
    Date date_emprunt;
    Date date_retour_prevue;
    bool est_retourne;
} ; 

typedef struct CelluleEmprunt{
    Emprunt emprunt ; 
    CelluleEmprunt *suivant;
};
typedef struct Listemprunts{
 CelluleEmprunt * tete ;
};

typedef struct StatistiquesLivre {
    int id_livre;
    int nombre_emprunts;
    int nombre_retards;
    float taux_emprunts;
    float taux_retards;
    // Ajoutez d'autres statistiques pertinentes selon vos besoins
} ;



#endif