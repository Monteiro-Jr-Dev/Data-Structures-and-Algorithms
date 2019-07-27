
typedef struct node{
	void* ptrDados;
	struct node* proximoNo;
}Node;

typedef struct {
	int cont;
	Node* topo;
}Pilha;

Pilha* CriarPilha();
int Empilhar(Pilha* ptrPilha, void* ptrDados);
void* Desempilhar(Pilha* ptrPilha);
int _pilhaVazia(Pilha* ptrPilha);
int _pilhaCheia(Pilha* ptrPilha);
int _pilhaCont(Pilha* ptrPilha);


Pilha* CriarPilha(){

	Pilha* ptrPilha = (Pilha*) malloc(sizeof(Pilha));
	//Checar se a pilha foi criada
	if(ptrPilha){
		ptrPilha->cont = 0;
		ptrPilha->topo = NULL;
	}
	return ptrPilha;
}

int Empilhar(Pilha* ptrPilha, void* ptrDados){

	Node* ptrNo = (Node*) malloc(sizeof(Node));

	// Se não foi possível criar o nó, retorna falso
	if(!ptrNo){
		return 0;
	}

	//Atualizar Ponteiro e contador
	ptrNo->proximoNo = ptrPilha->topo;
	ptrPilha->topo = ptrNo;
	(ptrPilha->cont)++;

	ptrNo->ptrDados = ptrDados;
	return 1;

}

void* Desempilhar(Pilha* ptrPilha){
	void* ptrDados;
	Node* ptrNo;
	
	if(_pilhaVazia(ptrPilha)){
		return NULL;
	}

	// Atualiza ponteiros e Contador
	ptrNo = ptrPilha->topo;
	ptrPilha->topo = ptrPilha->topo->proximoNo;
	(ptrPilha->cont)--;

	//Pega os dados e destroi o nó
	ptrDados = ptrNo->ptrDados;
	free(ptrNo);

	return ptrDados;
}

//Funções Auxiliares
int _pilhaVazia(Pilha* ptrPilha){
	if(ptrPilha->cont == 0)
		return 1;
	else
		return 0;
	
}

int _pilhaCheia(Pilha* ptrPilha){
	Node* ptrNo = (Node*) malloc(sizeof(Node));
	if(!ptrNo)
		return 1;

	free(ptrNo);

	return 0;
}

int _pilhaCont(Pilha* ptrPilha){
	return (ptrPilha->cont);
}

