#include "../src/tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <stdbool.h>

// FONCTION POUR Affichage du menu principal

void printMainMenu()
{
    system("clear");
    printf("               *********************************************************************************************************************\n");
    printf("               ***************************************   BIENVENUE DANS L' APPLICATION:  *******************************************\n");
    printf("               ***************************************      GESTION D'UNE BIBLIOTHEQUE   *******************************************\n");
    printf("               *********************************************************************************************************************\n\n");
    printf("                                                      MENU PRINCIPAL : \n");
    printf("                - A. AJOUTER UN LIVRE.                                            -I. SUPPRIMMER UN LIVRE (EXEMPLAIRE). \n");
    printf("                - B. AJOUTER UN UTILISATEUR.                                      -J. SUPPRIMMER UN UTILISATEUR. \n");
    printf("                - C. RECHERCHER UN LIVRE.                                         -K. SUPPRIMMER UN EMPRUNT. \n");
    printf("                - D. EMPRUNTER UN LIVRE.                                          -L. MODIFIER LES INFORMATIONS (D'UN LIVRE , D'UN UTILISATEUR ,D'UN EMPRUNT). \n");
    printf("                - E. RETOURNER UN LIVRE .                                         -M. LISTE DE LIVRE EMPRUNTE PAR UN UTILISATEUR . \n");
    printf("                - F. AFFICHER LA LISTE DES LIVRES .                               -N. LISTE DES UTILISATEURS AYANT EMPRUNTES UN LIVRE   \n");
    printf("                - G. AFFICHER LA LISTE DES UTILISATEURS.                          -O. STATISTIQUES DIVERS DE LA BIBLIOTHEQUE . \n");
    printf("                - H. AFFICHER LA LISTE DES EMPRUNTS.\n");
    printf("                                                       - Q QUITTER L'APPLICATION.\n");
}
// fonction pour Initialiser la liste des  livres

void initialiserListeLivres(ListeLivres *liste)
{
    liste->tete = NULL;
}

// fonction pour enregistrement d'un livre
Livre Enregistrementlivre(Livre livre)
{
    Livre nouveaulivre;
    printf("entrer l'identifiant du livre : \n ");
    scanf("%d", &nouveaulivre.id);
    printf("entrer le titre du livre : \n ");
    scanf("%s", nouveaulivre.titre);
    printf("entrer l'auteur du livre : \n ");
    scanf("%s", nouveaulivre.auteur);
    printf("entrer l'annee de publication  du livre : \n ");
    scanf("%d", &nouveaulivre.annee_publication);
    printf("entrer le genre   du livre : \n ");
    scanf("%s", nouveaulivre.genre);
    printf("entrer le nombre d'exemplaire du livre : \n ");
    scanf("%d", &nouveaulivre.nombre_exemplaires);

    return nouveaulivre;
}

// fonction pour creer une nouvelle  cellule livre pour stoker le nouveau livre
// et  Ajouter ce livre a la fin de la liste des livres de la  bibliothèque

void Ajouterlivre(ListeLivres *liste, Livre livre)
{

    CelluleLivre *nouveauLivre;
    nouveauLivre = (CelluleLivre *)malloc(sizeof(CelluleLivre));

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
    list->suivant = nouveauLivre;

    printf("Le Livre a ajouté dans la bibliotheque.\n");
    printf("\n");
}

// fonction pour  Afficher un livre de la  bibliothèque

void afficherLivre(Livre livre)
{

    printf(" Numéro d'identification' : %d  | titre : %s  | Auteur : %s  | annee de publication: %d  | genre : %s  | nombre d'exemplaire : %d   \n",
           livre.id, livre.titre, livre.auteur, livre.annee_publication, livre.genre, livre.nombre_exemplaires);
}
// fonction pour  Afficher la liste des livres   de la  bibliothèque

void Afficherlistelivre(ListeLivres *listelivre)
{
    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|                                    Informations des  livres                                                                         |\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");

    if (listelivre->tete == NULL)
    {
        printf("La liste des livres est vide.\n");
        return;
    }
    CelluleLivre *p = listelivre->tete;
    while (p != NULL)
    {
        printf(" Numéro d'identification' : %d  | titre : %s  | Auteur : %s  | annee de publication: %d  | genre : %s  | nombre d'exemplaire : %d   \n",
               p->livre.id, p->livre.titre, p->livre.auteur, p->livre.annee_publication, p->livre.genre, p->livre.nombre_exemplaires);
        p = p->suivant;
    }
}

// Fonction pour supprimer un livre dans la bibliotheque

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Supprime un livre de la liste et réécrit le fichier des livres
void supprimerLivre(ListeLivres *listeLivres, int idLivre)
{
    if (listeLivres == NULL || listeLivres->tete == NULL)
    {
        printf("La liste des livres est vide.\n");
        return;
    }

    // Recherche du livre à supprimer dans la liste
    CelluleLivre *precedent = NULL;
    CelluleLivre *courant = listeLivres->tete;
    while (courant != NULL && courant->livre.id != idLivre)
    {
        precedent = courant;
        courant = courant->suivant;
    }

    // Si le livre n'est pas trouvé dans la liste
    if (courant == NULL)
    {
        printf("Aucun livre trouvé avec l'identifiant %d.\n", idLivre);
        return;
    }

    // Décrémentation du nombre d'exemplaires du livre
    if (courant->livre.nombre_exemplaires > 0)
    {
        courant->livre.nombre_exemplaires--;
    }
    else
    {
        printf("Le livre avec l'identifiant %d n'a plus d'exemplaires disponibles.\n", idLivre);
        return;
    }

    // Si le nombre d'exemplaires atteint 0 après décrémentation, supprimer le livre de la liste
    if (courant->livre.nombre_exemplaires == 0)
    {
        // Suppression du livre de la liste
        if (precedent == NULL)
        {
            // Si le livre à supprimer est en tête de liste
            listeLivres->tete = courant->suivant;
        }
        else
        {
            // Si le livre à supprimer est au milieu ou à la fin de la liste
            precedent->suivant = courant->suivant;
        }
        free(courant); // Libération de la mémoire occupée par la cellule du livre supprimé
    }

    // Réécriture du fichier des livres avec la nouvelle liste de livres
    FILE *fichierLivres = fopen("livres.txt", "w");
    if (fichierLivres == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier livres.txt en écriture.\n");
        return;
    }

    // Parcours de la liste mise à jour et réécriture dans le fichier
    courant = listeLivres->tete;
    while (courant != NULL)
    {
        fprintf(fichierLivres, "%d %s %s %d %s %d\n", courant->livre.id,
                courant->livre.titre, courant->livre.auteur,
                courant->livre.annee_publication, courant->livre.genre,
                courant->livre.nombre_exemplaires);
        courant = courant->suivant;
    }

    // Fermeture du fichier
    fclose(fichierLivres);
    printf("Le livre avec l'identifiant %d a été supprimé avec succès.\n", idLivre);
}

