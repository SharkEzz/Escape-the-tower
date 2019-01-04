#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jeu_main.h"

/*
//Couleurs pour le terminal (non utilisé pour le moment)

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
*/

int main(int argc, const char **argv)
{

    // Déclaration des variables (PV, mana, etc...)

    int etat_partie = 0;
    int etage_actuel = 0;
    int ennemi_present = 0;
    int potion_present = 0;
    int pv = 100;
    int mana = 100;
    int choix = 0;
    int aleatoire = 0;
    int pv_ennemi = 100;

    etat_partie = 1; // Indique que la partie est lancée (non utile pour le moment)

    while(etat_partie)
    {

        // S'occupe de générer un nombre aléatoire et en fonction de celui-ci, faire en sorte qu'une potion/ennemi aparaisse dans la salle
        // Partie à équilibrer

        aleatoire = randomf(15,70);

        if(aleatoire > 15 && aleatoire <= 28)
        {
            potion_present = 1;
        }
        else if(aleatoire >= 40 && aleatoire <= 50 && etage_actuel != 0)
        {
            ennemi_present = 1;
        }
        else
        {
            potion_present = 0;
            ennemi_present = 0;
        }

        // Partie jeu

        efface_ecran();

        aff_stats(pv, mana, etage_actuel); // Affiche les stats en haut du terminal

        if(etage_actuel == 100)
        {
            efface_ecran();

            printf("Félécitation ! Vous avez gagné !\n");

            exit(1);
        }

        if(pv == 0)
        {
            efface_ecran();

            printf("Dommage ! Vous êtes mort !\n");

            exit(1);
        }

        if(mana == 0)
        {
            efface_ecran();

            printf("Vous n'avez plus de mana !\n");

            exit(1);
        }

        // Partie affichage des options en fonction des éléments présents dans la salle

        if(ennemi_present == 0 && potion_present == 0)
        {
            printf("Vous arrivez dans une salle vide. Continuer à monter ?\n\n");
            printf("1 −> Oui (Monter à l'étage)\n");
            printf("Votre choix : ");

            scanf("%d", &choix);

            if(choix == 1)
            {
                etage_actuel++;
            }

        }

        if(potion_present == 1)
        {
            printf("Une potion se trouve dans la salle\n");
            printf("Que faire ?\n\n");
            printf("1 -> La ramasser\n");
            printf("2 -> Continuer à monter\n\n");
            printf("Votre choix : ");
            scanf("%d", &choix);

            if(choix == 1)
            {
                if(pv <= 85 && mana <= 85)
                {
                    potion_present = 0;
                    pv = pv + 15;
                    mana = mana +15;
                    etage_actuel++;
                }
                else
                {
                    printf("Vous avez déjâ le nombre maximal de PV et de Mana !\n");
                    delay(5000);
                    potion_present = 0;
                    etage_actuel++;
                }
                
            }
            else if (choix == 2)
            {
                potion_present = 0;
                etage_actuel++;
            }



        }

        if(ennemi_present == 1)
        {
            printf("Vous rencontrez un ennemi ! Préparez vous au combat !\n");
            delay(3000);
            combat(&pv, &mana, &pv_ennemi);
            ennemi_present = 0;
        }

    }


    return 0;
}

void aff_stats(int pv, int mana, int etage)
{
    printf("Points de vie : %d\n", pv);
    printf("Points de mana : %d\n", mana);
    printf("Etage actuel : %d\n\n\n", etage);
}

void aff_stats_combat(int pv, int mana, int pv_ennemi)
{
    printf("PV : %d\n", pv);
    printf("MANA : %d\n", mana);
    printf("PV Ennemi : %d\n\n", pv_ennemi);
}

void combat(int *pv_pers, int *mana_pers, int *pv_ennemi)
{
    int choix = 0;

    while(*pv_ennemi != 0)
    {
        int aleatoire = randomf(1, 17);

        efface_ecran();

        printf(" -- EN COMBAT -- \n\n");

        *pv_pers = *pv_pers - aleatoire;

        aff_stats_combat(*pv_pers, *mana_pers, *pv_ennemi);

        printf("Vous subissez %d points de dégats !\n\n", aleatoire);

        printf("C'est votre tour !\n");
        printf("Vos attaques :\n");
        printf("1 -> Attaque 1 (10 dégats | 5 mana)\n");
        printf("2 -> Attaque 2 (30 dégats | 10 mana)\n");
        printf("3 -> Attaque spéciale (70 dégats | 50 mana\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch(choix)
        {
            case 1:
                printf("1\n");
                delay(2000);
                break;
            case 2:
                printf("2\n");
                delay(2000);
                break;
            case 3:
                printf("3\n");
                delay(2000);
                break;

        }
    }

    
}