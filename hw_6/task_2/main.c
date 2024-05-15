#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct node
{
    int key;
    uint32_t height;
    struct node *left;
    struct node *right;
};

uint32_t height(struct node *p)
{
    return p ? p->height : 0;
}

int bfactor(struct node *p)
{
    return height(p->right) - height(p->left);
}

void fixheight(struct node *p)
{
    uint32_t hl = height(p->left);
    uint32_t hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

struct node *rotateleft(struct node *Y)
{
    struct node *X = Y->right;
    Y->right = X->left;
    X->left = Y;
    fixheight(Y);
    fixheight(X);
    return X;
}
struct node *rotateright(struct node *X)
{
    struct node *Y = X->left;
    X->left = Y->right;
    Y->right = X;
    fixheight(X);
    fixheight(Y);
    return Y;
}

struct node *balance(struct node *p)
{
    fixheight(p);
    if (bfactor(p) == 2)
    {
        if (bfactor(p->right) < 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if (bfactor(p) == -2)
    {
        if (bfactor(p->left) > 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p;
}

struct node *insert(struct node *p, int k)
{
    if (p == NULL)
    {
        p = malloc(sizeof(struct node));
        p->key = k;
        p->height = 0;
        p->left = p->right = NULL;
        return p;
    }
    if (k < p->key)
        p->left = insert(p->left, k);
    else
        p->right = insert(p->right, k);
    return balance(p);
}

void inorder(struct node *root)
{
    if (root == NULL)
        return;
    if (root->left)
        inorder(root->left);
    printf("%d ", root->key);
    if (root->right)
        inorder(root->right);
}
void summValue(struct node *root, int *summ)
{
    if (root == NULL)
        return;
    if (root->left)
         summValue(root->left, summ);
    *summ += root->key;
    if (root->right)
         summValue(root->right, summ);
}


int main(int argc, char const *argv[])
{
    struct node *tr = NULL;
    int value = 0;
    printf("Enter 0 to complete the entry\n");
    scanf("%d", &value);
    while (value != 0)
    {
        tr = insert(tr, value);
        scanf("%d", &value);
    }
    int summ = 0;
    summValue(tr, &summ);
    // inorder(tr);
    printf("Sum value = %d\n", summ);

    return 0;
}