// Fonction pour rechercher un livre par titre, auteur ou genre

void rechercherLivre(ListeLivres *listeLivres)
{
    int choix;
    printf("Voulez-vous rechercher par titre, auteur, genre ou identifiant ?\n");
    printf("1. Titre\n");
    printf("2. Auteur\n");
    printf("3. Genre\n");
    printf("4. Identifiant\n");
    printf("Votre choix : ");
    scanf("%d", &choix);
    while (getchar() != '\n')
        ; // Nettoyage du reste de la ligne dans le tampon d'entrée

    char recherche[30];
    // Demande à l'utilisateur de saisir le critère de recherche
    printf("Veuillez entrer le critère de recherche (maximum 29 caractères) : ");
    // Lecture de la saisie de l'utilisateur tout en s'assurant qu'elle ne dépasse pas la taille maximale autorisée
    if (scanf("%29s", recherche) != 1)
    {
        // Gestion de l'erreur si la saisie échoue
        printf("Erreur : Impossible de lire l'entrée.\n");
        // Nettoyage du reste de la ligne dans le tampon d'entrée
        while (getchar() != '\n')
            ;
        return;
    }

    // Nettoyage du reste de la ligne dans le tampon d'entrée
    while (getchar() != '\n')
        ;

    // Si la saisie est valide, procéder à la recherche
    printf("Résultats de la recherche :\n");

    CelluleLivre *liste;
    liste = listeLivres->tete;
    int trouve = 0;

    while (liste != NULL)
    {
        // Effectuer la recherche en fonction du critère choisi par l'utilisateur
        if (choix == 1 && strstr(liste->livre.titre, recherche) != NULL)
        {
            afficherLivre(liste->livre);
            trouve = 1;
        }
        else if (choix == 2 && strstr(liste->livre.auteur, recherche) != NULL)
        {
            afficherLivre(liste->livre);
            trouve = 1;
        }
        else if (choix == 3 && strstr(liste->livre.genre, recherche) != NULL)
        {
            afficherLivre(liste->livre);
            trouve = 1;
        }
        else if (choix == 4 && liste->livre.id == atoi(recherche))
        {
            afficherLivre(liste->livre);
            trouve = 1;
        }
        liste = liste->suivant;
    }

    if (!trouve)
    {
        printf("Aucun livre trouvé pour la recherche : %s\n", recherche);
    }
}

// Fonction pour retourner un livre emprunté
// Fonction pour retourner un livre
void retournerLivre(Listemprunts *listemprunts, ListeLivres *listeLivres, const char *emprunts)
{
    int id_livre_retourner;

    // Demander à l'utilisateur de saisir l'identifiant du livre à retourner
    printf("Entrez l'identifiant du livre à retourner : ");
    scanf("%d", &id_livre_retourner);

    // Consommer le caractère de saut de ligne restant
    getchar();

    // Rechercher et supprimer l'emprunt associé au livre retourné
    CelluleEmprunt *precedent = NULL;
    CelluleEmprunt *courantEmprunt = listemprunts->tete;
    while (courantEmprunt != NULL)
    {
        if (courantEmprunt->emprunt.id_livre_emprunte == id_livre_retourner)
        {
            // Supprimer l'emprunt de la liste des emprunts
            if (precedent != NULL)
            {
                precedent->suivant = courantEmprunt->suivant;
            }
            else
            {
                listemprunts->tete = courantEmprunt->suivant;
            }
            free(courantEmprunt);
            break;
        }
        precedent = courantEmprunt;
        courantEmprunt = courantEmprunt->suivant;
    }

    // Mettre à jour le fichier des emprunts pour refléter la suppression
    FILE *fichierEmprunts = fopen(emprunts, "w");
    if (fichierEmprunts == NULL)
    {
        printf("Erreur : Impossible d'ouvrir le fichier des emprunts.\n");
        return;
    }

    courantEmprunt = listemprunts->tete;
    while (courantEmprunt != NULL)
    {
        fprintf(fichierEmprunts, "%d %d %d %d/%d/%d %d/%d/%d %d\n",
                courantEmprunt->emprunt.id_emprunt,
                courantEmprunt->emprunt.id_utilisateur,
                courantEmprunt->emprunt.id_livre_emprunte,
                courantEmprunt->emprunt.date_emprunt.jour,
                courantEmprunt->emprunt.date_emprunt.mois,
                courantEmprunt->emprunt.date_emprunt.annee,
                courantEmprunt->emprunt.date_retour_prevue.jour,
                courantEmprunt->emprunt.date_retour_prevue.mois,
                courantEmprunt->emprunt.date_retour_prevue.annee,
                courantEmprunt->emprunt.est_retourne ? 1 : 0);

        courantEmprunt = courantEmprunt->suivant;
    }

    fclose(fichierEmprunts);

    // Parcourir la liste des livres pour trouver celui à retourner
    CelluleLivre *courantLivre = listeLivres->tete;
    while (courantLivre != NULL)
    {
        if (courantLivre->livre.id == id_livre_retourner)
        {
            // Incrémenter le nombre d'exemplaires disponibles
            courantLivre->livre.nombre_exemplaires++;
            printf("Le livre avec l'ID %d a été retourné avec succès.\n", id_livre_retourner);
            return;
        }
        courantLivre = courantLivre->suivant;
    }

    printf("Erreur : Le livre avec l'ID %d n'a pas été trouvé dans la liste des livres.\n", id_livre_retourner);
}

// Fonction pour rechercher un livre par son ID dans la liste des livres
Livre rechercherLivreParID(CelluleLivre *listeLivres, int idLivre)
{
    CelluleLivre *courant = listeLivres;

    // Parcourir la liste des livres
    while (courant != NULL)
    {
        if (courant->livre.id == idLivre)
        {
            // Le livre avec l'ID spécifié a été trouvé
            return (courant->livre);
        }
        courant = courant->suivant;
    }

    // Le livre avec l'ID spécifié n'a pas été trouvé
    return;
}

// Fonction pour augmenter le nombre d'exemplaires disponibles pour un livre donné

