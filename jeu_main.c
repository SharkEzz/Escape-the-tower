#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Pour le générateur de random
#include <string.h>
#include <unistd.h> // Requis pour la fonction delay()
#include <ncurses.h> // A des fins de tests pour l'aide du jeu
#include "jeu_main.h"

//Couleurs pour le terminal

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

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
    int pv_ennemi = randomf(85,100);
    int score = 0;
    int inventaire = 0; // Nombre de potion dans l'inventaire
    int ennemi_precedent = 0; // Indique si un ennemi était présent à l'étage précédent

    if(argv[1] != NULL)
    {
        if(strcmp(argv[1], "-h") == 0)
        {
            aide();
            exit(1);
        }
    }
    
    etat_partie = accueil(&etat_partie);

    //etat_partie = 1;

    while(etat_partie)
    {

        // S'occupe de générer un nombre aléatoire et en fonction de celui-ci, faire en sorte qu'une action aie lieux
        // Partie à équilibrer

        aleatoire = randomf(10,65);

        if(aleatoire > 22 && aleatoire <= 35)
        {
            potion_present = 1;
            ennemi_precedent = 0;
        }
        else if(aleatoire >= 35 && aleatoire <= 50 && etage_actuel != 0 && ennemi_precedent == 0)
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

        if(mana <= 100)
        {
            mana = mana;
        }
        else
        {
            mana = mana + 2;
        }

        aff_stats(pv, mana, etage_actuel, inventaire); // Affiche les stats en haut du terminal

        if(etage_actuel >= 50)
        {
            efface_ecran();

            printf("Félécitation ! Vous avez gagné !\n");
            printf("Votre score est de %d points !\n", score);

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
            printf("2 -> Continuer à monter\n");
            printf("3 -> La stocker\n\n");
            printf("Votre choix : ");
            scanf("%d", &choix);

            if(choix == 1)
            {
                if(pv <= 85 && mana <= 85)
                {
                    potion_present = 0;
                    pv = pv + randomf(10,30);
                    mana = mana + randomf(10,30);
                    etage_actuel++;

                    if(mana > 100)
                    {
                        mana = 100;
                    }

                    if(pv > 100)
                    {
                        pv = 100;
                    }

                }
                else
                {
                    printf("Vous avez déjâ le nombre maximal de PV et de Mana !\n");
                    sleep(5);
                    potion_present = 0;
                    etage_actuel++;
                }
                
            }
            else if (choix == 2)
            {
                potion_present = 0;
                etage_actuel++;
            }
            else if (choix == 3)
            {
                etage_actuel++;
                inventaire++;
                printf("Potion stockée dans l'inventaire.\n");
                potion_present = 0;
                sleep(3);
            }



        }

        if(ennemi_present == 1)
        {
            ennemi_present = 0;
            ennemi_precedent = 1;
            printf("Vous rencontrez un ennemi ! Préparez vous au combat !\n");
            sleep(3);
            combat(&pv, &mana, &pv_ennemi, &score, &inventaire);
            pv_ennemi = 100;
            etage_actuel++;
        }

    }


    return 0;
}

void combat(int *pv_pers, int *mana_pers, int *pv_ennemi, int *score, int *inventaire)
{
    int choix = 0;

    while(*pv_ennemi > 0)
    {
        int aleatoire = randomf(1, 17);
        int valeur_potion = randomf(10, 30);

        *pv_pers = *pv_pers - aleatoire;
        *score = *score + aleatoire;

        aff_stats_combat(*pv_pers, *mana_pers, *pv_ennemi, *inventaire);

        printf("Vous subissez %s%d%s points de dégats !\n\n", RED, aleatoire, RESET);

        if(*pv_pers <= 0)
        {
            printf("Vous avez perdu !\n");
            sleep(3);
            exit(1);
        }
        else
        {
            printf("C'est votre tour !\n\n");
            printf("Vos attaques :\n");
            printf("1 -> Attaque 1 (10 dégats | 3 mana)\n");
            printf("2 -> Attaque 2 (30 dégats | 10 mana)\n");
            printf("3 -> Attaque spéciale (70 dégats | 50 mana)\n\n");
            if(*inventaire > 0)
            {
                printf("Objets dans l'inventaire :\n");
                printf("4 -> Utiliser potion\n\n");
            }
            printf("Votre choix : ");
            scanf("%d", &choix);

            switch(choix)
            {
                case 1:
                    if(*mana_pers - 3 <= 0)
                    {
                        printf("Vous n'avez pas assez de mana pour cette attaque\n");
                        sleep(3);
                        break;
                    }
                    else
                    {
                        printf("\nVous utilisez votre attaque n°1 et infligez 10 dégats à l'ennemi !\n");
                        *pv_ennemi = *pv_ennemi - 10;
                        *mana_pers = *mana_pers - 3;
                        sleep(3);
                        break;
                    }
                
                case 2:
                    if(*mana_pers - 10 <= 0)
                    {
                        printf("Vous n'avez pas assez de mana pour cette attaque\n");
                        sleep(3);
                        break;
                    }
                    else
                    {
                        printf("\nVous utilisez votre attaque n°1 et infligez 30 dégats à l'ennemi !\n");
                        *pv_ennemi = *pv_ennemi - 30;
                        *mana_pers = *mana_pers - 10;
                        sleep(3);
                        break;
                    }
                
                case 3:
                    if(*mana_pers - 50 <= 0)
                    {   
                        printf("Vous n'avez pas assez de mana pour cette attaque\n");
                        sleep(3);
                        break;
                    }
                    else
                    {
                        printf("\nVous utilisez votre attaque spéciale et infligez 50 dégats à l'ennemi !\n");
                        *pv_ennemi = *pv_ennemi - 70;
                        *mana_pers = *mana_pers - 50;
                        sleep(3);
                        break;
                    }

                case 4:
                    if(*inventaire >= 1)
                    {
                        *pv_pers = *pv_pers + valeur_potion;
                        *mana_pers = *mana_pers + valeur_potion;
                        *inventaire = *inventaire - 1;

                        if(*pv_pers > 100 || *mana_pers > 100)
                        {
                            *pv_pers = 100;
                            *mana_pers = 100;
                        }
                        break;
                    }
                    
                    

                
            }
        }

        
    }

    
}

