#include <stdbool.h>

typedef struct _data {
    int dia;
    int mes;
    int ano;
} Data;

// estrutura cliente
typedef struct _cliente{
   	int num_cliente;
   	char nome[20];
   	int telemovel;
   	struct _cliente* next;
} Cliente;

// estrutura alimento
typedef struct _alimentos{
   	int id_cliente;
   	Data data;
   	char refeicao[20];
   	char alimento[20];
   	int cal;
   	struct _alimentos* next;
} Alimentos;

typedef struct _plano{
   	int id_cliente;
   	Data data_inicio;
   	Data data_fim;
   	char refeicao[20];
   	int calmin;
   	int calmax;
   	struct _plano* next;
} Plano;


void menuPrincipal(Cliente*, Alimentos*, Plano*);

