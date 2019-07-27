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
void CadastrarDir(Arvore* ptrArvore);
void RemoverDir(Arvore* ptrArvore);
int BuscarDir(Arvore* ptrArvore);
int BuscarNo(Arvore* ptrArvore, Node* raiz, void* ptrDados);
int _buscar(Arvore* ptrArvore, void* dadosRaiz, void* ptrDados);
int FuncaoComparar(void* dado1, void* dado2);
void FuncaoProcessar(void* dados);

int main(){

	Arvore* ptrArvore = CriarArvore(FuncaoComparar);
	int opcao;
	while(opcao = Menu()){
		switch(opcao){
			case 1:
				CadastrarDir(ptrArvore);
			break;

			case 2:
				RemoverDir(ptrArvore);				
			break;

			case 3:
				if(!BuscarDir(ptrArvore))
				printf("Nao Encontrado\n");				
			break;

			case 4:
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
	printf("3. Consultar\n");
	printf("4. Em Ordem\n");
	printf("0. Sair\n");

	int opcao;
	printf("\nOpcao: ");
	scanf("%i", &opcao);
	return opcao;
}

void CadastrarDir(Arvore* ptrArvore){
	Diretorio* ptrDir = (Diretorio*) malloc(sizeof(Diretorio));
	printf("Nome: ");
	scanf("%s", ptrDir->nome);
	printf("Dia: ");
	scanf("%i", &(ptrDir->dia));
	printf("Mes: ");
	scanf("%i", &(ptrDir->mes));
	printf("Ano: ");
	scanf("%i", &(ptrDir->ano));
	printf("Tamanho: ");
	scanf("%f", &(ptrDir->tamanho));

	InserirNo(ptrArvore, ptrArvore->raiz, (void*)ptrDir);
}

void RemoverDir(Arvore* ptrArvore){
	Diretorio* ptrDir = (Diretorio*) malloc(sizeof(Diretorio));
	printf("Nome: ");
	scanf("%s", ptrDir->nome);

	RemoverNo(ptrArvore, ptrArvore->raiz, (void*)ptrDir);
	free(ptrDir);
}

int BuscarDir(Arvore* ptrArvore){
	Diretorio* ptrDir = (Diretorio*) malloc(sizeof(Diretorio));
	printf("Nome: ");
	scanf("%s", ptrDir->nome);
	return BuscarNo(ptrArvore, ptrArvore->raiz, (void*)ptrDir);
}

int BuscarNo(Arvore* ptrArvore, Node* raiz, void* ptrDados){
int res = 0;
	if(raiz != NULL){
		res += BuscarNo(ptrArvore, raiz->noEsquerda, ptrDados);
		res += BuscarNo(ptrArvore, raiz->noDireita, ptrDados);
		return (res += _buscar(ptrArvore ,raiz->ptrDados, ptrDados));		
	}
	return 0;
}

int _buscar(Arvore* ptrArvore, void* dadosRaiz, void* ptrDados){
	if (ptrArvore->comparar(dadosRaiz, ptrDados) == 0){
		FuncaoProcessar(dadosRaiz);
		return 1;
	}
	else
		return 0;
}

int FuncaoComparar(void* dado1, void* dado2){
	Diretorio* d1 = (Diretorio*) dado1;
	Diretorio* d2 = (Diretorio*) dado2;
	char nome1[20], nome2[20];
	strcpy(nome1, d1->nome);
	strcpy(nome2, d2->nome);

	return(strcmp(nome1, nome2));
}

void FuncaoProcessar(void* dados){
	Diretorio* d1 = (Diretorio*) dados;
	printf("----------\n");
	printf("Nome: %s\n",d1->nome);
	printf("Data de Criacao: %i/%i/%i\n",d1->dia, d1->mes, d1->ano);
	printf("Tamanho: %.2f bytes\n", d1->tamanho);
}