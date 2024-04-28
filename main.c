#include <stdio.h>
#include <stdlib.h>
#include <time.h> //Biblioteca para

//Definição da estrutura básica de um nó
struct node {
	int info; //Campo do conteúdo da célula
	struct node *next; //Campo do endereço da célula seguinte
};

//Definição da estrutura básica de um descritor
//É uma estrutura cuja função é fornecer informações sobre a lista encadeada
struct descriptor {
	int size; //Tamanho total da lista (Número total de nós)
	struct node *first; //Ponteiro para o primeiro nó da lista
	struct node *last; //Ponteiro para o último nó da lista
};

int main(int argc, char *argv[]) {
	struct node *lista, *p, *q, *r; //Definição de ponteiros auxiliares para manipulação dos nós
	struct descriptor *d; //Definição de um ponteiro auxiliares para manipulação do descritor
	int quantifyNode; //Definição de uma variável inteira para armazenar a quantidade de nós a serem inseridos na lista
	int count = 0; //Definição uma variável inteira para contagem de iterações
	
	//d recebe o endereço da memória 
	d = malloc(sizeof(struct descriptor));
	//Campos size, first e last são inicializados indicando que a lista está vazia
	d->size = 0;
	d->first = NULL;
	d->last = NULL;
	
	//Obtendo quantidade de nós:
	printf("Quantos nos voce deseja adicionar a lista? Digite um numero inteiro: ");
	scanf("%i", &quantifyNode);
	printf("\nAdicionando %d nos a lista: \n", quantifyNode);
		
	//Inicializa o gerador de números pseudoaleatórios (RNG - Random Number Generator)
	srand(time(NULL));
	
	//Looping do-while que executa até que o número desejado de nós seja inserido na lista encadeada
	do {
		// É criado um novo nó que recebe um valor aleatório e é colocado no início da fila
		//p recebe o endereço da memória onde uma nova instância da estrutura básica de um nó está sendo alocada dinamicamente
		p = malloc(sizeof(struct node));
		//Inserção no início com novos nós:
		p->info = rand()%99; // Número aleatório de 0 à 98
		p->next = lista;
		lista = p;
		//Aqui a lista já recebe um novo nó
		//Demonstrar como funciona a inserção à esquerda
		
		//Ordenação dos nós
		// Se a lista estiver vazia ou o valor for menor que o primeiro elemento
		// Pq d->first é igual a null sendo que a lista já tem um novo nó?
		//Fazer o d->first apontar =
		if(d->first == NULL || p->info <= d->first->info) {
			//Inserção à esquerda
			p->next = d->first;
			d->first = p;
		} else {
			struct node *current = d->first;
			// Encontra o ponto de inserção na lista
			//Inserção à direita
			while(current->next != NULL && current->next->info < p->info) {
				current = current->next;
			}
			p->next = current->next;
			current->next = p;
		}
	
		d->size++;
		count++;
		printf("%i ", p->info);
	} while(count < quantifyNode);	
	
	printf("\n");
	printf("\nLista ordenada:\n");
	//Imprimir a lista ordenada
	struct node *temp = d->first;
	while(temp != NULL) {
		printf("%i ", temp->info);
		temp = temp->next;
	}	
	printf("\n");
	
	// Calcular o valor médio dos nós na lista
	temp = d->first;
    int soma = 0;
    while (temp != NULL) {
        soma += temp->info;
        temp = temp->next;
    }
    float media = (float)soma / d->size;
    printf("\nValor medio:\n");
	printf("%.2f\n", media);
	
	// Remover o primeiro nó com valor imediatamente superior ao valor médio
    struct node *anterior = NULL;
    struct node *atual = d->first;
    while (atual != NULL && atual->info <= media) {
        anterior = atual;
        atual = atual->next;
    }
    if (atual != NULL) {
        if (anterior == NULL) {
            d->first = atual->next;
        } else {
            anterior->next = atual->next;
        }
        free(atual);
        d->size--;
    }
    
    printf("\nLista com descritor final:\n");
    // Imprimir a lista com descritor final
    temp = d->first;
    while (temp != NULL) {
        printf("%i ", temp->info);
        temp = temp->next;
    }
    printf("\n");
    
	return 0;
}
