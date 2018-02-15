#ifndef PERSONAGENS_H_INCLUDED
#define PERSONAGENS_H_INCLUDED

typedef struct {
    char nome[20];
    int habilidade;
    int energia;
    int energia_max;
    int sorte;
    int pocao_energia[5];
    int pocoes_utilizadas;
} Personagem;

typedef struct {
    char nome[20];
    int habilidade;
    int energia;
} Criatura;

typedef struct {
    char texto[2500];
    int concluido; /* Se esse desafio foi concluido 1, caso contrário 0 */
    Criatura criatura;
    int resposta;
    int tipo; /* se for desafio 1, se for batalha 2*/
} Desafio;

#endif // PERSONAGENS_H_INCLUDED
