#include "../src/tools.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include <math.h>
#include <stdbool.h>

// FONCTION POUR Affichage du menu principal

void printMainMenu() {
     system("clear");
      printf("               *********************************************************************************************************************\n");
	printf("               ***************************************   BIENVENUE DANS L' APPLICATION:  *******************************************\n");
	printf("               ***************************************      GESTION D'UNE BIBLIOTHEQUE   *******************************************\n");
        printf("               *********************************************************************************************************************\n\n");
        printf("           MENU PRINCIPAL :.\n");    
	printf("                - A. AJOUTER UN LIVRE.                                            -I. SUPPRIMMER UN LIVRE. \n" );                                 
    printf("                - B. AJOUTER UN UTILISATEUR.                                      -J. SUPPRIMMER UN UTILISATEUR. \n");
	printf("                - C. RECHERCHER UN LIVRE.                                         -K. SUPPRIMMER UN EMPRUNT. \n");
	printf("                - D. EMPRUNTER UN LIVRE.\n");
	printf("                - E. RETOURNER UN LIVRE .\n");
    printf("                - F. AFFICHER LA LISTE DES LIVRES .\n");
    printf("                - G. AFFICHER LA LISTE DES UTILISATEURS.                          - L. AFFICHER LE NOMBRE TOTAL DE LIVRES DE LA BIBLIOTHEQUE. \n");
    printf("                - H. AFFICHER LA LISTE DES EMPRUNTS.\n");
    printf("                                                             - Q QUITTER L'APPLICATION.\n"                       );

}
// fonction pour Initialiser la liste des  livres 

void initialiserListeLivres(ListeLivres*liste) {
    liste->tete = NULL;
   
} 

// fonction pour enregistrement d'un livre  
   Livre  Enregistrementlivre( Livre livre){
   Livre nouveaulivre ;
   printf("entrer l'identifiant du livre : \n ");
   scanf("%d",&nouveaulivre.id);
   printf("entrer le titre du livre : \n ");
   scanf("%s",nouveaulivre.titre);
   printf("entrer l'auteur du livre : \n ");
   scanf("%s",nouveaulivre.auteur);
   printf("entrer l'annee de publication  du livre : \n ");
   scanf("%d",&nouveaulivre.annee_publication);
   printf("entrer le genre   du livre : \n ");
   scanf("%s",nouveaulivre.genre);
   printf("entrer le nombre d'exemplaire du livre : \n ");
   scanf("%d",&nouveaulivre.nombre_exemplaires);

   return nouveaulivre ;
}

// fonction pour creer une nouvelle  cellule livre pour stoker le nouveau livre  et  Ajouter ce livre a la fin de la liste des livres de la  bibliothèque  

void Ajouterlivre(ListeLivres *liste, Livre livre) {
    CelluleLivre * nouveauLivre ;
    nouveauLivre =(CelluleLivre*)malloc(sizeof(CelluleLivre));

    nouveauLivre->livre = livre;
    nouveauLivre->suivant = NULL;

    if (liste->tete == NULL)
    {
        liste->tete = nouveauLivre;
        return;
    }
   CelluleLivre *list = liste->tete;
    while (list->suivant != NULL)
    {
        list = list->suivant;
    }
    list->suivant = nouveauLivre ;
    
    
    printf("Le Livre a ajouté dans la bibliotheque.\n");
    printf("\n");
}


//fonction pour  Afficher la liste des livres   de la  bibliothèque 

void Afficherlistelivre(ListeLivres  *listelivre)
 
{
    if (listelivre->tete == NULL)
    {
       printf("La liste des livres est vide.\n");
        return; 
    }
  CelluleLivre *p = listelivre->tete ;
  while ( p != NULL )
  {
   printf(" Numéro d'identification' : %d  | titre : %s  | Auteur : %s  | annee de publication: %d  | genre : %s  | nombre d'exemplaire : %d   \n", 
               p->livre.id, p->livre.titre, p->livre.auteur, p->livre.annee_publication,p->livre.genre,p->livre.nombre_exemplaires);
        p = p->suivant ;
  }
  

}

