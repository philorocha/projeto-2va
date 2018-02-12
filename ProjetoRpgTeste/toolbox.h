#ifndef TOOLBOX_H_INCLUDED
#define TOOLBOX_H_INCLUDED
#include <conio.h>
#include "personagens.h"

Desafio desafios[10];
int concluidos = 0;

void introducao(){
    FILE *intro = fopen("introducao.txt", "r");
    char msg[1000];

    if (!intro){
        printf("Erro ao tentar ler o arquivo! \n");
        exit(1);
    }

    while(fgets(msg, sizeof(msg), intro) != NULL){
        printf("%s", msg);
    }

    fclose(intro);
}

void save_desafios(Desafio desafios[]) {
    FILE *db = fopen("desafios.bin", "wb");

    if (!db) {
        printf("Erro ao tentar salvar.\n");
        exit(1);
    }

    fwrite(desafios, sizeof(Desafio), 10, db);

    fclose(db);
}

void load_desafios() {
    FILE *db = fopen("desafios.bin", "rb");

    if (!db) {
        printf("Erro ao tentar carregar desafios!\n");
        exit(1);
    }
    int cont = 0;

    while(fread(&desafios[cont], sizeof(Desafio), 1, db)) {
        if (desafios[cont].concluido) {
            concluidos += 1;
        }
        cont++;
    }

    fclose(db);
}

void load_desafios_bck() {
    FILE *db = fopen("desafios_bck.bin", "rb");

    if (!db) {
        printf("Erro ao tentar carregar desafios_bck.bin!\n");
        exit(1);
    }

    fread(desafios, sizeof(Desafio), 10, db);

    fclose(db);
}

void save(Personagem personagem) {
    FILE *fb = fopen("save.bin", "wb");

    if (!fb) {
        printf("Erro ao tentar salvar.\n");
        exit(1);
    }

    fwrite(&personagem, sizeof(Personagem), 1, fb);
    printf("\nSalvo.\n");

    fclose(fb);
}

Personagem load() {
    Personagem personagem;

    FILE *fb = fopen("save.bin", "rb");

    if (!fb) {
        printf("Erro ao tentar carregar.\n");
        exit(1);
    }

    fread(&personagem, sizeof(Personagem), 1, fb);
    printf("\nCarregado.\n");
    fclose(fb);

    return personagem;
}

