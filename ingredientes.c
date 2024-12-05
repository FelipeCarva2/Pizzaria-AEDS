#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ingredientes.h"

// Defini��o das vari�veis globais
Ingrediente ingredientes[MAX_INGREDIENTES];
int qtdIngredientes = 0;

// Implementa��o das fun��es

//Fun��o para adicionar ingredientes
void adicionarIngrediente() {
    if (qtdIngredientes >= MAX_INGREDIENTES) {
        printf("Limite de ingredientes atingido.\n");
        return;
    }
    Ingrediente ingrediente;
    ingrediente.id = qtdIngredientes + 1;
    printf("Nome do ingrediente: ");
    scanf(" %[^\n]", ingrediente.nome);
    printf("Pre�o do ingrediente: ");
    scanf("%f", &ingrediente.preco);

    ingredientes[qtdIngredientes++] = ingrediente;
    printf("Ingrediente adicionado com sucesso!\n");
}


//Fun��o para listar ingredientes
void listarIngredientes() {
    if (qtdIngredientes == 0) {
        printf("Nenhum ingrediente cadastrado.\n");
        return;
    }
    printf("\nIngredientes dispon�veis:\n");
    for (int i = 0; i < qtdIngredientes; i++) {
        printf("ID: %d | Nome: %s | Pre�o: %.2f\n", ingredientes[i].id, ingredientes[i].nome, ingredientes[i].preco);
    }
}


//Fun��o para editar ingredientes
void editarIngrediente() {
    listarIngredientes();
    if (qtdIngredientes == 0) return;

    int id;
    printf("Digite o ID do ingrediente a ser editado: ");
    scanf("%d", &id);

    if (id > 0 && id <= qtdIngredientes) {
        printf("Novo nome: ");
        scanf(" %[^\n]", ingredientes[id - 1].nome);
        printf("Novo pre�o: ");
        scanf("%f", &ingredientes[id - 1].preco);
        printf("Ingrediente atualizado com sucesso!\n");
    } else {
        printf("ID inv�lido.\n");
    }
}


//Fun��o para remover ingredientes
void removerIngrediente() {
    listarIngredientes();
    if (qtdIngredientes == 0) return;

    int id;
    printf("Digite o ID do ingrediente a ser removido: ");
    scanf("%d", &id);

    if (id > 0 && id <= qtdIngredientes) {
        for (int i = id - 1; i < qtdIngredientes - 1; i++) {
            ingredientes[i] = ingredientes[i + 1];
        }
        qtdIngredientes--;
        printf("Ingrediente removido com sucesso!\n");
    } else {
        printf("ID inv�lido.\n");
    }
}


//Fun��o para salvar ingredientes no arquivo
void salvarIngredientesEmArquivo() {
    // Abrir o arquivo de ingredientes em modo de escrita
    FILE *file = fopen("ingredientes.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de ingredientes.\n");
        return;
    }

    // Escrever todos os ingredientes no arquivo
    for (int i = 0; i < qtdIngredientes; i++) {
        fprintf(file, "%d;%s;%.2f\n", ingredientes[i].id, ingredientes[i].nome, ingredientes[i].preco);
    }

    // Fechar o arquivo ap�s a grava��o
    fclose(file);
    printf("Ingredientes salvos com sucesso em ingredientes.txt!\n");
}


//Fun��o para carregar ingredientes de um arquivo
void importarIngredientesDeArquivo() {
    // Abrir o arquivo de ingredientes em modo de leitura
    FILE *file = fopen("ingredientes.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de ingredientes para leitura.\n");
        return;
    }

    // Vari�veis auxiliares para ler os dados
    Ingrediente ingrediente;
    while (fscanf(file, "%d;%49[^;];%f\n", &ingrediente.id, ingrediente.nome, &ingrediente.preco) == 3) {
        // Adicionar o ingrediente lido � lista de ingredientes
        if (qtdIngredientes < MAX_INGREDIENTES) {
            ingredientes[qtdIngredientes++] = ingrediente;
        } else {
            printf("Limite de ingredientes atingido!\n");
            break;
        }
    }

    // Fechar o arquivo ap�s a leitura
    fclose(file);
    printf("Ingredientes importados com sucesso de ingredientes.txt!\n");
}


