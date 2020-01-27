#include <stdio.h>
#include <stdlib.h>
#include "PilhaBase.h"

void InserirNumero(Pilha* ptrPilha);
void RemoverNumero(Pilha* ptrPilha);
void ExibirPilha(Pilha* ptrPilha);
Pilha* CopiarPilha(Pilha* ptrPilha);
int Menu();

int main(){
	Pilha* ptrPilha = CriarPilha();
	Pilha* copiaPilha;
	int opcao;

	while(opcao = Menu()){
		switch(opcao){
			case 1:
			InserirNumero(ptrPilha);
			break;

			case 2:
			RemoverNumero(ptrPilha);
			break;

			case 3:
			ExibirPilha(ptrPilha);
			break;

			case 4:
			copiaPilha = CopiarPilha(ptrPilha);
			printf("Pilha Nova: \n");
			ExibirPilha(copiaPilha);
			break;
		}
	}
	return 0;
}

void InserirNumero(Pilha* ptrPilha){
	float* numero = (float*) malloc(sizeof(float));
	printf("Digite o Numero: ");
	scanf("%f", numero);
	printf("%.2f",*numero);
	Empilhar(ptrPilha, (void*)numero);
}

void RemoverNumero(Pilha* ptrPilha){
	if(_pilhaVazia(ptrPilha)){
		printf("Pilha Vazia\n");
		return;
	}

	float* numero = (float*) Desempilhar(ptrPilha);
	printf("Numero Desempilhado: %.2f", *numero);
	free(numero);
}

void ExibirPilha(Pilha* ptrPilha){
	
	if(_pilhaVazia(ptrPilha))
		return;
	
	float* numero;

	printf("Numeros na pilha: ");
	Node* ptrNo = ptrPilha->topo;
	do{	
		numero = (float*) ptrNo->ptrDados;
		printf("%.2f, ",*numero);
		ptrNo = ptrNo->proximoNo;
	} while (ptrNo != NULL);
}

Pilha* CopiarPilha(Pilha* ptrPilha){
	if(_pilhaVazia(ptrPilha))
		return NULL;

	Pilha* novaPilha = CriarPilha();
	Pilha* tempPilha = CriarPilha();

	void* ptrDados;
	
	while (!_pilhaVazia(ptrPilha)){
		ptrDados = Desempilhar(ptrPilha);
		Empilhar(tempPilha, ptrDados);
	}

	while (!_pilhaVazia(tempPilha)){
		ptrDados = Desempilhar(tempPilha);
		Empilhar(ptrPilha, ptrDados);

		float* novoDado = (float*) malloc(sizeof(float));
		*novoDado = *((float*)ptrDados);
		Empilhar(novaPilha, (void*)novoDado);
	}

	return novaPilha;
}

int Menu(){
	int numero;
	printf("\n01. Inserir\n");
	printf("02. Remover\n");
	printf("03. Exibir Pilha\n");
	printf("04. Copiar Pilha\n");
	printf("00. Sair\n");
	scanf("%i", &numero);
	return numero;
}