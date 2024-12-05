#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pizza.h"

// Defini��o das vari�veis globais
pizza pizzas[MAX_PIZZAS];
int qtdPizzas = 0;

// Implementa��o das fun��es

//Adionas as pizzas
void adicionarPizza() {
    //Olha o limite que se pode ter pizzas cadastradas
    if (qtdPizzas >= MAX_PIZZAS) {
        printf("Limite de pizzas atingido.\n");
        return;
    }

    pizza novaPizza;
    novaPizza.id = qtdPizzas + 1;   // Faz os id serem adicionados "automaticamente"
    novaPizza.qtdIngredientes = 0;  // Inicializa a quantidade de ingredientes

    // Solicita o nome da pizza
    printf("Nome da pizza: ");
    scanf(" %[^\n]", novaPizza.nome);

    // Solicita o tamanho da pizza
    printf("Tamanho da pizza (P/M/G): ");
    scanf(" %c", &novaPizza.tamanho);

    // Solicita o pre�o base da pizza
    printf("Pre�o base da pizza: ");
    scanf("%f", &novaPizza.preco);

    // Exibe os ingredientes j� cadastrados para o usu�rio escolher pelo ID
    printf("\n--- Ingredientes dispon�veis ---\n");
    listarIngredientes();  // Chama a fun��o para listar os ingredientes cadastrados

    // Pergunta quantos ingredientes a pizza ter�
    printf("Quantos ingredientes a pizza ter�? (M�ximo %d): ", MAX_INGREDIENTES_PIZZA);
    int qtdIngredientesPizza;
    scanf("%d", &qtdIngredientesPizza);

    if (qtdIngredientesPizza > MAX_INGREDIENTES_PIZZA) {
        printf("N�mero de ingredientes excede o limite permitido.\n");
        return;
    }

    for (int i = 0; i < qtdIngredientesPizza; i++) {
        int idIngrediente;
        printf("Digite o ID do ingrediente %d: ", i + 1);
        scanf("%d", &idIngrediente);

        // Verifica se o ID do ingrediente � v�lido
        if (idIngrediente <= 0 || idIngrediente > qtdIngredientes) {
            printf("ID inv�lido. Tente novamente.\n");
            i--;  // Decrementa i para repetir a inser��o desse ingrediente
            continue;
        }

        // Adiciona o ingrediente na pizza escolhida
        novaPizza.ingredientes[i] = ingredientes[idIngrediente - 1];
        novaPizza.qtdIngredientes++;  // Atualiza a quantidade de ingredientes na pizza
    }

    // Adiciona a pizza ao array de pizzas
    pizzas[qtdPizzas++] = novaPizza;
    printf("Pizza adicionada com sucesso!\n");
}

// Fun��o para listar pizzas
//Funcionamento: Varre o array de pizzas printando cada indice dele
void listarPizzas() {
    if (qtdPizzas == 0) {
        printf("Nenhuma pizza cadastrada.\n");
        return;
    }
    printf("\nPizzas no card�pio:\n");
    for (int i = 0; i < qtdPizzas; i++) {
        printf("ID: %d | Nome: %s | Tamanho: %c | Pre�o Base: %.2f\n", pizzas[i].id, pizzas[i].nome, pizzas[i].tamanho, pizzas[i].preco);
        printf("Ingredientes:\n");
        for (int j = 0; j < pizzas[i].qtdIngredientes; j++) {
            printf("   - %s (%.2f)\n", pizzas[i].ingredientes[j].nome, pizzas[i].ingredientes[j].preco);
        }
    }
}


//Fun��o vender pizzas
//Funcionamento: Lista as pizzas, recebe o id e faz as veifica��es para dar sequencia e mostra os detalhes da pizza com o pre�o
void venderPizza() {
        listarPizzas();

        if (qtdPizzas == 0) {
            printf("N�o h� pizzas dispon�veis para venda.\n");
            return;
        }

        int idPizza;
        printf("Digite o ID da pizza que deseja vender: ");
        scanf("%d", &idPizza);

        if (idPizza <= 0 || idPizza > qtdPizzas) {
            printf("ID inv�lido.\n");
            return;
        }

    pizza pizzaSelecionada = pizzas[idPizza - 1];

    // Exibir detalhes da pizza
    printf("\n=== Detalhes da Pizza Selecionada ===\n");
    printf("Nome: %s\n", pizzaSelecionada.nome);
    printf("Tamanho: %c\n", pizzaSelecionada.tamanho);
    printf("Pre�o Base: %.2f\n", pizzaSelecionada.preco);
    printf("Ingredientes:\n");
    float precoTotal = pizzaSelecionada.preco;
    for (int i = 0; i < pizzaSelecionada.qtdIngredientes; i++) {
        printf("  - %s (R$ %.2f)\n", pizzaSelecionada.ingredientes[i].nome, pizzaSelecionada.ingredientes[i].preco);
        precoTotal += pizzaSelecionada.ingredientes[i].preco;
    }

    // Exibir pre�o total
    printf("Pre�o Total da Pizza: R$ %.2f\n", precoTotal);
    printf("Venda registrada com sucesso!\n");
}


