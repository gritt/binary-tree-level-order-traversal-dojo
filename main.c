#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;

};

struct node *insert(struct node *root, int data) {

    if (root == NULL) {

        struct node *node = (struct node *) malloc(sizeof(struct node));

        node->data = data;

        node->left = NULL;
        node->right = NULL;
        return node;

    } else {

        struct node *cur;

        if (data <= root->data) {
            cur = insert(root->left, data);
            root->left = cur;
        } else {
            cur = insert(root->right, data);
            root->right = cur;
        }

        return root;
    }
}

/*
 * Solution
 *
 * FIFO - first in, first out
 */

/**
 * a linked list queueNode to store a queue item, also contains a pointer to the tree node
 */
struct queueNode {
    int key;
    struct queueNode *next;
    struct node *node;
};

/**
 * a queue must keep track of the front and the rear indexes (nodes)
 */
struct queue {
    struct queueNode *front, *rear;
};

/**
 * creates a new 'linked list type' queueNode
 *
 * @param key
 * @param node
 * @return struct queueNode
 */
struct queueNode *newQueueNode(int key, struct node *node) {

    struct queueNode *qNode = (struct queueNode *) malloc(sizeof(struct queueNode));

    qNode->key = key;
    qNode->node = node;
    qNode->next = NULL;

    return qNode;
}

/**
 * creates a new queue
 *
 * @return struct queue
 */
struct queue *newQueue() {

    struct queue *q = (struct queue *) malloc(sizeof(struct queue));

    q->front = NULL;
    q->rear = NULL;

    return q;
}

/**
 * add a node to the given queue
 *
 * @param q
 * @param key
 * @param node
 */
void push(struct queue *q, int key, struct node *node) {

    // create a new linked list queueNode
    struct queueNode *tmpNode = newQueueNode(key, node);

    // if queue is empty, the new node is both front and rear
    if (q->rear == NULL) {
        q->front = q->rear = NULL;
        return;
    }

    // add new node at the end of the queue
    q->rear->next = tmpNode;
    q->rear = tmpNode;
}

/**
 * remove a node from the given queue
 *
 * @param q
 * @return struct queueNode
 */
struct queueNode *pop(struct queue *q) {

    // if the queue is empty, return NULL
    if (q->front == NULL) {
        return NULL;
    }

    // store previous front and move one node ahead
    struct queueNode *tmpNode = q->front;
    q->front = q->front->next;

    // if front becomes NULL, then change rear also to NULL (empty)
    if (q->front == NULL) {
        q->rear = NULL;
    }

    return tmpNode;
}


void levelOrder(struct node *root) {

    if (root == NULL) {
        return;
    }



    /*
     *  visit the nodes level by level from left to right.
     */

    printf("%d", root->data);

}

int main() {

    struct node *root = NULL;

    int treeSize;
    int data;

    scanf("%d", &treeSize);

    while (treeSize-- > 0) {
        scanf("%d", &data);
        root = insert(root, data);
    }

    levelOrder(root);
    return 0;
}