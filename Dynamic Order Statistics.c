
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define TABLE_SIZE 805

typedef enum
{
    red,
    black
} Color;

typedef struct Node
{
    int key;
    Color color;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
    int size;
} Node;



// struct node {
//     int data;
//     struct node* next;
// };

Node NULL_NODE = {0, black, NULL, NULL, NULL};

Node *createNode(int key)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode != NULL)
    {
        newNode->key = key;
        newNode->color = red;
        newNode->parent = NULL;
        newNode->left = &NULL_NODE;
        newNode->right = &NULL_NODE;
        newNode->size = 1;
    }
    return newNode;
}

void leftRotate(Node **root, Node *x)
{
    Node *y = x->right;
    x->right = y->left;
    if (y->left != &NULL_NODE)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL)
    {
        *root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void rightRotate(Node **root, Node *y)
{
    Node *x = y->left;
    y->left = x->right;
    if (x->right != &NULL_NODE)
    {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NULL)
    {
        *root = x;
    }
    else if (y == y->parent->left)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

Node *rbSearch(Node *root, int key)
{
    while (root != &NULL_NODE && key != root->key)
    {
        if (key < root->key)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }
    return root;
}

void rbInsertFixup(Node **root, Node *z)
{
    while (z->parent != NULL && z->parent->color == red)
    {
        if (z->parent == z->parent->parent->left)
        {
            Node *y = z->parent->parent->right;
            if (y->color == red)
            {

                z->parent->color = black;
                y->color = black;
                z->parent->parent->color = red;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {

                    z = z->parent;
                    leftRotate(root, z);
                }

                z->parent->color = black;
                z->parent->parent->color = red;
                rightRotate(root, z->parent->parent);
            }
        }
        else
        {

            Node *y = z->parent->parent->left;
            if (y->color == red)
            {

                z->parent->color = black;
                y->color = black;
                z->parent->parent->color = red;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {

                    z = z->parent;
                    rightRotate(root, z);
                }

                z->parent->color = black;
                z->parent->parent->color = red;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = black;
}

void rbInsert(Node **root, int key)
{
    Node *z = createNode(key);
    Node *y = NULL;
    Node *x = *root;

    while (x != &NULL_NODE)
    {
        y = x;
        if (z->key < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    z->parent = y;
    if (y == NULL)
    {
        *root = z;
    }
    else if (z->key < y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }

    rbInsertFixup(root, z);
}

Node *findMinimum(Node *x)
{
    while (x->left != &NULL_NODE)
    {
        x = x->left;
    }
    return x;
}

void rbDeleteFixup(Node **root, Node *x)
{
    while (x != *root && x->color == black)
    {
        if (x == x->parent->left)
        {
            Node *w = x->parent->right;
            if (w->color == red)
            {

                w->color = black;
                x->parent->color = red;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == black && w->right->color == black)
            {
                w->color = red;
                x = x->parent;
            }
            else
            {
                if (w->right->color == black)
                {

                    w->left->color = black;
                    w->color = red;
                    rightRotate(root, w);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = black;
                w->right->color = black;
                leftRotate(root, x->parent);
                x = *root;
            }
        }
        else
        {

            Node *w = x->parent->left;
            if (w->color == red)
            {

                w->color = black;
                x->parent->color = red;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == black && w->left->color == black)
            {

                w->color = red;
                x = x->parent;
            }
            else
            {
                if (w->left->color == black)
                {

                    w->right->color = black;
                    w->color = red;
                    leftRotate(root, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = black;
                w->left->color = black;
                rightRotate(root, x->parent);
                x = *root;
            }
        }
    }
    x->color = black;
}

void rbTransplant(Node **root, Node *u, Node *v)
{
    if (u->parent == NULL)
    {
        *root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void rbDelete(Node **root, int key)
{
    Node *z = rbSearch(*root, key);
    if (z == &NULL_NODE)
    {
        printf("element %d not present in the RBT.\n", key);
        return;
    }

    Node *y = z;
    Node *x;
    Color yOriginalColor = y->color;

    if (z->left == &NULL_NODE)
    {
        x = z->right;
        rbTransplant(root, z, z->right);
    }
    else if (z->right == &NULL_NODE)
    {
        x = z->left;
        rbTransplant(root, z, z->left);
    }
    else
    {
        y = findMinimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            rbTransplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rbTransplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);

    if (yOriginalColor == black)
    {
        rbDeleteFixup(root, x);
    }
}

void inOrderTraversal(Node *root)
{
    if (root != &NULL_NODE)
    {
        inOrderTraversal(root->left);
        printf("%d ", root->key);
        inOrderTraversal(root->right);
    }
}

void preOrderTraversal(Node *root)
{
    if (root != &NULL_NODE)
    {
        printf("%d ", root->key);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

int os_select(Node *root, int kth)
{
    if (root == &NULL_NODE)
        return -1;  // Handle an invalid case, you may choose a different way to indicate failure.

    int r = root->left->size + 1;

    if (kth == r)
        return root->key;
    else if (kth < r)
        return os_select(root->left, kth);
    else
        return os_select(root->right, kth - r);
}

// int os_select(Node *root, int kth)
// {
//     int r = root->left->size + 1;
//     if(kth == r)
//         return root;
//     else if (kth<r)
//         return os_select(root->left, kth);
//     else
//         return os_select(root->right, kth-1);
// }


// int count = 0;
// Node* kthSmallest(Node* root, int k)
// {
//     // base case
//     if (root == NULL)
//         return NULL;
 
//     // search in left subtree
//     Node* left = kthSmallest(root->left, k);
 
//     // if k'th smallest is found in left subtree, return it
//     if (left != NULL)
//         return left;
 
//     // if current element is k'th smallest, return it
//     count++;
//     if (count == k)
//         return root;
 
//     // else search in right subtree
//     return kthSmallest(root->right, k);
// }

// void printKthSmallest(Node* root, int k)
// {
//     // maintain index to count number of nodes processed so far
//     Node* res = kthSmallest(root, k);
//     if (res == NULL)
//         printf("There are less than k nodes in the BST");
//     else
//     {
//         printf("K-th Smallest Element is %d", res->key);
//         // printf("K-th Smallest Element is %d", res->left->key);
//         // printf("K-th Smallest Element is %d", res->right->key);
//     }
        
// }




int main()
{
    Node *root = &NULL_NODE;
    int size, kth_smallest,mth_successor;
    // int var;
    int i;
    scanf("%d",&size);
    scanf("%d",&kth_smallest);
    scanf("%d",&mth_successor);
   
    int insert_element[size];
    
   for(i=0;i<size;i++)
    {
       scanf("%d",&insert_element[i]);
       rbInsert(&root, insert_element[i]);
    }
  int result = os_select(root, kth_smallest);
    if (result != -1)
    {
        printf("The %dth smallest number is: %d\n", kth_smallest, result);
    }
    else
    {
        printf("Invalid input or kth smallest not found.\n");
    }

    int result = os_select(root, kth_smallest);
    printf("%d",result);
    printf("\n");
    preOrderTraversal(root);
    printf("\n");
    inOrderTraversal(root);

}
