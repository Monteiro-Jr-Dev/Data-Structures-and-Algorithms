/*IFF Campos
* Estruturas de Dados
* Lista Simples
* Valmir Monteiro & José Gustavo
*/

// Estrutura do Nó da Lista
typedef struct node{
	void* PontDados;
	struct node* proximo;
}Node;

// Estrutura do Cabeçalho da Lista
typedef struct lista{
	int cont;
	Node* primeiroNo;
	int (*comparar)(void* parametro1, void* parametro2);
	// Recebe uma função de comparaçao
	// Retorna 0 se parametros iguais
	// Retorna 1 se Parametro1 > Parametro2
	// Retorna -1 se Parametro1 < Parametro2
}Lista;

// Funções Básicas da Lista
Lista* CriarLista(int (*comparar)(void* parametro1, void* parametro2));
void DestruirLista(Lista* lista);
int AdicionarNo(Lista* lista, void* ponteiroDados);
int RemoverNo(Lista* lista, void* PDados);
void AtravessarLista(Lista* lista, void (*Funcao)(Node* no));
void AdicionarNoOrdenado(Lista* lista, void* ponteiroDados);

// Funções Internas (Deveriam ser static)
int _procurarPosicaoNo(Lista* lista, void* dadoBuscar);			//Retorna posiçao do nó na lista
Node* _procurarNoAnterior(Lista* lista, int posicao);			//Retorna o ponteiro para o nó anterior ao selecionado
Node* _procurarUltimoNo(Lista* lista);
void _destruirNo(Node* no);
int _listaVazia(Lista* lista);
int _contagemLista(Lista* lista);


Lista* CriarLista(int (*comparar)(void* parametro1, void* parametro2)){
	Lista* lista = (Lista*) malloc(sizeof(Lista));
	lista->cont = 0;
	lista->primeiroNo = NULL;
	lista->comparar = comparar;
	return lista;
}

void DestruirLista(Lista* lista){

	// Verifica se a lista está vazia
	if(!_listaVazia(lista)){
		Node *no, *proximoNo;
		no = lista->primeiroNo;

		// Libera todos os nós
		while(no != NULL){
			proximoNo = no->proximo;
			_destruirNo(no);
			no = proximoNo;
		}
	}
	// Libera a lista
	free(lista);
	printf("Lista Destruida\n");
}

int AdicionarNo(Lista* lista, void* ponteiroDados){
	// Cria e inicializa do nó
	Node *novoNo = (Node*) malloc(sizeof(Node));
	Node* ultimoNo;
	novoNo->PontDados = ponteiroDados;
	novoNo->proximo = NULL;	

	if(_contagemLista(lista) == 0){
		 lista->primeiroNo = novoNo;

	} else{
		ultimoNo = _procurarUltimoNo(lista);
		ultimoNo->proximo = novoNo;		
	}
	(lista->cont)++;
}

int RemoverNo(Lista* lista, void* PDados){
	Node *noAnterior, *no, *noPosterior;
	int posNo;
	// Encontrar a posição do nó usando a função de comparação
	posNo = _procurarPosicaoNo(lista, PDados);	

	// Se não encontrar o nó
	if(posNo == 0)
		return 0; // retorna false

	//Se o nó buscado for o primeiro, então o nó anterior é o cabeçalho
	if(posNo == 1){ 
		no = lista->primeiroNo;
		noPosterior = no->proximo;
		lista->primeiroNo = noPosterior;

	} else{
		noAnterior = _procurarNoAnterior(lista, posNo);
		no = noAnterior->proximo;
		noPosterior = no->proximo;
		noAnterior->proximo = noPosterior;
	}

	// Deletar o nó e atualizar o contador
	_destruirNo(no);
	(lista->cont)--;

	return 1; //retorna true	
}

void AdicionarNoOrdenado(Lista* lista, void* ponteiroDados){
	// Cria e inicializa do nó
	Node *novoNo = (Node*) malloc(sizeof(Node));
	novoNo->PontDados = ponteiroDados;
	novoNo->proximo = NULL;
	(lista->cont)++;

	int tamLista = _contagemLista(lista);
	Node* noAtual = lista->primeiroNo;
	Node* noAnterior = NULL;

	if(_contagemLista(lista) == 1){
		 lista->primeiroNo = novoNo;

	} else {		
		for(int i = 1; i < tamLista; i++){
			void* dadoComparar = (noAtual->PontDados);
			// Usa a função de comparação para determinar onde inserir o novo nó
			int retorno = (* lista->comparar)(ponteiroDados, dadoComparar);

			// Inserir dado se Parametro1 <= Parametro2
			if(retorno != 1){
				if(i == 1){ //Primeiro nó
					Node* temp = lista->primeiroNo;
					lista->primeiroNo = novoNo;
					novoNo->proximo = temp;

				} else {
					Node* temp = noAnterior->proximo;
					noAnterior->proximo = novoNo;
					novoNo->proximo = temp;
				}
				return;
			}
			noAnterior = noAtual;
			noAtual = noAtual->proximo;
		}
		noAnterior->proximo = novoNo;		
	}	
	
}

// Executa a função passada no parâmetro em todos os nós
void AtravessarLista(Lista* lista, void (*Funcao)(Node* no)){
	int tamLista = _contagemLista(lista);
	Node* noAtual = lista->primeiroNo;
	for (int i = 0; i < tamLista; i++){
		// Executa a função em todos os nós
		(*Funcao)(noAtual);
		noAtual = noAtual->proximo;
	}
}

int _procurarPosicaoNo(Lista* lista, void* dadoBuscar){	
	Node* noAtual = lista->primeiroNo;
	Node* noAnterior = NULL;
	int tamLista = _contagemLista(lista);

	if(tamLista > 0){
		for(int i = 1; i <= tamLista; i++){
			void* dadoComparar = (noAtual->PontDados);
			int retorno = (*lista->comparar)(dadoBuscar, dadoComparar);						
			if(retorno == 0){
				return i;
			}
			noAnterior = noAtual;
			noAtual = noAtual->proximo;
		}
	} 
	// Se não encontrar o nó procurado
	return 0;
}

Node* _procurarNoAnterior(Lista* lista, int posicao){
	Node* noAtual = lista->primeiroNo;
	Node* noAnterior = NULL;
	for (int i = 1; i < posicao; i++){
		noAnterior = noAtual;
		noAtual = noAtual->proximo;
	}	
	return noAnterior;
}

Node* _procurarUltimoNo(Lista* lista){
	int tamLista = _contagemLista(lista);
	Node* noAnterior = _procurarNoAnterior(lista, tamLista);
	if(noAnterior == NULL) //Se só tiver um nó na lista
		return (lista->primeiroNo); 
	else
		return (noAnterior->proximo);
}

void _destruirNo(Node* no){
	free(no->PontDados);
	free(no);
}


int _listaVazia(Lista* lista){
	if(_contagemLista(lista) == 0){
		return 1;
	} else{
		return 0;
	}
}

int _contagemLista(Lista* lista){
	return lista->cont;
}

