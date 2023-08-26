#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 100

// Node structure for Huffman tree
struct Node {
    char data;
    unsigned freq;
    struct Node *left, *right;
};

// Priority queue structure for Huffman tree nodes
struct PriorityQueue {
    unsigned size;
    unsigned capacity;
    struct Node **array;
};

// Function to create a new node
struct Node* newNode(char data, unsigned freq) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->left = node->right = NULL;
    node->data = data;
    node->freq = freq;
    return node;
}

// Function to create a priority queue
struct PriorityQueue* createQueue(unsigned capacity) {
    struct PriorityQueue* queue = (struct PriorityQueue*) malloc(sizeof(struct PriorityQueue));
    queue->size = 0;
    queue->capacity = capacity;
    queue->array = (struct Node**) malloc(queue->capacity * sizeof(struct Node*));
    return queue;
}

// Function to swap two nodes
void swapNodes(struct Node** a, struct Node** b) {
    struct Node* t = *a;
    *a = *b;
    *b = t;
}

// Function to heapify the priority queue
void minHeapify(struct PriorityQueue* queue, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    if (left < queue->size && queue->array[left]->freq < queue->array[smallest]->freq)
        smallest = left;
    if (right < queue->size && queue->array[right]->freq < queue->array[smallest]->freq)
        smallest = right;
    if (smallest != idx) {
        swapNodes(&queue->array[smallest], &queue->array[idx]);
        minHeapify(queue, smallest);
    }
}

// Function to check if the priority queue has only one node left
int isSizeOne(struct PriorityQueue* queue) {
    return queue->size == 1;
}

// Function to extract the minimum node from the priority queue
struct Node* extractMin(struct PriorityQueue* queue) {
    struct Node* temp = queue->array[0];
    queue->array[0] = queue->array[queue->size - 1];
    --queue->size;
    minHeapify(queue, 0);
    return temp;
}

// Function to insert a node into the priority queue
void insertNode(struct PriorityQueue* queue, struct Node* node) {
    ++queue->size;
    int i = queue->size - 1;
    while (i && node->freq < queue->array[(i - 1) / 2]->freq) {
        queue->array[i] = queue->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    queue->array[i] = node;
}

// Function to build the Huffman tree
struct Node* buildHuffmanTree(char data[], int freq[], int size) {
    struct Node *left, *right, *top;
    struct PriorityQueue* queue = createQueue(size);
    for (int i = 0; i < size; ++i)
        insertNode(queue, newNode(data[i], freq[i]));
    while (!isSizeOne(queue)) {
        left = extractMin(queue);
        right = extractMin(queue);
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

