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

    novo_jogo();

    return 0;
}

