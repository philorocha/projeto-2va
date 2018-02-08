#ifndef TOOLBOX_H_INCLUDED
#define TOOLBOX_H_INCLUDED
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
    /*Abre o arquivo onde será salva a estrutura com
    os dados do personagem*/
    FILE *fb = fopen("save.bin", "wb");

    /*Verifica se houve algum erro na abertura do arquivo,
    caso haja é exibida uma mensagem e o programa sai.*/
    if (!fb) {
        printf("Erro ao tentar salvar.\n");
        exit(1);
    }

    /*Escreve o que está na estrutura personagem no
    arquivo fb que foi carregado na memória*/
    fwrite(&personagem, sizeof(Personagem), 1, fb);
    printf("Salvo.\n");
    /*Fecha o arquivo efetivando as modificações*/
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

void interface(Personagem *p, Desafio *d) {
    printf("#################################################\n");
    printf("# PERSONAGEM\t\t     CRIATURA (INIMIGO) #\n");
    printf("# ENERGIA: %d\t\t     ENERGIA: %2d        #\n", p->energia, d->criatura.energia);
    printf("# HABILIDADE: %2d\t     HABILIDADE: %2d\t#\n", p->habilidade, d->criatura.habilidade);
    printf("# SORTE: %d\t\t\t\t\t#\n", p->sorte);
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

void batalha(Personagem *p, Desafio *d) {
    system("cls");
    printf("%s", d->texto);
    system("pause");
    while (p->energia > 0 && d->criatura.energia > 0) {
        int ataque_personagem = p->habilidade + dado() + dado();
        int ataque_criatura = d->criatura.habilidade + dado() + dado();
        char opcao;
        do {
            interface(p, d);
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
                                        d->criatura.energia -= 4;
                                        if (d->criatura.energia <= 0) {
                                            printf("VOCÊ TEVE SORTE E FERIU A CRIATURA EM 4.\nPARABÉNS VOCÊ VENCEU A BATALHA!\n");
                                            d->concluido = 1;
                                            concluidos += 1;
                                        } else {
                                            printf("VOCÊ TEVE SORTE E FERIU A CRIATURA EM 4.\n");
                                        }
                                    } else {
                                        d->criatura.energia -= 1;
                                        if (d->criatura.energia <= 0) {
                                            printf("VOCÊ FOI AZARADO E FERIU A CRIATURA EM 1.\nPARABÉNS VOCÊ VENCEU A BATALHA!\n");
                                            d->concluido = 1;
                                            concluidos += 1;
                                        } else {
                                            printf("VOCÊ FOI AZARADO E FERIU A CRIATURA EM 1.\n");
                                        }
                                    }
                                    break;
                                case '2':
                                    d->criatura.energia -= 2;
                                    if (d->criatura.energia <= 0) {
                                        printf("VOCÊ FERIU A CRIATURA EM 2.\nPARABÉNS VOCÊ VENCEU A BATALHA!\n");
                                        d->concluido = 1;
                                        concluidos += 1;
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
                                    p->energia -= 1;
                                    if (p->energia <= 0) {
                                        printf("VOCÊ TEVE SORTE E A CRIATURA ESQUIVOU E FERIU VOCÊ EM 1.\nVOCÊ MORREU!\n");
                                    } else {
                                        printf("VOCÊ TEVE SORTE E A CRIATURA ESQUIVOU E FERIU VOCÊ EM 1.\n");
                                    }
                                } else {
                                    p->energia -= 3;
                                    if (p->energia <= 0) {
                                        printf("VOCÊ FOI AZARADO E A CRIATURA ESQUIVOU E FERIU VOCÊ EM 3.\nVOCÊ MORREU!\n");
                                    } else {
                                        printf("VOCÊ FOI AZARADO E A CRIATURA ESQUIVOU E FERIU VOCÊ EM 3.\n");
                                    }
                                }
                                break;
                            case '2':
                                p->energia -= 2;
                                if (p->energia <= 0) {
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

    printf("%s", d->texto);
    printf("Resposta: ");
    scanf("%d", &res);

    if (res == d->resposta) {
        printf("Parabéns você acertou.\n");
        d->concluido = 1;
        concluidos += 1;
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
        printf("DESAFIOS (CONCLUIDOS/TOTAL): %d/10\n", concluidos);
        printf("-----------------------------------\n");
        printf("1 - INICIAR DESAFIO\n");
        printf("2 - SALVAR JOGO\n");
        printf("3 - SALVAR E SAIR\n");
        printf("OPÇÃO: ");

        scanf("%c", &opcao);
        fflush(stdin);

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
                save(personagem);
                save_desafios(desafios);
                break;
            default:
                printf("Opção inválida!\n");
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

    char opcao;
    do {
        tela_inicial();
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
                printf("Opção inválida.\n");
                system("pause");
                system("cls");
        }
    } while (opcao != '1' && opcao != '2');

}

#endif // TOOLBOX_H_INCLUDED
