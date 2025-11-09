/*
        Nível Novato: Cadastro Inicial dos Territórios

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

//Configuracoes de Contrantes
#define MAX_TERRITORIO 5
#define TAM_STRING_NOME 30
#define TAM_STRING_COR 10

//Definindo a estrutula Struct
struct TERRITORIO {
    char nome[TAM_STRING_NOME];
    char cor[TAM_STRING_COR];
    int num_tropas;
};

// limpar buffer de entrada para evitar erros de fgets
void LimpaBuffer(){
    int c;
    while ((c = getchar())!= '\n' && c != EOF);   
}

// funcao principal
int main(){

    // difinindo o tamanho do territorio || contador territorio
    struct TERRITORIO biblioteca[MAX_TERRITORIO];
    int total_Territorios = 0;
    

    //mensagem de inicializacao
    printf("=====================================\n");
    printf("     SEJA BEM-VINDO AO JOGO WAR\n");
    printf("=====================================\n\n");
    printf("    Cadastraremos 5 territorios\n\n");

    //cadastros de territorios
    for ( int i = 0; i < MAX_TERRITORIO; i++){
        printf("=====================================\n");
        printf("   --- Cadastro territorio nº %d  ---   \n", i+1);
        printf("Nome do territorio: ");
        fgets(biblioteca[total_Territorios].nome,TAM_STRING_NOME,stdin);

        printf("Cor do exercito: ");
        fgets(biblioteca[total_Territorios].cor,TAM_STRING_COR,stdin);

        biblioteca[total_Territorios].nome[strcspn(biblioteca[total_Territorios].nome, "\n")] = '\0';
        biblioteca[total_Territorios].cor[strcspn(biblioteca[total_Territorios].cor, "\n")] = '\0';


        printf("Quantidade de tropas: ");
        scanf("%d", &biblioteca[total_Territorios].num_tropas);
        printf("=====================================\n");
        printf("\n");

        //limpeza de buffer para evitar erros
        LimpaBuffer();

        //atribuicao para contagem
        total_Territorios++;
    }

    //para organizacao do condigo e informar o usuario
    printf("\n"); 
    printf("    Cadastro realizado com sucesso!\n");
    printf("---- MAPA DO MUNDO LISTAGEM ATUAL ----\n\n\n");

    for( int i = 0; i < total_Territorios; i++){

        printf("=====Territorio nº %d =====\n", i+1);
        printf("Nome: %s\n",biblioteca[i].nome);
        printf("Cor do exercito: %s\n",biblioteca[i].cor);
        printf("Quantidade de tropas: %d\n",biblioteca[i].num_tropas);
        printf("===========================\n");
        printf("\n");
    }
}