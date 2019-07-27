/*IFF Campos
* Estruturas de Dados
* Lista Simples
* Valmir Monteiro & José Gustavo
*/
#include <stdio.h>
#include <stdlib.h>
#include "FilaBase.h"

typedef struct _aluno{
	int Idade;
}Aluno;

// Declaração das Funções
int FuncaoComparar(void* Parametro1, void* Parametro2);
int LerIdade();
int ArmazenarIdade(Lista* lista);
void MostrarLista(Lista* lista);
void _mostrarIdade(Node* no);
void AlunosMenores(Lista* lista);
void AlunosMaiores(Lista* lista);
void _maior18(Node* no);
void RemoverMaioresDe30(Lista* lista);
void AlunoMaisNovo(Lista* lista);



int main(){
	Lista* lista = CriarLista(FuncaoComparar);	
	// Loop ler idades
	while(ArmazenarIdade(lista) != 999);
	MostrarLista(lista);
	AlunosMenores(lista);
	AlunosMaiores(lista);
	RemoverMaioresDe30(lista);
	MostrarLista(lista);
	AlunoMaisNovo(lista);
	DestruirLista(lista);
}

int FuncaoComparar(void* Parametro1, void* Parametro2){
	Aluno* Aluno1 = (Aluno*)Parametro1;
	Aluno* Aluno2 = (Aluno*)Parametro2;	
	if(Aluno1->Idade == Aluno2->Idade){
		return 0;
	} else if(Aluno1->Idade > Aluno2->Idade){
		return 1;
	} else{
		return -1;
	}
}

int LerIdade(){
	int idade;
	printf("Insira a Idade do aluno: ");
	scanf("%i", &idade);
	return idade;
}

int ArmazenarIdade(Lista* lista){
	Aluno* a1 = (Aluno*)malloc(sizeof(Aluno));
	int idade;
	
	if((idade = LerIdade()) != 999){
		a1->Idade = idade;
		AdicionarNoOrdenado(lista, (void*)a1);
	} else{
		free(a1);		
	} 
	return idade;
}

void MostrarLista(Lista* lista){
	printf("----------Lista Completa----------\n");
	AtravessarLista(lista, _mostrarIdade);
	printf("\n--------------------\n");
}

void _mostrarIdade(Node* no){	
	Aluno* a1 = (Aluno*)(no->PontDados);
	printf("%i, ", a1->Idade);
}

void AlunosMenores(Lista* lista){
	int tamLista = _contagemLista(lista);
	int cont = 0;
	Node* noAtual = lista->primeiroNo;

	for(int i = 0; i < tamLista; i++){
		Aluno* a1 = (Aluno*)noAtual->PontDados;
		if(a1->Idade < 18){
			cont++;
		}
		noAtual = noAtual->proximo;
	}
	printf("--------------------\n");
	printf("Quantidade de alunos Menor de 18: %i\n", cont);
	printf("--------------------\n");	
}

void AlunosMaiores(Lista* lista){
	printf("----------Maiores de 18----------\n");
	AtravessarLista(lista, _maior18);
	printf("\n--------------------\n");	
}

void _maior18(Node* no){
	Aluno* a1 = (Aluno*)(no->PontDados);
	if(a1->Idade >= 18){
		printf("%i, ", a1->Idade);
	}
}

void RemoverMaioresDe30(Lista* lista){
	int tamLista = _contagemLista(lista);
	int cont = 0;
	Node* noAtual = lista->primeiroNo;

	for(int i = 0; i < tamLista; i++){
		Aluno* a1 = (Aluno*)noAtual->PontDados;
		if(a1->Idade > 30){
			RemoverNo(lista, (void*)a1);
		}
		noAtual = noAtual->proximo;
	}
	printf("Maiores de 30 Removidos\n");
}

void AlunoMaisNovo(Lista* lista){
	int tamLista = _contagemLista(lista);
	int menorIdade;
	Node* noAtual = lista->primeiroNo;
	for(int i = 0; i < tamLista; i++){		
		Aluno* a1 = (Aluno*)(noAtual->PontDados);
		if(i == 0){
			menorIdade = a1->Idade;
		}
		if(a1->Idade < menorIdade){
			menorIdade = a1->Idade;
		}		
		noAtual = noAtual->proximo;
	}
	printf("--------------------\n");
	printf("Idade do aluno mais novo: %i\n", menorIdade);
	printf("--------------------\n");
}