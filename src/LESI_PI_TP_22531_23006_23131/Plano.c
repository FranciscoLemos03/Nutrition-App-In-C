#include "ListaLigada.h"
#include "Plano.h"
#include "Cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

/**
 * @brief Função que envia dados para o ficheiro txt
 * 
 * @param listaPlano 
 */
void guardarNormal(Plano* listaPlano) {
    Plano* pl;
    FILE *dbPlano= fopen("dbPlano.txt", "w");

    if(dbPlano == NULL) 
		printf("\nERRO!");
    // iterar pela lista ligada e escrever no ficheiro
	for( pl = listaPlano; pl != NULL; pl = pl->next){
            fprintf(dbPlano,"%d;%d-%d-%d;%d-%d-%d;%s;%d;%d\n", pl->id_cliente, pl->data_inicio.dia, pl->data_inicio.mes, pl->data_inicio.ano, pl->data_fim.dia, pl->data_fim.mes, pl->data_fim.ano, pl->refeicao, pl->calmin, pl->calmax);
    }
    fclose(dbPlano);

}

/**
 * @brief Função que envia dados para o ficheiro txt em binario
 * 
 * @param listaPlano 
 */
void guardarBinario(Plano* listaPlano) {
    Plano* pli;
    FILE *PlanoBin = fopen("plano.dat", "wb");

    if (PlanoBin == NULL) {
        perror("Error opening binary file");
        exit(EXIT_FAILURE);
    }
    // Write data to the file
    for( pli = listaPlano; pli != NULL; pli = pli->next){
        fwrite(pli, sizeof(Plano), 1, PlanoBin);
    }
    // Close the file
    fclose(PlanoBin);
}

/**
 * @brief Função que envia dados para o ficheiro txt com tabs
 * 
 * @param listaPlano 
 */
void guardarTabuladores(Plano* listaPlano) {
    Plano* pl;
    FILE *dbPlano= fopen("PlanoTab.txt", "w");

    if(dbPlano == NULL) 
		printf("\nERRO!");
    // iterar pela lista ligada e escrever no ficheiro
	for( pl = listaPlano; pl != NULL; pl = pl->next){
            fprintf(dbPlano,"%d\t%d-%d-%d\t%d-%d-%d\t%s\t%d\t%d\n", pl->id_cliente, pl->data_inicio.dia, pl->data_inicio.mes, pl->data_inicio.ano, pl->data_fim.dia, pl->data_fim.mes, pl->data_fim.ano, pl->refeicao, pl->calmin, pl->calmax);
    }
    fclose(dbPlano);

}

/**
 * @brief Função que lê o txt de Planos ao iniciar o programa e guarda numa lista ligada
 * 
 * @return Plano* 
 */
Plano* lerBaseDeDadosPlano(){
    Plano* lista = NULL;
    Plano* novo = NULL;
	
	FILE *dbPlano = fopen("dbPlano.txt", "r");
    // Verificar se existe na diretoria
	if(dbPlano == NULL) {
		printf("\nERRO!");
	}
	
    //iterar a cada linha do ficheiro a fim de atribuir a um objeto e adiciona-lo a uma lista
    while(!feof(dbPlano)) {
        novo = (Plano*)calloc(1, sizeof(Plano));
        fscanf(dbPlano,"%d;%d-%d-%d;%d-%d-%d;%[^;];%d;%d\n", &(novo->id_cliente), &(novo->data_inicio.dia), &(novo->data_inicio.mes), &(novo->data_inicio.ano), &(novo->data_fim.dia), &(novo->data_fim.mes), &(novo->data_fim.ano), &(novo->refeicao), &(novo->calmin), &(novo->calmax));
            lista = adicionarPlano(lista, novo);
    }

    fclose(dbPlano);

    return lista;
}

/**
 * @brief Função que chama as 3 funções de guardar os dados
 * 
 * @param listaPlano 
 */
void guardarBaseDeDadosPlano(Plano* listaPlano){

guardarNormal(listaPlano);
guardarBinario(listaPlano);
guardarTabuladores(listaPlano);
}

