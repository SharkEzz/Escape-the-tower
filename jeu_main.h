#ifndef JEU_MAIN_H
#define JEU_MAIN_H

void aff_stats(int pv, int mana, int etage);

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

int random(int min, int max) // Retourne un nombre entre min et max
{
    return rand()%(max-min)+min;
}


#endif