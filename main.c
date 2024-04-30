#include <stdio.h>
#include <stdlib.h>
#include <time.h> //Defini��o da biblioteca para acesso aos n�meros aleat�rios

//Defini��o da estrutura b�sica de um n�
struct node {
	int info; //Campo do conte�do da c�lula
	struct node *next; //Campo do endere�o da c�lula seguinte
};

//Defini��o da estrutura b�sica de um descritor
//� uma estrutura cuja fun��o � fornecer informa��es sobre a lista encadeada
struct descriptor {
	int size; //Tamanho total da lista (N�mero total de n�s)
	struct node *first; //Ponteiro para o primeiro n� da lista
	struct node *last; //Ponteiro para o �ltimo n� da lista
};

int main(int argc, char *argv[]) {
	struct node *lista, *p, *q, *r; //Defini��o de ponteiros auxiliares para manipula��o dos n�s
	struct descriptor *d; //Defini��o de um ponteiro auxiliar para manipula��o do descritor
	int quantifyNode; //Defini��o de uma vari�vel inteira para armazenar a quantidade de n�s a serem inseridos na lista
	int count = 0; //Defini��o uma vari�vel inteira para contagem de itera��es
	
	//d recebe o endere�o da mem�ria onde uma nova inst�ncia da estrutura b�sica de um descritor est� sendo alocada dinamicamente
	d = malloc(sizeof(struct descriptor));
	//Campos size, first e last s�o inicializados indicando que a lista est� vazia
	d->size = 0;
	d->first = NULL;
	d->last = NULL;
	
	//Obtendo quantidade de n�s:
	printf("Quantos nos voce deseja adicionar a lista? Digite um numero inteiro: ");
	scanf("%i", &quantifyNode);
	printf("\nAdicionando %d nos a lista: \n", quantifyNode);
		
	//Inicializa o gerador de n�meros pseudoaleat�rios (RNG - Random Number Generator)
	srand(time(NULL));
	
	//Looping do-while que executa at� que o n�mero desejado de n�s seja inserido na lista encadeada
	do {
		//� criado um novo n� que recebe um valor aleat�rio e � colocado no in�cio da fila
		//p recebe o endere�o da mem�ria onde uma nova inst�ncia da estrutura b�sica de um n� est� sendo alocada dinamicamente
		p = malloc(sizeof(struct node));
		//Inser��o � esquerda:
		p->info = rand()%99; // N�mero aleat�rio de 0 � 98
		p->next = lista;
		lista = p;
		
		//Ordena��o dos n�s
		if(d->first == NULL || p->info <= d->first->info) { // Se a lista estiver vazia ou o valor for menor que o primeiro elemento
			p->next = d->first;
			d->first = p;
		} else {
			struct node *current = d->first;
			//Encontra o ponto de inser��o na lista
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
	
	//Calcular o valor m�dio dos n�s na lista
	temp = d->first;
    int soma = 0;
    while (temp != NULL) {
        soma += temp->info;
        temp = temp->next;
    }
    float media = (float)soma / d->size;
    printf("\nValor medio:\n");
	printf("%.2f\n", media);
	
	//Remover o primeiro n� com valor imediatamente superior ao valor m�dio
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
    //Imprimir a lista com descritor final
    temp = d->first;
    while (temp != NULL) {
        printf("%i ", temp->info);
        temp = temp->next;
    }
    printf("\n");
    
	return 0;
}
