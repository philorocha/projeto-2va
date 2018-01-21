#ifndef TOOLBOX_H_INCLUDED
#define TOOLBOX_H_INCLUDED
#include "personagens.h"

Desafio desafios[10];

void save(Personagem personagem) {
    FILE *fb = fopen("save.bin", "wb");

    if (!fb) {
        printf("Erro ao tentar salvar.\n");
        exit(1);
    }

    fwrite(&personagem, sizeof(Personagem), 1, fb);
    printf("Salvo.\n");
    fclose(fb);
}

Personagem load() {
    /*Carregando o personagem*/
    Personagem personagem;

    FILE *fb = fopen("save.bin", "rb");

    if (!fb) {
        printf("Erro ao tentar carregar.\n");
        exit(1);
    }

    fread(&personagem, sizeof(Personagem), 1, fb);
    printf("Carregado.\n");
    fclose(fb);

    /*Carregando desafios*/
    int i;

    FILE *df = fopen("desafios.bin", "rb");

    if (!df) {
        printf("Erro ao tentar abrir arquivo.\n");
        exit(1);
    }

    for (i = 0; i < 1; i++) {
        fseek(df, sizeof(Desafio) * i, SEEK_SET);
        /*Os desafios do arquivo desafios.bin são carregados na variável global desafios
        que é um vetor de Desafio com 10 posições*/
        fread(&desafios[i], sizeof(Desafio), 1, df);
    }

    fclose(df);

    /*Retornando estrutura do tipo Personagem*/
    return personagem;
}

void ajuda() {
    FILE *f = fopen("ajuda.txt", "r");

    if (f == NULL) {
        printf("Erro ao tentar abrir o arquivo.\n");
        exit(1);
    }

    char mensagem[1000];

    system("cls");
    while(fgets(mensagem, 1000, f) != NULL){
        printf("%s", mensagem);
    }

    fclose(f);
}

void interface(Personagem *p, Criatura *c) {
    printf("#################################################\n");
    printf("# PERSONAGEM\t\t     CRIATURA (INIMIGO) #\n");
    printf("# ENERGIA: %d\t\t     ENERGIA: %2d        #\n", (*p).energia, (*c).energia);
    printf("# HABILIDADE: %2d\t     HABILIDADE: %2d\t#\n", (*p).habilidade, (*c).habilidade);
    printf("# SORTE: %d\t\t\t\t\t#\n", (*p).sorte);
    printf("#################################################\n");
    printf("#                  CONTROLES                    #\n");
    printf("# 1 - ATACAR                   3 - AJUDA (DICAS)#\n");
    printf("# 2 - FUGIR                                     #\n");
    printf("#################################################\n");
    printf("OPÇÃO: ");
}

void interface_sorte_ataque() {
    printf("#################################################\n");
    printf("# DESEJA TESTAR A SORTE PARA CAUSAR MAIS DANO?	#\n");
    printf("# SE FOR SORTUDO CAUSA O DOBRO DE DANO (4 PTS)  #\n");
    printf("# SE FOR AZARADO CAUSA 1 PONTO A MENOS (1 PT)	#\n");
    printf("# DANO ATUAL CAUSADO: 2                         #\n");
    printf("#################################################\n");
    printf("# 1 - QUERO TESTAR A SORTE                      #\n");
    printf("# 2 - NÃO QUERO TESTAR A SORTE                  #\n");
    printf("#################################################\n");
    printf("OPÇÃO: ");
}

void interface_sorte_energia() {
    printf("#################################################\n");
    printf("# DESEJA TESTAR A SORTE PARA DIMINUIR O DANO	#\n");
    printf("# RECEBIDO?                                     #\n");
    printf("# SE FOR SORTUDO DIMINUI EM 1PT O DANO RECEBIDO #\n");
    printf("# SE FOR AZARADO RECEBE 1PT DE DANO EXTRA       #\n");
    printf("# DANO ATUAL RECEBIDO: 2                        #\n");
    printf("#################################################\n");
    printf("# 1 - QUERO TESTAR A SORTE                      #\n");
    printf("# 2 - NÃO QUERO TESTAR A SORTE                  #\n");
    printf("#################################################\n");
    printf("OPÇÃO: ");
}

int dado() {
    return rand() % 6 + 1;
}

int testarSorte(Personagem *p) {
    if (dado() + dado() <= (*p).sorte) {
        (*p).sorte -= 1;
        return 1;
    }
    (*p).sorte -= 1;
    return 0;
}

