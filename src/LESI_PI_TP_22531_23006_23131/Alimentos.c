#include "ListaLigada.h"
#include "Alimentos.h"
#include "Cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

/**
 * @brief Função que envia dados para o ficheiro txt
 * 
 * @param listaAlimentos
 * 
 */
void guardarNormalal(Alimentos* listaAlimentos) {
    Alimentos* al;
    FILE *dbAlimentos= fopen("dbAlimentos.txt", "w");

    if(dbAlimentos == NULL) 
		printf("\nERRO!");
	/**
	 * @brief Iterar pela lista ligada e escrever no ficheiro
	 * 
	 */
	for( al = listaAlimentos; al != NULL; al = al->next){
            fprintf(dbAlimentos,"%d;%d-%d-%d;%s;%s;%d\n", al->id_cliente, al->data.dia, al->data.mes, al->data.ano, al->refeicao, al->alimento, al->cal);
    }
    fclose(dbAlimentos);

}

/**
 * @brief Função que envia dados para o ficheiro txt em binario
 * 
 * @param listaAlimentos 
 */
void guardarBinarioal(Alimentos* listaAlimentos) {
    Alimentos* ali;
	
    FILE *AlimentosBin = fopen("alimentos.dat", "wb");

	/**
	 * @brief Verificar se existe na diretoria
	 * 
	 */
    if (AlimentosBin == NULL) {
        perror("Não foi possivel abrir o ficheiro");
        exit(EXIT_FAILURE);
    }
    // 
	/**
	 * @brief Enviar dados para o ficheiro em binário
	 * 
	 */
    for( ali = listaAlimentos; ali != NULL; ali = ali->next){
        fwrite(ali, sizeof(Alimentos), 1, AlimentosBin);
    }
    // Close the file
    fclose(AlimentosBin);
}

/**
 * @brief Guardar dados no ficheiro txt com Tabs
 * 
 * @param listaAlimentos 
 */
void guardarTabuladoresal(Alimentos* listaAlimentos) {
    Alimentos* al;
    FILE *dbAlimentos= fopen("AlimentosTab.txt", "w");

    if(dbAlimentos == NULL) 
		printf("\nERRO!");
    /**
     * @brief Iterar pela lista ligada e escrever no ficheiro
     * 
     */
	for( al = listaAlimentos; al != NULL; al = al->next){
            fprintf(dbAlimentos,"%d\t%d-%d-%d\t%s\t%s\t%d\n", al->id_cliente, al->data.dia, al->data.mes, al->data.ano, al->refeicao, al->alimento, al->cal);
    }

    fclose(dbAlimentos);

}

/**
 * @brief Função que lê o txt de alimentos ao iniciar o programa e guarda numa lista ligada
 * 
 * @return Alimentos* 
 */
Alimentos* lerBaseDeDadosAlimentos(){
    Alimentos* lista = NULL;
    Alimentos* novo = NULL;
	
	FILE *dbAlimentos = fopen("dbAlimentos.txt", "r");

    /**
     * @brief Verificar se existe na diretoria
     * 
     */
	if(dbAlimentos == NULL) {
		printf("\nERRO!");
	}
	
    /**
     * @brief iterar a cada linha do ficheiro a fim de atribuir a um objeto e adiciona-lo a uma lista
     * 
     */
    while(!feof(dbAlimentos)) {
        novo = (Alimentos*)calloc(1, sizeof(Alimentos));
        fscanf(dbAlimentos,"%d;%d-%d-%d;%[^;];%[^;];%d\n", &(novo->id_cliente), &(novo->data.dia), &(novo->data.mes), &(novo->data.ano), &(novo->refeicao), &(novo->alimento), &(novo->cal));
            lista = adicionarAlimentos(lista, novo);
    }

    fclose(dbAlimentos);

    return lista;
}

/**
 * @brief Função que chama as 3 funções de guardar ficheiros
 * 
 * @param listaAlimentos 
 */
void guardarBaseDeDadosAlimentos(Alimentos* listaAlimentos){
	
	guardarNormalal(listaAlimentos);
	guardarBinarioal(listaAlimentos);
	guardarTabuladoresal(listaAlimentos);
}

/**
 * @brief Função que pede os dados para adicionar um Alimento
 * 
 * @param listaCliente 
 * @param listaAlimentos 
 */
