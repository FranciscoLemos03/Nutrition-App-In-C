#include "ListaLigada.h"
#include "Cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


/**
 * @brief Função que envia dados para o ficheiro txt
 * 
 * @param lista 
 */
void guardarNormalcl(Cliente* lista) {
    Cliente* cl;
    FILE *dbCliente = fopen("dbCliente.txt", "w");

    if(dbCliente == NULL) 
		printf("\nERRO!");
    // iterar pela lista ligada e escrever no ficheiro
	for( cl = lista; cl != NULL; cl = cl->next){
            fprintf(dbCliente,"%d;%s;%d\n", cl->num_cliente, cl->nome, cl->telemovel);
    }
    fclose(dbCliente);

}

/**
 * @brief Função que envia dados para o ficheiro txt em binario
 * 
 * @param lista 
 */
void guardarBinariocl(Cliente* lista) {
        Cliente* cli;
	
    FILE *ClienteBin = fopen("clientes.dat", "wb");
    // Verificar se existe na diretoria

    if (ClienteBin == NULL) {
        perror("Error opening binary file");
        exit(EXIT_FAILURE);
    }
    // Write data to the file
    for( cli = lista; cli != NULL; cli = cli->next){
        fwrite(cli, sizeof(Cliente), 1, ClienteBin);
    }
    // Close the file
    fclose(ClienteBin);
}

/**
 * @brief Função que envia dados para o ficheiro txt com tabs
 * 
 * @param lista 
 */
void guardarTabuladorescl(Cliente* lista) {
    Cliente* cl;
    FILE *dbCliente = fopen("clienteTab.txt", "w");

    if (dbCliente == NULL) {
        printf("\nERRO!");
    // Handle the error, exit or return from the function
    }

    for (cl = lista; cl != NULL; cl = cl->next) {
        fprintf(dbCliente, "%d\t%s\t%d\n", cl->num_cliente, cl->nome, cl->telemovel);
    }

    fclose(dbCliente);

}

/**
 * @brief Função le as variaveis do ficheiro txt e guarda-as na lista
 * 
 * @return Cliente* 
 */
Cliente* lerBaseDeDados(){
    Cliente* lista = NULL;
    Cliente* novo = NULL;
	
	FILE *dbCliente = fopen("dbCliente.txt", "r");
    /**
     * @brief Verificar se existe na diretoria
     * 
     */
	if(dbCliente == NULL) {
		printf("\nERRO!");
	}
	
    /**
     * @brief Iterar a cada linha do ficheiro a fim de atribuir a um objeto e adiciona-lo a uma lista
     * 
     */
    while(!feof(dbCliente)) {
        novo = (Cliente*)calloc(1, sizeof(Cliente));
        fscanf(dbCliente,"%d;%[^;];%d\n", &(novo->num_cliente), &(novo->nome), &(novo->telemovel));
            lista = adicionarCliente(lista, novo);
    }

    fclose(dbCliente);

    return lista;
}


/**
 * @brief Guarda as variaveis num ficheiro txt
 * 
 * @param lista 
 */
void guardarBaseDeDados(Cliente* lista){

    guardarNormalcl(lista);
    guardarBinariocl(lista);
    guardarTabuladorescl(lista);

}

/**
 * @brief Liberta a memoria alocada pela lista e uso de recursao 
 * 
 * @param lista 
 */
void libertarMemoria(Cliente* lista){
    if(lista == NULL)
        return;

    libertarMemoria(lista->next);

    free(lista);
}

/**
 * @brief Funcao para pedir dados do cliente
 * 
 * @param listaCliente 
 */
void adicionar(Cliente* listaCliente) {
	/**
	 * @brief Variavel do tipo Cliente que retorna um ponteiro para o espaço alocado
	 * 
	 */
    Cliente* novoCliente = (Cliente*)calloc(1, sizeof(Cliente));
    int auxInt = -1;
    
    printf("Digite o nome: ");
	fflush(stdin);
	getchar();
    fgets(novoCliente->nome, 20, stdin);
    novoCliente->nome[strcspn(novoCliente->nome, "\n")] = 0; // tira a nova linha "\n" que tenho no nome
	
    /**
     * @brief gerar um id aleatorio 
     * 
     */
    novoCliente->num_cliente= obterIdAleatorio(listaCliente);
    
	auxInt = -1;
	printf("Digite o numero de telemovel:");
	fflush(stdin);
	scanf("%d", &auxInt);
	novoCliente->telemovel = auxInt;
    
    /**
     * @brief Vai percorrer a lista ate encontrar um espaço null
     * 
     */
    listaCliente = adicionarCliente(listaCliente, novoCliente);

    printf("\nAdicionado com sucesso!\n");
}

/**
 * @brief Procedimento para adicionar um cliente no espaço null
 * 
 * @param listaCliente 
 * @param novoCliente 
 * @return Cliente* 
 */
Cliente* adicionarCliente(Cliente *listaCliente, Cliente *novoCliente)
{
	/**
	 * @brief Se a lista for NULL, devolve o meu novo cliente
	 * 
	 */
	if(listaCliente == NULL) return novoCliente;
	/**
	 * @brief Se lista for diferente de NULL, o proximo cliente vai continuar a procurar um espaco "NULL"
	 * 
	 */
	listaCliente->next = adicionarCliente(listaCliente->next, novoCliente);
	/**
	 * @brief Da return a lista depois da atualizacao
	 * 
	 */
	return listaCliente;
}

/**
 * @brief Obter um id aleatorio
 * 
 * @param listaClientes 
 * @return int 
 */
