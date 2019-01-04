#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jeu_main.h"

int main(int argc, char **argv)
{

    int etat_partie = 0;
    int etage_actuel = 0;
    int ennemi_present = 0;
    int potion_present = 1;
    int pv = 100;
    int mana = 100;
    int choix = 0;

    etat_partie = 1;

    while(etat_partie)
    {

        aff_stats(pv, mana, etage_actuel);

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

        if(ennemi_present == 0 && potion_present == 0)
        {
            printf("Vous arrivez dans une salle vide. Continuer à monter ?\n\n");
            printf("1 −> Oui (Monter à l'étage\n");
            printf("2 -> Quitter le jeu\n");
            printf("Votre choix : ");

            scanf("%d", &choix);

            if(choix == 1)
            {
                etage_actuel++;
                printf("Vous montez d'un étage\n");
            }
            else if(choix == 2)
            {
                etat_partie = 0;
            }

        }

        if(potion_present == 1 && ennemi_present == 0)
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




        //etat_partie = 0;
    }



    return 0;
}

void aff_stats(int pv, int mana, int etage)
{
    efface_ecran();

    printf("Points de vie : %d\n", pv);
    printf("Points de mana : %d\n", mana);
    printf("Etage actuel : %d\n\n\n", etage);   
}

void efface_ecran()
{
    system("clear");
}

void delay(int sec) 
{ 
    int milli_seconds = 1000 * sec; 
    clock_t start_time = clock(); 
    while (clock() < start_time + milli_seconds); 
} 