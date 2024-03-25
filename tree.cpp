#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

TREE_ERROR TreeAdd (Node* Tree, const elem_t* elem)
{
    if (Tree == nullptr) return TREE_NULLPTR;
    if (elem == nullptr) return TREE_ELEM_NULLPTR;

    Node* new_Tree_elem = nullptr;
    if ((new_Tree_elem = (Node*) calloc (1, sizeof (Node) )) == nullptr)
        return TREE_CALLOC_ERROR;
    new_Tree_elem->value = *elem;

    while (1)
    {
        if (*elem <= Tree->value)
            if (Tree->left == nullptr)
            {
                Tree->left = new_Tree_elem;
                break;
            }
            else
                Tree = Tree->left;

        else
            if (Tree->right == nullptr)
            {
                Tree->right = new_Tree_elem;
                break;
            }
            else
                Tree = Tree->right;
    }

    return TREE_NO_ERROR;
}

TREE_ERROR TreePrint (const Node* Tree)
{
    if (Tree == nullptr)
        return TREE_NULLPTR;

    printf ("{\n%d\n", Tree->value);

    if (Tree->left != nullptr)
        TreePrint (Tree->left);
    else puts ("*");
    if (Tree->right != nullptr)
        TreePrint (Tree->right);
    else puts ("*");

    puts ("}");

    return TREE_NO_ERROR;
}

TREE_ERROR TreeCtor (Node* Tree, const elem_t* elem)
{
    if (Tree == nullptr) return TREE_NULLPTR;

    if (elem != nullptr) Tree->value = *elem;
    Tree->left = nullptr;
    Tree->right = nullptr;

    return TREE_NO_ERROR;
}

TREE_ERROR TreeCtor (Node* Tree)
{
    if (Tree == nullptr) return TREE_NULLPTR;

    Tree->left = nullptr;
    Tree->right = nullptr;

    return TREE_NO_ERROR;
}

TREE_ERROR TreeDtor (Node* Tree)
{
    if (Tree == nullptr)
        return TREE_NULLPTR;

    if (Tree->left != nullptr)
        TreeDtor (Tree->left);
    if (Tree->right != nullptr)
        TreeDtor (Tree->right);

    free (Tree->left);
    free (Tree->right);

    Tree->value = 0;
    Tree->left = nullptr;
    Tree->right = nullptr;

    return TREE_NO_ERROR;
}

TREE_ERROR TreeDelete (Node* Tree, const elem_t* elem)
{
    if (Tree == nullptr) return TREE_NULLPTR;
    if (elem == nullptr) return TREE_ELEM_NULLPTR;
    Node* prevNode = nullptr;

    int Tree_left_or_right = 0;

    if (Tree->value == *elem)
    {
        return ELEM_IS_VALUE_OF_NODE_OF_TREE;
    }

    while (Tree->value != *elem)
        if (*elem <= Tree->value)
        {
            if (Tree->left == nullptr)
                return TREE_NO_ELEM;

            prevNode = Tree;
            Tree = Tree->left;
            Tree_left_or_right = 1;
        }

        else
            if (Tree->right != nullptr)
            {
                prevNode = Tree;
                Tree = Tree->right;
                Tree_left_or_right = 0;
            }
            else return TREE_NO_ELEM;

    if (Tree->left != nullptr && Tree->right != nullptr)
    {
        TreeAddNode (Tree->left, Tree->right);
        switch (Tree_left_or_right)
        {
            case 0:
                prevNode->right = Tree->left;
                break;
            case 1:
                prevNode->left = Tree->left;
                break;
        }
    }

    else if (Tree->left != nullptr)
        switch (Tree_left_or_right)
        {
            case 0:
                prevNode->right = Tree->left;
                break;
            case 1:
                prevNode->left = Tree->left;
                break;
        }

    else if (Tree->right != nullptr)
        switch (Tree_left_or_right)
        {
            case 0:
                prevNode->right = Tree->right;
                break;
            case 1:
                prevNode->left = Tree->right;
                break;
        }

    else
        switch (Tree_left_or_right)
        {
            case 0:
                prevNode->right = nullptr;
                break;
            case 1:
                prevNode->left = nullptr;
                break;
        }

    free (Tree);

    return TREE_NO_ERROR;
}

TREE_ERROR TreeAddNode (Node* Tree, Node* NodeAdd)
{
    if (Tree == nullptr) return TREE_NULLPTR;
    if (NodeAdd == nullptr) return TREE_NULLPTR;

    while (1)
    {
        if (NodeAdd->value <= Tree->value)
            if (Tree->left == nullptr)
            {
                Tree->left = NodeAdd;
                break;
            }
            else
                Tree = Tree->left;

        else
            if (Tree->right == nullptr)
            {
                Tree->right = NodeAdd;
                break;
            }
            else
                Tree = Tree->right;
    }

    return TREE_NO_ERROR;
}
