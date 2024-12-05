#ifndef INGREDIENTES_H_INCLUDED
#define INGREDIENTES_H_INCLUDED

#define MAX_INGREDIENTES 100
#define FILE_INGREDIENTES "ingredientes.dat"

//Defini��o do tipo Ingredientes
typedef struct  Ingrediente{
    int id;
    char nome[50];
    float preco;
} Ingrediente;

// Vari�veis globais para ingredientes
extern Ingrediente ingredientes[MAX_INGREDIENTES];
extern int qtdIngredientes;

// Declara��es das fun��es
void adicionarIngrediente();
void listarIngredientes();
void editarIngrediente();
void removerIngrediente();
void importarIngredientesDeArquivo();
void salvarIngredientesEmArquivo();

#endif // INGREDIENTES_H_INCLUDED