/**
 * @brief Função que pede os dados do Plano
 * 
 * @param listaCliente 
 * @param listaPlano 
 */
void addPlano(Cliente* listaCliente, Plano* listaPlano) {
    
    Plano* novoPlano = (Plano*)calloc(1, sizeof(Plano));
    int auxIDCliente = -1, auxDataDiaI, auxDataMesI, auxDataAnoI, auxDataDiaF, auxDataMesF, auxDataAnoF, auxCalmin, auxCalmax;
    Cliente* clienteEscolhido;
    
    printf("Digite o id do Cliente: ");
	fflush(stdin); 
    scanf("%d", &auxIDCliente);
    
    clienteEscolhido = encontrarCliente(listaCliente, auxIDCliente);
    
    if(clienteEscolhido != NULL){
    	novoPlano->id_cliente = auxIDCliente;
		
		printf("Digite o dia do inicio: ");
		fflush(stdin); 
		scanf("%d", &auxDataDiaI);
		novoPlano->data_inicio.dia = auxDataDiaI;
		
		printf("Digite o mes do inicio: ");
		fflush(stdin); 
		scanf("%d", &auxDataMesI);
		novoPlano->data_inicio.mes = auxDataMesI;
		
		printf("Digite o ano do inicio: ");
		fflush(stdin); 
		scanf("%d", &auxDataAnoI);
		novoPlano->data_inicio.ano = auxDataAnoI;
		
		printf("Digite o dia do fim: ");
		fflush(stdin); 
		scanf("%d", &auxDataDiaF);
		novoPlano->data_fim.dia = auxDataDiaF;
		
		printf("Digite o mes do fim: ");
		fflush(stdin); 
		scanf("%d", &auxDataMesF);
		novoPlano->data_fim.mes = auxDataMesF;
		
		printf("Digite o ano do fim: ");
		fflush(stdin); 
		scanf("%d", &auxDataAnoF);
		novoPlano->data_fim.ano = auxDataAnoF;
		
		printf("Em que refeicao vai ser? ");
		fflush(stdin); 
		getchar();
	    fgets(novoPlano->refeicao, 20, stdin);
	    novoPlano->refeicao[strcspn(novoPlano->refeicao, "\n")] = 0; // tira a nova linha "\n" que tenho no Plano
		
		printf("Digite o numero de calorias minimo: ");
		fflush(stdin); 
		scanf("%d", &auxCalmin);
		novoPlano->calmin = auxCalmin;
		
		printf("Digite o numero de calorias maximo: ");
		fflush(stdin); 
		scanf("%d", &auxCalmax);
		novoPlano->calmax = auxCalmax;
		
		listaPlano = introduzirPlano(listaPlano, novoPlano);

		printf("\nAdicionado com sucesso!\n");
    	
			
	} else {
        printf("Cliente nao encontrado!\n");
	}
			
}


/**
 * @brief Função para adicionar um Plano
 * 
 * @param listaPlano 
 * @param novoPlano 
 * @return Plano* 
 */
Plano* introduzirPlano(Plano* listaPlano, Plano* novoPlano)
{
	//se a lista for NULL, devolve o meu novo Plano
	if(listaPlano == NULL) return novoPlano;
	//se lista for diferente de NULL, o proximo Plano vai continuar a procurar um espaco "NULL" 
	listaPlano->next = introduzirPlano(listaPlano->next, novoPlano);
	
	//da return a lista depois da atualiza??o
	return listaPlano;
}

/**
 * @brief Função para adicionar um Plano ao ler a base de dados
 * 
 * @param listaPlano 
 * @param novoPlano 
 * @return Plano* 
 */
Plano* adicionarPlano(Plano *listaPlano, Plano *novoPlano)
{
	//se a lista for NULL, devolve o meu novo cliente
	if(listaPlano == NULL) return novoPlano;
	//se lista for diferente de NULL, o proximo cliente vai continuar a procurar um espaco "NULL" 
	listaPlano->next = adicionarPlano(listaPlano->next, novoPlano);
	//da return a lista depois da atualizacao
	return listaPlano;
}

/**
 * @brief Liberta a memoria alocada pela lista e uso de recursao
 * 
 * @param lista 
 */
