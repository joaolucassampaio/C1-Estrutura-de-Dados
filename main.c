#include <stdio.h>
#include <stdlib.h>
#include <time.h> //Inclus�o da biblioteca para acesso aos n�meros aleat�rios

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
	struct node *lista, *p; //Defini��o de ponteiros auxiliares para manipula��o dos n�s
	struct descriptor *d; //Defini��o de um ponteiro auxiliar para manipula��o do descritor
	int quantifyNode; //Defini��o de uma vari�vel inteira para armazenar a quantidade de n�s a serem inseridos na lista
	int count = 0; //Defini��o uma vari�vel inteira para contagem de itera��es
	
	//Aloca��o din�mica de mem�ria para o descritor d e inicializa��o dos seus campos
	d = malloc(sizeof(struct descriptor));
	//Campos size, first e last s�o inicializados em 0 e NULl indicando que a lista est� vazia
	d->size = 0;
	d->first = NULL;
	d->last = NULL;
	
	//Solicita ao usu�rio que insira a quantidade de n�s a serem adicionados na lista
	printf("Quantos nos voce deseja adicionar a lista? Digite um numero inteiro: ");
	scanf("%i", &quantifyNode);
	//Confirma��o da quantidade de nos escolhidas
	printf("\nAdicionando %d nos a lista: \n", quantifyNode);
		
	//Inicializa o gerador de n�meros aleat�rios
	srand(time(NULL));
	
	//Looping que continua at� que o n�mero desejado de n�s seja inserido na lista encadeada
	while(count < quantifyNode) {
		//Aloca��o de mem�ria para um novo n� p
		p = malloc(sizeof(struct node));
		//Atribui��o de um valor aleat�rio ao campo info
		p->info = rand()%100; //0 � 99
		//Inser��o � esquerda:
		p->next = lista;
		lista = p;
		
		//Ordena��o dos n�s da lista encadeada em ordem crescente, mantendo o descritor atualizado
		if(d->first == NULL || p->info <= d->first->info) { // Se a lista estiver vazia ou o valor for menor que o primeiro elemento
			p->next = d->first;
			d->first = p;
		} else {
			struct node *current = d->first;
			while(current->next != NULL && current->next->info < p->info) { //Encontra o ponto de inser��o na lista
				current = current->next;
			}
			p->next = current->next;
			current->next = p;
		}
		
		//Incremento do tamanho da lista e do contador, e impress�o do valor do n� adicionado
		d->size++;
		count++;
		printf("%i ", p->info);
	};
		
	//Exibi��o do total de n�s na lista antes da remo��o
	printf("\nTotal de nos: %d\n", d->size);
	
	//Encontra o �ltimo n� da lista
	struct node *lastNode = d->first;
	while (lastNode->next != NULL) {
	    lastNode = lastNode->next;
	}
	
	//Atribu� o �ltimo n� encontrado a d->last
	d->last = lastNode;
	
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
    printf("\nPrimeiro no: %d\n", d->first != NULL ? d->first->info : -1);
    printf("Ultimo no: %d\n", d->last != NULL ? d->last->info : -1);
    printf("Total de nos: %d\n", d->size);
	return 0;
}
