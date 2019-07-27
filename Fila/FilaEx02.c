#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FilaBase.h"

void LerNomes(Fila* ptrFila);
void MostrarNomes(Fila* ptrFila);

int main(){
	Fila* ptrFila = CriarFila();
	for(int i = 0; i < 22; i++){
		LerNomes(ptrFila);
	}
	MostrarNomes(ptrFila);
	return 0;
}

void LerNomes(Fila* ptrFila){
	char* nome = (char*) malloc(sizeof(char)*30);

	printf("Nome: ");
	scanf("%s", nome);
	Enfileirar(ptrFila, (void*)nome);

}

void MostrarNomes(Fila* ptrFila){
	char* nome;

	printf("\nOrdem de Largada: \n");
	for(int i = 1; i <= 20; i++){
		nome = (char*) Desenfileirar(ptrFila);
		printf("%i. %s\n", i, nome);
		free(nome);
	} 
}