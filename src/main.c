#include<stdio.h>
#include "../src/tools.h"
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include <math.h>


void main() {

 char choix;
    do {
        system("clear");
      printf("               *********************************************************************************************************************\n");
	printf("               ***************************************   BIENVENUE DANS L' APPLICATION:  *******************************************\n");
	printf("               ***************************************      GESTION D'UNE BIBLIOTHEQUE   *******************************************\n");
        printf("               *********************************************************************************************************************\n\n");    
	printf("                - A RECHERCHER UN OUVRAGE.\n");
	printf("                - B EMPRUNTER UN OUVRAGE.\n");
	printf("                - C RETOURNER UN OUVRAGE.\n");
	printf("                - D AJOUTER UN OUVRAGE.\n");
    printf("                - E SUPPRIMER UN OUVRAGE.\n");
    printf("                - F AFFICHER LA LISTE DES OUVRAGES DISPONIBLES.\n");
    printf("                - Q QUITTER L'APPLICATION.\n");
	printf("Faitez votre choix:  ");

       
        choix = getchar();

       /* switch (choix) {
            case 'A':
                

            case 'P':
                
               
            case 'B':
        
               --
                
                system("clear");
                break;

            case 'V':
                p

            default:
                break;
        }
*/
    } while (choix != 'Q' && choix != 'q');
}