void batalha(Personagem *p, Criatura *c) {
    while ((*p).energia > 0 && (*c).energia > 0) {
        int ataque_personagem = (*p).habilidade + dado() + dado();
        int ataque_criatura = (*c).habilidade + dado() + dado();
        char opcao;
        do {
            interface(p, c);
            scanf("%c", &opcao);
            fflush(stdin);
            switch (opcao) {
                case '1':
                    if (ataque_personagem > ataque_criatura) {
                            interface_sorte_ataque();
                            char opcao_sorte;
                            scanf("%c", &opcao_sorte);
                            fflush(stdin);
                            switch (opcao_sorte) {
                                case '1':
                                    if (testarSorte(p)) {
                                        (*c).energia -= 4;
                                        if ((*c).energia <= 0) {
                                            printf("VOCÊ TEVE SORTE E FERIU A CRIATURA EM 4.\nPARABÉNS VOCÊ VENCEU A BATALHA!\n");
                                        } else {
                                            printf("VOCÊ TEVE SORTE E FERIU A CRIATURA EM 4.\n");
                                        }
                                    } else {
                                        (*c).energia -= 1;
                                        if ((*c).energia <= 0) {
                                            printf("VOCÊ FOI AZARADO E FERIU A CRIATURA EM 1.\nPARABÉNS VOCÊ VENCEU A BATALHA!\n");
                                        } else {
                                            printf("VOCÊ FOI AZARADO E FERIU A CRIATURA EM 1.\n");
                                        }
                                    }
                                    break;
                                case '2':
                                    (*c).energia -= 2;
                                    if ((*c).energia <= 0) {
                                        printf("VOCÊ FERIU A CRIATURA EM 2.\nPARABÉNS VOCÊ VENCEU A BATALHA!\n");
                                    } else {
                                        printf("VOCÊ FERIU A CRIATURA EM 2.\n");
                                    }
                                    break;
                                default:
                                    printf("OPÇÃO INVÁLIDA!\n");
                            }
                            system("pause");
                    } else if (ataque_personagem < ataque_criatura) {
                        interface_sorte_energia();
                        char opcao_sorte;
                        scanf("%c", &opcao_sorte);
                        switch (opcao_sorte) {
                            case '1':
                                if (testarSorte(p)) {
                                    (*p).energia -= 1;
                                    if ((*p).energia <= 0) {
                                        printf("VOCÊ TEVE SORTE E A CRIATURA ESQUIVOU E FERIU VOCÊ EM 1.\nVOCÊ MORREU!\n");
                                    } else {
                                        printf("VOCÊ TEVE SORTE E A CRIATURA ESQUIVOU E FERIU VOCÊ EM 1.\n");
                                    }
                                } else {
                                    (*p).energia -= 3;
                                    if ((*p).energia <= 0) {
                                        printf("VOCÊ FOI AZARADO E A CRIATURA ESQUIVOU E FERIU VOCÊ EM 3.\nVOCÊ MORREU!\n");
                                    } else {
                                        printf("VOCÊ FOI AZARADO E A CRIATURA ESQUIVOU E FERIU VOCÊ EM 3.\n");
                                    }
                                }
                                break;
                            case '2':
                                (*p).energia -= 2;
                                if ((*p).energia <= 0) {
                                    printf("A CRIATURA ESQUIVOU E FERIU VOCÊ EM 2.\nVOCÊ MORREU!\n");
                                } else {
                                    printf("A CRIATURA ESQUIVOU E FERIU VOCÊ EM 2.\n");
                                }
                                break;
                            default:
                                printf("OPÇÃO INVÁLIDA!\n");
                        }
                        system("pause");
                    } else {
                        printf("AMBOS DEFENDERAM O ATAQUE.\n");
                        system("pause");
                    }
                    break;
                case '2':
                    printf("Não implementado ainda.\n");
                    system("pause");
                    break;
                case '3':
                    ajuda();
                    system("pause");
                    break;
                default:
                    printf("Opção inválida.\n");
                    getchar();
            }
            system("cls");
        } while(opcao != '1' && opcao != '2' && opcao != '3' && opcao != '4');
    }
}

void desafio(Personagem *personagem, Desafio *d) {
    system("cls");

    int res;

    printf("%s", (*d).texto);
    printf("Resposta: ");
    scanf("%d", &res);

    if (res == (*d).resposta) {
        printf("Parabéns você acertou.\n");
        (*d).concluido = 1;

    } else {
        printf("Voce errou.\n");
    }
    fflush(stdin);
}

void interface_personagem(Personagem personagem) {
    int i;
    char opcao;
    do {
        system("cls");
        printf("STATUS DO PERSONAGEM:\n");
        printf("-----------------------------------\n");
        printf("PERSONAGEM: %s\n", personagem.nome);
        printf("ENERGIA: %d\n", personagem.energia);
        printf("HABILIDADE: %d\n", personagem.habilidade);
        printf("SORTE: %d\n", personagem.sorte);
        printf("\n");
        printf("DESAFIOS (CONCLUIDOS/TOTAL): 0/10\n");
        printf("-----------------------------------\n");
        printf("1 - INICIAR DESAFIO\n");
        printf("2 - SALVAR JOGO\n");
        printf("3 - SALVAR E SAIR\n");
        printf("OPÇÃO: ");

        scanf("%c", &opcao);
        fflush(stdin);

        switch (opcao) {
            case '1':
                for (i = 0; i < 1; i++) {
                    if (!desafios[i].concluido) {
                        printf("Encontrei um desafio não concluido.\n");
                        printf("%s", desafios[i].texto);
                        system("pause");
                    }
                }
                break;
            case '2':
                save(personagem);
                break;
            case '3':
                save(personagem);
                break;
            default:
                printf("Opção inválida!\n");
                system("pause");
        }
    } while (opcao != '3');

}

void novo_jogo() {
    Personagem jogador;

    FILE *f = fopen("tela_inicial.txt", "r");

    if (f == NULL) {
        printf("Erro ao tentar abrir o arquivo.\n");
        exit(1);
    }

    char mensagem[2200];

    system("cls");
    fread(mensagem, sizeof(mensagem), 1, f);

    fclose(f);

    char opcao;
    do {
        printf("%s", mensagem);
        scanf("%c", &opcao);
        fflush(stdin);
        switch (opcao) {
            case '1':
                do {
                    printf("Nome do Jogador: ");
                    fflush(stdin);
                    gets(jogador.nome);
                } while (strlen(jogador.nome) < 1);
                jogador.habilidade = dado() + 6;
                jogador.energia = dado() + dado() + 12;
                jogador.sorte = dado() + 6;
                save(jogador);
                interface_personagem(jogador);
                break;
            case '2':
                jogador = load();
                interface_personagem(jogador);
                break;
            default:
                printf("Opção inválida.\n");
                system("pause");
                system("cls");
        }
    } while (opcao != '1' && opcao != '2');

}

#endif // TOOLBOX_H_INCLUDED