void augmenterExemplairesDisponibles(ListeLivres *listeLivres, int idLivre)
{
    // Parcourir la liste des livres pour trouver le livre correspondant à l'identifiant idLivre
    CelluleLivre *courant = listeLivres->tete;
    while (courant != NULL && courant->livre.id != idLivre)
    {
        courant = courant->suivant;
    }

    // Si le livre est trouvé, incrémenter le nombre d'exemplaires disponibles
    if (courant != NULL)
    {
        courant->livre.nombre_exemplaires++;
    }
    else
    {
        // Gérer le cas où le livre n'est pas trouvé (peut-être une erreur)
        printf("Erreur : Le livre avec l'identifiant %d n'existe pas dans la liste des livres.\n", idLivre);
    }
}

//     Fonction pour initialisation de  la liste des utilisateurs
void initialiserListeutilisateurs(ListeUtilisateurs *liste)
{
    liste->tete = NULL;
}

//  Fonction pour enregistrement d'un utilisateur

Utilisateur Enregistrementutilisateur(Utilisateur utilisateur, CelluleUtilisateur *listeUtilisateurs)
{
    Utilisateur util;

    printf("entrer l'identifiant de l'utilisateur \n");
    scanf("%d", &util.id);
    printf("entrer le nom  de l'utilisateur \n");
    scanf("%s", util.nom);
    printf("entrer le prenom  de l'utilisateur \n");
    scanf("%s", util.prenom);
    printf("entrer l'adresse  de l'utilisateur \n");
    scanf("%s", util.adresse);
    printf("entrer l'adrsesse mail de l'utilisateur \n");
    scanf("%s", util.email);
    printf("entrer le numero de telephone  de l'utilisateur \n");
    scanf("%d", &util.telephone);

    return util;
}

// Fonction pour ajouter un utilisateur

