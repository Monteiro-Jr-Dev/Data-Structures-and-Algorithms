#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define tamanho_nome 25
#define tamanho_telefone 15
#define tamanho_maximo 100

struct tpessoa{
	char nome[tamanho_nome], telefone[tamanho_telefone];
	int idade;
};

typedef struct tpessoa Pessoa;

struct tagenda{
	Pessoa pessoa[tamanho_maximo];
	int total_pessoa;
};

typedef struct tagenda Agenda;

void inicializar(Agenda *minha_agenda){
	minha_agenda->pessoa[0].idade = -1;
	minha_agenda->total_pessoa = 0;
	return;
}

void inserir(Agenda *minha_agenda){
	system("cls");
	for(int i=0;i<tamanho_maximo;i++){
		if(minha_agenda->pessoa[i].idade == -1){
			system("cls");
			while(getchar() != '\n');
			printf("-------Inserir--------\n\nDigite o nome: ");
			fgets(minha_agenda->pessoa[i].nome, tamanho_nome, stdin);
			if(strncmp(minha_agenda->pessoa[i].nome, "fim", 3) == 0){
				printf("\n\nEncerrado...\n\n");
				return;
			}
			printf("Digite o numero do telefone: ");
			fgets(minha_agenda->pessoa[i].telefone, tamanho_telefone, stdin);
			printf("Digite a idade: ");
			scanf("%d", &minha_agenda->pessoa[i].idade);
			minha_agenda->total_pessoa = i+1;
			minha_agenda->pessoa[i+1].idade = -1;
		}
	}
	printf("\n\nA Agenda esta cheia!!!");
	return;
}

void exibir(Agenda *minha_agenda){
	system("cls");
	printf("--------Exibir---------\n\n");
	for(int i=0;i<minha_agenda->total_pessoa;i++){
		printf("Pessoa %d: %sTelefone: %sIdade: %d\n\n", i+1, minha_agenda->pessoa[i].nome, minha_agenda->pessoa[i].telefone, minha_agenda->pessoa[i].idade);
	}
	return;
}

void organizar(Agenda *minha_agenda){
	char aux_nome[tamanho_nome], aux_telefone[tamanho_telefone];
	int aux_idade;
	system("cls");
	for(int i=0;i<minha_agenda->total_pessoa;i++){
		for(int j=0;j<minha_agenda->total_pessoa-1;j++){
			if(strcmp(minha_agenda->pessoa[j].nome, minha_agenda->pessoa[j+1].nome) > 0){
				strcpy(aux_nome, minha_agenda->pessoa[j].nome);
				strcpy(aux_telefone, minha_agenda->pessoa[j].telefone);
				aux_idade = minha_agenda->pessoa[j].idade;
				strcpy(minha_agenda->pessoa[j].nome, minha_agenda->pessoa[j+1].nome);
				strcpy(minha_agenda->pessoa[j].telefone, minha_agenda->pessoa[j+1].telefone);
				minha_agenda->pessoa[j].idade = minha_agenda->pessoa[j+1].idade;
				strcpy(minha_agenda->pessoa[j+1].nome, aux_nome);
				strcpy(minha_agenda->pessoa[j+1].telefone, aux_telefone);
				minha_agenda->pessoa[j+1].idade = aux_idade;
			}
		}
	}
	return;
}

void pesquisar(Agenda *minha_agenda){
	int esq=0, dir=minha_agenda->total_pessoa-1, meio, achou = 0;
	char nome_pesquisado[tamanho_nome];
	while(getchar() != '\n');
	printf("--------Pesquisar----------\n\nDigite o nome desejado: ");
	fgets(nome_pesquisado, tamanho_nome, stdin);
	while(esq<=dir && !achou){
		meio = (esq+dir)/2;
		if(strcmp(minha_agenda->pessoa[meio].nome, nome_pesquisado) == 0){
			printf("\nPessoa %d\nNome: %sTelefone: %sIdade: %d\n", meio+1, minha_agenda->pessoa[meio].nome, minha_agenda->pessoa[meio].telefone, minha_agenda->pessoa[meio].idade);
			achou = 1;
		}
		if(strcmp(minha_agenda->pessoa[meio].nome, nome_pesquisado) < 0){
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
	char nome_pesquisado[tamanho_nome];
	system("cls");
	while(getchar() != '\n');
	printf("--------Alterar---------\n\nDigite o nome: ");
	fgets(nome_pesquisado, tamanho_nome, stdin);
	for(int i=0; i<minha_agenda->total_pessoa;i++){
		if(strcmp(minha_agenda->pessoa[i].nome, nome_pesquisado) == 0){
			printf("\nDigite o novo numero de telefone: ");
			fgets(minha_agenda->pessoa[i].telefone, tamanho_telefone, stdin);
			printf("Digite a nova idade: ");
			scanf("%d", &minha_agenda->pessoa[i].idade);
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
		printf("---------Agenda----------\n\n1. Inserir\n2. Alterar\n3. Organizar\n4. Pesquisar\n5. Exibir\n\nDigite a sua opcao: ");
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
