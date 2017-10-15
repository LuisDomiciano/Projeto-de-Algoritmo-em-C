#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define limpatela();system ("cls");
#define clrbuffer(); fflush (stdin);

typedef struct Telefone 
{
	char NOME [30], TELEFONE [20];
	struct Telefone *prox;
	struct Telefone *ant;
} TEL;

TEL *apInicio, *apFim;

void adicionar ( char *xNome, char *xTelefone );
void imprime();
void busca (char *chave);
void remover (char *chave);

int main(int argc, char *argv[]) {

	apInicio = apFim = NULL;	
	int  op = 1;
	
	do {		
		limpatela();
		puts ("0-Sair\n1-Adicionar\n2-Imprimir\n3-Busca\n4-Remover");
		puts ("\nSua opcao:	");
		scanf ("%d", &op);
		switch (op){
			case 0:
					return 0;
			break;
			case 1:
				   limpatela();
				   char nome [30], phone [20];
				   puts ("Informe o nome: ");
				   clrbuffer();
				   gets (nome);
				   puts ("Informe o telefone: ");
				   gets (phone);
				   strlwr (nome);
				   adicionar (nome, phone);
				   getch();
		    break;
			case 2:
				   imprime();
				   getch();
			break;
			case 3:
				   limpatela();
				   puts ("Informe o nome a ser pesquisado: ");
				   clrbuffer();
				   gets (nome);
				   strlwr (nome);
				   busca(nome);
				   getch();
		    break;
			case 4:
					limpatela();
					puts ("Informe o elemento a ser removido");
					clrbuffer();
					gets (nome);
					remover (nome);
					getch();
			break;
			default: 
					puts ("Opcao errada");
					getch();
			break;
		}
	
	} while (op != 0);
	
	
	getch();
	return 0;
}

void remover (char *chave)
{
	TEL *proc;
	proc = apInicio;
	
	if ( proc == NULL ){
		puts ("Lista vazia");
	} 
	
	else 
	{			
		if(proc->ant == NULL && strcmp(proc->NOME, chave) == 0)
		{
			apInicio = apInicio->prox;
			apInicio->ant = NULL;
			free(proc);
		}
		else
		{
			do
			{
				proc = proc->prox;
			//	achou = strcmp(proc->NOME, chave);
				
				if(proc->prox != NULL && strcmp (proc->NOME, chave) == 0)
				{
					proc->prox->ant = proc->ant;
					proc->ant->prox = proc->prox;
					free(proc);
					break;
				}
				if(proc->prox == NULL && strcmp(proc->NOME, chave) == 0)
				{
					apFim = apFim->ant;
					apFim->prox = NULL;
					free(proc);
					break;
				}
			}while(proc->prox != NULL);
		}
		
	}
}


void busca (char *chave)
{
	TEL *proc;
	proc = apInicio;
	
	if (proc == NULL)
	{
		puts ("Lista Vazia");
	} else {
		int achou = 0;
		do {
			if( strcmp (proc->NOME, chave ) == 0 ){
				achou = 1;
				printf ("\nContato encontrado\n Nome: %s\tTelefone: %s", proc->NOME, proc->TELEFONE);
				break;
			}
			proc = proc->prox;
		} while (proc != apFim->prox && achou == 0);
		if ( achou == 0)
			puts ("\nContato nao existe\n");
	}	
}

void imprime()
{
	limpatela();
	TEL *ponto;
	ponto = apInicio;
	
	if (ponto == NULL)
	{
		puts ("Lista Vazia...");
		
	} else {
		puts ("Lista de contatos\n");
		do {
			printf ("Nome: %s\nTelefone: %s\n\n",ponto->NOME, ponto->TELEFONE);
			ponto = ponto->prox;
		} while (ponto != apFim->prox);
	}

}

void adicionar ( char *xNome, char *xTelefone )
{
	TEL *apnovo;

	apnovo = (TEL *) malloc ( sizeof (TEL));
	
	if (!apnovo) // verifica se foi alocado espaço de memória
	{
		puts ("\nNao foi possivel adicionar contato\nMemoria cheia ...\n");
		exit (1);
	}
	
	strcpy (apnovo->NOME, xNome);
	strcpy (apnovo->TELEFONE,  xTelefone);
	if (apInicio == NULL) //verifica se a lista está vazia
	{
		apnovo->prox = NULL;
		apnovo->ant = NULL;
		apFim = apnovo; //guarda o endereço do novo
		apInicio = apnovo;
	}
	//O ínicio nunca será alterado
	apnovo->ant = apFim;
	apnovo->prox = NULL; //novo elemento não tem ninguém a frente
	apFim->prox = apnovo;
	apFim = apnovo; //fum recebe o endereço do atual novo
	
	puts ("Cadastrado com suceso !");
}
	