void addAlimento(Cliente* listaCliente, Alimentos* listaAlimentos) {
    
    Alimentos* novoAlimento = (Alimentos*)calloc(1, sizeof(Alimentos));
    int auxIDCliente = -1, auxDataDia, auxDataMes, auxDataAno, auxCal;
    Cliente* clienteEscolhido;
    
    printf("Digite o id do Cliente: ");
	fflush(stdin);
    scanf("%d", &auxIDCliente);
    
    clienteEscolhido = encontrarCliente(listaCliente, auxIDCliente);
    
    if(clienteEscolhido != NULL){
    	novoAlimento->id_cliente = auxIDCliente;
		
		printf("Digite o dia: ");
		fflush(stdin); 
		scanf("%d", &auxDataDia);
		novoAlimento->data.dia = auxDataDia;
		
		printf("Digite o mes: ");
		fflush(stdin); 
		scanf("%d", &auxDataMes);
		novoAlimento->data.mes = auxDataMes;
		
		printf("Digite o ano: ");
		fflush(stdin); 
		scanf("%d", &auxDataAno);
		novoAlimento->data.ano = auxDataAno;
		
		printf("Em que refeicao vai ser? ");
		fflush(stdin);
		getchar();
	    fgets(novoAlimento->refeicao, 20, stdin);
	    novoAlimento->refeicao[strcspn(novoAlimento->refeicao, "\n")] = 0; // tira a nova linha "\n" que tenho no alimento
		
		printf("Digite o Alimento: ");
		fflush(stdin);
		getchar();
	    fgets(novoAlimento->alimento, 20, stdin);
	    novoAlimento->alimento[strcspn(novoAlimento->alimento, "\n")] = 0; // tira a nova linha "\n" que tenho no alimento
		
		printf("Digite o numero de calorias: ");
		fflush(stdin); 
		scanf("%d", &auxCal);
		novoAlimento->cal = auxCal;
		
		listaAlimentos = introduzirAlimento(listaAlimentos, novoAlimento);

		printf("\nAdicionado com sucesso!\n");
    	
			
	} else {
        printf("Cliente nao encontrado!\n");
	}
			
}

/**
 * @brief Função para adicionar um cliente
 * 
 * @param listaAlimentos 
 * @param novoAlimento 
 * @return Alimentos* 
 */
Alimentos* introduzirAlimento(Alimentos* listaAlimentos, Alimentos* novoAlimento)
{
	//se a lista for NULL, devolve o meu novo cliente
	if(listaAlimentos == NULL) return novoAlimento;
	//se lista for diferente de NULL, o proximo cliente vai continuar a procurar um espaco "NULL" 
	listaAlimentos->next = introduzirAlimento(listaAlimentos->next, novoAlimento);
	
	//da return a lista depois da atualiza??o
	return listaAlimentos;
}

/**
 * @brief Função para adicionar um alimento ao ler um ficheiro txt
 * 
 * @param listaAlimentos 
 * @param novoAlimento 
 * @return Alimentos* 
 */
Alimentos* adicionarAlimentos(Alimentos *listaAlimentos, Alimentos *novoAlimento)
{
	//se a lista for NULL, devolve o meu novo cliente
	if(listaAlimentos == NULL) return novoAlimento;
	//se lista for diferente de NULL, o proximo cliente vai continuar a procurar um espaco "NULL" 
	listaAlimentos->next = adicionarAlimentos(listaAlimentos->next, novoAlimento);
	//da return a lista depois da atualizacao
	return listaAlimentos;
}

/**
 * @brief Liberta a memoria alocada pela lista & Uso de recursao 
 * 
 * @param lista 
 */
void libertarMemoriaAlimentos(Alimentos* lista){
    if(lista == NULL)
        return;

    libertarMemoriaAlimentos(lista->next);

    free(lista);
}

/**
 * @brief Função que valida se a data está entre outras duas datas
 * 
 * @param dia1 
 * @param dia2 
 * @param dia3 
 * @param mes1 
 * @param mes2 
 * @param mes3 
 * @param ano1 
 * @param ano2 
 * @param ano3 
 * @return int 
 */
int dataEstaEntre(int dia1, int dia2, int dia3, int mes1, int mes2, int mes3, int ano1, int ano2, int ano3) {
    if ((ano1 < ano3 && ano3 < ano2) ||
        (ano1 == ano3 && ano3 == ano2 &&
         ((mes1 <= mes3 && mes3 <= mes2) ||
          (mes1 == mes3 && mes3 == mes2 &&
           (dia1 <= dia3 && dia3 <= dia2))))) {
        return 1; // Verdadeiro, data3 est� entre data1 e data2
    } else {
        return 0; // Falso, data3 n�o est� entre data1 e data2
    }
}

