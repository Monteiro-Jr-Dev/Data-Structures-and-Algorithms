#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "PilhaBase.h"

typedef struct{
	char Carta[10];
}Carta;

void InserirCarta(Pilha* ptrPilha);
void RemoverCarta(Pilha* ptrPilha);
void ExibirPilha(Pilha* ptrPilha);
Pilha* CopiarPilha(Pilha* ptrPilha);
void Consultar(Pilha* ptrPilha);
void Embaralhar(Pilha* ptrPilha);
int numAleatorio(int tamPilha);
int Menu();

int main(){
	Pilha* ptrPilha = CriarPilha();
	Pilha* copiaPilha;
	int opcao;

	while(opcao = Menu()){
		switch(opcao){
			case 1:
			InserirCarta(ptrPilha);
			break;

			case 2:
			if(!_pilhaVazia(ptrPilha))
				RemoverCarta(ptrPilha);
			else
				printf("\nPilha Vazia\n");
			break;

			case 3:
			if(!_pilhaVazia(ptrPilha))
				Consultar(ptrPilha);
			else
				printf("\nPilha Vazia\n");
			break;

			case 4:
			if(_pilhaCont(ptrPilha) > 1){
				printf("\nPilha Antes de Embaralhar: \n");
				ExibirPilha(ptrPilha);
				Embaralhar(ptrPilha);
				printf("\nPilha Embaralhada: \n");
				ExibirPilha(ptrPilha);
			} else{
				printf("\nSem elementos suficientes\n");
			}
			break;
		}
	}
	return 0;
}

void InserirCarta(Pilha* ptrPilha){
	char* carta = (char*) malloc(sizeof(char) * 10);
	printf("Digite a Carta: ");
	scanf("%s", carta);
	Empilhar(ptrPilha, (void*)carta);
}

void RemoverCarta(Pilha* ptrPilha){
	if(_pilhaVazia(ptrPilha)){
		printf("Pilha Vazia\n");
		return;
	}

	char* carta = (char*) Desempilhar(ptrPilha);
	printf("Carta Desempilhada: %s", carta);
	free(carta);
}

void ExibirPilha(Pilha* ptrPilha){
	
	if(_pilhaVazia(ptrPilha))
		return;
	
	char* carta;

	printf("Cartas na pilha: ");
	Node* ptrNo = ptrPilha->topo;
	do{	
		carta = (char*) ptrNo->ptrDados;
		printf("%s , ",carta);
		ptrNo = ptrNo->proximoNo;
	} while (ptrNo != NULL);
	printf("\n");
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

void Consultar(Pilha* ptrPilha){
	if(_pilhaVazia(ptrPilha))
		return;
	
	char consulta[10];
	char* carta;

	printf("Carta para Consultar: ");
	scanf("%s", consulta);

	Node* ptrNo = ptrPilha->topo;
	do{	
		carta = (char*) ptrNo->ptrDados;
		if(!strcmp(carta, consulta)){
			printf("\nCarta esta na pilha\n");
			return;
		}
		ptrNo = ptrNo->proximoNo;
	} while (ptrNo != NULL);
	printf("\nCarta nao encontrada\n");
}

void Embaralhar(Pilha* ptrPilha){

	int tamPilha = _pilhaCont(ptrPilha);

	// Vetor de Ponteiros (void*) para armazenar os dados
	void** vetorDados = (void**) malloc(sizeof(void*) * tamPilha);	

	// Desempilhar tudo e preencher o vetor com dados
	for(int i = 0; i < tamPilha; i++){
		vetorDados[i] = Desempilhar(ptrPilha);
	}	

	//Empilha de forma aleatória
	// Obs.: Extremamente ineficiente
	// O tempo para embaralhar é muito alto
	printf("\nEmbaralhando, por favor aguarde...\n");
	for(int i = 0; i < tamPilha; i++){
		int controle = 1;
		int randNum;
		do{
			randNum = numAleatorio(tamPilha);
			//Verifica se a o dado na posição indicada já foi empilhado e 
			//se a posição é a mesma que o dado ocupava antes de desempilhar
			if((vetorDados[randNum] != NULL) && (randNum != (tamPilha - 1) - i)){
				Empilhar(ptrPilha, vetorDados[randNum]);
				vetorDados[randNum] = NULL;
				controle = 0;
			}
		} while(controle);
	}
}

// Retorna um numero entre 0 e o tamanhoPilha
int numAleatorio(int tamanhoPilha){
	//Gera numero aleatório
	srand(time(NULL));
	int numAl = rand();			
	return (numAl % tamanhoPilha);

}

int Menu(){
	int numero;
	printf("\n----------\n");
	printf("\n(O) Ouro, (C)Copas, (P)Paus, (E)Espadas\n");
	// Ex: 10 de Copas 10C, Ás de Ouro AO.
	printf("\n01. Inserir\n");
	printf("02. Remover\n");
	printf("03. Consultar Carta\n");
	printf("04. Embaralhar Pilha\n");
	printf("00. Sair\n");
	scanf("%i", &numero);
	return numero;
}