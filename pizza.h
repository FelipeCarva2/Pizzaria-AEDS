#ifndef PIZZA_H_INCLUDED
#define PIZZA_H_INCLUDED

#include "ingredientes.h"
#define MAX_PIZZAS 100
#define MAX_INGREDIENTES_PIZZA 10
#define FILE_PIZZAS "pizzas.dat"

extern int qtdPizzas;
//Definição do tipo pizza
typedef struct pizza{
    int id;
    char nome[50];
    char tamanho;
    float preco;
    Ingrediente ingredientes[MAX_INGREDIENTES_PIZZA];
    int qtdIngredientes;
}pizza;

//Funções de pizza
void adicionarPizza();
void listarPizzas();
void venderPizza();
void importarPizzasDeArquivo();
void editarPizza();
void removerPizza();
void salvarPizzasEmArquivo();


#endif // PIZZA_H_INCLUDED