void ajuda() {
    FILE *f = fopen("ajuda.txt", "r");

    if (!f) {
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

void interface(Personagem *p, Desafio *d) {
    printf("#################################################\n");
    printf("# %-20s  VS %20s #\n", p->nome, d->criatura.nome);
    printf("# ENERGIA: %-20dENERGIA: %7d #\n", p->energia, d->criatura.energia);
    printf("# HABILIDADE: %-17dHABILIDADE: %4d\t#\n", p->habilidade, d->criatura.habilidade);
    printf("# SORTE: %-38d #\n", p->sorte);
    printf("#################################################\n");
    printf("#                  CONTROLES                    #\n");
    printf("# 1 - ATACAR                   2 - AJUDA (DICAS)#\n");
    printf("#################################################\n");
    printf("OPÇÃO: ");
}

void interface_sorte_ataque() {
    printf("\n#################################################\n");
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
    printf("\n#################################################\n");
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

int valida_sorte(Personagem *p) {
    if (p->sorte > 0) return 1;

    return 0;
}

void batalha(Personagem *p, Desafio *d) {
    system("cls");
    printf("%s", d->texto);
    system("pause");
    while (p->energia > 0 && d->criatura.energia > 0) {
        int ataque_personagem = p->habilidade + dado() + dado();
        int ataque_criatura = d->criatura.habilidade + dado() + dado();
        int opcao;
        do {
            interface(p, d);
            opcao = getche();
            switch (opcao) {
                case '1':
                    if (ataque_personagem > ataque_criatura) {
                        int opcao_sorte;
                        do {
                            interface_sorte_ataque();
                            opcao_sorte = getche();
                            if (opcao_sorte != '1' && opcao_sorte != '2') {
                                system("cls");
                                printf("\nOpção Inválida!\nPressione qualquer tecla para continuar...");
                                getche();
                            }
                        } while (opcao_sorte != '1' && opcao_sorte != '2');
                        switch (opcao_sorte) {
                            case '1':
                                if (valida_sorte(p)) {
                                    if (testarSorte(p)) {
                                        d->criatura.energia -= 4;
                                        if (d->criatura.energia <= 0) {
                                            printf("\nVOCÊ TEVE SORTE E FERIU A CRIATURA EM 4.\nPARABÉNS VOCÊ VENCEU A BATALHA!\n");
                                            d->concluido = 1;
                                            concluidos += 1;
                                        } else {
                                            printf("\nVOCÊ TEVE SORTE E FERIU A CRIATURA EM 4.\n");
                                        }
                                    } else {
                                        d->criatura.energia -= 1;
                                        if (d->criatura.energia <= 0) {
                                            printf("\nVOCÊ FOI AZARADO E FERIU A CRIATURA EM 1.\nPARABÉNS VOCÊ VENCEU A BATALHA!\n");
                                            d->concluido = 1;
                                            concluidos += 1;
                                        } else {
                                            printf("\nVOCÊ FOI AZARADO E FERIU A CRIATURA EM 1.\n");
                                        }
                                    }
                                } else {
                                    printf("\nVOCÊ NÃO TEM PONTOS DE SORTE PARA USAR!\n");
                                }
                                break;
                            case '2':
                                d->criatura.energia -= 2;
                                if (d->criatura.energia <= 0) {
                                    printf("\nVOCÊ FERIU A CRIATURA EM 2.\nPARABÉNS VOCÊ VENCEU A BATALHA!\n");
                                    d->concluido = 1;
                                    concluidos += 1;
                                } else {
                                    printf("\nVOCÊ FERIU A CRIATURA EM 2.\n");
                                }
                                break;
                            default:
                                printf("\nOPÇÃO INVÁLIDA!\n");
                        }
                        system("pause");
                    } else if (ataque_personagem < ataque_criatura) {
                        int opcao_sorte;
                        do {
                            interface_sorte_energia();
                            opcao_sorte = getche();
                            if (opcao_sorte != '1' && opcao_sorte != '2') {
                                system("cls");
                                printf("\nOpção Inválida!\nPressione qualquer tecla para continuar...");
                                getche();
                            }
                        } while (opcao_sorte != '1' && opcao_sorte != '2');
                        switch (opcao_sorte) {
                            case '1':
                                if (valida_sorte(p)) {
                                    if (testarSorte(p)) {
                                        p->energia -= 1;
                                        if (p->energia <= 0) {
                                            printf("\nVOCÊ TEVE SORTE E A CRIATURA ESQUIVOU E FERIU VOCÊ EM 1.\nVOCÊ MORREU!\n");
                                        } else {
                                            printf("\nVOCÊ TEVE SORTE E A CRIATURA ESQUIVOU E FERIU VOCÊ EM 1.\n");
                                        }
                                    } else {
                                        p->energia -= 3;
                                        if (p->energia <= 0) {
                                            printf("\nVOCÊ FOI AZARADO E A CRIATURA ESQUIVOU E FERIU VOCÊ EM 3.\nVOCÊ MORREU!\n");
                                        } else {
                                            printf("\nVOCÊ FOI AZARADO E A CRIATURA ESQUIVOU E FERIU VOCÊ EM 3.\n");
                                        }
                                    }
                                } else {
                                    printf("\nVOCÊ NÃO TEM PONTOS DE SORTE PARA USAR!\n");
                                }
                                break;
                            case '2':
                                p->energia -= 2;
                                if (p->energia <= 0) {
                                    printf("\nA CRIATURA ESQUIVOU E FERIU VOCÊ EM 2.\nVOCÊ MORREU!\n");
                                } else {
                                    printf("\nA CRIATURA ESQUIVOU E FERIU VOCÊ EM 2.\n");
                                }
                                break;
                            default:
                                printf("\nOPÇÃO INVÁLIDA!\n");
                        }
                        system("pause");
                    } else {
                        printf("\nAMBOS DEFENDERAM O ATAQUE.\n");
                        system("pause");
                    }
                    break;
                case '2':
                    ajuda();
                    system("pause");
                    break;
                default:
                    printf("\nOpção inválida. Pressione qualquer tecla para continuar...");
                    getche();
            }
            system("cls");
        } while(opcao != '1' && opcao != '2');
    }
}

void desafio(Personagem *personagem, Desafio *d) {
    system("cls");

    int res;

    printf("%s", d->texto);
    printf("Resposta: ");
    scanf("%d", &res);

    if (res == d->resposta) {
        printf("Parabéns você acertou.\n");
        system("pause");
        d->concluido = 1;
        concluidos += 1;
    } else {
        printf("Voce errou.\n");
        system("pause");
    }
    fflush(stdin);
}

void game_over() {
    FILE *f = fopen("gameover.txt", "r");

    if (!f) {
        printf("Erro ao tentar ler o arquivo gameover.txt!\n");
        exit(1);
    }

    char msg[500];

    while (fgets(msg, sizeof(msg), f) != NULL) {
        printf("%s", msg);
    }

    fclose(f);
}

void interface_personagem(Personagem personagem) {
    int i;
    int opcao;
    do {
        if (concluidos == 10) {
            printf("VOCÊ VENCEU O JOGO! PARABÉNS\n");
            break;
        }
        if (personagem.energia <= 0) {
            game_over();
            break;
        }
        system("cls");
        printf("STATUS DO PERSONAGEM:\n");
        printf("-----------------------------------\n");
        printf("PERSONAGEM: %s\n", personagem.nome);
        printf("ENERGIA: %d\n", personagem.energia);
        printf("HABILIDADE: %d\n", personagem.habilidade);
        printf("SORTE: %d\n", personagem.sorte);
        printf("\n");
        printf("DESAFIOS (CONCLUIDOS/TOTAL): %d/10\n", concluidos);
        printf("-----------------------------------\n");
        printf("1 - INICIAR DESAFIO\n");
        printf("2 - SALVAR JOGO\n");
        printf("3 - SAIR\n");
        printf("OPÇÃO: ");

        opcao = getche();

        switch (opcao) {
            case '1':
                for (i = 0; i < 10; i++) {
                    if (desafios[i].concluido != 1) {
                        if (desafios[i].tipo == 1) {
                            desafio(&personagem, &desafios[i]);
                            break;
                        } else {
                            batalha(&personagem, &desafios[i]);
                            break;
                        }
                    }
                }
                break;
            case '2':
                save(personagem);
                save_desafios(desafios);
                break;
            case '3':
                break;
            default:
                printf("\nOpção inválida!\n");
                system("pause");
        }
    } while (opcao != '3');

}

void tela_inicial() {
    FILE *f = fopen("tela_inicial.txt", "r");

    if (f == NULL) {
        printf("Erro ao tentar abrir o arquivo.\n");
        exit(1);
    }

    char mensagem[1000];

    system("cls");
    while (fgets(mensagem, sizeof(mensagem), f) != NULL) {
        printf("%s", mensagem);
    }

    fclose(f);
}

void novo_jogo() {
    Personagem jogador;

    int opcao;
    do {
        tela_inicial();
        opcao = getche();
        switch (opcao) {
            case '1':
                do {
                    printf("\nNome do Jogador: ");
                    fflush(stdin);
                    gets(jogador.nome);
                } while (strlen(jogador.nome) < 1);
                jogador.habilidade = dado() + 6;
                jogador.energia = dado() + dado() + 12;
                jogador.sorte = dado() + 6;
                save(jogador);
                load_desafios_bck();
                system("cls");
                introducao();
                system("pause");
                interface_personagem(jogador);
                break;
            case '2':
                jogador = load();
                load_desafios();
                interface_personagem(jogador);
                break;
            default:
                printf("\nOpção inválida.\n");
                system("pause");
                system("cls");
        }
    } while (opcao != '1' && opcao != '2');

}

#endif // TOOLBOX_H_INCLUDED
