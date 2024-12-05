//Feito por: Filipe Estopa Tavares Santos Felipe Gabriel de Carvalho
#include <stdio.h>
#include <stdlib.h>
#include <locale.h> // Necessário para poder usar acentuação nas palavras
#include <windows.h> // Necessário para a função Sleep()
#include "pizza.h"  // Header com o CRUD da pizza
#include "ingredientes.h" // Header com o CRUD do ingredientes

void salvarPizzasEmArquivo();
pizza pizzas[MAX_PIZZAS];

int main(){
    int opcao;

    printf("Seja bem vindo ao menu de nossa pizzaria!!\n");

    setlocale(LC_ALL, ""); // Configura a localidade de acordo com o sistema operacional para poder usar acentos
    Sleep(2000); // Aguarda 2 segundos
    system("cls"); //Limpa a tela do usuário

//Menu da pizzaria
    do {
        printf("\n=== Pizzaria MAMA-MIA ===\n");
    printf("1. Adicionar Ingrediente\n");
    printf("2. Listar Ingredientes\n");
    printf("3. Editar Ingrediente\n");
    printf("4. Remover Ingrediente\n");
    printf("5. Adicionar Pizza\n");
    printf("6. Listar Pizzas\n");
    printf("7. Vender Pizza\n");
    printf("8. Editar pizzas\n");
    printf("9. Remover Pizza\n");
    printf("10. Salvar Dados \n");
    printf("11. Importar Dados\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
//Condicional dos menus
    switch (opcao) {
        case 1:
            adicionarIngrediente();
            break;
        case 2:
            listarIngredientes();
            break;
        case 3:
            editarIngrediente();
            break;
        case 4:
            removerIngrediente();
            break;
        case 5:
            adicionarPizza();
            break;
        case 6:
            listarPizzas();
            break;
        case 7:
            venderPizza();
            break;
        case 8:
             editarPizza();
            break;
        case 9:
            removerPizza();
            break;
        case 10:
            salvarPizzasEmArquivo();
            salvarIngredientesEmArquivo();
            break;
        case 11:
            importarIngredientesDeArquivo();
            importarPizzasDeArquivo();
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida.\n");
    }
    } while (opcao != 0);
}





