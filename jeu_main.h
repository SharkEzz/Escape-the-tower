#ifndef JEU_MAIN_H
#define JEU_MAIN_H

void aff_stats(int pv, int mana, int etage, int inventaire);

void efface_ecran()
{
    system("@cls||clear");
}

void delay(int sec)
{ 
    int milli_seconds = 1000 * sec; 
    clock_t start_time = clock(); 
    while (clock() < start_time + milli_seconds); 
}

int randomf(int min, int max) // Retourne un nombre entre min et max
{
    srand(time(NULL));
    return rand()%(max-min)+min;
}

void combat(int *pv_pers, int *mana_pers, int *pv_ennemi, int *score, int *inventaire);
void aff_stats_combat(int pv, int mana, int pv_ennemi, int inventaire);
void aide();



#endif