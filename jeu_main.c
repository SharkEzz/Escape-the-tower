#include <stdio.h>
#include <stdlib.h>
#include "jeu_main.h"

int main(int argc, char *argv[])
{

    if(argv[1] == "-h")
        help();

    return 0;
}

void help()
{
    printf("Ceci est l'aide");
}