// Fonction pour afficher le nombre total de livres de la bibliotheque  

int affichernombretotallivrebibliotheque(ListeLivres *  liste){
if (liste == NULL)
{
   printf(" il n'y a aucun livre dans la bibliotheque pour l'instant\n");
   return;
}

 int nbre = 0;
 CelluleLivre * p = liste->tete  ;
 while (p!= NULL)
 {
    nbre++;
    p = p->suivant ;
 }
 return nbre  ;
 
}
// Fonction pour supprimer un livre dans la bibliotheque 

void supprimerLivre(ListeLivres *listeLivres, int idLivre) {
    // Vérifiez si la liste est vide
    if (listeLivres->tete == NULL) {
        printf("La liste des livres est vide.\n");
        return;
    }

    // Recherche du livre avec l'identifiant donné
    CelluleLivre *courant = listeLivres->tete;
    CelluleLivre *precedent = NULL;
    while (courant != NULL && courant->livre.id != idLivre) {
        precedent = courant;
        courant = courant->suivant;
    }

    if (courant == NULL) {
        printf("Aucun livre trouvé avec l'identifiant %d.\n", idLivre);
        return;
    }

    // Si le livre est trouvé, mettez à jour le nombre d'exemplaires disponibles
    courant->livre.nombre_exemplaires--;

    // Si le nombre d'exemplaires disponibles est devenu 0 après la mise à jour,
    // supprimez-le de la liste des livres
    if (courant->livre.nombre_exemplaires == 0) {
        if (precedent == NULL) {
            // Si le livre est en tête de liste
            listeLivres->tete = courant->suivant;
        } else {
            // Si le livre n'est pas en tête de liste
            precedent->suivant = courant->suivant;
        }
        printf("Livre avec l'identifiant %d supprimé avec succès.\n", idLivre);
        free(courant);
    } else {
        printf("Un exemplaire du livre avec l'identifiant %d a été supprimé.\n", idLivre);
    }

    // Maintenant, vous devriez réécrire le fichier avec la liste mise à jour
    FILE *fichier = fopen("livres.txt", "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    courant = listeLivres->tete;
    while (courant != NULL) {
        fprintf(fichier, "%d %s %d\n", courant->livre.id, courant->livre.titre, courant->livre.nombre_exemplaires);
        courant = courant->suivant;
    }

    fclose(fichier);
}

// Fonction pour rechercher un livre par titre, auteur ou genre 

void rechercherLivre(ListeLivres * listeLivres) {
    char recherche[30];
    // Demande à l'utilisateur de saisir le titre, l'auteur ou le genre du livre à rechercher
    printf("Veuillez entrer le titre, l'auteur ou le genre du livre à rechercher (maximum 29 caractères) : ");
    // Lecture de la saisie de l'utilisateur tout en s'assurant qu'elle ne dépasse pas la taille maximale autorisée
    if (scanf("%29s", recherche) != 1) {
        // Gestion de l'erreur si la saisie échoue
        printf("Erreur : Impossible de lire l'entrée.\n");
        // Nettoyage du reste de la ligne dans le tampon d'entrée
        while (getchar() != '\n');
        return;
    }

    // Nettoyage du reste de la ligne dans le tampon d'entrée
    while (getchar() != '\n');

    // Si la saisie est valide, procéder à la recherche
    printf("Résultats de la recherche :\n");

    CelluleLivre * liste ;
    liste = listeLivres->tete ;
    int trouve = 0;

    while (liste  != NULL) {
        // Vérifie si le titre, l'auteur ou le genre contient la chaîne de recherche
        if (strstr(liste ->livre.titre, recherche) != NULL ||
            strstr(liste ->livre.auteur, recherche) != NULL ||
            strstr(liste ->livre.genre, recherche) != NULL) {
            // Le livre correspond à la recherche
            printf("ID : %d\n", liste ->livre.id);
            printf("Titre : %s\n", liste ->livre.titre);
            printf("Auteur : %s\n", liste ->livre.auteur);
            printf("Genre : %s\n", liste ->livre.genre);
            printf("Nombre d'exemplaires : %d\n\n", liste->livre.nombre_exemplaires);
            trouve = 1;
        }
        liste  = liste ->suivant;
    }

    if (!trouve) {
        printf("Aucun livre trouvé pour la recherche : %s\n", recherche);
    }
} 

//Fonction de retour d'un livre emprunté

void retournerLivre(Listemprunts* listeEmprunts, ListeLivres* listeLivres) {
    int idLivre;

    // Demande à l'utilisateur de saisir l'identifiant du livre à retourner
    printf("Veuillez entrer l'identifiant du livre à retourner : ");

    // Lecture de l'entrée de l'utilisateur pour l'identifiant du livre
    if (scanf("%d", &idLivre) != 1) {
        // Gestion de l'erreur si la saisie échoue
        printf("Erreur : Entrée invalide pour l'identifiant du livre.\n");
        // Nettoyage du reste de la ligne dans le tampon d'entrée
        while (getchar() != '\n');
        return;
    }

    // Nettoyage du reste de la ligne dans le tampon d'entrée
    while (getchar() != '\n');

    // Recherche de l'emprunt correspondant au livre dans la liste des emprunts
    CelluleEmprunt* courant = listeEmprunts->tete;
    CelluleEmprunt* empruntPrecedent = NULL;
    while (courant != NULL && courant->emprunt.id_livre_emprunte != idLivre) {
        empruntPrecedent = courant;
        courant = courant->suivant;
    }

    if (courant != NULL) {
        // L'emprunt correspondant au livre est trouvé dans la liste des emprunts
        if (courant->emprunt.est_retourne) {
            printf("Erreur : Ce livre est déjà retourné.\n");
        } else {
            // Marquez le livre comme retourné dans l'emprunt
            courant->emprunt.est_retourne = true;

            // Mettez à jour le nombre d'exemplaires disponibles dans la liste des livres
            augmenterExemplairesDisponibles(listeLivres, idLivre);

            // Affichez un message de confirmation
            printf("Le livre avec l'identifiant %d a été retourné avec succès.\n", idLivre);

            // Supprimez le nœud de la liste des emprunts
            if (empruntPrecedent == NULL) {
                listeEmprunts->tete = courant->suivant;
            } else {
                empruntPrecedent->suivant = courant->suivant;
            }
            free(courant);
        }
    } else {
        // Le livre n'est pas trouvé dans la liste des emprunts
        printf("Erreur : Le livre avec l'identifiant %d n'est pas emprunté ou n'existe pas.\n", idLivre);
    }
}

// Fonction pour augmenter le nombre d'exemplaires disponibles pour un livre donné

void augmenterExemplairesDisponibles(ListeLivres* listeLivres, int idLivre) {
    // Parcourir la liste des livres pour trouver le livre correspondant à l'identifiant idLivre
    CelluleLivre* courant = listeLivres->tete;
    while (courant != NULL && courant->livre.id != idLivre) {
        courant = courant->suivant;
    }

    // Si le livre est trouvé, incrémenter le nombre d'exemplaires disponibles
    if (courant != NULL) {
        courant->livre.nombre_exemplaires++;
    } else {
        // Gérer le cas où le livre n'est pas trouvé (peut-être une erreur)
        printf("Erreur : Le livre avec l'identifiant %d n'existe pas dans la liste des livres.\n", idLivre);
    }
}

//     Fonction pour initialisation de  la liste des utilisateurs
void initialiserListeutilisateurs(ListeUtilisateurs *liste) {
    liste->tete = NULL;
   
}

//  Fonction pour enregistrement d'un utilisateur

Utilisateur Enregistrementutilisateur( Utilisateur utilisateur){
 Utilisateur util ;

 printf("entrer l'identifiant de l'utilisateur \n");
 scanf("%d",&util.id );
 printf("entrer le nom  de l'utilisateur \n");
 scanf("%s",util.nom );
 printf("entrer le prenom  de l'utilisateur \n");
 scanf("%s",util.prenom );
 printf("entrer l'adresse  de l'utilisateur \n");
 scanf("%s",util.adresse );
 printf("entrer l'adrsesse mail de l'utilisateur \n");
 scanf("%s",util.email );
 printf("entrer le numero de telephone  de l'utilisateur \n");
 scanf("%d",&util.telephone );

 return util;
}
// Fonction pour ajouter un utilisateur 

void Ajouterutilisateurs(ListeUtilisateurs *listeUtilisateurs , Utilisateur utilisateur){
CelluleUtilisateur *nouveauutilisateur;
nouveauutilisateur =(CelluleUtilisateur*) malloc(sizeof(CelluleUtilisateur));
// Affecter les données du nouvel utilisateur à la nouvelle cellule
nouveauutilisateur->utilisateur = utilisateur;
// Mettre à jour les pointeurs pour ajouter le nouvel utilisateur à la fin de la liste
nouveauutilisateur->suivant = NULL ;  // La nouvelle cellule sera la dernière de la liste
// Si la liste est vide, la nouvelle cellule devient la tête de liste
if (listeUtilisateurs->tete == NULL)
{
    listeUtilisateurs->tete = nouveauutilisateur ;
    return;
}
// Sinon, parcourir la liste jusqu'à la dernière cellule
CelluleUtilisateur *liste = listeUtilisateurs->tete;
while (liste->suivant != NULL)
{
   liste = liste->suivant;
}
 // Ajouter la nouvelle cellule à la fin de la liste
liste->suivant = nouveauutilisateur;

printf("L'utilisateur a été ajouté dans la liste des utilisateurs.\n");
}

//  Fonction pour Afficher la liste des UTILISATEURS

 void Afficherlisteutilisateurs(ListeUtilisateurs *listeUtilisateurs){
    // Vérifier si la liste est vide
    if (listeUtilisateurs->tete == NULL)
    {
       printf("La liste des utilisateurs est vide.\n");
        return; 
    }
    // Parcourir la liste des utilisateurs et afficher les données de chaque utilisateur
    printf("la liste des utilisateurs de la  bibliotheque   :\n");
    CelluleUtilisateur * liste ;
    liste = listeUtilisateurs->tete ; 
    while (liste != NULL)
    {
   printf(" Numéro d'identification' : %d | nom : %s | prenom : %s | adresse : %s  | email : %s  | telephone : %d   \n", 
               liste->utilisateur.id, liste->utilisateur.nom, liste->utilisateur.prenom, liste->utilisateur.adresse,liste->utilisateur.email,liste->utilisateur.telephone);
        liste = liste->suivant ;
    }
    
    
 }

 // Fonction pour supprimer un utilisateur de la liste des utilisateurs

void supprimerUtilisateur(ListeUtilisateurs *listeUtilisateurs, int idUtilisateur) {
    // Vérifier si la liste est vide
    if (listeUtilisateurs->tete == NULL) {
        printf("La liste des utilisateurs est vide.\n");
        return;
    }

    // Recherche de l'utilisateur avec l'identifiant donné
    CelluleUtilisateur *courant = listeUtilisateurs->tete;
    CelluleUtilisateur *precedent = NULL;
    while (courant != NULL && courant->utilisateur.id != idUtilisateur) {
        precedent = courant;
        courant = courant->suivant;
    }

    // Vérifier si l'utilisateur a été trouvé
    if (courant == NULL) {
        printf("Aucun utilisateur trouvé avec l'identifiant %d.\n", idUtilisateur);
        return;
    }

    // Supprimer l'utilisateur de la liste
    if (precedent == NULL) {
        // Si l'utilisateur est en tête de liste
        listeUtilisateurs->tete = courant->suivant;
    } else {
        // Si l'utilisateur n'est pas en tête de liste
        precedent->suivant = courant->suivant;
    }

    // Libérer la mémoire de la cellule de l'utilisateur supprimé
    free(courant);

    printf("Utilisateur avec l'identifiant %d supprimé avec succès.\n", idUtilisateur);

    // Maintenant, vous devriez réécrire le fichier avec la liste mise à jour
    FILE *fichier = fopen("utilisateurs.txt", "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    courant = listeUtilisateurs->tete;
    while (courant != NULL) {
        fprintf(fichier, "%d %s\n", courant->utilisateur.id, courant->utilisateur.nom);
        courant = courant->suivant;
    }

    fclose(fichier);
}

//  Fonction pour initialiser liste des emprunts 

void initialiserListemprunts(Listemprunts *liste ) {
 liste->tete = NULL;
}

//  Fonction pourenregistrement d'un emprunt

Emprunt Enregistrementemprunt(Emprunt emprunt){

Emprunt nouvelemprunt ;

printf("entrer l'identifiant de emprunt a éffectué: \n  ");  
scanf("%d",&nouvelemprunt.id_emprunt);
printf("entrer l'identifiant du livre a emprunté :\n  ");  
scanf("%d",&nouvelemprunt.id_livre_emprunte);
printf("entrer l'identifiant de l'utilisateur qui va emprunté ce livre : \n  ");  
scanf("%d",&nouvelemprunt.id_utilisateur);
printf("saisir  la date de l'emprunt  du livre : \n  ");  
printf("jour :   "); 
scanf("%d",&nouvelemprunt.date_emprunt.jour);
printf("mois:    "); 
scanf("%d",&nouvelemprunt.date_emprunt.mois);
printf("anneé :   "); 
scanf("%d",&nouvelemprunt.date_emprunt.annee);
printf("saisir  la date de retour prevue  du livre  \n  ");  
printf("jour :   "); 
scanf("%d",&nouvelemprunt.date_retour_prevue.jour);
printf("mois:     "); 
scanf("%d",&nouvelemprunt.date_retour_prevue.mois);
printf("anneé :   "); 
scanf("%d",&nouvelemprunt.date_retour_prevue.annee);

 return nouvelemprunt ;
}

//  Fonction pour Mettre à jour le nombre d'exemplaires disponibles dans la liste des livres

void diminuerExemplairesDisponibles(ListeLivres* listeLivres, int idLivre) {
    // Parcourir la liste des livres pour trouver le livre correspondant à l'identifiant idLivre
    CelluleLivre* courant = listeLivres->tete;
    while (courant != NULL && courant->livre.id != idLivre) {
        courant = courant->suivant;
    }
 // Si le livre est trouvé, décrémenter le nombre d'exemplaires disponibles
    if (courant != NULL) {
        // Vérifier si des exemplaires sont disponibles avant de décrémenter
        if (courant->livre.nombre_exemplaires > 0) {
            courant->livre.nombre_exemplaires--;
        } else {
            printf("Erreur : Aucun exemplaire disponible pour ce livre.\n");
        }
    } else {
             // Gérer le cas où le livre n'est pas trouvé (peut-être une erreur)
        printf("Erreur : Le livre avec l'identifiant %d n'existe pas dans la liste des livres.\n", idLivre);
    }
}


//  Fonction pour Ajout  d'un emprunt

void Ajouteremprunts(Listemprunts *liste, Emprunt emprunt, ListeLivres *listeLivres){
    // Allouer de la mémoire pour la nouvelle cellule d'emprunt
    CelluleEmprunt *nouvellecell = (CelluleEmprunt*)malloc(sizeof(CelluleEmprunt));
    if (nouvellecell == NULL) {
        printf("Erreur: Impossible d'allouer de la mémoire pour la nouvelle cellule d'emprunt.\n");
        return;
    }

    // Remplir les informations de la nouvelle cellule d'emprunt
    nouvellecell->emprunt = emprunt;
    nouvellecell->suivant= NULL;

    // Insérer la nouvelle cellule d'emprunt dans la liste des emprunts
    if (liste->tete == NULL) {
        liste->tete = nouvellecell;
    } else {
        CelluleEmprunt *courant = liste->tete;
        while (courant->suivant != NULL) {
            courant = courant->suivant;
        }
        courant->suivant = nouvellecell;
    }

    // Mettre à jour le nombre d'exemplaires disponibles du livre emprunté
    diminuerExemplairesDisponibles(listeLivres, emprunt.id_livre_emprunte);

    printf("Emprunt ajouté avec succès.\n");
}

//  Fonction pour afficher la liste des  emprunts effectués
void AfficherlisteEmprunts(Listemprunts *listemprunts){

    if (listemprunts->tete == NULL)
    {
        printf("la liste des emprunts est vide\n");
    }
  
     CelluleEmprunt * liste ;
    liste = listemprunts->tete ; 
    while (liste != NULL)
    {
   printf(" Numéro d'identification de l'emprunt  : %d | Numéro d'identification de l'utilisateur  : %d |Numéro d'identification du livre emprunté: %d |date de l'emprunt: jour : %d  mois: %d annee: %d  |date de retour prevue: jour : %d mois :%d annee: %d   \n", 
               liste->emprunt.id_emprunt, liste->emprunt.id_utilisateur, liste->emprunt.id_livre_emprunte, liste->emprunt.date_emprunt.jour,liste->emprunt.date_emprunt.mois,liste->emprunt.date_emprunt.annee,
               liste->emprunt.date_retour_prevue.jour,liste->emprunt.date_retour_prevue.mois,liste->emprunt.date_retour_prevue.annee);
        liste = liste->suivant ;
    }
    
   
 }
 // Fonction pour supprimer un emprunt de la liste des emprunts

void supprimerEmprunt(Listemprunts *listeEmprunts, int idEmprunt) {
    // Vérifier si la liste est vide
    if (listeEmprunts->tete == NULL) {
        printf("La liste des emprunts est vide.\n");
        return;
    }

    // Recherche de l'emprunt avec l'identifiant donné
    CelluleEmprunt *courant = listeEmprunts->tete;
    CelluleEmprunt *precedent = NULL;
    while (courant != NULL && courant->emprunt.id_emprunt != idEmprunt) {
        precedent = courant;
        courant = courant->suivant;
    }

    // Vérifier si l'emprunt a été trouvé
    if (courant == NULL) {
        printf("Aucun emprunt trouvé avec l'identifiant %d.\n", idEmprunt);
        return;
    }

    // Supprimer l'emprunt de la liste
    if (precedent == NULL) {
        // Si l'emprunt est en tête de liste
        listeEmprunts->tete = courant->suivant;
    } else {
        // Si l'emprunt n'est pas en tête de liste
        precedent->suivant = courant->suivant;
    }

    // Libérer la mémoire de la cellule de l'emprunt supprimé
    free(courant);

    printf("Emprunt avec l'identifiant %d supprimé avec succès.\n", idEmprunt);

    // Maintenant, vous devriez réécrire le fichier avec la liste mise à jour
    FILE *fichier = fopen("emprunts.txt", "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    courant = listeEmprunts->tete;
    while (courant != NULL) {
        fprintf(fichier, "%d %d %d %d %d %d\n", courant->emprunt.id_emprunt, courant->emprunt.id_utilisateur, courant->emprunt.id_livre_emprunte, courant->emprunt.date_emprunt.jour, courant->emprunt.date_emprunt.mois, courant->emprunt.date_emprunt.annee);
        courant = courant->suivant;
    }

    fclose(fichier);
}


 // Fonction pour Enregistrer la liste des livres dans un fichier : 

 void sauvegarderListeLivres(ListeLivres *listeLivres, const char *livres) {
    FILE *fichier = fopen(livres, "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", livres);
        return;
    }

    CelluleLivre *courant = listeLivres->tete;
    while (courant != NULL) {
        fprintf(fichier, "%d %s %s %d %s %d\n", courant->livre.id, courant->livre.titre, courant->livre.auteur,
                courant->livre.annee_publication, courant->livre.genre, courant->livre.nombre_exemplaires);
        courant = courant->suivant;
    }

    fclose(fichier);
}

//  Fonction pour Enregistrer la liste des utilisateurs dans un fichier :

void sauvegarderListeUtilisateurs(ListeUtilisateurs *listeUtilisateurs, const char *utilisateurs) {
    FILE *fichier = fopen(utilisateurs, "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", utilisateurs);
        return;
    }

    CelluleUtilisateur *courant = listeUtilisateurs->tete;
    while (courant != NULL) {
        fprintf(fichier, "%d %s %s %s %s %d\n", courant->utilisateur.id, courant->utilisateur.nom,
                courant->utilisateur.prenom, courant->utilisateur.adresse, courant->utilisateur.email,
                courant->utilisateur.telephone);
        courant = courant->suivant;
    }

    fclose(fichier);
}

//Enregistrer la liste des emprunts dans un fichier :

void sauvegarderListeEmprunts(Listemprunts *listeEmprunts, const char *emprunts) {
    FILE *fichier = fopen(emprunts, "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", emprunts);
        return;
    }

    CelluleEmprunt *courant = listeEmprunts->tete;
    while (courant != NULL) {
        fprintf(fichier, "%d %d %d %d %d %d %d %d %d\n", courant->emprunt.id_emprunt, courant->emprunt.id_utilisateur,
                courant->emprunt.id_livre_emprunte, courant->emprunt.date_emprunt.jour,
                courant->emprunt.date_emprunt.mois, courant->emprunt.date_emprunt.annee,
                courant->emprunt.date_retour_prevue.jour, courant->emprunt.date_retour_prevue.mois,
                courant->emprunt.date_retour_prevue.annee);
        courant = courant->suivant;
    }
     
    fclose(fichier);
}

