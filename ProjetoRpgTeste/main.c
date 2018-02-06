#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "toolbox.h"
#include "personagens.h"

int main()
{
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    char nome[20];
    char nome2[20];
    strcpy(nome, "Felipe Vieira");
    strcpy(nome2, "Denise Evellyn");
    //novo_jogo();
    printf("   .-.     .-.     .-.     .-.     .-.     .-.     .-.     .-.     .-. \n");
    printf(" .'   `._.'   `._.'   `._.'   `._.'   `._.'   `._.'   `._.'   `._.'   `.\n");
    printf("(    .     .-.     .-.     .-.     .-.     .-.     .-.     .-.     .    )\n");
    printf(" `.   `._.'   `._.'   `._.'   `._.'   `._.'   `._.'   `._.'   `._.'   .'\n");
    printf("   )    ) %20s %20s            (    (\n", nome, nome2);
    printf(" ,'   ,'                                                        `.   `.\n");
    printf("(    (                                                             )    )\n");
    printf(" `.   `.                                                         .'   .' \n");
    printf("   )    )                                                       (    (\n");
    printf(" ,'   ,'                                                         `.   `.\n");
    printf("(    (                                                             )    )\n");
    printf(" `.   `.                                                         .'   .' \n");
    printf("   )    )                                                       (    (\n");
    printf(" ,'   ,'                                                         `.   `.\n");
    printf("(    (                                                             )    )\n");
    printf(" `.   `.                                                         .'   .' \n");
    printf("   )    )       _       _       _       _       _       _       (    (\n");
    printf(" ,'   .' `.   .' `.   .' `.   .' `.   .' `.   .' `.   .' `.   .' `.   `.\n");
    printf("(    '  _  `-'  _  `-'  _  `-'  _  `-'  _  `-'  _  `-'  _  `-'  _  `    )\n");
    printf(" `.   .' `.   .' `.   .' `.   .' `.   .' `.   .' `.   .' `.   .' `.   .'\n");
    printf("   `-'     `-'     `-'     `-'     `-'     `-'     `-'     `-'     `-'\n");
    return 0;
}

