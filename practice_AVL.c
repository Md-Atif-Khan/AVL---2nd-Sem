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

struct tree *insert(struct tree *root, int n)
{
    if (root == NULL)
        return create_node(n);
    else if (n < root->val)
        root->left = insert(root->left, n);
    else if (n > root->val)
        root->right = insert(root->right, n);
    return root;
}

void search(struct tree *root, int n)
{
    if (root == NULL)
        printf("Element is not present in tree\n");
    else if (n < root->val)
        search(root->left, n);
    else if (n > root->val)
        search(root->right, n);
    else
        printf("Given element is present in the tree\n");
}

struct tree *inorder_predecessor(struct tree *root)
{
    if (root == NULL || root->right == NULL)
        return root;
    else
        return inorder_predecessor(root->right);
}

struct tree *inorder_successor(struct tree *root)
{
    if (root == NULL || root->left == NULL)
        return root;
    else
        return inorder_successor(root->left);
}

struct tree *delete_node(struct tree *root, int n)
{
    if (root == NULL)
    {
        printf("Given element doesn't exists\n");
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
        // struct tree *temp = inorder_successor(root->right);
        // root->val = temp->val;
        // root->right = delete_node(root->right, root->val);
    }
    else if (root->left != NULL)
    {
        struct tree *temp = root->left;
        free(root);
        return temp;
    }
    else if (root->right != NULL)
    {
        struct tree *temp = root->right;
        free(root);
        return temp;
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

void min_element(struct tree *root)
{
    if (root->left == NULL)
        printf("Minimum element in the tree is %d \n", root->val);
    else
        min_element(root->left);
}

void max_element(struct tree *root)
{
    if (root->right == NULL)
        printf("Maximum element in the tree is %d \n", root->val);
    else
        max_element(root->right);
}

int total_nodes(struct tree *root)
{
    if (root == NULL)
        return 0;
    else
        return (total_nodes(root->left) + total_nodes(root->right) + 1);
}

int total_internal_nodes(struct tree *root)
{
    if (root == NULL || (root->left == NULL && root->right == NULL))
        return 0;
    else
        return (total_internal_nodes(root->left) + total_internal_nodes(root->right) + 1);
}

int total_leaf_nodes(struct tree *root)
{
    if (root == NULL)
        return 0;
    else if (root->left == NULL && root->right == NULL)
        return 1;
    else
        return (total_leaf_nodes(root->left) + total_leaf_nodes(root->right));
}

int height_tree(struct tree *root)
{
    if (root == NULL)
        return 0;
    else
    {
        int left_height, right_height;
        left_height = height_tree(root->left);
        right_height = height_tree(root->right);
        if (left_height > right_height)
            return (left_height + 1);
        else
            return (right_height + 1);
    }
}
// //DOUBT--> HOW TO MIRROR IT AND THEN APPLY DELETE NODE FUNCTION
// void mirror(struct tree **root)
// {
//     if ((*root) != NULL)
//     {
//         (*root)=(*root)->left; //SEGMENTATION FAULT
//         mirror(root);
//         (*root)=(*root)->right;
//         mirror(root);
//         struct tree *temp = (*root)->left;
//         (*root)->left = (*root)->right;
//         (*root)->right = temp;
//     }
// }

struct tree *delete_tree(struct tree *root)
{
    if (root != NULL)
    {
        delete_tree(root->left);
        delete_tree(root->right);
        free(root);
    }
}

void main()
{
    int choice, n;
    struct tree *root = NULL;
    while (1)
    {
        printf("***MENU***\n");
        printf("1-Insert a element\n");
        printf("2-Check if element exist\n");
        printf("3-Delete a node\n");
        printf("4-Preorder Display\n");
        printf("5-Inorder Display\n");
        printf("6-Postorder Display\n");
        printf("7-Display Minimum element\n");
        printf("8-Display Maximum element\n");
        printf("9-Count total nodes\n");
        printf("10-Count total leaf/external nodes\n");
        printf("11-Count total internal nodes\n");
        printf("12-Height of tree\n");
        printf("13-Mirror the tree\n");
        printf("14-Delete whole tree\n");
        printf("15-Exit\n");
        printf("Choose from above option\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter the element to be inserted\n");
            scanf("%d", &n);
            if (root == NULL)
                root = create_node(n);
            else
                root = insert(root, n);
            break;

        case 2:
            printf("Enter the element to be searched\n");
            scanf("%d", &n);
            search(root, n);
            break;

        case 3:
            printf("Enter the element to be deleted\n");
            scanf("%d", &n);
            root = delete_node(root, n);
            break;

        case 4:
            if (root == NULL)
                printf("Tree is empty\n");
            else
                preorder_display(root);
            printf("\n");
            break;

        case 5:
            if (root == NULL)
                printf("Tree is empty\n");
            else
                inorder_display(root);
            printf("\n");
            break;

        case 6:
            if (root == NULL)
                printf("Tree is empty\n");
            else
                postorder_display(root);
            printf("\n");
            break;

        case 7:
            if (root == NULL)
                printf("Tree is empty\n");
            else
                min_element(root);
            break;

        case 8:
            if (root == NULL)
                printf("Tree is empty\n");
            else
                max_element(root);
            break;

        case 9:
            printf("Total no. of nodes in the tree: %d\n", total_nodes(root));
            break;

        case 10:
            printf("Total no. of leaf nodes in the tree: %d\n", total_leaf_nodes(root));
            break;

        case 11:
            printf("Total no. of internal nodes in the tree: %d\n", total_internal_nodes(root));
            break;

        case 12:
            printf("Height of the BST is %d\n", height_tree(root));
            break;

        case 13:
            mirror(&root);
            break;

        case 14:
            root = delete_tree(root);
            break;

        case 15:
            exit(0);

        default:
            printf("Please choose a valid option\n");
            break;
        }
    }
}

// #include <stdio.h>
// #include <stdlib.h>
// struct tree
// {
//     int val;
//     struct tree *left, *right;
// };

// struct tree *create_node(int n)
// {
//     struct tree *temp = (struct tree *)malloc(sizeof(struct tree));
//     temp->val = n;
//     temp->left = NULL;
//     temp->right = NULL;
//     return temp;
// }

// void search(struct tree *root, int n)
// {
//     if(root == NULL)
//     {
//         printf("Element not present\n");
//         return;
//     }
//     else if(n < root->val)
//         search(root->left, n);
//     else if(n > root->val)
//         search (root->right, n);
//     else
//         printf("Element is present\n");
// }

// int height(struct tree *root)
// {
//     if(root == NULL)
//         return 0;
//     else
//     {
//         int lh = height(root->left);
//         int rh = height(root->right);
//         if(lh > rh)
//             return lh + 1;
//         else
//             return rh + 1;
//     }
// }

// int balance_factor(struct tree *root)
// {
//     if(root == NULL)
//         return 0;
//     else
//         return height(root->left) - height(root->right);
// }

// struct tree *ll_rotation(struct tree *root)
// {
//     struct tree *x, *y;
//     x = root->left;
//     y = x->right;
//     x->right = root;
//     root->left = y;
//     return x;
// }

// struct tree *rr_rotation(struct tree *root)
// {
//     struct tree *x, *y;
//     x = root->right;
//     y = x->left;
//     x->left = root;
//     root->right = y;
//     return x;
// }

// struct tree *inorder_predecessor(struct tree *root)
// {
//     if(root == NULL || root->right == NULL)
//         return root;
//     return inorder_predecessor(root->left);
// }

// struct tree *inorder_sucessor(struct tree *root)
// {
//     if(root == NULL || root->left == NULL)
//         return root;
//     return inorder_sucessor(root->right);
// }

// struct tree *insert_node(struct tree *root, int n)
// {
//     if(root == NULL)
//     {
//         struct tree *temp = create_node(n);
//         root = temp;
//     }
//     else if(n < root->val)
//         root->left = insert_node(root->left, n);
//     else if(n > root->val)
//         root->right = insert_node(root->right, n);
//     int bf = balance_factor(root);
//     if(bf < -1 && balance_factor(root->right) <= 0)
//         return rr_rotation(root);
//     else if(bf < -1)
//     {
//         root->right = ll_rotation(root->right);
//         return rr_rotation(root);
//     }
//     else if (bf > 1 && balance_factor(root->left) >= 0)
//         return ll_rotation(root);
//     else if (bf > 1)
//     {
//         root->left = rr_rotation(root->left);
//         return ll_rotation(root);
//     }
//     return root;
// }

// struct tree *delete(struct tree *root, int n)
// {
//     if(root == NULL)
//         printf("Given element doesn't exist\n");
//     else if(n < root->val)
//         root->left = delete(root->left, n);
//     else if(n > root->val)
//         root->right = delete(root->right, n);
//     else if(root->left != NULL && root->right != NULL)
//     {
//         struct tree *temp = inorder_predecessor(root->left);
//         root->val = temp->val;
//         root->left = delete(root->left, root->val);
//     }
//     else if(root->left == NULL)
//     {
//         struct tree *temp = root->right;
//         free(root);
//         return temp;
//     }
//     else if(root->right == NULL)
//     {
//         struct tree *temp = root->left;
//         free(root);
//         return temp;
//     }
//     return root;
// }

// void pre_display(struct tree *root)
// {
//     if(root != NULL)
//     {
//         printf("%d ", &root->val);
//         pre_display(root->left);
//         pre_display(root->right);
//     }
// }

// void in_display(struct tree *root)
// {
//     if(root != NULL)
//     {
//         in_display(root->left);
//         printf("%d ", root->val);
//         in_display(root->right);
//     }
// }

// void po_display(struct tree *root)
// {
//     if(root != NULL)
//     {
//         po_display(root->left);
//         po_display(root->right);
//         printf("%d ", root->val);
//     }
// }

// int min_element(struct tree *root)
// {
//     if(root->left == NULL)
//         return root->val;
//     else 
//         return min_element(root->left);
// }

// int max_element(struct tree *root)
// {
//     if(root->right == NULL)
//         return root->val;
//     else
//         return max_element(root->right);
// }

// int total_count(struct tree *root)
// {
//     if(root == NULL)
//         return 0;
//     else
//         return total_count(root->left) + total_count(root->right) + 1;
// }

// int total_leaf(struct tree *root)
// {
//     if(root == NULL)
//         return 0;
//     else if(root->left == NULL && root->right == NULL)
//         return 1;
//     else
//         return total_leaf(root->left) + total_leaf(root->right);
// }

// int total_internal(struct tree *root)
// {
//     if(root == NULL || (root->left == NULL && root->right == NULL))
//         return 0;
//     else
//         return total_internal(root->left) + total_internal(root->right) + 1;
// }



// void main()
// {
//     struct tree *root = NULL;
//     int n, choice;
//     while (1)
//     {
//         printf("***MENU***\n");
//         printf("1-Insert a element\n");
//         printf("2-Check if element exist\n");
//         printf("3-Delete a node\n");
//         printf("4-Preorder Display\n");
//         printf("5-Inorder Display\n");
//         printf("6-Postorder Display\n");
//         printf("7-Display Minimum element\n");
//         printf("8-Display Maximum element\n");
//         printf("9-Count total nodes\n");
//         printf("10-Count total leaf/external nodes\n");
//         printf("11-Count total internal nodes\n");
//         printf("12-Height of tree\n");
//         printf("13-Mirror the tree\n");
//         printf("14-Delete whole tree\n");
//         printf("15-Exit\n");
//         printf("Choose from above option\n");
//         scanf("%d", &choice);
//         switch (choice)
//         {
//             case 1:
//                 printf("Enter a element\n");
//                 scanf("%d", &n);
//                 if(root == NULL)
//                     root = create_node(n);
//                 else
//                     root = insert_node(root, n);
//                 break;


//         }
//     }
// }