//Fun��o para importar pizzas do arquivo
void importarPizzasDeArquivo() {
    // Abrir o arquivo de pizzas em modo de leitura
    FILE *file = fopen("pizzas.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de pizzas para leitura.\n");
        return;
    }

    // Vari�veis auxiliares para ler os dados
    pizza novaPizza;
    char ingredientesStr[500];  // Buffer para armazenar a lista de ingredientes
    while (fscanf(file, "%d;%49[^;];%c;%f;%[^\n]\n", &novaPizza.id, novaPizza.nome, &novaPizza.tamanho, &novaPizza.preco, ingredientesStr) == 5) {
        // Parse dos ingredientes da pizza
        char *ingredienteToken = strtok(ingredientesStr, ",");  // Separa os ingredientes por v�rgula
        novaPizza.qtdIngredientes = 0;

        while (ingredienteToken != NULL && novaPizza.qtdIngredientes < MAX_INGREDIENTES_PIZZA) {
            // Para cada ingrediente, separa nome e pre�o
            char nomeIngrediente[50];
            float precoIngrediente;
            sscanf(ingredienteToken, "%49[^|]|%f", nomeIngrediente, &precoIngrediente);

            // Adiciona o ingrediente � pizza
            strcpy(novaPizza.ingredientes[novaPizza.qtdIngredientes].nome, nomeIngrediente);
            novaPizza.ingredientes[novaPizza.qtdIngredientes].preco = precoIngrediente;
            novaPizza.qtdIngredientes++;

            // Avan�a para o pr�ximo ingrediente
            ingredienteToken = strtok(NULL, ",");
        }

        // Adiciona a pizza � lista de pizzas
        if (qtdPizzas < MAX_PIZZAS) {
            pizzas[qtdPizzas++] = novaPizza;
        } else {
            printf("Limite de pizzas atingido!\n");
            break;
        }
    }

    // Fechar o arquivo ap�s a leitura
    fclose(file);
    printf("Pizzas importadas com sucesso de pizzas.txt!\n");
}


