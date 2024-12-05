#ifndef INGREDIENTES_H_INCLUDED
#define INGREDIENTES_H_INCLUDED

#define MAX_INGREDIENTES 100
#define FILE_INGREDIENTES "ingredientes.dat"

//Definição do tipo Ingredientes
typedef struct  Ingrediente{
    int id;
    char nome[50];
    float preco;
} Ingrediente;

// Variáveis globais para ingredientes
extern Ingrediente ingredientes[MAX_INGREDIENTES];
extern int qtdIngredientes;

// Declarações das funções
void adicionarIngrediente();
void listarIngredientes();
void editarIngrediente();
void removerIngrediente();
void importarIngredientesDeArquivo();
void salvarIngredientesEmArquivo();

#endif // INGREDIENTES_H_INCLUDED
