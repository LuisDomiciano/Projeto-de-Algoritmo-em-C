#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#define TAM 30
#define cls(); system("cls");
#define color(); system("color 1e");
#define clrbuffer(); fflush(stdin);

typedef struct arvore {
		char info[TAM];
		int cont;
		struct arvore *lado_direito, *lado_esquerdo;
} no;

no *apraiz, *apno, *apaux;
void adiciona_no (char info[TAM]);
void imprime_arvore (no *apno, int tabulacoes);
int copia ( char *d, char *o);
int localiza (char info [TAM]);

char nome[TAM];
char str [200];
char destino[TAM];

int achou;

int main (void)
{
	color();
	cls();
	apraiz = malloc( sizeof (no) );
	apraiz = NULL;

	puts("\tDigite uma frase");
	clrbuffer();// limpa buffer
	gets(str);
    strupr(str);
	char destino[TAM];
	
	char *pointer_char;
	/*Atribui a pointer_char um ponteiro para o token em "str"
	O segundo argumento são os delimitadores, isto é, os caracteres
	a serem ignorados na divisão da string em pedaços (tokens).*/
	pointer_char = strtok (str, " ,.-"); // arg str e os delimitadores, pointer_char aponta para os caracteres que não forem ,.-
	
	while (pointer_char != NULL) 
	{
		copia(destino, pointer_char);
		/*Ao encontrar caracteres do segundo argumento
		é substituído por NULL ('\0') indicando o fim do primeiro token*/
		pointer_char =  strtok ( NULL, " -.,"); 
		/*o primeiro argumento NULL indica que a divisão (token) deve continuar
		a partir da última chamada a strtok*/
		printf("\n%s\n", destino);
		adiciona_no(destino);
	}    

    if ( apraiz == NULL) {
        puts("Arvore vazia\nFim do Programa");
        return 0;
    } 

	puts("\n\nImpressao da arvore");
	imprime_arvore(apraiz, 1);
	puts("\n<ENTER> para continuar");
	getchar();

	int *retorno = malloc(sizeof(int));

    do {
		cls();
		puts("\t\tImpressao da arvore\n");
		imprime_arvore(apraiz, 1);
        puts("\n\nInforme a palavra a ser localizada (fim-finaliza)");
        clrbuffer();
        gets(nome);
        strupr(nome);
        *retorno = localiza(nome);
		
        if ( *retorno > 0 ) {
            printf("Palavra: %s  Repete: %d vezes", nome, apno->cont);
			getch();
			
        } else if ( strcmp (nome, "FIM") == 0) {
                  printf("\nFim do programa");
        }
         else {	
            printf("\nEsta palavra nao se encontra na arvore!");
			getch();
        }
		
    } while (strcmp (nome, "FIM") !=0 );
	
	getch();
	return 0;
}

/* ponteiro d (destino) recebe os caracteres do ponteiro o (origem) 
enquanto não for encontrado o caracter nulo '\0' que indica o fim da palavra*/
/* char *d e *o são parâmetros de refência que altera o conteúdo das variáveis
no local chamador*/
int copia ( char *d, char *o)
{
	/* *d recebe os caracteres de *o enquanto não for encontrado o caracter nulo ('\0') que 
	indica o fim do token ( a palavra )*/
	while ( (*d++ = *o++) != '\0' );
	return 1; // ocorreu a cópia
}

void adiciona_no (char info[TAM])
{
	int achou, entraesq;
	apno = apraiz; //apno aponta para raiz
	achou = 0;
	

	while (apno != NULL && achou == 0)
	{
		apaux = apno;
		//se a informação for menor que a raiz, então entra a esquerda
		if ( strcmp (apno->info, info ) > 0 )
		{
			apno = apno->lado_esquerdo;
			entraesq = 1;
		}
		//se a informação for maior, então entra a direita
		else if ( strcmp ( apno->info, info ) < 0 )
			{
				apno = apno->lado_direito;
				entraesq = 0;
			}
			else { achou = 1; // se não é maior e nem menor, logo é igual
			       apno->cont = apno->cont+1;			   
			}
	}//while
	if ( achou == 0 )
    {
		apno = malloc ( sizeof ( no ) );
		strcpy ( apno->info, info); //copia o novo elemento para o no
		apno->lado_direito = NULL;
		apno->lado_esquerdo = NULL;
		apno-> cont=1;
		//como é o primeiro nó da arvore, não aponta para ninguém
		if ( apraiz == NULL ) // se a raiz estiver vazia o elemento entra na raiz
			apraiz = apno;
		else if ( entraesq == 1)
			 apaux->lado_esquerdo = apno;
		else
		    apaux->lado_direito = apno;
	}//if
}//função adiciona elemento

void imprime_arvore (no *apno, int tabulacoes)
{
	int j;

	if ( apno != NULL)
	{	
		imprime_arvore ( apno->lado_esquerdo, tabulacoes+2 );
		for (j = 1; j <= tabulacoes; j++)
		
			printf ("\t");
			printf("[ %s ]%d]\n",apno->info, apno->cont);
			imprime_arvore(apno->lado_direito,tabulacoes+2);		
	}	
}

int localiza (char busca [TAM]) {

	apno = apraiz;
	achou = 0;
	while ( apno != NULL )
	{
		/*se a informação do nó for igual a busca 
		é retornado o campo cont que indica quantas vezes a palavra se repete*/
		if ( strcmp (apno->info, busca) == 0)
			return apno->cont;
		/*se a informação do nó for menor que busca
		deve-se percorrer a sub-arvore da direita*/	
		if ( strcmp (apno->info, busca) < 0)
		{
			apno = apno->lado_direito;
		}else {
			apno = apno->lado_esquerdo;
		/*caso a informação do nó seja maior que a busca
		deve-se percorrer a sub-arvore da esquerda*/
		}
	}
  return -1; // caso "busca" não seja encontrado é retornado -1
}