void Ajouterutilisateurs(ListeUtilisateurs *listeUtilisateurs, Utilisateur utilisateur)
{
    CelluleUtilisateur *nouveauutilisateur;
    nouveauutilisateur = (CelluleUtilisateur *)malloc(sizeof(CelluleUtilisateur));
    // Affecter les données du nouvel utilisateur à la nouvelle cellule
    nouveauutilisateur->utilisateur = utilisateur;
    // Mettre à jour les pointeurs pour ajouter le nouvel utilisateur à la fin de la liste
    nouveauutilisateur->suivant = NULL; // La nouvelle cellule sera la dernière de la liste
    // Si la liste est vide, la nouvelle cellule devient la tête de liste
    if (listeUtilisateurs->tete == NULL)
    {
        listeUtilisateurs->tete = nouveauutilisateur;
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

void Afficherlisteutilisateurs(ListeUtilisateurs *listeUtilisateurs)
{
    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|                                    Informations des  Utilisateurs                                                                         |\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");

    // Vérifier si la liste est vide
    if (listeUtilisateurs->tete == NULL)
    {
        printf("La liste des utilisateurs est vide.\n");
        return;
    }
    // Parcourir la liste des utilisateurs et afficher les données de chaque utilisateur
    printf("la liste des utilisateurs de la  bibliotheque   :\n");
    CelluleUtilisateur *liste;
    liste = listeUtilisateurs->tete;
    while (liste != NULL)
    {
        printf(" Numéro d'identification' : %d | nom : %s | prenom : %s | adresse : %s  | email : %s  | telephone : %d   \n",
               liste->utilisateur.id, liste->utilisateur.nom, liste->utilisateur.prenom, liste->utilisateur.adresse, liste->utilisateur.email, liste->utilisateur.telephone);
        liste = liste->suivant;
    }
}

// Fonction pour supprimer un utilisateur de la liste des utilisateurs

void supprimerUtilisateur(ListeUtilisateurs *listeUtilisateurs, int idUtilisateur)
{
    // Vérifier si la liste d'utilisateurs est vide
    if (listeUtilisateurs == NULL || listeUtilisateurs->tete == NULL)
    {
        printf("La liste d'utilisateurs est vide.\n");
        return;
    }

    // Rechercher l'utilisateur dans la liste
    CelluleUtilisateur *courant = listeUtilisateurs->tete;
    CelluleUtilisateur *precedent = NULL;
    while (courant != NULL && courant->utilisateur.id != idUtilisateur)
    {
        precedent = courant;
        courant = courant->suivant;
    }

    // Vérifier si l'utilisateur a été trouvé
    if (courant == NULL)
    {
        printf("Aucun utilisateur trouvé avec l'identifiant %d.\n", idUtilisateur);
        return;
    }

    // Supprimer l'utilisateur de la liste
    if (precedent == NULL)
    {
        // L'utilisateur à supprimer est en tête de liste
        listeUtilisateurs->tete = courant->suivant;
    }
    else
    {
        precedent->suivant = courant->suivant;
    }
    free(courant); // Libérer la mémoire de l'utilisateur supprimé

    // Réécrire le fichier utilisateur avec la liste mise à jour
    FILE *fichierUtilisateurs = fopen("utilisateurs.txt", "w");
    if (fichierUtilisateurs == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier utilisateurs.txt.\n");
        return;
    }

    courant = listeUtilisateurs->tete;
    while (courant != NULL)
    {
        fprintf(fichierUtilisateurs, "%d %s %s %s %s %d\n", courant->utilisateur.id,
                courant->utilisateur.nom, courant->utilisateur.prenom,
                courant->utilisateur.adresse, courant->utilisateur.email,
                courant->utilisateur.telephone);
        courant = courant->suivant;
    }

    fclose(fichierUtilisateurs);
    printf("Utilisateur avec l'identifiant %d supprimé avec succès.\n", idUtilisateur);
}

//  Fonction pour initialiser liste des emprunts

void initialiserListemprunts(Listemprunts *liste)
{
    liste->tete = NULL;
}

//  Fonction pour enregistrement d'un emprunt

Emprunt Enregistrementemprunt(Emprunt emprunt)
{

    Emprunt nouvelemprunt;

    printf("entrer l'identifiant de emprunt a éffectué: \n  ");
    scanf("%d", &nouvelemprunt.id_emprunt);
    printf("entrer l'identifiant du livre a emprunté :\n  ");
    scanf("%d", &nouvelemprunt.id_livre_emprunte);
    printf("entrer l'identifiant de l'utilisateur qui va emprunté ce livre : \n  ");
    scanf("%d", &nouvelemprunt.id_utilisateur);
    printf("saisir  la date de l'emprunt  du livre : \n  ");
    printf("jour :   ");
    scanf("%d", &nouvelemprunt.date_emprunt.jour);
    printf("mois:    ");
    scanf("%d", &nouvelemprunt.date_emprunt.mois);
    printf("anneé :   ");
    scanf("%d", &nouvelemprunt.date_emprunt.annee);
    printf("saisir  la date de retour prevue  du livre  \n  ");
    printf("jour :   ");
    scanf("%d", &nouvelemprunt.date_retour_prevue.jour);
    printf("mois:     ");
    scanf("%d", &nouvelemprunt.date_retour_prevue.mois);
    printf("anneé :   ");
    scanf("%d", &nouvelemprunt.date_retour_prevue.annee);

    return nouvelemprunt;
}

//  Fonction pour Mettre à jour le nombre d'exemplaires disponibles dans la liste des livres APRES UN EMPRUNT

void diminuerExemplairesDisponibles(ListeLivres *listeLivres, int idLivre)
{
    // Parcourir la liste des livres pour trouver le livre correspondant à l'identifiant idLivre
    CelluleLivre *courant = listeLivres->tete;
    while (courant != NULL && courant->livre.id != idLivre)
    {
        courant = courant->suivant;
    }
    // Si le livre est trouvé, décrémenter le nombre d'exemplaires disponibles
    if (courant != NULL)
    {
        // Vérifier si des exemplaires sont disponibles avant de décrémenter
        if (courant->livre.nombre_exemplaires > 0)
        {
            courant->livre.nombre_exemplaires--;
        }
        else
        {
            printf("Erreur : Aucun exemplaire disponible pour ce livre.\n");
        }
    }
    else
    {
        // Gérer le cas où le livre n'est pas trouvé (peut-être une erreur)
        printf("Erreur : Le livre avec l'identifiant %d n'existe pas dans la liste des livres.\n", idLivre);
    }
}

// Fonction pour vérifier si un livre existe dans la liste des livres

bool livreExiste(ListeLivres *listeLivres, int idLivre)
{
    // Vérifier si la liste des livres est vide
    if (listeLivres->tete == NULL)
    {
        return false; // Aucun livre dans la liste
    }

    // Parcourir la liste des livres pour trouver le livre avec l'identifiant donné
    CelluleLivre *courant = listeLivres->tete;
    while (courant != NULL)
    {
        if (courant->livre.id == idLivre)
        {
            return true; // Le livre existe dans la liste
        }
        courant = courant->suivant;
    }

    return false; // Le livre n'existe pas dans la liste
}

// fonction pour verifier qu'un utilisateur exite

int utilisateurExiste(ListeUtilisateurs *listeUtilisateurs, int idUtilisateur)
{
    // Vérifier si la liste des utilisateurs est vide
    if (listeUtilisateurs->tete == NULL)
    {
        return 0; // Aucun utilisateur enregistré dans la liste
    }

    // Parcourir la liste des utilisateurs pour trouver une correspondance d'identifiant
    CelluleUtilisateur *P = listeUtilisateurs->tete;
    while (P != NULL)
    {
        if (P->utilisateur.id == idUtilisateur)
        {
            return 1; // L'utilisateur avec l'identifiant spécifié existe dans la liste
        }
        P = P->suivant;
    }

    return 0; // Aucun utilisateur trouvé avec l'identifiant spécifié
}
//  Fonction pour Ajout  d'un emprunt

void Ajouteremprunts(Listemprunts *liste, Emprunt emprunt, ListeUtilisateurs *listeUtilisateurs, ListeLivres *listeLivres)
{

    // Vérifier si l'utilisateur est enregistré
    if (!utilisateurExiste(listeUtilisateurs, emprunt.id_utilisateur))
    {
        printf("L'utilisateur avec l'identifiant %d n'est pas enregistré. Impossible d'emprunter.\n", emprunt.id_utilisateur);

        return;
    }

    // Vérifier si le livre existe dans la liste des livres
    if (!livreExiste(listeLivres, emprunt.id_livre_emprunte))
    {
        printf("Le livre avec l'identifiant %d n'existe pas. Impossible d'emprunter.\n", emprunt.id_livre_emprunte);
        return;
    }
    // Mettre à jour le nombre d'exemplaires disponibles dans la liste des livres
    diminuerExemplairesDisponibles(listeLivres, emprunt.id_livre_emprunte);
    // Allouer de la mémoire pour la nouvelle cellule d'emprunt
    CelluleEmprunt *nouvellecell = (CelluleEmprunt *)malloc(sizeof(CelluleEmprunt));
    if (nouvellecell == NULL)
    {
        printf("Erreur: Impossible d'allouer de la mémoire pour la nouvelle cellule d'emprunt.\n");
        return;
    }

    // Remplir les informations de la nouvelle cellule d'emprunt
    nouvellecell->emprunt = emprunt;
    nouvellecell->suivant = NULL;

    // Insérer la nouvelle cellule d'emprunt dans la liste des emprunts
    if (liste->tete == NULL)
    {
        liste->tete = nouvellecell;
    }
    else
    {
        CelluleEmprunt *courant = liste->tete;
        while (courant->suivant != NULL)
        {
            courant = courant->suivant;
        }
        courant->suivant = nouvellecell;
    }

    printf("Emprunt ajouté avec succès.\n");
}

//  Fonction pour afficher la liste des  emprunts effectués
void AfficherlisteEmprunts(Listemprunts *listemprunts)
{
    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|                                    Informations des  emprunts                                                                        |\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");

    if (listemprunts->tete == NULL)
    {
        printf("la liste des emprunts est vide\n");
    }

    CelluleEmprunt *liste;
    liste = listemprunts->tete;
    while (liste != NULL)
    {
        printf(" Numéro d'identification de l'emprunt  : %d | Numéro d'identification de l'utilisateur  : %d |Numéro d'identification du livre emprunté: %d |date de l'emprunt: jour : %d  mois: %d annee: %d  |date de retour prevue: jour : %d mois :%d annee: %d   \n",
               liste->emprunt.id_emprunt, liste->emprunt.id_utilisateur, liste->emprunt.id_livre_emprunte, liste->emprunt.date_emprunt.jour, liste->emprunt.date_emprunt.mois, liste->emprunt.date_emprunt.annee,
               liste->emprunt.date_retour_prevue.jour, liste->emprunt.date_retour_prevue.mois, liste->emprunt.date_retour_prevue.annee);
        liste = liste->suivant;
    }
}
// Fonction pour supprimer un emprunt de la liste des emprunts

void supprimerEmprunt(Listemprunts *listeEmprunts, int idEmprunt)
{
    // Vérifier si la liste est vide
    if (listeEmprunts->tete == NULL)
    {
        printf("La liste des emprunts est vide.\n");
        return;
    }

    // Recherche de l'emprunt avec l'identifiant donné
    CelluleEmprunt *courant = listeEmprunts->tete;
    CelluleEmprunt *precedent = NULL;
    while (courant != NULL && courant->emprunt.id_emprunt != idEmprunt)
    {
        precedent = courant;
        courant = courant->suivant;
    }

    // Vérifier si l'emprunt a été trouvé
    if (courant == NULL)
    {
        printf("Aucun emprunt trouvé avec l'identifiant %d.\n", idEmprunt);
        return;
    }

    // Supprimer l'emprunt de la liste
    if (precedent == NULL)
    {
        // Si l'emprunt est en tête de liste
        listeEmprunts->tete = courant->suivant;
    }
    else
    {
        // Si l'emprunt n'est pas en tête de liste
        precedent->suivant = courant->suivant;
    }

    // Libérer la mémoire de la cellule de l'emprunt supprimé
    free(courant);

    printf("Emprunt avec l'identifiant %d supprimé avec succès.\n", idEmprunt);

    // Maintenant, nous devons réécrire le fichier avec la liste mise à jour

    FILE *fichier = fopen("emprunts.txt", "w");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    // Parcourir la liste mise à jour et réécrire les données dans le fichier
    courant = listeEmprunts->tete;
    while (courant != NULL)
    {
        fprintf(fichier, "%d %d %d %d %d %d %d %d %d\n", courant->emprunt.id_emprunt, courant->emprunt.id_utilisateur, courant->emprunt.id_livre_emprunte, courant->emprunt.date_emprunt.jour, courant->emprunt.date_emprunt.mois, courant->emprunt.date_emprunt.annee, courant->emprunt.date_retour_prevue.jour, courant->emprunt.date_retour_prevue.mois, courant->emprunt.date_retour_prevue.annee);
        courant = courant->suivant;
    }

    fclose(fichier);
}

// Fonction pour Enregistrer la liste des livres dans un fichier :

void sauvegarderListeLivres(ListeLivres *listeLivres, const char *livres)
{
    FILE *fichier = fopen(livres, "w");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier %s\n", livres);
        return;
    }

    CelluleLivre *courant = listeLivres->tete;
    while (courant != NULL)
    {
        fprintf(fichier, "%d %s %s %d %s %d\n", courant->livre.id, courant->livre.titre, courant->livre.auteur,
                courant->livre.annee_publication, courant->livre.genre, courant->livre.nombre_exemplaires);
        courant = courant->suivant;
    }

    fclose(fichier);
}

//  Fonction pour Enregistrer la liste des utilisateurs dans un fichier :

void sauvegarderListeUtilisateurs(ListeUtilisateurs *listeUtilisateurs, const char *utilisateurs)
{
    FILE *fichier = fopen(utilisateurs, "w");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier %s\n", utilisateurs);
        return;
    }

    CelluleUtilisateur *courant = listeUtilisateurs->tete;
    while (courant != NULL)
    {
        fprintf(fichier, "%d %s %s %s %s %d\n", courant->utilisateur.id, courant->utilisateur.nom,
                courant->utilisateur.prenom, courant->utilisateur.adresse, courant->utilisateur.email,
                courant->utilisateur.telephone);
        courant = courant->suivant;
    }

    fclose(fichier);
}

