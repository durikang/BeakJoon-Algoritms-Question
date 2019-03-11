#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996)

typedef struct stack{
	int data;
	struct stack*link;

}Stack;
////////////////////////////Stack///////////////////////////////////
void InitStack(Stack**top) {
	*top = NULL;
}

int IsEmpty(Stack*top) {
	if (top == NULL)return 1;
	else return 0;

}

void Push(Stack **top, int data) {
	Stack *tmp = *top;
	*top= (Stack*)malloc(sizeof(Stack));
	(*top)->data = data;
	(*top)->link = tmp;

}

Stack Pop(Stack **top) {
	Stack tmp = { NULL };
	if (*top != NULL) {
		tmp = **top;
		free(*top);
		*top = tmp.link;
	}
	return tmp;
}
//////////////////////////////stack/////////////////////////////////////////////////
//////////////////////////////Queue/////////////////////////////////////////////////
typedef struct queue {
	int data;
	struct queue*link;
}Queue;

void InitQueue(Queue **front, Queue **rear) {
	*front = NULL;
	*rear = NULL;
}

int IsEmptyQ(Queue *front, Queue *rear) {
	if (front == NULL && rear == NULL)return 1;
	else return 0;

}

int Enqueue(Queue **front,Queue **rear, int data) {
	Queue *tmp = (Queue*)malloc(sizeof(Queue));
	if (*front == NULL) {
		*front = tmp;
	}
	else {
		(*rear)->link = tmp;
	}
	*rear = tmp;
	(*rear)->data = data;
	(*rear)->link = NULL;
}
Queue Dequeue(Queue **front, Queue **rear) {
	Queue tmp = { NULL };
	if (*front == NULL)return tmp;
	tmp = **front;
	free(*front);
	*front = tmp.link;
	if (*front == NULL) {
		*rear = NULL;
	}
	return tmp;


}



typedef struct graph {
	int vertexCount;
	int *vertex;
	int *visited;
	int **matrix;

}Graph;

Graph *MakeGraph(int vertexCount) {
	Graph *g = (Graph*)malloc(sizeof(Graph));
	g->vertexCount = vertexCount;
	g->vertex = (int*)malloc(sizeof(int)*g->vertexCount);
	g->visited = (int*)malloc(sizeof(int)*g->vertexCount);
	g->matrix = (int**)malloc(sizeof(int*)*g->vertexCount);

	for (int i = 0; i < g->vertexCount; i++) {
		g->vertex[i] = 0;
		g->visited[i] = 0;
		g->matrix[i] = (int*)malloc(sizeof(int)*g->vertexCount);
		for (int j = 0; j < g->vertexCount; j++) {
			g->matrix[i][j] = 0;
		}

	}
	return g;
}

int Addvertex(Graph *g, int vertex) {
	Graph *tmp = g;
	int i;
	for (i = 0; i < g->vertexCount&&g->vertex[i] != vertex; i++) {
		if (g->vertex[i] == 0) {
			g->vertex[i] = i + 1;

		}
	}
	return -1;

}

int AddEdge(Graph *g, int startVertex, int endVertex) {
	int i, j;
	Addvertex(g, startVertex);
	Addvertex(g, endVertex);
	for (i = 0; i < g->vertexCount&&g->vertex[i] != startVertex; i++);
	for (j = 0; j < g->vertexCount&&g->vertex[j] != endVertex; j++);

	g->matrix[i][j] = 1;
	g->matrix[j][i] = 1;
	return 0;

}



void Display(Graph *g) {
	int i,j;
	printf("     ");
	for (i = 0; i < g->vertexCount; i++) {
		printf("%d    ",g->vertex[i]);
	}
	printf("\n");
	for (i = 0; i < g->vertexCount; i++) {
		printf("%d", g->vertex[i]);
		for (j = 0; j < g->vertexCount; j++) {
			printf("%5d", g->matrix[i][j]);
		}printf("\n");
	}


}
/* Àç±Í Ç¥Çö
void DFS(Graph *g, int vertex) {
	g->visited[vertex - 1] = 1;
	printf("%d ", vertex);
	for (int i = 0; i < g->vertexCount; i++) {
		if (g->matrix[vertex - 1][i] == 1 && g->visited[i] == 0) {
			DFS(g, i + 1);
		}

	}

}

*/

void DFS(Graph *g, int vertex) {
	int i;
	Stack *top;
	InitStack(&top);
	
	g->visited[vertex - 1] = 1;
	printf("%d ", vertex);
	
	do {
		for (i = 0; i < g->vertexCount; i++) {
			if (g->matrix[vertex - 1][i] == 1 && g->visited[i] == 0) {
				Push(&top, vertex);
				g->visited[i] = 1;
				printf("%d ", i + 1);
				vertex = i + 1;
				break;
			}
		}
		if (i == g->vertexCount)vertex = Pop(&top).data;
	} while (!IsEmpty(top));
	memset(g->visited, 0, sizeof(int)*g->vertexCount);
	
}



void BFS(Graph*g, int vertex) {

	Queue *front;
	Queue *rear;
	InitQueue(&front, &rear);

	int i;
	g->visited[vertex - 1] = 1;
	printf("%d ", vertex);
	Enqueue(&front, &rear, vertex);

	do {
		vertex = Dequeue(&front, &rear).data;
		for (i = 0; i < g->vertexCount; i++) {
			if (g->matrix[vertex-1][i] == 1 && g->visited[i] == 0) {
				g->visited[i] = 1;
				printf("%d ", i + 1);
				Enqueue(&front, &rear, i + 1);

			}

		}

	} while (!IsEmptyQ(front, rear));
	memset(g->visited, 0, sizeof(int)*g->vertexCount);
}




int main() {
	Graph *g;
	int v, e, s;
	int sv = 0, ev = 0;
	scanf("%d %d %d", &v, &e, &s);
	g = MakeGraph(v);
	Addvertex(g, v);
	for (int i = 0; i < e; i++) {
		scanf("%d %d", &sv, &ev);
		AddEdge(g, sv, ev);
	}
	DFS(g, s);
	printf("\n");
	BFS(g, s);

	return 0;

}