typedef struct node{
	void* 			ptrDados;
	struct node* 	noEsquerda;
	struct node* 	noDireita;
}Node;

typedef struct {
	int 	cont;
	// a == b returns 0
	// a < b returns -1
	// a > b returns +1
	int  	(*comparar) (void* argu1, void* argu2);
	Node*	raiz;
}Arvore;

Node* InserirNo(Arvore* ptrArvore, Node* raiz, void* ptrDados);
void RemoverNo(Arvore* ptrArvore, Node* raiz, void* ptrDados);
Node* _remover(Arvore* ptrArvore, Node* raiz, void* ptrDados);
Node* CriarNo(void* ptrDados);
Arvore* CriarArvore(int (*comparar) (void* argu1, void* argu2));
void PreOrdem(Node* ptrArvore, void (*processar) (void* dados));
void EmOrdem(Node* ptrArvore, void (*processar) (void* dados));
void PosOrdem(Node* ptrArvore, void (*processar) (void* dados));
void _destruirNo(Node* ptrNo);
void _desconectarNo(Node* ptrArvore, Node* noDesconectar);
Node* _encontrarMaior(Node* raiz);

Node* InserirNo(Arvore* ptrArvore, Node* raiz, void* ptrDados){


	// Se a arvore está vazia
	if(ptrArvore->cont == 0){
		ptrArvore->raiz = CriarNo(ptrDados);		
		(ptrArvore->cont)++;
		return raiz;
	}

	// Se encontrou nó certo 
	if(raiz == NULL){
		raiz = CriarNo(ptrDados);
		(ptrArvore->cont)++;
		return raiz;
	}

	// guarda os dados da raiz
	void* dadosRaiz = raiz->ptrDados;

	int resultado = ptrArvore->comparar(ptrDados, dadosRaiz);	
	// Se o dado a ser inserido é menor que o que está na raiz
	if(resultado < 0){
		
		raiz->noEsquerda = (InserirNo(ptrArvore, raiz->noEsquerda, ptrDados));
		
	} else { 		
		raiz->noDireita = (InserirNo(ptrArvore, raiz->noDireita, ptrDados));
		
	}
}

Node* CriarNo(void* ptrDados){

	Node* ptrNo = (Node*) malloc(sizeof(Node));

	ptrNo->noEsquerda = NULL;
	ptrNo->noDireita = NULL;
	ptrNo->ptrDados = ptrDados;

	return ptrNo;
}

Arvore* CriarArvore(int (*comparar) (void* argu1, void* argu2)){

	Arvore* ptrArvore = (Arvore*) malloc(sizeof(Arvore));

	ptrArvore->cont = 0;
	ptrArvore->raiz = NULL;
	ptrArvore->comparar = comparar;

	return ptrArvore;
}

void EmOrdem(Node* raiz, void (*processar) (void* dados)){
	if(raiz != NULL){
		EmOrdem(raiz->noEsquerda, processar);
		processar(raiz->ptrDados);
		EmOrdem(raiz->noDireita,processar);
	}
}

void PreOrdem(Node* raiz, void (*processar) (void* dados)){
	if(raiz != NULL){
		processar(raiz->ptrDados);
		PreOrdem(raiz->noEsquerda, processar);
		PreOrdem(raiz->noDireita,processar);
	}
}

void PosOrdem(Node* raiz, void (*processar) (void* dados)){
	if(raiz != NULL){
		PosOrdem(raiz->noEsquerda, processar);
		PosOrdem(raiz->noDireita, processar);
		processar(raiz->ptrDados);
		
	}
}

void RemoverNo(Arvore* ptrArvore, Node* raiz, void* ptrDados){

	Node* tempNo = _remover(ptrArvore, ptrArvore->raiz, ptrDados);
	if(tempNo != NULL) {
		ptrArvore->raiz = tempNo;
	}

	if(ptrArvore->cont == 0)
		ptrArvore->raiz = NULL;

}

Node* _remover(Arvore* ptrArvore, Node* raiz, void* ptrDados){
	
	// Se nó não existe, retorna falso
	if(raiz == NULL)
		return raiz;

	void* dadosRaiz = raiz->ptrDados;
	Node* tempNo;

	// Procura qual caminho seguir na árvore
	if(ptrArvore->comparar(ptrDados, dadosRaiz) < 0){
		raiz->noEsquerda = _remover(ptrArvore, raiz->noEsquerda, ptrDados);
	} else 
	if(ptrArvore->comparar(ptrDados, dadosRaiz) > 0){
		raiz->noDireita = _remover(ptrArvore, raiz->noDireita, ptrDados);
	// Nó encontrado
	} else {

		if(raiz->noDireita == NULL && raiz->noEsquerda == NULL){
			_destruirNo(raiz);
			(ptrArvore->cont)--;
			raiz = NULL;
			return raiz;
		}
		
		// Raiz apenas com filho na esquerda
		if(raiz->noDireita == NULL && raiz->noEsquerda != NULL){
			tempNo = raiz->noEsquerda;
			_destruirNo(raiz);
			raiz = tempNo;
			(ptrArvore->cont)--;
			return raiz;

		// Raiz apenas com filho na direita
		} else if(raiz->noDireita != NULL && raiz->noEsquerda == NULL){
			tempNo = raiz->noDireita;
			_destruirNo(raiz);
			raiz = tempNo;
			(ptrArvore->cont)--;		
			return raiz;	

		// Raiz com dois filhos
		} else {
			tempNo = _encontrarMaior(raiz->noEsquerda);
			// Se o nó a esquerda tiver filhos para a direita
			if(raiz->noEsquerda != tempNo){
				_desconectarNo(raiz->noEsquerda, tempNo);
				tempNo->noEsquerda = raiz->noEsquerda;
				tempNo->noDireita = raiz->noDireita;
			} else {
				tempNo->noEsquerda = NULL;
				tempNo->noDireita = raiz->noDireita;
			}
						
			_destruirNo(raiz);
			raiz = tempNo;
			(ptrArvore->cont)--;
			return raiz;
		}
	}

}

void _destruirNo(Node* ptrNo){
	free(ptrNo->ptrDados);
	free(ptrNo);
	return;
}

void _desconectarNo(Node* raiz, Node* noDesconectar){

	if(raiz->noDireita == noDesconectar){
		raiz->noDireita = NULL;
		return;
	} else{
		_desconectarNo(raiz->noDireita, noDesconectar);
	}
}

Node* _encontrarMaior(Node* raiz){
	if(raiz->noDireita == NULL){
		return raiz;
	} else{
		return _encontrarMaior(raiz->noDireita);
	}
}

