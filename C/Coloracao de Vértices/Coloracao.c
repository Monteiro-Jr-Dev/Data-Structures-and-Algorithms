/*IFF Campos
* Estruturas de Dados Avançada
* Alunos: Valmir, Israel e José Gustavo
*/
#include <stdio.h>
#include <stdlib.h>
#include "ListaBase.h"

// Declaração de Funções
int ComparaInserir (void* parametro1, void* parametro2);
int ComparaBusca (void* parametro1, void* parametro2);
void PreencherLista(FILE* grafo, int vertices, Lista* listaCandidatos);
void ColorirVertices(Lista* listaCandidatos);
int Adjacente(Lista* listaCor, void* noComparar);
void ImprimirCor(void* PontDados);
void AtualizarListaCandidatos(Lista* listaCandidatos, Lista* listaCor);
int RemoverNoColorido(Lista* lista, void* PDados);
int _procurarPosicaoNoColorido(Lista* lista, void* dado);

int main(){

	// Declaração de variáveis
	FILE* grafo; 
	Lista* listaCandidatos = CriarLista(ComparaInserir, ComparaBusca);
	int qVertice, qAresta;
	char nomeGrafo[20];

	// Solicitar o arquivo ao usuário
	do{
		printf("Nome de um arquivo valido: ");
		scanf("%s", nomeGrafo);
		grafo = fopen(nomeGrafo,"r");
	} while(!grafo);

	// Ler |V| e |E| 
	fscanf(grafo, "%i %i", &qVertice, &qAresta);

	printf("Coloracao: \n");
	PreencherLista(grafo, qVertice, listaCandidatos);
	ColorirVertices(listaCandidatos);

	DestruirLista(listaCandidatos);
	fclose(grafo);
	return 0;
}

// Ordenar vértices de forma decrescente pelo grau
int ComparaInserir (void* parametro1, void* parametro2){
	int* vetor1 = (int*)parametro1;
	int* vetor2 = (int*)parametro2;

	if(vetor1[1] > vetor2[1]){
		return 1;
	} else if(vetor1[1] < vetor2[1]){
		return -1;
	} else {
		return 0;
	}
}

// Busca vértices com base no índice
int ComparaBusca (void* parametro1, void* parametro2){
	int* vetor1 = (int*)parametro1;
	int* vetor2 = (int*)parametro2;

	if(vetor1[0] > vetor2[0]){
		return 1;
	} else if(vetor1[0] < vetor2[0]){
		return -1;
	} else {
		return 0;
	}
}

void PreencherLista(FILE* grafo, int vertices, Lista* listaCandidatos){
	// Declaração
	int grauVertice, aresta;	

	for (int i = 0; i < vertices; i++){
		grauVertice = 0;

		//Cria vetores que formam a lista
		int* vetor = (int*) malloc(sizeof(int) * (vertices + 2));		

		for(int j = 0; j < vertices; j++){
			// Offset de 2, pois as duas primeiras posições do vetor são reservadas para armazenar o índice e grau
			fscanf(grafo, "%i", &vetor[j + 2]);
			if(vetor[j + 2] == 1){
				grauVertice++;
			}
		}

		// Posição 0 reservada para o índice do vértice (Identificação)
		vetor[0] = i; 

		// Posição 1 reservada para o grau do vértice (Ordenação)
		vetor[1] = grauVertice; 
		AdicionarNoOrdenado(listaCandidatos, (void*)vetor);
	}
}

void ColorirVertices(Lista* listaCandidatos){
	int qVertices;
	Node *noAtual;
	Lista* listaCor;

	// Verifica se a lista de candidatos tem elementos
	if(qVertices = ContagemLista(listaCandidatos)){
		listaCor = CriarLista(ComparaInserir, ComparaBusca);
		// Insere o primeiro vértice dos candidatos na lista da cor
		noAtual = listaCandidatos->primeiroNo; 
		AdicionarNo(listaCor, noAtual->PontDados);
		
		// Percorre a lista de candidatos procurando vértices não adjacentes 
		// aos vértices já inseridos na lista de cor
		for (int i = 1; i < qVertices; i++){
			 noAtual = noAtual->proximo;
			 if(!Adjacente(listaCor, noAtual->PontDados)){
			 	AdicionarNo(listaCor, noAtual->PontDados);			 	
			 }
		}
		// Imprime os vértices que tem a mesma cor
		printf("{ ");
		AtravessarLista(listaCor, ImprimirCor); 
		printf("}\n");

		// Remove vértices já coloridos da lista de candidatos
		AtualizarListaCandidatos(listaCandidatos, listaCor); 

		// Repete a coloração nos candidatos restantes
		ColorirVertices(listaCandidatos);
	}
}

// Verifica se um vértice é adjacente a algum vértice da lista
int Adjacente(Lista* listaCor, void* noComparar){
	int *vertice, *verticeComp, indiceComp;
	int tamLista = ContagemLista(listaCor);
	verticeComp = (int*)(noComparar);
	indiceComp = verticeComp[0];
	Node* noAtual = listaCor->primeiroNo;

	for (int i = 0; i < tamLista; i++){
		vertice = (int*)(noAtual->PontDados);
		// Se existe um vértice na lista que é adjacente 
		if(vertice[indiceComp + 2] == 1){
			return 1;
		}
		noAtual = noAtual->proximo;
	}
	return 0;
}

void ImprimirCor(void* PontDados){
	int* vertice = (int*)PontDados;
	printf("%i ", vertice[0] + 1); // +1 só para os vértices começarem em 1
}

// Remove vértices já coloridos da lista de candidatos
void AtualizarListaCandidatos(Lista* listaCandidatos, Lista* listaCor){
	int tamLista = ContagemLista(listaCor);
	Node* noAtual = listaCor->primeiroNo;

	for (int i = 0; i < tamLista; i++){
		// Como o ponteiro já está em outra lista, não há necessidade de armazenar o retorno
		RemoverNo(listaCandidatos, noAtual->PontDados);
		noAtual = noAtual->proximo;
	}
	DestruirLista(listaCor);
}
