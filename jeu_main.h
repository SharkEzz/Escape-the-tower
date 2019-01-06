#ifndef JEU_MAIN_H
#define JEU_MAIN_H

void aff_stats(int pv, int mana, int etage, int inventaire);

void efface_ecran()
{
    system("@cls||clear");
}

int randomf(int min, int max) // Retourne un nombre entre min et max
{
    srand(time(NULL));
    return rand()%(max-min)+min;
}

void combat(int *pv_pers, int *mana_pers, int *pv_ennemi, int *score, int *inventaire);
void aff_stats_combat(int pv, int mana, int pv_ennemi, int inventaire);
void aide();
int accueil(int *etat_partie);



#endif