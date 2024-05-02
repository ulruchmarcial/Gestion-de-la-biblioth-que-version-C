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
        choix = toupper(choix); // Convertir en majuscule
        switch ((MenuChoice)choix)
        {
        case CHOIX_A:

            Livre nouveaulivre = Enregistrementlivre(livre);

            Ajouterlivre(&listeLivres, nouveaulivre);
            sauvegarderListeLivres(&listeLivres, "livres.txt");
            printf("\nLivre enregistré. Appuyez sur Entrée pour revenir au menu...");
            getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
            getchar(); // Attendez l'entrée de l'utilisateur
            system("clear");

            break;
        case CHOIX_B:

            Utilisateur nouveauutilisateur = Enregistrementutilisateur(utilisateur);
            Ajouterutilisateurs(&listeUtilisateurs, nouveauutilisateur);
            sauvegarderListeUtilisateurs(&listeUtilisateurs, "utilisateurs.txt");
            printf("\nUtilisateur enregistré. Appuyez sur Entrée pour revenir au menu...");
            getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
            getchar(); // Attendez l'entrée de l'utilisateur
            system("clear");

            break;
        case CHOIX_C:

            rechercherLivre(&listeLivres);
            printf("\n Appuyez sur Entrée pour revenir au menu...");
            getchar(); // Attendez l'entrée de l'utilisateur
            system("clear");
            break;

        case CHOIX_D:

            Emprunt nouvelemprunt = Enregistrementemprunt(emprunt);
            Ajouteremprunts(&listemprunts, nouvelemprunt, &listeUtilisateurs, &listeLivres);
            // Ajouteremprunts(&listemprunts,nouvelemprunt,&listeLivres);
            sauvegarderListeEmprunts(&listemprunts, "emprunts.txt");
            printf("\nemprunt enregistré. Appuyez sur Entrée pour revenir au menu...");
            getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
            getchar(); // Attendez l'entrée de l'utilisateur
            system("clear");

            break;

        case CHOIX_E:
            retournerLivre(&listemprunts, &listeLivres, "emprunts.txt");
            // retournerLivre(&listemprunts, &listeLivres);
            augmenterExemplairesDisponibles(&listeLivres, idLivre);
            printf("\n Appuyez sur Entrée pour revenir au menu...");
            getchar(); // Attendez l'entrée de l'utilisateur
            system("clear");
            break;

        case CHOIX_F:
            printf("     *************************************** LISTE DES LIVRES  *************************************** \n");
            Afficherlistelivre(&listeLivres);
            trierEtReecrireLivresParIdentifiant(&listeLivres); 
            printf("Appuyez sur Entrée pour continuer...");
            getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
            getchar(); // Attendez l'entrée de l'utilisateur

            break;
        case CHOIX_G:
            printf("  *************************************** LISTE DES UTILISATEURS  *************************************** \n");
            Afficherlisteutilisateurs(&listeUtilisateurs);
            trierEtReecrireUtilisateursParIdentifiant(&listeUtilisateurs);
            printf("Appuyez sur Entrée pour continuer...");
            getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
            getchar(); // Attendez l'entrée de l'utilisateur
            break;

        case CHOIX_H:
            printf("  *************************************** LISTE DES EMPRUNTS   *************************************** \n");
            AfficherlisteEmprunts(&listemprunts);
            printf("Appuyez sur Entrée pour continuer...");
            getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
            getchar(); // Attendez l'entrée de l'utilisateur
            break;
        case CHOIX_I:
            int idLivreASupprimer;
            printf("Veuillez saisir l'identifiant du livre à supprimer : ");
            scanf("%d", &idLivreASupprimer);
            supprimerLivre(&listeLivres, idLivreASupprimer);
            printf("Appuyez sur Entrée pour continuer...");
            getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
            getchar(); // Attendez l'entrée de l'utilisateur
            break;
        case CHOIX_J:
            int idUtilisateurASupprimer;
            printf("Veuillez saisir l'identifiant dE l'utilisateur  à supprimer : ");
            scanf("%d", &idUtilisateurASupprimer);
            supprimerUtilisateur(&listeUtilisateurs, idUtilisateurASupprimer);
            printf("Appuyez sur Entrée pour continuer...");
            getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
            getchar(); // Attendez l'entrée de l'utilisateur
            break;
        case CHOIX_K:
            int idEmpruntASupprimer;
            printf("Veuillez saisir l'identifiant dE l'emprunt   à supprimer : ");
            scanf("%d", &idEmpruntASupprimer);
            supprimerEmprunt(&listemprunts, idEmpruntASupprimer);
            printf("Appuyez sur Entrée pour continuer...");
            getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
            getchar(); // Attendez l'entrée de l'utilisateur
            break;
        case CHOIX_L:
            modifierElement(&listeLivres, &listeUtilisateurs, &listemprunts, "livres.txt", "utilisateurs.txt", "emprunts.txt");
            printf("Appuyez sur Entrée pour continuer...");
            getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
            getchar(); // Attendez l'entrée de l'utilisateur
            break;
        case CHOIX_M:
            afficherLivresEmpruntesParUtilisateur(&listemprunts, &listeLivres);
            printf("Appuyez sur Entrée pour continuer...");
            getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
            getchar(); // Attendez l'entrée de l'utilisateur
            break;
        case CHOIX_N:
            utilisateursEmpruntantLivre(&listemprunts, &listeUtilisateurs);
            printf("Appuyez sur Entrée pour continuer...");
            getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
            getchar(); // Attendez l'entrée de l'utilisateur
            break;
        case CHOIX_O:
            statistiques(&listeLivres, &listeUtilisateurs, &listemprunts);
            printf("Appuyez sur Entrée pour continuer...");
            getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
            getchar(); // Attendez l'entrée de l'utilisateur
              break;
            case CHOIX_QUITTER:
            // Sortir de la boucle si l'utilisateur choisit de quitte
            break;
        default:
            printf("Choix invalide. Veuillez réessayer.\n");
            printf("Appuyez sur Entrée pour continuer...");
            getchar(); // Consomme le caractère de nouvelle ligne restant dans le tampon
            getchar(); // Attendez l'entrée de l'utilisateur
            break;
        }

    } while ((MenuChoice)choix != CHOIX_QUITTER);
}
