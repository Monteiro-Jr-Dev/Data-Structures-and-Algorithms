/*IFF Campos
* Estruturas de Dados Avançada
* Lista Base 
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
	int (*ComparaInserir)(void* parametro1, void* parametro2); // Função comparação para inserção	
	int (*ComparaBusca)(void* parametro1, void* parametro2); // Função de comparação para buscas

}Lista;

// Funções Básicas da Lista
Lista* CriarLista(int (*ComparaInserir)(void* parametro1, void* parametro2),
int (*ComparaBusca)(void* parametro1, void* parametro2));
void DestruirLista(Lista* lista);
int AdicionarNo(Lista* lista, void* ponteiroDados);
void* RemoverNo(Lista* lista, void* PDados);
void AtravessarLista(Lista* lista, void (*Funcao)(void* PtrDados));
void AdicionarNoOrdenado(Lista* lista, void* ponteiroDados);
int ListaVazia(Lista* lista);
int ContagemLista(Lista* lista);

int _procurarPosicaoNo(Lista* lista, void* dadoBuscar);			//Retorna posiçao do nó na lista
Node* _procurarNoAnterior(Lista* lista, int posicao);			//Retorna o ponteiro para o nó anterior ao selecionado
Node* _procurarUltimoNo(Lista* lista);
void _destruirNo(Node* no);



Lista* CriarLista(int (*ComparaInserir)(void* parametro1, void* parametro2), int (*ComparaBusca)(void* parametro1, void* parametro2)){
	Lista* lista = (Lista*) malloc(sizeof(Lista));
	lista->cont = 0;
	lista->primeiroNo = NULL;
	lista->ComparaInserir = ComparaInserir;
	lista->ComparaBusca = ComparaBusca;
	return lista;
}

void DestruirLista(Lista* lista){

	// Verifica se a lista está vazia
	if(!ListaVazia(lista)){
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
}

int AdicionarNo(Lista* lista, void* ponteiroDados){
	// Cria e inicializa do nó
	Node *novoNo = (Node*) malloc(sizeof(Node));
	Node* ultimoNo;
	novoNo->PontDados = ponteiroDados;
	novoNo->proximo = NULL;	

	if(ListaVazia(lista)){
		 lista->primeiroNo = novoNo;

	} else{
		ultimoNo = _procurarUltimoNo(lista);
		ultimoNo->proximo = novoNo;		
	}
	(lista->cont)++;
}

// Remove o nó e retorna o ponteiro do dado
void* RemoverNo(Lista* lista, void* PDados){
	Node *noAnterior, *no, *noPosterior;
	int posNo;
	void* dadoNo = NULL;
	// Encontrar a posição do nó usando a função de comparação
	posNo = _procurarPosicaoNo(lista, PDados);	

	// Se não encontrar o nó
	if(posNo == 0)
		return dadoNo; // dadoNo ainda é NULL

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
	dadoNo = no->PontDados;
	free(no);
	(lista->cont)--;

	return dadoNo; //retorna ponteiro dado	
}

void AdicionarNoOrdenado(Lista* lista, void* ponteiroDados){
	// Cria e inicializa do nó
	Node *novoNo = (Node*) malloc(sizeof(Node));
	novoNo->PontDados = ponteiroDados;
	novoNo->proximo = NULL;
	(lista->cont)++;
	
	int tamLista = ContagemLista(lista);
	Node* noAtual = lista->primeiroNo;
	Node* noAnterior = NULL;

	//Se a lista está vazia 
	if(ContagemLista(lista) == 1){
		 lista->primeiroNo = novoNo;	
	} else {	
	
		for(int i = 1; i < tamLista; i++){
			void* dadoComparar = (noAtual->PontDados);
			// Usa a função de comparação para determinar onde inserir o novo nó
			int retorno = (* lista->ComparaInserir)(ponteiroDados, dadoComparar);

			// Inserir nó se a condição de inserção for atendida 
			if(retorno == 1){
				// Se for primeiro nó, inserir no cabeçalho
				if(i == 1){ 
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
		// Inserir novoNo no final da se a condição de inserção não for atendida
		noAnterior->proximo = novoNo;
	}	
	
}

// Executa a função passada em todos os nós
void AtravessarLista(Lista* lista, void (*Funcao)(void* PtrDados)){
	int tamLista = ContagemLista(lista);
	Node* noAtual = lista->primeiroNo;
	for (int i = 0; i < tamLista; i++){
		// Executa a função em todos os nós
		(*Funcao)(noAtual->PontDados);
		noAtual = noAtual->proximo;
	}
}

int _procurarPosicaoNo(Lista* lista, void* dadoBuscar){	
	Node* noAtual = lista->primeiroNo;
	Node* noAnterior = NULL;
	int tamLista = ContagemLista(lista);

	if(tamLista > 0){
		for(int i = 1; i <= tamLista; i++){
			void* dadoComparar = (noAtual->PontDados);
			int retorno = (*lista->ComparaBusca)(dadoBuscar, dadoComparar);						
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
	int tamLista = ContagemLista(lista);
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


int ListaVazia(Lista* lista){
	if(ContagemLista(lista) == 0){
		return 1;
	} else{
		return 0;
	}
}

int ContagemLista(Lista* lista){
	return lista->cont;
}