void libertarMemoriaPlano(Plano* lista){
    if(lista == NULL)
        return;

    libertarMemoriaPlano(lista->next);

    free(lista);
}

/**
 * @brief Função para listar Planos que estão entre 2 datas pedidas e que são de uma certa refeição
 * 
 * @param listaPlano 
 * @param listaCliente 
 */
void ListarPlanosPorCliente(Plano* listaPlano, Cliente* listaCliente){
	Plano* pl;
	Cliente* cl;
	Cliente* clienteEscolhido;
	
	char auxRefeicao[20];
	int auxClienteId , auxDataDiaI, auxDataMesI, auxDataAnoI, auxDataDiaF, auxDataMesF, auxDataAnoF;
	
	system("clear");
	printf("Digite o id do cliente: ");
	fflush(stdin); 
	scanf("%d", &auxClienteId);
	
	clienteEscolhido = encontrarCliente(listaCliente, auxClienteId);
    
    if(clienteEscolhido != NULL){
		
		printf("Digite o dia Inicial: ");
		fflush(stdin); 
		scanf("%d", &auxDataDiaI);
		
		printf("Digite o mes Inicial: ");
		fflush(stdin); 
		scanf("%d", &auxDataMesI);
		
		printf("Digite o ano Inicial: ");
		fflush(stdin); 
		scanf("%d", &auxDataAnoI);
		
		printf("Digite o dia Final: ");
		fflush(stdin); 
		scanf("%d", &auxDataDiaF);
		
		printf("Digite o mes Final: ");
		fflush(stdin); 
		scanf("%d", &auxDataMesF);
		
		printf("Digite o ano Final: ");
		fflush(stdin); 
		scanf("%d", &auxDataAnoF);
		
		printf("Digite a refeicao: ");
    	scanf("%s", auxRefeicao);
		
		system("clear");
		for( pl = listaPlano; pl != NULL; pl = pl->next){
    		if(dataEstaEntre(auxDataDiaI, auxDataDiaF, pl->data_inicio.dia, auxDataMesI, auxDataMesF, pl->data_inicio.mes, auxDataAnoI, auxDataAnoF, pl->data_inicio.ano) && dataEstaEntre(auxDataDiaI, auxDataDiaF, pl->data_fim.dia, auxDataMesI, auxDataMesF, pl->data_fim.mes, auxDataAnoI, auxDataAnoF, pl->data_fim.ano) && strcmp(pl->refeicao, auxRefeicao) == 0){
				for( cl = listaCliente; cl != NULL; cl =cl->next){
					if(pl->id_cliente == cl->num_cliente){
						printf("\nPlano do %s\n\n", &cl->nome);
						printf("---------------------------------\n\n");
						printf("Data Inicial: %d-%d-%d\n", pl->data_inicio.dia, pl->data_inicio.mes, pl->data_inicio.ano);
						printf("Data Final: %d-%d-%d\n", pl->data_fim.dia, pl->data_fim.mes, pl->data_fim.ano);
						printf("Refeicao: %s\n", &pl->refeicao);
						printf("Calorias Minimas: %d\n", pl->calmin);
						printf("Calorias Maximas: %d\n\n", pl->calmax);
						printf("---------------------------------");
					}
				}
				
			}
    	}
	
	} else {
        printf("Cliente nao encontrado!\n");
	}
}

/**
 * @brief Função que faz a media de calorias de todos os clientes entre 2 datas pedidas
 * 
 * @param listaCliente 
 * @param listaAlimentos 
 */
