/*IFF Campos
* Estruturas de Dados
* Lista Simples
* Valmir Monteiro & José Gustavo
*/
#include <stdio.h>
#include <stdlib.h>
#include "FilaBase.h"

typedef struct _produto{
	int Codigo;
	char Nome[50];
	float Preco;
}Produto;

// Declaração das Funções
int FuncaoComparar(void* Parametro1, void* Parametro2);
int Menu();
void Cadastrar(Lista* lista);
void BuscaProduto(Lista* lista);
void AlterarProduto(Lista* lista);
int Pesquisar(Lista* lista);
void LerDados(Produto* prod);
void MostrarDados(Node* no);
void AlterarDados(Node* no);
void ExcluirProduto(Lista* lista);
void ExibirLista(Lista* lista);
void FaixaDePreco(Lista* lista);


int main(){
	int controle;
	Lista* lista = CriarLista(FuncaoComparar);

	// Cria um vetor de funções
	void (*FuncoesMenu[])(Lista*) = {Cadastrar, BuscaProduto, AlterarProduto, ExcluirProduto, ExibirLista, FaixaDePreco};

	// Chama o menu de opções
	while(controle = Menu()){
		if(controle >= 0 && controle < 7)
			(*FuncoesMenu[controle - 1])(lista);
	}

	DestruirLista(lista);
}

int FuncaoComparar(void* Parametro1, void* Parametro2){
	Produto* p1 = (Produto*)Parametro1;
	Produto* p2 = (Produto*)Parametro2;
	if(p1->Codigo == p2->Codigo){
		return 0;
		//printf("0\n");
	} else if (p1->Codigo > p2->Codigo){
		return 1;
		//printf("1\n");
	} else{
		return -1;
		//printf("-1\n");
	}
}

int Menu(){
	int opcao;
	printf("-------------------\n");
	printf("1. Cadastrar Produto\n");
	printf("2. Pesquisar Produto\n");
	printf("3. Alterar Produto\n");
	printf("4. Excluir Produto\n");
	printf("5. Exibir Lista\n");
	printf("6. Exibir Produtos em Faixa de Preço\n");
	printf("0. Sair\n");
	printf("Opcçao: ");
	scanf("%i", &opcao);
	printf("-------------------\n");
	return opcao;
}

void Cadastrar(Lista* lista){
	Produto* novoProduto = (Produto*) malloc(sizeof(Produto));
	printf("Codigo: ");
	scanf("%i", &(novoProduto->Codigo));
	printf("Nome: ");
	scanf("%s", novoProduto->Nome);
	printf("Preço: ");
	scanf("%f", &(novoProduto->Preco));
	AdicionarNo(lista, novoProduto);
}

void BuscaProduto(Lista* lista){
	int retorno = Pesquisar(lista);
	Node* noMostrar;
	if(retorno == 0){
		printf("-------------------\n");
		printf("Produto não encontrado\n");
		printf("-------------------\n");
		return;
	} else if(retorno == 1){
		noMostrar = lista->primeiroNo;
	}else{
		noMostrar = _procurarNoAnterior(lista, retorno)->proximo;		
	}
	MostrarDados(noMostrar);
}

void AlterarProduto(Lista* lista){
	int retorno = Pesquisar(lista);
	
	Node* noAlterar;
	if(retorno == 0){
		printf("-------------------\n");
		printf("Produto não encontrado\n");
		printf("-------------------\n");
		return;
	} else if(retorno == 1){//Primeiro no
		noAlterar = lista->primeiroNo;
	} else {
		noAlterar = _procurarNoAnterior(lista, retorno)->proximo;		
	}
	AlterarDados(noAlterar);
}

int Pesquisar(Lista* lista){
	Produto* busca = (Produto*) malloc(sizeof(Produto));
	printf("-------------------\n");
	printf("Codigo: ");
	scanf("%i", &(busca->Codigo));
	printf("-------------------\n");
	// Por algum motivo ta imprimindo os valores
	int retorno = _procurarPosicaoNo(lista, (void*)busca);	
	free(busca);
	return retorno;
}


void LerDados(Produto* prod){
	printf("-------------------\n");
	printf("Codigo: ");
	scanf("%i", &(prod->Codigo));
	printf("Nome: ");
	scanf("%s", prod->Nome);
	printf("Preço: ");
	scanf("%f", &(prod->Preco));
	printf("-------------------\n");
}

void MostrarDados(Node* no){	
	Produto* prodMostrar = (Produto*)no->PontDados;
	printf("-------------------\n");
	printf("Codigo: %i\n", prodMostrar->Codigo);
	printf("Nome: %s\n", prodMostrar->Nome);
	printf("Preço R$ %.2f\n", prodMostrar->Preco);
	printf("-------------------\n");
}

void AlterarDados(Node* no){
	Produto* prod = (Produto*)no->PontDados;
	LerDados(prod);	
}

void ExcluirProduto(Lista* lista){
	Produto* busca = (Produto*) malloc(sizeof(Produto));
	//int posicao = Pesquisar(lista);
	printf("Codigo: ");
	scanf("%i", &(busca->Codigo));	
	int retorno = RemoverNo(lista, (void*)busca);
	if(retorno == 0){
		printf("-------------------\n");
		printf("Produto nao encontrado\n");		
		printf("-------------------\n");
	} else{
		printf("-------------------\n");
		printf("Produto Excluido\n");
		printf("-------------------\n");
	}
}

void ExibirLista(Lista* lista){
	AtravessarLista(lista, MostrarDados);
}

void FaixaDePreco(Lista* lista){
	int tamLista = _contagemLista(lista);
	float pMax, pMin;
	printf("-------------------\n");
	printf("Preço Mínimo: \n");
	scanf("%f", &pMin);
	printf("Preço Maximo: \n");
	scanf("%f", &pMax);
	printf("-------------------\n");

	Node *noAtual = lista->primeiroNo;
	for(int i = 1; i <= tamLista; i++){
		float preco = ((Produto*)(noAtual->PontDados))->Preco;
		if(preco <= pMax && preco >= pMin){
			MostrarDados(noAtual);
		}
		noAtual= noAtual->proximo;
	}
}