// Enregistrer la liste des emprunts dans un fichier :

void sauvegarderListeEmprunts(Listemprunts *listeEmprunts, const char *emprunts)
{
    FILE *fichier = fopen(emprunts, "w");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier %s\n", emprunts);
        return;
    }

    CelluleEmprunt *courant = listeEmprunts->tete;
    while (courant != NULL)
    {
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

void chargerListeLivres(ListeLivres *listeLivres, const char *livres)
{
    FILE *fichier = fopen(livres, "r");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier %s\n", livres);
        return;
    }

    Livre livre;
    while (fscanf(fichier, "%d %99s %99s %d %49s %d", &livre.id, livre.titre, livre.auteur,
                  &livre.annee_publication, livre.genre, &livre.nombre_exemplaires) == 6)
    {
        Ajouterlivre(listeLivres, livre);
    }

    fclose(fichier);
}

// Fonction pour Charger la liste des utilisateurs :

void chargerListeUtilisateurs(ListeUtilisateurs *listeUtilisateurs, const char *utilisateurs)
{
    FILE *fichier = fopen(utilisateurs, "r");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier %s\n", utilisateurs);
        return;
    }

    Utilisateur utilisateur;
    while (fscanf(fichier, "%d %99s %99s %199s %99s %d", &utilisateur.id, utilisateur.nom, utilisateur.prenom,
                  utilisateur.adresse, utilisateur.email, &utilisateur.telephone) == 6)
    {
        Ajouterutilisateurs(listeUtilisateurs, utilisateur);
    }

    fclose(fichier);
}

// Fonction pour  Charger la liste des emprunts :

void chargerListeEmprunts(Listemprunts *listeEmprunts, const char *emprunts, ListeLivres *listeLivres, ListeUtilisateurs *listeUtilisateurs)
{
    FILE *fichier = fopen(emprunts, "r");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier %s\n", emprunts);
        return;
    }

    Emprunt emprunt;
    while (fscanf(fichier, "%d %d %d %d %d %d %d %d %d", &emprunt.id_emprunt, &emprunt.id_utilisateur,
                  &emprunt.id_livre_emprunte, &emprunt.date_emprunt.jour, &emprunt.date_emprunt.mois,
                  &emprunt.date_emprunt.annee, &emprunt.date_retour_prevue.jour, &emprunt.date_retour_prevue.mois,
                  &emprunt.date_retour_prevue.annee) == 9)
    {
        Ajouteremprunts(listeEmprunts, emprunt, listeUtilisateurs, listeLivres);
        // Ajouteremprunts(listeEmprunts, emprunt, listeLivres);
    }

    fclose(fichier);
}
// Fonction pour modifier un livre

void modifierLivre(ListeLivres *listeLivres, const char *nomFichierLivres)
{
    int idLivre;
    printf("Veuillez entrer l'identifiant du livre à modifier : ");
    if (scanf("%d", &idLivre) != 1)
    {
        printf("Erreur : saisie invalide pour l'identifiant du livre.\n");
        while (getchar() != '\n')
            ; // Vider le tampon d'entrée
        return;
    }

    CelluleLivre *courant = listeLivres->tete;
    while (courant != NULL && courant->livre.id != idLivre)
    {
        courant = courant->suivant;
    }

    if (courant == NULL)
    {
        printf("Aucun livre trouvé avec l'identifiant %d.\n", idLivre);
        return;
    }

    Livre nouveauLivre;
    printf("Nouveau titre : ");
    scanf("%s", nouveauLivre.titre);
    printf("Nouvel auteur : ");
    scanf("%s", nouveauLivre.auteur);
    printf("Nouveau genre : ");
    scanf("%s", nouveauLivre.genre);
    printf("Nouveau nombre d'exemplaires : ");
    scanf("%d", &nouveauLivre.nombre_exemplaires);

    // Modifier les attributs du livre
    strcpy(courant->livre.titre, nouveauLivre.titre);
    strcpy(courant->livre.auteur, nouveauLivre.auteur);
    strcpy(courant->livre.genre, nouveauLivre.genre);
    courant->livre.nombre_exemplaires = nouveauLivre.nombre_exemplaires;

    printf("Livre avec l'identifiant %d modifié avec succès.\n", idLivre);

    // Mettre à jour le fichier des livres pour refléter la modification
    FILE *fichierLivres = fopen(nomFichierLivres, "w");
    if (fichierLivres == NULL)
    {
        printf("Erreur : Impossible d'ouvrir le fichier des livres.\n");
        return;
    }

    courant = listeLivres->tete;
    while (courant != NULL)
    {
        fprintf(fichierLivres, "%d %s %s %d %s %d\n",
                courant->livre.id,
                courant->livre.titre,
                courant->livre.auteur,
                courant->livre.annee_publication,
                courant->livre.genre,
                courant->livre.nombre_exemplaires);

        courant = courant->suivant;
    }

    fclose(fichierLivres);
}

