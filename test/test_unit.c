#include "../lib/acutest.h"
#include<stdio.h>
#include "../src/tools.h"
#include "../test/test_unit.h"



void check_client(void) {
          // TEST UNITAIRE  POUR LES UTILISATEURS

    ListeUtilisateurs listeUtilisateurs;
    initialiserListeutilisateurs(&listeUtilisateurs);
    Utilisateur utilisateur1 = {1, "user1", "user1", "addr1", "email1", 123};
    Ajouterutilisateurs(&listeUtilisateurs, utilisateur1);

    TEST_CHECK_(utilisateurExiste(&listeUtilisateurs, 1) != 0, "Check exercise1_p1");
    TEST_CHECK_(utilisateurExiste(&listeUtilisateurs, 2) == 0, "Check exercise1_p1");

    Utilisateur utilisateur2 = {2, "user2", "user2", "addr2", "email2", 123};
    Ajouterutilisateurs(&listeUtilisateurs, utilisateur2);
    TEST_CHECK_(utilisateurExiste(&listeUtilisateurs, 2) != 0, "Check exercise1_p1");

    sauvegarderListeUtilisateurs(&listeUtilisateurs, "utilisateurs.txt");
    ListeUtilisateurs listeUtilisateurs2;
    initialiserListeutilisateurs(&listeUtilisateurs2);
    chargerListeUtilisateurs(&listeUtilisateurs2, "utilisateurs.txt");
    TEST_CHECK_(utilisateurExiste(&listeUtilisateurs2, 1) != 0, "Check exercise1_p1");
    TEST_CHECK_(utilisateurExiste(&listeUtilisateurs2, 2) != 0, "Check exercise1_p1");

    // TEST UNITAIRE  POUR LES LIVRES

    ListeLivres listeLivres;
    initialiserListeLivres(&listeLivres);
    Livre livre1 = {1, "livre1", "auteur1", 2002, "sciences", 3};
    Ajouterlivre(&listeLivres, livre1);

    TEST_CHECK_(livreexiste(&listeLivres, 1) != 0, "Check exercise1_p1");
    TEST_CHECK_(livreexiste(&listeLivres, 2) == 0, "Check exercise1_p1");

    Livre livre2 = {2, "livre2", "auteur2", 2003, "theatre", 2};
    Ajouterlivre(&listeLivres, livre2);
    TEST_CHECK_(livreexiste(&listeLivres, 2) != 0, "Check exercise1_p1");

    sauvegarderListeLivres(&listeLivres, "livres.txt");
    ListeLivres listeLivres2;
    initialiserListeLivres(&listeLivres);
    chargerListeLivres(&listeLivres, "livres.txt");
    TEST_CHECK_(livreexiste(&listeLivres, 1) != 0, "Check exercise1_p1");
    TEST_CHECK_(livreexiste(&listeLivres, 2) != 0, "Check exercise1_p1");
}



TEST_LIST = {
    {"void check_client(void)", check_client},
    {0}
};