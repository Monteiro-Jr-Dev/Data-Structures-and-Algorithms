#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreBase.h"

typedef struct{
	char titulo[20];
	char autor[20];
	char editora[20];
}Livro;

int FuncaoComparar(void* dado1, void* dado2);
void FuncaoProcessar(void* dados);
int Menu();
void CadastrarLivro(Arvore* ptrArvore);
int BuscaLivro(Arvore* ptrArvore);
int BuscarNo(Arvore* ptrArvore, Node* raiz, void* ptrDados);
int _buscar(Arvore* ptrArvore, void* dadosRaiz, void* ptrDados);

int main(){

	Arvore* ptrArvore = CriarArvore(FuncaoComparar);
	int opcao, res;
	while(opcao = Menu()){
		switch(opcao){
			case 1:
				CadastrarLivro(ptrArvore);
			break;

			case 2:
				res = BuscaLivro(ptrArvore);
				printf("Existe %i cadastros do livro informado\n", res);
			break;

			case 3:
				PosOrdem(ptrArvore->raiz, FuncaoProcessar);
			break;
		}
	}
	return 0;
}

int Menu(){
	printf("\n----------\n");
	printf("1. Cadastrar\n");
	printf("2. Buscar\n");
	printf("3. Pos Ordem\n");
	printf("0. Sair\n");

	int opcao;
	printf("\nOpcao: ");
	scanf("%i", &opcao);
	return opcao;
}

void CadastrarLivro(Arvore* ptrArvore){
	Livro* ptrLivro = (Livro*) malloc(sizeof(Livro));
	printf("Titulo: ");
	scanf("%s", ptrLivro->titulo);
	printf("Autor: ");
	scanf("%s", ptrLivro->autor);
	printf("Editora: ");
	scanf("%s", ptrLivro->editora);

	InserirNo(ptrArvore, ptrArvore->raiz, (void*)ptrLivro);
}

int BuscaLivro(Arvore* ptrArvore){
	Livro* ptrLivro = (Livro*) malloc(sizeof(Livro));

	printf("Titulo: ");
	scanf("%s", ptrLivro->titulo);

	return BuscarNo(ptrArvore, ptrArvore->raiz, (void*)ptrLivro);
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
	if (ptrArvore->comparar(dadosRaiz, ptrDados) == 0)
		return 1;
	else
		return 0;
}

int FuncaoComparar(void* dado1, void* dado2){
	char titulo1[20], titulo2[20];
	Livro* l1 = (Livro*)(dado1);
	Livro* l2 = (Livro*)(dado2);

	strcpy(titulo1, l1->titulo);
	strcpy(titulo2, l2->titulo);

	return (strcmp(titulo1, titulo2));
}

void FuncaoProcessar(void* dados){
	char titulo[20], autor[20], editora[20];
	Livro* l1 = (Livro*)(dados);

	strcpy(titulo, (l1->titulo));
	strcpy(autor, (l1->autor));
	strcpy(editora, (l1->autor));

	printf("\n----------\n");
	printf("Titulo: %s\n", titulo);
	printf("Autor: %s\n", autor);
	printf("Editora: %s\n",editora);
}