// Fonction pour modifier un utilisateur :

void modifierUtilisateur(ListeUtilisateurs *listeUtilisateurs, const char *utilisateurs)
{
    int idUtilisateur;
    printf("Veuillez entrer l'identifiant de l'utilisateur à modifier : ");
    if (scanf("%d", &idUtilisateur) != 1)
    {
        printf("Erreur : saisie invalide pour l'identifiant de l'utilisateur.\n");
        while (getchar() != '\n')
            ; // Vider le tampon d'entrée
        return;
    }

    CelluleUtilisateur *courant = listeUtilisateurs->tete;
    while (courant != NULL && courant->utilisateur.id != idUtilisateur)
    {
        courant = courant->suivant;
    }

    if (courant == NULL)
    {
        printf("Aucun utilisateur trouvé avec l'identifiant %d.\n", idUtilisateur);
        return;
    }

    // Demander les nouvelles informations pour l'utilisateur
    printf("Nouveau nom de l'utilisateur : ");
    scanf("%s", courant->utilisateur.nom);
    printf("Nouveau prénom de l'utilisateur : ");
    scanf("%s", courant->utilisateur.prenom);
    printf("Nouvelle adresse de l'utilisateur : ");
    scanf("%s", courant->utilisateur.adresse);
    printf("Nouvel email de l'utilisateur : ");
    scanf("%s", courant->utilisateur.email);
    printf("Nouveau numéro de téléphone de l'utilisateur : ");
    scanf("%d", &courant->utilisateur.telephone);

    printf("Utilisateur avec l'identifiant %d modifié avec succès.\n", idUtilisateur);

    // Mettre à jour le fichier des utilisateurs pour refléter la modification
    FILE *fichierUtilisateurs = fopen(utilisateurs, "w");
    if (fichierUtilisateurs == NULL)
    {
        printf("Erreur : Impossible d'ouvrir le fichier des utilisateurs.\n");
        return;
    }

    courant = listeUtilisateurs->tete;
    while (courant != NULL)
    {
        fprintf(fichierUtilisateurs, "%d %s %s %s %s %d\n",
                courant->utilisateur.id,
                courant->utilisateur.nom,
                courant->utilisateur.prenom,
                courant->utilisateur.adresse,
                courant->utilisateur.email,
                courant->utilisateur.telephone);

        courant = courant->suivant;
    }

    fclose(fichierUtilisateurs);
}
// Fonction pour modifier un emprunt :

