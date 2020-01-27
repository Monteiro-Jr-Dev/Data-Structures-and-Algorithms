typedef struct node{
	void* ptrDados;
	struct node* proximoNo;
}Node;

typedef struct{
	int cont;
	Node* primeiroNo;
	Node* ultimoNo;
}Fila;

Fila* CriarFila();
void Enfileirar(Fila* ptrFila, void* ptrDados);
void* Desenfileirar(Fila* ptrFila);
int _filaVazia(Fila* ptrFila);
int _filaCheia(Fila* ptrFila);
int _filaCont(Fila* ptrFila);
//void DestruirFila(Fila* ptrFila);

Fila* CriarFila(){
	Fila* ptrFila = (Fila*) malloc(sizeof(Fila));
	
	// Inicializar Fila
	ptrFila->cont = 0;
	ptrFila->primeiroNo = NULL;
	ptrFila->ultimoNo = NULL;

	return ptrFila;
}

void Enfileirar(Fila* ptrFila, void* ptrDados){

	Node* ptrNo = (Node*) malloc(sizeof(Node*));
	ptrNo->ptrDados = ptrDados;
	
	if(_filaVazia(ptrFila)){
		ptrFila->primeiroNo = ptrNo;
		ptrFila->ultimoNo = ptrNo;
	} else {
		ptrNo->proximoNo = ptrFila->primeiroNo;
		ptrFila->primeiroNo = ptrNo;	
	}

	(ptrFila->cont)++;
}

void* Desenfileirar(Fila* ptrFila){
	Node* ptrNo;
	void* ptrDados;

	//Encontrar penúltimo nó
	if(!_filaVazia(ptrFila)){
		ptrNo = ptrFila->primeiroNo;

		// Pegar dados e atualizar ponteiros
		if(_filaCont(ptrFila) != 1){
			while(ptrNo->proximoNo != ptrFila->ultimoNo){
				ptrNo = ptrNo->proximoNo;
			}
			ptrDados = ptrFila->ultimoNo->ptrDados;	
			free(ptrFila->ultimoNo);
			ptrNo->proximoNo = NULL;
			ptrFila->ultimoNo = ptrNo;
			
		} else{
			ptrDados = ptrFila->ultimoNo->ptrDados;	
			ptrFila->ultimoNo = ptrFila->primeiroNo = NULL;
			free(ptrNo);
		}
	}

	
	(ptrFila->cont)--;
	return ptrDados;
}

int _filaVazia(Fila* ptrFila){
	if(_filaCont(ptrFila) == 0)
		return 1;
	else
		return 0;
}

int _filaCheia(Fila* ptrFila){
	Node* tempNo = (Node*) malloc(sizeof(Node));
	if(tempNo){
		return 0;
	} else{
		free(tempNo);
		return 1;
	}
}

int _filaCont(Fila* ptrFila){
	return (ptrFila->cont);
}


//void DestruirFila(Fila* ptrFila){
//	return;
//}