// Fonction pour  Charger la liste des livres :

void chargerListeLivres(ListeLivres *listeLivres, const char *livres) {
    FILE *fichier = fopen(livres, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", livres);
        return;
    }

    Livre livre;
    while (fscanf(fichier, "%d %99s %99s %d %49s %d", &livre.id, livre.titre, livre.auteur,
                  &livre.annee_publication, livre.genre, &livre.nombre_exemplaires) == 6) {
        Ajouterlivre(listeLivres, livre);
    }

    fclose(fichier);
}

// Fonction pour Charger la liste des utilisateurs :

void chargerListeUtilisateurs(ListeUtilisateurs *listeUtilisateurs, const char *utilisateurs) {
    FILE *fichier = fopen(utilisateurs, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", utilisateurs);
        return;
    }

    Utilisateur utilisateur;
    while (fscanf(fichier, "%d %99s %99s %199s %99s %d", &utilisateur.id, utilisateur.nom, utilisateur.prenom,
                  utilisateur.adresse, utilisateur.email, &utilisateur.telephone) == 6) {
        Ajouterutilisateurs(listeUtilisateurs, utilisateur);
    }
    
    fclose(fichier);
}
// Fonction pour  Charger la liste des emprunts :
void chargerListeEmprunts(Listemprunts *listeEmprunts, const char *emprunts, ListeLivres *listeLivres) {
    FILE *fichier = fopen(emprunts, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", emprunts);
        return;
    }

    Emprunt emprunt;
    while (fscanf(fichier, "%d %d %d %d %d %d %d %d %d", &emprunt.id_emprunt, &emprunt.id_utilisateur,
                  &emprunt.id_livre_emprunte, &emprunt.date_emprunt.jour, &emprunt.date_emprunt.mois,
                  &emprunt.date_emprunt.annee, &emprunt.date_retour_prevue.jour, &emprunt.date_retour_prevue.mois,
                  &emprunt.date_retour_prevue.annee) == 9) {
                    
        Ajouteremprunts(listeEmprunts, emprunt, listeLivres);
    }
    
    fclose(fichier);
}