void MediaCalPorCliente(Cliente* listaCliente, Alimentos* listaAlimentos){
	Alimentos* al;
	Cliente* cl;
	Cliente* clienteEscolhido;
	
	int auxDataDiaI, auxDataMesI, auxDataAnoI, auxDataDiaF, auxDataMesF, auxDataAnoF;
	double mediaCalPa, mediaCalA, mediaCalL, mediaCalJ, somaCalPAlm = 0, somaCalAlm = 0, somaCalLan = 0,somaCalJan = 0, ipa = 0, ia = 0, il = 0, ij = 0;
	
	system("clear");
		
	printf("Digite o dia Inicial: ");
	fflush(stdin); 
	scanf("%d", &auxDataDiaI);
	
	printf("Digite o mes Inicial: ");
	fflush(stdin); 
	scanf("%d", &auxDataMesI);
	
	printf("Digite o ano Inicial: ");
	fflush(stdin); 
	scanf("%d", &auxDataAnoI);
	
	printf("Digite o dia Final: ");
	fflush(stdin); 
	scanf("%d", &auxDataDiaF);
	
	printf("Digite o mes Final: ");
	fflush(stdin); 
	scanf("%d", &auxDataMesF);
	
	printf("Digite o ano Final: ");
	fflush(stdin); 
	scanf("%d", &auxDataAnoF);
	
	system("clear");
	for( cl = listaCliente; cl != NULL; cl = cl->next){
		for( al = listaAlimentos; al != NULL; al = al->next){
			
			//filtrar lista de alimentos apenas pelos os alimentos do intervalo pedido
			if(dataEstaEntre(auxDataDiaI, auxDataDiaF, al->data.dia, auxDataMesI, auxDataMesF, al->data.mes, auxDataAnoI, auxDataAnoF, al->data.ano)){
				
				if(cl->num_cliente == al->id_cliente && strcmp(al->refeicao, "pequeno almoco") == 0){
					somaCalPAlm = somaCalPAlm + al->cal;
					ipa = ipa + 1;
				}
				
				if(cl->num_cliente == al->id_cliente && strcmp(al->refeicao, "almoco") == 0){
					somaCalAlm = somaCalAlm + al->cal;
					ia = ia + 1;
				}
				
				if(cl->num_cliente == al->id_cliente && strcmp(al->refeicao, "lanche") == 0){
					somaCalLan = somaCalLan + al->cal;
					il = il + 1;
				}
				
				if(cl->num_cliente == al->id_cliente && strcmp(al->refeicao, "jantar") == 0){
					somaCalJan = somaCalJan + al->cal;
					ij = ij + 1;
				}
				
			}
			
		}
		mediaCalPa = somaCalPAlm/ipa;
		if(mediaCalPa > 0){
			printf("\nO Cliente %s consumiu em media %.2f nos seus pequenos almocos\n\n", &cl->nome, mediaCalPa);
			printf("----------------------------------------------------------------------\n\n");
		}
		somaCalPAlm = 0;
		ipa = 0;
		
		mediaCalA = somaCalAlm/ia;
		if(mediaCalA > 0){
			printf("O Cliente %s consumiu em media %.2f nos seus almocos\n\n", &cl->nome, mediaCalA);
			printf("----------------------------------------------------------------------\n\n");
		}
		somaCalAlm = 0;
		ia = 0;
		
		mediaCalL = somaCalLan/il;
		if(mediaCalL > 0){
			printf("O Cliente %s consumiu em media %.2f nos seus Lanches\n\n", &cl->nome, mediaCalL);
			printf("----------------------------------------------------------------------\n\n");
		}
		somaCalLan = 0;
		il = 0;
		
		mediaCalJ = somaCalJan/ij;
		if(mediaCalJ > 0){
			printf("O Cliente %s consumiu em media %.2f nos seus Jantares\n\n", &cl->nome, mediaCalJ);
			printf("----------------------------------------------------------------------\n\n");
		}
		somaCalJan = 0;
		ij = 0;
	}
}

/**
 * @brief Função que faz uma tabela com todos os Planos e com as calorias consumidas
 * 
 * @param listaCliente 
 * @param listaAlimentos 
 * @param listaPlano 
 */
