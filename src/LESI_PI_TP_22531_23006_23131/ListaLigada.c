#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include "ListaLigada.h"
#include "Cliente.h"
#include "Alimentos.h"
#include "Plano.h"

/**
 * @brief Função que imprime o menu do programa
 * 
 * @param listaCliente 
 * @param listaAlimentos 
 * @param listaPlano 
 */
void menuPrincipal(Cliente* listaCliente, Alimentos* listaAlimentos, Plano* listaPlano)
{
	// sera usada como condicao para que o laco DO WHILE ocorra. Assim, caso o usuario digite 0, ele vai sair do programa. 
	// Caso ele digite qualquer outro numero, a opcao tratada pelo teste condicional SWITCH.	
    int continuar=-1;
    int aux=-1;
    int idEscolhido=-1;
    do {
    	
        system("clear");
        printf("====================================================================\n");
        printf("\n\tNutricionista\n\n");
        printf("====================================================================\n\n");
        printf(" 1. Adicionar Paciente\n");
        printf(" 2. Remover Paciente\n");
        printf(" 3. Editar Paciente\n");
        printf(" 4. Ver Paciente\n\n");
        printf("====================================================================\n\n");
        printf(" 5. Adicionar Alimento\n\n");
        printf("====================================================================\n\n");
        printf(" 6. Adicionar Plano Nutricional\n\n");
        printf("====================================================================\n\n");
        printf(" 7. Ver Pacientes que passaram certas calorias\n");
        printf(" 8. Listar Pacientes Fora de Calorias\n");
        printf(" 9. Listar Planos por Paciente\n");
        printf(" 10. Media de calorias dos Pacientes\n");
        printf(" 11. Tabela de Informacoes\n\n");
        printf("====================================================================\n\n");  
        printf(" 0. Sair\n\n");
        printf("====================================================================\n");

        do
        {
            fflush(stdin);
            if(scanf("%d", &aux) != 0){
                continuar = aux;
            }
            if(continuar < 0 || continuar > 8) {
                system("clear");
		        printf("====================================================================\n");
		        printf("\n\tNutricionista\n\n");
		        printf("====================================================================\n\n");
		        printf(" 1. Adicionar Paciente\n");
		        printf(" 2. Remover Paciente\n");
		        printf(" 3. Editar Paciente\n");
		        printf(" 4. Ver Paciente\n\n");
		        printf("====================================================================\n\n");
		        printf(" 5. Adicionar Alimento\n\n");
		        printf("====================================================================\n\n");
		        printf(" 6. Adicionar Plano\n\n");
		        printf("====================================================================\n\n");
		        printf(" 7. Validar Pacientes que ultrapassaram o numero de calorias\n");
		        printf(" 8. Listar Pacientes Fora de Calorias\n");
		        printf(" 9. Listar Planos por Paciente num periodo\n");
		        printf(" 10. Media de calorias dos Pacientes\n");
        		printf(" 11. Tabela de Informacoes\n\n");
		        printf("====================================================================\n\n");  
		        printf(" 0. Sair\n\n");
		        printf("====================================================================\n");
            }
        } while(continuar < 0 || continuar > 11 );

        switch(continuar)
        {
            case 1:
            	adicionar(listaCliente);
                break;

            case 2:
                remover(listaCliente);
                break;

            case 3:
				editar(listaCliente);
                break;
            
            case 4:
                visualizarCliente(listaCliente);
				break;
				
			case 5:
                addAlimento(listaCliente, listaAlimentos);
				break;
				
			case 6:
				addPlano(listaCliente, listaPlano);
				break;
				
			case 7:
				NumPacientesPassamCals(listaAlimentos, listaCliente);
				break;
				
			case 8:
				PacientesComRefeicaoForadeCals(listaAlimentos, listaCliente, listaPlano);
				break;
				
			case 9:
				ListarPlanosPorCliente(listaPlano, listaCliente);
				break;
			
			case 10:
				MediaCalPorCliente(listaCliente, listaAlimentos);
				break;	
				
			case 11:
				TabelaDados(listaCliente,  listaAlimentos, listaPlano);
				break;	

            case 0:
                printf("\n***  Adeus!  ***");
                break;

            default:
                printf("\nDigite uma opcao valida\n\n\n");
                break;
            
        }
		
		//guardar variaveis a cada alteracao
		guardarBaseDeDados(listaCliente);
		guardarBaseDeDadosAlimentos(listaAlimentos);
		guardarBaseDeDadosPlano(listaPlano);
		
        printf("\n");
        printf("Pressione Enter para continuar");
        getchar();

        while(getchar() != '\n');
        
    } while(continuar != 0);
}
