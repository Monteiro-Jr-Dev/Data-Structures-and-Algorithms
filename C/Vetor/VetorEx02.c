#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define tamanho_nome 25
#define tamanho_endereco 25
#define tamanho_maximo 1000

struct tpessoa{
	char nome[tamanho_nome], endereco[tamanho_endereco];
	int matricula;
};

typedef struct tpessoa Pessoa;

struct tagenda{
	Pessoa pessoa[tamanho_maximo];
	int total_pessoa;
};

typedef struct tagenda Agenda;

void inicializar(Agenda *minha_agenda){
	minha_agenda->pessoa[0].matricula = -1;
	minha_agenda->total_pessoa = 0;
	return;
}

void inserir(Agenda *minha_agenda){
	system("cls");
	for(int i=0;i<tamanho_maximo;i++){
		if(minha_agenda->pessoa[i].matricula == -1){
			system("cls");
			while(getchar() != '\n');
			printf("-------Inserir--------\n\nDigite o nome: ");
			fgets(minha_agenda->pessoa[i].nome, tamanho_nome, stdin);
			printf("Digite o endereco: ");
			fgets(minha_agenda->pessoa[i].endereco, tamanho_endereco, stdin);
			printf("Digite o numero de matricula: ");
			scanf("%d", &minha_agenda->pessoa[i].matricula);
			minha_agenda->total_pessoa = i+1;
			minha_agenda->pessoa[i+1].matricula = -1;
			return;
		}
	}
	printf("\n\nA Agenda esta cheia!!!");
	return;
}

void exibir(Agenda *minha_agenda){
	system("cls");
	printf("--------Exibir---------\n\n");
	for(int i=0;i<minha_agenda->total_pessoa;i++){
		printf("Pessoa: %sEndereco: %sMatricula: %d\n\n", minha_agenda->pessoa[i].nome, minha_agenda->pessoa[i].endereco, minha_agenda->pessoa[i].matricula);
	}
	return;
}

void organizar(Agenda *minha_agenda){
	char aux_nome[tamanho_nome], aux_endereco[tamanho_endereco];
	int aux_matricula;
	system("cls");
	for(int i=0;i<minha_agenda->total_pessoa;i++){
		for(int j=0;j<minha_agenda->total_pessoa-1;j++){
			if(minha_agenda->pessoa[j].matricula > minha_agenda->pessoa[j+1].matricula){
				strcpy(aux_nome, minha_agenda->pessoa[j].nome);
				strcpy(aux_endereco, minha_agenda->pessoa[j].endereco);
				aux_matricula = minha_agenda->pessoa[j].matricula;
				strcpy(minha_agenda->pessoa[j].nome, minha_agenda->pessoa[j+1].nome);
				strcpy(minha_agenda->pessoa[j].endereco, minha_agenda->pessoa[j+1].endereco);
				minha_agenda->pessoa[j].matricula = minha_agenda->pessoa[j+1].matricula;
				strcpy(minha_agenda->pessoa[j+1].nome, aux_nome);
				strcpy(minha_agenda->pessoa[j+1].endereco, aux_endereco);
				minha_agenda->pessoa[j+1].matricula = aux_matricula;
			}
		}
	}
	return;
}

void pesquisar(Agenda *minha_agenda){
	int esq=0, dir=minha_agenda->total_pessoa-1, meio, achou = 0;
	int matricula_pesquisada;
	while(getchar() != '\n');
	printf("--------Pesquisar----------\n\nDigite a matricula desejado: ");
	scanf("%d", &matricula_pesquisada);
	while(esq<=dir && !achou){
		meio = (esq+dir)/2;
		if(minha_agenda->pessoa[meio].matricula == matricula_pesquisada){
			printf("\nNome: %sEndereco: %s\n", minha_agenda->pessoa[meio].nome, minha_agenda->pessoa[meio].endereco);
			achou = 1;
		}
		if(minha_agenda->pessoa[meio].matricula < matricula_pesquisada){
			esq = meio + 1;
		}else{
			dir = meio - 1;
		}
	}
	if(achou == 0){
		printf("\nNao existe essa pessoa na Agenda!!!!!\n");
	}
	return;
}

void alterar(Agenda *minha_agenda){
	int matricula_desejada;
	system("cls");
	while(getchar() != '\n');
	printf("--------Alterar---------\n\nDigite o numero de matricula: ");
	scanf("%d", &matricula_desejada);
	for(int i=0; i<minha_agenda->total_pessoa;i++){
		if(minha_agenda->pessoa[i].matricula == matricula_desejada){
			while(getchar() != '\n');
			printf("\nDigite o novo endereco: ");
			fgets(minha_agenda->pessoa[i].endereco, tamanho_endereco, stdin);
			printf("\nModificacao feita!!!!!\n");
			return;
		}
	}
	printf("Nao existe essa pessoa na Agenda!!!!!!");
	return;
}

int main() {
	Agenda minha_agenda;
	int opcao, controle;
	inicializar(&minha_agenda);
	do{
		system("cls");
		printf("---------Matriculas de Alunos----------\n\n1. Inserir\n2. Alterar\n3. Organizar\n4. Pesquisar\n5. Exibir\n\nDigite a sua opcao: ");
		scanf("%d", &opcao);
		switch(opcao){
			case 1:
				inserir(&minha_agenda);
				break;
			case 2:
				alterar(&minha_agenda);
				break;
			case 3:
				organizar(&minha_agenda);
				printf("Ordenacao feita!!!!!\n\n");
				break;
			case 4:
				organizar(&minha_agenda);
				pesquisar(&minha_agenda);
				break;
			case 5:
				exibir(&minha_agenda);
				break;
			default:
				printf("Opcao invalida!");
				break;
		}
		printf("\nDigite 0 para continuar ou 1 para encerrar: ");
		scanf("%d", &controle);
	}while(controle == 0);
	return 0;
}