void modifierEmprunt(Listemprunts *listeEmprunts, const char *emprunts)
{
    int idEmprunt;
    printf("Veuillez entrer l'identifiant de l'emprunt à modifier : ");
    if (scanf("%d", &idEmprunt) != 1)
    {
        printf("Erreur : saisie invalide pour l'identifiant de l'emprunt.\n");
        while (getchar() != '\n')
            ; // Vider le tampon d'entrée
        return;
    }

    CelluleEmprunt *courant = listeEmprunts->tete;
    while (courant != NULL && courant->emprunt.id_emprunt != idEmprunt)
    {
        courant = courant->suivant;
    }

    if (courant == NULL)
    {
        printf("Aucun emprunt trouvé avec l'identifiant %d.\n", idEmprunt);
        return;
    }

    // Demander les nouvelles informations pour l'emprunt
    printf("Nouvelle date de retour prévue (jour mois année) : ");
    scanf("%d %d %d", &courant->emprunt.date_retour_prevue.jour,
          &courant->emprunt.date_retour_prevue.mois,
          &courant->emprunt.date_retour_prevue.annee);

    printf("Emprunt avec l'identifiant %d modifié avec succès.\n", idEmprunt);

    // Mettre à jour le fichier des emprunts pour refléter la modification
    FILE *fichierEmprunts = fopen(emprunts, "w");
    if (fichierEmprunts == NULL)
    {
        printf("Erreur : Impossible d'ouvrir le fichier des emprunts.\n");
        return;
    }

    courant = listeEmprunts->tete;
    while (courant != NULL)
    {
        fprintf(fichierEmprunts, "%d %d %d %d/%d/%d %d/%d/%d %d\n",
                courant->emprunt.id_emprunt,
                courant->emprunt.id_utilisateur,
                courant->emprunt.id_livre_emprunte,
                courant->emprunt.date_emprunt.jour,
                courant->emprunt.date_emprunt.mois,
                courant->emprunt.date_emprunt.annee,
                courant->emprunt.date_retour_prevue.jour,
                courant->emprunt.date_retour_prevue.mois,
                courant->emprunt.date_retour_prevue.annee,
                courant->emprunt.est_retourne);

        courant = courant->suivant;
    }

    fclose(fichierEmprunts);
}
void modifierElement(ListeLivres *listeLivres, ListeUtilisateurs *listeUtilisateurs, Listemprunts *listeEmprunts, const char *livres, const char *utilisateurs, const char *emprunts)
{
    int choix;

    printf("Quel élément souhaitez-vous modifier ?\n");
    printf("1. Livre\n");
    printf("2. Utilisateur\n");
    printf("3. Emprunt\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

    switch (choix)
    {
    case 1:
        // modifierLivre(listeLivres);
        modifierLivre(listeLivres, livres);
        break;
    case 2:
        // Modification d'un utilisateur
        modifierUtilisateur(listeUtilisateurs, utilisateurs);
        break;
    case 3:
        // Modification d'un emprunt
        modifierEmprunt(listeEmprunts, emprunts);
        break;
    default:
        printf("Choix invalide.\n");
        break;
    }
}

void afficherLivresEmpruntesParUtilisateur(Listemprunts *listeEmprunts, ListeLivres *listeLivres)
{
    int idUtilisateur;
    printf("Entrez l'identifiant de l'utilisateur dont vous voulez afficher les livres empruntés : ");
    scanf("%d", &idUtilisateur);

    printf("Livres empruntés par l'utilisateur avec l'identifiant %d :\n", idUtilisateur);

    // Parcourir la liste des emprunts
    CelluleEmprunt *courant = listeEmprunts->tete;
    while (courant != NULL)
    {
        // Vérifier si l'emprunt correspond à l'utilisateur spécifié
        if (courant->emprunt.id_utilisateur == idUtilisateur)
        {
            // Trouver le livre correspondant à l'ID de livre de l'emprunt
            CelluleLivre *livreCourant = listeLivres->tete;
            while (livreCourant != NULL)
            {
                if (livreCourant->livre.id == courant->emprunt.id_livre_emprunte)
                {
                    // Afficher les détails du livre emprunté
                    printf("ID : %d\n", livreCourant->livre.id);
                    printf("Titre : %s\n", livreCourant->livre.titre);
                    printf("Auteur : %s\n", livreCourant->livre.auteur);
                    printf("Genre : %d\n", livreCourant->livre.genre);
                    printf("Nombre d'exemplaires : %d\n", livreCourant->livre.nombre_exemplaires);
                    printf("\n");
                    break; // Sortir de la boucle une fois que le livre est trouvé
                }
                livreCourant = livreCourant->suivant;
            }
        }
        courant = courant->suivant;
    }
}
// Fonction pour obtenir la liste des utilisateurs ayant emprunté un livre spécifique
void utilisateursEmpruntantLivre(Listemprunts *listeEmprunts, ListeUtilisateurs *listeUtilisateurs)
{
    int idLivreRecherche;
    printf("Veuillez entrer l'identifiant du livre : ");
    if (scanf("%d", &idLivreRecherche) != 1)
    {
        printf("Erreur : saisie invalide pour l'identifiant du livre.\n");
        while (getchar() != '\n')
            ; // Vider le tampon d'entrée
        return;
    }

    CelluleEmprunt *courantEmprunts = listeEmprunts->tete;
    bool livreEmprunte = false;

    printf("Utilisateurs ayant emprunté le livre avec l'identifiant %d :\n", idLivreRecherche);

    while (courantEmprunts != NULL)
    {
        if (courantEmprunts->emprunt.id_livre_emprunte == idLivreRecherche)
        {
            CelluleUtilisateur *courantUtilisateurs = listeUtilisateurs->tete;
            while (courantUtilisateurs != NULL)
            {
                if (courantUtilisateurs->utilisateur.id == courantEmprunts->emprunt.id_utilisateur)
                {
                    printf("ID Emprunt : %d\n", courantEmprunts->emprunt.id_emprunt);
                    printf("ID Utilisateur : %d\n", courantUtilisateurs->utilisateur.id);
                    printf("Nom : %s\n", courantUtilisateurs->utilisateur.nom);
                    printf("Prénom : %s\n", courantUtilisateurs->utilisateur.prenom);
                    printf("Adresse : %s\n", courantUtilisateurs->utilisateur.adresse);
                    printf("Email : %s\n", courantUtilisateurs->utilisateur.email);
                    printf("Téléphone : %d\n", courantUtilisateurs->utilisateur.telephone);
                    printf("\n");
                    livreEmprunte = true;
                    break;
                }
                courantUtilisateurs = courantUtilisateurs->suivant;
            }
        }
        courantEmprunts = courantEmprunts->suivant;
    }

    if (!livreEmprunte)
    {
        printf("Aucun utilisateur n'a emprunté ce livre.\n");
    }
}

// Fonction pour gérer le sous-menu des statistiques
void statistiques(ListeLivres *listeLivres, ListeUtilisateurs *listeUtilisateurs, Listemprunts *listemprunts)
{
    int choix;
    printf("********************** Sous-menu Statistiques : **********************\n");
    printf("Veuillez choisir une option : \n");
    printf("1. Nombre total de livres dans la bibliothèque\n");
    printf("2. Nombre total d'utilisateurs de la bibliothèque\n");
    printf("3. Nombre total d'emprunts\n");
    printf("4. Nombre d'exemplaires disponibles pour chaque livre \n");
    printf("5. Moyenne d'emprunts par utilisateur \n");

    scanf("%d", &choix);

    switch (choix)
    {
    case 1:
        afficherNombreLivres(listeLivres);
        break;
    case 2:
        afficherNombreUtilisateurs(listeUtilisateurs);
        break;
    case 3:
        afficherNombreEmprunts(listemprunts);
        break;
    case 4:
        afficherNombreExemplairesDisponibles(listeLivres);
        break;
    case 5:
        float moyenne = calculerMoyenneEmpruntsParUtilisateur(listemprunts, listeUtilisateurs);
        printf("Moyenne d'emprunts par utilisateur : %.2f\n", moyenne);
        break;
    default:
        printf("Choix invalide.\n");
        break;
    }
}

// Fonction pour afficher le nombre total de livres dans la bibliothèque
void afficherNombreLivres(ListeLivres *listeLivres)
{
    int nombreLivres = 0;
    CelluleLivre *courant = listeLivres->tete;
    while (courant != NULL)
    {
        nombreLivres += courant->livre.nombre_exemplaires;
        courant = courant->suivant;
    }
    printf("Nombre total de livres dans la bibliothèque : %d\n", nombreLivres);
}

// Fonction pour afficher le nombre total d'utilisateurs de la bibliothèque
void afficherNombreUtilisateurs(ListeUtilisateurs *listeUtilisateurs)
{
    int nombreUtilisateurs = 0;
    CelluleUtilisateur *courant = listeUtilisateurs->tete;
    while (courant != NULL)
    {
        nombreUtilisateurs++;
        courant = courant->suivant;
    }
    printf("Nombre total d'utilisateurs de la bibliothèque : %d\n", nombreUtilisateurs);
}
// Fonction pour afficher le nombre total d'emprunts
void afficherNombreEmprunts(Listemprunts *listemprunts)
{
    int nombreEmprunts = 0;
    CelluleEmprunt *courant = listemprunts->tete;
    while (courant != NULL)
    {
        nombreEmprunts++;
        courant = courant->suivant;
    }
    printf("Nombre total d'emprunts : %d\n", nombreEmprunts);
}
// Fonction pour afficher le nombre d'exemplaires disponibles pour chaque livre
void afficherNombreExemplairesDisponibles(ListeLivres *listeLivres)
{
    CelluleLivre *courant = listeLivres->tete;
    while (courant != NULL)
    {
        printf("Livre : %s\n", courant->livre.titre);
        printf("Nombre d'exemplaires disponibles : %d\n", courant->livre.nombre_exemplaires);
        courant = courant->suivant;
    }
}
// Fonction pour calculer la moyenne d'emprunts par utilisateur
float calculerMoyenneEmpruntsParUtilisateur(Listemprunts *listeEmprunts, ListeUtilisateurs *listeUtilisateurs)
{
    int nombreEmprunts = 0;
    int nombreUtilisateurs = 0;

    // Parcourir la liste des emprunts pour compter le nombre total d'emprunts
    CelluleEmprunt *courantEmprunt = listeEmprunts->tete;
    while (courantEmprunt != NULL)
    {
        nombreEmprunts++;
        courantEmprunt = courantEmprunt->suivant;
    }

    // Parcourir la liste des utilisateurs pour compter le nombre total d'utilisateurs
    CelluleUtilisateur *courantUtilisateur = listeUtilisateurs->tete;
    while (courantUtilisateur != NULL)
    {
        nombreUtilisateurs++;
        courantUtilisateur = courantUtilisateur->suivant;
    }

    // Vérifier si le nombre d'utilisateurs est différent de zéro pour éviter une division par zéro
    if (nombreUtilisateurs != 0)
    {
        return (float)nombreEmprunts / nombreUtilisateurs;
    }
    else
    {
        // Retourner zéro si le nombre d'utilisateurs est zéro pour éviter une division par zéro
        return 0.0;
    }
}
#include <stdio.h>
#include <stdlib.h>
// trier la liste des livres par ordre croissant d'identifiant et mettre à jour le fichier des livres avec les changements
void trierEtReecrireLivresParIdentifiant(ListeLivres *listeLivres)
{
    if (listeLivres == NULL || listeLivres->tete == NULL)
    {
        // Liste vide ou un seul élément, aucun besoin de trier
        return;
    }

    // Initialisation d'une liste temporaire pour stocker les livres triés
    ListeLivres listeTriee;
    listeTriee.tete = NULL;

    // Parcourir la liste des livres non triés
    CelluleLivre *courant = listeLivres->tete;
    while (courant != NULL)
    {
        // Sauvegarder le prochain élément de la liste non triée
        CelluleLivre *suivant = courant->suivant;

        // Insérer le livre courant dans la liste triée
        if (listeTriee.tete == NULL || courant->livre.id < listeTriee.tete->livre.id)
        {
            // Cas spécial : si la liste triée est vide ou si le livre courant a l'ID le plus bas
            courant->suivant = listeTriee.tete;
            listeTriee.tete = courant;
        }
        else
        {
            // Trouver l'emplacement approprié pour insérer le livre courant dans la liste triée
            CelluleLivre *precedent = listeTriee.tete;
            while (precedent->suivant != NULL && precedent->suivant->livre.id < courant->livre.id)
            {
                precedent = precedent->suivant;
            }
            courant->suivant = precedent->suivant;
            precedent->suivant = courant;
        }

        // Passer au prochain élément de la liste non triée
        courant = suivant;
    }

    // Mettre à jour la tête de la liste des livres avec la liste triée
    listeLivres->tete = listeTriee.tete;

    // Réécrire le fichier livres.txt avec les livres triés
    FILE *fichierLivres = fopen("livres.txt", "w");
    if (fichierLivres == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier livres.txt en écriture.\n");
        return;
    }

    // Parcourir la liste des livres triée et réécrire chaque livre dans le fichier
    courant = listeTriee.tete;
    while (courant != NULL)
    {
        fprintf(fichierLivres, "%d %s %s %d %s %d\n", courant->livre.id,
                courant->livre.titre, courant->livre.auteur,
                courant->livre.annee_publication, courant->livre.genre,
                courant->livre.nombre_exemplaires);
        courant = courant->suivant;
    }

    // Fermer le fichier de livres
    fclose(fichierLivres);
    printf("Le fichier livres.txt a été mis à jour avec succès.\n");
}

// classer la liste des utilisateurs par ordre croissant d'identifiant et mettre à jour le fichier d'utilisateurs avec les changements

void trierEtReecrireUtilisateursParIdentifiant(ListeUtilisateurs *listeUtilisateurs)
{
    if (listeUtilisateurs == NULL || listeUtilisateurs->tete == NULL)
    {
        // Liste vide ou un seul élément, aucun besoin de trier
        return;
    }

    // Initialisation d'une liste temporaire pour stocker les utilisateurs triés
    ListeUtilisateurs listeTriee;
    listeTriee.tete = NULL;

    // Parcourir la liste des utilisateurs non triés
    CelluleUtilisateur *courant = listeUtilisateurs->tete;
    while (courant != NULL)
    {
        // Sauvegarder le prochain élément de la liste non triée
        CelluleUtilisateur *suivant = courant->suivant;

        // Insérer l'utilisateur courant dans la liste triée
        if (listeTriee.tete == NULL || courant->utilisateur.id < listeTriee.tete->utilisateur.id)
        {
            // Cas spécial : si la liste triée est vide ou si l'utilisateur courant a l'ID le plus bas
            courant->suivant = listeTriee.tete;
            listeTriee.tete = courant;
        }
        else
        {
            // Trouver l'emplacement approprié pour insérer l'utilisateur courant dans la liste triée
            CelluleUtilisateur *precedent = listeTriee.tete;
            while (precedent->suivant != NULL && precedent->suivant->utilisateur.id < courant->utilisateur.id)
            {
                precedent = precedent->suivant;
            }
            courant->suivant = precedent->suivant;
            precedent->suivant = courant;
        }

        // Passer au prochain élément de la liste non triée
        courant = suivant;
    }

    // Mettre à jour la tête de la liste des utilisateurs avec la liste triée
    listeUtilisateurs->tete = listeTriee.tete;

    // Réécrire le fichier utilisateurs.txt avec les utilisateurs triés
    FILE *fichierUtilisateurs = fopen("utilisateurs.txt", "w");
    if (fichierUtilisateurs == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier utilisateurs.txt en écriture.\n");
        return;
    }

    // Parcourir la liste des utilisateurs triée et réécrire chaque utilisateur dans le fichier
    courant = listeTriee.tete;
    while (courant != NULL)
    {
        fprintf(fichierUtilisateurs, "%d %s %s %s %s %d\n", courant->utilisateur.id,
                courant->utilisateur.nom, courant->utilisateur.prenom,
                courant->utilisateur.adresse, courant->utilisateur.email,
                courant->utilisateur.telephone);
        courant = courant->suivant;
    }

    // Fermer le fichier d'utilisateurs
    fclose(fichierUtilisateurs);
    printf("Le fichier utilisateurs.txt a été mis à jour avec succès.\n");
}
