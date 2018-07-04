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

/**
 * A 'linked list' style QueueNode, which points to the next QueueNode
 */
struct QueueNode {
    struct node *node;
    struct QueueNode *next;
};

/**
 * A classic Queue, that keeps track of the front and the rear nodes
 */
struct Queue {
    struct QueueNode *front, *rear;
};

/**
 * Creates a new QueueNode
 *
 * @param key
 * @return
 */
struct QueueNode *newNode(struct node *node) {

    struct QueueNode *tmpNode = (struct QueueNode *) malloc(sizeof(struct QueueNode));

    tmpNode->node = node;
    tmpNode->next = NULL;

    return tmpNode;
}

/**
 * Creates a new Queue
 *
 * @return
 */
struct Queue *newQueue() {

    struct Queue *q = (struct Queue *) malloc(sizeof(struct Queue));

    q->front = q->rear = NULL;

    return q;
}

/**
 * Adds a new QueueNode to the end of the Queue
 *
 * @param q
 * @param key
 */
void enQueue(struct Queue *q, struct node *node) {

    struct QueueNode *tmpNode = newNode(node);

    // if queue is empty, then the new node is both front and rear
    if (q->rear == NULL) {
        q->front = q->rear = tmpNode;
        return;
    }

    // add the new node at the end of queue and change rear
    q->rear->next = tmpNode;
    q->rear = tmpNode;
}

/**
 * Removes a QueueNode of the front of the Queue, moves front->next to actual "front"
 *
 * @param q
 * @return
 */
struct QueueNode *deQueue(struct Queue *q) {

    // if queue is empty, return NULL.
    if (q->front == NULL) {
        return NULL;
    }

    // store previous front and move front one node ahead
    struct QueueNode *tmpNode = q->front;
    q->front = q->front->next;

    // if front becomes NULL, then change rear also as NULL
    if (q->front == NULL)
        q->rear = NULL;

    return tmpNode;
}

/**
 * Checks whether the Queue is empty
 *
 * @param q
 * @return
 */
int isEmpty(struct Queue *q) {

    // queue is empty if there's no front or rear nodes
    if (q->front == NULL && q->rear == NULL) {
        return 1;
    }

    return 0;
}


void levelOrder(struct node *root) {

    if (root == NULL) {
        return;
    }

    /*
     * Solution:
     *
     * First node is visited, than removed, child nodes are put in a FIFO queue,
     * The loop continues till the queue is empty
     *
     *
     * Using Queue Linked List algorithm from
     * https://github.com/gritt/queue-linked-list
     */
    struct Queue *treeQueue = newQueue();

    /*
     * root node is added to the queue (1)
     *
     * while the queue is not consumed {
     *
     *      we visit the first node of the queue (1)
     *
     *      we then remove the first node of the queue (empty)
     *
     *      and we add it's child nodes to the queue, left(2) -> right(3), as is expected to show in level order traversal)
     *
     *      following the loop..
     *
     *      we visit the first node of the queue - left(2)
     *
     *      we then remove the first node of the queue (left the right node at front (3))
     *
     *      add left and right child..
     *
     *      visit the first node - right(3)
     *
     *      remove it..
     *
     *      add left and right
     * }
     */

    enQueue(treeQueue, root);

    while (isEmpty(treeQueue) == 0) {

        struct QueueNode *queueNode = treeQueue->front;

        printf("%d", queueNode->node->data);

        deQueue(treeQueue);

        // enqueue left child
        if (queueNode->node->left != NULL) {
            enQueue(treeQueue, queueNode->node->left);
        }

        // enqueue right child
        if (queueNode->node->right != NULL) {
            enQueue(treeQueue, queueNode->node->right);
        }
    }
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
