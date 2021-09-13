#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N 100000

typedef enum {true, false} bool;

struct heap_node{
    unsigned int distance;
    int index;
};

struct node{
    int value;
    bool isProcessed;
};

int d, k, heap_size, numOfGraphs = 0;
int **matrix;
unsigned int result;

//PROJECT FUNCTIONS
void AggiungiGrafo(struct heap_node** heap);
void TopK(struct heap_node** heap);
void getMatrix();
int findMinDistance(struct node* array);
unsigned int dijkstra();
bool hasPath(int weight, int x, int y);

//DATA STRUCTURE FUNCTIONS
void build_max_heap(struct heap_node **a);
void max_heapify(struct heap_node **a, int n);
void heap_insert(struct heap_node** heap, unsigned int el);
void heap_delete_max(struct heap_node** heap);
int left(int i);
int right(int i);
int parent(int i);
void swap(struct heap_node **x, struct heap_node **y);

int main(){
    char* str = (char*)malloc(N);
    str = fgets(str, N, stdin);
    sscanf(str, "%d %d", &d, &k);

    struct heap_node *max_heap[k+1];
    heap_size = k;

    for(int i = 1; i < k + 1; i++){
        max_heap[i] = malloc(sizeof(struct heap_node));
    }

    matrix = (int **)malloc(d * sizeof(int *));
    for (int i = 0; i < d; i++){
        matrix[i] = (int *)malloc(d * sizeof(int));
    }

    while (fgets(str, N, stdin) != NULL) {
        if (str[0] == 'A') {
            AggiungiGrafo(max_heap);
        } else if (str[0] == 'T') {
            TopK(max_heap);
        }
    }
    return 0;
}

void AggiungiGrafo(struct heap_node** heap){
    getMatrix();
    result = dijkstra(matrix);
    numOfGraphs++;

    if(numOfGraphs <= k){
        heap[numOfGraphs]->distance = result;
        heap[numOfGraphs]->index = numOfGraphs - 1;
        if(numOfGraphs == k) {
            build_max_heap(heap);
        }
    }
    else if(numOfGraphs > k && result < heap[1]->distance){
        heap_delete_max(heap);
        heap_insert(heap, result);
    }
}

void TopK(struct heap_node** heap){
    int n, i;

    if(numOfGraphs == 0) {
        printf("\n");
        return;
    }
    else if(numOfGraphs >= k) n = k;
    else n = numOfGraphs;

    for(i = 1; i < n; i++){
        printf("%d ", heap[i]->index);
    }
    printf("%d\n", heap[i]->index);
}

void getMatrix(){
    int ch, count, sum = 0;

    for(int i = 0; i < d; i++){
        count = 0;
        ch = getchar_unlocked();
        while(ch != '\n'){
            if(ch >= 48 && ch <= 57) {
                sum = sum*10 + ch - '0';
            }
            else {
                matrix[i][count++] = sum;
                sum = 0;
            }
            ch = getchar_unlocked();
        }
        matrix[i][count] = sum;
    }
}

void build_max_heap(struct heap_node **a){
    for(int i = ((k+1) / 2); i >= 1; i--){
        max_heapify(a,i);
    }
}

void heap_insert(struct heap_node** heap, unsigned int el){
    int i = k;
    heap[heap_size]->distance = el;
    heap[heap_size]->index = numOfGraphs - 1;

    while(i > 1 && heap[parent(i)]->distance < heap[i]->distance){
        swap(&heap[parent(i)], &heap[i]);
        i = parent(i);
    }
}

void heap_delete_max(struct heap_node** heap){
    *heap[1] = *heap[k];
    max_heapify(heap, 1);
}

void max_heapify(struct heap_node **a, int n){
    int l = left(n);
    int r = right(n);
    int pos;

    if(l <= heap_size && a[l]->distance > a[n]->distance){
        pos = l;
    }
    else pos = n;

    if(r <= heap_size && a[r]->distance > a[pos]->distance){
        pos = r;
    }

    if(pos != n){
        swap(&a[n], &a[pos]);
        max_heapify(a, pos);
    }
}

void swap(struct heap_node **x, struct heap_node **y){
    struct heap_node *temp = *x;
    *x = *y;
    *y = temp;
}

int left(int i){
    return (2*i);
}

int right(int i){
    return (2*i + 1);
}

int parent(int i){
    return (i/2);
}

bool hasPath(int weight, int x, int y){
    if(weight != INT_MAX && matrix[x][y] != 0) return true;
    else return false;
}

int findMinDistance(struct node* array){
    int minDist = INT_MAX, index = 0;
    for (int i = 0; i < d; i++){
        if (array[i].isProcessed == false && array[i].value <= minDist){
            minDist = array[i].value;
            index = i;
        }
    }
    return index;
}

unsigned int dijkstra(){
    struct node nodes[d];
    int x, y, numVertex, newDist;
    unsigned int sum = 0;

    for (int i = 1; i < d; i++){
        nodes[i].value = INT_MAX;
        nodes[i].isProcessed = false;
    }
    nodes[0].value = 0;
    nodes[0].isProcessed = false;
    numVertex = d;

    while(numVertex != 0){
        if(numVertex == d) x = 0;
        else x = findMinDistance(nodes);

        for (y = 0; y < d; y++){
            newDist = nodes[x].value + matrix[x][y];
            if (y != x //don't consider the distance of a node from itself
                &&
                hasPath(nodes[x].value, x, y) == true //there is a path between the nodes x and y
                &&
                nodes[y].isProcessed == false //the arrival node hasn't been visited yet
                &&
                newDist < nodes[y].value //check if any adjacent node has a shorter distance than the extracted one
            ){
                nodes[y].value = newDist; //update the node distance
            }
        }
        nodes[x].isProcessed = true;
        numVertex--;
    }

    for(int i = 1; i < d; i++){
        if(nodes[i].value != INT_MAX) sum += nodes[i].value;
    }
    return sum;
}