void TabelaDados(Cliente* listaCliente, Alimentos* listaAlimentos, Plano* listaPlano){
	
	Alimentos* al;
	Cliente* cl;
	Plano* pl;
	Cliente* clienteEscolhido;
	
	int somaCalPAlm = 0, somaCalAlm = 0, somaCalLan = 0, somaCalJan = 0;
	
	system("clear");
	
	printf("=======================================================================================================================\n");
    printf("=   NP   =    Paciente    =    Tipo Refeicao    =    Inicio    =     Fim      =   Minimo   =   Maximo   =   Consumo   =\n");
    printf("=======================================================================================================================\n");
	
	for( cl = listaCliente; cl != NULL; cl = cl->next){
		
		for( pl = listaPlano; pl != NULL; pl = pl->next){
			
			if(cl->num_cliente == pl->id_cliente){
				
				for( al = listaAlimentos; al != NULL; al = al->next){
					
					//filtrar lista de alimentos apenas pelos os alimentos do intervalo pedido
					if(dataEstaEntre(pl->data_inicio.dia, pl->data_fim.dia, al->data.dia, pl->data_inicio.mes, pl->data_fim.mes, al->data.mes, pl->data_inicio.ano, pl->data_fim.ano, al->data.ano) ){
							
							if(strcmp(pl->refeicao, al->refeicao) == 0 && pl->id_cliente == al->id_cliente){
								
								if(strcmp(al->refeicao, "jantar") == 0){
									somaCalPAlm = somaCalPAlm + al->cal;
									fflush(stdin); 
								} else if(strcmp(al->refeicao, "almoco") == 0){
									somaCalAlm = somaCalAlm + al->cal;
									fflush(stdin); 
								} else if(strcmp(al->refeicao, "lanche") == 0){
									somaCalLan = somaCalLan + al->cal;
									fflush(stdin); 
								} else if(strcmp(al->refeicao, "pequeno almoco") == 0){
									somaCalJan = somaCalJan + al->cal;
									fflush(stdin); 
								}
								
							}
							
								
					}			
				}
		
				if(strcmp(pl->refeicao, "jantar") == 0){
					printf("=   %-4d =    %-11s =        %-12s =  %02d-%02d-%d  =  %02d-%02d-%d  =     %-6d =     %-6d =     %-6d  =\n", pl->id_cliente, &cl->nome, &pl->refeicao, pl->data_inicio.dia, pl->data_inicio.mes, pl->data_inicio.ano, pl->data_fim.dia, pl->data_fim.mes, pl->data_fim.ano, pl->calmin, pl->calmax, somaCalPAlm);
				    printf("=======================================================================================================================\n");
					somaCalPAlm = 0;
					
				} else if(strcmp(pl->refeicao, "almoco") == 0){
					printf("=   %-4d =    %-11s =        %-12s =  %02d-%02d-%d  =  %02d-%02d-%d  =     %-6d =     %-6d =     %-6d  =\n", pl->id_cliente, &cl->nome, &pl->refeicao, pl->data_inicio.dia, pl->data_inicio.mes, pl->data_inicio.ano, pl->data_fim.dia, pl->data_fim.mes, pl->data_fim.ano, pl->calmin, pl->calmax, somaCalAlm);
				    printf("=======================================================================================================================\n");
					somaCalAlm = 0;
				} else if(strcmp(pl->refeicao, "lanche") == 0){
					printf("=   %-4d =    %-11s =        %-12s =  %02d-%02d-%d  =  %02d-%02d-%d  =     %-6d =     %-6d =     %-6d  =\n", pl->id_cliente, &cl->nome, &pl->refeicao, pl->data_inicio.dia, pl->data_inicio.mes, pl->data_inicio.ano, pl->data_fim.dia, pl->data_fim.mes, pl->data_fim.ano, pl->calmin, pl->calmax, somaCalLan);
				    printf("=======================================================================================================================\n");
					somaCalLan = 0;
				} else if(strcmp(pl->refeicao, "pequeno almoco") == 0) {
					printf("=   %-4d =    %-11s =   %-17s =  %02d-%02d-%d  =  %02d-%02d-%d  =     %-6d =     %-6d =     %-6d  =\n", pl->id_cliente, &cl->nome, &pl->refeicao, pl->data_inicio.dia, pl->data_inicio.mes, pl->data_inicio.ano, pl->data_fim.dia, pl->data_fim.mes, pl->data_fim.ano, pl->calmin, pl->calmax, somaCalJan);
				    printf("=======================================================================================================================\n");
					somaCalJan = 0;
				}
				
			}	
		
		}
					
	}
	
}	

