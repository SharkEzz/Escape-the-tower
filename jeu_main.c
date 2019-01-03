#include <stdio.h>
#include <stdlib.h>
#include "jeu_main.h"

int main(int argc, char **argv)
{
    accueil();

    return 0;
}

void accueil()
{
    system("clear");

    int choix = 0;

    printf("--Escape the tower-- ALPHA\n\n\n");
    printf("Menu principal\n\n");

    printf("1 -> Lancer une partie\n");
    printf("2 -> Afficher l'aide\n");
    printf("3 -> Quitter\n\n");

    printf("Entrez votre choix : ");

    scanf("%d", &choix);

    switch(choix)
    {
        case 1:
            lancer_partie();
            break;
        case 2:
            afficher_aide();
            break;
        case 3:
            exit(1);


    }

}

void lancer_partie()
{
    //Je ne fais rien
}

void afficher_aide()
{
    //Je ne fais rien
}