void aff_stats(int pv, int mana, int etage, int inventaire)
{
    if(pv >= 50)
    {
        printf("Points de vie : %s%d%s\n", GRN, pv, RESET);
    }
    else if(pv >=30 && pv < 50)
    {
        printf("Points de vie : %s%d%s\n", YEL, pv, RESET); 
    }
    else if(pv < 30)
    {
        printf("Points de vie : %s%d%s\n", RED, pv, RESET); 
    }

    if(mana >= 50)
    {
        printf("Points de mana : %s%d%s\n", GRN, mana, RESET);
    }
    else if(mana >=30 && mana < 50)
    {
        printf("Points de mana : %s%d%s\n", YEL, mana, RESET);
    }
    else if(mana < 30)
    {
        printf("Points de mana : %s%d%s\n", RED, mana, RESET);
    }

    printf("Nombre de potions stockées : %d\n", inventaire);
    printf("Etage actuel : %d\n\n\n", etage);
}

void aff_stats_combat(int pv, int mana, int pv_ennemi, int inventaire)
{
    efface_ecran();

    printf(" -- EN COMBAT -- \n\n");

    if(pv >= 50)
    {
        printf("Points de vie : %s%d%s\n", GRN, pv, RESET);
    }
    else if(pv >=30 && pv < 50)
    {
        printf("Points de vie : %s%d%s\n", YEL, pv, RESET); 
    }
    else if(pv < 30)
    {
        printf("Points de vie : %s%d%s\n", RED, pv, RESET); 
    }

    if(mana >= 50)
    {
        printf("Points de mana : %s%d%s\n", GRN, mana, RESET);
    }
    else if(mana >=30 && mana < 50)
    {
        printf("Points de mana : %s%d%s\n", YEL, mana, RESET);
    }
    else if(mana < 30)
    {
        printf("Points de mana : %s%d%s\n", RED, mana, RESET);
    }

       printf("Nombre de potions stockées : %d\n", inventaire);

    if(pv_ennemi >= 50)
    {
        printf("PV Ennemi : %s%d%s\n\n", RED, pv_ennemi, RESET);
    }
    else if(pv_ennemi >=30 && pv_ennemi < 50)
    {
        printf("PV Ennemi : %s%d%s\n\n", YEL, pv_ennemi, RESET);
    }
    else if(pv_ennemi < 30)
    {
        printf("PV Ennemi : %s%d%s\n\n", GRN, pv_ennemi, RESET);
    }

}

void aide()
{
    char *nom = "-- Escape the tower --";

    WINDOW *fenetre_aide;

    initscr();

    fenetre_aide = subwin(stdscr, LINES - 2, COLS, 2, 0);
    box(fenetre_aide, ACS_VLINE, ACS_HLINE);

    mvprintw(0, (COLS - strlen(nom))/ 2, nom);
    mvprintw(1, (COLS - strlen("AIDE v.1")) / 2, "AIDE v.1");

    wrefresh(fenetre_aide);

    getch();

    endwin();

}

int accueil(int *etat_partie)
{
    int choix = 0;

    efface_ecran();

    printf("%s -- ESCAPE THE TOWER -- %s\n\n\n", GRN, RESET);

    printf("Menu principal :\n\n");
    printf("1 -> Lancer le jeu\n");
    printf("2 -> Charger la dernière partie\n");
    printf("3 -> Quitter\n\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

    switch(choix)
    {
        case 1:
            *etat_partie = 1;
            printf("\n\nLancement de la partie !\n");
            sleep(2);
            break;
        case 2:
            printf("Pas encore implémenté\n");
            sleep(5);
            exit(1);
            break;
        case 3:
            exit(1);
            break;
    }

    return *etat_partie;
}