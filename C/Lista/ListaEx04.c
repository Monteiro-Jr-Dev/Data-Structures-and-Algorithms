/*IFF Campos
* Estruturas de Dados
* Lista Simples
* Valmir Monteiro & José Gustavo
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FilaBase.h"

typedef struct  _string{
	char Palavra[50];
}String;

// Declaração das Funções
int FuncaoComparar(void* parametro1, void* parametro2);
void LerPalavra(String* s1);
int ArmazenarPalavra(Lista* lista);
void ExibirLista(Lista* lista);
void _imprimirPalavras(Node* no);


int main(){
	Lista* lista = CriarLista(FuncaoComparar);	
	while(ArmazenarPalavra(lista));
	ExibirLista(lista);
	DestruirLista(lista);
}

int FuncaoComparar(void* parametro1, void* parametro2){
	String* s1 = (String*)parametro1;
	String* s2 = (String*)parametro2;
	int res = strcmp(s1->Palavra, s2->Palavra);
	if(res > 0)
		return 1;
	else if(res < 0)
		return -1;
	return 0;
}

void LerPalavra(String* s1){	
	printf("Palavra: ");
	scanf("%s", s1->Palavra);
	while (getchar() != '\n');
}

int ArmazenarPalavra(Lista* lista){
	String* s1 = (String*) malloc(sizeof(String));
	LerPalavra(s1);

	if(!strcmp(s1->Palavra, "xyz")){
		return 0;
	}

	if(_procurarPosicaoNo(lista, (void*) s1)){
		printf("--------------------\n");
		printf("Palavra já existe. \n");
		printf("--------------------\n");
		return 1;
	} else {
		AdicionarNoOrdenado(lista, s1);
	}
}

void ExibirLista(Lista* lista){
	printf("---------- Lista Ordenada ----------\n");
	AtravessarLista(lista, _imprimirPalavras);
	printf("---------- Fim da Lista ----------\n");
}

void _imprimirPalavras(Node* no){
	String* s1 = (String*)(no->PontDados);
	printf("%s\n",s1->Palavra);
}