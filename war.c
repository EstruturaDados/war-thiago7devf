/*
        Nível Aventureiro

    Objetivo

Criar uma structchamada Territorio.
Usar um vetor estático de 5 elementos para armazenar os territórios.
Cadastrar os dados de cada território: Nome , Cor do Exército , e Número de Tropas .
Exibir o estado atual do mapa.

    Funcionalidades

Leitura de dados pelo terminal ( fgetse scanf)
Impressão organizada dos dados de todos os territórios

    Conceitos abordados
struct
Vetor estático
Entrada/saída com scanf, fgets, eprintf

    Entrada
O usuário digita o nome do território, o corpo do exército dominante e o número de tropas para cada um dos 5 territórios .

    Saída
*/

//bibliotecas usadas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERR 5
#define TAM_NOME 40
#define TAM_COR 20

// Estrutura do território
typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

// Limpeza de buffer
void limpaBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Cadastro dos 5 territórios
void cadastrarTerritorios(Territorio mapa[], int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cadastrando Territorio %d ---\n", i + 1);

        printf("Nome do Territorio: ");
        fgets(mapa[i].nome, TAM_NOME, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do Exercito: ");
        fgets(mapa[i].cor, TAM_COR, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Numero de Tropas: ");
        while (scanf("%d", &mapa[i].tropas) != 1) {
            printf("Entrada inválida. Digite um número: ");
            limpaBuffer();
        }
        limpaBuffer();
    }
}

// Mostrar estado atual do mapa
void mostrarMapa(Territorio mapa[], int qtd) {
    printf("\n=====================================\n");
    printf("       MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("=====================================\n\n");

    for (int i = 0; i < qtd; i++) {
        printf("%d. %s (Exército %s, Tropas: %d)\n",
            i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("\n");
}

// Função de ataque com REGRAS DE CONQUISTA
void atacar(Territorio *atacante, Territorio *defensor) {
    if (atacante->tropas <= 1) {
        printf("\nO atacante precisa de mais de 1 tropa para atacar!\n");
        return;
    }

    int dado_atk = (rand() % 6) + 1;
    int dado_def = (rand() % 6) + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("Atacante %s rolou: %d\n", atacante->nome, dado_atk);
    printf("Defensor %s rolou: %d\n", defensor->nome, dado_def);

    if (dado_atk > dado_def) {
        defensor->tropas -= 1;
        printf(">>> Ataque VENCEU! O defensor perdeu 1 tropa.\n");

        // CONQUISTA DO TERRITÓRIO
        if (defensor->tropas == 0) {
            printf("\n>>> O TERRITÓRIO %s FOI CONQUISTADO! <<<\n", defensor->nome);

            strcpy(defensor->cor, atacante->cor); // muda dono

            atacante->tropas -= 1;  // atacante envia 1 tropa obrigatória
            defensor->tropas = 1;   // território recém-conquistado fica com 1 tropa

            printf("O atacante moveu 1 tropa para ocupar o território conquistado!\n");
        }

    } else {
        atacante->tropas -= 1;
        printf(">>> Defesa segurou! O atacante perdeu 1 tropa.\n");
    }
}

int main(void) {
    srand((unsigned)time(NULL));

    int qtd = MAX_TERR;

    // Agora usando calloc para alocar memória para os territórios
    Territorio *mapa = (Territorio*) calloc(qtd, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    printf("Cadastro inicial de %d territórios (1 a %d):\n", qtd, qtd);
    cadastrarTerritorios(mapa, qtd);

    mostrarMapa(mapa, qtd);

    while (1) {
        printf("--- FASE DE ATAQUE ---\n");
        printf("Escolha o territorio ATACANTE (1 a %d ou 0 para sair): ", qtd);

        int atk, def;
        if (scanf("%d", &atk) != 1) {
            printf("Entrada inválida!\n");
            limpaBuffer();
            continue;
        }

        if (atk == 0) break;

        if (atk < 1 || atk > qtd) {
            printf("ID inválido! Escolha entre 1 e %d.\n", qtd);
            limpaBuffer();
            continue;
        }

        printf("Escolha o territorio DEFENSOR (1 a %d): ", qtd);
        if (scanf("%d", &def) != 1) {
            printf("Entrada inválida!\n");
            limpaBuffer();
            continue;
        }
        limpaBuffer();

        if (def < 1 || def > qtd) {
            printf("ID inválido! Escolha entre 1 e %d.\n", qtd);
            continue;
        }

        if (atk == def) {
            printf("Um territorio não pode atacar ele mesmo!\n");
            continue;
        }

        int A = atk - 1;
        int D = def - 1;

        if (strcmp(mapa[A].cor, mapa[D].cor) == 0) {
            printf("Você NÃO pode atacar territórios da mesma cor!\n");
            continue;
        }

        atacar(&mapa[A], &mapa[D]);

        printf("\nPressione ENTER para continuar...");
        getchar();

        mostrarMapa(mapa, qtd);
    }

    free(mapa);   // libera memória
    printf("\nJogo encerrado! memória liberada! Obrigado por jogar.\n");

   

    return 0;
}
