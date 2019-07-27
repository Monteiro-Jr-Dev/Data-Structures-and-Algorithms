#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreBase.h"

typedef struct{
	char nome[20];
	int dia;
	int mes;
	int ano;
	float tamanho;
}Diretorio;


int FuncaoComparar(void* dado1, void* dado2);
void FuncaoProcessar(void* dados);
int Menu();
void CadastrarNum(Arvore* ptrArvore);
void RemoverNum(Arvore* ptrArvore);
int FuncaoComparar(void* dado1, void* dado2);
void FuncaoProcessar(void* dados);

int main(){

	Arvore* ptrArvore = CriarArvore(FuncaoComparar);
	int opcao;
	while(opcao = Menu()){
		switch(opcao){
			case 1:
				CadastrarNum(ptrArvore);
			break;

			case 2:
				RemoverNum(ptrArvore);				
			break;

			case 3:
			printf("Pre Ordem:\n");
				PreOrdem(ptrArvore->raiz, FuncaoProcessar);			
			break;

			case 4:
			printf("Pos Ordem:\n");
				PosOrdem(ptrArvore->raiz, FuncaoProcessar);
			break;

			case 5:
				printf("Em Ordem:\n");
				EmOrdem(ptrArvore->raiz, FuncaoProcessar);
			break;
		}
	}
	return 0;
}

int Menu(){
	printf("\n----------\n");
	printf("1. Inserir\n");
	printf("2. Remover\n");
	printf("3. Pre Ordem\n");
	printf("4. Pos Ordem\n");
	printf("5. Em Ordem\n");
	printf("0. Sair\n");

	int opcao;
	printf("\nOpcao: ");
	scanf("%i", &opcao);
	return opcao;
}

void CadastrarNum(Arvore* ptrArvore){
	int* num = (int*) malloc(sizeof(int));
	printf("Numero: ");
	scanf("%i", num);
	InserirNo(ptrArvore, ptrArvore->raiz, (void*) num);
}

void RemoverNum(Arvore* ptrArvore){
	int* num = (int*) malloc(sizeof(int));
	printf("Numero: ");
	scanf("%i", num);
	RemoverNo(ptrArvore, ptrArvore->raiz, (void*)num);	
	free(num);
}

int FuncaoComparar(void* dado1, void* dado2){

	int num1 = *((int*) dado1);
	int num2 = *((int*) dado2);

	if(num1 > num2){
		return 1;
	}else if(num1 < num2){
		return -1;
	} else{
		return 0;
	}
}

void FuncaoProcessar(void* dados){
	int num;
	num = *((int*) dados);
	//num = (int*) dados;
	printf("%i\n", num);
}