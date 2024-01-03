#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "ListaLigada.h"
#include "Cliente.h"
#include "Alimentos.h"
#include "Plano.h"

/**
 * @brief Função para correr o -help
 * 
 */
void displayHelp() {
    printf("Comandos Disponiveis:\n");
    printf("-help\t\tAmonstra esta mensagem.\n");
    printf("-bin <FICHEIRO>\tLe e imprime os ficheiros escolhidos no modo binario.\n");
    printf("-tab <FICHEIRO>\tLe e imprime os ficheiros escolhidos com uma divisão por tabuladores.\n");
}

/**
 * @brief Função que pede o ficheiro, lê-o em binario e imprime em texto normal
 * 
 * @param fileName 
 */
void executeBinCommand(const char* fileName) {


    FILE *file = fopen(fileName, "rb");

    if (file == NULL) {
        perror("Error opening binary file");
        exit(EXIT_FAILURE);
    }

    if (strcmp(fileName, "clientes.dat") == 0) {
      printf("-----------* Dados Dos Clientes *-------------\n");
      Cliente* cli = malloc(sizeof(Cliente));
      while(fread(cli, sizeof(Cliente), 1, file) == 1) {
        printf("ID: %d\nNome: %s\nTelemovel: %d\n", cli->num_cliente, cli->nome, cli->telemovel);
        printf("----------------------------------------------\n");
      }
      free(cli);
    
    
    } else if (strcmp(fileName, "alimentos.dat") == 0) {
      printf("----------* Dados Dos Alimentos *-----------\n");
      Alimentos* ali = malloc(sizeof(Alimentos));
      while(fread(ali, sizeof(Alimentos), 1, file) == 1) {
        printf("ID: %d\nData: %d-%d-%d\nRefeicao: %s\nAlimento: %s\nCalorias: %d\n",
                   ali->id_cliente, ali->data.dia, ali->data.mes, ali->data.ano, ali->refeicao, ali->alimento, ali->cal);
        printf("----------------------------------------------\n");
      }
      free(ali);
    
    
    } else if (strcmp(fileName, "plano.dat") == 0) {
      printf("-----------* Dados Dos Planos *-------------\n");
      Plano* pl = malloc(sizeof(Plano));
      while(fread(pl, sizeof(Plano), 1, file) == 1) {
        printf("ID: %d\nData Inicial: %d-%d-%d\nData Final: %d-%d-%d\nRefeicao: %s\nCalorias Min: %d\nCalorias Max: %d\n",
                   pl->id_cliente, pl->data_inicio.dia, pl->data_inicio.mes, pl->data_inicio.ano, pl->data_fim.dia, pl->data_fim.mes, pl->data_fim.ano, pl->refeicao, pl->calmin, pl->calmax);
        printf("----------------------------------------------\n");
      }
      free(pl);
    }
    

    // Close the file
    fclose(file);

    

    return 0;
}

/**
 * @brief FUnção que pede um ficheiro e lê-o um ficheiro organizado por tabs
 * 
 * @param fileName 
 */
void executeTabCommand(const char* fileName) {
  
    // Implement the logic for the -tab command here

    FILE *file = fopen(fileName, "r");

    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read data from the file into a dynamically allocated Cliente structure
    if (strcmp(fileName, "clienteTab.txt") == 0) {
      printf("-----------* Dados Dos Clientes *-------------\n");
      Cliente* novo = NULL;
      novo = (Cliente*)calloc(1, sizeof(Cliente));
      // Iterar a cada linha do ficheiro a fim de atribuir a um objeto e adiciona-lo a uma lista
      while (fscanf(file, "%d\t%[^\t]\t%d\n", &(novo->num_cliente), &(novo->nome), &(novo->telemovel)) == 3) {                      
        printf("ID: %d\nName: %s\nTelemovel: %d\n", novo->num_cliente, novo->nome, novo->telemovel);
        printf("----------------------------------------------\n");
    }
    free(novo);  

    } else if (strcmp(fileName, "AlimentosTab.txt") == 0) {
      printf("----------* Dados Dos Alimentos *-----------\n");
      Alimentos* novo = NULL;
      novo = (Alimentos*)calloc(1, sizeof(Alimentos));
      // Iterar a cada linha do ficheiro a fim de atribuir a um objeto e adiciona-lo a uma lista
      while (fscanf(file, "%d\t%d-%d-%d\t%[^\t]\t%[^\t]\t%d\n", &(novo->id_cliente), &(novo->data.dia), &(novo->data.mes), &(novo->data.ano), &(novo->refeicao), &(novo->alimento), &(novo->cal)) == 7) {
        printf("ID: %d\nData: %d-%d-%d\nRefeicao: %s\nAlimento: %s\nCalorias: %d\n", novo->id_cliente, novo->data.dia, novo->data.mes, novo->data.ano, novo->refeicao, novo->alimento, novo->cal);
        printf("----------------------------------------------\n");
    }
    free(novo);  
    
    
    } else if (strcmp(fileName, "PlanoTab.txt") == 0) {
      printf("-----------* Dados Dos Planos *-------------\n");
      Plano* pl = NULL;
      pl = (Plano*)calloc(1, sizeof(Plano));
      // Iterar a cada linha do ficheiro a fim de atribuir a um objeto e adiciona-lo a uma lista
      while (fscanf(file, "%d\t%d-%d-%d\t%d-%d-%d\t%[^\t]\t%d\t%d\n", &(pl->id_cliente), &(pl->data_inicio.dia), &(pl->data_inicio.mes), &(pl->data_inicio.ano), &(pl->data_fim.dia), &(pl->data_fim.mes), &(pl->data_fim.ano), &(pl->refeicao), &(pl->calmin), &(pl->calmax)) == 10) {
        printf("ID: %d\nData Inicial: %d-%d-%d\nData Final: %d-%d-%d\nRefeicao: %s\nCalorias Min: %d\nCalorias Max: %d\n",
                   pl->id_cliente, pl->data_inicio.dia, pl->data_inicio.mes, pl->data_inicio.ano, pl->data_fim.dia, pl->data_fim.mes, pl->data_fim.ano, pl->refeicao, pl->calmin, pl->calmax);
                   printf("----------------------------------------------\n");
    }
    free(pl);  
    }
    

    fclose(file);

    return 0;
}

/**
 * @brief Função principal que vai correr outras funções como (Ler base de dados / Menu Principal / Guardar Base de dados / Limpar Memoria)
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[]) {
    if (argc == 1) {
        // No command-line arguments, run the program as usual
        Cliente* listaCliente = lerBaseDeDados();
        Alimentos* listaAlimentos = lerBaseDeDadosAlimentos();
        Plano* listaPlano = lerBaseDeDadosPlano();

        menuPrincipal(listaCliente, listaAlimentos, listaPlano);

        guardarBaseDeDados(listaCliente);
        libertarMemoria(listaCliente);

        guardarBaseDeDadosAlimentos(listaAlimentos);
        libertarMemoriaAlimentos(listaAlimentos);

        guardarBaseDeDadosPlano(listaPlano);
        libertarMemoriaPlano(listaPlano);
    } else if (argc == 2 && strcmp(argv[1], "-help") == 0) {
        // Display help message
        displayHelp();
    } else if (argc == 3 && strcmp(argv[1], "-bin") == 0) {
        // Execute the -bin command
        executeBinCommand(argv[2]);
    } else if (argc == 3 && strcmp(argv[1], "-tab") == 0) {
        // Execute the -tab command
        executeTabCommand(argv[2]);
    } else {
        // Invalid command-line arguments
        fprintf(stderr, "Invalid command-line arguments. Use -help for usage information.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
