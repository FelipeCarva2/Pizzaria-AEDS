#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ingredientes.h"

// Definição das variáveis globais
Ingrediente ingredientes[MAX_INGREDIENTES];
int qtdIngredientes = 0;

// Implementação das funções

//Função para adicionar ingredientes
void adicionarIngrediente() {
    if (qtdIngredientes >= MAX_INGREDIENTES) {
        printf("Limite de ingredientes atingido.\n");
        return;
    }
    Ingrediente ingrediente;
    ingrediente.id = qtdIngredientes + 1;
    printf("Nome do ingrediente: ");
    scanf(" %[^\n]", ingrediente.nome);
    printf("Preço do ingrediente: ");
    scanf("%f", &ingrediente.preco);

    ingredientes[qtdIngredientes++] = ingrediente;
    printf("Ingrediente adicionado com sucesso!\n");
}


//Função para listar ingredientes
void listarIngredientes() {
    if (qtdIngredientes == 0) {
        printf("Nenhum ingrediente cadastrado.\n");
        return;
    }
    printf("\nIngredientes disponíveis:\n");
    for (int i = 0; i < qtdIngredientes; i++) {
        printf("ID: %d | Nome: %s | Preço: %.2f\n", ingredientes[i].id, ingredientes[i].nome, ingredientes[i].preco);
    }
}


//Função para editar ingredientes
void editarIngrediente() {
    listarIngredientes();
    if (qtdIngredientes == 0) return;

    int id;
    printf("Digite o ID do ingrediente a ser editado: ");
    scanf("%d", &id);

    if (id > 0 && id <= qtdIngredientes) {
        printf("Novo nome: ");
        scanf(" %[^\n]", ingredientes[id - 1].nome);
        printf("Novo preço: ");
        scanf("%f", &ingredientes[id - 1].preco);
        printf("Ingrediente atualizado com sucesso!\n");
    } else {
        printf("ID inválido.\n");
    }
}


//Função para remover ingredientes
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
        printf("ID inválido.\n");
    }
}


//Função para salvar ingredientes no arquivo
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

    // Fechar o arquivo após a gravação
    fclose(file);
    printf("Ingredientes salvos com sucesso em ingredientes.txt!\n");
}


//Função para carregar ingredientes de um arquivo
void importarIngredientesDeArquivo() {
    // Abrir o arquivo de ingredientes em modo de leitura
    FILE *file = fopen("ingredientes.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de ingredientes para leitura.\n");
        return;
    }

    // Variáveis auxiliares para ler os dados
    Ingrediente ingrediente;
    while (fscanf(file, "%d;%49[^;];%f\n", &ingrediente.id, ingrediente.nome, &ingrediente.preco) == 3) {
        // Adicionar o ingrediente lido à lista de ingredientes
        if (qtdIngredientes < MAX_INGREDIENTES) {
            ingredientes[qtdIngredientes++] = ingrediente;
        } else {
            printf("Limite de ingredientes atingido!\n");
            break;
        }
    }

    // Fechar o arquivo após a leitura
    fclose(file);
    printf("Ingredientes importados com sucesso de ingredientes.txt!\n");
}