//Fun��o para editar pizza
//Funcionamento: Lista as pizzas e faz as verifica��es com base no id, e segue editando tudo sobre a pizza
void editarPizza() {
    listarPizzas();  // Lista todas as pizzas dispon�veis

    if (qtdPizzas == 0) {
        printf("N�o h� pizzas cadastradas para editar.\n");
        return;
    }

    int idPizza;
    printf("Digite o ID da pizza que deseja editar: ");
    scanf("%d", &idPizza);

    if (idPizza <= 0 || idPizza > qtdPizzas) {
        printf("ID inv�lido. Tente novamente.\n");
        return;
    }

    pizza *pizzaEdicao = &pizzas[idPizza - 1];  // Acesso � pizza selecionada

    // Editando os dados principais da pizza
    printf("Editando a pizza: %s\n", pizzaEdicao->nome);
    printf("Novo nome (atual: %s): ", pizzaEdicao->nome);
    scanf(" %[^\n]", pizzaEdicao->nome);

    printf("Novo tamanho (atual: %c): ", pizzaEdicao->tamanho);
    scanf(" %c", &pizzaEdicao->tamanho);

    printf("Novo pre�o base (atual: %.2f): ", pizzaEdicao->preco);
    scanf("%f", &pizzaEdicao->preco);

    // Editando os ingredientes
    printf("Deseja editar os ingredientes? (1 - Sim / 0 - N�o): ");
    int editarIngredientes;
    scanf("%d", &editarIngredientes);

    if (editarIngredientes == 1) {
        int opcaoIngrediente;
        do {
            printf("\n--- Menu de Ingredientes ---\n");
            printf("1. Adicionar Ingrediente\n");
            printf("2. Remover Ingrediente\n");
            printf("3. Listar Ingredientes\n");
            printf("0. Voltar\n");
            printf("Escolha uma op��o: ");
            scanf("%d", &opcaoIngrediente);

            switch (opcaoIngrediente) {
                case 1: {
                    if (pizzaEdicao->qtdIngredientes >= MAX_INGREDIENTES_PIZZA) {
                        printf("Limite de ingredientes atingido.\n");
                    } else {
                        // Adiciona um ingrediente
                        printf("Nome do ingrediente: ");
                        scanf(" %[^\n]", pizzaEdicao->ingredientes[pizzaEdicao->qtdIngredientes].nome);
                        printf("Pre�o do ingrediente: ");
                        scanf("%f", &pizzaEdicao->ingredientes[pizzaEdicao->qtdIngredientes].preco);
                        pizzaEdicao->qtdIngredientes++;
                        printf("Ingrediente adicionado com sucesso!\n");
                    }
                    break;
                }
                case 2: {
                    // Remover um ingrediente
                    if (pizzaEdicao->qtdIngredientes == 0) {
                        printf("N�o h� ingredientes para remover.\n");
                    } else {
                        int idIngrediente;
                        printf("Digite o ID do ingrediente que deseja remover (1 a %d): ", pizzaEdicao->qtdIngredientes);
                        scanf("%d", &idIngrediente);

                        if (idIngrediente <= 0 || idIngrediente > pizzaEdicao->qtdIngredientes) {
                            printf("ID inv�lido.\n");
                        } else {
                            // Remove o ingrediente
                            for (int i = idIngrediente - 1; i < pizzaEdicao->qtdIngredientes - 1; i++) {
                                pizzaEdicao->ingredientes[i] = pizzaEdicao->ingredientes[i + 1];
                            }
                            pizzaEdicao->qtdIngredientes--;
                            printf("Ingrediente removido com sucesso!\n");
                        }
                    }
                    break;
                }
                case 3: {
                    // Listar os ingredientes da pizza
                    printf("\nIngredientes da pizza %s:\n", pizzaEdicao->nome);
                    for (int i = 0; i < pizzaEdicao->qtdIngredientes; i++) {
                        printf("  %d. %s (R$ %.2f)\n", i + 1, pizzaEdicao->ingredientes[i].nome, pizzaEdicao->ingredientes[i].preco);
                    }
                    break;
                }
                case 0:
                    break;
                default:
                    printf("Op��o inv�lida. Tente novamente.\n");
            }
        } while (opcaoIngrediente != 0);
    }

    printf("Pizza %s editada com sucesso!\n", pizzaEdicao->nome);
}

//Fun��o para remover uma pizza
void removerPizza() {
    if (qtdPizzas == 0) {
        printf("Nenhuma pizza cadastrada para remover.\n");
        return;
    }

    // Exibe as pizzas cadastradas
    printf("\n--- Pizzas Cadastradas ---\n");
    listarPizzas();  // Chama a fun��o para listar as pizzas

    int idPizza;
    printf("Digite o ID da pizza que deseja remover: ");
    scanf("%d", &idPizza);

    // Verifica se o ID da pizza � v�lido
    if (idPizza <= 0 || idPizza > qtdPizzas) {
        printf("ID inv�lido. Nenhuma pizza foi removida.\n");
        return;
    }

    // Desloca as pizzas subsequentes para preencher o espa�o
    for (int i = idPizza - 1; i < qtdPizzas - 1; i++) {
        pizzas[i] = pizzas[i + 1];
    }

    // Atualiza a quantidade de pizzas
    qtdPizzas--;

    printf("Pizza removida com sucesso!\n");
}


//Fun��o para salvar as pizzas no arquivo
void salvarPizzasEmArquivo() {
    FILE *file = fopen("pizzas.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < qtdPizzas; i++) {
        fprintf(file, "%d;%s;%c;%.2f;", pizzas[i].id, pizzas[i].nome, pizzas[i].tamanho, pizzas[i].preco);

        // Salvar ingredientes da pizza no formato ingrediente1|preco1,ingrediente2|preco2,...
        for (int j = 0; j < pizzas[i].qtdIngredientes; j++) {
            fprintf(file, "%s|%.2f", pizzas[i].ingredientes[j].nome, pizzas[i].ingredientes[j].preco);
            if (j < pizzas[i].qtdIngredientes - 1) {
                fprintf(file, ",");
            }
        }

        fprintf(file, "\n"); // Pr�xima pizza em nova linha
    }

    fclose(file);
    printf("Pizzas salvas com sucesso em pizzas.txt!\n");
}

