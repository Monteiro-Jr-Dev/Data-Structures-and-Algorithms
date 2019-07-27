#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreBase.h"

typedef struct {
	char nome[20];
	int telefone;
	char email[30];
}Pessoa;

int FuncaoComparar(void* dado1, void* dado2);
void FuncaoProcessar(void* dados);
int Menu();
void Cadastrar(Arvore* ptrArvore);
void RemoverCadastro(Arvore* ptrArvore);
int BuscaCadastro(Arvore* ptrArvore);
int BuscarNo(Arvore* ptrArvore, Node* raiz, void* ptrDados);
int _buscar(Arvore* ptrArvore, void* dadosRaiz, void* ptrDados);

int main(){

	Arvore* ptrArvore = CriarArvore(FuncaoComparar);
	int opcao;
	while(opcao = Menu()){
		switch(opcao){
			case 1:
				Cadastrar(ptrArvore);
			break;

			case 2:
				RemoverCadastro(ptrArvore);				
			break;

			case 3:
				if(!BuscaCadastro(ptrArvore))
					printf("Nao Encontrado\n");
			break;

			case 4:
				PreOrdem(ptrArvore->raiz, FuncaoProcessar);
			break;
		}
	}
	return 0;
}

int Menu(){
	printf("\n----------\n");
	printf("1. Cadastrar\n");
	printf("2. Remover\n");
	printf("3. Buscar\n");
	printf("4. Pre Ordem\n");
	printf("0. Sair\n");

	int opcao;
	printf("\nOpcao: ");
	scanf("%i", &opcao);
	return opcao;
}

void Cadastrar(Arvore* ptrArvore){
	Pessoa* ptrPessoa = (Pessoa*) malloc(sizeof(Pessoa));
	printf("Nome: ");
	scanf("%s", ptrPessoa->nome);
	printf("Telefone: ");
	scanf("%i", &(ptrPessoa->telefone));
	printf("E-Mail: ");
	scanf("%s", ptrPessoa->email);

	InserirNo(ptrArvore, ptrArvore->raiz, (void*)ptrPessoa);
}

void RemoverCadastro(Arvore* ptrArvore){
	Pessoa* ptrPessoa = (Pessoa*) malloc(sizeof(Pessoa));
	printf("Nome: ");
	scanf("%s", ptrPessoa->nome);

	RemoverNo(ptrArvore, ptrArvore->raiz, (void*)ptrPessoa);
	free(ptrPessoa);
}

int BuscaCadastro(Arvore* ptrArvore){
	Pessoa* ptrPessoa = (Pessoa*) malloc(sizeof(Pessoa));
	printf("Nome: ");
	scanf("%s", ptrPessoa->nome);
	return BuscarNo(ptrArvore, ptrArvore->raiz, (void*)ptrPessoa);
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
	Pessoa* p1 = (Pessoa*) dado1;
	Pessoa* p2 = (Pessoa*) dado2;
	char nome1[20], nome2[20];
	strcpy(nome1, p1->nome);
	strcpy(nome2, p2->nome);

	return(strcmp(nome1, nome2));
}

void FuncaoProcessar(void* dados){
	Pessoa* p1 = (Pessoa*) dados;
	printf("----------\n");
	printf("Nome: %s\n",p1->nome);
	printf("Telefone: %i\n",p1->telefone);
	printf("E-mail: %s\n", p1->email);
}