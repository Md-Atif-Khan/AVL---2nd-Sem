#include <stdio.h>
#include <stdlib.h>
struct tree
{
    int val;
    struct tree *left;
    struct tree *right;
};

struct tree *create_node(int n)
{
    struct tree *temp = (struct tree *)malloc(sizeof(struct tree));
    temp->val = n;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

int height(struct tree *root)
{
    if (root == NULL)
        return 0;
    else
    {
        int left_height = height(root->left);
        int right_height = height(root->right);
        if (left_height > right_height)
            return left_height + 1;
        else
            return right_height + 1;
    }
}

int balance_factor(struct tree *root)
{
    if (root == NULL)
        return 0;
    else
        return height(root->left) - height(root->right);
}

struct tree *ll_rotation(struct tree *root)
{
    struct tree *x, *y;
    x = root->left;
    y = x->right;
    x->right = root;
    root->left = y;
    return x;
}

struct tree *rr_rotation(struct tree *root)
{
    struct tree *x, *y;
    x = root->right;
    y = x->left;
    x->left = root;
    root->right = y;
    return x;
}

void search(struct tree *root, int n, int *count)
{
    if (root == NULL)
        printf("Given element doesn't exist\n");
    else if (n < root->val)
    {
        *count++;
        search(root->left, n, count);
    }
    else if (n > root->val)
    {
        *count++;
        search(root->right, n, count);
    }
    else
        printf("Given element exist, Access required: %d\n", *count);
}

struct tree *insert(struct tree *root, int n)
{
    if (root == NULL)
        return create_node(n);
    else if (n > root->val)
        root->right = insert(root->right, n);
    else if (n < root->val)
        root->left = insert(root->left, n);
    else
    {
        printf("Similar element is already present in the tree\n");
        return root;
    }
    int bf = balance_factor(root);
    // LL ROTATION
    if (bf > 1 && n < root->left->val)
        return ll_rotation(root);
    // RR ROTATION
    else if (bf < -1 && n > root->right->val)
        return rr_rotation(root);
    // LR ROTATION
    else if (bf > 1 && n > root->left->val)
    {
        root->left = rr_rotation(root->left);
        return ll_rotation(root);
    }
    // RL ROTATION
    else if (bf < -1 && n < root->right->val)
    {
        root->right = ll_rotation(root->right);
        return rr_rotation(root);
    }
    return root;
}

struct tree *inorder_predecessor(struct tree *root)
{
    if (root == NULL || root->right == NULL)
        return root;
    else
        return inorder_predecessor(root->right);
}

struct tree *delete_node(struct tree *root, int n)
{
    if (root == NULL)
    {
        printf("Given element doesn't exist\n");
        return root;
    }
    else if (n < root->val)
        root->left = delete_node(root->left, n);
    else if (n > root->val)
        root->right = delete_node(root->right, n);
    else if (root->left != NULL && root->right != NULL)
    {
        struct tree *temp = inorder_predecessor(root->left);
        root->val = temp->val;
        root->left = delete_node(root->left, root->val);
    }
    else if (root->left == NULL)
    {
        struct tree *temp = root->right;
        free(root);
        return temp;
    }
    else if (root->right == NULL)
    {
        struct tree *temp = root->left;
        free(root);
        return temp;
    }
    int bf = balance_factor(root);
    // LL ROTATION
    if (bf > 1 && balance_factor(root->left) >= 0)
        return ll_rotation(root);
    // LR ROTATION
    else if (bf > 1 && balance_factor(root->left) < 0)
    {
        root->left = rr_rotation(root->left);
        return ll_rotation(root);
    }
    // RR ROTATION
    else if (bf < -1 && balance_factor(root->right) <= 0)
        return rr_rotation(root);
    // RL ROTATION
    else if (bf < -1 && balance_factor(root->right) > 0)
    {
        root->right = ll_rotation(root->right);
        return rr_rotation(root);
    }
    return root;
}

void preorder_display(struct tree *root)
{
    if (root != NULL)
    {
        printf("%d ", root->val);
        preorder_display(root->left);
        preorder_display(root->right);
    }
}

void inorder_display(struct tree *root)
{
    if (root != NULL)
    {
        inorder_display(root->left);
        printf("%d ", root->val);
        inorder_display(root->right);
    }
}

void postorder_display(struct tree *root)
{
    if (root != NULL)
    {
        postorder_display(root->left);
        postorder_display(root->right);
        printf("%d ", root->val);
    }
}

void main()
{
    struct tree *root = NULL;
    int n, choice, count = 0;;
    while (1)
    {
        printf("***MENU***\n");
        printf("1-Insert a element\n");
        printf("2-Check if element exist\n");
        printf("3-Delete a node\n");
        printf("4-Preorder Display\n");
        printf("5-Inorder Display\n");
        printf("6-Postorder Display\n");
        printf("7-Exit\n");
        printf("Choose from above option\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter the value to be inserted in the AVL Tree\n");
            scanf("%d", &n);
            if (root == NULL)
                root = create_node(n);
            else
                root = insert(root, n);
            break;

        case 2:
            if (root == NULL)
                printf("No elements present\n");
            else
            {
                printf("Enter the element to be searched\n");
                scanf("%d", &n);
                search(root, n, &count);
            }
            break;

        case 3:
            printf("Enter the element to be deleted\n");
            scanf("%d", &n);
            root = delete_node(root, n);
            break;

        case 4:
            if (root == NULL)
                printf("No elements present\n");
            else
                preorder_display(root);
            printf("\n");
            break;

        case 5:
            if (root == NULL)
                printf("No elements present\n");
            else
                inorder_display(root);
            printf("\n");
            break;

        case 6:
            if (root == NULL)
                printf("No elements present\n");
            else
                postorder_display(root);
            printf("\n");
            break;

        case 7:
            exit(0);

        default:
            printf("Choose a correct option\n");
        }
    }
}