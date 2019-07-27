/*IFF Campos
* Estruturas de Dados
* Lista Simples
* Valmir Monteiro & José Gustavo
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FilaBase.h"

typedef struct _contato{
	char Nome[50];
	char Endereco[100];
	int Telefone;
}Contato;

// Declaração das Funções
int FuncaoComparar(void* parametro1, void* parametro2);
int Menu();
void Cadastrar(Lista* lista);
int Pesquisar(Lista* lista);
void BuscaContato(Lista* lista);
void MostrarDados(Node* no);
void AlterarContato(Lista* lista);
void LerDados(Contato* contato);
void AlterarDados(Node* no);
void LerDadosAlt(Contato* contato);
void ExcluirContato(Lista* lista);
void ExibirLista(Lista* lista);




int main(){
	int controle;
	Lista* lista = CriarLista(FuncaoComparar);

	// Cria um vetor de funções
	void (*FuncoesMenu[])(Lista*) = {Cadastrar, BuscaContato, AlterarContato, ExcluirContato, ExibirLista};

	// Chama o menu de opções
	while(controle = Menu()){
		if(controle >= 0 && controle < 6)
			(*FuncoesMenu[controle - 1])(lista);
	}

	DestruirLista(lista);
}

int FuncaoComparar(void* parametro1, void* parametro2){
	Contato* c1 = (Contato*)parametro1;
	Contato* c2 = (Contato*)parametro2;
	int res = strcmp(c1->Nome, c2->Nome);
	if(res > 0)
		return 1;
	else if(res < 0)
		return -1;
	return 0;
}

int Menu(){
	int opcao;
	printf("-------------------\n");
	printf("1. Cadastrar Contato\n");
	printf("2. Pesquisar Contato\n");
	printf("3. Alterar Contato\n");
	printf("4. Excluir Contato\n");
	printf("5. Exibir Lista\n");
	printf("0. Sair\n");
	printf("Opcçao: ");
	scanf("%i", &opcao);
	printf("-------------------\n");
	return opcao;
}



void Cadastrar(Lista* lista){
	Contato* contato = (Contato*) malloc(sizeof(Contato));
	LerDados(contato);
	// Busca se já existe
	if(_procurarPosicaoNo(lista, contato)){
		printf("Contato já existe\n");
		free(contato);
		return;
	}
	AdicionarNo(lista, contato);
}

int Pesquisar(Lista* lista){
	Contato* contato = (Contato*) malloc(sizeof(Contato));
	printf("-------------------\n");
	printf("Nome: ");
	while (getchar() != '\n');
	fgets(contato->Nome, 50, stdin);
	//scanf("%s", contato->Nome);
	printf("-------------------\n");
	int retorno = _procurarPosicaoNo(lista, (void*)contato);	
	free(contato);
	return retorno;
}

void BuscaContato(Lista* lista){
	int retorno = Pesquisar(lista);
	Node* noMostrar;
	if(retorno == 0){
		printf("-------------------\n");
		printf("Contato não encontrado\n");
		printf("-------------------\n");
		return;
	} else if(retorno == 1){//Primeiro no
		noMostrar = lista->primeiroNo;
	}else{
		noMostrar = _procurarNoAnterior(lista, retorno)->proximo;		
	}
	MostrarDados(noMostrar);
}

void MostrarDados(Node* no){	
	Contato* contMostrar = (Contato*)no->PontDados;
	printf("-------------------\n");
	printf("Nome: %s\n", contMostrar->Nome);
	printf("Endereço: %s\n", contMostrar->Endereco);
	printf("Telefone %i\n", contMostrar->Telefone);
	printf("-------------------\n");
}

void AlterarContato(Lista* lista){
	int retorno = Pesquisar(lista);	
	Node* noAlterar;

	if(retorno == 0){
		printf("-------------------\n");
		printf("Contato não encontrado\n");
		printf("-------------------\n");
		return;
	} else if(retorno == 1){//Primeiro no
		noAlterar = lista->primeiroNo;
	} else {
		noAlterar = _procurarNoAnterior(lista, retorno)->proximo;		
	}
	AlterarDados(noAlterar);
}

void AlterarDados(Node* no){
	Contato* contato = (Contato*)no->PontDados;
	LerDadosAlt(contato);	
}

void LerDadosAlt(Contato* contato){
	printf("-------------------\n");	
	printf("Endereço: ");
	fgets(contato->Endereco, 100, stdin);
	//scanf("%s", contato->Endereco);
	printf("Telefone: ");
	scanf("%i", &(contato->Telefone));
	printf("-------------------\n");
}

void LerDados(Contato* contato){
	printf("-------------------\n");
	while (getchar() != '\n');
	printf("Nome: ");
	fgets(contato->Nome, 50, stdin);
	//scanf("%s", contato->Nome);
	printf("Endereço: ");
	fgets(contato->Endereco, 100, stdin);
	//scanf("%s", contato->Endereco);
	printf("Telefone: ");
	scanf("%i", &(contato->Telefone));
	printf("-------------------\n");
}

void ExcluirContato(Lista* lista){
	Contato* busca = (Contato*) malloc(sizeof(Contato));
	//int posicao = Pesquisar(lista);
	printf("Nome: ");
	while (getchar() != '\n');
	fgets(busca->Nome, 50, stdin);	
	int retorno = RemoverNo(lista, (void*)busca);
	if(retorno == 0){
		printf("-------------------\n");
		printf("Contato nao encontrado\n");		
		printf("-------------------\n");
	} else{
		printf("-------------------\n");
		printf("Contato Excluido\n");
		printf("-------------------\n");
	}
}

void ExibirLista(Lista* lista){
	AtravessarLista(lista, MostrarDados);
}