/**
 * @brief Função que vê quantos Pacientes passaram o numero de calorias introduzidas
 * 
 * @param listaAlimentos 
 * @param listaCliente 
 */
void NumPacientesPassamCals(Alimentos* listaAlimentos, Cliente* listaCliente){
	Alimentos* al;
	Cliente* cl;
	
	int auxDataDiaI, auxDataMesI, auxDataAnoI, auxDataDiaF, auxDataMesF, auxDataAnoF, auxCalPedido, CalSoma = 0, numClientesCal = 0;
	
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
	
	printf("Digite o numero de calorias: ");
	fflush(stdin); 
	scanf("%d", &auxCalPedido);
	
	for( cl = listaCliente; cl != NULL; cl = cl->next){
		for( al = listaAlimentos; al != NULL; al = al->next){
			if(cl->num_cliente == al->id_cliente && dataEstaEntre(auxDataDiaI, auxDataDiaF, al->data.dia, auxDataMesI, auxDataMesF, al->data.mes, auxDataAnoI, auxDataAnoF, al->data.ano)){
				CalSoma = CalSoma + al->cal;
			}
    	}
    	if(CalSoma > auxCalPedido){
			numClientesCal = numClientesCal + 1;
    	}
    	
		CalSoma = 0;
		
    	
    };
    
    if(numClientesCal == 1){
    	printf("So 1 pessoa e que passou o limite de calorias");
	} else {
		printf("%d pessoas passaram o limite de calorias", numClientesCal);
	}
	
}


/**
 * @brief Função que Lista todos os Pacientes fora de Calorias em uma certa refeição, por ordem decrescente
 * 
 * @param listaAlimentos 
 * @param listaCliente 
 * @param listaPlano 
 */
void PacientesComRefeicaoForadeCals(Alimentos* listaAlimentos, Cliente* listaCliente, Plano* listaPlano) {
	 
	system("clear");
	 
	Alimentos* al;
	Cliente* cl;
	Cliente* temp;
	Plano* pl;
	
	int auxDataDiaI, auxDataMesI, auxDataAnoI, auxDataDiaF, auxDataMesF, auxDataAnoF, count = 0;
	
	
	for(cl = listaCliente; cl != NULL; cl = cl->next){
		count += 1;
}
	
	Cliente* arrcl[count];
	
	count = 0;
	
	for(cl = listaCliente; cl != NULL; cl = cl->next){
		arrcl[count] = cl;
		count += 1;
	}
	
	
	
	int i, j;
    bool swapped;
	/**
	 * @brief for para trocar a ordem dos Pacientes por ordem decrescente
	 * 
	 */
    for (i = 0; i < count - 1; i++) {
       	swapped = false;
       	for (j = 0; j < count - i - 1; j++) {
           	if (arrcl[j]->num_cliente > arrcl[j + 1]->num_cliente) {
            	
            	temp = arrcl[j];
            	arrcl[j] =arrcl[j + 1];
            	arrcl[j + 1] = temp;
               	
           	}
       	}
		/**
		 * @brief Se nao trocar de ordem dá break
		 * 
		 */
        if (swapped == false)
            break;
  	}
    
    
	
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
	
	printf("\n");

	printf("------------------------------------------------------------------------------------------------------------\n\n");
	/**
	 * @brief Vários For's e If's para percorrer as varias listas e imprimir os cliente com as respectivas condições
	 * 
	 */
	for(i = 0; i < count; i++){
		for( al = listaAlimentos; al != NULL; al = al->next){
    		if(arrcl[i]->num_cliente == al->id_cliente && dataEstaEntre(auxDataDiaI, auxDataDiaF, al->data.dia, auxDataMesI, auxDataMesF, al->data.mes, auxDataAnoI, auxDataAnoF, al->data.ano)){
    			
    			
    			for( pl = listaPlano; pl != NULL; pl = pl->next){
    				if(arrcl[i]->num_cliente == pl->id_cliente && dataEstaEntre(pl->data_inicio.dia, pl->data_fim.dia, al->data.dia, pl->data_inicio.mes, pl->data_fim.mes, al->data.mes, pl->data_inicio.ano, pl->data_fim.ano, al->data.ano)){

						if(al->id_cliente == pl->id_cliente) {
							if(al->cal > pl->calmax || al->cal < pl->calmin) {
								printf("O cliente %s tinha de consumir entre %d e %d calorias no dia %d-%d-%d e consumiu %d \n\n", &arrcl[i]->nome, pl->calmin, pl->calmax, al->data.dia, al->data.mes, al->data.ano, al->cal);
							}
						}
					}
				}	
			}
		}
    }
    
    
	
}



