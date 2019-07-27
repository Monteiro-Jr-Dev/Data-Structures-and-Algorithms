#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FilaBase.h"

int LerNomes(Fila* ptrFila);
void MostrarNomes(Fila* ptrFila);

int main(){
	Fila* ptrFila = CriarFila();
	while (LerNomes(ptrFila));
	MostrarNomes(ptrFila);
	return 0;
}

int LerNomes(Fila* ptrFila){
	char* nome = (char*) malloc(sizeof(char)*30);

	printf("Nome: ");
	scanf("%s", nome);

	if(!strcmp(nome, "FIM")){
		free(nome);
		return 0;
	}

	Enfileirar(ptrFila, (void*)nome);
	return 1;
}

void MostrarNomes(Fila* ptrFila){
	char* nome;

	printf("\nOrdem de Atendimento: \n");
	while(!_filaVazia(ptrFila)){
		nome = (char*) Desenfileirar(ptrFila);
		printf("%s\n", nome);
		free(nome);
	} 
}