int obterIdAleatorio(Cliente* listaClientes) {
    int randomId;
    time_t t;

	//inicia um numero random
    srand((unsigned) time(&t));
    
    //dar valor ao id at� encontrar um numero entre 0 e 100 que nao exista
    do {
        randomId = rand() % 100; 
    } while(existeCliente(listaClientes,randomId));
    
    return randomId;
}

/**
 * @brief função que verifica se existe cliente
 * 
 * @param lista 
 * @param id 
 * @return true 
 * @return false 
 */
bool existeCliente(Cliente* lista, int id) {
	//se a lista for null retorna falso
    if(lista == NULL)
        return false;
    
    // se o id dado for igual ao da lista retorna verdadeiro
    if(lista->num_cliente == id)
        return true;
    
    return existeCliente(lista->next, id);    
}

/**
 * @brief funcao para editar um cliente
 * 
 * @param listaCliente 
 */
void editar(Cliente* listaCliente)
{
    int auxInt = -1;
    int idEscolhido;
    Cliente* clienteEscolhido;

    printf("\nQual o numero do Cliente?\n");
    do {
        auxInt = -1;
    	fflush(stdin);
    	if(scanf("%d", &auxInt) != 0){
    		idEscolhido = auxInt;
		}
		if(auxInt < 0 ) {
			printf("erro, Escolha um valor positivo!\n");
		}
	} while(auxInt < 0 );

	//funcao para encontrar cliente
    clienteEscolhido = encontrarCliente(listaCliente, idEscolhido);

	// se existir algum cliente na lista com esse id edita, senao mensagem a avisar que nao encontrou
    if(clienteEscolhido != NULL)
        editarCliente(listaCliente, clienteEscolhido);
    else
        printf("Cliente nao encontrado!\n");
}

/**
 * @brief Dado um cliente, pede-se os dados para edita-lo
 * 
 * @param listaCliente 
 * @param clienteEscolhido 
 */
void editarCliente(Cliente* listaCliente, Cliente* clienteEscolhido) {
    int auxInt = -1;
    
    printf("Digite o nome: ");
	fflush(stdin); 
    getchar();
    fgets(clienteEscolhido->nome, 20, stdin);
    clienteEscolhido->nome[strcspn(clienteEscolhido->nome, "\n")] = 0; // tira a nova linha "\n" que tenho no nome
    
	auxInt = -1;
	printf("Digite o numero de telemovel:");
	fflush(stdin);
	scanf("%d", &auxInt);
	clienteEscolhido->telemovel = auxInt;

    printf("\nAlterado com sucesso!\n");
}

/**
 * @brief Funcao para encontrar um cliente
 * 
 * @param lista 
 * @param id 
 * @return Cliente* 
 */
Cliente* encontrarCliente(Cliente* lista, int id) {
    if(lista == NULL)
        return NULL;

    if(lista->num_cliente == id) 
        return lista;
    
    return encontrarCliente(lista->next, id);
}

/**
 * @brief funcao para remover o cliente
 * 
 * @param listaCliente 
 */
void remover(Cliente* listaCliente) {
    int auxInt = -1;
    int idEscolhido;
    Cliente* clienteRemovido;

    printf("\nDigite o Id do Cliente\n");
    do {
        auxInt = -1;
    	fflush(stdin);
    	if(scanf("%d", &auxInt) != 0){
    		idEscolhido = auxInt;
		}
		if(auxInt < 0 ) {
			printf("erro, Id invalido!\n");
		}
	} while(auxInt < 0 );
	
	
	//funcao para encontrar e remover cliente	
    clienteRemovido = removerCliente(listaCliente, idEscolhido);

	// se existir algum cliente na lista mensagem a avisar que removeu, senao mensagem a avisar que nao encontrou
    if(clienteRemovido != NULL) {
        printf("Cliente removido com sucesso\n");
    } else {
        printf("Cliente nao encontrado!\n");
    }
}

/**
 * @brief Função para remover um cliente da lista
 * 
 * @param lista 
 * @param id 
 * @return Cliente* 
 */
Cliente* removerCliente(Cliente* lista, int id) {
    Cliente* prox = NULL;

    if(lista == NULL)
        return NULL;

    if(lista->num_cliente == id) {
        prox = lista->next;
        free(lista);
        return prox;
    }
    
    lista->next = removerCliente(lista->next, id);
    return lista;
}

/**
 * @brief funcao para visualizar cliente
 * 
 * @param listaCliente 
 */
void visualizarCliente(Cliente* listaCliente) {
	int auxInt = -1;
    int idEscolhido;
    Cliente* clienteEscolhido;

    printf("\nQual o numero do Cliente?\n");
    do {
        auxInt = -1;
    	fflush(stdin);
    	if(scanf("%d", &auxInt) != 0){
    		idEscolhido = auxInt;
		}
		if(auxInt < 0 ) {
			printf("erro, Escolha um valor positivo!\n");
		}
	} while(auxInt < 0 );

	//funcao para encontrar o cliente pelo id
    clienteEscolhido = encontrarCliente(listaCliente, idEscolhido);

	// se existir algum cliente com o mesmo id lista o cliente, senao mensagem a avisar que nao encontrou
    if(clienteEscolhido != NULL)
        printf("Numero Cliente: %d\nNome: %s\nNumero Telemovel: %d\n", clienteEscolhido->num_cliente, clienteEscolhido->nome, clienteEscolhido->telemovel);
    else
        printf("Cliente nao encontrado!\n");
}


