#include <stdio.h>
#include "../src/tools.h"
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <stdbool.h>

FILE *livres_file = NULL;
FILE *Utilisateur_file = NULL;
FILE *emprunt_file = NULL;

void main(int argc, char *argv[])
{
    ListeLivres listeLivres;
    initialiserListeLivres(&listeLivres);
    Livre livre;
    ListeUtilisateurs listeUtilisateurs;
    initialiserListeutilisateurs(&listeUtilisateurs);
    Utilisateur utilisateur;
    Listemprunts listemprunts;
    initialiserListemprunts(&listemprunts);
    Emprunt emprunt;
    int idLivre, nbre_total_livre, idUtilisateur, idEmprunt;
    chargerListeLivres(&listeLivres, "livres.txt");
    chargerListeUtilisateurs(&listeUtilisateurs, "utilisateurs.txt");
    chargerListeEmprunts(&listemprunts, "emprunts.txt", &listeLivres, &listeUtilisateurs);

    char choix;
    do
    {
        printMainMenu();

        printf("Faites votre choix:  ");

        choix = getchar();

        switch (choix)
        {
        case 'A':

            Livre nouveaulivre =  Enregistrementlivre( livre, &listeLivres) ;

            Ajouterlivre(&listeLivres, nouveaulivre);
            sauvegarderListeLivres(&listeLivres, "livres.txt");
            printf("\nLivre enregistré. Appuyez sur Entrée pour revenir au menu...");
            getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
            getchar(); // Attendez l'entrée de l'utilisateur
            system("clear");

            break;
        case 'B':

            Utilisateur nouveauutilisateur = Enregistrementutilisateur(utilisateur , &listeUtilisateurs);
            Ajouterutilisateurs(&listeUtilisateurs, nouveauutilisateur);
            sauvegarderListeUtilisateurs(&listeUtilisateurs, "utilisateurs.txt");
            printf("\nUtilisateur enregistré. Appuyez sur Entrée pour revenir au menu...");
            getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
            getchar(); // Attendez l'entrée de l'utilisateur
            system("clear");

            break;
        case 'C':

            rechercherLivre(&listeLivres);
            printf("\n Appuyez sur Entrée pour revenir au menu...");
            getchar(); // Attendez l'entrée de l'utilisateur
            system("clear");
            break;

        case 'D':

            Emprunt nouvelemprunt = Enregistrementemprunt(emprunt);
            Ajouteremprunts(&listemprunts, nouvelemprunt, &listeUtilisateurs, &listeLivres);
            // Ajouteremprunts(&listemprunts,nouvelemprunt,&listeLivres);
            sauvegarderListeEmprunts(&listemprunts, "emprunts.txt");
            printf("\nemprunt enregistré. Appuyez sur Entrée pour revenir au menu...");
            getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
            getchar(); // Attendez l'entrée de l'utilisateur
            system("clear");

            break;

        case 'E':
            retournerLivre(&listemprunts, &listeLivres, "emprunts.txt");
            //retournerLivre(&listemprunts, &listeLivres);
            augmenterExemplairesDisponibles(&listeLivres, idLivre);
            printf("\n Appuyez sur Entrée pour revenir au menu...");
            getchar(); // Attendez l'entrée de l'utilisateur
            system("clear");
            break;

        case 'F':
            printf("     *************************************** LISTE DES LIVRES  *************************************** \n");
            Afficherlistelivre(&listeLivres);
            printf("Appuyez sur Entrée pour continuer...");
            getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
            getchar(); // Attendez l'entrée de l'utilisateur

            break;
        case 'G':
            printf("  *************************************** LISTE DES UTILISATEURS  *************************************** \n");
            Afficherlisteutilisateurs(&listeUtilisateurs);
            printf("Appuyez sur Entrée pour continuer...");
            getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
            getchar(); // Attendez l'entrée de l'utilisateur
            break;

        case 'H':
            printf("  *************************************** LISTE DES EMPRUNTS   *************************************** \n");
            AfficherlisteEmprunts(&listemprunts);
            printf("Appuyez sur Entrée pour continuer...");
            getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
            getchar(); // Attendez l'entrée de l'utilisateur
            break;
        case 'I':
            int idLivreASupprimer;
            printf("Veuillez saisir l'identifiant du livre à supprimer : ");
            scanf("%d", &idLivreASupprimer);
            supprimerLivre(&listeLivres, idLivreASupprimer);
            printf("Appuyez sur Entrée pour continuer...");
            getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
            getchar(); // Attendez l'entrée de l'utilisateur
            break;
        case 'J':
            int idUtilisateurASupprimer;
            printf("Veuillez saisir l'identifiant dE l'utilisateur  à supprimer : ");
            scanf("%d", &idUtilisateurASupprimer);
            supprimerUtilisateur(&listeUtilisateurs, idUtilisateurASupprimer);
            printf("Appuyez sur Entrée pour continuer...");
            getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
            getchar(); // Attendez l'entrée de l'utilisateur
            break;
        case 'K':
            int idEmpruntASupprimer;
            printf("Veuillez saisir l'identifiant dE l'emprunt   à supprimer : ");
            scanf("%d", &idEmpruntASupprimer);
            supprimerEmprunt(&listemprunts, idEmpruntASupprimer);
            printf("Appuyez sur Entrée pour continuer...");
            getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
            getchar(); // Attendez l'entrée de l'utilisateur
            break;
            case 'L':
            modifierElement(&listeLivres, &listeUtilisateurs, &listemprunts ,"livres.txt","utilisateurs.txt", "emprunts.txt");
            printf("Appuyez sur Entrée pour continuer...");
            getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
            getchar(); // Attendez l'entrée de l'utilisateur
            break;
            case 'M':
            afficherLivresEmpruntesParUtilisateur(&listemprunts, &listeLivres);
            printf("Appuyez sur Entrée pour continuer...");
            getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
            getchar(); // Attendez l'entrée de l'utilisateur
            break;
            case 'O':
            utilisateursEmpruntantLivre(&listemprunts, &listeUtilisateurs);
            printf("Appuyez sur Entrée pour continuer...");
            getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
            getchar(); // Attendez l'entrée de l'utilisateur
            break;
        
        case 'N':
            nbre_total_livre = affichernombretotallivrebibliotheque(&listeLivres );
            printf("le nombre  total de livres  dans la  bibliotheque est : %d \n", nbre_total_livre);
            printf("Appuyez sur Entrée pour continuer...");
            getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
            getchar(); // Attendez l'entrée de l'utilisateur
            break;
        default:
            break;
        }

    } while (choix != 'Q' && choix != 'q');
}
