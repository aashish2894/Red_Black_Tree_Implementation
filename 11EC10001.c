#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0
#define MAXQUEUE 500
#define NULL 0

struct treenode
{
    int info;
    struct treenode *leftchild;
    struct treenode *rightchild;
    struct treenode *parent;
    int color; //0 for black and 1 for red
};
typedef struct treenode *NODEPTR;

struct queue
{
    NODEPTR items[MAXQUEUE];
    int front;
    int rear;
};

int empty(struct queue *pq);
NODEPTR dequeue(struct queue *pq);
void enqueue(struct queue *pq,NODEPTR x);
NODEPTR getnode();
NODEPTR BST_insert(NODEPTR *root,int x);
void RB_insert(NODEPTR *root,int x);
void LeftRotate(NODEPTR *root,NODEPTR x);
void RightRotate(NODEPTR *root,NODEPTR y);
void inorder(NODEPTR root);
void BFS(NODEPTR root);

int main()
{
    NODEPTR root;
    root = getnode();
    root = NULL;

    RB_insert(&root,5);

    RB_insert(&root,11);

    RB_insert(&root,3);

    RB_insert(&root,8);

    RB_insert(&root,9);

    RB_insert(&root,10);

    RB_insert(&root,14);

    RB_insert(&root,12);

    RB_insert(&root,1);

    RB_insert(&root,15);

    RB_insert(&root,20);

    RB_insert(&root,19);

    printf("BSF\n\n");
    BFS(root);

    return 0;
}

void RB_insert(NODEPTR *root,int x_info)
{
    NODEPTR x,y,temp;
    x = BST_insert(root,x_info);
    if(x==NULL)
    {
        return;
    }
    x->color = RED;
    while((x!=(*root)) && (x->parent->color==RED))
    {
        if(x->parent == x->parent->parent->leftchild)
        {
            y = x->parent->parent->rightchild;
            if(y!=NULL && y->color==RED)
            {
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else
            {
                if(x==x->parent->rightchild)
                {
                    x = x->parent;
                    LeftRotate(root,x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                RightRotate(root,x->parent->parent);
            }
        }
        else
        {
            y = x->parent->parent->leftchild;
            if(y!=NULL && y->color==RED)
            {
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else
            {
                if(x==x->parent->leftchild)
                {
                    x = x->parent;
                    RightRotate(root,x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                LeftRotate(root,x->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

NODEPTR BST_insert(NODEPTR *root,int x)
{
    NODEPTR p,q,S;
    p = getnode();
    p->info = x;
    if((*root)==NULL)
    {
        (*root) = p;
    }
    else
    {
        S = (*root);
        while(S!=NULL)
        {
            q = S;
            if(x == q->info)
            {
                printf("Already present\n\n");
                return NULL;
            }
            else if(x > S->info)
            {
                S = S->rightchild;
            }
            else
            {
                S = S->leftchild;
            }
        }
        if(x > q->info)
        {
            q->rightchild = p;
        }
        else
        {
            q->leftchild = p;
        }
        p->parent = q;
    }
    return(p);
}

void LeftRotate(NODEPTR *root,NODEPTR x)
{
    NODEPTR y;
    y = x->rightchild;
    x->rightchild = y->leftchild;
    if(y->leftchild!=NULL)
    {
        y->leftchild->parent = x;
    }
    if(x->parent == NULL)
    {
        (*root) = y;
    }
    else
    {
        y->parent = x->parent;
        if(x==x->parent->leftchild)
        {
            x->parent->leftchild = y;
        }
        else
        {
            x->parent->rightchild = y;
        }
    }

    y->leftchild = x;
    x->parent = y;
}

void RightRotate(NODEPTR *root,NODEPTR y)
{
    NODEPTR x;
    x = y->leftchild;
    y->leftchild = x->rightchild;
    if(x->rightchild!=NULL)
    {
        x->rightchild->parent = y;
    }
    if(y->parent == NULL)
    {
        (*root) = x;
    }
    else
    {
        x->parent = y->parent;
        if(y == y->parent->leftchild)
        {
            y->parent->leftchild = x;
        }
        else
        {
            y->parent->rightchild = x;
        }
    }

    x->rightchild = y;
    y->parent = x;
}

void inorder(NODEPTR root)
{
    if(root!=NULL)
    {
        inorder(root->leftchild);
        printf("%d\n",root->info);
        inorder(root->rightchild);
    }
}

void BFS(NODEPTR root)
{
    struct queue q,q2;
    q.front = MAXQUEUE - 1;
    q.rear = MAXQUEUE - 1;
    NODEPTR temp,NULL_node;
    int count1 = 0;
    int count2 = 0;
    NULL_node = getnode();
    NULL_node->info = -1;

    if(root==NULL)
    {
        printf("Empty tree");
        return;
    }
    enqueue(&q,root);
    count1++;

    while(count1!=0)
    {
        while(count1!=0)
        {
            temp = dequeue(&q);
            count1--;
            if(temp->info == -1)
            {
                printf("-1 ");
            }
            else
            {
                if(temp->color==BLACK)
                {
                    printf("B%d ",temp->info);
                }
                else
                {
                    printf("R%d ",temp->info);
                }
                if(temp->leftchild==NULL)
                {
                    enqueue(&q,NULL_node);
                }
                else
                {
                    enqueue(&q,temp->leftchild);
                }
                if(temp->rightchild==NULL)
                {
                    enqueue(&q,NULL_node);
                }
                else
                {
                    enqueue(&q,temp->rightchild);
                }
                count2 = count2 + 2;
            }
        }
        printf("\n");
        count1 = count2;
        count2 = 0;
    }
}

int empty(struct queue *pq)
{
    return(pq->front==pq->rear);
}

NODEPTR dequeue(struct queue *pq)
{
    if(empty(pq))
    {
        printf("Queue underflow\n");
    }
    if(pq->front==MAXQUEUE-1)
    {
        pq->front = 0;
    }
    else
    {
        pq->front = pq->front + 1;
    }
    return(pq->items[pq->front]);
}

void enqueue(struct queue *pq,NODEPTR x)
{
    if(pq->rear==MAXQUEUE-1)
    {
        pq->rear = 0;
    }
    else
    {
        pq->rear = pq->rear + 1;
    }
    if(pq->rear==pq->front)
    {
        printf("Queue Overflow\n");
    }
    else
    {
        pq->items[pq->rear] = x;
    }
}


NODEPTR getnode()
{
    NODEPTR p;
    p = (NODEPTR)malloc(sizeof(struct treenode));
    p->leftchild = NULL;
    p->rightchild = NULL;
    p->parent = NULL;
    return (p);
}
